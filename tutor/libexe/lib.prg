
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

#ifdef NOT_DEFINED
  MS környezetben 
  a VCToolkitSetup.exe-ből és az MS Platform SDK CD-ből
  nem kerül elő 32-bites lib.exe.
  
  Ennek pótlására két lehetőség van:
  
  1) 
    Valahogy lefordítjuk ezt a programot (tyúk-tojás probléma).
    A program mutatja, hogy lib.exe == link.exe -lib.
  2)
    Bevesszük a path-ba a 64-bites (?) lib.exe-t,
    ami a ...\bin\win64-ben van, és tapasztalat szerint 
    működik 32-bites környezetben is.
#endif


function main(*)

local args:={*},n
local cmd:="link.exe -lib"

    for n:=1 to len(args)
        cmd+=" "+args[n]
    next

    errorlevel(run(cmd))
    