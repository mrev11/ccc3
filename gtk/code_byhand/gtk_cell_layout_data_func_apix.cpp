
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

#define DEBUG_NOTIFY

namespace _nsp_gtk{
namespace _nsp_cell_layout{

extern void _clp_cell_register_codeblock(int argno);
extern void _clp_cell_unregister_codeblock(int argno);
extern void _clp_cell_execute_codeblock(int argno);


//------------------------------------------------------------------------------
static void cell_data_func( GtkCellLayout* column,
                            GtkCellRenderer* renderer,
                            GtkTreeModel* model,
                            GtkTreeIter* iter,
                            gpointer x )
{
    number((LONG)x); //idx
    pointer(column);
    pointer(renderer);
    pointer(model);
    pointer(iter);
    _nsp_gtk::_nsp_cell_layout::_clp_cell_execute_codeblock(5);
    pop();
}                            

//------------------------------------------------------------------------------
static void destroy_notify(void *x)
{
    #ifdef DEBUG_NOTIFY
    printf("\nNOTIFY-cell-data-func %ld", (LONG)x);
    #endif 

    number((LONG)x); //idx
    _nsp_gtk::_nsp_cell_layout::_clp_cell_unregister_codeblock(1);
    pop();
}

//------------------------------------------------------------------------------
// GtkTreeViewColumn method set_cell_data_func
//  c_name       gtk_cell_layout_set_cell_data_func
//  return       none
//  param-1      {GtkTreeViewColumn*,self}
//  param-2      {GtkCellRenderer*,cell_renderer}
//  param-3      {GtkCellDataFunc,func}
//  param-4      {gpointer,func_data}
//  param-5      {GtkDestroyNotify,destroy}
//  ccc          byhand

void _clp_set_cell_data_func(int argno)
{
    CCC_PROLOG("gtk.cell_layout.set_cell_data_func",5);
    gpointer column=_parp(1);
    gpointer renderer=_parp(2);
    VALUE *datablk=_par(3);
    VALUE *objcol=_par(4);
    VALUE *objrnd=_par(5);
    
    pointer(column);
    pointer(renderer);
    push_symbol(datablk);
    push_symbol(objcol);
    push_symbol(objrnd);
    _nsp_gtk::_nsp_cell_layout::_clp_cell_register_codeblock(5);
    long idx=D2INT(TOP()->data.number);
    pop();

    gtk_cell_layout_set_cell_data_func(     GTK_CELL_LAYOUT(column),
                                            GTK_CELL_RENDERER(renderer),
                                            cell_data_func,
                                            (gpointer)idx,
                                            destroy_notify);
    _ret();
    CCC_EPILOG();
}

//------------------------------------------------------------------------------
}//cell_layout
}//gtk

