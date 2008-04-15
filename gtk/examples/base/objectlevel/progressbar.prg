
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

#ifdef NOT_DEFINED
  Hogyan lehet használni a gyakorlatban?

  Ha a feldolgozás közvetlenül hívogatja a pb:set_fraction()-t,
  akkor nem halad progressbar, hanem a cb_ok visszatérése után áll 
  rá az utolsó értékre. Ezért külön lökdösni kell a main loopot:

    while( gtk_events_pending() )
        gtk_main_iteration();

  Ha a (timeout-os) cb_ok1-ban valamit dolgozni kezd a program,
  akkor a timer mindaddig nem hívódik meg, amíg a cb_ok1-ból 
  vissza nem tér a vezérlés, azaz nem halad a progressbar.
  
  Meg lehet tenni, hogy a cb_ok-ból azonnal visszatérünk,
  és a feldolgozást kis szakaszokban a cb_timer-ból csináljuk,
  akkor a feldolgozás is megy és a progressbar is. Csakhogy
  nem a progressbar az élet értelme.
  
  Ha a progressbar haladása közben leöljük az ablakot
  (akár cb_cancel, akár ALT-F4), akkor a program végtelen 
  ciklusban marad. Elég szarnak látszik az egész progressbar ügy.
#endif


#include "gtk.ch"

#define FALSE .f.
#define TRUE  .t.

*******************************************************************************
function main()

local window, vbox, hbox
local progbar, button_cancel, button_ok

    gtk.init()

    window:=gtkwindowNew()
    window:set_size_request(400,-1)
    window:set_title("GTK ProgressBar Demó")
    window:signal_connect("destroy",{||gtk.main_quit()})

    vbox:=gtkvboxNew(FALSE,0)
    window:add(vbox)

    progbar:=gtkprogressbarNew()
    progbar:set_size_request(-1,30)
    vbox:add(progbar)

    hbox:=gtkhboxNew(FALSE, 0)
    vbox:add(hbox)
    
    button_cancel:=gtkbuttonNew_from_stock("gtk-cancel")
    button_cancel:signal_connect("clicked",{|w|cb_cancel(w,window)})
    hbox:add(button_cancel)

    button_ok:=gtkbuttonNew_from_stock("gtk-ok")
    button_ok:signal_connect("clicked",{|w|cb_ok1(w,progbar)})
    hbox:add(button_ok)
                                  
    window:show_all()

    gtk.main()
    ?

*******************************************************************************
static function cb_cancel(w,win)
    ? "clicked", w:get_label
    win:destroy


*******************************************************************************
static function cb_ok(w,pb)

    ? "clicked", w:get_label

    if( pb:get_fraction==0 )
        pb:set_text("Türelem rózsát terem")
        while( pb:get_fraction+0.01<=1 )
            pb:set_fraction(pb:get_fraction+0.01) 
            gtk.main_stabilize() //lökdösni kell
            sleep(20)
        end

        pb:set_fraction(0) 
        pb:set_text("")
    end
  

*******************************************************************************
static function cb_ok1(w,pb)

    ? "clicked", w:get_label

    if( pb:get_fraction==0 )
        //beindít
        pb:set_fraction(0.01)
        pb:set_text("Türelem rózsát terem")
        g_timeout_add(100,{||cb_timer(pb)})

        //A timer mindaddig hívogatja a kódblokkot, amíg az .t.-t ad.
        //A kódblokkot nem szabad közvetlenül hívni, mert elromolhat
        //a timer automatikus kezelése.
    else
        //leállít
        pb:set_fraction(0) 
    end
    
    //processing

*******************************************************************************
static function cb_timer(pb)
local fraction:=pb:get_fraction

    if( fraction==0 )
        pb:set_text("")
        return .f. //timer leáll
    end

    fraction+=0.02

    if( fraction>1 )
        pb:set_fraction(0)
        pb:set_text("")
        return .f. //timer leáll
    end

    pb:set_fraction(fraction)
    return .t.

******************************************************************************* 

