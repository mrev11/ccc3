
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

//------------------------------------------------------------------------------
static void push_data(gpointer self, GtkTreeIter* iter, int col)
{
    GType ct=gtk_tree_model_get_column_type(GTK_TREE_MODEL(self),col);

    if( ct==G_TYPE_STRING )
    {
        gchar *value;
        gtk_tree_model_get(GTK_TREE_MODEL(self),iter,col,&value,-1);
        if( (value==0) || (*value==0) )
        {
            string(L"");
        }
        else
        {
            stringnb(value);
        }
        g_free(value);
    }
    else if( ct==G_TYPE_INT )
    {
        int value;
        gtk_tree_model_get(GTK_TREE_MODEL(self),iter,col,&value,-1);
        number(value);
    }
    else if( ct==G_TYPE_DOUBLE )
    {
        double value;
        gtk_tree_model_get(GTK_TREE_MODEL(self),iter,col,&value,-1);
        number(value);
    }
    else if( ct==G_TYPE_BOOLEAN )
    {
        gboolean value;
        gtk_tree_model_get(GTK_TREE_MODEL(self),iter,col,&value,-1);
        logical(value);
    }
    else if( ct==G_TYPE_OBJECT )
    {
        gpointer value;
        gtk_tree_model_get(GTK_TREE_MODEL(self),iter,col,&value,-1);
        pointer(value);
    }
}        

//------------------------------------------------------------------------------
void _clp_get(int argno)
{
    CCC_PROLOG("gtk.tree_model.get",2);
    gpointer self=_parp(1);
    GtkTreeIter* iter=(GtkTreeIter*)_parp(2);
    int n_columns=gtk_tree_model_get_n_columns(GTK_TREE_MODEL(self));
    for(int col=0; col<n_columns; col++ )
    {
        push_data(self,iter,col);
    }
    array(n_columns);
    _rettop();
    CCC_EPILOG();
}

//------------------------------------------------------------------------------
// GtkTreeModel method get_value
//  c_name       gtk_tree_model_get_value
//  return       none
//  param-1      {GtkTreeModel*,self}
//  param-2      {GtkTreeIter*,iter}
//  param-3      {gint,column}
//  param-4      {GValue*,value}

void _clp_get_value(int argno)
{
    CCC_PROLOG("gtk.tree_model.get_value",4);
    gpointer self=_parp(1);
    GtkTreeIter* iter=(GtkTreeIter*)_parp(2);
    gint column=_parni(3);
    VALUE *value=_par(4);
    //gtk_tree_model_get_value(GTK_TREE_MODEL(self),iter,column,value);
    push_data(self,iter,column);
    assign(value); //ref-ben is adja
    _rettop();
    CCC_EPILOG();
}

//------------------------------------------------------------------------------
}//tree_model
}//gtk
