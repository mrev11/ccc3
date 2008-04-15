
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

//----------------------------------------------------------------------------
void _clp_g_slist_get_data(int argno)
{
    CCC_PROLOG("g_slist_get_data",1);
    GSList *list=(GSList*)_parp(1);
    _retp(list->data);
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp_g_slist_free(int argno)
{
    CCC_PROLOG("g_slist_free",1);
    GSList *list=(GSList*)_parp(1);
    g_slist_free(list);
    _ret();
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp_g_slist_last(int argno)
{
    CCC_PROLOG("g_slist_last",1);
    GSList *list=(GSList*)_parp(1);
    GSList *item=g_slist_last(list);
    _retp(item);
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp_g_slist_next(int argno)
{
    CCC_PROLOG("g_slist_next",1);
    GSList *list=(GSList*)_parp(1);
    GSList *item=g_slist_next(list);
    _retp(item);
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
