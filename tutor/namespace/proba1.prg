
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

namespace proba hopp1  

// A modul "proba" névtérhez tartozik. 
// A namespace utasítás legfeljebb egyszer,
// a modul első utasításaként fordulhat elő.

// A névtér neve után felsorolt függvényeket is
// az aktuális névtérbem fogja keresni. Ha hopp1
// nem volna felsorolva, akkor csak így lehetne rá
// hivatkozni: proba.hopp1

// A függvényeket, amik ugyanabban a prg modulban
// (tehát ugyanabban a névtérben) vannak definiálva 
// magától megtalálja.

function hopp()
    xx.yy.hopp()            //megtalálja, mert azonos modulban van
    proba.xx.yy.hopp()      //megtalálja, mert teljesen minősítve van
    ? "proba.hopp"
    hopp1()                 //megtalálja a namespace lista alapján
    return NIL


function xx.yy.hopp()
    ? "proba.xx.yy.hopp"    //teljes név
    return NIL


