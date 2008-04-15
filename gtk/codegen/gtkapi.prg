
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


function gtkapi_append(o,kihagy)
if( !empty(getenv("GTKAPI_BT")) )
    GTKAPI:seek(o:c_api)

    if( !alltrim(GTKAPI_CAPI)==o:c_api )

        GTKAPI:append

        GTKAPI_CAPI        :=o:c_api
        GTKAPI_CCCAPI      :=o:ccc_api
        GTKAPI_ISFUNCTION  :=o:isfunction
        GTKAPI_ISMETHOD    :=o:ismethod
        GTKAPI_ISCONSTRUC  :=o:isconstructor
        GTKAPI_CLNAME      :=o:clname
        GTKAPI_MODNAME     :=o:modname
        GTKAPI_STATE       :=o:state
        GTKAPI_RETTYPE     :=o:return_type
        GTKAPI_RETOPTION   :=!empty(o:return_option)
        GTKAPI_VARARGS     :=!empty(o:varargs)
        GTKAPI_CCC         :=o:ccc
        GTKAPI_CODEBLOCK   :=o:codeblock
        GTKAPI_PARAMETERS  :=arr2str(o:parameters)
    else
        alert(o:c_api)
    end
    
    if( kihagy!=NIL )
        GTKAPI_KIHAGY:=alltrim(GTKAPI_KIHAGY)+kihagy
    end
end
