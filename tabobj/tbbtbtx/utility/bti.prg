
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

//Indexelo utility btbtx formatumhoz
//
// bti [-f]fname [-l]             // indexek listazasa
// bti fname -diname              // index torles (+osszes suppindex)
// bti fname -ainame -sseg1 ...   // uj index hozzaadasa
// bti fname -adeleted            // deleted index hozzaadasa
// bti fname -kiname              // a megadott index kulcsainak listazasa
// bti fname -k                   // az osszes index kulcsainak listazasa


#include "bttable.ch"
#include "table.ch"

*****************************************************************************
function main()

local a:=argv(),n
local fname, iname, seg:={}
local x, v, op:="l"

    for n:=1 to len(a)

        if( !left(a[n],1)=="-" )
            fname:=a[n] 
            loop
        end

        x:=left(a[n],2)
        v:=substr(a[n],3)

        if( x=="-f" )
            fname:=v

        elseif( x=="-l" )
            op:="l"

        elseif( x=="-k" )
            iname:=v
            op:="k"

        elseif( x=="-a" )
            iname:=v
            op:="a"
 
        elseif( x=="-d" )
            iname:=v
            op:="d"

        elseif( x=="-s" )
            aadd(seg,v)

        elseif( x=="-h" )
            usage()

        else
            usage("Invalid option: "+a[n])
        end
    next

    if( fname==NIL )
        usage("No input file")
    end
    if( !"."$fname )
        fname+=".bt"
    end

    if( op=="l" )
        listindex(fname)

    elseif( op=="k" )
        listkeys(fname,iname)
        
    elseif( op=="a" )
        addindex(fname,iname,seg)

    elseif( op=="d" )
        delindex(fname,iname)
 
    else
        usage("No operation")
    end
    ?
 
    
    
*****************************************************************************
static function usage(errtxt)
    if( errtxt!=NIL )
        ? errtxt
        ?
    end
    ??<<usage>>    
  Usage : bti.exe fname [-aindex -sseg1 -sseg2 | -dindex | -k[index] | -l | -h]

  fname : bt file specification 
  index : index name
  segN  : index segment (column name in the table)

  -a    : add an index
  -d    : delete an index
  -k    : list all keys of an index (or all indices)
  -l    : list all indices (default operation)
  -h    : print this help

<<usage>>    
    quit


*****************************************************************************
static function listindex(fname)
local t:=tabResource(fname)
local x:=tabIndex(t),n,c,i
    ? fname
    for n:=1 to len(x)
        c:=aclone(x[n][IND_COL])
        for i:=1 to len(c)
            if( valtype(c[i])=="N"  )
                c[i]:=tabColumn(t)[c[i]][COL_NAME]
            end
        next 
        ? x[n][1],if(x[n][4],"s","p"),c
    next
    ?


*****************************************************************************
static function addindex(fname,iname,seg)

local t:=tabResource(fname)
local b:=errorblock(),e,order,n

    if( iname=="deleted" )
        tabOpen(t,OPEN_EXCLUSIVE)
        _db_creord(t[TAB_BTREE],"deleted")
        return NIL
    end

    for n:=1 to len(seg)
        begin
            tabColNumber(t,seg[n])
        recover
            usage("Column does not exist: "+seg[n])
        end
    next

    //ha letezett az index, akkor toroljuk,
    //majd az uj adatokkal (ujra) betesszuk

    begin
        order:=tabGetIndex(t,iname)  
        adel(tabIndex(t),order)
        asize(tabIndex(t),len(tabIndex(t))-1)
    end
    tabAddIndex(t,{iname,"",seg,.f.})
    
    //Az uj index strukturaval megnyitjuk a filet,
    //ha az index inkompatibilis, akkor tabindexerror hiba keletkezik,
    //amit csendben tovabbengedunk, es tabOpen ujraepiti az indexet.
    //Itt kifejezetten az errorblock-os hibakezeles kell,
    //ui. vissza kell terni tabOpen-be, hogy az folytassa.

    errorblock({|x|if(x:candefault,qout("build: "+iname),eval(b,e))}) 
    tabOpen(t,OPEN_EXCLUSIVE)
    errorblock(b)


*****************************************************************************
static function delindex(fname,iname)
local t:=tabResource(fname),o

    tabOpen(t,OPEN_EXCLUSIVE)

    if( iname=="deleted" )
        _db_delord(t[TAB_BTREE],"deleted")
        return NIL
    end

    begin
        o:=tabGetIndex(t,iname)
    recover
        usage("Index does not exist: "+iname)
    end  
    tabIndex(t)[o][4]:=.t.    //beallitva a suppindex flag
    tabDropindex(t)   //torli az osszes suppindexet is
 

*****************************************************************************
static function listkeys(fname,iname)
local table:=tabResource(fname)
local index:={},tabind,i

    if(iname=="recno")
        aadd(index,iname)
    elseif(iname=="deleted")
        aadd(index,iname)
    elseif( !iname::empty )
        aadd(index,iname::upper)
    end
    
    if( index::empty )
        aadd(index,"recno")
        aadd(index,"deleted")
        tabind:=tabIndex(table)
        for i:=1 to len(tabind)
            aadd(index,tabind[i][IND_NAME])
        next
    end

    tabOpen(table)

    for i:=1 to len(index)
        print_ord(table,index[i])
    next


*****************************************************************************
static function print_ord(table,name)
local btree:=table[TAB_BTREE]
local ord:=_db_setord(btree,name)
local key,cnt:=0

    ? "----------------------------------------------------------------"
    ? "SETORD",name,ord

    if( ord>=0 )
        key:=_db_first(btree)
        while( key!=NIL )
            ++cnt
            ? key::key2str
            key:=_db_next(btree)
        end
        ? "Number of keys:",cnt::str::alltrim
    else
        ? "Index does not exist:", name
    end
    ?
    

*****************************************************************************
    
    
    
    
    
    