
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
local a
    settermsize(10,30)
    while(.t.)
        a:=alert("settermsize",{"a","b","c","d","e"})
        if(a==0)
            exit
        elseif(a==1)
            settermsize(10,30)
        elseif(a==2)
            settermsize(14,35)
        elseif(a==3)
            settermsize(18,40)
        elseif(a==4)
            settermsize(24,60)
        elseif(a==5)
            settermsize(32,80)
        end
    end
