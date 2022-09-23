
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

static clid_error:=errorRegister()

****************************************************************************
function errorClass() 
    return clid_error

****************************************************************************
static function errorRegister() 
local clid:=classRegister("error",objectClass()) //osztalynev,parentID

    classMethod(clid,"initialize",{|this|errorIni(this)})
    classAttrib(clid,"args")
    classAttrib(clid,"candefault")
    classAttrib(clid,"canretry")   
    classAttrib(clid,"cansubstitute")
    classAttrib(clid,"cargo")
    classAttrib(clid,"description")
    classAttrib(clid,"filename")  
    classAttrib(clid,"gencode")     
    classAttrib(clid,"operation") 
    classAttrib(clid,"oscode")    
    classAttrib(clid,"severity")
    classAttrib(clid,"subcode")     
    classAttrib(clid,"subsystem")
    classAttrib(clid,"tries")    

    return clid


****************************************************************************
function errorNew()  
local clid:=errorClass()
    return objectNew(clid):initialize


****************************************************************************
function errorIni(this) 

    //pelda arra, 
    //hogyan lehet inicializalni a baseclass-okat,
    //a konkret esetben erre nincs szukseg,
    //ha azonban kesobb az objectClass-ba valami 
    //inicializalando dolog kerul, akkor igen

    objectIni(this)

    this:candefault:=.f.
    this:canretry:=.f.
    this:cansubstitute:=.f.
    this:description:=""
    this:filename:=""
    this:operation:=""
    this:subsystem:=""
    this:gencode:=0
    this:oscode:=0
    this:severity:=0
    this:subcode:=0
    this:tries:=0

    return this


****************************************************************************
