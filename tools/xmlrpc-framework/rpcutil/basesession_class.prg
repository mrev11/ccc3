
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

*****************************************************************************
#ifdef NOT_DEFINED
  Objektum, 
  amiben egy XMLRPC szerver tarolhatja egy session alapadatait.
  Tarolva: sid, szervernev, utolso request ideje, felhasznalo adatai.
#endif

*****************************************************************************
class basesession(object)  new: //absztrakt
    method  initialize
    attrib  sid
    attrib  srvname
    attrib  seconds
    attrib  userid
    attrib  username
    attrib  usertype
    attrib  groupid
    method  access          {||NIL}

****************************************************************************
static function basesession.initialize(this,sid,srv) 
local perm,i
    this:(object)initialize
    this:sid:=sid
    this:srvname:=srv
    this:seconds:=0
    this:userid:=wrapper():call("session.userid",sid)
    this:username:=wrapper():call("session.username",sid)
    this:usertype:=wrapper():call("session.usertype",sid)
    this:groupid:=wrapper():call("session.groupid",sid)
    return this

*****************************************************************************
