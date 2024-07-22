
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
namespace _nsp_item_factory {


//---------------------------------------------------------------------------
void _clp_create_items(int argno) //eltérő paraméterezés!
{
    CCC_PROLOG("gtk.item_factory.create_items",2);
    gpointer item_factory=_parp(1);
    guint n_entries=_paralen(2);
    VALUE *ventries=_para(2);
    gpointer callback_data=0;

    //GtkItemFactoryEntry entries[n_entries]; //nem megy, fasz MS
    GtkItemFactoryEntry *entries=(GtkItemFactoryEntry*)malloc(n_entries*sizeof(GtkItemFactoryEntry));

    for(guint i=0; i<n_entries; i++)
    {
        #define IDX(x) push(idxl0(x)) // a --- a[x]

        char *p=0;
        push(_par(2));IDX(i+1);IDX(1);str2bin(TOP());
        if( TOP()->type==TYPE_BINARY )
        { 
            p=BINARYPTR(TOP());
        }

        char *a=0;
        push(_par(2));IDX(i+1);IDX(2);str2bin(TOP());
        if( TOP()->type==TYPE_BINARY ) 
        {
            a=BINARYPTR(TOP());
        }

        char *t=0;
        push(_par(2));IDX(i+1);IDX(4);str2bin(TOP());
        if( TOP()->type==TYPE_BINARY ) 
        {
            t=BINARYPTR(TOP());
        }

        char *x=0;
        push(_par(2));IDX(i+1);
        if( 5<=ARRAYLEN(TOP()) )
        {
            IDX(5);str2bin(TOP());
            if( TOP()->type==TYPE_BINARY ) 
            {
                x=BINARYPTR(TOP());
            }
        }

        printf("\n%s %s %s",p,a?a:"(null)",t);fflush(0);

        entries[i].path=p;
        entries[i].accelerator=a;
        entries[i].callback=0; //nem használjuk
        entries[i].callback_action=0; //nem használjuk
        entries[i].item_type=t;
        entries[i].extra_data=x; //stock-id
    }

    _clp_gc(0);pop();
    gtk_item_factory_create_items(GTK_ITEM_FACTORY(item_factory),n_entries,entries,callback_data);

    //utólag bekapcsoljuk a kódblokkokat

    extern void _clp_register_callbacks(int argno); //gtk.item_factory névtér!
    push_symbol(_par(1)); //item_factory
    push_symbol(_par(2)); //entries
    _clp_register_callbacks(2);
    pop();
    free(entries); //fasz MS
    _ret();
    CCC_EPILOG();
    _clp_gc(0);pop();
}

//---------------------------------------------------------------------------

} //item_factory
} //gtk

