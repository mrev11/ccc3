
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
local p2:=pipe()
local r1:=p1[1],w1:=p1[2]
local r2:=p2[1],w2:=p2[2]
local d,n,c:=bin(0)
    
    if( 0==fork() )
        //child 

        fclose( w1 )           //csak a parent-nak kell
        fclose( r2 )           //csak a parent-nak kell 
        
        fclose(0); fdup(r1)    //átirányítva: stdin
        fclose(1); fdup(w2)    //átirányítva: stdout
        fclose(2); fdup(w2)    //átirányítva: stderr
        
        fclose(r1)             //már nem kell, ne öröklődjön
        fclose(w2)             //már nem kell, ne öröklődjön 
 
        exec( "/bin/bash", "-c", "child.exe" ) 
        quit
    end

    //parent
 
    fclose( r1 )               //csak a child-nak kell 
    fclose( w2 )               //csak a child-nak kell  
    
    d:=directory("*","H")
    
    for n:=1 to len(d)
        fwrite( w1, d[n][1]+endofline() )
    next

    fclose( w1 )
    
    while( 0<fread(r2,@c,1) )
        ?? upper(c)
    end
    
    //child.exe kilépését az jelzi, hogy lezáródik r2,
    //amibe child.exe az stdout-ját írja
    
    return NIL
