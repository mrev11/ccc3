
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


#include "gdk.ch"
#include "gtk.ch"

static selected_file


******************************************************************************
function main()

local window
local hbox
local vbox
local button
    
    gtk.init()

    window:=gtkwindowNew()
    window:set_title("File Chooser DEMO")
    window:set_default_size(600,200)
    window:signal_connect("destroy",{||quit()})
    window:set_border_width(50)
    window:set_resizable(.t.)
    window:set_position(GTK_WIN_POS_MOUSE)
    
    hbox:=gtkhboxNew(.f.,1)
    window:add(hbox)

    vbox:=gtkvboxNew(.f.,10)
    hbox:add(vbox)

    button:=gtkbuttonNew_with_mnemonic_from_stock("_Save","gtk-save") 
    button:signal_connect("clicked",{||cb_save(window)})
    vbox:pack_start(button)

    window:show_all
    gtk.main()
    ?


******************************************************************************
static function cb_save(window) //w=gtkbutton object
local fs,dlg
    selected_file:=NIL
    fs:=gtkfileselectionNew("File selection")
    fs:get_ok_button:signal_connect("clicked",{||selected_file:=fs:get_filename,fs:destroy})
    fs:get_cancel_button:signal_connect("clicked",{||fs:destroy})
    fs:set_filename("próba szerencse")
    fs:set_select_multiple(.f.)
    fs:set_position(GTK_WIN_POS_MOUSE)
    fs:run
    if( selected_file!=NIL .and. file(selected_file)  )
        dlg:=gtkmessagedialogNew(window,;
                GTK_DIALOG_MODAL,;
                GTK_MESSAGE_WARNING,;
                GTK_BUTTONS_YES_NO,;
                selected_file)
        dlg:set_title("File exists, do you want to replace it?")        
        dlg:signal_connect('response',{|w,r|if(r==GTK_RESPONSE_NO,selected_file:=NIL,NIL),dlg:destroy})
        dlg:set_position(GTK_WIN_POS_MOUSE)
        dlg:run
    end
    ? selected_file


******************************************************************************
static function gtkbuttonNew_with_mnemonic_from_stock(label_text,stock_id)
local button,box,label,image
    box:=gtkhboxNew(.f.,0)
    box:set_border_width(2)
    image:=gtkimageNew_from_stock(stock_id,GTK_ICON_SIZE_DIALOG)
    label:=gtklabelNew(label_text)
    label:set_use_underline(.t.)
    box:pack_start(image, .f., .f., 3)
    box:pack_start(label, .f., .f., 3)
    button:=gtkbuttonNew()
    button:add(box)
    return button


******************************************************************************
    