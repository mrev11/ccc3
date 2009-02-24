
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

namespace sql2.oracle

#include "oci.ch"
#include "sql.ch"

******************************************************************************
function sqldebug(stmt)
static debug:=!empty(getenv("SQLDEBUG"))
    if(debug)
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
            //A lobokat nem lehet közvetlenül beírni az adatbázisba
            //insert/update alkalmával, hanem először be kell rakni
            //egy empty clob/blob-ot (nem felcserélhető), utána ennek
            //lokátorát egy külön select-ben be kell olvasni,
            //és ezen keresztül lehet beírni az oszlop tartalmát.
            //Az üres lobok helyére azonnal null-t teszünk, 
            //ilyenkor a lokátor olvasása és az írás elmarad.
            x:=if(empty(x),"null","empty_blob()")
        end
    end
    return x
 
******************************************************************************
function sqlliteral(x) //x-et SQL utasításba írható literállá alakítja
local t:=valtype(x)
    if( t=="C" )
        return sqlliteral_c(x)
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
    x:=rtrim(x)
    if( "'"$x )
        x:=strtran(x,"'","''")
    end
    return "'"+x+"'"

static function sqlliteral_n(x)
    return ltrim(str(x))

static function sqlliteral_d(x)
    return  if(empty(x),"null","to_date('"+dtoc(x)+"')")

static function sqlliteral_l(x)
    return if(x,"1","0")

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
function sqldate2cccdate(x)
local s:= padl(asc(substr(x,1,1))-100,2,"0")+;
          padl(asc(substr(x,2,1))-100,2,"0")+;
          padl(asc(substr(x,3,1)),2,"0")+;
          padl(asc(substr(x,4,1)),2,"0") 
    return stod(s)
    

******************************************************************************
function cccdate2sqldate(x)

local s:=dtos(x)
    s:=bin(val(substr(s,1,2))+100) +;
       bin(val(substr(s,3,2))+100) +;
       bin(val(substr(s,5,2))    ) +;
       bin(val(substr(s,7,2))    ) +;   
       replicate(bin(1),3) 
    return s
    
//megj: 1992. nov. 30 ábrázolása: 119,192,11,30,1,1,1

 
******************************************************************************
function quotedname(x)
    return sql2.oracle.sqlidquote(alltrim(x))

#ifdef EMLEKEZTETO // az "IDENT" alakú nevek használatáról

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

    Az a baj, hogy a normális használathoz 

        Oracle-ben   "NAME" alakú,
        Postgresben  "name" alakú

    azonosítókat kell generálni.

#endif


******************************************************************************
 