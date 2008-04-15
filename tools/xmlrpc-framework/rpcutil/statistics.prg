
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

//xmlrpcclient statisztikát számoló változata

*****************************************************************************
class xmlrpcclientStatistics(xmlrpcclient)
    method  initialize
    attrib  cnt
    attrib  x1
    attrib  x2
    method  call
    method  printstatistics

*****************************************************************************
function xmlrpcclientstatistics.initialize(this,ip,port) 
local qb:=quitblock()
    this:(xmlrpcclient)initialize(ip,port) 
    this:cnt:=0
    this:x1:=0
    this:x2:=0
    quitblock( {||this:printstatistics,eval(qb)} )
    return this

*****************************************************************************
static function xmlrpcclientstatistics.call(this,met,par)
local t0:=gettickcount(),t1,dt
local result:=this:(xmlrpcclient)call(met,par) 
    t1:=gettickcount()
    dt:=t1-t0
    this:x1+=dt
    this:x2+=(dt*dt)
    this:cnt++
    return result

*****************************************************************************
static function xmlrpcclientstatistics.printstatistics(this)

local e:=this:x1/this:cnt          //átlag
local d2:=this:x2/this:cnt-e**2    //szórásnégyzet

    set alternate to client_statistics additive
    set alternate on
    ? "PS:", argv(0), str(e,5,0), str(sqrt(d2),5,0)
    set alternate to
    set alternate off

*****************************************************************************

 