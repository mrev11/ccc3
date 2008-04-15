
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

static keytable:=init_keytable()

*******************************************************************************
static function init_keytable()
local kt:=gladehashtableNew()

    kt:add({"BackSpace",0xFF08})
    kt:add({"Tab",0xFF09})
    kt:add({"Linefeed",0xFF0A})
    kt:add({"Clear",0xFF0B})
    kt:add({"Return",0xFF0D})
    kt:add({"Pause",0xFF13})
    kt:add({"Scroll_Lock",0xFF14})
    kt:add({"Sys_Req",0xFF15})
    kt:add({"Escape",0xFF1B})
    kt:add({"Num_Lock",0xFF7F})

    kt:add({"Home",0xFF50})
    kt:add({"Left",0xFF51})
    kt:add({"Up",0xFF52})
    kt:add({"Right",0xFF53})
    kt:add({"Down",0xFF54})
    kt:add({"Page_Up",0xFF55})
    kt:add({"Page_Down",0xFF56})
    kt:add({"End",0xFF57})
    kt:add({"Delete",0xFFFF})
    kt:add({"Insert",0xFF63})

    kt:add({"KP_Home",0xFF95})
    kt:add({"KP_Left",0xFF96})
    kt:add({"KP_Up",0xFF97})
    kt:add({"KP_Right",0xFF98})
    kt:add({"KP_Down",0xFF99})
    kt:add({"KP_Page_Up",0xFF9A})
    kt:add({"KP_Page_Down",0xFF9B})
    kt:add({"KP_End",0xFF9C})
    kt:add({"KP_Insert",0xFF9E})
    kt:add({"KP_Delete",0xFF9F})

    kt:add({"F1",0xFFBE})
    kt:add({"F2",0xFFBF})
    kt:add({"F3",0xFFC0})
    kt:add({"F4",0xFFC1})
    kt:add({"F5",0xFFC2})
    kt:add({"F6",0xFFC3})
    kt:add({"F7",0xFFC4})
    kt:add({"F8",0xFFC5})
    kt:add({"F9",0xFFC6})
    kt:add({"F10",0xFFC7})
    kt:add({"F11",0xFFC8})
    kt:add({"F12",0xFFC9})

    return kt

*******************************************************************************
function gladekeysym_to_gdkkeysym(sym)
local code:=keytable:get(sym)
    if( code==NIL )
        code:=asc(sym)
    end
    return code

*******************************************************************************
