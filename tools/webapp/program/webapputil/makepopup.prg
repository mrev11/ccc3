
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


***************************************************************************************
function makepopup(content,popupid:=content,popuptag:="popup",popupcls:="popup")
local node:=xhtmlnodeNew("div")

    if( valtype(content)=="O" )
        node:addcontent(content)
    else
        node:addtext(content)
    end

    node:setattrib("popupid",popupid)
    node:setattrib("popuptag",popuptag)
    node:setattrib("popupcls",popupcls)
    node:setattrib("onclick","XCODE.xlib.popup.clicked(this)")

    return node


// ez egy eleg altalanosan hasznalhato utility
// az eredeti contentet beleteszi egy popupolhato div-be
// a DOM-ba az eredeti node helyett ezt a div-et kell tenni
//
//
// content 
//  lehet egy szoveg vagy egy xhtlmnode objektum
//  azt beleteszi egy popupolhato div objektumba
//  a bongeszoben az eredeti content latszik, 
//  amin ha klikkelnek, megjelenitheto egy popup
//
// popupid
//  egy olyan szoveg, ami alapjan azonosithato,
//  hogy hol klikkeltek: eldontheto mi legyen a popupban
//
// popuptag
//  a bongeszo <popuptag> XML uzenetet fog kuldeni
//
// popupcls
//  a popup div osztalya <div class="popupcls"> lesz
//  ez alapjan lehet a css-ekben konfiguralni
//
// a szerver ilyen uzeneteket kap
//  <popuptag>popupid</popuptag>


***************************************************************************************

