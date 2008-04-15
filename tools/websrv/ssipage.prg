
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

#include "websrv.ch"

*****************************************************************************
function ssipage(wd,fspec) //server side include

local x:=memoread(fspec,.t.)
local t1:=a"<!--#include",t2:=a"-->"
local pos,a,b,inc,locinc,absinc

    while( (pos:=at(t1,x))>0 )
        a:=left(x,pos-1)  // a<--#include...
        x:=substr(x,pos+len(t1))
        pos:=at(t2,x)
        if( pos==0 )
            pos:=len(x)
        end
        b:=substr(x,pos+len(t2))  // ...-->b
        x:=alltrim(left(x,pos-1)) // virtual="inc"
        if( left(x,9)==a'virtual="' .and. right(x,1)==a'"' )
            inc:=substr(x,10,len(x)-10)

            if( left(inc,1)==a"/" )
                absinc:=wd+inc
                x:=ssipage(wd,absinc)
            else
                locinc:=fpath0(fspec)+a"/"+inc
                if( file(locinc) )
                    x:=ssipage(wd,locinc)
                else
                    absinc:=wd+a"/"+inc
                    x:=ssipage(wd,absinc)
                end
            end
        else
            x:=a""  //invalid format
        end
        x:=a+x+b
    end
    return x //binary

*****************************************************************************

