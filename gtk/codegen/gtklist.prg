
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

#include "table.ch"
#include "_gtkapi.ch"



******************************************************************************
static function filter_g()
    //a nem nyilvános API függvények ilyenek
    //ezeket egyelőre teljesen kihagyjuk minden vizsgálatból
    //kb. 25-30 ilyen van
    return "G"$GTKAPI_STATE


******************************************************************************
static function filter_x()
    return !empty(GTKAPI_KIHAGY)



******************************************************************************
function main()

local flags

    GTKAPI:open
    GTKAPI:control:="capi"
    GTKAPI:gotop
    

    while( !GTKAPI:eof )
    
        if( filter_g() )
            GTKAPI:skip
            loop
        end

        if( !filter_x() )
            GTKAPI:skip
            loop
        end

    
        flags:=""
        flags+=if(GTKAPI_ISFUNCTION,"F","M")
        flags+=if(GTKAPI_ISCONSTRUC,"C","_")
        flags+=if(GTKAPI_RETOPTION,"R","_")
        flags+=if(GTKAPI_VARARGS,"V","_")
        
        ??  GTKAPI_CAPI,;
            GTKAPI_KIHAGY,;
            flags,;
            GTKAPI_STATE,;
            GTKAPI_RETTYPE,;
            GTKAPI_MODNAME,;
            GTKAPI_CLNAME,;
            GTKAPI_CCCAPI
            

        if(!empty(GTKAPI_PARAMETERS))
            ?? " PAR"+alltrim(GTKAPI_PARAMETERS)
        end

        if(!empty(GTKAPI_CCC))
            ?? " CCC{"+alltrim(GTKAPI_CCC)+"}"
        end

        if(!empty(GTKAPI_CODEBLOCK))
            ?? " BLK"+alltrim(GTKAPI_CODEBLOCK)
        end
        ?

        GTKAPI:skip
    end

******************************************************************************
