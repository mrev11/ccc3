
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

#include "set.ch"
#include "fileconv.ch"
 
***********************************************************************
function _clp_set(spec,newset,mode,xmode)

    if( spec==_SET_CONSOLE )
        return setconsole(newset)

    elseif( spec==_SET_PRINTER )
        return setprinter(newset)

    elseif( spec==_SET_PRINTFILE )
        return setprintfile(newset,mode,xmode)

    elseif( spec==_SET_ALTERNATE )
        return setalternate(newset)

    elseif( spec==_SET_ALTFILE )
        return setaltfile(newset,mode,xmode)

    elseif( spec==_SET_EXTRA )
        return setextra(newset)

    elseif( spec==_SET_EXTRAFILE )
        return setextrafile(newset,mode,xmode)

    //elseif( spec==_SET_CURSOR )
    //    return setcursor(newset)

    elseif( spec==_SET_COLOR )
        return setcolor(newset)

    elseif( spec==_SET_INSERT )
        return setinsert(newset)

    elseif( spec==_SET_EXIT )
        //return readexit(newset)

    elseif( spec==_SET_CONFIRM )
        return setconfirm(newset)

    elseif( spec==_SET_DATEFORMAT )
        return setdateformat(newset)

    elseif( spec==_SET_DOSCONV )
        return setdosconv(newset)
 
    end
    return NIL


***********************************************************************
function setprintfile(p1,p2,p3)
static setting
local oldsetting:=setting
      
    if( p1==NIL )
        //lekérdezés        

    elseif( valtype(p1)=="C" )
        setting:=p1
        __printer(p1,p2,p3)

    end
    return oldsetting


***********************************************************************
function setaltfile(p1,p2,p3)
static setting
local oldsetting:=setting
      
    if( p1==NIL )
        //lekérdezés        

    elseif( valtype(p1)=="C" )
        setting:=p1
        __alternate(p1,p2,p3)

    end
    return oldsetting


***********************************************************************
function setextrafile(p1,p2,p3)
static setting
local oldsetting:=setting
      
    if( p1==NIL )
        //lekérdezés        

    elseif( valtype(p1)=="C" )
        setting:=p1
        __extra(p1,p2,p3)

    end
    return oldsetting


***********************************************************************
function setcolor(newset)
static setting:="W/N,N/W,W/N,W/N,W/N,W/N,W/N"
local oldsetting:=setting
      
    if( newset==NIL )
        //lekérdezés        

    elseif( valtype(newset)=="C" )
        setting:=newset
        __clr2num(newset)

    end
    return oldsetting


***********************************************************************
function setinsert(newset)
static setting:=.t.
local oldsetting:=setting
      
    if( newset==NIL )
        //lekérdezés        

    elseif( valtype(newset)=="L" )
        setting:=newset

    end
    return oldsetting


***********************************************************************
function setconfirm(newset)
static setting:=.t.
local oldsetting:=setting
      
    if( newset==NIL )
        //lekérdezés        

    elseif( valtype(newset)=="L" )
        setting:=newset

    end
    return oldsetting


***********************************************************************
function setdateformat(newset,rec)
static setting:="yy.mm.dd"  //default
local oldsetting:=setting
      
    if( newset==NIL )
        //lekérdezés        

    elseif( valtype(newset)=="C" )
        setting:=lower(alltrim(newset))

    end
    return oldsetting


***********************************************************************
function __setcentury(arg)

local dform:=setdateformat()
local prevstate:="yyyy"$dform

    if( arg!=NIL )

        dform:=strtran(dform,"yyyy","?")
        dform:=strtran(dform,"yy","?")

        if( (valtype(arg)=="L" .and. arg) .or.;
            (valtype(arg)=="C" .and. "on"==lower(alltrim(arg))) )

            dform:=strtran(dform,"?","yyyy")
        else
            dform:=strtran(dform,"?","yy")
        end

        setdateformat(dform)
    end
    return prevstate


***********************************************************************
function setdosconv(newset)
local prevset:=get_dosconv()
    if( newset==NIL )
        //csak lekérdezés

    elseif( valtype(newset)=="N" )
        set_dosconv(newset)

    elseif( lower(newset)=="fileshare" )
        set_dosconv(DOSCONV_FILESHARE)
 
    elseif( lower(newset)=="off" )
        set_dosconv(0)

    elseif( lower(newset)=="on" )
        reset_dosconv()

    elseif( lower(newset)=="default" )
        reset_dosconv()
 
    end
    return prevset


***********************************************************************
 