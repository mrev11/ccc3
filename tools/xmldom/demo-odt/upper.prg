
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

// Egy LibreOffice Writer dokumentumban
// minden szoveget nagybeture konvertal

**************************************************************************************
function main()
local parser,dom

    ferase("content.xml")
    filecopy("demo.odt","upper.odt")
    run("unzip -q upper.odt content.xml") // kiszedi

    parser:=xmlparser2New()
    parser:contentblock:={|*|content(*)}
    dom:=parser:parse("content.xml")      // elemzi, modositja

    set console off
    set printer on
    set printer to "content.xml"          // felulirja
        parser:qmxml:xmloutpre
        dom:xmloutpre
    set printer to
    set printer off
    set console on

    run("zip -q upper.odt content.xml")   // visszarakja


**************************************************************************************
static function content(parser,node)
    if( node:type=="#TEXT" .or. node:type=="#CDATA" )
        node:content:={node:gettext::upper}
    end
    return .t.


**************************************************************************************
        