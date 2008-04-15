
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
namespace _nsp_file_selection {

//---------------------------------------------------------------------------
void _clp_get_selections(int argno)
{
    CCC_PROLOG("gtk.file_selection.get_selections",1);
    gpointer self=_parp(1);
    gchar **selections=gtk_file_selection_get_selections(GTK_FILE_SELECTION(self));
    int i;
    for( i=0; *(selections+i); i++ )
    {
        stringnb(*(selections+i));
    }
    g_strfreev(selections);
    array(i);
    _rettop();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_get_ok_button(int argno)
{
    CCC_PROLOG("gtk.file_selection.get_ok_button",1);
    gpointer self=_parp(1);
    _retp( GTK_FILE_SELECTION(self)->ok_button );
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_get_cancel_button(int argno)
{
    CCC_PROLOG("gtk.file_selection.get_cancel_button",1);
    gpointer self=_parp(1);
    _retp( GTK_FILE_SELECTION(self)->cancel_button );
    CCC_EPILOG();
}

//---------------------------------------------------------------------------

} //file_selection
} //gtk

