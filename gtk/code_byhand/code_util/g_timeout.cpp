
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

extern void _clp_g_timeout_register_codeblock(int);
extern void _clp_g_timeout_execute_codeblock(int);


//----------------------------------------------------------------------------
static gboolean cb(gpointer data)
{
    number((LONG)data);
    _clp_g_timeout_execute_codeblock(1);
    return flag();
}

//----------------------------------------------------------------------------
void _clp_g_timeout_add(int argno)
{
    CCC_PROLOG("g_timeout_add",2);
    int timeout=_parni(1);
    if( !ISBLOCK(2) )
    {
        ARGERROR();
    }
    _clp_g_timeout_register_codeblock(1);
    int x=D2INT(TOP()->data.number);
    g_timeout_add(timeout,cb,(gpointer)(LONG)x);
    _ret();
    CCC_EPILOG();
}

//----------------------------------------------------------------------------


