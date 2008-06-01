
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


local i, exitcode, result, resfil:="result.txt"

local top:=5
local lef:=10
local bot:=20
local rig:=70

local z:=zeditnew(memoread("zdemo.prg"),top,lef,bot,rig)

    setcolor("b/w")

    for i:=0 to maxrow()
        @ i,0 say replicate( chr(asc("a")+ i%26 ), maxcol()+1 ) 
    next 
    
    z:modflg:=.t.               // modosithato-e
    alert("HOPP-1")             // editalas indul
    exitcode:=z:loop            // edital
    alert("HOPP-2;")            // nincs benne restscreen
    ? "exit", exitcode          // inkey code, amivel kileptek
    ? "changed", z:changed      // valtozott-e
    result:=z:gettext           // az editalt szoveg
    memowrit(resfil,result)     // kimenet tarolva
    
    // meg egy csomo parameter beallithato,
    // ezeknek a hasznalatat a z.prg-bol lehet kinezni, 
    // ilyenek:
    //
    // kezdeti poziciok
    // kezdeti searchstring
    // kezdeti replacestring
    // clipboardfile
    // billentyu kombinaciok (keymapblk)
    // custom header (headerblk)

    ?
