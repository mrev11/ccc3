
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

#include <stdint.h>
#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include <cccapi.h>
#include <cccgtk.h>

namespace _nsp_gdk {
namespace _nsp_window {

//------------------------------------------------------------------------------
void _clp_invalidate_rect(int argno)
{
    CCC_PROLOG("gdk.window.invalidate_rect",6);
    gpointer window=_parp(1);

    GdkRectangle rect;
    rect.x=_parni(2);
    rect.y=_parni(3);
    rect.width=_parni(4);
    rect.height=_parni(5);
    
    gboolean invalidate_children=ISFLAG(6)?(0!=_parl(6)):0;

    gdk_window_invalidate_rect(GDK_WINDOW(window),&rect,invalidate_children);
    _ret();
    CCC_EPILOG();
}

//------------------------------------------------------------------------------
void _clp_get_pointer(int argno)
{
    CCC_PROLOG("gdk.window.get_pointer",6);
    gpointer window=_parp(1);
    int x;
    int y;
    GdkModifierType mask;
    gdk_window_get_pointer(GDK_WINDOW(window),&x,&y,&mask);
    number(x);
    number(y);
    number((int)mask);
    array(3);
    _rettop();
    CCC_EPILOG();
}

//------------------------------------------------------------------------------

} //window
} //gdk
