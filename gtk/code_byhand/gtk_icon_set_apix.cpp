
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
namespace _nsp_icon_set {

//---------------------------------------------------------------------------
void _clp_get_sizes(int argno)
{
    CCC_PROLOG("gtk.icon_set.get_sizes",1);
    GtkIconSet *self=(GtkIconSet*)_parp(1);
    GtkIconSize *sizes;
    gint n_sizes;
    gtk_icon_set_get_sizes(self,&sizes,&n_sizes);
    for(int i=0; i<n_sizes; i++)
    {
        number( (int)sizes[i] );
    }
    g_free(sizes);
    array(n_sizes);
    _rettop();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------

} //icon_set
} //gtk

