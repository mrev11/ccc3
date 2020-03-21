
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

//Példa,  hogyan lehet egybeépíteni maszkokat:


#include "mask100x50.html"     //paneleket tartalmazó maszk
#include "textget.html"        //egyik belső panel
#include "fizmod.html"         //másik belső panel

function main()

local dom:=xhtmldom.mask100x50("Próba szerencse")
local get:=xhtmldom.textget("Ezis azis")
local fiz:=xhtmldom.fizmod("Fizetési mód")
local hash:=xhtmlnode.createnodehash(dom)


    hash["get"]:content:={get}
    hash["chk"]:content:={fiz}
    
    hash:=xhtmlnode.createnodehash(dom)  //újra kell építeni
    
    hash["g1"]:setattrib( xhtmlnode.attrib("value","Próba szerencse")  )
    hash["getx"]:setattrib( xhtmlnode.attrib("value","Helló!")  )
    hash["gety"]:setattrib( xhtmlnode.attrib("value","Viszlát")  )


    hash["fbank"]:setattrib( xhtmlnode.attrib("checked","checked")  )
    
    memowrit("proba.html",dom:html)
    ?
