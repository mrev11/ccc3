
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

local i,key
local rus:="Копирование и распространение"

    setcursor(0)
    setcolor("b/w")

    for i:=0 to maxrow()
        @ i,0 say replicate( chr(asc("a")+i), maxcol()+1 ) 
    next 

    setcolor("w/bg")
    
    scroll(3,3,13,13,4)
    
    inverserect(10,20,20,40)

    while( key!=27 )
        ? key:=inkey(0)
         
        if( .f. )
        elseif( key==5 ) //up
            setpos(row()-1,col())
        elseif( key==24) //down
            setpos(row()+1,col())
        elseif( key==19) //left
            setpos(row(),col()-1)
        elseif( key==4)  //right
            setpos(row(),col()+1)
        elseif( key==8)  //BS
            @ row(),col()-1 say space(1)
            setpos(row(),col()-1)
        else
            @ row(),col() say chr(key)
            setpos(row(),col()+1)
        end


        ?? " row="+alltrim(str(row())), "col="+alltrim(str(col()))
        ?? "",isalnum(chr(key))
        setcursor(1)
    end
    