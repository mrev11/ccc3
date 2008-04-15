
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

namespace _nsp_gtk {
namespace _nsp_stock_item {


//---------------------------------------------------------------------------
void _clp_new(int argno)
{
    CCC_PROLOG("gtk.stock_item.new",0);
    _retp( new GtkStockItem );
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_free(int argno)
{
    CCC_PROLOG("gtk.stock_item.free",1);
    delete( (GtkStockItem*)_parp(1) );
    _ret();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_get_stock_id(int argno)
{
    CCC_PROLOG("gtk.stock_item.get_stock_id",1);
    GtkStockItem *p=(GtkStockItem*)_parp(1);
    _retc_utf8(p->stock_id);
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_get_label(int argno)
{
    CCC_PROLOG("gtk.stock_item.get_label",1);
    GtkStockItem *p=(GtkStockItem*)_parp(1);
    _retc_utf8(p->label);
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_get_modifier(int argno)
{
    CCC_PROLOG("gtk.stock_item.get_modifier",1);
    GtkStockItem *p=(GtkStockItem*)_parp(1);
    _retni((int)p->modifier);
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_get_keyval(int argno)
{
    CCC_PROLOG("gtk.stock_item.get_keyval",1);
    GtkStockItem *p=(GtkStockItem*)_parp(1);
    _retni(p->keyval);
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_get_translation_domain(int argno)
{
    CCC_PROLOG("gtk.stock_item.get_translation_domain",1);
    GtkStockItem *p=(GtkStockItem*)_parp(1);
    _retc_utf8(p->translation_domain);
    CCC_EPILOG();
}

//---------------------------------------------------------------------------

}//stock_item
}//gtk

