
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

static modules:={}

****************************************************************************
function nsclose(this)
local modspec,m

    for m:=1 to len(modules)
        modspec:=modules[m]
        set printer to (sourcefile(modspec)) additive
        set printer on
        ? funsep()
        ? "}//"+nspace(modspec)
        ? "}//"+"gtk"
        ?
    next

****************************************************************************
function codegen_api(this)

    if( "API"$this:ccc .or. empty(this:state) .and. empty(this:ccc) )
        if( 0==ascan(modules,{|x|x==this:modname}) )
            aadd(modules,this:modname)
            set printer to (sourcefile(this:modname))
            set printer on
            ? "#include <gdk/gdk.h>"
            ? "#include <gtk/gtk.h>"
            ? "#include <cccapi.h>"
            ? "#include <cccgtk.h>"
            ?
            ? "namespace _nsp_gtk{"
            ? "namespace _nsp_"+nspace(this:modname)+"{"
            ?
        end

        set printer to (sourcefile(this:modname)) additive
        set printer on
        codegen1(this)
        ?
        set printer off
    end

****************************************************************************
static function codegen1(this)

local func:=<<func>>
void _clp_FUNCDEF_NAME(int argno)
{
    CCC_PROLOG("PUSHCALL_NAME",PARCNT);
    GETPAR
    GTKCALL
    RETURN
    CCC_EPILOG();
}<<func>>

local p, par, gtkcall, ret, retstat, push

    ? funsep()
    this:list
    
    func:=strtran(func,chr(13),"")
    func:=strtran(func,"FUNCDEF_NAME",funcdef_name(this))
    func:=strtran(func,"PUSHCALL_NAME",pushcall_name(this))
    func:=strtran(func,"PARCNT",alltrim(str(len(this:parameters))))
    
    for p:=1 to len(this:parameters)
        func:=strtran(func,"GETPAR",getpar(this,p)+chr(10)+"    GETPAR")
    next
    func:=strtran(func,chr(10)+"    GETPAR","")

    gtkcall:=this:c_api+"("
    for p:=1 to len(this:parameters)
        gtkcall+=if(p>1,",","")
        gtkcall+=typed_name(this:parameters[p][1],this:parameters[p][2])
    next
    gtkcall+=")"

    if( this:return_type=="none" )
        gtkcall+=";"
        retstat:="_ret();"

    else
        gtkcall:=par_type(this:return_type)+" ret="+gtkcall+";"

        if( "array"$this:return_option )

            push:="push"
        
            if( this:return_type=="GSList*" )
                push+="_gslist"
            elseif( this:return_type=="GList*" )
                push+="_glist"
            end

            if( ".carray."$this:return_option )
                push+="_c"
            elseif( ".parray."$this:return_option )
                push+="_p"
            end

            if( ".freelist."$this:return_option )
                push+="_freelist"
            end
            if( ".freedata."$this:return_option )
                push+="_freedata"
            end

            retstat:=push+"(ret);_rettop();"

        else
            ret:=ret_ret(this:return_type)
            if( ret=="_retc" )
                retstat:=ret+"_utf8((char*)ret);"
                if( ".free."$this:return_option )
                    retstat+="g_free(ret);"
                end
            else
                retstat:=ret+"("+ret_cast(this:return_type)+"ret);"
            end
        end
    end

    func:=strtran(func,"GTKCALL",gtkcall)
    func:=strtran(func,"RETURN",retstat)

    ? func

****************************************************************************
static function sourcefile(modspec)
    return codedir()+dirsep()+modspec+"_api.cpp"

****************************************************************************
static function nspace(modspec)
    return lower(substr(modspec,5))  //gtk_...

****************************************************************************
static function funsep()
    return "//"+replicate("-",78)

****************************************************************************
static function funcdef_name(this)
    return this:ccc_api //sok a hiba a gtk.defs-ben!

****************************************************************************
static function pushcall_name(this)
    return lower(strtran(this:modname,"gtk_","gtk.") +"."+funcdef_name(this))

****************************************************************************
static function getpar(this,idx)
local par:=this:parameters[idx]
local type:=par[1]
local name:=par[2]
local x

    x:=par_type(type)+" "+name+"="+par_isnil(par,idx)+par_cast(type)+par_par(type,idx)+";"
    return x

****************************************************************************
static function par_isnil(par,idx)

local isnil:=""
local default
local template:="ISNIL(IDX)?DEFAULT:"

    if( len(par)>2 )
        if( par[3][1]=="null-ok" )
            template:=strtran(template,"IDX",alltrim(str(idx)))
            template:=strtran(template,"DEFAULT","0")
            isnil:=template

        elseif( par[3][1]=="default" )

            default:=par_cast(par[1])+"("+par[3][2]+")"
        
            template:=strtran(template,"IDX",alltrim(str(idx)))
            template:=strtran(template,"DEFAULT",default)
            template:=strtran(template,"TRUE","1")
            template:=strtran(template,"FALSE","0")
            isnil:=template
        end
    end
    return isnil

****************************************************************************
static function par_type(type)  // [type] par = (cast) _par();

local const:="const-"$type
    if(const)
        type:=strtran(type,"const-","")
    end

    if( type_macro(type)!=NIL )
        type:="gpointer"
    end
    return  if(const,"const ","")+type

****************************************************************************
static function par_cast(type)  // type par = [(cast)] _par();

local cast:=""
local const:="const-"$type
    if(const)
        type:=strtran(type,"const-","")
    end

    if( type_macro(type)!=NIL )
    elseif(type=="gint")
    elseif(type=="gint16")
    elseif(type=="guint")
    elseif(type=="guint16")
    elseif(type=="guint32")
    elseif(type=="char*".and. const)
        cast:="char*"
    elseif(type=="gchar*".and. const)
        cast:="gchar*"
    elseif(type=="guchar*")
        cast:="guchar*"
    elseif(type=="gboolean")
    elseif(type=="gfloat")
    elseif(type=="gdouble")
    elseif( isupper(left(type,1)) )
        cast:=type
    else
        set alternate to extra_types.bak additive
        set alternate on
        set printer off
        ? type
        set printer on
        set alternate off
    end
    
    if( !empty(cast) )
        cast:=if(const,"(const ","(")+type+")"
    end
    
    return cast

#ifdef ILYENEK_IS_VANNAK

    char*
    gboolean*
    gchar**
    gdouble*
    gfloat*
    gint*
    gpointer
    guint*
    guint16*
    gunichar
    va_list

    Ezekhez csak kézzel lehet interfészt írni.
#endif

****************************************************************************
static function par_par(type,idx)  // type par = (cast) [_par(x);]

local par:=""

    type:=strtran(type,"const-","")

    if( type_macro(type)!=NIL )
        par:="_parp"

    elseif(type=="gint")
        par:="_parni"

    elseif(type=="gint16")
        par:="_parni"

    elseif(type=="guint")
        par:="_parnu"

    elseif(type=="guint16")
        par:="_parnu"

    elseif(type=="guint32")
        par:="_parnu"

    elseif(type=="char*")
        par:="_parc"

    elseif(type=="gchar*")
        par:="_parc"

    elseif(type=="guchar*")
        par:="_parc"

    elseif(type=="gboolean")
        par:="_parl"

    elseif(type=="gfloat")
        par:="_parnd"

    elseif(type=="gdouble")
        par:="_parnd"

    elseif( type=="gpointer" )
        par:="_parp"

    elseif( type=="GType" )
        par:="_parp"

    elseif( type=="GtkType" )
        par:="_parp"

    elseif( isupper(left(type,1)) )
        if( right(type,1)=="*"  )
            par:="_parp"
        else
            par:="_parnu"
        end

    else
        set alternate to extra_types.bak additive
        set alternate on
        set printer off
        ? type
        set printer on
        set alternate off
        alert(type)
    end
    
    if( par=="_parl" )
        par:="(0!="+par+"("+alltrim(str(idx))+"))"
    elseif( par=="_parc" )    
        //par+="_utf8("+alltrim(str(idx))+",base,argno)"
        par+="_utf8("+alltrim(str(idx))+")"
    else
        par+="("+alltrim(str(idx))+")"
    end

    return par

****************************************************************************
static function ret_ret(type)  //[_ret]( (cast)ret );

local ret
local const:="const-"$type

    if(const)
        type:=strtran(type,"const-","")
    end

    if( type_macro(type)!=NIL )
        ret:="_retp"

    elseif(type=="gint")
        ret:="_retni"

    elseif(type=="gint16")
        ret:="_retni"

    elseif(type=="guint")
        ret:="_retni"

    elseif(type=="guint16")
        ret:="_retni"

    elseif(type=="guint32")
        ret:="_retni"

    elseif(type=="char*")
        ret:="_retc"

    elseif(type=="gchar*")
        ret:="_retc"

    elseif(type=="guchar*")
        ret:="_retc"

    elseif(type=="gboolean")
        ret:="_retl"

    elseif(type=="gfloat")
        ret:="_retnd"

    elseif(type=="gdouble")
        ret:="_retnd"

    elseif( type=="gpointer" )
        ret:="_retp"

    elseif( type=="GType" )
        ret:="_retp"

    elseif( type=="GtkType" )
        ret:="_retp"

    elseif( isupper(left(type,1)) )
        if( right(type,1)=="*"  )
            ret:="_retp"
        else
            ret:="_retni"
        end

    else
        set alternate to extra_types.bak additive
        set alternate on
        set printer off
        ? type
        set printer on
        set alternate off
    end

    return ret

****************************************************************************
static function ret_cast(type)  //_ret( [(cast)]ret );

local cast:=""

    type:=strtran(type,"const-","")

    if( type_macro(type)!=NIL )
    elseif(type=="gint")
    elseif(type=="gint16")
    elseif(type=="guint")
        cast:="(int)"
    elseif(type=="guint16")
        cast:="(int)"
    elseif(type=="guint32")
        cast:="(int)"
    elseif(type=="char*")
    elseif(type=="gchar*")
    elseif(type=="guchar*")
        cast:="(char*)"
    elseif(type=="gboolean")
    elseif(type=="gfloat")
    elseif(type=="gdouble")
    elseif( type=="GType" )
        cast:="(void*)"
    elseif( type=="GtkType" )
        cast:="(void*)"
    elseif( isupper(left(type,1)) )
        cast:="("+type+")"
    else
        set alternate to extra_types.bak additive
        set alternate on
        set printer off
        ? type
        set printer on
        set alternate off
    end
    return cast

****************************************************************************
