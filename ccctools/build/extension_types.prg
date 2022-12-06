
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


****************************************************************************
function extension_types()
local r1,r2,n

    s_primary("")
    s_resource("")

    for n:=1 to len(s_rules())
        r1:=s_rules()[n][1]
        r2:=s_rules()[n][2]

        //vigyazat: tdc$primary and tdc$resource!
        
        if( r2==".obj" )
            s_primary(s_primary()+r1)
        end
        if( !r2+"."$".obj.lib.exe." )
            s_resource(s_resource()+r1) //tobbszorozodhet
        end
    next
    s_primary(s_primary()+".")
    s_resource(s_resource()+".")
    //? s_primary()
    //? s_resource()

*
***************************************************************************
