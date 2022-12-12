
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

class array(object)
    attrib   array
    attrib   ecount
    method   initialize
    method   add
    method   resize
    
static function array.initialize(this)
    this:array:=array(256)
    this:ecount:=0
    return this

static function array.add(this,x)                                                    
   if( len(this:array)<=this:ecount )
       asize(this:array,len(this:array)+1024)
   end
   this:array[++this:ecount]:=x
   return x

static function array.resize(this)
   return asize(this:array,this:ecount)



#ifdef NOTDEFINED
****************************************************************************
function arrayClass() 
static clid_array:=arrayRegister()
    return clid_array

****************************************************************************
static function arrayRegister() 
local clid:=classRegister("array",{objectClass()})
    classMethod(clid,"initialize",{|this|arrayIni(this)})
    classAttrib(clid,"array")  
    classAttrib(clid,"ecount")  
    classMethod(clid,"add",{|this,x|_array_add(this,x)})  
    classMethod(clid,"resize",{|this|_array_resize(this)})  
    return clid

****************************************************************************
function arrayNew() 
local clid:=arrayClass()
    return objectNew(clid):initialize()

****************************************************************************
function arrayIni(this) 
    this:array:=array(256)
    this:ecount:=0
    return this

****************************************************************************
static function _array_add(this,x)
   if( len(this:array)<=this:ecount )
       asize(this:array,len(this:array)+1024)
   end
   this:array[++this:ecount]:=x
   return x

****************************************************************************
static function _array_resize(this)
   return asize(this:array,this:ecount)
 
****************************************************************************
#endif
