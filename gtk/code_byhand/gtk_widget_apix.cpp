
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
namespace _nsp_widget {

//---------------------------------------------------------------------------
void _clp_grab_default(int argno)
{
    CCC_PROLOG("gtk.widget.grab_default",1);
    gpointer self=_parp(1);
    GTK_WIDGET_SET_FLAGS(GTK_WIDGET(self),GTK_CAN_DEFAULT); //betoldva
    gtk_widget_grab_default(GTK_WIDGET(self));
    _ret();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_get_drawable(int argno)  //bővítmény
{
    CCC_PROLOG("gtk.widget.get_drawable",1);
    gpointer self=_parp(1);
    if( GTK_WIDGET_NO_WINDOW(GTK_WIDGET(self)) )
    {
        _ret(); //nincs neki ablaka
    }
    else
    {
        _retp( GTK_WIDGET(self)->window ); //drawable
    }
    CCC_EPILOG();
}


//---------------------------------------------------------------------------
void _clp_get_allocation(int argno)  //bővítmény
{
    CCC_PROLOG("gtk.widget.get_allocation",1);
    GtkWidget *self=GTK_WIDGET(_parp(1));
    number( self->allocation.x );
    number( self->allocation.y );
    number( self->allocation.width );
    number( self->allocation.height );
    array(4);
    _rettop();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------

} //widget
} //gtk


