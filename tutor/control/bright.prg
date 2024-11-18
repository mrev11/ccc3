
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

#define DISPLAY aeval(getlist,{|g|g:display})


#include "bright.say"

******************************************************************************************
function main()
    bright({|*|load(*)},{|*|readmodal(*)},{|*|.t.},)
    ?


******************************************************************************************
function load(getlist) 

    ? g_get1:colorspec   
    ? g_lab1:colorspec   

    g_lab1:varput("Egyszer hopp, máskor kopp.")
    g_lab2:varput("Van, aki forrón szereti.")
    
    g_get1:varput("Próba szerencse!")
    g_get2:varput("Hány meggymag megy ma Magyra?")
    g_get3:varput("Mit sütsz kis szűcs?")

    g_alt:alternatives("Kutya/Macska/Nyúl")


    g_lab2:bright:=.t.
    g_get2:bright:=.t.
 
    DISPLAY
    
******************************************************************************************

    