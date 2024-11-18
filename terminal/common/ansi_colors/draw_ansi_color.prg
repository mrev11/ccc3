
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

******************************************************************************************
function main(bg:="1",fg:="0")


    ? chr(27)+"[38;5;"+ fg +"m"+chr(27)+"[48;5;"+ bg +"m                        "+chr(27)+"[m "
    ? chr(27)+"[38;5;"+ fg +"m"+chr(27)+"[48;5;"+ bg +"m                        "+chr(27)+"[m "
    ? chr(27)+"[38;5;"+ fg +"m"+chr(27)+"[48;5;"+ bg +"m                        "+chr(27)+"[m "
    ?? ansi_colors(bg::val+1)::rgb
   
    ?

******************************************************************************************
static function rgb(rgb)
local x:=" ["

    x+=" "+rgb[1]::l2hex::padl(2,"0")
    x+=" "+rgb[2]::l2hex::padl(2,"0")
    x+=" "+rgb[3]::l2hex::padl(2,"0")
    x+=" ] "
    
    return x

******************************************************************************************
    