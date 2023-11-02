
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
// bti fname [-l]                 // indexek listazasa
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


        if( x=="-l" )
            op:="l"+v

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
    if( fname::right(3)!=".bt" )
        fname+=".bt"
    end

    if( "l"$op )
        listindex(fname,op)

    elseif( op=="k" )
        listkeys(fname,iname)

    elseif( op=="a" )
        addindex(fname,iname,seg)

    elseif( op=="d" )
        delindex(fname,iname)
    end

    ?
 
    
    
*****************************************************************************
static function usage(errtxt)
    if( errtxt!=NIL )
        ? errtxt
        ?
    end
    ??<<usage>>    
  Usage : bti.exe fname [-aindex -sseg1 -sseg2 | -dindex | -k[index] | -l[p][f] | -h]

  fname : bt file specification 
  index : index name
  segN  : index segment (column name in the table)

  -a    : add an index
  -d    : delete an index
  -k    : list all keys of an index (or all indices)
  -lpf  : list all indices (pages and freelist)
  -h    : print this help

<<usage>>    
    quit


*****************************************************************************
static function listindex(fname,op)
local t:=tabResource(fname)
local x:=tabIndex(t),n,c,i
local btree,iname

    if( "f"$op .or. "p"$op ) 
        tabOpen(t)
        btree:=t[2]
    end

    ? fname

    if( "f"$op ) 
        listfree(btree)
    end
    if( "p"$op ) 
        ? "recno {}";listpages(btree,"recno")
    end
    if( "p"$op .and. tabKeepDeleted(t)!=NIL )
        ? "deleted {}";listpages(btree,"deleted")
    end

    for n:=1 to len(x)
        iname:=x[n][IND_NAME]
        c:=aclone(x[n][IND_COL])
        for i:=1 to len(c)
            if( valtype(c[i])=="N"  )
                c[i]:=tabColumn(t)[c[i]][COL_NAME]
            end
        next 
        ? iname,if(x[n][4],"s","p"),c

        if( "p"$op ) 
            listpages(btree,iname)
        end
    next
   
    ?


*****************************************************************************
static function listpages(btree,iname)
local header,nords,n,order
    header:=_db_pgread(btree,0)
    nords:=header[29..32]::num
    iname::=str2bin
    for n:=1 to nords
        order:=header::substr(48+(n-1)*32+1,32)
        if(  iname==order::substr(17,len(iname)) )
            listpages1(btree,order)
            exit
        end
    next

static function listpages1(btree,order)
local page,link,type,cnt:=0
local tree:=0,leaf:=0,free:=0
    
    link:=order::substr(5,4)::num

    while( link!=0  )
        ++cnt 
        ?? " "+link::l2hex
        page:=_db_pgread(btree,link)
        type:=page::substr(17,4)::num
        if( type==0 )
            free++  
            ?? "*"
        elseif( type==1 )
            tree++
            ?? "!"
        elseif( type==2 )
            leaf++
        end
        
        link:=page::substr(5,4)::num
    end

    tree:=" tree="+tree::str::alltrim
    leaf:=" leaf="+leaf::str::alltrim
    free:=" free="+free::str::alltrim

    ?? " NUMBER_OF_PAGES="+cnt::str::alltrim, tree, leaf, free


*****************************************************************************
static function listfree(btree)
local page,link,cnt:=0
    ? "free {}"
    page:=_db_pgread(btree,0)
    link:=page[17..20]::num
    while( link!=0 )
        ++cnt
        ?? " "+link::l2hex
        page:=_db_pgread(btree,link)
        link:=page[5..8]::num
    end

    ?? " NUMBER_OF_PAGES="+cnt::str::alltrim

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
    tabIndex(t)[o][4]:=.t.  //beallitva a suppindex flag
    tabDropindex(t)         //torli az osszes suppindexet is
 

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
local key,crs,cnt:=0

    ? "----------------------------------------------------------------"
    ? "SETORD",name::alltrim,ord::str(3)

    if( ord>=0 )
        key:=_db_first(btree)
        crs:=_db_getcur(btree)
        while( key!=NIL )
            ++cnt
            //index neve      kulcs lapja            kulcs indexe   kulcs tartalma
            ? name::padr(16), crs[1]::l2hex::padl(5),crs[2]::str(4),crs[3]::key2str
            key:=_db_next(btree)
            crs:=_db_getcur(btree)
        end
        ? "Number of keys in ["+name+"]:",cnt::str::alltrim
    else
        ? "Index does not exist:", name
    end
    ?
    

*****************************************************************************
    
    
    
    
    
    