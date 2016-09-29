
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

//Windows spawn, pipe example-0

******************************************************************************
function main()
    if( argc()<=1 )
        parent()
    else
        child()
    end
    return NIL


******************************************************************************
static function parent() //olvas a pipe-ból

local pp:=pipe()
local pr:=pp[1]
local pw:=pp[2]
local nbyte,buf:=replicate(a" ",32)

    spawn(.f., "test0.exe", str(pw) )
    
    fclose(pw)

    while( 0<(nbyte:=fread(pr,@buf,len(buf))) )
        ?? a"'"+left(buf,nbyte)+a"'", nbyte, crlf()
    end

    ? nbyte
    
    fclose(pr)

    return NIL
 
 
******************************************************************************
static function child() //ír a pipe-ba 

local pw:=val(argv(1))
local d:=directory("*.*","H"),n
 
    for n:=1 to len(d)
        fwrite( pw,d[n][1] )
        sleep(1000)
    end
    return NIL
 

******************************************************************************
 
    