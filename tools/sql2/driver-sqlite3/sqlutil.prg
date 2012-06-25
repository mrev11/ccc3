
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

namespace sql2.sqlite3

#include "sqlite3.ch"
#include "sql.ch"

******************************************************************************
function sqldebug(stmt)
static debug:=!empty(getenv("SQLDEBUG"))
    if( debug )
        stmt:=strtran(stmt,chr(10)," ")
        stmt:=strtran(stmt,chr(13)," ")
        ? ">>>>",alltrim(stmt)
    end
    return NIL

******************************************************************************
function sqlvalue(row,c) //insert/update utasításba írandó érték
local t,x
    if( c:isnull(row) ) //2006.09.13
        x:='null'
    else
        t:=left(c:type,1)
        x:=c:eval(row)
        
        if( t=="C" )
            x:=sqlliteral_c(x)
        elseif( t=="N" )
            x:=sqlliteral_n(x)
        elseif( t=="D" )
            x:=sqlliteral_d(x)
        elseif( t=="L" )
            x:=sqlliteral_l(x)
        elseif( t=="M" )
            x:=sqlliteral_x(x)
        end
    end
    return x
    

 
******************************************************************************
function sqlliteral(x) //x-et SQL utasításba írható literállá alakítja
local t:=valtype(x)
    if( t=="C" )
        return sqlliteral_c(x)
    elseif( t=="X" )
        return sqlliteral_x(x)
    elseif( t=="N" )
        return sqlliteral_n(x)
    elseif( t=="D" )
        return sqlliteral_d(x)
    elseif( t=="L" )
        return sqlliteral_l(x)
    elseif( t=="A" )
        return sqlliteral_a(x)
    end
    return NIL
 
static function sqlliteral_c(x)
    if( empty(x) )
        x:="null"
    else
        x::=strtran("'","''")
        x:="'"+x+"'"
    end
    return x

#ifdef EMLEKEZTETO // null karakter literál: ''
    Az Oracle a '' karakter literált null-nak értelmezi,
    a Postgres üres stringnek. A különbséget ki kell egyenlíteni.
#endif

static function sqlliteral_x(x)
local uc
    if( x==a"" )
        x:="null"
    else
        uc:=bin2str(x)
        if( str2bin(uc)==x )
            x:=sqlliteral_c(uc)
        else
            x:=sql2.sqlite3.bin2hex_c(x)
            x:="x'"+x+"'"
        end
    end
    return x


static function sqlliteral_n(x)
    return ltrim(str(x))


static function sqlliteral_d(x)
    //return  if(empty(x),"null","to_date('"+dtoc(x)+"')")
    return  if(empty(x),"null","'"+dtoc(x)+"'")

#ifdef EMLEKEZTETO //dátum literál formátum
    A Postgres 'yyyy-mm-dd' alakban, szövegesen adja a dátumokat, és
    literálként ugyanígy kell beírni az SQL utasításba (to_date() nincs).
    A dátumformátum a locale-tól függ. A 'C' locale-ban, amit más okból 
    is be kell állítani az adatbázis létrehozásakor, a formátum yyyy-mm-dd.
#endif


static function sqlliteral_l(x)
    return if(x,"1","0")
    //return if(x,"TRUE","FALSE")

#ifdef EMLEKEZTETO //boolean típus
    Oracle-ben number(1) típust használtunk, mert nincs boolean.
    Postgresben van boolean, melynek értékét a TRUE/FALSE literál jelöli.
#endif

static function sqlliteral_a(x)
local a:="(",n
    for n:=1 to len(x)
        if(n>1)
            a+=","
        end
        a+=sqlliteral(x[n])
    next
    a+=")"
    return a

******************************************************************************
function quotedname(x)
    return alltrim(x)
    //return sql2.postgres.sqlidquote(alltrim(x)) //megszűnt: 2011.07.20

#ifdef EMLEKEZTETO //az idézett azonosítókról
    Oracle-ben a "NAME" alakkal lehet tetszőleges azonosítót definiálni.
    "NAME" nem ütközik a kulcsszavakkal, pl. "UPDATE" használható.
    Ha az idézőjelen belül csupa NAGYBETŰ van, akkor az így definiált
    azonosító case insensitive, egyébként case sensitive.

    Postgresben a "name" alakkal lehet tetszőleges azonosítót definiálni. 
    "name" nem ütközik a kulcsszavakkal, pl. "update" használható.
    Ha az idézőjelen belül csupa KISBETŰ van, akkor az így definiált
    azonosító case insensitive, egyébként case sensitive.
    Ha case sensitive nevet definiáltunk, akkor arra később csak
    idézőjeles szintaktikával lehet hivatkozni. 
    Pl.
        def: "abc"  esetén  ref: ABC, Abc, "abc" működik
        def: "ABC"  esetén  ref: csak "ABC" működik

    Az a kényelmetlenség, hogy a normális használathoz 

        Oracle-ben   "NAME" alakú,
        Postgresben  "name" alakú

    azonosítókat kell generálni.
#endif

******************************************************************************
