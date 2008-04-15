
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


class template(object)
    method initialize
    attrib cargo

static function template.initialize(this)
    this:(object)initialize
    return this


#ifdef NOT_DEFINED
//Régen így definiáltuk az osztályokat.
//Ez most is működik, csak kicsit nyüstös.

static clid_template:=templateRegister()

****************************************************************************
static function templateRegister()
local clid:=classRegister("template",{objectClass()})
    classMethod(clid,"initialize",{|this|templateIni(this)})
    classAttrib(clid,"cargo")
    return clid


****************************************************************************
function templateClass()
    return clid_template


****************************************************************************
function templateNew()
local clid:=templateClass()
    return objectNew(clid):initialize()


****************************************************************************
function templateIni(this)
    objectIni(this)
    return this
    
****************************************************************************
#endif
