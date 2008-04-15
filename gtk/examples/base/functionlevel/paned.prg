
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

#include "gtk.ch"
   
******************************************************************************
function main()

local window,vpaned

    gtk.init()
   
    window:=gtk.window.new()
    gtk.window.set_title(window,"Paned Windows")
    gtk.gobject.signal_connect(window,"destroy",{||gtk.main_quit()})
    gtk.container.set_border_width(window,10)
    gtk.widget.set_size_request(window,450,400)

    vpaned:=gtk.vpaned.new()
    gtk.container.add(window,vpaned)
    gtk.paned.add1(vpaned,create_list())
    gtk.paned.add2(vpaned,create_text())
    gtk.widget.show_all(window)

    gtk.main()

******************************************************************************
static function create_list()

local scrolled_window
local tree_view
local model             //GtkListStore
local iter              //GtkTreeIter
local cell              //GtkCellRenderer
local column            //GtkTreeViewColumn
local msg1, msg2, i
   
    scrolled_window:=gtk.scrolled_window.new()
    gtk.scrolled_window.set_policy(scrolled_window,1,1)
    tree_view:=gtk.tree_view.new()
    gtk.scrolled_window.add_with_viewport(scrolled_window,tree_view)

    model:=gtk.list_store.new("SS") //2 oszlop
    gtk.tree_view.set_model(tree_view,model)

    iter:=gtk.tree_iter.new() //fel kell szabadítani!
    for i:=1 to 16
        gtk.list_store.append(model,iter)
        msg1:="XXX-Message #"+alltrim(str(i))
        msg2:=if(i%3==0,"","YYY-Message #"+alltrim(str(i)))
        //msg2:=i%3==0
        //msg2:=i+0.1*i
        gtk.list_store.set(model,iter,{msg1,msg2})
    next
    gtk.tree_iter.free(iter)

    cell:=gtk.cell_renderer_text.new()
    column:=gtk.tree_view_column.new()
    gtk.tree_view.append_column(tree_view,column)
    gtk.tree_view_column.set_title(column,"XXX-Message")
    gtk.tree_view_column.pack_start(column,cell,.t.)
    gtk.tree_view_column.add_attribute(column,cell,"text",0)
    gtk.tree_view_column.set_resizable(column,.t.)
    gtk.tree_view_column.set_reorderable(column,.t.)

    //cell:=gtk.cell_renderer_text.new()
    //column:=gtk.tree_view_column.new()
    column:=gtk.tree_view_column.new_with_attributes("Title",cell)
    gtk.tree_view.append_column(tree_view,column)
    //gtk.tree_view_column.set_title(column,"YYY-Message")
    //gtk.tree_view_column.pack_start(column,cell,.t.)
    gtk.tree_view_column.add_attribute(column,cell,"text",1)
    gtk.tree_view_column.set_reorderable(column,.t.)


    return scrolled_window

******************************************************************************
static function create_text()

local txt:=<<TEXT>>0
1 From: pathfinder@nasa.gov
2 To: mom@nasa.gov
3 Subject: Made it!
4yyyyyyyyyyyyyyyyyyy
5 We just got in this morning. The weather has been
6 great - clear but cold, and there are lots of fun sights.
7 Sojourner says hi. See you soon.
8 -Path
<<TEXT>>

local ins:="<<XXX>>"

local view:=gtk.text_view.new()
local buffer:=gtk.text_view.get_buffer(view)
local scrolled_window:=gtk.scrolled_window.new()
local text_iter

    gtk.scrolled_window.set_policy(scrolled_window,1,1)
    gtk.container.add(scrolled_window,view)

#define WITH_TEXT_ITER
#ifdef  WITH_TEXT_ITER
    text_iter:=gtk.text_iter.new() //nincs rá referenciaszámlálás!
    gtk.text_buffer.get_iter_at_offset(buffer,text_iter,0)
    gtk.text_buffer.insert(buffer,text_iter,txt,-1) //length==-1 (whole text)

    //karakterpozícióra pozícionál
    //gtk.text_buffer.get_iter_at_offset(buffer,text_iter,20)

    //sorra pozícionál
    //gtk.text_buffer.get_iter_at_line(buffer,text_iter,5)

    //megadott soron belül karakterre pozicionál
    gtk.text_buffer.get_iter_at_line_offset(buffer,text_iter,4,5)

    gtk.text_buffer.insert(buffer,text_iter,ins)
    gtk.text_iter.free(text_iter) //fel kell szabadítani

#else
    gtk.text_buffer.set_text(buffer,txt,-1)
#endif

    return scrolled_window

******************************************************************************
