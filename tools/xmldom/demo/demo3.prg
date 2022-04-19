
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

static remark:=<<REMARK>>
    kilistazza a szamla es szamlaegyenleg objektumokat
    ez annyival bonyolultabb az ugyfeleknel,
    hogy a kivonat reszfa epitese is szukseges,
    azonban, hogy a fa ne nojon az egig,
    minden elkeszult kivonat utan a fat visszavagjuk

<<REMARK>>


#ifdef MEGJEGYZES

A contentblock  akkor hívódik meg, amikor az elemző beolvasott 
egy komplett node-ot (xml elemet), vagyis a node záró tagjának 
beolvasása után. A content block visszatérése kétféle lehet:

1) .t. az aktuális node bekerül a parent content-jébe (épül a fa)
2) .f. az elemző eldobja a node-ot (nem épül a fa)

#endif  

****************************************************************************
function main(fname:="example.xml")
local p

    ? remark

    p:=xmlparser2New(fname) 
    p:contentblock:={|*|content(*)}
    p:parse
   
    ?

****************************************************************************
static function content(parser,node)
local type:=node:type 
    if( type=="szamla" .or. type=="szlaegyenleg" )
        node:xmlout
    end
    return !(type=="kivonat")

****************************************************************************

