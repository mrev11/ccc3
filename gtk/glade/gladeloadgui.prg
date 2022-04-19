
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
function gladeloadgui(fspec)
local glade,parser,dom
local gladepath,n,f,err

    gladepath:=getenv("GLADEPATH")
    gladepath:=strtran(gladepath,":",";")
    gladepath:=split(".;"+gladepath,";")

    for n:=1 to len(gladepath)
        f:=gladepath[n]+dirsep()+fspec
        if( file(f) )
            exit
        end
    next

    if( !file(f) )
        err:=apperrorNew()
        err:operation:="gladeloadgui"
        err:description:="file not found"
        err:filename:=fspec
        break(err)
    end

    glade:=memoread(f,.t.)
    parser:=xmlparser2New()
    parser:entityconv:=.t.
    dom:=parser:parsestring(glade)

    return gladewidgetNew(dom)

******************************************************************************
function gladeloadgui_from_string(glade)
local parser,dom

    parser:=xmlparser2New()
    parser:entityconv:=.t.
    dom:=parser:parsestring(glade)

    return gladewidgetNew(dom)

******************************************************************************

