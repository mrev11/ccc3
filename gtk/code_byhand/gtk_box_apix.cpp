
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
#include <gtk/gtk.h>
#include <cccapi.h>
#include <cccgtk.h>

namespace _nsp_gtk {
namespace _nsp_box {

//---------------------------------------------------------------------------
void _clp_query_child_packing(int argno) //eltérés: array-t adunk vissza
{
    CCC_PROLOG("gtk.box.query_child_packing",6);
    gpointer box=_parp(1);
    gpointer child=_parp(2);
    gboolean expand;
    gboolean fill;
    guint padding;
    GtkPackType ptype;
    gtk_box_query_child_packing(GTK_BOX(box),GTK_WIDGET(child),&expand,&fill,&padding,&ptype);
    logical(expand); assign(base+2); //ref változóban is adja
    logical(fill); assign(base+3); //ref változóban is adja
    number(padding); assign(base+4); //ref változóban is adja
    number((int)ptype); assign(base+5); //ref változóban is adja
    array(4);
    _rettop();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------

} //box
} //gtk

