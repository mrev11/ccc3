
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

#include "directry.ch"


****************************************************************************
function main()

local window
local combo
local comboentry
local button_cancel, button_ok
local progressbar
local d,n

    set date format "yyyy-mm-dd"

    gtk.init()
    
    window:=gladeloadgui("project9.glade")
    window:signal_connect("destroy",{||gtk.main_quit()})


    combo:=window:lookup("combobox1")
    combo:signal_connect("changed",{|w|cb_combo_changed(w)})

    comboentry:=window:lookup("comboboxentry1")
    comboentry:signal_connect("changed",{|w|cb_comboentry_changed(w)})
    comboentry:get_child:signal_connect("activate",{|w|cb_comboentry_activate(w)})

    d:=directory("*.prg","H")
    
    for n:=1 to len(d)
        combo:append_text(d[n][1])
        comboentry:append_text(d[n][1])
    next
    
    combo:set_active(0) //-1: deselect
    comboentry:set_active(0) //-1: deselect

    button_cancel:=window:lookup("button_cancel")
    button_cancel:signal_connect("clicked",{|w|button_cancel_clicked(w)})

    button_ok:=window:lookup("button_ok")
    button_ok:signal_connect("clicked",{|w|button_ok_clicked(w)})
    
    progressbar:=window:lookup("progressbar1")
    progressbar:set_fraction(0)
    progressbar:set_pulse_step(0.01)


    draw(window:lookup("drawingarea1"))
    
    window:show_all()
    
    gtk.main()
    ?


**************************************************************************** 
static function cb_combo_changed(w)
    ? "changed", w:get_active, w:get_active_text

**************************************************************************** 
static function cb_comboentry_changed(w)
    //itt w a comboentrybox,
    //w:get_child a benne levő entry, de gtkwidget típussal,
    //ezért w:get_text vagy w:get_child:get_text  elszáll
    //"no exported method" hibával, úgyhogy ravasz.
    //? "changed", w:get_child:(gtkentry)get_text  //ez jó

    ? "changed", w:get_active, w:get_active_text //ezt kell használni

**************************************************************************** 
static function cb_comboentry_activate(w)
    //most viszont w az entry
    ? "activated", w:(gtkentry)get_text


**************************************************************************** 
static function button_cancel_clicked(w)
    ? "clicked", w:get_label
    w:lookup("window1"):destroy


**************************************************************************** 
static function button_ok_clicked(w)

local pb:=w:lookup("progressbar1")

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
    ? "clicked", w:get_label


**************************************************************************** 
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

**************************************************************************** 
