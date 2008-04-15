
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


//Olyan objektum, aminek egyetlen attribútuma van, egy pointer.
//Az attribútum neve gobject, ami megtévesztő, ui. nem mindig 
//gobjectet tárolunk benne (csak a gobject-ekhez hasonlóan
//akarjuk kezelni).


******************************************************************************
class gstruct(object) new:  //nem kell automatikus konstruktor
    attrib gobject

******************************************************************************
function gstructNew(gpointer)
local o:=objectNew(gstructClass())
    o:gobject:=gpointer
    return o

******************************************************************************

    