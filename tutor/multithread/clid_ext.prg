
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
    Ez a program demonstralja a CCC-nek azt a tulajdonsagat,
    hogy a kulso static valtozok inicializatorat szinkronizalja.

    A CLID_EXT definialasaval clid_test KULSO valtozo, 
    a CCC automatikusan szinkronizalja az inicializatort, 
    ezert WAIT erteketol fuggetlenul testRegister() csak egyszer 
    fut, ez a megkivant mukodes.
    
    A CLID_EXT definicio nelkul clid_test BELSO valtozo,
    amit a CCC (jelenleg) nem szinkronizal automatikusan,
    ezert WAIT>0 eseten testRegister() hibasan ketszer fut.
    
    Megjegyzes: A C++ egyaltalan nem foglalkozik a static valtozok 
    inicializatoranak szinkronizalasaval (nem resze a nyelvnek),
    ezert C++-ban a static valtozok tobbszor inicializalodhatnak
    (ezt a hibat orokli a CCC).
    
    Megjegyzes: Ha mutex-szel szinkronizalunk, annak nyilvan
    static-nak kell lennie, hogy minden szal ugyanazt a mutexet fogja.
    Ha a CCC mutex belso static valtozonak van definialva,
    akkor elofordulhat, hogy a static mutex hibasan tobbszor is
    inicializalodik, tehat hasznalhatatlan. Ezert KULSO static 
    mutexeket celszeru hasznalni.
    
    Megjegyzes: A belso static-ok azert nincsenek szinkronizalva, 
    mert a szinkronizalas draga, es viszonylag ritkan van ra szukseg 
    (keves tobbszalu program van).  A kulsok static-ok szinkronizalva 
    vannak, maskepp minden mutexet elore letre kellene hozni (a program 
    egyszalu koraban), nehogy mar maga a mutex is rossz legyen.
    
    Megjegyzes: A CCC static valtozok inicializatora akkor fut,
    amikor a program hasznalni kezdi a valtozot. Korabban ez nem
    igy volt, es problemat okozott, hogy az MSC nem tudta kezelni
    a rekurziv inicializalast, amikor egy inicializator hivatkozik
    egy masik static valtozora, amit szinten inicializalni kell...
    
    Megjegyzes: Mit mond a C/C++ szabvany a static valtozok
    inicializalasarol?
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
