
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
namespace _nsp_gc {

//------------------------------------------------------------------------------
void _clp_new(int argno)
{
    CCC_PROLOG("gdk.gc.new",1);
    gpointer drawable=_parp(1);
    GdkGC *gc=gdk_gc_new(GDK_DRAWABLE(drawable));
    _retp(gc);
    CCC_EPILOG();
}

//------------------------------------------------------------------------------
void _clp_set_rgb_fg_color(int argno)
{
    CCC_PROLOG("gdk.gc.set_rgb_fg_color",2);
    gpointer gc=_parp(1);
    gpointer color=_parp(2);
    gdk_gc_set_rgb_fg_color(GDK_GC(gc),(GdkColor*)color);
    _ret();
    CCC_EPILOG();
}

//------------------------------------------------------------------------------

} //color
} //gdk
