
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

#define PRINT(x)    ? padr(#x,16), x




function main()

local epoch

local xmldate_m2
local xmldate_z
local xmldate_p2

local toffset:=timeoffset() // local time offset (nálunk most 7200)

    // toffset-=120

    ? epoch:=xmltimestamp()                       // json-ba irhato timestamp
    ? datetime2epoch( date(), time()+".123" )     // timestamp (opcionalis millis hozzatoldva)
    ? datetime2epoch( date(), time(), toffset )   // megadhato a timezone offset (default a local)
    ?

    // ezek mind ugyanazt az idopontot jelentik
    // csak kulonbozó idozonakban vannak kiirva

    xmldate_m2 :=epoch2xmldate(epoch,-toffset)
    xmldate_z  :=epoch2xmldate(epoch,)            // XML-be irhato timestamp
    xmldate_p2 :=epoch2xmldate(epoch,toffset)

    PRINT(xmldate_m2)
    PRINT(xmldate_z)
    PRINT(xmldate_p2)
    ?

    // ellenőrzés
    ? epoch - xmldate2epoch(xmldate_m2)
    ? epoch - xmldate2epoch(xmldate_z)
    ? epoch - xmldate2epoch(xmldate_p2)
    ?
    ?

