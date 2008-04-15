
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
    set printer to log-list-ps
    set printer on


    tbl:=proba.tableEntityNew(con)
    rset:=tbl:select
    while( (row:=rset:next)!=NIL )
        ? printitem(row:szamlaszam ,  24),; 
          printitem(row:devnem     ,   3),; 
          printitem(row:nev        ,  30),; 
          printitem(row:egyenleg   ,  17),; 
          printitem(row:tulmenflag ,   1),; 
          printitem(row:konyvkelt  ,  10),; 
          printitem(row:megjegyzes ,  24)
    end
    rset:close  //magától is lezáródik
    ?


    tbl:=szerencse.tableEntityNew(con)
    rset:=tbl:select
    while( (row:=rset:next)!=NIL )
        ? printitem(row:szamlaszam ,  24),; 
          printitem(row:kiegdata   ,  32)
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
