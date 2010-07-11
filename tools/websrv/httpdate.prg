
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

static mon:=mon_init()

***************************************************************************************
static function mon_init()
local hash:=simplehashNew()
    hash[a"Jan"]:=a"01"
    hash[a"Feb"]:=a"02"
    hash[a"Mar"]:=a"03"
    hash[a"Apr"]:=a"04"
    hash[a"May"]:=a"05"
    hash[a"Jun"]:=a"06"
    hash[a"Jul"]:=a"07"
    hash[a"Aug"]:=a"08"
    hash[a"Sep"]:=a"09"
    hash[a"Oct"]:=a"10"
    hash[a"Nov"]:=a"11"
    hash[a"Dec"]:=a"12"
    return hash


***************************************************************************************
function httpdate_value(text)

//Sun, 06 Nov 1994 08:49:37 GMT
//00000000011111111112222222222
//12345678901234567890123456789

local y,m,d,t,s

    text::=str2bin

    y:=text[13..16]
    m:=mon[text[9..11]]
    d:=text[6..7]
    t:=text[18..25]

    if( m!=NIL )
        s:=y+m+d
        if( s::stod::cdow::str2bin::left(3)==text[1..3] )
            return s+t
        end
    end
    
    return a"0000000000:00:00"

***************************************************************************************
