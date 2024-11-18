
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

static option_hash:=option_hash()


***************************************************************************************
function param_iface()
local iface:=option_hash["iface"]
    return if(iface==NIL,"localhost",iface)


***************************************************************************************
function param_port()
local port:=option_hash["port"]
    return if( port==NIL,45678,val(port))



***************************************************************************************
function param_ssl()
static ssl:=if(option_hash["ssl"]=="false",.f.,.t.)
    return ssl  

// false: nem használ SSL-t, true: SSL-t használ, default=true
//
// Az SSL-lel osszhangban levo URL-t kell megadni a bongeszoben, pl.:
//  (plain)   http://localhost:45678/webapp 
//  (ssl)     https://localhost:45678/webapp


***************************************************************************************
function param_gzip()
static gzip:=if(option_hash["gzip"]=="false",.f.,.t.)
    return gzip

// false: nem tomorit, true: tomorit, default=true


***************************************************************************************
function param_permessage_deflate()
static pmd:=if(option_hash["permessage-deflate"]=="false",.f.,.t.)
    return pmd

// false: nem tomorit, true: tomorit, default=true


***************************************************************************************
function param_exec()
static module:=if(option_hash["exec"]==NIL,"/bin/bash",option_hash["exec"])
    return module


***************************************************************************************
