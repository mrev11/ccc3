
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
function timetosec(ctime)  //CA-tools
local s:=0
    s+=val(substr(ctime,1,2))*3600
    s+=val(substr(ctime,4,2))*60
    s+=val(substr(ctime,7,2))
    s+=val(substr(ctime,10,2))/100
    return s


*****************************************************************************
function sectotime(sec) //CA-tools 
local h,m,s
    h:=int(sec/3600) 
    sec-=h*3600    
    m:=int(sec/60)
    s:=int(sec-m*60)
    return padl(h,2,"0")+":"+padl(m,2,"0")+":"+padl(s,2,"0")


*****************************************************************************
 