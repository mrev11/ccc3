
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

****************************************************************************
function main()

local window,button1,button2,button3

//    printpid()
//    printexe()

    gtk.init()
    
    window:=gladeloadgui("project1.glade")
    
    printhash(window)

    button1:=window:lookup("button1")
    button2:=window:lookup("button2")
    button3:=window:lookup("button3")

    window:signal_connect("destroy",{||gtk.main_quit()})
    button1:signal_connect("clicked",{|w|cb_button1_clicked(w)})
    button2:signal_connect("clicked",{|w|cb_button2_clicked(w)})
    button3:signal_connect("clicked",{||window:destroy})

    window:show_all()
    gtk.main()
    ?

    return NIL


****************************************************************************
static function cb_button1_clicked(b)
local statbar:=b:lookup("statusbar1")
local view:=b:lookup("textview1")
local buffer:=view:get_buffer
    buffer:set_text(memoread("project1.glade"))
    statbar:pop(0)
    statbar:push(0,"button1 clicked")
    ? "button1 clicked"


****************************************************************************
static function cb_button2_clicked(b)
local statbar:=b:lookup("statusbar1")
local view:=b:lookup("textview1")
local buffer:=view:get_buffer
    ? buffer:get_text
    statbar:pop(0)
    statbar:push(0,"button2 clicked")
    ? "button2 clicked"


****************************************************************************
static function printpid()
    set printer to pid
    set printer on
    ?? getpid()
    set printer to
    set printer off

static function printexe()
    set printer to exe
    set printer on
    ?? exename()
    set printer to
    set printer off

****************************************************************************
static function printhash(wdg)
local hash,n
    hash:=eval(wdg:widgettableblock):hasharray
    for n:=1 to len(hash)
        if( hash[n]!=NIL )
            ? n, hash[n][1], hash[n][2]:classname
        end
    next

****************************************************************************
