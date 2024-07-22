
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

#ifdef EMLEKEZTETO
  A GTK néha a glib könyvtár struktúrái segítségével ad adatokat,
  amihez kényelmetlen alkalmazkodni, ui. nyilván jobb lenne, ha
  a CCC (Python) a saját eszközeit használhatná. Ezek itt a kétirányú
  lista bejárásához szükséges függvények. A listát (kiolvasás után)
  általában fel kell szabadítani (adattagonként is és egyben is):

    iter:=gtk.tree_iter.new()
    item:=g_list_first(list)
    while( !empty(item) )
        path:=g_list_get_data(item) //tudni kell, mi van benne
        ...
        gtk.tree_path.free(path)
        item:=g_list_next(item)
    end
    gtk.tree_iter.free(iter)
    g_list_free(list)
    
  Semmi védelem nincs az ellen, ha a típusok  nem találkoznak,
  olyankor a program símán SIGSEGV-zik.
#endif

//----------------------------------------------------------------------------
void _clp_g_list_get_data(int argno)
{
    CCC_PROLOG("g_list_get_data",1);
    GList *list=(GList*)_parp(1);
    _retp(list->data);
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp_g_list_free(int argno)
{
    CCC_PROLOG("g_list_free",1);
    GList *list=(GList*)_parp(1);
    g_list_free(list);
    _ret();
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp_g_list_first(int argno)
{
    CCC_PROLOG("g_list_first",1);
    GList *list=(GList*)_parp(1);
    GList *item=g_list_first(list);
    _retp(item);
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp_g_list_last(int argno)
{
    CCC_PROLOG("g_list_last",1);
    GList *list=(GList*)_parp(1);
    GList *item=g_list_last(list);
    _retp(item);
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp_g_list_next(int argno)
{
    CCC_PROLOG("g_list_next",1);
    GList *list=(GList*)_parp(1);
    GList *item=g_list_next(list);
    _retp(item);
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp_g_list_previous(int argno)
{
    CCC_PROLOG("g_list_previous",1);
    GList *list=(GList*)_parp(1);
    GList *item=g_list_previous(list);
    _retp(item);
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
