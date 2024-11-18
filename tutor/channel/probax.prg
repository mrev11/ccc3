
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

local a,b,c,d

    set channel(a) to log-proba-a  additive
    set channel(b) to log-proba-b
    set channel(c) to log-proba-c
    set channel(d) to log-proba-d

    // ilyenekre preprocesszalodik
    // (a:=channelNew("log-proba-a")):open(.t.)
    // (b:=channelNew("log-proba-b")):open
    // (c:=channelNew("log-proba-c")):open
    // (d:=channelNew("log-proba-d")):open

    ? "ir a konzolra"

    a:on; ? "hopp a", 1 // lehetne: SET CHANNEL(a) ON; ? "hopp..."
    b:on; ? "hopp b", 1
    c:on; ? "hopp c", 1
    d:on; ? "hopp d", 1
                     
    a:on; ? "hopp a", 2
    b:on; ? "hopp b", 2
    c:on; ? "hopp c", 2
    d:on; ? "hopp d", 2

    d:off

    // vagy lehetne itt
    // SET CHANNEL(d) OFF
    // SET CHANNEL OFF 
    // channel.off()       
    
    
    ? "ez megint csak a konzolra megy"
    ?
    





