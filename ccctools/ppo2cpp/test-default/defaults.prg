
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

static var:="STATIC VARIABLE"
static flg:=.t.
static blk:={|x|lower(x)}
static err:=errorNew()

******************************************************************************
function main()
local x,y,z

    ? default1(@x,@y,@z,1,2,3)
    ? x,y,z

    ? default2("default-2"), default2()
    ? default3("default-3"), default3()
    ? default4("default-4"), default4()
    ? default5("default-5"), default5()
    ? default6("default-6"), default6()
    ? default7("default-7"), default7()
    ? default8({||"default-8"}), default8()
    ? default9("HOPP","default-9"), default9("HOPP")
    ? default10({"HOPP","KOPP"},"default-10"), default10({"HOPP","KOPP"})
    ? default11(err,"default-11"), default11(err)

    ? var
    ?

******************************************************************************
function default1(a,b:="b",c:="c",*)
    return {*}

function default2(a:={"A1","A2","A3"})
    return a

function default3( a:=time() )
    return a

function default4( a:=var )
    return a

function default5( a:=var:="AbCd" )
    return a

function default6(a:=if(flg,"T","F"))
    return a

function default7(a:=eval(blk,var))
    return a

function default8(blk:={||"HOPP"})
    return eval(blk)

function default9(x,y:=eval(blk,x))
//fordított sorrenddel x undefined 
    return y

function default10(x,y:=x[2])
//fordított sorrenddel x undefined 
    return y

function default11(x,y:=x:classname)
//fordított sorrenddel x undefined 
    return y
    
******************************************************************************

    