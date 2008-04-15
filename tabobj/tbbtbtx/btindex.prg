
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
#define KEYFILE(t,o)   lower(tabPathName(t)+alltrim(str(o)))
#define OPERATION      "build_bt_index"

//Felépíti (vagy újraépíti) az {order} sorszámú index(ek)et.
//A táblának exkluzívan nyitva kell lennie.
//Kötelezően ord>0, azaz order nem tartalmazhatja a recno indexet.
//Ha resource==.t., akkor frissíti a filében a resource infót.

******************************************************************************
function build_bt_index(table,order,resource)

local msg,total,rcount:=0 
local fdkey:={},keylen:={},keynam:={},ord:={}
local fd,o,n

    if( valtype(order)!="A" )
        order:={order}
    end
    
    for n:=1 to len(order)
    
        if( empty(o:=tabGetIndex(table,order[n])) )
            taberrOperation(OPERATION)
            taberrDescription(@"invalid control")
            taberrArgs({order[n]})
            tabError(table) 
        else
            aadd(ord,o)
        end

        ferase(KEYFILE(table,o))
        if( 0>(fd:=fcreate(KEYFILE(table,o),FO_READWRITE+FO_SHARED)) )
            taberrOperation(OPERATION)
            taberrDescription(@"failed creating file (fd<0)")
            tabError(table) 
        else
            aadd(fdkey,fd)
        end

        aadd(keylen,tabKeyLength(table,o) )
        aadd(keynam,tabIndex(table)[o][IND_NAME] )
    next

    total:="/"+alltrim(str(tabLastrec(table)))

    tabGotop(table)
    while( !tabEof(table) )
        if( ++rcount%PRIME==0 )
            msg:=message(msg,@"Index "+tabFile(table)+str(rcount)+total)
        end
        for n:=1 to len(ord)
            fwrite(fdkey[n],tabKeyCompose(table,ord[n]))
        end
        tabSkip(table)
    end
    
    for n:=1 to len(ord)
        if( rcount>0 )
            __bt_sortkey(KEYFILE(table,ord[n]),rcount,keylen[n])
            __copy_keys(table,fdkey[n],rcount,keylen[n],keynam[n],msg) 
        end
        fclose(fdkey[n])
        ferase(KEYFILE(table,ord[n]))
    end
    
    if( resource==.t. )
        _db_addresource(table[TAB_BTREE],arr2bin(tabIndex(table)),1) 
    end
 
    if( msg!=NIL )
        message(msg)
    end
    return NIL


******************************************************************************
static function __copy_keys(table,fdkey,rcount,keylen,keynam,msg)

local db1:=table[TAB_BTREE]
local n,key:=replicate(x"20",keylen),rb,stat
local tmpnam:="<#>", total 
 
    _db_delord(db1,keynam) 
    _db_delord(db1,tmpnam)

    if( 0>_db_creord(db1,tmpnam) )
        taberrOperation(OPERATION)
        taberrDescription(@"_db_creord failed)")
        taberrArgs({"<*>"})
        tabError(table) 
    end
    _db_setord(db1,tmpnam)

    total:="/"+alltrim(str(rcount))
 
    fseek(fdkey,0,FS_SET)
    for n:=1 to rcount
        if( n%PRIME==0 .and. msg!=NIL )
            message(msg,@"Build "+tabFile(table)+" ("+keynam+")"+str(n)+total)
        end

        rb:=fread(fdkey,@key,keylen)
        if( rb!=keylen )
            taberrOperation(OPERATION)
            taberrDescription(@"failed reading file (rb!=keylen)")
            taberrArgs({keynam,ferror()})
            tabError(table) 
        end

        stat:=_db_put(db1,key)
        if( stat!=0 )
            taberrOperation(OPERATION)
            taberrDescription(@"failed building index (_db_put!=0)")
            taberrArgs({keynam,stat})
            tabError(table) 
        end
    next

    if( 0>_db_renord(db1,tmpnam,keynam) )
        taberrOperation(OPERATION)
        taberrDescription(@"_db_renord failed)")
        taberrArgs({tmpnam,keynam})
        tabError(table) 
    end
   
    return NIL

******************************************************************************
