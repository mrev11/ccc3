
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


#ifdef EMLEKEZTETO
  A gladewidgetNew(dom[,parent]) a DOM leírás alapján felépíti
  a derived osztályú widgetet (egyelőre nem ismer minden osztályt).
  
  Csak felső szintű widgetekre hívjuk meg közvetlenül (ilyenkor 
  parent==NIL).  A gladewidgetNew (saját maga rekurzív hívásával) 
  elkészíti a childokat is,  azaz egyszerre egy egész widget hierarchia 
  jön létre. A hierarchia minden elemében megvan ugyanaz az

    accelgroup
    tooltips
    widgettableblock
  
  attribútum. A widgettableblock alapján bármelyik widget bármely
  másik widgetet meg tud keresni id szerint a lookup metódussal:

    window:=gladewidgetNew(desc)
    button1:=window:lookup("button1")

  A child widgetek berakása a packitem metódussal történik,
  amit a gladewidget leszármazottak felüldefiniálnak, 
  ha az itteni legegyszerűbb packolási mód nem elegendő.
#endif


#include "gdk.ch"
#include "gtk.ch"
#include "gladeutil.ch"

static clid_hash:=init_clid_hash()

******************************************************************************
static function init_clid_hash()
local clid:=gladehashtableNew()

    //csak az itt definiált osztályokból építkezik

    clid:add({"GtkWindow",gladewindowClass()})
    clid:add({"GtkVBox",gladevboxClass()})
    clid:add({"GtkHBox",gladehboxClass()})
    clid:add({"GtkMenuBar",glademenubarClass()})
    clid:add({"GtkMenuItem",glademenuitemClass()})
    clid:add({"GtkMenu",glademenuClass()})
    clid:add({"GtkImageMenuItem",gladeimagemenuitemClass()})
    clid:add({"GtkSeparatorMenuItem",gladeseparatormenuitemClass()})
    clid:add({"GtkImage",gladeimageClass()})
    clid:add({"GtkCheckMenuItem",gladecheckmenuitemClass()})
    clid:add({"GtkRadioMenuItem",gladeradiomenuitemClass()})
    clid:add({"GtkVPaned",gladevpanedClass()})
    clid:add({"GtkHPaned",gladehpanedClass()})
    clid:add({"GtkHSeparator",gladehseparatorClass()})
    clid:add({"GtkVSeparator",gladevseparatorClass()})
    clid:add({"GtkScrolledWindow",gladescrolledwindowClass()})
    clid:add({"GtkTextView",gladetextviewClass()})
    clid:add({"GtkTreeView",gladetreeviewClass()})
    clid:add({"GtkStatusbar",gladestatusbarClass()})
    clid:add({"GtkTable",gladetableClass()})
    clid:add({"GtkToolbar",gladetoolbarClass()})
    clid:add({"GtkToolItem",gladetoolitemClass()})
    clid:add({"GtkToolButton",gladetoolbuttonClass()})
    clid:add({"GtkToggleToolButton",gladetoggletoolbuttonClass()})
    clid:add({"GtkRadioToolButton",gladeradiotoolbuttonClass()})
    clid:add({"GtkSeparatorToolItem",gladeseparatortoolitemClass()})
    clid:add({"GtkButton",gladebuttonClass()})
    clid:add({"GtkLabel",gladelabelClass()})
    clid:add({"GtkEntry",gladeentryClass()})
    clid:add({"GtkHButtonBox",gladehbuttonboxClass()})
    clid:add({"GtkVButtonBox",gladevbuttonboxClass()})
    clid:add({"GtkAlignment",gladealignmentClass()})
    clid:add({"GtkFrame",gladeframeClass()})
    clid:add({"GtkNotebook",gladenotebookClass()})
    clid:add({"GtkFileChooserButton",gladefilechooserbuttonClass()})
    clid:add({"GtkViewport",gladeviewportClass()})
    clid:add({"GtkHandleBox",gladehandleboxClass()})
    clid:add({"GtkComboBox",gladecomboboxClass()})
    clid:add({"GtkComboBoxEntry",gladecomboboxentryClass()})
    clid:add({"GtkCheckButton",gladecheckbuttonClass()})
    clid:add({"GtkRadioButton",gladeradiobuttonClass()})
    clid:add({"GtkSpinButton",gladespinbuttonClass()})
    clid:add({"GtkToggleButton",gladetogglebuttonClass()})
    clid:add({"GtkProgressBar",gladeprogressbarClass()})
    clid:add({"GtkDrawingArea",gladedrawingareaClass()})
    clid:add({"GtkFixed",gladefixedClass()})
    clid:add({"GtkCalendar",gladecalendarClass()})

    return clid


******************************************************************************
class gladewidget(object) new:
    attrib accelgroup
    attrib tooltips
    attrib widgettableblock
    attrib widgetid
    attrib widget_hash
    attrib packing_hash
    attrib internalchild
    method listall
    method lookup
    method packitem


******************************************************************************
function gladewidgetNew(dom,parent)

local this,clid,err
local n,node, p,prop
local gwt, childlist:={}
local acckey

    if( dom:type=="#ROOT" )
        for n:=1 to len(dom:content)
            node:=dom:content[n]
            if( node:type=="glade-interface" )
                dom:=node
                dom:type:="child"
                exit
            elseif( n==len(dom:content) )
                err:=errorNew()
                err:operation:="gladewidgetNew"
                err:description:='no <glade-interface> tag in glade document'
                break(err)
            end
        next
    end

    if( !dom:type=="child" )
        err:=errorNew()
        err:operation:="gladewidgetNew"
        err:description:='<child> tag expected'
        err:args:={dom:type}
        break(err)
    end
 
    for n:=1 to len(dom:content)
        node:=dom:content[n]

        if( node:type=="widget" )

            clid:=clid_hash:get(node:getattrib("class"))
            
            if( clid==NIL )
                //az ismeretleneket kihagyjuk
                ? "unknown class:",node:getattrib("class")
                return NIL
            end

            this:=objectNew(clid)

            if( parent==NIL )
                gwt:=gladehashtableNew()
                this:accelgroup:=gtkaccelgroupNew()
                this:tooltips:=gtktooltipsNew()    
                this:widgettableblock:={||gwt}
            else
                this:accelgroup:=parent:accelgroup
                this:tooltips:=parent:tooltips
                this:widgettableblock:=parent:widgettableblock
            end

            this:widgetid:=node:getattrib("id")
            if( eval(this:widgettableblock):get(this:widgetid)!=NIL )
                err:=errorNew()
                err:operation:="gladewidgetNew"
                err:description:='multiple widgetid'
                err:args:={this:widgetid}
                break(err)
            end
            eval(this:widgettableblock):add({this:widgetid,this})
            this:widget_hash:=gladehashtableNew(16)
            this:packing_hash:=gladehashtableNew(16)
            this:internalchild:=dom:getattrib("internal-child")

            for p:=1 to len(node:content)
                prop:=node:content[p]
                if( prop:type=="property" )
                    this:widget_hash:add({prop:getattrib("name"),prop:gettext})

                elseif( prop:type=="accelerator" )
                    acckey:=this:widget_hash:get("accelerator")
                    if( acckey==NIL )
                        this:widget_hash:add({"accelerator",acckey:={}})
                    end
                    aadd(acckey,{prop:getattrib("key"),prop:getattrib("modifiers"),prop:getattrib("signal")})

                elseif( prop:type=="signal" )
                    //kihagy

                elseif( prop:type=="child" )
                    aadd(childlist,gladewidgetNew(prop,this)) //rekurzió
                end
            next

        elseif(node:type=="packing")

            for p:=1 to len(node:content)
                prop:=node:content[p]
                if( prop:type=="property" )
                    this:packing_hash:add({prop:getattrib("name"),prop:gettext})
                end
            next

        elseif(node:type=="placeholder")
            //this:=objectNew(gladelabelClass())
            //this:gobject:=gtk.label.new("placeholder")
            this:=objectNew(gladevboxClass())
            this:gobject:=gtk.vbox.new()
            //this:widget_hash:=gladehashtableNew(2)
            this:packing_hash:=gladehashtableNew(2)
            //this:widgetid:="placeholder"
            return this
        end
    next

    if( this==NIL )
        //placeholder (nincs benne <widget> tag)
        return NIL
    end


    //? "widget_hash", this:classname    
    //this:widget_hash:list
    //? "packing_hash"    
    //this:packing_hash:list
        
    this:initialize //mostantól van benne gobject
    
    init_accelerator(this)
    init_tooltip(this)
    init_border_width(this)
    init_can_focus(this)
    init_size_request(this)

    for n:=1 to len(childlist)
        if( NIL!=childlist[n] )
            this:packitem( childlist[n] )
            childlist[n]:packing_hash:=NIL //már nem kell
        end
    next

    this:widget_hash:=NIL //már nem kell

    return this


******************************************************************************
static function init_accelerator(this)

local acckey,n
local key,mod,sig
local visible:=1//GTK_ACCEL_VISIBLE

    if( (acckey:=this:widget_hash:get("accelerator"))!=NIL )
        for n:=1 to len(acckey)
            key:=acckey[n][1]
            mod:=acckey[n][2]
            sig:=acckey[n][3]
            this:add_accelerator(sig,this:accelgroup,gladekeysym_to_gdkkeysym(key),gtksym(mod),visible)
        next
    end

#ifdef EMEKEZTETO
  Az ilyenek kiértékelésére való gtksym:
  <accelerator key="P" modifiers="GDK_CONTROL_MASK | GDK_SHIFT_MASK | GDK_MOD1_MASK" signal="activate"/>
#endif


******************************************************************************
static function init_tooltip(this)
local item:=this:widget_hash:get("tooltip")
    if( item!=NIL )
        this:tooltips:set_tip(this,item)
    end

******************************************************************************
static function init_border_width(this)
local item:=this:widget_hash:get("border_width")
    if( item!=NIL )
        this:set_border_width(val(item))
    end

******************************************************************************
static function init_can_focus(this)
local item:=this:widget_hash:get("can_focus")
    if( item!=NIL )
        if( FLAG1(item) )
            this:set_flags(GTK_CAN_FOCUS)
        else
            this:unset_flags(GTK_CAN_FOCUS)
        end
    end


******************************************************************************
static function init_size_request(this)
local x:=this:widget_hash:get("width_request")
local y:=this:widget_hash:get("height_request")
    if( x!=NIL .or. y!=NIL )
        x:=VAL2(x,-1)
        y:=VAL2(y,-1)
        this:set_size_request(x,y)
    end


******************************************************************************
static function gladewidget.listall(this)
local hash,n,id,wo
    hash:=eval(this:widgettableblock):hasharray
    for n:=1 to len(hash)
        if( hash[n]!=NIL )
            id:=hash[n][1]
            wo:=hash[n][2]
            ? str(n,4), padr(id,32), if(this==wo,">"," "), wo:classname
        end
    next

******************************************************************************
static function gladewidget.packitem(this,w)
    if( w:internalchild=="image" )
        this:set_image(w) //<child internal-child="image">
    else
        this:add(w)
    end

******************************************************************************
static function gladewidget.lookup(this,id)
local err,item:=eval(this:widgettableblock):get(id)
    if( item==NIL )
        err:=errorNew()
        err:operation:="gladewidget.lookup"
        err:description:="widget not found"
        err:args:={id}
        break(err)
    end
    return item


******************************************************************************
