
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

//konnektál, kiírja a szerver verziókat

#ifdef MEGJEGYZES

A névterek jelentik az első komoly eltérést az eredeti 
Clipper 5.2 szintaktikától. Ez a sor 

    sqlconnectionNew():version

a régi Clipperben is helyes -- szintaktikailag. Más kérdés,
hogy a régi Clipperben nem lehet olyan függvényt írni, ami 
olyan objektumot ad vissza, aminek version attribútuma van. 
Ez azonban fordításkor nem derül ki, csak a linkeléskor,
vagy a futáskor.

Korábban csak a methodcast lógott ki a régi Clipper 
szintaktikából:

    x:(object)list
    
ami azt jelöli, hogy az x objektumra nem a saját list metódusát 
akarjuk alkalmazni, hanem az object osztály list metódusát. 
Ez azonban elég ritkán fordul elő alkalmazási programokban.
Minden egyéb még most is (2004.szept.) színtiszta Clipper.

Ha már... 
Még egy apró eltérés van, nevezetesen CCC-ben nem szükséges tudni, 
hogy egy metódus/attribútum ténylegesen metódusként vagy attribútumként 
van-e implementálva, azaz mindegy, hogy írunk-e utána zárójelet. 
Metódusnevek után üres zárójelpárt írni felesleges tudálékoskodás.
C-ben persze más a helyzet, mert () úgy tekinthető, mint egy
operátor, amit egy függvénypointerre alkalmazva előidézzük
a függvény végrehajtását. CCC-ben ilyesmi nincs.

#endif


function main()
local con

    set date format "yyyy-mm-dd"
    set printer to log-connect
    set printer on
    
    con:=sqlconnect()
    ?? con:version
    ?
    con:sqldisconnect

    return NIL
 
    