
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

//  error ---> err1 ---> err2
//                  ---> err3


static clid_err1:=err1Register()
static clid_err2:=err2Register()
static clid_err3:=err3Register()


****************************************************************************
function err1Class()
    return clid_err1

static function err1Register()
local clid:=classRegister("err1",{errorClass()})
    classMethod(clid,"initialize",{|this|err1Ini(this)})
    return clid

function err1New()
local clid:=err1Class()
    return objectNew(clid):initialize()

function err1Ini(this)
    errorIni(this)
    return this
    

****************************************************************************
function err2Class()
    return clid_err2

static function err2Register()
local clid:=classRegister("err2",{err1Class()})
    classMethod(clid,"initialize",{|this|err2Ini(this)})
    return clid

function err2New()
local clid:=err2Class()
    return objectNew(clid):initialize()

function err2Ini(this)
    err1Ini(this)
    return this
    

****************************************************************************
function err3Class()
    return clid_err3

static function err3Register()
local clid:=classRegister("err3",{err1Class()})
    classMethod(clid,"initialize",{|this|err3Ini(this)})
    return clid

function err3New()
local clid:=err3Class()
    return objectNew(clid):initialize()

function err3Ini(this)
    err1Ini(this)
    return this
    

****************************************************************************
