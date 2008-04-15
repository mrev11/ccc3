
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

function gtk.item_factory.register_callbacks(item_factory,entries)

local i,blk,path,wdg,err

    for i:=1 to len(entries)
        blk:=entries[i][3]
        if( blk!=NIL )
            path:=strtran(entries[i][1],"_","")
            wdg:=gtk.item_factory.get_widget(item_factory,path)
            if( empty(wdg) )
                err:=errorNew()
                err:operation:="gtk.item_factory.get_widget"
                err:description:="widget not found"
                err:args:={path}
                break(err)
            end
            gtk.gobject.signal_connect(wdg,"activate",blk)
        end
    next

    return NIL

    