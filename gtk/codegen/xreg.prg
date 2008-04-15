
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
function main(fspec)

local x,o,pos:=1

    readinput(fspec)
    readobhi("obhi.txt")

    pos:=1
    while( !empty(x:=getdef({},@pos)) )
        if( x[1]=="define-method" )
            o:=gtkdefNew(x)
            if( "REG"$o:ccc .or. empty(o:ccc) .and. empty(o:state) )
                codegen_reg1(o) //metódusok
            end
        end
    end
    
    //retclid()

    pos:=1
    while( !empty(x:=getdef({},@pos)) )
        if( x[1]=="define-function" )
            o:=gtkdefNew(x)
            if( "REG"$o:ccc .or. empty(o:ccc) .and. empty(o:state) )
                codegen_reg2(o) //konstruktorok
            end
        end
    end

    moduleclose()

    ?

******************************************************************************
