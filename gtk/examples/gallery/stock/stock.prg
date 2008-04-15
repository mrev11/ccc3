
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

function main()

local stock_list,n
local item,icon_set,sizes
local id,label,modif,keyval,domain


    gtk.init()

    item:=gtk.stock_item.new()
    stock_list:=gtk.stock.list_ids()


    asort(stock_list)

    for n:=1 to len(stock_list)
        if(gtk.stock.lookup(stock_list[n],item))
            id      :=gtk.stock_item.get_stock_id(item)
            label   :=gtk.stock_item.get_label(item)
            modif   :=gtk.stock_item.get_modifier(item)
            keyval  :=gtk.stock_item.get_keyval(item)
            domain  :=gtk.stock_item.get_translation_domain(item)
               
            icon_set:=gtk.icon_factory.lookup_default(id)
            sizes:=gtk.icon_set.get_sizes(icon_set)
            //? stock_list[n]
        else
            ? stock_list[n]
        end
    next
    ?

    gtk.stock_item.free(item)
    quit
    

    