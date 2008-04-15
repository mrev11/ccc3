
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

local key,env,i
local rus:="Копирование и распространение"

    set alternate to proba.log
    set alternate on

    ? getenv("CCCTERM_CONNECT")

    setcursor(1)
    ? "proba szerencse 1"
    @ 0,1 say "Van, aki forrón szereti."
    @ 1,1 say "Öt szép szűzlány őrült írót nyúz."
    @ 2,8 say rus  color "bg+/b"
    devoutvertical(rus,"w+/r")
    devout(rus,"b+/r")

    ? "proba szerencse 2"
    
    @  2,1 say x"e29594"+x"e29590"+x"e295a6"+x"e29590"+x"e29597"
    @  3,1 say x"e29591"+x"20"    +x"e29591"+x"20"    +x"e29591"
    @  4,1 say x"e295a0"+x"e29590"+x"e295ac"+x"e29590"+x"e295a3"
    @  5,1 say x"e2959a"+x"e29590"+x"e295a9"+x"e29590"+x"e2959d"

    @  7,1 say x"e2948c"+x"e29480"+x"e294ac"+x"e29480"+x"e29490"
    @  8,1 say x"e29482"+x"20"    +x"e29482"+x"20"    +x"e29482"
    @  9,1 say x"e2949c"+x"e29480"+x"e294bc"+x"e29480"+x"e294a4"
    @ 10,1 say x"e29494"+x"e29480"+x"e294b4"+x"e29480"+x"e29498"

    @ 12,1 say x"e29592"+x"e29590"+x"e295a4"+x"e29590"+x"e29595"
    @ 13,1 say x"e2959e"+x"e29590"+x"e295aa"+x"e29590"+x"e295a1"
    @ 14,1 say x"e29598"+x"e29590"+x"e295a7"+x"e29590"+x"e2959b"

    @ 16,1 say x"e29593"+x"e29480"+x"e295a5"+x"e29480"+x"e29596"
    @ 17,1 say x"e2959f"+x"e29480"+x"e295ab"+x"e29480"+x"e295a2"
    @ 18,1 say x"e29599"+x"e29480"+x"e295a8"+x"e29480"+x"e2959c"

    @ 20,1 say replicate(x"e29691",8)
    @ 21,1 say replicate(x"e29692",8)
    @ 22,1 say replicate(x"e29693",8)
    @ 23,1 say replicate(x"e29688",8)
    
    //sleep(2000)
        
    keyboard("ABCDEFGH")
    
    setpos(10,40)
    
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
        
    end
    ?
