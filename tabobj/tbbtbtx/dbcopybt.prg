
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


#define PRIME          1103
#define KEYNAME(t,o)   lower(tabPathName(t)+alltrim(str(o)))


******************************************************************************
function tabCopybt(table)

local btname,tfile
local fd,db,db1
local n,rb
local msg,total,cnt:=0
local recno:=0,recbuf,reclen,recpos
local fdkey:={},kfilnam
local ord,key
local memcol:={},memdec:={},mempos,memval

    //-----------------------
    //regi adatfile
    //-----------------------

    btname:=lower(tabPathName(table))

    fd:=fopen(btname,FO_READWRITE+FO_EXCLUSIVE)
    if( fd<0 )
        taberrOperation("tabCopybt")
        taberrDescription(@"failed opening file (fd)")
        tabError(table)
    end

    db:=_db_open(fd)
    if( db==NIL )
        taberrOperation("tabCopybt")
        taberrDescription(@"failed opening file (db)")
        tabError(table)
    end

    //-----------------------
    //uj adatfile
    //-----------------------

    tfile:=tabFile(table)
    tabFile(table,TMPCHR+tfile)
    ferase(lower(tabPathName(table)))
    tabCreate(table)
    tabOpen(table,OPEN_EXCLUSIVE)
    tabZap(table)
    db1:=table[TAB_BTREE]
    tabCrypt(table,_db_cryptflg(db))  // titkositas oroklodik

    //-----------------------
    //ideiglenes kulcsfilek
    //-----------------------

    for ord:=0 to len(tabIndex(table))
        ferase(kfilnam:=KEYNAME(table,ord))
        aadd(fdkey,fopen(kfilnam,FO_CREATE+FO_TRUNCATE+FO_READWRITE+FO_NOLOCK))
        if( atail(fdkey)<0 )
            taberrOperation("tabCopybt")
            taberrDescription(@"failed creating file (fdkey)")
            tabError(table)
        end
    next


    //-----------------------
    //memo mezok
    //-----------------------

    for n:=1 to len(tabColumn(table))
        if( tabMemoField(table,n) )
            memcol::aadd(n)
            memdec::aadd(tabColumn(table)[n][COL_DEC])
        end
    next


    //-----------------------
    //rekordok atmasolasa
    //-----------------------


    total:="/"+alltrim(str(_db_lastrec(db)))
    reclen:=table[TAB_RECLEN]
    recbuf:=table[TAB_RECBUF]

    //Csak akkor mukodik, ha epsegben van a recno index,
    //lassabb is, viszont megtartja a rekordok eredeti sorrendjet.
    //Ez szukseges ahhoz, hogy a tabPack replikalhato legyen.

    _db_setord(db,"recno")
    key:=_db_first(db)

    while( key!=NIL )
        recpos:=right(key,6)
        rb:=_db_read(db,recbuf,recpos)

        if( rb!=reclen )

            //serult file
            taberrOperation("tabCopybt")
            taberrDescription(@"read failed (rb!=reclen)")
            tabError(table)

        elseif( left(recbuf,1)==a"*" )
            //torolt rekord

        else
            recno++

            if( ++cnt%PRIME==0 )
                msg:=message(msg,@"COPY "+btname+str(cnt)+total)
            end

            for n:=1 to len(memcol)
                mempos:=getmempos(table,memcol[n])
                if(!mempos::empty)
                    memval:=_db_memoread(db,mempos,xvgetbig32(key,0),memdec[n])
                    mempos:=_db_memowrite(db1,memval,recno,memdec[n])
                end
                setmempos(table,memcol[n],mempos)
            next

            table[TAB_RECPOS]    :=  _db_append(db1,recbuf)
            table[TAB_POSITION]  :=  recno

            for ord:=0 to len(tabIndex(table))
                key:=tabKeyCompose(table,ord)
                fwrite(fdkey[1+ord],key)
            next
        end

        key:=_db_next(db)
    end

    for ord:=0 to len(tabIndex(table))
        if( recno>0 ) //2002.11.13
            build_index(table,ord,fdkey[1+ord],msg,btname)
        end
        fclose(fdkey[1+ord])
        ferase(KEYNAME(table,ord))
    next

    if( msg!=NIL )
        message(msg)
    end

    _db_close(db)
    tabClose(table)

    set signal block
    ferase(btname)
    frename(lower(tabPathName(table)),btname)
    set signal unblock

    tabFile(table,tfile)

    return .t.


******************************************************************************
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
static function build_index(table,ord,fd,msg,btname)

local keyval,keynam,keylen
local db1:=table[TAB_BTREE]
local rcount:=table[TAB_POSITION]
local n,rb,stat

    if( ord==0 )
        keynam:="recno"
    else
        keynam:=tabIndex(table)[ord][IND_NAME]
    end

    if( 0>_db_setord(db1,keynam) )
        taberrOperation("tabCopybt")
        taberrDescription(@"no index (_db_setord<0)")
        taberrArgs({keynam})
        tabError(table)
    end

    keylen:=tabKeyLength(table,ord)
    keyval:=replicate(x"00",keylen)

    if( ord>0 )
        __bt_sortkey(KEYNAME(table,ord),rcount,keylen)
    end

    fseek(fd,0,FS_SET)
    for n:=1 to rcount

        if( n%PRIME==0 .and. msg!=NIL )
            message(msg,@"COPY "+btname+" ("+keynam+")"+str(n))
        end

        rb:=fread(fd,@keyval,keylen)

        if( rb!=keylen )
            taberrOperation("tabCopybt")
            taberrDescription(@"read failed (rb!=keylen)")
            taberrArgs({keynam,ferror()})
            tabError(table)
        end

        stat:=_db_put(db1,keyval)
        if( stat!=0 )
            taberrOperation("tabCopybt")
            taberrDescription(@"failed building index (_db_put!=0)")
            taberrArgs({keynam,stat})
            tabError(table)
        end
    next

    return NIL

******************************************************************************
