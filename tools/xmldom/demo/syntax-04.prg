
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
    csak szintaktikai ellenorzes
    p:info:buildflag:=.f. miatt nem keszit node-okat
    az xml-ben szandekos hiba van
    ellenorzessel eszrevett szintaktikai hiba

<<REMARK>>


****************************************************************************
function main()

local fspec:="x-hiba4.xml"

local p,dom,err

    ? remark

    p:=xmlparser2New()
    p:file:=fspec
    p:info:buildflag:=.f.

    begin
        dom:=p:parse 
    recover err
        ? "class:",err:classname
        err:list
        listxml( fspec ) 
    end
    ?

****************************************************************************
