
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
namespace _nsp_stock {


//---------------------------------------------------------------------------
void _clp_list_ids(int argno)
{
    CCC_PROLOG("gtk.stock.list_ids",0);
    GSList *list=gtk_stock_list_ids();
    GSList *item=list;
    int n=0;
    while( item )
    {
        stringnb( (gchar*)item->data );
        g_free((gchar*)item->data);
        item=item->next;
        n++;
    }
    g_slist_free(list);
    array(n);
    _rettop();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_lookup(int argno)
{
    CCC_PROLOG("gtk.stock.lookup",2);
    const gchar *stock_id=_parc_utf8(1);
    GtkStockItem *stock_item=(GtkStockItem*)_parp(2);
    _retl( gtk_stock_lookup(stock_id,stock_item) );
    CCC_EPILOG();
}

//---------------------------------------------------------------------------

}//stock
}//gtk

