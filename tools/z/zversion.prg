
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

#include "z.ver"

 
function zversion()

#ifdef _CCC2_
local ccc:="CCC2"
#else
local ccc:="CCC3"
#endif


local v:="Z-editor "+VERSION+" "+ccc 

    if( maxrow()>=24 )

        v+=";;"
    
        v+="[ F2             save           ];"
        v+="[ F3 (shift)     search (next)  ];"
        v+="[ F4 (shift)     replace (next) ];"
        v+="[ F6 (shift)     lower (upper)  ];"
        v+="[ F7             clipboard      ];"
        v+="[ F10            save and exit  ];;"

        v+="[ X/C/V-alt      cut/copy/paste ];"
        v+="[ Y-ctrl         cut line       ];;"
 
        v+="[ Move-alt       mark           ];"
        v+="[ R-alt          RECT mode      ];"
        v+="[ W-alt          WIDE mode      ];;"
 
        v+="[ Escape         quit           ];"
    end
 
    return v

    


    