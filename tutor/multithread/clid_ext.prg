
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

//#define CLID_EXT
#define WAIT 1000

#ifdef EMLEKEZTETO
    Ez a program demonstrálja a CCC-nek azt a tulajdonságát,
    hogy a külső static változók inicializátorát szinkronizálja.

    A CLID_EXT definiálásával clid_test KÜLSŐ változó, 
    a CCC automatikusan szinkronizálja az inicializátort, 
    ezért WAIT értékétől függetlenül testRegister() csak egyszer 
    fut, ez a megkívánt működés.
    
    A CLID_EXT definíció nélkül clid_test BELSŐ változó,
    amit a CCC (jelenleg) nem szinkronizál automatikusan,
    ezért WAIT>0 esetén testRegister() hibásan kétszer fut.
    
    Megjegyzés: A C++ egyáltalán nem foglalkozik a static változók 
    inicializátorának szinkronizálásával (nem része a nyelvnek),
    ezért C++-ban a static változók többször inicializálódhatnak
    (ezt a hibát örökli a CCC).
    
    Megjegyzés: Ha mutex-szel szinkronizálunk, annak nyilván
    static-nak kell lennie, hogy minden szál ugyanazt a mutexet fogja.
    Ha a CCC mutex belső static változónak van definiálva,
    akkor előfordulhat, hogy a static mutex hibásan többször is
    inicializálódik, tehát használhatatlan. Ezért KÜLSŐ static 
    mutexeket célszerű használni.
    
    Megjegyzés: A belső static-ok azért nincsenek szinkronizálva, 
    mert a szinkronizálás drága, és viszonylag ritkán van rá szükség 
    (kevés többszálú program van).  A külsők static-ok szinkronizálva 
    vannak, másképp minden mutexet előre létre kellene hozni (a program 
    egyszálú korában), nehogy már maga a mutex is rossz legyen.
    
    Megjegyzés: A CCC static változók inicializátora akkor fut,
    amikor a program használni kezdi a változót. Korábban ez nem
    így volt, és problémát okozott, hogy az MSC nem tudta kezelni
    a rekurzív inicializálást, amikor egy inicializátor hivatkozik
    egy másik static változóra, amit szintén inicializálni kell...
    
    Megjegyzés: Mit mond a C/C++ szabvány a static változók
    inicializálásáról?
#endif


#ifdef CLID_EXT
static clid_test:=testRegister()
#endif

function testClass()
#ifndef CLID_EXT
static clid_test:=testRegister()
#endif
    return clid_test

static function testRegister()
local clid:=classRegister("test",{objectClass()})
    ?? "*"
    sleep(WAIT)
    return clid

*****************************************************************************
function main()
local th1,th2
    th1:=thread_create({||th()})
    th2:=thread_create({||th()})
    thread_join(th1)
    thread_join(th2)
    ?

static function th()
    ? "clid", testClass()

*****************************************************************************
