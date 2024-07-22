
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

namespace _nsp_gtk{
namespace _nsp_list_store{

DEFINE_METHOD(gobject);

//------------------------------------------------------------------------------
void _clp_new(int argno) //eltérő paraméterezés

// Pl.   gtk.list_store.new({"B","I","S"})  //Boolean, Int, String
// vagy  gtk.list_store.new("B","I","S")  //Boolean, Int, String
// vagy  gtk.list_store.new("BIS")  //Boolean, Int, String
//
// Az első két paraméterezést visszavezetjük a harmadikra.

{
    VALUE *base=stack-argno;
    push_call("gtk.list_store.new",base);

    int i;

    if( (argno==1) && ISARRAY(1) )
    {
        argno=_paralen(1);
        VALUE *a=ARRPTR(1);
        for( i=0; i<argno; i++ )
        {
            push(a+i);
            swap();
        }
        pop();
    }

    while( argno>1 )
    {
        add();
        argno--;
    }

    if( argno<=0 )
    {
        ARGERROR();
    }

    char *ctype=_parc_utf8(1);
    int n_columns=_parblen(1);
    //GType gtype[n_columns]; //fasz MS
    GType *gtype=(GType*)malloc(n_columns*sizeof(GType)); 

    for( i=0; i<n_columns; i++ )
    {
        char t=ctype[i];

             if( t=='S' )  gtype[i]=G_TYPE_STRING;
        else if( t=='D' )  gtype[i]=G_TYPE_DOUBLE;
        else if( t=='I' )  gtype[i]=G_TYPE_INT;
        else if( t=='B' )  gtype[i]=G_TYPE_BOOLEAN;
        else if( t=='O' )  gtype[i]=G_TYPE_OBJECT;
        else
        {
            ARGERROR();
        }
    }

    gpointer ret=gtk_list_store_newv(n_columns,gtype);
    free(gtype); //fasz MS
    _retp(ret);
    pop_call();
}

//------------------------------------------------------------------------------
static void store(gpointer self, GtkTreeIter *iter, 
                        VALUE *base, int argno, int i, VALUE v)
{
    //az i-edik oszlopba beírja v-t
    
    str2bin(&v);

    GType ct=gtk_tree_model_get_column_type(GTK_TREE_MODEL(self),i);

    if( v.type==TYPE_NIL )
    {
        //kihagy
    }
    else if( v.type==TYPE_BINARY )
    {
        if( ct==G_TYPE_STRING )
        {
            char *value=BINARYPTR(&v);
            gtk_list_store_set(GTK_LIST_STORE(self),iter,i,value,-1);
        }
        else
        {
            ARGERROR();
        }
    }
    else if( v.type==TYPE_NUMBER )
    {
        if( ct==G_TYPE_INT )
        {
            int value=D2INT(v.data.number);
            gtk_list_store_set(GTK_LIST_STORE(self),iter,i,value,-1);
        }
        else if( ct==G_TYPE_DOUBLE )
        {
            double value=v.data.number;
            gtk_list_store_set(GTK_LIST_STORE(self),iter,i,value,-1);
        }
        else
        {
            ARGERROR();
        }
    }
    else if( v.type==TYPE_FLAG )
    {
        if( ct==G_TYPE_BOOLEAN )
        {
            int value=(v.data.flag?1:0);
            gtk_list_store_set(GTK_LIST_STORE(self),iter,i,value,-1);
        }
        else
        {
            ARGERROR();
        }
    }
    else if( v.type==TYPE_POINTER )
    {
        if( ct==G_TYPE_OBJECT )
        {
            gpointer value=v.data.pointer;
            gtk_list_store_set(GTK_LIST_STORE(self),iter,i,value,-1);
        }
        else
        {
            ARGERROR();
        }
    }
    else if( v.type==TYPE_OBJECT )
    {
        if( ct==G_TYPE_OBJECT )
        {
            push_symbol(&v);
            _o_method_gobject.eval(1);
            gpointer value=TOP()->data.pointer;
            pop();
            gtk_list_store_set(GTK_LIST_STORE(self),iter,i,value,-1);
        }
        else
        {
            ARGERROR();
        }
    }
    else if( v.type==TYPE_ARRAY )  //{idx,value}
    {
        int len=v.data.array.oref->length;
        VALUE *a=v.data.array.oref->ptr.valptr;
        if( (len!=2) || (a[0].type!=TYPE_NUMBER) )
        {
            ARGERROR();
        }
        int idx=D2INT(a[0].data.number);
        store(self,iter,base,argno,idx,a[1]); //rekurzió
    }
    else
    {
        ARGERROR();
    }
}

//------------------------------------------------------------------------------
void _clp_set(int argno)
{

#ifdef EMLEKEZTETO
Hivási formák:

1)  gtk.list_store.set(self,iter,{val1,val2,...})
    
    Ez a 0-ás oszlopindextől kezdve feltölti az oszlopokat,
    annyit, ahány value meg van adva. Ha egy value értéke NIL,
    akkor az az oszlop kimarad.

2)  gtk.list_store.set(self,iter,val1,val2,...)
    
    Ez ugyanaz mint az előző eset, vissza van rá vezetve.

3)  gtk.list_store.set(self,iter,{val1, {idx,val2}, ...})

    Speciális esetként, ha (1)-ben valamelyik value {idx,val} alakú,
    akkor az idx-edik oszlopba töltődik val (tehát nem kell minden
    oszlopértéket felsorolni).

Megjegyzés:
    Ha egy string oszlopot nem töltünk ki,
    akkor a lista működik (az oszlop üresnek látszik)
    de a program kilépéskor SIGSEGV keletkezik,
    gondolom azért, mert a GTK fel akarja szabadítani
    a lista adattagját, de a semmibe nyúl.
    Ez a GTK hibája, nem lehet rajta másképp segíteni,
    mint hogy mindig ki kell tölteni az oszlopokat.
#endif

    VALUE *base=stack-argno;
    push_call("gtk.list_store.set",base);
    gpointer self=_parp(1);
    GtkTreeIter* iter=(GtkTreeIter*)_parp(2);
    
    if( (argno>=3) && !ISARRAY(3)  )
    {
        array(argno-2);
        argno=3;
    }

    VALUE *a=_para(3);
    gint n_values=_paralen(3);
    
    for( int i=0; i<n_values; i++ )
    {
        store(self,iter,base,argno,i,a[i]);
    }
    _ret();
    pop_call();
}

//------------------------------------------------------------------------------
void _clp_set_value(int argno)
{
    CCC_PROLOG("gtk.list_store.set_value",4);
    gpointer self=_parp(1);
    GtkTreeIter* iter=(GtkTreeIter*)_parp(2);
    gint column=_parni(3);
    VALUE *v=_par(4);
    store(self,iter,base,argno,column,v[0]);    
    _ret();
    pop_call();
}

//------------------------------------------------------------------------------
}//list_store
}//gtk
