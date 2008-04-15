
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


DEFINE_METHOD(operation);
DEFINE_METHOD(description);

namespace _nsp_gtk {
namespace _nsp_gobject {

static  const char *type_i=".gint.guint.GEnum.";
static  const char *type_d=".gdouble.gfloat.";
static  const char *type_b=".gboolean.";
static  const char *type_s=".gchararray.";
static  const char *type_p=".GBoxed.GObject.";
static  const char *type_v=".void.";

//---------------------------------------------------------------------------
const char *partype(gpointer wdg, char *propname, int mode)
{
    int get=(mode&G_PARAM_READABLE);
    int set=(mode&G_PARAM_WRITABLE);

    GParamSpec *pspec;
    pspec=g_object_class_find_property(G_OBJECT_GET_CLASS(wdg),propname);
    
    if( pspec==0 )
    {
        //ERROR: nincs ilyen property
        
        _clp_errornew(0);
        dup();string(get?L"get_property":L"set_property");_o_method_operation.eval(2);pop();
        dup();string(L"unknown property: ");stringn0(propname);add();_o_method_description.eval(2);pop();
        _clp_break(1);
        pop();
    }
    else if( get && ((pspec->flags&G_PARAM_READABLE)==0) )
    {
        //ERROR: nem olvasható

        _clp_errornew(0);
        dup();string(L"get_property");_o_method_operation.eval(2);pop();
        dup();string(L"not readable");_o_method_description.eval(2);pop();
        _clp_break(1);
        pop();
    }
    else if( set && ((pspec->flags&G_PARAM_WRITABLE)==0) )
    {
        //ERROR: nem írható
        _clp_errornew(0);
        dup();string(L"set_property");_o_method_operation.eval(2);pop();
        dup();string(L"not writable");_o_method_description.eval(2);pop();
        _clp_break(1);
        pop();
    }
    
    //printf("%s.%s(%s)\n", G_OBJECT_TYPE_NAME(wdg), propname, g_type_name(G_TYPE_FUNDAMENTAL(pspec->value_type)));
    
    return g_type_name(G_TYPE_FUNDAMENTAL(pspec->value_type));
}

//---------------------------------------------------------------------------
void _clp_set_property(int argno)
{
    CCC_PROLOG("gtk.gobject.set_property",3);
    gpointer o=_parp(1);
    gchar *prop=_parc_utf8(2);
    VALUE *value=_par(3);
    
    char ptype[128];
    sprintf(ptype,".%s.",partype(o,prop,G_PARAM_WRITABLE));
    
    if( strstr(type_i,ptype) ) //int
    {
        gint value=_parni(3);
        g_object_set(o,prop,value,NULL);
    }
    else if( strstr(type_d,ptype) ) //double
    {
        double value=_parnd(3);
        g_object_set(o,prop,value,NULL);
    }
    else if( strstr(type_s,ptype) ) //string
    {
        gchar *value=_parc_utf8(3);
        g_object_set(o,prop,value,NULL);
    }
    else if( strstr(type_b,ptype) ) //boolean
    {
        gint value=_parl(3)?1:0;
        g_object_set(o,prop,value,NULL);
    }
    else if( strstr(type_p,ptype) ) //pointer
    {
        gpointer value=_parp(3);
        g_object_set(o,prop,value,NULL);
    }
    else
    {
        //ERROR: ismeretlen típus
        _clp_errornew(0);
        dup();string(L"set_property");_o_method_operation.eval(2);pop();
        dup();string(L"unknown type: ");stringnb(ptype);add();_o_method_description.eval(2);pop();
        _clp_break(1);
        pop();
    }
    _ret();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_get_property(int argno)
{
    CCC_PROLOG("gtk.gobject.get_property",2);
    gpointer o=_parp(1);
    gchar *prop=_parc_utf8(2);
    
    char ptype[128];
    sprintf(ptype,".%s.",partype(o,prop,G_PARAM_READABLE));

    if( strstr(type_i,ptype) ) //int
    {
        gint value;
        g_object_get(o,prop,&value,NULL);
        _retni(value);
    }
    else if( strstr(type_d,ptype) ) //double
    {
        double value;
        g_object_get(o,prop,&value,NULL);
        _retnd(value);
    }
    else if( strstr(type_s,ptype) ) //string
    {
        gchar *value;
        g_object_get(o,prop,&value,NULL);
        stringn0(value);
        _rettop();
    }
    else if( strstr(type_b,ptype) ) //boolean
    {
        gint value;
        g_object_get(o,prop,&value,NULL);
        _retl(value);
    }
    else if( strstr(type_p,ptype) ) //pointer
    {
        GObject *value;
        g_object_get(o,prop,&value,NULL);
        pointer(value);
        _rettop();
    }
    else
    {
        //ERROR: ismeretlen típus
        _clp_errornew(0);
        dup();string(L"get_property");_o_method_operation.eval(2);pop();
        dup();string(L"unknown type: ");stringnb(ptype);add();_o_method_description.eval(2);pop();
        _clp_break(1);
        pop();
    }
    _ret();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------

} //gobject
} //gtk

