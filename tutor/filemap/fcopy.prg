
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

function main(fspec1,fspec2)

local fd1:=fopen(fspec1)
local fd2:=fcreate(fspec2)
local map:=filemap.open(fd1)
    fclose(fd1)         //  nem kell többé
    fwrite(fd2,map)     //  átmásolja az egészet
    filemap.close(map)  //  a rend kedvéért
    fclose(fd2)         //  a rend kedvéért

/*
  map a programnak olyan, mint egy bájt-string változó,
  azzal a különbséggel, hogy a buffer nem a tényleges memóriában,
  hanem a virtuális memóriában van, ezért nagyon nagy is lehet,
  32-biten 3G, 64-biten még sokkal több (amekkora a címtér),
  sokkal nagyobb, mint a tényleges fizikai memória, az operációs
  rendszer gondoskodik arról, hogy a ténylegesen használt
  adat bekerüljön a memóriába, amikor kell.
*/
