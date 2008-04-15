
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

******************************************************************************
class gobject(gstruct) new: //nem kell automatikus konstruktor
    method signal_connect {|self,name,blk|gtk.gobject.signal_connect(self,name,blk,self)}
    method signal_connect_after {|self,name,blk|gtk.gobject.signal_connect_after(self,name,blk,self)}
    method signal_handler_disconnect {|self,id|gtk.gobject.signal_handler_disconnect(self,id)}
    method signal_handler_block {|self,id|gtk.gobject.signal_handler_block(self,id)}
    method signal_handler_unblock {|self,id|gtk.gobject.signal_handler_unblock(self,id)}
    method ref {|self|gtk.gobject.ref(self)}
    method unref {|self|gtk.gobject.unref(self)}
    method type_name {|self|gtk.gobject.type_name(self)}
    method cast {|self,clid,o|o:=objectNew(clid),o:gobject:=self:gobject,o}
    method set_property {|self,prop,value|gtk.gobject.set_property(self,prop,value)}
    method get_property {|self,prop|gtk.gobject.get_property(self,prop)}

******************************************************************************
function gobjectNew(clid,gobject)
local o:=objectNew(clid)
    o:gobject:=gobject
    return o

******************************************************************************

    