
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

******************************************************************************
function main()
local x,n,p,macro

    set printer to types.txt
    set printer on

    x:=memoread("obhi.txt")
    x:=split(x,chr(10))

    for n:=1 to len(x)
        p:=x[n]
        p:=strtran(p,"{","")
        p:=strtran(p,"}","")
        p:=split(p)
        if( empty(p) )
            loop
        end
        macro:=macroname(p[1])
        
        macro:=strtran(macro,"_I_M_","_IM_") //kivétel
        
        if( at("GTK_",macro)==1 )
            ? macro
        end
    next

    ? "GTK_CLIPBOARD" //hiányzik

******************************************************************************
static function macroname(object)

local x:=object 

    x:=strtran(x, "A","_a" )
    x:=strtran(x, "B","_b" )
    x:=strtran(x, "C","_c" )
    x:=strtran(x, "D","_d" )
    x:=strtran(x, "E","_e" )
    x:=strtran(x, "F","_f" )
    x:=strtran(x, "G","_g" )
    x:=strtran(x, "H","_h" )
    x:=strtran(x, "I","_i" )
    x:=strtran(x, "J","_j" )
    x:=strtran(x, "K","_k" )
    x:=strtran(x, "L","_l" )
    x:=strtran(x, "M","_m" )
    x:=strtran(x, "N","_n" )
    x:=strtran(x, "O","_o" )
    x:=strtran(x, "P","_p" )
    x:=strtran(x, "Q","_q" )
    x:=strtran(x, "R","_r" )
    x:=strtran(x, "S","_s" )
    x:=strtran(x, "T","_t" )
    x:=strtran(x, "U","_u" )
    x:=strtran(x, "V","_v" )
    x:=strtran(x, "W","_w" )
    x:=strtran(x, "X","_x" )
    x:=strtran(x, "Y","_y" )
    x:=strtran(x, "Z","_z" )

    //itt tartunk:
    // GtkWidget --> _gtk_widget

    x:=strtran(x, "_gtk_", "GTK_" )

    return upper(x)

******************************************************************************
    