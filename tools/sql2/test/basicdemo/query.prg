
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

//lekérdezés sqlquery objektummal

function main()

local query_a:=<<query>>
select id, name, datum, flag, value from konto.a order by id
<<query>>

local query_ax:=<<query>>
select  id, name, datum, flag, value
from  konto.a where  id>:1 order  by id
<<query>>

local query_b:=<<query>>
select id, value, remark from konto.b order by id
<<query>>

local query_c:=<<query>>
select name, attrib from konto.c order by name
<<query>>


local query_ab:=<<query>>
select
    konto.a.id as id_a,
    name,
    datum,
    flag,
    konto.a.value as val_a,
    konto.b.id as id_b,
    konto.b.value as val_b
from
    konto.a full join konto.b on konto.a.id=konto.b.id
order by
    konto.a.id -- nulls first -- csak Oracle
<<query>>

//join helyén kipróbálható:
//
//1) (síma) join
//2) left join
//3) right join
//4) full join


local query_abc:=<<query>>
select
    konto.a.id as id_a,
    konto.a.name as name_a, -- a síma "name" nem elég
    konto.a.value as val_a,
    konto.b.id as id_b,
    konto.b.value as val_b,
    konto.c.attrib
from
    konto.a 
    full join konto.b on konto.a.id=konto.b.id
    left join konto.c on konto.a.name=konto.c.name
order by
    konto.a.id
<<query>>


//Az Oracle és a Postgres eltérnek abban,
//hogy a rendezés után hova kerülnek a null-ok.
//Oracleben a "nulls first", "nulls last" kiegészítéssel
//szabályozható (default: nulls last).
//Postgresben a null-ok a többi sor közé vegyülnek.


local con:=sqlconnect()
local query, n

    set date format "yyyy-mm-dd"
    set printer to log-query
    set printer on

    ? "-------------------------------------------------------------"
    ?? query_a

    query:=con:sqlquerynew(query_a)
    while( query:next )
        ? printitem(query, 'id'    ,"N",  4),; 
          printitem(query, 'name'  ,"C", 10),; 
          printitem(query, 'datum' ,"D", 10),; 
          printitem(query, 'flag'  ,"L",  5),; 
          printitem(query, 'value' ,"N", 10)
    end
    query:close  //magától is lezáródik


    ? "-------------------------------------------------------------"
    ?? query_ax,2

    query:=con:sqlquerynew(query_ax,{2})
    while( query:next )
        ? printitem(query, 'id'    ,"N",  4),; 
          printitem(query, 'name'  ,"C", 10),; 
          printitem(query, 'datum' ,"D", 10),; 
          printitem(query, 'flag'  ,"L",  5),; 
          printitem(query, 'value' ,"N", 10)
    end
    query:close  //magától is lezáródik

    ? "-------------------------------------------------------------"
    ?? query_ax,3

    query:=con:sqlquerynew(query_ax,{3})
    while( query:next )
        ? printitem(query, 'id'    ,"N",  4),; 
          printitem(query, 'name'  ,"C", 10),; 
          printitem(query, 'datum' ,"D", 10),; 
          printitem(query, 'flag'  ,"L",  5),; 
          printitem(query, 'value' ,"N", 10)
    end
    query:close  //magától is lezáródik



    ? "-------------------------------------------------------------"
    ?? query_b

    query:=con:sqlquerynew(query_b)
    while( query:next )
        ? printitem(query, 'id'    ,"N",  4),; 
          printitem(query, 'value' ,"C", 10),; 
          printitem(query, 'remark',"C", 24)
    end
    query:close  //magától is lezáródik


    ? "-------------------------------------------------------------"
    ?? query_c

    query:=con:sqlquerynew(query_c)
    while( query:next )
        ? printitem(query, 'name' , "C", 10),; 
          printitem(query, 'attrib',"C", 24)
    end
    query:close  //magától is lezáródik


    ? "-------------------------------------------------------------"
    ?? query_ab

if( con:driver $ "sql2.mysql.sql2.sqlite3" )
    ? con:driver,"does not support full join"
else
    query:=con:sqlquerynew(query_ab)
    //query:list //megfigyelhető a prefetch
    while( query:next )
        #define TABULAR
        #ifndef TABULAR
            //primitív listázás
            for n:=1 to query:fcount
                ? padr(query:fname(n),20), query:isnull(n), query:getchar(n)
            next
            ? query:getnumber('id_a')
            ? query:getchar('name')
            ? query:getdate('datum')
            ? query:getlogical('flag')
            ? query:getnumber('val_a')
            ? query:getnumber('id_b')
            ? query:getnumber('val_b')
            ?
        #else
            //tabulált listázás
            ? printitem(query, 'id_a'  ,"N",  4),; 
              printitem(query, 'name'  ,"C", 10),; 
              printitem(query, 'datum' ,"D", 10),; 
              printitem(query, 'flag'  ,"L",  5),; 
              printitem(query, 'val_a' ,"N", 10),; 
              printitem(query, 'id_b'  ,"N",  4),; 
              printitem(query, 'val_b' ,"N",  6)
        #endif
    end
    query:close  //magától is lezáródik
end

    ? "-------------------------------------------------------------"
    ?? query_abc

if( con:driver $ "sql2.mysql.sql2.sqlite3" )
    ? con:driver,"does not support full join"
else
    query:=con:sqlquerynew(query_abc)
    while( query:next )
        ? printitem(query, 'id_a'  ,"N",  4),; 
          printitem(query, 'name_a',"C", 10),; 
          printitem(query, 'val_a' ,"N", 10),; 
          printitem(query, 'id_b'  ,"N",  4),; 
          printitem(query, 'val_b' ,"N",  6),;
          printitem(query, 'attrib',"C", 24)
    end
    query:close  //magától is lezáródik
end

    con:sqldisconnect

    //classprint()
   
    return NIL


******************************************************************************
static function printitem(query,x,t,w)

    //Megjegyzés:
    //Ha az érték null, akkor a driver egyező típusú empty
    //értéket ad, és csak az explicit null vizsgálat mutatja,
    //hogy eredetileg null jött. Ehhez vagyunk szokva a Clipperből,
    //ha ez megváltozna, és ezután NIL-eket kapnánk, akkor folyton
    //elszálldosnának a programok.

    if( query:isnull(x) )
        x:="Null"
        x:=if(t=="N",padl(x,w),padr(x,w))

    elseif( t=="C" )
        x:=query:getchar(x)
        x:=padr(x,w)

    elseif( t=="N" )
        x:=query:getnumber(x)
        x:=transform(x,replicate("9",w))

    elseif( t=="D" )
        x:=query:getdate(x)
        x:=padr(dtoc(x),w)

    elseif( t=="L" )
        x:=query:getlogical(x)
        x:=padr(if(x,"True","False"),w)
    end
    return "  "+x

******************************************************************************

