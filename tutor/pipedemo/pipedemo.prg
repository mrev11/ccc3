
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

*****************************************************************************
function main()

local p:=child("echo.exe") //{r,w}
local buf:=padr("Van, aki forrón szereti!",32),n
local th:=thread_create({||read(p[1])})

    set printer to pipedmo.log
    set printer on
 
    for n:=1 to 10
        fwrite(p[2],buf)
        sleep(100)
    next
    fclose(p[2])
    thread_join(th)
    return NIL

*****************************************************************************
function read(fd)
local buf:=bin(0)
    while( 0<fread(fd,@buf,1) )
        ?? buf
    end
    return NIL


*****************************************************************************
 