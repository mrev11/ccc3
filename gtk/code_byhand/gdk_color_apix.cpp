
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

#include <gdk/gdk.h>
#include <cccapi.h>
#include <cccgtk.h>

#ifdef EMLEKEZTETO
static function cb_color_changed(colorsel)
local ncolor:=gdk.color.new() //fel kell szabadítani!
    gtk.color_selection.get_current_color(colorsel,ncolor)
    gtk.widget.modify_bg(drawingarea,GTK_STATE_NORMAL,ncolor)
    gdk.color.free(ncolor)
#endif

namespace _nsp_gdk {
namespace _nsp_color {

//------------------------------------------------------------------------------
void _clp_new(int argno)
{
    CCC_PROLOG("gdk.color.new",1);
    const gchar *spec=ISSTRING(1)?_parc_utf8(1):0;
    GdkColor *color=new GdkColor;
    if(spec)
    {
        gdk_color_parse(spec,color);
    }
    _retp(color);
    CCC_EPILOG();
}

//------------------------------------------------------------------------------
void _clp_new_from_string(int argno)
{
    CCC_PROLOG("gdk.color.new_from_string",1);
    const gchar *spec=_parc_utf8(1);
    GdkColor *color=new GdkColor;
    gdk_color_parse(spec,color);
    _retp(color);
    CCC_EPILOG();
}

//------------------------------------------------------------------------------
void _clp_free(int argno)
{
    CCC_PROLOG("gdk.color.free",1);
    GdkColor *color=(GdkColor*)_parp(1);
    delete color;
    _ret();
    CCC_EPILOG();
}

//------------------------------------------------------------------------------
void _clp_parse(int argno)
{
    CCC_PROLOG("gdk.color.parse",2);
    const gchar *spec=_parc_utf8(1);
    GdkColor *color=(GdkColor*)_parp(2);
    _retl(gdk_color_parse(spec,color));
    CCC_EPILOG();
}

//------------------------------------------------------------------------------

} //color
} //gdk
