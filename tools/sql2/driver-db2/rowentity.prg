
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

namespace sql2.db2

****************************************************************************
class rowentity(object)  new: // nem kell new
    method  initialize
    attrib  __tableentity__
    attrib  __buffer__
    attrib  __memolist__
    method  show                {|t|t:__tableentity__:show(t)}
    method  showflags           {|t|t:__tableentity__:showflags(t)}
    method  insert              {|t|t:__tableentity__:insert(t)}
    method  update              {|t|t:__tableentity__:update(t)}
    method  delete              {|t|t:__tableentity__:delete(t)}
    method  find                {|t,lck|t:__tableentity__:find(t,lck)}
    method  getprimarykey       {|t|t:__tableentity__:getprimarykey(t)}
    method  setdirty            {|t,f|t:__tableentity__:setdirty(t,f)}
    method  setnull             {|t,f|t:__tableentity__:setnull(t,f)}
    method  tableentity         {|t|t:__tableentity__}

****************************************************************************
static function rowentity.initialize(this,t) 
    this:(object)initialize
    this:__tableentity__:=t
    this:__buffer__:=substr(t:__buffer__,1) //másolat!
    if( t:__memocount__!=NIL )
        this:__memolist__:=array(t:__memocount__)
    end
    return this

****************************************************************************
