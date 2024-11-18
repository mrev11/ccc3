
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

//tdc2tabobj 1.2

class tabobj.proba(tabobj)
    method  proba                    {||}
    method  length                   {||}
    method  dbmchr                   {||}
    method  dbmbin                   {||}
    method  initialize
    method  __stamp__
    method  __mutex__

static function tabobj.proba.initialize(this,alias:='proba')
    this:(tabobj)initialize(alias)
    tabAddColumn(this,{"proba                   ","C",   8, 0})
    tabAddColumn(this,{"length                  ","N",   6, 0})
    tabAddColumn(this,{"dbmchr                  ","C",  10, 1})
    tabAddColumn(this,{"dbmbin                  ","X",  10, 2})
    tabAddIndex(this,{"proba","proba",{"proba"}})
    tabKeepDeleted(this,0)
    return this

static function tabobj.proba.__stamp__(this,x) 
static stamp
    if( x!=NIL )
        stamp:=x
    end
    return stamp

static function tabobj.proba.__mutex__()
static mutex:=thread_mutex_init()
    return mutex
