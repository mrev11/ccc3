
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

*************************************************************************
function _clp_strtran(s,s1,s2,sta,cnt)

// s  : alapstring
// s1 : ennek előfordulásait keressük
// s2 : s1 előfordulásait erre cseréljük
// sta: start (első cserélendő előfordulás), default=1
// cnt: cserék száma, default=összes

local l1:=len(s1),l2
local p1:=1,p
local no:=0   //előfordulások száma
local chg:=0  //cserék száma

    if( s2==NIL )
        s2:=left(s1,0) //típustól függően "" vagy a"" (2006.10.17)
    end
    l2:=len(s2)
              
    while( (cnt==NIL.or.chg<cnt) .and. 0<(p:=at(s1,s,p1))  )
        if( sta!=NIL .and. ++no<sta )
            p1:=p+1 //!
        else
            s:=stuff(s,p,l1,s2)
            p1:=p+l2
            chg++
        end
    end
    return s


*************************************************************************
