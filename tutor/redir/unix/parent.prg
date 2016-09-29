
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

function main()

local p1:=pipe()
local r1:=p1[1],w1:=p1[2]
local redir:=" <&"+alltrim(str(r1))
local nowait:=" &"
local torun:="child.exe"
local childpid,d,n 
    
    if( (childpid:=fork())==0 )
        //child
        fclose( w1 )
        run( torun+redir ) //vár!
        quit
    end

    //parent

    fclose( r1 )
    
    d:=directory("*","H")
    
    for n:=1 to len(d)
        fwrite( w1, d[n][1]+endofline() )
    next

    fclose( w1 )

    waitpid(childpid,,0) //0 hang, 1 nohang
    
    //child.exe kilépését az jelzi, hogy kilép a fork-kal  
    //indított process, amit waitpid-del megvárunk;
    //ennek a megoldásnak szépséghibája, hogy egyszerre
    //négy program is fut: parent,parent,sh,child
    
    return NIL
