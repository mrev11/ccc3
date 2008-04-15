
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

//jtget-ek, picture-ök tanulmányozásához

#include "get.dlg"

function main()

local dlg,msg

    dlg:=getNew()
    //dlg:(object)list
 
    dlg:char:picture   := "@R XXXXXXXX/XXXXXXXX"
    dlg:number:picture := "@RN 999,999,999.99" 
    dlg:date:picture   := "@RDXE" 
    dlg:f:picture      := "@L!X" 

    dlg:ok:focusable   := .f.
    
    dlg:char:varput( "!"+chr(12)+"!" ) // XML-ben invalid!

    dlg:show
    
    while(  NIL!=(msg:=dlg:getmessage) )
        if( msg=="ok" )
            dlg:list
        end
    end
    
    return NIL
    
    
    