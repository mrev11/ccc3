
/*
 *  CCC - The Clipper to C++ Compiler
 *  Copyright (C) 2005 ComFirm BT.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "fileio.ch" 
#include "tabobj.ch" 

******************************************************************************
//Public interface

//function tabOpen(table,mode,userblock)  //megnyitja a table-t 
//function tabGoEOF(table)                //EOF-ra áll (belső)
//function tabClose(table)                //lezárja a table-t
//function tabCloseAll()                  //minden table-t lezár
//function tabIsOpen(table)               //nyitási mód


******************************************************************************
static function setquitblock()
static flag:=.t.
local blk
    if( flag )
        flag:=.f.
        blk:=quitblock()
        quitblock({||qb(),eval(blk)}) 
    end

static function qb()
    if( errorlevel()==0 )
        tranRollback(1)
        tabCloseAll()
    end
    

******************************************************************************
#ifdef KORABBI_VALTOZAT
static function setquitblock()

static flag:=.f.
local blk,blk1

    if( !flag )
        flag:=.t.

        blk:=quitblock()
        //quitblock({||qout("quit: tabCloseAll"),tabCloseAll(),eval(blk)}) 
        quitblock({||tranRollback(1),tabCloseAll(),eval(blk)}) 

        if( "TABTBROWSE" $ getenv("QUITBLOCK") )
            blk1:=quitblock()
            //quitblock({||qout("quit: tabTBrowse"),tabTBrowse(),eval(blk1)})
            //quitblock({||tabTBrowse(),eval(blk1)})
        end
    end
    return NIL
#endif // KORABBI_VALTOZAT


******************************************************************************
function tabOpen(table,mode,userblock) //megnyitja a db-t 

local fname:=lower(tabPathName(table)), n, dbf
local errblk, err

    setquitblock()

    tranNotAllowedInTransaction(table,"open",.t.)
 
    if( !file(fname) )

        //teszteléshez automatikus dbf->dat konverzió
        dbf:=lower(tabPath(table)+tabFile(table)+".dbf")
        if( file(dbf)  )
            tabCreate(table)
            tabOpen(table,OPEN_EXCLUSIVE)
            tabLoadDBF(table,dbf)

        else
            n:=alert(fname+@" not found, create?",{@"Create",@"Quit"})
            if( n==2 )
                taberrOperation("tabOpen")
                taberrDescription(@"file not found")
                tabError(table)
            else
                tabCreate(table)
            end
        end
    end

    tabClose(table)

    if( empty(mode) )
        mode:=OPEN_SHARED
    elseif( valtype(mode)=="C" )
        mode:=openmode(mode)
    end

    if( valtype(mode)!="N".or.mode<OPEN_READONLY.or.OPEN_APPEND<mode )
        taberrOperation("tabOpen")
        taberrDescription(@"invalid open mode")
        taberrArgs(mode)
        tabError(table)
    end

    if( mode>OPEN_EXCLUSIVE ) //OPEN_APPEND implementációja később
        mode:=OPEN_EXCLUSIVE
    end
 
    while( .t. )
 
        while( 0>=tabSlock(table,{||0}) .or. !tabUse(table,mode) )
            tabSunlock(table)

            taberrOperation("tabOpen")
            taberrDescription(@"open failed") 
            taberrUserBlock(userblock,"PUK")

            if( valtype(userblock)=="B" )
                return tabError(table) 
            else
                tabError(table)
            end
        end
        tabSunlock(table)
        
        begin
            tabVerify(table)  //kiszámítja table[TAB_RECLEN]-t
            //Az új begin/recover/finally-ból szabad kiugrani.
            exit //OK

            //Ha az objektum és a filé inkompatibilisek,
            //akkor tabVerify tabindexerror/tabstructerror-t dob,
            //és err:args-ban az inkompatibilis indexek neve van,
            //amit meg kell jegyezni a konverzióhoz.

        recover err <tabindexerror>

            err:candefault:=.t.
            break(err)

            //Csak akkor jön vissza, 
            //ha az interaktív alertben a "Default"-ot választották.
            //Probléma, ha a breaket eltéríti egy külső recover.

            //visszazár
            tabClose(table)
            
            if( 0<tabSlock(table,{||0}) .and. tabUse(table,OPEN_EXCLUSIVE) )
                tabSunlock(table)
                //konverzió (reindex)
                tabAlloc(table) 
                tabGotop(table) 
                build_bt_index(table,err:args,.t.)
                tabClose(table)
            end
            tabSunlock(table)
        end
    end
 
    tabAlloc(table) 
    tabSetFieldTable(table)
    tabGotop(table) 
    table[TAB_OPEN]:=mode
    return .t.


******************************************************************************
static function tabUse(table,mode)  //megnyit egy dbf-et

local fname:=lower(tabPathName(table))
local fmode:=FO_READWRITE+FO_EXCLUSIVE
local memohnd

    if( mode==OPEN_APPEND )
        fmode:=FO_READWRITE+FO_EXCLUSIVE
    elseif( mode==OPEN_EXCLUSIVE )
        fmode:=FO_READWRITE+FO_EXCLUSIVE
    elseif( mode==OPEN_SHARED )
        fmode:=FO_READWRITE+FO_SHARED
    elseif( mode==OPEN_READONLY )
        fmode:=FO_READ+FO_SHARED
    end

    table[TAB_FMODE]:=fmode

    if( 0>(table[TAB_FHANDLE]:=fopen(fname,fmode)) )
        table[TAB_FHANDLE]:=NIL 
        Sleep(500)
        return .f.
    else
        #ifdef _UNIX_
          //fdup elvesztené a protokoll lockot
          setcloexecflag(table[TAB_FHANDLE],.t.)
        #else
          table[TAB_FHANDLE]:=fdup(table[TAB_FHANDLE],.f.,.t.)
        #endif
    end
    
    table[TAB_BTREE]:=_db_open(table[TAB_FHANDLE],btbtx_pagesize())
    if( NIL==table[TAB_BTREE] )
        return .f.
    end
    
    //esetleges beragadt index törlése 
    _db_delord(table[TAB_BTREE],"<#>") 
 
    if( 0<tabMemoCount(table) )
        memohnd:=memoOpen(lower(tabMemoName(table)))
        if( memohnd<0 )
            taberrOperation("tabUse")
            taberrDescription(@"open failed")
            taberrFilename(lower(tabMemoName(table)))
            tabError(table)
        end
    end

    table[TAB_MEMOHND]:=memohnd //memohandler vagy NIL

    return .t.


******************************************************************************
function tabGoEOF(table) // EOF-ra áll
    tabCommit(table)
    xvputfill(table[TAB_RECBUF],0,table[TAB_RECLEN],32) //space
    table[TAB_EOF]:=.t.
    table[TAB_POSITION]:=0
    return NIL


******************************************************************************
function tabClose(table) //lezárja a fájlt

    tranNotAllowedInTransaction(table,"close",.t.)
 
    tabCommit(table)
    
    tabDeleteFieldTable(table)

    if( NIL!=table[TAB_FHANDLE] )
        fclose(table[TAB_FHANDLE])
    end

    if( NIL!=table[TAB_BTREE] )
        _db_close(table[TAB_BTREE])
    end

    table[TAB_OPEN]     := OPEN_CLOSED
    table[TAB_FHANDLE]  := NIL
    table[TAB_BTREE]    := NIL
    table[TAB_ORDER]    := 0
    table[TAB_FILTER]   := NIL
    table[TAB_LOCKLST]  := {}
    table[TAB_LOCKFIL]  := .f.
    table[TAB_POSITION] := 0
    table[TAB_MODIF]    := .f.
    table[TAB_MODIFKEY] := .f.
    table[TAB_MODIFAPP] := .f.

    if( tabMemoActive(table) )
        memoClose(tabMemoHandle(table))
    end
    table[TAB_MEMOHND]:=NIL
    table[TAB_MEMODEL]:=NIL

    tabFree(table)
    return NIL


******************************************************************************
function tabCloseAll() //minden táblaobjektumot lezár
local objectlist:=tabObjectList(), n
    for n:=1 to len(objectList)
         tabClose(objectList[n])
    next
    return NIL


******************************************************************************
function tabIsOpen(table) //visszaadja a megnyitási módot
    return table[TAB_OPEN]


******************************************************************************
static function tabFree(table)
    xvfree(table[TAB_RECBUF])
    xvfree(table[TAB_KEYBUF])
    return NIL


******************************************************************************
static function tabAlloc(table)
    tabFree(table)
    table[TAB_KEYBUF]:=xvalloc(256)
    table[TAB_RECBUF]:=xvalloc(table[TAB_RECLEN])
    return NIL


******************************************************************************
function openmode(mode)
static cmode:={"READONLY","SHARED","EXCLUSIVE","APPEND"}

    if( mode==NIL )
        return cmode
    elseif( valtype(mode)=="C" )
        return ascan(cmode,upper(alltrim(mode)))
    elseif( valtype(mode)=="N" .and. 1<=mode .and. mode<=len(cmode) )
        return cmode[mode]
    end
    return NIL


******************************************************************************
function btbtx_pagesize()
local ps:=getenv("BTBTX_PAGESIZE")
    if( empty(ps) )
        ps:=NIL
    else
        ps:=val(ps)
    end
    return ps


******************************************************************************
 