
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

//A driverekben definiált osztály egyszerűsített változata,
//ami csak adattárolásra képes, viszont adatbázisfüggetlen.


namespace tdsutil

******************************************************************************
class columnref(object)
    method  initialize
    attrib  name        // a mező programbeli neve
    attrib  expr        // oszlopkifejezés
    

******************************************************************************
static function columnref.initialize(this,nam,exp)  
    this:(object)initialize
    this:name:=nam
    if( exp==NIL )
        this:expr:=quotedname(nam)
    else            
        this:expr:=quotedname(exp)
    end
    return this


******************************************************************************
static function quotedname(x)
    return tdsutil.sqlidquote(alltrim(x))

#ifdef EMLEKEZTETO
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
