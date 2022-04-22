
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
class xmlattrib(object)
    method  initialize
    attrib  name
    attrib  value
    method  nsprefix
    method  uqname

******************************************************************************
static function xmlattrib.initialize(this,name,value)
    this:(object)initialize(this)
    this:name:=name
    this:value:=value
    return this

******************************************************************************
static function xmlattrib.nsprefix(this)
local pos:=at(":",this:name)
    if( pos>0 )
        return left(this:name,pos-1)
    end
    return ""

******************************************************************************
static function xmlattrib.uqname(this)
local pos:=at(":",this:name)
    if( pos>0 )
        return substr(this:name,pos+1)
    end
    return this:name

******************************************************************************
