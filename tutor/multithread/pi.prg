
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

static pi:=0
static pi_lock:=thread_mutex_init()

static intervals:=100000
static thcount:=10

******************************************************************************
function main()

local blk:={|ip|process(ip)}
local th:={},n

    for n:=1 to thcount
        aadd(th,thread_create(blk,n))
    next

    for n:=1 to len(th)
        thread_join( th[n] )
    next

    set printer to log additive
    set printer on
 
    ? "Estimation of pi is:", str(pi)
    ?
    
    return NIL
 

******************************************************************************
function process(iproc)  //iproc==1,2,...

local localsum:=0
local width:=1/intervals 
local i, x

    ? thread_self()

    for i:=iproc to intervals step thcount
        x:=(i-0.5)*width
        localsum+=4/(1+x*x)
    next
    localsum*=width

    thread_mutex_lock(pi_lock)
    pi+=localsum
    thread_mutex_unlock(pi_lock)

    return NIL

 
******************************************************************************

