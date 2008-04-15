
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

#include <string.h>
#include <gtk/gtk.h>
#include <cccapi.h>
#include <cccgtk.h>


namespace _nsp_gtk {
namespace _nsp_gobject {

extern void _clp_signal_register_codeblock(int argno);
extern void _clp_signal_unregister_codeblock(int argno);
extern void _clp_signal_execute_codeblock(int argno);


DEFINE_METHOD(operation);
DEFINE_METHOD(description);

//---------------------------------------------------------------------------
static void cb_wxv(GtkWidget *w, gpointer x)
{
    number((long)x); //idx
    pointer(w); //widget
    _nsp_gtk::_nsp_gobject::_clp_signal_execute_codeblock(2);
    pop();
}

//---------------------------------------------------------------------------
static void cb_wixv(GtkWidget *w, gint a, gpointer x)
{
    number((long)x); //idx
    pointer(w); //widget
    number(a);
    _nsp_gtk::_nsp_gobject::_clp_signal_execute_codeblock(3);
    pop();
}

//---------------------------------------------------------------------------
static void cb_wiixv(GtkWidget *w, gint a1, gint a2, gpointer x)
{
    number((long)x); //idx
    pointer(w); //widget
    number(a1);
    number(a2);
    _nsp_gtk::_nsp_gobject::_clp_signal_execute_codeblock(4);
    pop();
}

//---------------------------------------------------------------------------
static void cb_wiibxv(GtkWidget *w, gint a1, gint a2, gint b, gpointer x)
{
    number((long)x); //idx
    pointer(w); //widget
    number(a1);
    number(a2);
    logical(b);
    _nsp_gtk::_nsp_gobject::_clp_signal_execute_codeblock(5);
    pop();
}

//---------------------------------------------------------------------------
static void cb_wsxv(GtkWidget *w, gpointer s, gpointer x)
{
    number((long)x); //idx
    pointer(w); //widget
    stringn0((char*)s); //path_string
    _nsp_gtk::_nsp_gobject::_clp_signal_execute_codeblock(3);
    pop();
}

//---------------------------------------------------------------------------
static void cb_wssxv(GtkWidget *w, gchar *a1, gchar *a2, gpointer x)
{
    number((long)x); //idx
    pointer(w); //widget
    stringn0(a1); //pathstr
    stringn0(a2); //newtext
    _nsp_gtk::_nsp_gobject::_clp_signal_execute_codeblock(4);
    pop();
}

//---------------------------------------------------------------------------
static void cb_wpxv(GtkWidget *w, gpointer *p, gpointer x)
{
    number((long)x); //idx
    pointer(w); //widget
    pointer(p);
    _nsp_gtk::_nsp_gobject::_clp_signal_execute_codeblock(3);
    pop();
}

//---------------------------------------------------------------------------
static void cb_wppxv(GtkWidget *w, gpointer *p1, gpointer *p2, gpointer x)
{
    number((long)x); //idx
    pointer(w); //widget
    pointer(p1);
    pointer(p2);
    _nsp_gtk::_nsp_gobject::_clp_signal_execute_codeblock(4);
    pop();
}

//---------------------------------------------------------------------------
static void cb_wpixv(GtkWidget *w, gpointer *p1, gint a, gpointer x)
{
    number((long)x); //idx
    pointer(w); //widget
    pointer(p1);
    number(a);
    _nsp_gtk::_nsp_gobject::_clp_signal_execute_codeblock(4);
    pop();
}

//---------------------------------------------------------------------------
static gint cb_wpxb(GtkWidget *w, gpointer *e, gpointer x)
{
    number((long)x); //idx
    pointer(w); //widget
    pointer(e); //event 
    _nsp_gtk::_nsp_gobject::_clp_signal_execute_codeblock(3);
    
    int result=0;
    if( TOP()->type==TYPE_FLAG )
    {
        result=TOP()->data.flag;
    }
    pop();
    return result;
}

//---------------------------------------------------------------------------
static gint cb_wixb(GtkWidget *w, gint a, gpointer x)
{
    number((long)x); //idx
    pointer(w); //widget
    number(a);
    _nsp_gtk::_nsp_gobject::_clp_signal_execute_codeblock(3);
    
    int result=0;
    if( TOP()->type==TYPE_FLAG )
    {
        result=TOP()->data.flag;
    }
    pop();
    return result;
}

//---------------------------------------------------------------------------
static gint cb_wbxb(GtkWidget *w, gint b, gpointer x)
{
    number((long)x); //idx
    pointer(w); //widget
    logical(b);
    _nsp_gtk::_nsp_gobject::_clp_signal_execute_codeblock(3);
    
    int result=0;
    if( TOP()->type==TYPE_FLAG )
    {
        result=TOP()->data.flag;
    }
    pop();
    return result;
}

//---------------------------------------------------------------------------
static int partype(const char *gname)
{
    const char *type_i=".gint.guint.GEnum.";
    const char *type_d=".gdouble.gfloat.";
    const char *type_b=".gboolean.";
    const char *type_s=".gchararray.";
    const char *type_p=".GBoxed.GObject.gpointer.";
    const char *type_v=".void.";

    char name[128];
    sprintf(name,".%s.",gname);

         if( strstr(type_i,name) ) return 'i';
    else if( strstr(type_d,name) ) return 'd';
    else if( strstr(type_b,name) ) return 'b';
    else if( strstr(type_s,name) ) return 's';
    else if( strstr(type_p,name) ) return 'p';
    else if( strstr(type_v,name) ) return 'v';
    else
    {
        //ERROR: ismeretlen a típus

        _clp_errornew(0);
        dup();string(L"signal_connect");_o_method_operation.eval(2);pop();
        dup();string(L"unknown partype: ");stringnb(gname);add();_o_method_description.eval(2);pop();
        _clp_break(1);
        pop();
    }
    
    return 0;
}

//---------------------------------------------------------------------------
void *find_callback(gpointer widget, const char *sig)
{
    void *callback=0;

    GType itype=G_TYPE_FROM_INSTANCE(widget);
    guint signal_id=g_signal_lookup(sig,itype);
    if( signal_id==0 )
    {
        //ERROR: nincs regisztrálva ilyen szignál

        char spec[128];
        sprintf(spec,"%s.%s",g_type_name(itype),sig);
        _clp_errornew(0);
        dup();string(L"signal_connect");_o_method_operation.eval(2);pop();
        dup();string(L"unknown signal: ");stringnb(spec);add();_o_method_description.eval(2);pop();
        _clp_break(1);
        pop();
    }

    GSignalQuery query;
    g_signal_query(signal_id,&query);
  
    char cb_spec[128];
    int idx=0;
    cb_spec[idx++]='w';
    
    for(int i=0; i<(int)query.n_params; i++)
    {
        GType type=G_TYPE_FUNDAMENTAL(query.param_types[i]);
        const char *name=g_type_name(type);
        cb_spec[idx++]=(char)partype(name);
    }

    cb_spec[idx++]='x';

    GType type=G_TYPE_FUNDAMENTAL(query.return_type);
    const char *name=g_type_name(type);
    cb_spec[idx++]=(char)partype(name);

    cb_spec[idx++]=0;
    
    //printf("\n%s",cb_spec);

         if( strcmp(cb_spec,"wxv")==0 )       callback=(void*)cb_wxv;
    else if( strcmp(cb_spec,"wixv")==0 )      callback=(void*)cb_wixv;
    else if( strcmp(cb_spec,"wiixv")==0 )     callback=(void*)cb_wiixv;
    else if( strcmp(cb_spec,"wiibxv")==0 )    callback=(void*)cb_wiibxv;
    else if( strcmp(cb_spec,"wsxv")==0 )      callback=(void*)cb_wsxv;
    else if( strcmp(cb_spec,"wssxv")==0 )     callback=(void*)cb_wssxv;
    else if( strcmp(cb_spec,"wpxv")==0 )      callback=(void*)cb_wpxv;
    else if( strcmp(cb_spec,"wppxv")==0 )     callback=(void*)cb_wppxv;
    else if( strcmp(cb_spec,"wpixv")==0 )     callback=(void*)cb_wpixv;
    else if( strcmp(cb_spec,"wpxb")==0 )      callback=(void*)cb_wpxb;
    else if( strcmp(cb_spec,"wixb")==0 )      callback=(void*)cb_wixb;
    else if( strcmp(cb_spec,"wbxb")==0 )      callback=(void*)cb_wbxb;
    else
    {
        //ERROR: nincs megfelelő callback

        _clp_errornew(0);
        dup();string(L"signal_connect");_o_method_operation.eval(2);pop();
        dup();string(L"no proper callback for ");stringnb(cb_spec);add();_o_method_description.eval(2);pop();
        _clp_break(1);
        pop();
    }

    return callback;
}

//---------------------------------------------------------------------------

} //gobject
} //gtk

