
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
namespace _nsp_pixbuf {

//------------------------------------------------------------------------------
void _clp_new_from_inline(int argno)
{
    CCC_PROLOG("gdk.pixbuf.new_from_inline",2);
    gint data_length=_parblen(1);
    const guint8 *data=(guint8*)_parb(1);
    gboolean copy_pixels=ISNIL(2)?1:_parl(2);
    GdkPixbuf *pb=gdk_pixbuf_new_from_inline(data_length,data,copy_pixels,0);
    _retp(pb);
    CCC_EPILOG();
}

//------------------------------------------------------------------------------

} //pixbuf
} //gdk
