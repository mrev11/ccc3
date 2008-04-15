
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


****************************************************************************
class gtkdef(object)

    method initialize
    method list
    method clist

    attrib isfunction        //.t., ha define-function
    attrib ismethod          //.t., ha define-method
    attrib ccc_api           //CCC-API név (így hívjuk kívülről)
    attrib c_api             //C-API név (ezt hívjuk belül)
    attrib isconstructor     //.t., ha is-constructor-of
    attrib clname            //osztálynév, pl. GtkButtonBox/NIL
    attrib modname           //modulnév, pl. gtk_button_box

    attrib return_type
    attrib return_option
    attrib parameters
    attrib varargs
    attrib deprecated
    attrib caller_owns_return

    attrib ccc
    attrib state
    attrib codeblock
    attrib comment


****************************************************************************
static function gtkdef.initialize(this,x)

local i,j,a

    this:(object)initialize

    this:isfunction:=(x[1]=="define-function")
    this:ismethod:=(x[1]=="define-method")
    this:ccc_api:=x[2]
    this:isconstructor:=.f.
    this:parameters:={}
    this:return_type:="none" 
    this:return_option:=""
    this:state:=""
    this:ccc:=""
    this:comment:=""

    for i:=3 to len(x)
        a:=x[i]
        if( valtype(a)=="A" )

            if( a[1]=="is-constructor-of")
                this:clname:=a[2]
                this:isconstructor:=.t.
 
            elseif( a[1]=="of-object")
                this:clname:=a[2]
 
            elseif( a[1]=="in-module")
                this:clname:=a[2]
 
            elseif( a[1]=="c-name" )
                this:c_api:=a[2]
 
            elseif( a[1]=="return-type" )
                this:return_type:=a[2]
                if( len(a)>=3 ) 
                    this:return_option:=a[3] 
                end

            elseif( a[1]=="parameters" )
                this:parameters:=a
                adel(a,1)
                asize(a,len(a)-1)

            elseif( a[1]=="varargs" )
                this:varargs:=a[2]
 
            elseif( a[1]=="deprecated" )
                this:deprecated:=a[2]
 
            elseif( a[1]=="caller-owns-return" )
                this:caller_owns_return:=a[2]
 
            elseif( a[1]=="CCC" )
                this:ccc:=a[2]
 
            elseif( a[1]=="codeblock" )
                this:codeblock:=a[2]
 
            elseif( a[1]=="comment" )
                for j:=2 to len(a)
                    this:comment+=a[j]+endofline()
                next
            else
                alert("Unknown attribute", any2str(a) )
                ? x
                ? a
                quit
            end
        end
    next
    
    this:state:=state(this)
    
    if( empty(this:state) )
        //Nem generálunk kódot, ha state nem üres
    
        this:modname:=modulespec(this)

        //Metódusoknál a név NEM tartalmazza a gtk_class_ prefixet,
        //konstruktoroknál a név tartalmazza a gtk_class_ prefixet,
        //utóbbiaknál ezt most levágjuk, és ellenőrizzük az egyezést.
        
        if( this:isconstructor )
            if( 1!=at(this:modname+"_",this:ccc_api) )
                alert("Inconsistent constructor name: "+this:ccc_api)
                quit
            end
            this:ccc_api:=strtran(this:ccc_api,this:modname+"_","")

        elseif( this:isfunction )
            if( 1!=at(this:modname+"_",this:ccc_api) )
            
                if( ".funcname." $ debuginfo() )
                    set alternate to inkonz.bak additive
                    set alternate on
                    set console off
                    ? padr(this:modname,20), padr(this:ccc_api,32), this:c_api
                    set alternate to
                    set alternate off
                    set console off
                end
            end
            this:ccc_api:=strtran(this:ccc_api,this:modname+"_","")
        end
    end

    if( this:ismethod )
        //A metódusoknál eredetileg nincs bevéve a paraméterek
        //közé a self, most betesszük az első helyre

        if( this:parameters==NIL )
            this:parameters:={}
        end
        asize(this:parameters,len(this:parameters)+1)
        ains(this:parameters,1)
        this:parameters[1]:={ this:clname+"*", "self"  }
    end

    return this

****************************************************************************
static function state(this)
local x:=""

    if( this:clname==NIL )
        x+="O"  //nincs meghatározva az osztály
    end

    if( !empty(this:deprecated) )
        x+="D"  //Deprecated
    end

    if( !lower(left(this:c_api,4))=="gtk_" )
        x+="G"  //nem Gtk
    end

    if( this:varargs!=NIL )
        x+="V"  //Varargs
    end

    //if(  this:caller_owns_return!=NIL )
    //    x+="R"  //caller owns Return
    //end


    return x

****************************************************************************
static function modulespec(o)
local x:=o:clname

    x:=strtran(x,"HB","_hb")  //HButton, HBox
    x:=strtran(x,"HP","_hp")  //HPaned
    x:=strtran(x,"HR","_hr")  //HRuler
    x:=strtran(x,"HS","_hs")  //HSeparator

    x:=strtran(x,"VB","_vb")
    x:=strtran(x,"VP","_vp")
    x:=strtran(x,"VR","_vr")
    x:=strtran(x,"VS","_vs")

    x:=strtran(x,"IMC","_im_c")
    x:=strtran(x,"IMM","_im_m")

    return lower(macroname(x))  //pl. gtk_button_box


****************************************************************************
static function gtkdef.clist(this)
    ? "//", this:clname
    if( this:isconstructor )
        ?? " constructor "
    elseif( this:ismethod )
        ?? " method "
    else
        ?? " function "
    end
    ?? this:ccc_api

****************************************************************************
static function gtkdef.list(this)
local i

    this:clist
    ? "//  c_name      ", this:c_api
    ? "//  return      ", this:return_type,this:return_option
    
    //if( !empty(this:return_option) )
    //    ?? "",this:return_option
    //end
    
    if( !empty(this:parameters) )
        for i:=1 to len(this:parameters)
            ? padr("//  param-"+alltrim(str(i)),16), this:parameters[i]
        next
    else
        ? "//  parameters  ", this:parameters
    end

    if( !empty(this:ccc) )
        ? "//  ccc         ", this:ccc
    end

    if( !empty(this:state) )
        ? "//  state       ", this:state
    end

    if( !empty(this:varargs) )
        ? "//  varargs     ", this:varargs
    end

    if( !empty(this:deprecated) )
        ? "//  deprecated  ", this:deprecated
    end

    if( !empty(this:caller_owns_return) )
        ? "//  caller_owns ", this:caller_owns_return
    end


****************************************************************************
