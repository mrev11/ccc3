
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

static globvar:="globvar"

*******************************************************************************
class adapter(object)
    method  initialize
    method  hopp
    attrib  error
    attrib  x

static function adapter.initialize(this)
    this:error:=errorNew()
    this:x:="adapter.x"
    return this

static function adapter.hopp(*)
    //? {"hopp",*}
    varstack()
    return "HOPP"


*******************************************************************************
class derived(object)
    method  initialize

    attrib  adapter
    attrib  x
    method  masik
    method  ugv         upper(globvar)   //=> {||upper(globvar)}


    method  hopp        :adapter:hopp
    method  desc        :adapter:error:description
    method  ax          :adapter:x
    method  dx          :x
    method  egyik       :masik


static function derived.initialize(this,adapter)
    this:(object)initialize
    this:adapter:=adapter
    this:x:="derived.x"
    return this

static function derived.masik(this,*)
    //? {"masik",*}
    varstack()
    return "MASIK"


*******************************************************************************
function main()

local a:=adapterNew()
local d:=derivedNew(a)

    ? d:hopp("a","bb","ccc","dddd","eeeee")
    ? d:egyik(11,22,33,44)

    ? d:ax
    ? d:dx
    d:ax:=upper(d:ax)
    d:dx:=upper(d:dx)
    ? d:ax
    ? d:dx
    
    a:error:description:="vanaki forrón"
    ? d:desc
    d:desc:=upper(d:desc)
    ? a:error:description
    
    ? d:ugv

    ?

*******************************************************************************
    