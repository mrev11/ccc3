
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

namespace _nsp_gtk{
namespace _nsp_tree_model{
extern void _clp_get(int argno);
}}//namespace gtk.tree_model

namespace _nsp_gtk{
namespace _nsp_tree_selection{

//------------------------------------------------------------------------------
void _clp_get_selected(int argno)
{
    //success:=treeselection:get_selected(iter,@model)
    //a paraméterként kapott itert és modelt beállítja,
    //a sikerességet successben jelzi

    CCC_PROLOG("gtk.tree_selection.get_selected",3);
    gpointer self=_parp(1);
    gpointer iter=_parp(2);
    VALUE *refmod=_par(3); //opcionális
    GtkTreeModel *model;
    gboolean ret=gtk_tree_selection_get_selected(GTK_TREE_SELECTION(self),&model,(GtkTreeIter*)iter);
    pointer(model);assign(refmod);pop(); //ref változóban adja a modelt
    _retl(ret);
    CCC_EPILOG();
}

//------------------------------------------------------------------------------
void _clp_get_selected_data(int argno) //bővítmény: rögtön az adatsort adja
{
    CCC_PROLOG("gtk.tree_selection.get_selected_data",1);
    gpointer self=_parp(1);
    GtkTreeModel *model;
    GtkTreeIter iter;
    gboolean ret=gtk_tree_selection_get_selected(GTK_TREE_SELECTION(self),&model,&iter);
    if( ret )
    {
        pointer(model);
        pointer(&iter);
        _nsp_gtk::_nsp_tree_model::_clp_get(2); //list_store datarow
        _rettop();
    }
    else
    {
        _ret(); //NIL nincs választás
    }
    CCC_EPILOG();
}

//------------------------------------------------------------------------------
void _clp_get_selected_rows(int argno)
{
    CCC_PROLOG("gtk.tree_selection.get_selected_rows",2);
    gpointer self=_parp(1);
    VALUE *refmod=_par(2); //opcionális
    GtkTreeModel *model;
    GList *rows=gtk_tree_selection_get_selected_rows(GTK_TREE_SELECTION(self),&model);
    pointer(model);assign(refmod);pop(); //ref változóban adja a modelt

    int n=0;
    GList *item=g_list_first(rows);
    while( item )
    {
        pointer((GtkTreePath*)item->data);
        item=item->next;
        n++;
    }
    g_list_free(rows);
    array(n);
    _rettop();

    CCC_EPILOG();
}

//------------------------------------------------------------------------------
void _clp_get_selected_rows_data(int argno) //bővítmény: rögtön az adatsorokat adja
{
    CCC_PROLOG("gtk.tree_selection.get_selected_rows",1);
    gpointer self=_parp(1);
    GtkTreeModel *model;
    GList *rows=gtk_tree_selection_get_selected_rows(GTK_TREE_SELECTION(self),&model);
    
    int n=0;
    GList *item=g_list_first(rows);
    GtkTreeIter iter;
    while( item )
    {
        GtkTreePath *path=(GtkTreePath*)item->data;
        gtk_tree_model_get_iter(model,&iter,path);
        gtk_tree_path_free(path);

        pointer(model);
        pointer(&iter);
        _nsp_gtk::_nsp_tree_model::_clp_get(2); //list_store datarow
        item=item->next;
        n++;
    }
    g_list_free(rows);
    array(n);
    _rettop();
    CCC_EPILOG();
}

//------------------------------------------------------------------------------
}//tree_selection
}//gtk
