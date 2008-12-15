
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
namespace _nsp_text_iter{

//Kellemetlen kivétel:
//Ez nem referenciaszámlált gobject,
//hanem (a példaprogramok szerint) 
//a stack-en létrehozott struktúra
//CCC-ben létre kell hozni, majd fel kell szabadítani.
//A gtk.text_iter.free automatikusan generálódik.

//------------------------------------------------------------------------------
void _clp_new(int argno)
{
    CCC_PROLOG("gtk.text_iter.new",0);
    _retp( g_slice_new(GtkTextIter) ); //2008.12.14
    CCC_EPILOG();
}

//------------------------------------------------------------------------------

} //text_iter
} //gtk
