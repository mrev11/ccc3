
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
#include <gtk/gtk.h>
#include <cccapi.h>
#include <cccgtk.h>

#define DEBUG_NOTIFY

namespace _nsp_gtk{
namespace _nsp_tree_view_column{

//------------------------------------------------------------------------------
void _clp_new_with_attributes(int argno)
{
    CCC_PROLOG("gtk.tree_view_column.new_with_attributes",2);
    const gchar *title=_parc_utf8(1);
    gpointer cell=_parp(2);
    gpointer ret=gtk_tree_view_column_new_with_attributes(title,GTK_CELL_RENDERER(cell),(void*)0);
    _retp(ret);
    CCC_EPILOG();
    
    //Csökkentett képességű változat:
    //csak a title és cell paramétereket veszi át.
    //A doksiból nem érthető, hogy az attribútumok mire vonatkoznak,
    //milyen attribútumok lehetnek, és azoknak milyen értékük lehet.
}

//------------------------------------------------------------------------------
}//tree_view_column
}//gtk
