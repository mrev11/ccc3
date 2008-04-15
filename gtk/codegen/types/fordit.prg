
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
function main()
local x,n,p,i

    set printer to obhi-rev.txt
    set printer on

    x:=memoread("obhi.txt")
    x:=split(x,chr(10))
    for n:=1 to len(x)
        p:=x[n]
        p:=strtran(p,"{","")
        p:=strtran(p,"}","")
        p:=split(p)
        if( empty(p) )
            loop
        end
        arev(p)
        for i:=1 to len(p)
            if( i==1 )
                ? "{"
            else
                ?? ","
            end
            ?? p[i]
        next
        ?? "}"
    next

******************************************************************************
static function arev(a)
local n:=len(a),t,i
    for i:=1 to int(n/2)
        t:=a[i]
        a[i]:=a[n-i+1]
        a[n-i+1]:=t
    next

******************************************************************************
    