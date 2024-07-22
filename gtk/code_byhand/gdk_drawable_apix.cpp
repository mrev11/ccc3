
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
namespace _nsp_drawable {

//------------------------------------------------------------------------------
void _clp_draw_rectangle(int argno)
{
    CCC_PROLOG("gdk.draw_rectangle",7);

    gpointer drawable=_parp(1);
    gpointer gc=_parp(2);
    gboolean filled=_parl(3);
    gint x=_parni(4);
    gint y=_parni(5);
    gint width=_parni(6);
    gint height=_parni(7);

    gdk_draw_rectangle( GDK_DRAWABLE(drawable),
                        GDK_GC(gc),
                        filled,
                        x,
                        y,
                        width,
                        height);
    _ret();
    CCC_EPILOG();
}

//------------------------------------------------------------------------------
void _clp_draw_layout(int argno)
{
    CCC_PROLOG("gdk.draw_layout",5);

    gpointer drawable=_parp(1);
    gpointer gc=_parp(2);
    gint x=_parni(3);
    gint y=_parni(4);
    PangoLayout *layout=(PangoLayout*)_parp(5);
    gdk_draw_layout( GDK_DRAWABLE(drawable),GDK_GC(gc),x,y,layout);
    _ret();
    CCC_EPILOG();
}

//------------------------------------------------------------------------------
void _clp_draw_point(int argno)
{
    CCC_PROLOG("gdk.draw_point",4);

    gpointer drawable=_parp(1);
    gpointer gc=_parp(2);
    gint x=_parni(3);
    gint y=_parni(4);
    gdk_draw_point( GDK_DRAWABLE(drawable),GDK_GC(gc),x,y);
    _ret();
    CCC_EPILOG();
}

//------------------------------------------------------------------------------
void _clp_draw_line(int argno)
{
    CCC_PROLOG("gdk.draw_line",6);

    gpointer drawable=_parp(1);
    gpointer gc=_parp(2);
    gint x1=_parni(3);
    gint y1=_parni(4);
    gint x2=_parni(5);
    gint y2=_parni(6);
    gdk_draw_line( GDK_DRAWABLE(drawable),GDK_GC(gc),x1,y1,x2,y2);
    _ret();
    CCC_EPILOG();
}

//------------------------------------------------------------------------------
void _clp_draw_drawable(int argno)
{
    CCC_PROLOG("gdk.draw_drawable",9);

    gpointer drawable=_parp(1);
    gpointer gc=_parp(2);
    gpointer src=_parp(3);
    gint xsrc=_parni(4);
    gint ysrc=_parni(5);
    gint xdest=_parni(6);
    gint ydest=_parni(7);
    gint width=_parni(8);
    gint height=_parni(9);

    gdk_draw_drawable(  GDK_DRAWABLE(drawable),
                        GDK_GC(gc),
                        GDK_DRAWABLE(src),
                        xsrc,
                        ysrc,
                        xdest,
                        ydest,
                        width,
                        height);
    _ret();
    CCC_EPILOG();
}

//------------------------------------------------------------------------------

} //drawable 
} //gdk
