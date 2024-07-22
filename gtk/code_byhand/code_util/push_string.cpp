
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
#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include <cccapi.h>
#include <cccgtk.h>


namespace _nsp_gtk {

//---------------------------------------------------------------------------
void push_string(const char *str) // stack:  --- string
{
    if( str )
    {
        stringnb(str);
    }
    else
    {
        string(L"");
    }
}

//---------------------------------------------------------------------------
void push_string_free(const gchar *str) // stack:  --- string
{
    if( str )
    {
        stringnb(str);
        g_free((gchar*)str);
    }
    else
    {
        string(L"");
    }
}

//---------------------------------------------------------------------------

} //gtk

