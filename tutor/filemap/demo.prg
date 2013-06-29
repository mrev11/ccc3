
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
local fd:=fopen("demo.prg")
local map:=filemap.open(fd)

    fclose(fd) //már nem kell

    // map olyan, mint egy binary string
    // működnek rá a függvények és operátorok
    
    ? valtype(map)
    ? len(map)
    ? map::left(20)
    ? map::right(20)
    ? at(a"demo.prg",map)
    ? rat(a"demo.prg",map)
    ? map[1..32]
    ? map[1],map[2],map[3],map[4],map[5],map[6],map[7],map[8]
    ? a"demo.prg"$map
    ? a"function main()"<=map
    ?

// A közönséges bájtstringekkel szemben egy map óriási, akár
// sok GB is lehet (amekkora a címtér), ugyanis valójában nincs 
// benn a tényleges memóriában (csak a virtuális memóriában),
// és az operációs rendszer biztosítja, hogy a buffer megcímzett
// részei (amikor kell) bekerüljenek a tényleges fizikai memóriába.
//
// A map[offset..offset+1023] kifejezés egy avi fájl akármelyik
// részletét beolvassa. Tudni kell, hogy az ilyen "beolvasott" részek
// a fizikai memóriába kerülnek, ezért nem lehetnek akármilyen nagyok,
// a CCC védekezik a MAXBINLEN-nél nagyobb változók ellen.
// Pl. a map[..] vagy substr(map,1) kifejezések áttöltenék az egész 
// buffert a virtuális memóriából a fizikaiba, ami csak akkor sikerülhet,
// ha a buffer mérete < MAXBINLEN.