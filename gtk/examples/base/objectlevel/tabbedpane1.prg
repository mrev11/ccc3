
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

#define  GTK_POS_LEFT       0
#define  GTK_POS_RIGHT      1
#define  GTK_POS_TOP        2
#define  GTK_POS_BOTTOM     3


function main()

local window
local notebook
local i,frame
    
    gtk.init ()
       
    window:=gtkwindowNew()
    window:signal_connect("destroy",{||gtk.main_quit()})
    window:set_size_request(600,500)
    window:set_title("Tabbed Window")
    window:set_border_width(20)

    notebook:=gtknotebookNew()  //ez a tabbed pane!
    window:add(notebook)
    notebook:set_tab_pos(GTK_POS_TOP ) //fulek fenn

    for i:=1 to 4
        frame:=gtkframeNew("Append Frame "+str(i)::alltrim)
        frame:set_border_width(10)
        frame:set_size_request(100,90)
        frame:add( gtklabelNew("APPEND FRAME "+str(i)::alltrim) )
        notebook:append_page(frame, gtklabelNew("Page "+str(i)::alltrim))
    next

    notebook:append_page(gtkcalendarNew(),gtk.label.new("Calendar"))

    window:show_all
    gtk.main()


