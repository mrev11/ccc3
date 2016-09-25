
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

#include "directry.ch"


***************************************************************************************
function main()
local wd:=dirsep()+curdir()
    isempty(wd)
    ?


***************************************************************************************
function isempty(path)

local cnt:=0,name,attr,n
local dir:=directory(path+dirsep()+fullmask(),"DLH")

    for n:=1 to len(dir)
        name:=dir[n][F_NAME]
        attr:=dir[n][F_ATTR]

        if( "."==name )
            //kihagy

        elseif( ".."==name )
            //kihagy

        elseif( ".git"==name )
            //kihagy

        elseif( ".svn"==name )
            //kihagy

        elseif( !"D"$attr )
            cnt++ //file

        elseif( !isempty(path+dirsep()+name) )
            cnt++ //nemüres directory

        //elseif( 0!=ferase(path+dirsep()+name) )
        elseif( 0!=dirremove(path+dirsep()+name) )
            ? "cannot delete", path+dirsep()+name
            cnt++ //nem törölhető directory
 
        else
            ? "deleted", path+dirsep()+name
        end
    next

    return cnt==0 //.t. ha üres


***************************************************************************************
    