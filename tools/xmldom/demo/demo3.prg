
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

//kilistázza a számla objektumokat
//ez annyival bonyolultabb az ügyfeleknél,
//hogy a kivonat részfa építése is szükséges,
//azonban, hogy a fa ne nőjön az égig,
//minden elkészült kivonat után a fát visszavágjuk

#ifdef MEGJEGYZES

A processblock  akkor hívódik meg, amikor az elemző beolvasott 
egy komplett node-ot (xml elemet), vagyis a node záró tagjának 
beolvasása után. A feldolgozó block visszatérése kétféle lehet:

1) .f. az aktuális node bekerül a parent content-jébe (épül a fa)
2) .t. az elemző eldobja a node-ot (nem épül a fa)

#endif  

****************************************************************************
function main(fname)
local p:=xmlparserNew(fname) 

    p:processblock:={|node|feldolgozo(node)}
    p:parse
   
    ? //"maximális stack méret:", yaccmaxidx() 
    
    return NIL

****************************************************************************
static function feldolgozo(node)

local type:=node:type 

    if( type=="szamla" .or. type=="szlaegyenleg" )
        node:xmlout
    end

    return  type=="kivonat" 

****************************************************************************

