
#include "gdk.ch"
#include "gtk.ch"
#include "gdkkey.ch"

******************************************************************************
function main()

local window
local mask

    gtk.init ()
    window:=gtkwindowNew()
    window:signal_connect("destroy",{||gtk.main_quit()})
    window:signal_connect("key-press-event",{|*|cb_key_press(*)})
    window:signal_connect("button_press_event",{|*|cb_button_press(*)})

    mask:=window:get_events
    mask:=numor(mask,GDK_BUTTON_PRESS_MASK)
    mask:=numor(mask,GDK_BUTTON_RELEASE_MASK)
    mask:=numor(mask,GDK_POINTER_MOTION_MASK)
    window:set_events(mask)


    window:show_all()
    gtk.main()
    ?


******************************************************************************
static function cb_button_press(window,event)
    ? "CB_BUTTON_PRESS",{*}

******************************************************************************
static function cb_key_press(window,event)

local keyval:=gdk.event_key.get_keyval(event)

    ? "CB_KEY_PRESS",{*}, keyval::l2hex

    if( keyval==GDK_KEY_Escape )
        ? "GDK_KEY_Escape"

    elseif( keyval==GDK_KEY_Left )
        ? "GDK_KEY_Left"

    elseif( keyval==GDK_KEY_Right )
        ? "GDK_KEY_Right"

    elseif( keyval==GDK_KEY_Home )
        ? "GDK_KEY_Home"

    elseif( keyval==GDK_KEY_End )
        ? "GDK_KEY_End"


    elseif( keyval==GDK_KEY_F1 )
        ? "GDK_KEY_F1"

    elseif( keyval==asc("a") )
        ? "Letter", chr(keyval)
    elseif( keyval==asc("b") )
        ? "Letter", chr(keyval)
    elseif( keyval==asc("c") )
        ? "Letter", chr(keyval)

    end

******************************************************************************
