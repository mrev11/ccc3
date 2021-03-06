
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

#include "directry.ch"

namespace webapp

#define MENUWIDTH 140
#define FSMARGIN    4

************************************************************************************************
//page
************************************************************************************************
class page(xhtmlnode)

    method  initialize

    attrib  menu             // <div.menu>      főmenü az oldal bal szélén, egymás alatti gombok
    attrib  formset          // <div.formset>   amiben a caption, tabbuttonok es formok vannak
    attrib  caption          // <div.caption>   az oldal címe
    attrib  tabbut           // <div.tabbut>    a látható formot kiválasztó buttonok
    attrib  form             // <div.form>      amiben a formok vannak, egyszerre egy látható
    attrib  action           // <div.action>    a formok alatt vizszintesen sorakozó gombok
    attrib  status           // <div.status>    a formok alatt egy üres hely üzenetek számára
    
    method  setcaption
    method  addmenu
    method  addpdmenu
    method  addsubmenu
    method  addform
    method  addaction
    attrib  actionhash
    method  setstatus        {|t,x|webapp.innerhtml(t:status:getattrib("id"),x)}

    method  switch_to_form
    attrib  active_form
    
    attrib  formdata         // minden formdata message frissíti
    attrib  cargo            // tetszőleges adat

    attrib  nodehash         // hash a kontrollokból, item={id,ctrl}, nem feltétlenül uptodate
    method  createnodehash   {|this|this:nodehash:=xhtmlnode.createnodehash(this)}
    method  get              :nodehash:get

    attrib  cacheable
    attrib  restorekey             
    method  uploaded         {|this|this:restorekey!=NIL}
    method  upload
    method  update           :upload
    method  reload           //kicsereli a fa egy reszfajat

    attrib  closed           //mutatja, hogy ki kell lepni a loop-bol
    method  close            {|this|this:closed:=.t.} 
    attrib  msgtimeout       //getmessage-nek atadott timeout millisec


    method  onclick_formdata
    method  onchange_formdata
    method  onenter_formdata

    method  input_date
    method  input_number
    method  input_picture
    method  input_pattern
    method  input_accountnumber

    method  input_datepicker
    method  input_combo
    method  input_selbox

    method  loop
    

************************************************************************************************
static function page.initialize(this,caption)

    this:(xhtmlnode)initialize("div","class=page")

    this:createnodehash
    this:cacheable:=.t.    
    this:uploaded:=.f.
    this:actionhash:=simplehashNew()
    this:formdata:=webapp.formdataNew(xmlnodeNew())  //egy üres formdata


    //HTML structure

    this:menu:=xhtmlnodeNew("div","class=menu"/*,"style=display:none"*/)
    this:addcontent(this:menu)
    
    this:formset:=xhtmlnodeNew("div","class=formset")
    this:addcontent(this:formset)

    this:caption:=xhtmlnodeNew("div","class=caption")
    this:formset:addcontent(this:caption)
    if( caption!=NIL )
        this:caption:addcontent(xhtmlnodeNew("#TEXT"))
        this:caption:content[1]:addcontent(caption)
        //itt a '<' karakterek escapelése ki van kerülve
        //ezert a caption lehet pl. <h3>text</h3>
        //(ez egy trükk? vagy rendben van)
    end

    this:tabbut:=xhtmlnodeNew("div","class=tabbut","style=display:none")
    this:formset:addcontent(this:tabbut)

    this:form:=xhtmlnodeNew("div","class=form")
    this:formset:addcontent(this:form)

    this:action:=xhtmlnodeNew("div","class=action","style=display:none")
    this:formset:addcontent(this:action)

    this:status:=xhtmlnodeNew("div","class=status")
    this:formset:addcontent(this:status)

    return this


#ifdef NOTDEFINED
A page xhtmlnode-ok szerkezete:

<div class="page">

    <div class="menu">
        <br/><input.../><br/><input.../> ...
    </div>

    <div class=formset>
        <div class=caption>captxt</div>
        <div class="tabbut"><input.../><input.../> ...</div>
        <div class="form">
            <div id="formid1"><fieldset.../></div> 
            <div id="formid2"><fieldset.../></div> 
            ... 
        </div>
        <div class="action"><input.../><input.../>...</div>
        <div id="status"></div>
    </div>
</div>
#endif


************************************************************************************************
static function page.setcaption(this,caption)
    this:caption:content::asize(0)
    this:caption:addcontent(xhtmlnodeNew("#TEXT"))
    this:caption:content[1]:addcontent(caption)


************************************************************************************************
static function page.addmenu(this,id,value,title,blk)
local button
    if( valtype(id)=="O" )
        button:=id  //kész objektum
    else
        button:=menubuttonNew(id,value,title)
    end
    this:menu:addcontent(button)
    if(blk!=NIL)
        this:actionhash["formdata."+id]:=blk
    end
    //this:menu:setstyle("display:block")


************************************************************************************************
static function page.addpdmenu(this,id,value,title)
local button
    if( valtype(id)=="O" )
        button:=id
    else
        button:=pdmenubuttonNew(id,value,title)
    end
    this:menu:addcontent(button)
    //this:menu:setstyle("display:block")


************************************************************************************************
static function page.addsubmenu(this,id,value,title,blk)
local button
    if( valtype(id)=="O" )
        button:=id //kész objektum
    else
        button:=submenubuttonNew(id,value,title)
    end
    this:menu:addcontent(button) 
    if(blk!=NIL)
        this:actionhash["formdata."+id]:=blk
    end


************************************************************************************************
static function page.addaction(this,id,value,title,blk)
local button
    if(  valtype(id)=="O" )
        button:=id //kész objektum
    else
        button:=buttonNew(id,value,title)
    end
    this:action:addcontent(button)
    if(blk!=NIL)
        this:actionhash["formdata."+id]:=blk
    end
    this:action:setstyle("display:block")


************************************************************************************************
static function page.addform(this,form)
local fid,bid,but,item

    fid:=form:getattrib("id")
    form:setattrib("class","subform")
    this:form:addcontent(form)

    form:pageblk:={||this}
    if( form:actionhash!=NIL )
        //atveszi az ideiglenes tarolobol
        item:=form:actionhash:first
        while( item!=NIL )
            this:actionhash[item[1]]:=item[2]
            item:=form:actionhash:next
        end
        form:actionhash:=NIL //nem kell tobbet
    end
    
    if( this:form:content::len==1 )
        this:active_form:=fid
    end

    if( form:tabtext!=NIL )
        bid:=fid::strtran("form_","tabbut_")
        but:=tabbuttonNew(bid,form:tabtext)
        this:tabbut:addcontent(but)
        this:tabbut:setstyle("display:block")
    end


************************************************************************************************
static function page.switch_to_form(this,fid)
local disp:={},n,idn
local push:={},buttxt,butidn,butid
    disp::aadd("none")
    push::aadd(.f.)
    for n:=1 to len(this:form:content)
        idn:=this:form:content[n]:getattrib("id")
        buttxt:=this:form:content[n]:tabtext
        butidn:=if(buttxt==NIL,NIL,idn::strtran("form_","tabbut_"))
        if( !idn==fid )
            disp::aadd(idn)
            if( butidn!=NIL )
                push::aadd(butidn)
            end
        else
            butid:=butidn
        end
    next
    disp::aadd("block")
    disp::aadd(fid)
    evalarray({|*|webapp.style.display(*)},disp)
    if( butid!=NIL )
        push::aadd(.t.)
        push::aadd(butid)
    end
    if( len(push)>1 )
        evalarray({|*|webapp.data.pushed(*)},push)
    end
    this:active_form:=fid


************************************************************************************************
static function page.upload(this)
local pageid

    pageid:=pageid()
    this:restorekey:=pageid+time()
    webapp.savedisplay(this:restorekey) 
    webapp.emptydisplay()
    //webapp.unrefdisplay() //nem javit (ezzel is villog) 

    if( !this:cacheable )
        webapp.uploaddisplay(this:html)
    elseif( !webapp.xlib.isdefined(pageid) )
        webapp.uploaddisplay(this:html)
        webapp.xlib.save_innerHTML(pageid,"display_webapp")
    else
        webapp.xlib.set_innerHTML("display_webapp",pageid)
    end

************************************************************************************************
static function page.reload(this,node)

local nodeid
local nodeobj

    if( valtype(node)=="C" )
        nodeid:=node
        nodeobj:=this[nodeid]
    else
        nodeobj:=node
        nodeid:=node:getattrib("id") 
    end

    webapp.innerhtml(nodeid,nodeobj:htmlcontent) //csereli a belsejet
     

************************************************************************************************
static function pageid()
local pageid,pn,pl,n:=2
    pageid:=dati_of_exe()
    while( !empty(pn:=procname(n)) ) 
        pl:=procline(n)::any2str::alltrim
        pageid+=pn+"("+pl+")"
        n++
    end 
    pageid+=argv(0)
    return pageid  


************************************************************************************************
static function dati_of_exe() //az exe linkelési dátumideje
local pid:=getpid()::str::alltrim
local dir:=directory("/proc/"+pid+"/exe","L")
    return dir[1][F_DATE]::dtos+dir[1][F_TIME]::strtran(":","") 


************************************************************************************************
static function page.onclick_formdata(this,ctrlid,blk)
    this[ctrlid]:onclick_formdata
    this:actionhash["formdata."+ctrlid]:=blk

static function page.onchange_formdata(this,ctrlid,blk)
    this[ctrlid]:onchange_formdata
    this:actionhash["formdata."+ctrlid]:=blk

static function page.onenter_formdata(this,ctrlid,blk)
    this[ctrlid]:onenter_formdata
    this:actionhash["formdata."+ctrlid]:=blk


************************************************************************************************
static function page.input_date(this,ctrlid)
    this[ctrlid]:input_date

static function page.input_number(this,ctrlid,dec,flags)
    this[ctrlid]:input_number(dec,flags)

static function page.input_picture(this,ctrlid,pic)
    this[ctrlid]:input_picture(pic)

static function page.input_pattern(this,ctrlid,pat)
    this[ctrlid]:input_pattern(pat)

static function page.input_accountnumber(this,ctrlid,opt)
    this[ctrlid]:input_accountnumber(opt)


************************************************************************************************
static function page.input_datepicker(this,ctrlid)
local inp:=this[ctrlid]::webapp.input_datepicker() //elromlik a nodehash  
    this:nodehash[ctrlid]:=inp //megjavitja

static function page.input_combo(this,ctrlid,table)
local inp:=this[ctrlid]::webapp.input_combo(table) //elromlik a nodehash  
    this:nodehash[ctrlid]:=inp //megjavitja

static function page.input_selbox(this,ctrlid,table)
local inp:=this[ctrlid]::webapp.input_selbox(table) //elromlik a nodehash  
    this:nodehash[ctrlid]:=inp //megjavitja


************************************************************************************************
static function page.loop(this)

local msg,data,blk
local n,menuid,visible

    if( !this:uploaded )
        //menti a kepernyot 
        //megorzi a visszallitashoz szukseges kulcsot
        //feltölti az oldalt (mint stringet innerHTML-be)
        //kezeli az objektum cache-t
        //tudja, ha mar futott (csak egyszer fut)
        //a loop elott kulon is hivhato

        this:upload  
    end

    this:formdata:update
    
    if( this:active_form!=NIL )
        //lehet, hogy nincs egy form sem
        this:switch_to_form(this:active_form)
    end

    this:closed:=.f.
    while( !this:closed ) 
        msg:=webapp.getmessage(@data,this:msgtimeout)
        //? "MESSAGE:", msg

        if( msg==NIL )
            //a kapcsolat megszakadt
            //leggyakoribb ok, hogy kiléptek a böngészőből
            exit

        elseif( msg::empty  )
            //lejárt a timeout
            //leggyakoribb ok, hogy a user inaktiv
            
            if( NIL!=(blk:=this:actionhash["msgtimeout"]) )
                eval(blk,this)
                this:formdata:update
            else
                exit
            end
        
        elseif( NIL!=(blk:=this:actionhash[msg]) )
            if( msg::startswith("formdata.") )
                this:formdata:=data
            end
            eval(blk,this,data)  
            this:formdata:update

        elseif( msg=="tabbutton" )
            this:switch_to_form( data:gettext::strtran("tabbut_","form_") )

        elseif( msg=="pdbutton" )
            visible:={}
            for n:=1 to len(this:menu:content)
                menuid:=this:menu:content[n]:getattrib("id")
                if( menuid==data:gettext )
                    //pdmenu, amin klikkeltek
                    if( !this:menu:content[n]:visible )
                        this:menu:content[n]:visible:=.t.
                        visible::aadd("block")
                    else
                        this:menu:content[n]:visible:=.f.
                        visible::aadd("none")
                    end

                elseif( this:menu:content[n]:classname=="webapp.pdmenubutton" )
                    //pdmenu, masik
                    this:menu:content[n]:visible:=.f.
                    visible::aadd("none")

                elseif( this:menu:content[n]:classname=="webapp.submenubutton" )
                    //submenu
                    visible::aadd(menuid)
     
                end
            next
            evalarray({|*|webapp.style.display(*)},visible)

        end
    end

    webapp.restoredisplay(this:restorekey)
    this:restorekey:=NIL
    
    return msg //az utolso message

    //(NIL)     magszakadt a kapcsolat
    //(empty)   lejart a msgtimeout es nem volt megadva akcio
    //(other)   az akcio bezarta a page-et

************************************************************************************************
//form
************************************************************************************************
class form(xhtmlnode)
    method  initialize
    method  upload
    attrib  tabtext
    
    attrib  formaction
    attrib  actionhash
    method  addformaction

    attrib  pageblk
    method  page            {|this| if(this:pageblk==NIL,NIL,eval(this:pageblk))}

static function form.initialize(this,formid,fieldset,tabtext)
    this:(xhtmlnode)initialize("div")
    if( fieldset!=NIL )
        //üres is lehet
        this:addcontent(fieldset)
        if( fieldset:content::len>=1 .and. fieldset:content[1]:type=="legend" )
            fieldset:content[1]:setattrib("id","legend_"+formid)
        end
    end
    this:addattrib(xhtmlnode.attrib("id","form_"+formid))
    this:setstyle("display:none") //nem látható
    this:tabtext:=tabtext
    return this


static function form.upload(this)
    webapp.innerhtml(this:getattrib("id"),this:htmlcontent)


static function form.addformaction(this,id,value,title,blk)
    if( this:formaction==NIL )
        this:formaction:=xhtmlnodeNew("div","class=formaction")
        this:content::aadd(this:formaction)
    end
    if(  valtype(id)=="O" )
        this:formaction:addcontent(id) //kész objektum
    else
        this:formaction:addcontent(buttonNew(id,value,title))
    end
    if( blk!=NIL )
        if( this:page==NIL )
            // ideiglenes tárolás
            if( this:actionhash==NIL )
                this:actionhash:=simplehashNew()
            end
            this:actionhash["formdata."+id]:=blk
        else
            this:page:actionhash["formdata."+id]:=blk
        end
    end


************************************************************************************************
//button
************************************************************************************************
class button(xhtmlnode)
    method  initialize

static function button.initialize(this,id,value,title)
    this:(xhtmlnode)initialize("input")
    this:addattrib(xhtmlnode.attrib("type","button"))
    this:addattrib(xhtmlnode.attrib("id",id))
    this:addattrib(xhtmlnode.attrib("value",value))
    this:addattrib(xhtmlnode.attrib("onclick","XCODE.onclick_formdata(this.id)"))
    if( title!=NIL  )
        this:addattrib(xhtmlnode.attrib("title",title))
    end
    return this


************************************************************************************************
//menubutton
************************************************************************************************
class menubutton(webapp.button)
    method  initialize

static function menubutton.initialize(this,id,value,title)
    this:(webapp.button)initialize(id,value,title)
    this:addattrib(xhtmlnode.attrib("class","menubutton"))
    this:setstyle("display:block")
    return this


************************************************************************************************
//tabbutton
************************************************************************************************
class tabbutton(webapp.button)
    method  initialize

static function tabbutton.initialize(this,id,value,title)
local msg:="<tabbutton>ID</tabbutton>"::strtran("ID",id)::webapp.jsstring
    this:(webapp.button)initialize(id,value,title)
    this:addattrib(xhtmlnode.attrib("class","tabbutton"))
    this:setattrib(xhtmlnode.attrib("onclick","XCODE.echo(MSG)"::strtran("MSG",msg)))
    return this


************************************************************************************************
//pdmenubutton (pulldown)
************************************************************************************************
class pdmenubutton(webapp.button)
    attrib  visible
    method  initialize

static function pdmenubutton.initialize(this,id,value,title)
local msg:="<pdbutton>ID</pdbutton>"::strtran("ID",id)::webapp.jsstring
    //this:(webapp.button)initialize(id,"["+value+"]",title)
    this:(webapp.button)initialize(id,value+" »",title)
    this:addattrib(xhtmlnode.attrib("class","pdmenubutton"))
    this:setattrib(xhtmlnode.attrib("onclick","XCODE.echo(MSG)"::strtran("MSG",msg)))
    this:setstyle("display:block")
    this:visible:=.f.
    return this

    //e29dae ❮
    //e29daf ❯
    //2039 ‹
    //203a ›
    //171 «
    //187 »


************************************************************************************************
//submenubutton
************************************************************************************************
class submenubutton(webapp.button)
    method  initialize

static function submenubutton.initialize(this,id,value,title)
    this:(webapp.button)initialize(id,value,title)
    this:addattrib(xhtmlnode.attrib("class","submenubutton"))
    this:setstyle("display:none")
    return this


************************************************************************************************
