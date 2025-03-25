
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
function psort(x,y)
local ix:=ruleidx(filespec.extension(x[2]),filespec.extension(x[1]))
local iy:=ruleidx(filespec.extension(y[2]),filespec.extension(y[1]))
    return if(ix==iy,x[1]<y[1],ix<iy)


****************************************************************************
static function ruleidx(e1,e2)
local n
    for n:=1 to len(s_rules())
        if( e1==s_rules()[n][1] .and. e2==s_rules()[n][2] )
            return n
        end
    next
    return 0


****************************************************************************
