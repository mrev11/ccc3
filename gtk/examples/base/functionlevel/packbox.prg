
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
static function make_box(homogeneous,spacing,expand,fill,padding ) 

// Make a new hbox filled with button-labels. Arguments for the 
// variables we're interested are passed in to this function. 
// We do not show the box, but do show everything inside. 

local box
local button
local padstr
    
    box := gtk.hbox.new(homogeneous,spacing)
    
    // Create a series of buttons with the appropriate settings 
    button:=gtk.button.new_with_label("gtk.box.pack")
    gtk.box.pack_start(box, button, expand, fill, padding)
    gtk.widget.show (button)
    
    button:=gtk.button.new_with_label("(box,")
    gtk.box.pack_start(box,button,expand,fill,padding)
    gtk.widget.show (button)
    
    button:=gtk.button.new_with_label("button,")
    gtk.box.pack_start(box,button,expand,fill,padding)
    gtk.widget.show (button)
    
    //Create a button with the label depending on the value of expand.
    if( expand == TRUE )
        button:=gtk.button.new_with_label("TRUE,")
    else
        button:=gtk.button.new_with_label("FALSE,")
    end
    
    gtk.box.pack_start(box,button,expand,fill,padding)
    gtk.widget.show (button)
    
    button:=gtk.button.new_with_label(if(fill,"TRUE,","FALSE,")) 
    gtk.box.pack_start(box, button, expand, fill, padding)
    gtk.widget.show (button)
    
    padstr:=alltrim(str(padding))+");"
    
    button:=gtk.button.new_with_label(padstr)
    gtk.box.pack_start(box, button, expand, fill, padding)
    gtk.widget.show (button)
    
    return box

******************************************************************************
function main(arg)

local window, button, box1, box2
local separator, label, quitbox
local xalign, yalign
local which
    
    gtk.init()
    
    if( arg==NIL .or. !("."+arg+"."$".1.2.3.") ) 
        ? "Usage: packbox num, where num is 1, 2, or 3."
        errorlevel(1)
        quit
    end
    
    which:=val(arg)

    window := gtk.window.new(GTK_WINDOW_TOPLEVEL)

    //You should always remember to connect 
    //the delete_event signal to the main window. 

    gtk.gobject.signal_connect(window,"delete_event",{||gtk.main_quit(),FALSE})
    gtk.container.set_border_width(window,10)
    
    //We create a vertical box (vbox) to pack the horizontal boxes into.
    //This allows us to stack the horizontal boxes filled with buttons one
    //on top of the other in this vbox.

    box1:=gtk.vbox.new(FALSE,0)

    do case // which example to show
    case which==1

        label:=gtk.label.new("gtk.hbox.new (FALSE, 0)")
        /* Align the label to the left side.  We'll discuss this function and 
         * others in the section on Widget Attributes. */
        ? gtk.misc.get_alignment(label,@xalign,@yalign),xalign,yalign
        gtk.misc.set_alignment(label,0,0)
        ? gtk.misc.get_alignment(label)

        /* Pack the label into the vertical box (vbox box1).  Remember that 
         * widgets added to a vbox will be packed one on top of the other in
         * order. */
        gtk.box.pack_start(box1, label, FALSE, FALSE, 0)
        gtk.widget.show (label)
        
        /* Call our make box function  
         * homogeneous = FALSE, spacing = 0,
         * expand = FALSE, fill = FALSE, padding = 0 */
        box2 := make_box (FALSE, 0, FALSE, FALSE, 0)
        gtk.box.pack_start(box1, box2, FALSE, FALSE, 0)
        gtk.widget.show (box2)

        /* Call our make box function 
         * homogeneous = FALSE, spacing = 0,
         * expand = TRUE, fill = FALSE, padding = 0 */
        box2 := make_box(FALSE, 0, TRUE, FALSE, 0)
        gtk.box.pack_start(box1, box2, FALSE, FALSE, 0)
        gtk.widget.show(box2)
        
        /* Call our make box function 
         * homogeneous = FALSE, spacing = 0,
         * expand = TRUE, fill = TRUE, padding = 0 */
        box2 := make_box (FALSE, 0, TRUE, TRUE, 0)
        gtk.box.pack_start (box1, box2, FALSE, FALSE, 0)
        gtk.widget.show (box2)
        

        /* Creates a separator, we'll learn more about these later, 
         * but they are quite simple. */
        separator := gtk.hseparator.new()
        /* Pack the separator into the vbox. Remember each of these
         * widgets is being packed into a vbox, so they'll be stacked
         * vertically. */
        gtk.box.pack_start(box1, separator, FALSE, TRUE, 5)
        gtk.widget.show(separator)

        
        /* Create another new label, and show it. */
        label := gtk.label.new ("gtk.hbox.new (TRUE, 0)")
        gtk.misc.set_alignment (label, 0, 0)
        gtk.box.pack_start (box1, label, FALSE, FALSE, 0)
        gtk.widget.show (label)
        
        /* Args are: homogeneous, spacing, expand, fill, padding */
        box2 := make_box (TRUE, 0, TRUE, FALSE, 0)
        gtk.box.pack_start (box1, box2, FALSE, FALSE, 0)
        gtk.widget.show (box2)
        
        /* Args are: homogeneous, spacing, expand, fill, padding */
        box2 := make_box (TRUE, 0, TRUE, TRUE, 0)
        gtk.box.pack_start (box1, box2, FALSE, FALSE, 0)
        gtk.widget.show (box2)
        
        /* Another new separator. */
        separator := gtk.hseparator.new ()
        /* The last 3 arguments to gtk.box.pack_start are:
         * expand, fill, padding. */
        gtk.box.pack_start (box1, separator, FALSE, TRUE, 5)
        gtk.widget.show (separator)

        
    case which==2

        /* Create a new label, remember box1 is a vbox as created 
         * near the beginning of main() */
        label := gtk.label.new ("gtk.hbox.new (FALSE, 10)")
        gtk.misc.set_alignment (label, 0, 0)
        gtk.box.pack_start (box1, label, FALSE, FALSE, 0)
        gtk.widget.show (label)
        
        /* Args are: homogeneous, spacing, expand, fill, padding */
        box2 := make_box (FALSE, 10, TRUE, FALSE, 0)
        gtk.box.pack_start (box1, box2, FALSE, FALSE, 0)
        gtk.widget.show (box2)
        
        /* Args are: homogeneous, spacing, expand, fill, padding */
        box2 := make_box (FALSE, 10, TRUE, TRUE, 0)
        gtk.box.pack_start (box1, box2, FALSE, FALSE, 0)
        gtk.widget.show (box2)
        
        separator := gtk.hseparator.new ()
        /* The last 3 arguments to gtk.box.pack_start are:
         * expand, fill, padding. */
        gtk.box.pack_start (box1, separator, FALSE, TRUE, 5)
        gtk.widget.show (separator)
        
        label := gtk.label.new ("gtk.hbox.new (FALSE, 0)")
        gtk.misc.set_alignment (label, 0, 0)
        gtk.box.pack_start (box1, label, FALSE, FALSE, 0)
        gtk.widget.show (label)
        
        /* Args are: homogeneous, spacing, expand, fill, padding */
        box2 := make_box (FALSE, 0, TRUE, FALSE, 10)
        gtk.box.pack_start (box1, box2, FALSE, FALSE, 0)
        gtk.widget.show (box2)
        
        /* Args are: homogeneous, spacing, expand, fill, padding */
        box2 := make_box (FALSE, 0, TRUE, TRUE, 10)
        gtk.box.pack_start (box1, box2, FALSE, FALSE, 0)
        gtk.widget.show (box2)
        
        separator := gtk.hseparator.new ()
        /* The last 3 arguments to gtk.box.pack_start are: expand, fill, padding. */
        gtk.box.pack_start (box1, separator, FALSE, TRUE, 5)
        gtk.widget.show (separator)

    
    case which==3

        /* This demonstrates the ability to use gtk.box.pack_end() to
         * right justify widgets. First, we create a new box as before. */
        box2 := make_box (FALSE, 0, FALSE, FALSE, 0)

        /* Create the label that will be put at the end. */
        label := gtk.label.new ("end")
        /* Pack it using gtk.box.pack_end(), so it is put on the right
         * side of the hbox created in the make_box() call. */
        gtk.box.pack_end (box2, label, FALSE, FALSE, 0)
        gtk.widget.show(label)
        

        /* Create the label that will be put at the end. */
        label := gtk.label.new ("END")
        /* Pack it using gtk.box.pack_end(), so it is put on the right
         * side of the hbox created in the make_box() call. */
        gtk.box.pack_end (box2, label, FALSE, FALSE, 0)
        gtk.widget.show(label)
        

        /* Pack box2 into box1 (the vbox remember ? :) */
        gtk.box.pack_start (box1, box2, FALSE, FALSE, 0)
        gtk.widget.show (box2)
        
        /* A separator for the bottom. */
        separator := gtk.hseparator.new()
        /* This explicitly sets the separator to 400 pixels wide by 5 pixels
         * high. This is so the hbox we created will also be 400 pixels wide,
         * and the "end" label will be separated from the other labels in the
         * hbox. Otherwise, all the widgets in the hbox would be packed as
         * close together as possible. */
        gtk.widget.set_size_request(separator,400,5)
        /* pack the separator into the vbox (box1) created near the start 
         * of main() */
        gtk.box.pack_start(box1, separator, FALSE, TRUE, 5)
        gtk.widget.show (separator)    

    end //case

    
    //Create another new hbox. 
    //Remember we can use as many as we need!
    quitbox:=gtk.hbox.new(FALSE,0)
    
    //Our quit button.
    button:=gtk.button.new_with_label("Quit")
    gtk.gobject.signal_connect(button,"clicked",{||gtk.main_quit(),FALSE})
    gtk.box.pack_start(quitbox,button,TRUE,FALSE, 0) //expand,fill,padding
    gtk.box.pack_start(box1,quitbox,FALSE,FALSE,0)
    
    gtk.container.add(window, box1)
    gtk.widget.show (button)
    gtk.widget.show (quitbox)
    gtk.widget.show (box1)

    //Showing the window last so everything pops up at once.
    gtk.window.set_title(window,"packbox "+arg)
    gtk.widget.show (window)
    
    gtk.main()

    //Control returns here when gtk.main_quit() is called, 
    //but not when exit() is used.

******************************************************************************
