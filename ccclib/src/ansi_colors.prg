
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

static colors:=init_colors()


******************************************************************************************
static function init_colors()

local v := {0x00, 0x5f, 0x87, 0xaf, 0xd7, 0xff}


local i,r,g,b
local colors:={}

    // 1   ->  16  CGA alapszinek
    // 17  -> 231  szines arnyalatok
    // 232 -> 256  szurke arnyalatok


    colors::aadd({0x00,0x00,0x00})  // black    
    colors::aadd({0xc0,0x00,0x00})  // red      
    colors::aadd({0x00,0xc0,0x00})  // green    
    colors::aadd({0xc0,0xc0,0x00})  // yellow   
    colors::aadd({0x00,0x00,0xc0})  // blue     
    colors::aadd({0xc0,0x00,0xc0})  // magenta  
    colors::aadd({0x00,0xc0,0xc0})  // cyan     
    colors::aadd({0xe0,0xe0,0xe0})  // white    
                
    colors::aadd({0x60,0x60,0x60})  // lt-black  
    colors::aadd({0xff,0x40,0x40})  // lt-red    
    colors::aadd({0x40,0xff,0x40})  // lt-green  
    colors::aadd({0xff,0xff,0x40})  // lt-yellow 
    colors::aadd({0x40,0x40,0xff})  // lt-blue   
    colors::aadd({0xff,0x40,0xff})  // lt-magenta
    colors::aadd({0x40,0xff,0xff})  // lt-cyan   
    colors::aadd({0xff,0xff,0xff})  // lt-white  


    for i:=0 to 215
        r := v[ 1+ int(i/36)%6 ]
        g := v[ 1+ int(i/ 6)%6 ]
        b := v[ 1+ int(i   )%6 ]
        aadd(colors,{r,g,b})
    end

    for i:=0 to 23
        r:=8+i*10
        g:=8+i*10
        b:=8+i*10
        aadd(colors,{r,g,b})
    end

    return colors


******************************************************************************************
function ansi_colors(x)
    if( x==NIL )
        return colors
    end
    return colors[x] // {r,g,b}


******************************************************************************************
