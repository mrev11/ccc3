
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


namespace _nsp_gtk {

//---------------------------------------------------------------------------
void push_gslist_c_freelist_freedata(GSList *list) // stack:  --- array
{
    GSList *item=list;
    int n_items=0;
    while( item )
    {
        if( item->data )
        {
            stringnb( (gchar*)item->data );
            g_free((gchar*)item->data);
        }
        else
        {
            string(L"");
        }
        item=item->next;
        n_items++;
    }
    g_slist_free(list);
    array(n_items);
}    


//---------------------------------------------------------------------------
void push_gslist_p_freelist(GSList *list) // stack:  --- array
{
    GSList *item=list;
    int n_items=0;
    while( item )
    {
        pointer(item->data);
        item=item->next;
        n_items++;
    }
    g_slist_free(list);
    array(n_items);
}


//---------------------------------------------------------------------------
void push_gslist_p(GSList *list) // stack:  --- array
{
    GSList *item=list;
    int n_items=0;
    while( item )
    {
        pointer(item->data);
        item=item->next;
        n_items++;
    }
    array(n_items);
}

//---------------------------------------------------------------------------
void push_glist_p_freelist(GList *list) // stack:  --- array
{
    GList *item=list;
    int n_items=0;
    while( item )
    {
        pointer(item->data);
        item=item->next;
        n_items++;
    }
    g_list_free(list);
    array(n_items);
}

//---------------------------------------------------------------------------
void push_glist_p(GList *list) // stack:  --- array
{
    GList *item=list;
    int n_items=0;
    while( item )
    {
        pointer(item->data);
        item=item->next;
        n_items++;
    }
    array(n_items);
}


//---------------------------------------------------------------------------

} //gtk

