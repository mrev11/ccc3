
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
#include "fileconv.ch"

#include "table.ch"
#include "table.gtkapi.tdh"

*******************************************************************************
function main()

local dc:=setdosconv(DOSCONV_BS2SLASH+DOSCONV_FNAME2LOWER )

local defs:=directory("../defs/*.defs","H")
local defsa:=directory("../defs/api/*.defs","H")
local defsr:=directory("../defs/reg/*.defs","H")

local api:=directory(codedir()+dirsep()+"*_api.cpp","H")
local reg:=directory(codedir()+dirsep()+"*_reg.prg","H")
local n

    gtkapi_init()

    dirmake(codedir())

    for n:=1 to len(defs)
        xapi(api,defs[n],"../defs/"+defs[n][F_NAME])
        xreg(reg,defs[n],"../defs/"+defs[n][F_NAME])
    next
    for n:=1 to len(defsa)
        xapi(api,defsa[n],"../defs/api/"+defsa[n][F_NAME])
    next
    for n:=1 to len(defsr)
        xreg(reg,defsr[n],"../defs/reg/"+defsr[n][F_NAME])
    next

    ?

*******************************************************************************
static function xapi(api,def,fspec)
    if( get_time(api,def[F_NAME]) < ftime(def) )
        xprint(def[F_NAME], "api")
        run("xapi.exe >log.bak "+fspec)
    end

static function xreg(reg,def,fspec)
    if( get_time(reg,def[F_NAME]) < ftime(def) )
        xprint(def[F_NAME], "reg")
        run("xreg.exe >log.bak "+fspec)
    end

*******************************************************************************
static function xprint(name,mode)
static lastname
    if( lastname==name )
        ?? "",mode
    else
        ? name,mode
        lastname:=name
    end

*******************************************************************************
static function get_time(dir,name)
local time:="0"
local idx:=ascan(dir,{|x|nametran(x[F_NAME])==name})
    if(idx>0)
        time:=ftime(dir[idx])
    end
    return time

*******************************************************************************
static function nametran(name)
    name:=strtran(name,"_api.cpp",".defs")
    name:=strtran(name,"_reg.prg",".defs")
    name:=strtran(name,"_","")
    return name


*******************************************************************************
static function ftime(spec)
    return dtos(spec[F_DATE])+spec[F_TIME]


*******************************************************************************
static function gtkapi_init()
    if( !empty(getenv("GTKAPI_BT")) )
        GTKAPI:create
        GTKAPI:open(OPEN_EXCLUSIVE)
        GTKAPI:zap
        GTKAPI:close
    end

******************************************************************************
