
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

#include "tdcutil.ch"

// kulonbsegek TDC2CH es TDC2TDH kozott
//
// .ch kiterjesztes helyett .tdh kiterjesztes keszul
//
// kulonbozik a tabla definicio
// #define SZAMLA       (TABLE:_szamla)          // a .ch-ban
// #define SZAMLA       (TABLE:table.szamla)     // a .tdh-ban

******************************************************************************************
function main(*)  // args: tdcspec1, tdcspec2, ...
local tdc:={*},n
local data,src,out
local tcre,tacc,tmod

    for n:=1 to len(tdc)
        data:=tdc[n]::parsetdc
        src:=data::gensrc

        // kimenet nevkepzese a tdc-bol
        out:=tdc[n]::strtran(".tdc",".ch")
        memowrit(out,src)
        {tcre,tacc,tmod}:=getfiletime(tdc[n])
        setfiletime(out,tcre,tacc,tmod)
    next


******************************************************************************************
static function gensrc(data)

local table:=data[1]
local path:=data[2]
local index:=data[3]
local field:=data[4]
local keep:=data[5]

local lf:=chr(10),n

local src:="//"+TDCUTIL_BUILD+lf+lf
local def

    src+=("#define "+table::upper)::padr(48)+"(TABLE:_"+table::lower+")"+lf+lf

    for n:=1 to len(field)
        def:="#define "
        def+=table::upper+"_"+field[n]:column::upper
        def::=padr(48)
        def+=table::lower+"->"+field[n]:column::lower
        src+=def+lf
    next

    return src


******************************************************************************************
