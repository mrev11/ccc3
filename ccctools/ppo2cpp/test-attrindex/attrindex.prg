
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

function main()

local x,y,z

    ? getmethod(xClass(),"a1"),;
      getmethod(xClass(),"a2"),; 
      getmethod(xClass(),"a3"),;
      getmethod(xClass(),"a4")

    ? getmethod(yClass(),"a1"),;
      getmethod(yClass(),"a2"),; 
      getmethod(yClass(),"a3"),;
      getmethod(yClass(),"a4")


    ? getmethod(zClass(),"a1"),;
      getmethod(zClass(),"a2"),;
      getmethod(zClass(),"a3"),;
      getmethod(zClass(),"a4")
    
    x:=xNew("1","2","3","4")
    y:=yNew("1","2","3","4")
    z:=zNew("1","2","3","4")

    ? x:attrnames
    ? x:attrvals
    ?

    ? y:attrnames
    ? y:attrvals
    ?

    ? z:attrnames
    ? z:attrvals
    ?

    ? <<rem>>
    L?tszik, hogy az attrib?tumok sorrendje m?s:

        x-ben az a3 indexe 3
        z-ben az a3 indexe 6
    <<rem>>

    ? x:a3     // 3
    ? z:a3     // 3
    ? z:(x)a3  // 1, hib?s!

    ? <<rem>>
    Kivesz?nk egy elemet z-b?l arr?l a helyr?l,
    ahol az x-ben t?rol?dik, azaz mell?ny?lunk.
    Ez mutatja, hogy a met?dus-cast attrib?tumokra
    nem haszn?lhat?.
    <<rem>>
    ?

class x(object)
    attrib a1
    attrib a2
    attrib a3
    attrib a4
    method initialize

function x.initialize(this,a1,a2,a3,a4)
    this:a1:=a1
    this:a2:=a2
    this:a3:=a3
    this:a4:=a4
    return this

class y(x)
    attrib b1
    attrib b2
    attrib b3
    attrib b4
    
class z(y)
    //ugyanaz, mint y m?gis k?l?nb?zik a sorrend

    