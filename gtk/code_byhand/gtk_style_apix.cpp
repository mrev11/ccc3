
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
namespace _nsp_style{

//------------------------------------------------------------------------------
void _clp_get_fg_gc(int argno)
{
    CCC_PROLOG("gtk.style.get_fg_gc",2);
    gpointer self=_parp(1);
    guint idx=ISNUMBER(1)?_parni(2):0;
    gpointer ret=GTK_STYLE(self)->fg_gc[idx]; //5 db van neki
    _retp(ret);
    CCC_EPILOG();
}

//------------------------------------------------------------------------------
void _clp_get_bg_gc(int argno)
{
    CCC_PROLOG("gtk.style.get_bg_gc",2);
    gpointer self=_parp(1);
    guint idx=ISNUMBER(1)?_parni(2):0; 
    gpointer ret=GTK_STYLE(self)->bg_gc[idx]; //5 db van neki
    _retp(ret);
    CCC_EPILOG();
}

//------------------------------------------------------------------------------
void _clp_get_black_gc(int argno)
{
    CCC_PROLOG("gtk.style.get_black_gc",1);
    gpointer self=_parp(1);
    gpointer ret=GTK_STYLE(self)->black_gc;
    _retp(ret);
    CCC_EPILOG();
}

//------------------------------------------------------------------------------
void _clp_get_white_gc(int argno)
{
    CCC_PROLOG("gtk.style.get_white_gc",1);
    gpointer self=_parp(1);
    gpointer ret=GTK_STYLE(self)->white_gc;
    _retp(ret);
    CCC_EPILOG();
}


//------------------------------------------------------------------------------
} //style
} //gtk
