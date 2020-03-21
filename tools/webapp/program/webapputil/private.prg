
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

namespace webapp

using webapp script jsstring

//private API

************************************************************************************
function privatelength()  //lekérdezi a stack állását
local dom
    script("XCODE.privatelength();") //PRIVATELENGTH-t küld vissza
    webapp.waitmessage('PRIVATELENGTH',@dom)
    return dom:gettext::val


************************************************************************************
function privatepush() //új elemet rak a stackre (egy üres arrayt)
    script("XCODE.privatepush();")


************************************************************************************
function privatepop(len) //leüríti a stacket len-ig
    script("XCODE.privatepop("+str(len)::alltrim+");")


************************************************************************************
function savedisplay(key) //elmenti a displayt a key kulcs alatt
    script('XCODE.savedisplay("'+key+'");') //elmenti a displayt (a böngészőben)


************************************************************************************
function restoredisplay(key) //a key kulcs alatt mentett displayt visszaállítja
    script('XCODE.restoredisplay("'+key+'");') //visszaállítja a displayt


************************************************************************************
function emptydisplay() //üres (új) displayt csinál (div element)
    script('XCODE.emptydisplay();') 


************************************************************************************
function uploaddisplay(x) //betölt egy oldalt webapp.display-be
    script("XCODE.webapp.display.x.innerHTML="+x::jsstring+";XCODE.settle();")


************************************************************************************
