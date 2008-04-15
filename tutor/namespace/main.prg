
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

// A main kötelezően a global namespace-ben van.
// Mivel a namespace csak egyszer, és csak a prg modul első
// utasításaként fordulhat elő, azért a main-t tartalmazó modul
// mindig a global névtérben van.

// Az opcionális namespace utasítás után jöhetnek a using-ok.
// Egy using utasítás mindig egyetlen Clipper sorban van, ha ez 
// túl hosszú volna, akkor használható a ';' folytatósor.

using proba=p;
    hopp hopp1
    
using szerencse=s
    
// A using szót követő első szimbólum a külső névtér neve.
// Az ezután felsorolt függvényneveket nem kell minősíteni,
// mert a fordító automatikusan minősít. 


function main()
    hopp()                  //automatikusan minősít: proba.hopp
    hopp1()                 //automatikusan minősít: proba.hopp1
    proba.hopp2()           //explicit minősítés (névtér megadás)
    s.print()               //explicit névtér megadás alias használattal
    proba.xx.yy.hopp()      //explicit minősítés (névtér megadás)
    ? errorNew():subcode    //objektumok működnek
    ?
    return NIL
    
