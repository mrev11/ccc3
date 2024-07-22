
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

#include <string.h>
#include <stdint.h>
#include <gtk/gtk.h>
#include <cccapi.h>
#include <cccgtk.h>

namespace _nsp_gtk {
namespace _nsp_gobject {

//---------------------------------------------------------------------------
void _clp_ref(int argno)
{
    CCC_PROLOG("gtk.gobject.ref",1);
    gpointer o=_parp(1);
    g_object_ref(o);
    _ret();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_unref(int argno)
{
    CCC_PROLOG("gtk.gobject.unref",1);
    gpointer o=_parp(1);
    g_object_unref(o);
    _ret();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_type_name(int argno)
{
    CCC_PROLOG("gtk.gobject.type_name",1);
    gpointer o=_parp(1);
    const char *name=G_OBJECT_TYPE_NAME(o);
    _retcb(name);
    CCC_EPILOG();
}

//---------------------------------------------------------------------------

} //gobject
} //gtk
