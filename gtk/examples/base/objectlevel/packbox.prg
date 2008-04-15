
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

#define FALSE .f.
#define TRUE  .t.

******************************************************************************
function main(arg)

local window, button, box1, box2
local separator, label, quitbox
local xalign, yalign
local which
    
    gtk.init()
    
    if( arg==NIL )
        arg:="1"
    end
    
    which:=val(arg)

    window:=gtkwindowNew()
    window:signal_connect("delete_event",{||gtk.main_quit(),FALSE})
    window:set_border_width(10)
    
    //We create a vertical box (vbox) to pack the horizontal boxes into.
    //This allows us to stack the horizontal boxes filled with buttons one
    //on top of the other in this vbox.

    box1:=gtkvboxNew(FALSE,0)

    do case // which example to show
    case which==1

        label:=gtklabelNew("gtk.hbox.new(FALSE, 0)")
        /* Align the label to the left side.  We'll discuss this function and 
         * others in the section on Widget Attributes. */

        label:set_alignment(0.2,0.3)
        ? label:get_alignment(@xalign,@yalign),xalign,yalign
        ? gtk.misc.get_alignment(label:gobject,@xalign,@yalign),xalign,yalign
        //Megj: az objektum interfész nem viszi át a refeket.

        label:set_alignment(0,0)
        ? label:get_alignment()

        /* Pack the label into the vertical box (vbox box1).  Remember that 
         * widgets added to a vbox will be packed one on top of the other in
         * order. */
        box1:pack_start(label,FALSE,FALSE,0)
        
        /* Call our make box function  
         * homogeneous = FALSE, spacing = 0,
         * expand = FALSE, fill = FALSE, padding = 0 */
        box2:=make_box(FALSE,0,FALSE,FALSE,0)
        box1:pack_start(box2,FALSE,FALSE,0)

        /* Call our make box function 
         * homogeneous = FALSE, spacing = 0,
         * expand = TRUE, fill = FALSE, padding = 0 */
        box2:=make_box(FALSE,0,TRUE,FALSE,0)
        box1:pack_start(box2,FALSE,FALSE,0)
        
        /* Call our make box function 
         * homogeneous = FALSE, spacing = 0,
         * expand = TRUE, fill = TRUE, padding = 0 */
        box2:=make_box(FALSE,0,TRUE,TRUE,0)
        box1:pack_start(box2,FALSE,FALSE,0)

        /* Creates a separator, we'll learn more about these later, 
         * but they are quite simple. */
        separator:=gtkhseparatorNew()
        /* Pack the separator into the vbox. Remember each of these
         * widgets is being packed into a vbox, so they'll be stacked
         * vertically. */
        box1:pack_start(separator,FALSE,TRUE,5)
        
        /* Create another new label, and show it. */
        label:=gtklabelNew("gtk.hbox.new (TRUE, 0)")
        label:set_alignment(0,0)
        box1:pack_start(label,FALSE,FALSE,0)
        
        /* Args are: homogeneous, spacing, expand, fill, padding */
        box2:=make_box(TRUE,0,TRUE,FALSE,0)
        box1:pack_start(box2,FALSE,FALSE,0)
        
        /* Args are: homogeneous, spacing, expand, fill, padding */
        box2:=make_box(TRUE,0,TRUE,TRUE,0)
        box1:pack_start(box2,FALSE,FALSE,0)
        
        separator:=gtkhseparatorNew()
        /* The last 3 arguments to gtk.box.pack_start are:
         * expand, fill, padding. */
        box1:pack_start(separator,FALSE,TRUE,5)

        
    case which==2

        /* Create a new label, remember box1 is a vbox as created 
         * near the beginning of main() */
        label:=gtklabelNew("gtk.hbox.new (FALSE, 10)")
        label:set_alignment(0,0)
        box1:pack_start(label,FALSE,FALSE,0)
        
        /* Args are: homogeneous, spacing, expand, fill, padding */
        box2:=make_box(FALSE,10,TRUE,FALSE,0)
        box1:pack_start(box2,FALSE,FALSE,0)
        
        /* Args are: homogeneous, spacing, expand, fill, padding */
        box2:=make_box(FALSE,10,TRUE,TRUE,0)
        box1:pack_start(box2,FALSE,FALSE,0)
        
        separator:=gtkhseparatorNew()
        /* The last 3 arguments to gtk.box.pack_start are:
         * expand, fill, padding. */
        box1:pack_start(separator,FALSE,TRUE,5)
        
        label:=gtklabelNew("gtk.hbox.new (FALSE, 0)")
        label:set_alignment(0,0)
        box1:pack_start(label,FALSE,FALSE,0)
        
        /* Args are: homogeneous, spacing, expand, fill, padding */
        box2:=make_box(FALSE,0,TRUE,FALSE,10)
        box1:pack_start(box2,FALSE,FALSE,0)
        
        /* Args are: homogeneous, spacing, expand, fill, padding */
        box2:=make_box(FALSE,0,TRUE,TRUE,10)
        box1:pack_start(box2,FALSE,FALSE,0)
        
        separator:=gtkhseparatorNew()
        /* The last 3 arguments to gtk.box.pack_start are: expand, fill, padding. */
        box1:pack_start(separator, FALSE, TRUE, 5)

    
    case which==3

        /* This demonstrates the ability to use gtk.box.pack_end() to
         * right justify widgets. First, we create a new box as before. */
        box2 := make_box (FALSE, 0, FALSE, FALSE, 0)

        /* Create the label that will be put at the end. */
        label := gtklabelNew ("end")
        /* Pack it using gtk.box.pack_end(), so it is put on the right
         * side of the hbox created in the make_box() call. */
        box2:pack_end (label, FALSE, FALSE, 0)

        /* Create the label that will be put at the end. */
        label := gtklabelNew ("END")
        /* Pack it using gtk.box.pack_end(), so it is put on the right
         * side of the hbox created in the make_box() call. */
        box2:pack_end ( label, FALSE, FALSE, 0)

        /* Pack box2 into box1 (the vbox remember ? :) */
        box1:pack_start (box2, FALSE, FALSE, 0)
        
        /* A separator for the bottom. */
        separator := gtkhseparatorNew()
        /* This explicitly sets the separator to 400 pixels wide by 5 pixels
         * high. This is so the hbox we created will also be 400 pixels wide,
         * and the "end" label will be separated from the other labels in the
         * hbox. Otherwise, all the widgets in the hbox would be packed as
         * close together as possible. */
        separator:set_size_request(400,5)
        /* pack the separator into the vbox (box1) created near the start 
         * of main() */
        box1:pack_start( separator, FALSE, TRUE, 5)

    end //case

    
    //Create another new hbox. 
    //Remember we can use as many as we need!
    quitbox:=gtkhboxNew(FALSE,0)
    
    //Our quit button.
    button:=gtkbuttonNew("Quit")
    button:signal_connect("clicked",{||gtk.main_quit(),FALSE})
    quitbox:pack_start(button,TRUE,FALSE, 0) //expand,fill,padding
    box1:pack_start(quitbox,FALSE,FALSE,0)
    
    window:add(box1)
    //Showing the window last so everything pops up at once.
    window:set_title("packbox "+arg)
    window:show_all
    
    gtk.main()
    ?

******************************************************************************
static function make_box(homogeneous,spacing,expand,fill,padding ) 

// Make a new hbox filled with button-labels. Arguments for the 
// variables we're interested are passed in to this function. 

local box, button
    
    box:=gtkhboxNew(homogeneous,spacing)
    
    // Create a series of buttons with the appropriate settings 
    button:=gtkbuttonNew("gtk.box.pack")
    box:pack_start(button,expand,fill,padding)
    
    button:=gtkbuttonNew("(box,")
    box:pack_start(button,expand,fill,padding)
    
    button:=gtkbuttonNew("button,")
    box:pack_start(button,expand,fill,padding)
    
    //Create a button with the label depending on the value of expand.
    if( expand == TRUE )
        button:=gtkbuttonNew("TRUE,")
    else
        button:=gtkbuttonNew("FALSE,")
    end
    box:pack_start(button,expand,fill,padding)
    
    button:=gtkbuttonNew(if(fill,"TRUE,","FALSE,")) 
    box:pack_start(button,expand,fill,padding)
    
    button:=gtkbuttonNew(alltrim(str(padding))+");")
    box:pack_start(button,expand,fill,padding)
    
    return box

******************************************************************************
