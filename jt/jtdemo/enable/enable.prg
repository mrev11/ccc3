
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

#include "enable.dlg"

function main()

local dlg,msg

    jtencoding("UTF-8")

    dlg:=enableNew()
    //dlg:(object)list
 
    dlg:enb:valid     := .t. 
    dlg:enb:varput    := .t.

    dlg:foc:valid     := .t. 
    dlg:foc:varput    := .t.

    dlg:get:varput    := "Próba szerencse!"
 
    dlg:show
    
    while(  NIL!=(msg:=dlg:getmessage) )
        if( msg=="enb" )
            dlg:get:changeenabled( dlg:enb:varget ) 
        elseif( msg=="foc" )
            dlg:get:changefocusable( dlg:foc:varget ) 
            if( dlg:foc:varget )
                dlg:get:setfocus
            end
        elseif( msg=="ok" )
            dlg:close
        end
    end
    
    return NIL

