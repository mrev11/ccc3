
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

// random(mode) CA-tools, egyenletes (0,65536)/(-32768,32768)
// rand(init)   CA-tools, egyenletes (0,1), inicializálható 

// 2001.12.09
// Korábban rand() is Clipperben volt implementálva, 
// de (hibásan) nagyon kis periódussal működött,
// ezért átkerült rand.cpp-be, ahol pontosabban implementált
// lebegőpontos dmod-dal nem kimutatható a periódus.

***************************************************************************** 
function random(mode) 
local r:=rand()     
    if( mode==.t. )
        r:=round((r-0.5)*65535,0) 
    else
        r:=round(r*65535,0) 
    end
    return r

***************************************************************************** 
