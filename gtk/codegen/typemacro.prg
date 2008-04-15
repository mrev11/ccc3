
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

static types:=readtypes()

******************************************************************************
function maindbg()
local n
    for n:=1 to len(types)
        ? types[n][1]+"(0);"
    next

******************************************************************************
function type_macro(type)
local n,type2

    if( right(type,1)=="*" .and. !right(type,2)=="**" )
        type2:=strtran(type,"*","")

        for n:=1 to len(types)
            if( types[n][2]==type2 )
                return types[n][1]
            end
        next
    end

    return NIL


******************************************************************************
function typed_name(type,name)
local n,type2

    if( right(type,1)=="*" .and. !right(type,2)=="**" )

        type2:=strtran(type,"*","")

        for n:=1 to len(types)
            if( types[n][2]==type2 )
                return types[n][1]+"("+name+")"
            end
        next
    end
    
    return  name

******************************************************************************
static function readtypes()
local x,n
    x:=memoread("types.txt")
    x:=strtran(x,chr(13),"")
    x:=split(x,chr(10))
    for n:=1 to len(x)
        x[n]:={x[n],objectname(x[n])}
    next
    return x

******************************************************************************
function objectname(makro)

local x:=lower(makro)

    x:=strtran(x, "gtk_", "Gtk_" )
    x:=strtran(x, "_a","A" )
    x:=strtran(x, "_b","B" )
    x:=strtran(x, "_c","C" )
    x:=strtran(x, "_d","D" )
    x:=strtran(x, "_e","E" )
    x:=strtran(x, "_f","F" )
    x:=strtran(x, "_g","G" )
    x:=strtran(x, "_h","H" )
    x:=strtran(x, "_i","I" )
    x:=strtran(x, "_j","J" )
    x:=strtran(x, "_k","K" )
    x:=strtran(x, "_l","L" )
    x:=strtran(x, "_m","M" )
    x:=strtran(x, "_n","N" )
    x:=strtran(x, "_o","O" )
    x:=strtran(x, "_p","P" )
    x:=strtran(x, "_q","Q" )
    x:=strtran(x, "_r","R" )
    x:=strtran(x, "_s","S" )
    x:=strtran(x, "_t","T" )
    x:=strtran(x, "_u","U" )
    x:=strtran(x, "_v","V" )
    x:=strtran(x, "_w","W" )
    x:=strtran(x, "_x","X" )
    x:=strtran(x, "_y","Y" )
    x:=strtran(x, "_z","Z" )

    return x

******************************************************************************
function macroname(object)

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
