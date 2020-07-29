
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
//function tabGoEOF(table)                //EOF-ra all (belso)
//function tabClose(table)                //lezarja a table-t
//function tabCloseAll()                  //minden table-t lezar
//function tabIsOpen(table)               //nyitasi mod


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

        //teszteleshez automatikus dbf->dat konverzio
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

    if( mode>OPEN_EXCLUSIVE ) //OPEN_APPEND implementacioja kesobb
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
            tabVerify(table)  //kiszamitja table[TAB_RECLEN]-t
            //Az uj begin/recover/finally-bol szabad kiugrani.
            exit //OK

            //Ha az objektum es a file inkompatibilisek,
            //akkor tabVerify tabindexerror/tabstructerror-t dob,
            //es err:args-ban az inkompatibilis indexek neve van,
            //amit meg kell jegyezni a konverziohoz.

        recover err <tabindexerror>

            err:candefault:=.t.
            break(err)

            //Csak akkor jon vissza, 
            //ha az interaktiv alertben a "Default"-ot valasztottak.
            //Problema, ha a breaket elteriti egy kulso recover.

            //visszazar
            tabClose(table)
            
            if( 0<tabSlock(table,{||0}) .and. tabUse(table,OPEN_EXCLUSIVE) )
                tabSunlock(table)
                //konverzio (reindex)
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

    if( 0>_db_setord(table[TAB_BTREE],"deleted") )
        // nincs a fajlban deleted
        if( mode>OPEN_READONLY .and. NIL!=tabKeepDeleted(table) )
            // de az objektumban van
            formatum_konverzio(table)
        end
    else
        // van a fajlban benne deleted
        if( NIL==tabKeepDeleted(table) )
            // de az objektumban nincs
            tabKeepDeleted(table,1)
        end
    end

    _db_setord(table[TAB_BTREE],"recno")
    tabGotop(table) 
    table[TAB_OPEN]:=mode
    return .t.


******************************************************************************
static function formatum_konverzio(table)
local n
    //? "FORMATUM KONVERZIO", tabPathName(table)
    _db_header_read(table[TAB_BTREE],.t.) //for writing
    _db_creord(table[TAB_BTREE],"deleted")

// kerdes, hogy ez kell-e:
// ha ki van hagyva, akkor a regi toroltek
// benne maradnak a fajlban (nem zavarnak)
// 
//    for n:=1 to tabLastRec(table)
//        if( tabGoto(table,n) .and. tabDeleted(table) )
//            move_to_deleted(table,n)
//        end
//    next

    _db_header_write(table[TAB_BTREE])

static function move_to_deleted(table,pos)
local key:=tabKeyCompose(table,0)
    _db_del(table[TAB_BTREE],key)
    _db_setord(table[TAB_BTREE],"deleted")
    _db_put(table[TAB_BTREE],key)
    _db_setord(table[TAB_BTREE],"recno")


******************************************************************************
static function tabUse(table,mode)  //megnyit egy dbf-et
local result
    if( mode<OPEN_EXCLUSIVE )
        result:=tabUse1(table,mode)
    else
        tabLockCount(table,1)
        result:=tabUse1(table,mode)
        if( !result )
            tabLockCount(table,-1)
        end
    end
    return result


******************************************************************************
static function tabUse1(table,mode)  //megnyit egy dbf-et

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
          //fdup elvesztene a protokoll lockot
          setcloexecflag(table[TAB_FHANDLE],.t.)
        #else
          table[TAB_FHANDLE]:=fdup(table[TAB_FHANDLE],.f.,.t.)
        #endif
    end
    
    table[TAB_BTREE]:=_db_open(table[TAB_FHANDLE],btbtx_pagesize())
    if( NIL==table[TAB_BTREE] )
        return .f.
    end
    
    //esetleges beragadt index torlese 
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
function tabGoEOF(table) // EOF-ra all
    tabCommit(table)
    xvputfill(table[TAB_RECBUF],0,table[TAB_RECLEN],32) //space
    table[TAB_EOF]:=.t.
    table[TAB_POSITION]:=0
    return NIL


******************************************************************************
function tabClose(table) //lezarja a fajlt

    tranNotAllowedInTransaction(table,"close",.t.)
 
    tabCommit(table)

    if( tabIsOpen(table)>=OPEN_EXCLUSIVE )
        tabLockCount(table,-1)
    else
        tabUnlock(table)
    end
    
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
function tabCloseAll() //minden tablaobjektumot lezar
local objectlist:=tabObjectList(), n
    for n:=1 to len(objectList)
         tabClose(objectList[n])
    next
    return NIL


******************************************************************************
function tabIsOpen(table) //visszaadja a megnyitasi modot
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
 