
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

#define HEX(c,i)  c::str2bin[i]::asc::l2hex::padl(2,"0")
#define SEQ(c)    HEX(c,1)+HEX(c,2)+","+c::asc::str::alltrim


function main()

local c

    ? c:="á",SEQ(c)
    ? c:="é",SEQ(c)
    ? c:="í",SEQ(c)
    ? c:="ó",SEQ(c)
    ? c:="ö",SEQ(c)
    ? c:="ő",SEQ(c)
    ? c:="ú",SEQ(c)
    ? c:="ü",SEQ(c)
    ? c:="ű",SEQ(c)
    ? c:="ä",SEQ(c)

    ? c:="Á",SEQ(c)
    ? c:="É",SEQ(c)
    ? c:="Í",SEQ(c)
    ? c:="Ó",SEQ(c)
    ? c:="Ö",SEQ(c)
    ? c:="Ő",SEQ(c)
    ? c:="Ú",SEQ(c)
    ? c:="Ü",SEQ(c)
    ? c:="Ű",SEQ(c)
    ? c:="Ä",SEQ(c)
    ?