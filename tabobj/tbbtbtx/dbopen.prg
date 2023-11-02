
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
#include "btcharconv.ch"

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
local timeout

    setquitblock()

    tranNotAllowedInTransaction(table,"open",.t.)

    if( !file(fname) )
        n:=alert(fname+@" not found, create?",{@"Create",@"Quit"})
        if( n==2 )
            taberrOperation("tabOpen")
            taberrDescription(@"file not found")
            tabError(table)
        else
            tabCreate(table)
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

        if( valtype(userblock)=="N" )
            timeout:=userblock
        end

        while( 0>=tabSlock(table,{||0}) .or. !tabUse(table,mode) )
            tabSunlock(table)
            if( timeout!=NIL )
                if( timeout<=0 )
                    return .f.
                else
                    sleep(userblock/10)
                    timeout-=userblock/10
                end
            else
                taberrOperation("tabOpen")
                taberrDescription(@"open failed")
                taberrUserBlock(userblock,"PUK")

                if( valtype(userblock)=="B" )
                    return tabError(table)
                else
                    tabError(table)
                end
            end
        end
        tabSunlock(table)

        begin
            tabVerify(table)
            exit //OK

        recover err <tabobjerror>

            break(err)

            //Csak akkor jon ide (vissza), ha err:candefault==.t.,
            //es az interaktiv alertben a "Default"-ot valasztottak.
            //(Ezert terminal nelkuli program alertjebol sosem jön vissza.)
            //Problema, ha a breaket elteriti egy kulso recover.

            tabClose(table)
            tabUpgrade(table)
        end
    end

    tabAlloc(table)
    table[TAB_OPEN]:=mode

    //? getpid(), "mode", if(mode>1,"w","r") , "version-bef", read_disk_version(table)
    while( 1>tabSlock(table,{||0}) )
        sleep(100)
    end
    if( read_disk_version(table)<4 )
        // version_upgrade_4-ben
        // - inicializalva kell legyen a record buffer: tabAlloc
        // - ismert kell legyen a nyitasi mod: table[TAB_OPEN]
        // - csak egy programban futhat az upgrade: tabSlock
        // - meg kell eloznie az alias->field tablazat kesziteset: tabSetFieldTable
        version_upgrade_4(table)
    end
    tabSunlock(table)
    //? getpid(), "mode", if(mode>1,"w","r") , "version-aft", read_disk_version(table)


    tabSetFieldTable(table)

    if( 0>_db_setord(table[TAB_BTREE],"deleted") )
        // nincs a fajlban deleted
        if( NIL!=tabKeepDeleted(table) )
            // de az objektumban van
            if( mode>=OPEN_EXCLUSIVE )
                formatum_konverzio(table)
            else
                table[TAB_KEEPDELETED]:=NIL //fallback
            end
        end
    else
        // van a fajlban deleted
        if( NIL==tabKeepDeleted(table) )
            // de az objektumban nincs
            tabKeepDeleted(table,1)
        end
    end

    _db_setord(table[TAB_BTREE],"recno")
    tabGotop(table)
    table[TAB_STAMP]:=tabStamp(table)
    return .t.


******************************************************************************
function tabStamp(table)
local stamp:=""
local column,n,col
    column:=tabColumn(table)
    for n:=1 to len(column)
        col:=column[n]
        stamp+=col[1]+":"+col[2]+col[3]::str::alltrim+"."+col[4]::str::alltrim+";"
    next
    return stamp


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
    // for n:=1 to tabLastRec(table)
    //     if( tabGoto(table,n) .and. tabDeleted(table) )
    //         move_to_deleted(table,n)
    //     end
    // next

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
        if( tranEnforced() )
            tranSemaOn(SEMA_XOPEN)
        end
        result:=tabUse1(table,mode)
        if( !result .and. tranEnforced()  )
            tranSemaOff(SEMA_XOPEN)
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
    if( mode>OPEN_READONLY   )
        _db_delord(table[TAB_BTREE],"<#>")
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

    if( tabIsOpen(table)<OPEN_EXCLUSIVE )
        tabUnlock(table)
    elseif( tranEnforced() )
        tranSemaOff(SEMA_XOPEN)
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
    table[TAB_MEMOHND]:=NIL
    table[TAB_MEMODEL]:=NIL

    tabFree(table)
    return NIL


******************************************************************************
function tabCloseAll() //minden tablaobjektumot lezar
local objectlist:=tabObjectList(), n
    for n:=len(objectList) to 1 step -1
        if( valtype(objectList[n])=="O" )
            objectList[n]:close
        else
            tabClose(objectList[n])
        end
    next

// visszafele kell jaratni a ciklust, mert a nemstatic
// objektumok a :close-ban kiszedik magukat a listabol

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
static function version_upgrade_4(table_orig)

local memcol:={}
local memdec:={}
local mempos,memval
local table,column,n

    if( tabIsOpen(table_orig)>=OPEN_SHARED )
        table:=table_orig
    else
        table:=tabResource(tabPathName(table_orig))
        if( table==NIL .or. !tabOpen(table,OPEN_SHARED,{||.f.}) )
            table:=table_orig
        else
            //REKURZIO - KESZ!
            tabClose(table)
            return NIL
        end
    end

    column:=tabColumn(table)
    for n:=1 to len(column)
        if(tabMemoField(table,column[n]))
            memcol::aadd(n)
            memdec::aadd(tabColumn(table)[n][COL_DEC])
        end
    next

    if( len(memcol)>0 )

        if( tabIsOpen(table)>=OPEN_SHARED )
            // READWRITE modban nyitva
            // elvegezheto a konverzio
            ?? "version_upgrade_4", tabPathName(table); ?

            table[TAB_MEMOHND]:=memoOpen(lower(tabMemoName(table)),FO_EXCLUSIVE)
            if( table[TAB_MEMOHND]<0 )
                taberrOperation("version_upgrade_4")
                taberrDescription(@"memoOpen failed")
                taberrFilename(lower(tabMemoName(table)))
                tabError(table)
            end

            tabGotop(table)
            while( !tabEof(table) )
                for n:=1 to len(memcol)
                    mempos:=getmempos(table,memcol[n])
                    memval:=_v1_tabMemoRead(table,mempos)
                    if( !memval::empty )
                        mempos:=_db_memowrite(table[TAB_BTREE],memval::trim,tabPosition(table),memdec[n])
                    else
                        mempos:=a"          "
                    end
                    setmempos(table,memcol[n],mempos)
                next
                table[TAB_MODIF]:=.t.
                tabCommit(table)
                tabSkip(table)
            end

            fclose(table[TAB_MEMOHND])
            table[TAB_MEMOHND]:=NIL
            ferase(lower(tabMemoName(table)))

        else
            // READONLY modban nyitva
            // nem vegezheto el a konverzio
            ? getpid(),"version_fallback_4", tabPathName(table)

            table[TAB_MEMOHND]:=memoOpen(lower(tabMemoName(table)),FO_READ)
            if( table[TAB_MEMOHND]<0 )
                taberrOperation("version_upgrade_4")
                taberrDescription(@"memoOpen failed")
                taberrFilename(lower(tabMemoName(table)))
                tabError(table)
            end

            for n:=1 to len(memcol)
                set_readonly_memoblk(table,column[memcol[n]])
            next
        end
    end

    if( tabIsOpen(table)>=OPEN_SHARED )
        write_disk_version(table,4)
    end



static function getmempos(table,n)
local column:=table[TAB_COLUMN][n]
local offs:=column[COL_OFFS]
local width:=column[COL_WIDTH]
    return xvgetchar(table[TAB_RECBUF],offs,width)


static function setmempos(table,n,pos)
local column:=table[TAB_COLUMN][n]
local offs:=column[COL_OFFS]
local width:=column[COL_WIDTH]
    xvputbin(table[TAB_RECBUF],offs,width,pos)


******************************************************************************
static function set_readonly_memoblk(table,col)
local type:=col[COL_TYPE]
local offs:=col[COL_OFFS]
local width:=col[COL_WIDTH]

    if( type=="C" )
        col[COL_BLOCK]:=blkmemoc(table,offs,width)
    elseif( type=="X" )
        col[COL_BLOCK]:=blkmemox(table,offs,width)
    else
        col[COL_BLOCK]:=(||)
    end


static function blkmemoc(table,offs,width)
    return (||bin2str(CHARCONV_LOAD(_v1_tabMemoRead(table,xvgetchar(table[TAB_RECBUF],offs,width)))))


static function blkmemox(table,offs,width)
    return (|| _v1_tabMemoRead(table,xvgetchar(table[TAB_RECBUF],offs,width)) )


******************************************************************************
static function read_disk_version(table)
local head:=replicate(bin(0),8)
local magic,version

    fseek(table[TAB_FHANDLE],0,FS_SET)
    fread(table[TAB_FHANDLE],@head,8)
    magic:=head[1..4]

    if( magic==x"62310500" )
        version:=asc(head[5])     // little endian
    elseif( magic==x"00053162" )
        version:=asc(head[8])     // big endian
    else
        //ide nem johet
        //mert ha rossz a magic
        //akkor nem lehet nyitva a fajl
    end

    return version


******************************************************************************
static function write_disk_version(table,version)
local magic:=replicate(bin(0),4)

    fseek(table[TAB_FHANDLE],0,FS_SET)
    fread(table[TAB_FHANDLE],@magic,4)

    if( magic==x"62310500" )
        fseek(table[TAB_FHANDLE],4,FS_SET) // little endian
    elseif( magic==x"00053162" )
        fseek(table[TAB_FHANDLE],7,FS_SET) // big endian
    else
        //ide nem johet
        //mert ha rossz a magic
        //akkor nem lehet nyitva a fajl
    end

    fwrite(table[TAB_FHANDLE],bin(version),1)


******************************************************************************
