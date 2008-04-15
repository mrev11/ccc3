
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

#define OK(fs)      gtk.file_selection.get_ok_button(fs)
#define CANCEL(fs)  gtk.file_selection.get_cancel_button(fs)

******************************************************************************
function main()
local filew
    
    gtk.init()
    
    filew:=gtk.file_selection.new ("File selection")

    gtk.gobject.signal_connect(filew,"destroy",{||gtk.main_quit()})
    gtk.gobject.signal_connect(OK(filew),"clicked",{||file_ok_sel(filew)})
    gtk.gobject.signal_connect(CANCEL(filew),"clicked",{||gtk.widget.destroy(filew)})
    gtk.file_selection.set_filename(filew,"penguin.png")
    gtk.file_selection.set_select_multiple(filew,.t.)
    gtk.widget.show(filew)

    gtk.main()
    ?

******************************************************************************
static function file_ok_sel(fs)
    //? gtk.file_selection.get_filename(fs)
    ? gtk.file_selection.get_selections(fs)


******************************************************************************
    