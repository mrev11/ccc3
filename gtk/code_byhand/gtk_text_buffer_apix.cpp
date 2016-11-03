
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

#include <gtk/gtk.h>
#include <cccapi.h>
#include <cccgtk.h>

namespace _nsp_gtk {
namespace _nsp_text_buffer {

//---------------------------------------------------------------------------
void _clp_get_text(int argno)
{
    CCC_PROLOG("gtk.text_buffer.get_text",4);
    gpointer self=_parp(1);
    GtkTextIter *iter_start=ISNIL(2)?0:(GtkTextIter*)_parp(2);
    GtkTextIter *iter_end=ISNIL(3)?0:(GtkTextIter*)_parp(3);
    gboolean include_hidden=ISNIL(4)?1:_parl(4);
    GtkTextIter i_start,i_end;
    if( (iter_start==0) || (iter_end==0) )
    {
        gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(self),&i_start,&i_end);
        if(iter_start==0)
        {
            iter_start=&i_start;
        }
        if(iter_end==0)
        {
            iter_end=&i_end;
        }
    }
    gchar *ret=gtk_text_buffer_get_text(GTK_TEXT_BUFFER(self),iter_start,iter_end,include_hidden);
    _retc_utf8(ret);
    g_free(ret); //allocated UTF-8 string
    CCC_EPILOG();
}

//---------------------------------------------------------------------------

} //text_buffer
} //gtk
