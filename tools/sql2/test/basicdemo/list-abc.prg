
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

function main()

local con:=sqlconnect(),tbl,rset,row

    set date format "yyyy-mm-dd"
    set printer to log-list-abc
    set printer on


    tbl:=testdata.a.tableEntityNew(con)
    rset:=tbl:select
    while( (row:=rset:next)!=NIL )
        ? printitem(row:id    ,  4),; 
          printitem(row:name  , 10),; 
          printitem(row:datum , 10),; 
          printitem(row:flag  ,  5),; 
          printitem(row:value , 10)
    end
    rset:close  //magától is lezáródik
    ?


    tbl:=testdata.b.tableEntityNew(con)
    rset:=tbl:select
    while( (row:=rset:next)!=NIL )
        ? printitem(row:id    ,  4),; 
          printitem(row:remark, 32),; 
          printitem(row:value,   6)
    end
    rset:close  //magától is lezáródik
    ?


    tbl:=testdata.c.tableEntityNew(con)
    rset:=tbl:select
    while( (row:=rset:next)!=NIL )
        ? printitem(row:name  , 10),; 
          printitem(row:attrib, 24)
    end
    rset:close  //magától is lezáródik
    ?

    con:sqldisconnect
   
    return NIL



******************************************************************************
static function printitem(x,w)

//Megjegyzés:
//Ha az érték null, akkor a driver egyező típusú empty
//értéket ad, és csak az explicit null vizsgálat mutatja,
//hogy eredetileg null jött. Ehhez vagyunk szokva a Clipperből,
//ha ez megváltozna, és ezután NIL-eket kapnánk, akkor folyton
//elszálldosnának a programok.

local t:=valtype(x)


    if( t=="C" )
        x:=padr(x,w)

    elseif( t=="N" )
        x:=transform(x,replicate("9",w))

    elseif( t=="D" )
        x:=padr(dtoc(x),w)

    elseif( t=="L" )
        x:=padr(if(x,"True","False"),w)

    elseif( t=="X" )
        x:=padr(bin2str(x),w)
    end

    return "  "+x


******************************************************************************
