
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

local blk0:={|*|qualified.name.f(*)}
local blk1:={|x,a,b|qualified.name.f(x,a,b)}
local x,y,z

    ? qualified.name.f(@x,"a","b","c"), x
    ? eval(blk0,@y,"a","b","c"), y          //k?zvetlen f?ggv?nyh?v?s
    ? eval(blk1,@z,"a","b","c"), z          //param?terek ?tpakkolva
    ?


static function qualified.name.f(x,a,b,c,d)
    //varstack()
    x:=cat(x,a)
    x:=cat(x,b)
    x:=cat(x,c)
    x:=cat(x,d)
    return x


static function cat(x,y)
    return if(x==NIL,"",x)+if(y==NIL,"",y)
