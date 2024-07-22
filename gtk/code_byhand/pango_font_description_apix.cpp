
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
#include <pango/pango.h>
#include <gtk/gtk.h>
#include <cccapi.h>
#include <cccgtk.h>

namespace _nsp_pango {
namespace _nsp_font_description {

//------------------------------------------------------------------------------
void _clp_new(int argno)
{
    CCC_PROLOG("pamgo.font_description.new",1);
    gchar *str=ISSTRING(1)?_parc_utf8(1):0;
    gpointer desc=0;
    if(str)
    {
        desc=pango_font_description_from_string(str);
    }
    else
    {
        desc=pango_font_description_new();
    }
    _retp(desc);
    CCC_EPILOG();
}

//------------------------------------------------------------------------------
void _clp_new_from_string(int argno)
{
    CCC_PROLOG("pamgo.font_description.new_from_string",1);
    gchar *str=_parc_utf8(1);
    gpointer desc=pango_font_description_from_string(str);
    _retp(desc);
    CCC_EPILOG();
}

//------------------------------------------------------------------------------
void _clp_set_family(int argno)
{
    CCC_PROLOG("pamgo.font_description.set_family",2);
    gpointer desc=_parp(1);
    gchar *family=_parc_utf8(2);
    pango_font_description_set_family((PangoFontDescription*)desc,family);
    _ret();
    CCC_EPILOG();
}

//------------------------------------------------------------------------------
void _clp_free(int argno)
{
    CCC_PROLOG("pamgo.font_description.free",1);
    gpointer desc=_parp(1);
    pango_font_description_free((PangoFontDescription*)desc);
    _ret();
    CCC_EPILOG();
}

//------------------------------------------------------------------------------

} //font_description
} //pango
