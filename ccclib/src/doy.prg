
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

***********************************************************************
function doy(date) //CA-tools, day of year
local s,d

    if( date==NIL )
        date:=date()
    end

    if( !empty(date) )
        s:=dtos(date)
        d:=stod(left(s,4)+"0101")
        return (date-d)+1
    end
    return 0
 
 
***********************************************************************
function eom(date) //CA-tools, end of month
local s
    if( date==NIL )
        date:=date()
    end
    if( empty(date) )
        return date
    end
    s:=left(dtos(date),6)+padl(lastdayom(date),2,"0")
    return stod(s)


***********************************************************************
function eoy(date)  //CA-tools, end of year
local s
    if( date==NIL )
        date:=date()
    end
    if( empty(date) )
        return date
    end
    s:=left(dtos(date),4)+"1231"
    return stod(s)
 

***********************************************************************
function bom(date)  //CA-tools, beginning of month 
local s
    if( date==NIL )
        date:=date()
    end
    if( empty(date) )
        return date
    end
    s:=left(dtos(date),6)+"01"
    return stod(s)
 

***********************************************************************
function boy(date)  //CA-tools, beginning of year
local s
    if( date==NIL )
        date:=date()
    end
    if( empty(date) )
        return date
    end
    s:=left(dtos(date),4)+"0101"
    return stod(s)


***********************************************************************
 