
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

namespace _nsp_gtk{
namespace _nsp_editable{

//------------------------------------------------------------------------------
void _clp_insert_text(int argno)
{
    CCC_PROLOG("gtk.editable.insert_text",3);
    gpointer self=_parp(1);
    //const char *text=_parc(2);
    const char *text=_parc_utf8(2);
    gint length=_parblen(2);
    gint position=0;

    if( ISNUMBER(3) )
    {
        position=_parnu(3);
    }
    else if( ISREF(3) )
    {
        VALUE v=_par(3)->data.vref->value;
        if( v.type==TYPE_NUMBER )
        {
            position=D2INT(v.data.number);
        }
    }

    gtk_editable_insert_text(GTK_EDITABLE(self),text,length,&position);

    if( ISREF(3) )
    {
        number(position);
        assign(_par(3));
        pop();
    }
    _retni(position);
    CCC_EPILOG();
}
//------------------------------------------------------------------------------

} //editable
} //gtk
