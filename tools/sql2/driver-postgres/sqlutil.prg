
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

namespace sql2.postgres

#include "pq.ch"
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
            x:=if(empty(x),"null","E'"+bin2str(sql2.postgres._pq_escapebytea(x))+"'")
            //E'proba \\ooo szerencse'
            //8.0.x nem fogadja el az E prefixet
            //8.1.x E-vel és E nélkül is elfogadja
            //8.2.x E hiánya esetén warningot ad
        end
    end
    return x
    
#ifdef EMLEKEZTETO  //a bináris adatokról
    Az Oracle simán át tudja vinni a '...' között levő 0 byte-ot,
    mert a string adatokhoz mindig meg kell adni azok hosszát.
    A Postgres azonban nem viseli el a 0 byte-ot, mert azt az utasítást
    tartalmazó string végének értelmezi. Ezért kell vesződni az escape
    függvényekkel.
    
    Oracle-ben a char típusoknál a "'"-t duplázni kell.
    Postgresben a "'"-t és "\"-t kell duplázni.
    
    Postgresben a tetszőleges tartalom (0 byte) tárolása csak a bytea
    típusban lehetséges. Jelenleg csak a memók használnak bytea típust,
    tehát a normál char mezőkbem nem lehet bináris adatot tárolni.
#endif

 
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
    if( empty(x) )
        x:="null"
    else
        x:="E'"+sql2.postgres._pq_escapestring(rtrim(x))+"'"  // "'"-t és "\"-t duplázza
    end
    return x

#ifdef EMLEKEZTETO // null karakter literál: ''
    Az Oracle a '' karakter literált null-nak értelmezi,
    a Postgres üres stringnek. A különbséget ki kell egyenlíteni.
#endif


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
    //return if(x,"1","0")
    return if(x,"TRUE","FALSE")

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
    return sql2.postgres.sqlidquote(alltrim(x))

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
function sqlerrorCreate(result)
local status,code,desc,err

    status:=sql2.postgres._pq_resultstatus(result)
    code:=sql2.postgres._pq_resulterrorfield(result,PG_DIAG_SQLSTATE)

#ifndef RESULTERRORMESSAGE
    desc:="PG-"+code+" "+sql2.postgres._pq_resulterrorfield(result,PG_DIAG_MESSAGE_PRIMARY)
#else
    desc:=sql2.postgres._pq_resulterrormessage(result)
    desc:=strtran(desc,chr(10),";")
    desc:=strtran(desc,chr(13),"")
#endif    

    if( code=="40P01" )
        err:=sqldeadlockerrorNew()
    elseif( code=="40001" )
        err:=sqlserialerrorNew()
    else
        err:=sqlerrorNew()
    end

    err:description:=desc
    err:subsystem:="sql2.postgres"
    err:subcode:=status

    return err


******************************************************************************


