
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

//lekérdezés tableentity objektummal
//
//Ugyanazokkal a táblákkal ugyanannak az eredménynek
//kell kijönnie, mint a query objektumos lekérdezésnek;
//az a, b, c egyszerű táblák az entitylib.testdata-ból,
//az ab, abc összetett táblák a lokális tds-ből valók.

function main()

local con:=sqlconnect(),tbl,rset,row

    set date format "yyyy-mm-dd"
    set printer to log-entity
    set printer on

    ? "-------------------------------------------------------------"
    ? "testdata.a"

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


    ? "-------------------------------------------------------------"
    ? "testdata.b"

    tbl:=testdata.b.tableEntityNew(con)
    rset:=tbl:select
    while( (row:=rset:next)!=NIL )
        ? printitem(row:id,4),; 
          printitem(row:value, 10),; 
          printitem(upper(bin2str(row:remark)),40)
    end
    rset:close  //magától is lezáródik


    ? "-------------------------------------------------------------"
    ? "testdata.c"

    tbl:=testdata.c.tableEntityNew(con)
    rset:=tbl:select
    while( (row:=rset:next)!=NIL )
        ? printitem(row:name  , 10),; 
          printitem(row:attrib, 24)
    end
    rset:close  //magától is lezáródik


    ? "-------------------------------------------------------------"
    ? "localtds.ab"

if( con:driver $ "sql2.mysql.sql2.sqlite3" )
    ? con:driver,"does not support full join"
else
    tbl:=localtds.ab.tableEntityNew(con)
    rset:=tbl:selord
    while( (row:=rset:next)!=NIL )
        ? printitem(row:id_a  ,  4),;
          printitem(row:name  , 10),;
          printitem(row:datum , 10),;
          printitem(row:flag  ,  5),;
          printitem(row:val_a , 10),;
          printitem(row:id_b  ,  4),;
          printitem(row:val_b , 10)
    end
    rset:close  //magától is lezáródik
end


    ? "-------------------------------------------------------------"
    ? "localtds.abc"

if( con:driver $ "sql2.mysql.sql2.sqlite3" )
    ? con:driver,"does not support full join"
else
    tbl:=localtds.abc.tableEntityNew(con)
    rset:=tbl:selord
    while( (row:=rset:next)!=NIL )
        ? printitem(row:id_a  ,  4),;
          printitem(row:name_a, 10),;
          printitem(row:val_a , 10),;
          printitem(row:id_b  ,  4),;
          printitem(row:val_b , 10),;
          printitem(row:attrib, 10)
    end
    rset:close  //magától is lezáródik
end


    ? "-------------------------------------------------------------"
    ? "localtds.abc (nulls)"

if( con:driver $ "sql2.mysql.sql2.sqlite3" )
    ? con:driver,"does not support full join"
else
    tbl:=localtds.abc.tableEntityNew(con)
    rset:=tbl:selord
    while( (row:=rset:next)!=NIL )
        ? pxitem(tbl:getcolumn('id_a')  , row,  4),;
          pxitem(tbl:getcolumn('name_a'), row, 10),;
          pxitem(tbl:getcolumn('val_a') , row, 10),;
          pxitem(tbl:getcolumn('id_b')  , row,  4),;
          pxitem(tbl:getcolumn('val_b') , row, 10),;
          pxitem(tbl:getcolumn('attrib'), row, 10)
    end
    rset:close  //magától is lezáródik
end

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


    if( t=="X" )
        x:=padr(bin2str(x),w)

    elseif( t=="C" )
        x:=padr(x,w)

    elseif( t=="N" )
        x:=transform(x,replicate("9",w))

    elseif( t=="D" )
        x:=padr(dtoc(x),w)

    elseif( t=="L" )
        x:=padr(if(x,"True","False"),w)
    end

    return "  "+x


******************************************************************************
static function pxitem(col,row,w)

//Megjegyzés:
//A tableEntity koncepcióban nincs nagy hangsúly
//az SQL null értékek vizsgálatán. Ha az alkalmazás
//mégis firtatni akarja a null értékeket, akkkor 
//valami ilyesmit csinálhat:

local x:=col:eval(row)   //mezőérték
local z:=col:isnull(row) //null flag
local t:=valtype(x)      //mezőtípus

    if( z )
        x:="Null"
        x:=if(t=="N",padl(x,w),padr(x,w))

    elseif( t=="C" )
        x:=padr(x,w)

    elseif( t=="N" )
        x:=transform(x,replicate("9",w))

    elseif( t=="D" )
        x:=padr(dtoc(x),w)

    elseif( t=="L" )
        x:=padr(if(x,"True","False"),w)
    end

    return "  "+x

******************************************************************************

