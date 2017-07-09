
#include "directry.ch"

namespace webapp

#define MENUWIDTH 140
#define FSMARGIN    4

************************************************************************************************
//page
************************************************************************************************
class page(xhtmlnode)

    method  initialize

    attrib  caption          // <#TEXT>, az oldal címe
    attrib  menu             // <div>, főmenü az oldal bal szélén, egymás alatti gombok
    attrib  form             // <div>, amiben a formok vannak, egyszerre egy látható
    attrib  tabbut           // <div>, a látható formot kiválasztó buttonok
    attrib  action           // <div>, a formok alatt vizszintesen sorakozó gombok
    attrib  status           // <div>, a formok alatt egy üres hely üzenetek számára
    
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

    attrib  cacheable
    attrib  restorekey             
    method  uploaded         {|this|this:restorekey!=NIL}
    method  upload
    method  update           :upload

    attrib  closed           //mutatja, hogy ki kell lepni a loop-bol
    method  close            {|this|this:closed:=.t.} 
    attrib  msgtimeout       //getmessage-nek atadott timeout millisec

    method  loop
    

************************************************************************************************
static function page.initialize(this,caption)
local fs

    this:(xhtmlnode)initialize("div")

    this:createnodehash
    this:cacheable:=.t.    
    this:uploaded:=.f.
    
    this:actionhash:=simplehashNew()

    this:formdata:=webapp.formdataNew(xmlnodeNew())  //egy üres formdata

    this:menu:=xhtmlnodeNew("div")
    this:addcontent(this:menu)
    this:menu:addattrib( xhtmlnode.attrib("class","menu") )
    this:menu:setstyle("float:left;margin-top:64")
    
    fs:=xhtmlnodeNew("fieldset")
    //nem kell a margin-left
    //fs:setstyle("border:0;margin-left:FORMMARGIN"::strtran("FORMMARGIN",(MENUWIDTH+FSMARGIN)::str::alltrim)  )
    fs:setstyle("border:0;")
    this:addcontent(fs)

    this:caption:=xhtmlnodeNew("#TEXT")
    if( caption!=NIL )
        this:caption:addcontent(caption)
    end
    fs:addcontent(this:caption)
    
    this:tabbut:=xhtmlnodeNew("div")
    this:tabbut:addattrib( xhtmlnode.attrib("class","tabbut") )
    fs:addcontent(this:tabbut)

    fs:addcontent(xhtmlnodeNew("p"))

    this:form:=xhtmlnodeNew("div")
    this:form:addattrib( xhtmlnode.attrib("class","form") )
    fs:addcontent(this:form)

    fs:addcontent(xhtmlnodeNew("p"))

    this:action:=xhtmlnodeNew("div")
    this:action:addattrib( xhtmlnode.attrib("class","action") )
    fs:addcontent(this:action)

    fs:addcontent(xhtmlnodeNew("p"))

    this:status:=xhtmlnodeNew("div")
    this:status:addattrib( xhtmlnode.attrib("class","status") )
    this:status:addattrib( xhtmlnode.attrib("id","status") )
    fs:addcontent(this:status)

    return this


#ifdef NOTDEFIND //ez a szerkezete
<div>
    <div class="menu">
        <br/><input.../><br/><input.../> ...
    </div>
    <fieldset>
        caption-text
        <div class="tabbut"><input.../><input.../> ... <p/></div>
        <p/>
        <div class="form"><div id="formid"><fieldset.../></div> ... </div>
        <p/>
        <div class="action"><input.../><input.../>...</div>
        <div id="status"></div>
    </fieldset>
</div>
#endif

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


************************************************************************************************
static function page.addpdmenu(this,id,value,title)
local button
    if( valtype(id)=="O" )
        button:=id
    else
        button:=pdmenubuttonNew(id,value,title)
    end
    this:menu:addcontent(button)


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


************************************************************************************************
static function page.addform(this,form)
local fid,bid,but,item

    fid:=form:getattrib("id")
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
    end


************************************************************************************************
static function page.switch_to_form(this,fid)
local par:={},n,idn
local push:={},buttxt,butidn,butid
    par::aadd("none")
    push::aadd(.f.)
    for n:=1 to len(this:form:content)
        idn:=this:form:content[n]:getattrib("id")
        buttxt:=this:form:content[n]:tabtext
        butidn:=if(buttxt==NIL,NIL,idn::strtran("form_","tabbut_"))
        if( !idn==fid )
            par::aadd(idn)
            if( butidn!=NIL )
                push::aadd(butidn)
            end
        else
            butid:=butidn
        end
    next
    par::aadd("block")
    par::aadd(fid)
    evalarray({|*|webapp.style.display(*)},par)
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

    if( !this:cacheable )
        webapp.uploaddisplay(this:html)
    elseif( !webapp.xlib.isdefined(pageid) )
        webapp.uploaddisplay(this:html)
        webapp.xlib.save_innerHTML(pageid,"display")
    else
        webapp.xlib.set_innerHTML("display",pageid)
    end

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
    this:switch_to_form(this:active_form)

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
            eval(blk,this)  
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
    end
    this:addattrib(xhtmlnode.attrib("id","form_"+formid))
    this:setstyle("display:none") //nem látható
    this:tabtext:=tabtext
    return this


static function form.upload(this)
    webapp.innerhtml(this:getattrib("id"),this:htmlcontent)


static function form.addformaction(this,id,value,title,blk)
    if( this:formaction==NIL )
        this:formaction:=xhtmlnodeNew("div")
        this:formaction:setattrib("class","formaction")
        this:content::aadd(xhtmlnodeNew("p"))
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
    this:addattrib(xhtmlnode.attrib("onclick","CODE.onclick_formdata(this.id)"))
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
    this:addattrib(xhtmlnode.attrib("class","menu"))
    this:setstyle("width:MENUWIDTH"::strtran("MENUWIDTH",MENUWIDTH::str::alltrim))
    this:setstyle("margin:6 4 0 4;display:block")
    return this


************************************************************************************************
//tabbutton
************************************************************************************************
class tabbutton(webapp.button)
    method  initialize

static function tabbutton.initialize(this,id,value,title)
local msg:="<tabbutton>ID</tabbutton>"::strtran("ID",id)::webapp.jsstring
    this:(webapp.button)initialize(id,value,title)
    this:setattrib(xhtmlnode.attrib("onclick","CODE.echo(MSG)"::strtran("MSG",msg)))
    return this


************************************************************************************************
//pdmenubutton (pulldown)
************************************************************************************************
class pdmenubutton(webapp.menubutton)
    attrib  visible
    method  initialize

static function pdmenubutton.initialize(this,id,value,title)
local msg:="<pdbutton>ID</pdbutton>"::strtran("ID",id)::webapp.jsstring
    this:(webapp.menubutton)initialize(id,"["+value+"]",title)
    this:setattrib(xhtmlnode.attrib("onclick","CODE.echo(MSG)"::strtran("MSG",msg)))
    this:visible:=.f.
    return this


************************************************************************************************
//submenubutton
************************************************************************************************
class submenubutton(webapp.menubutton)
    method  initialize

static function submenubutton.initialize(this,id,value,title)
    this:(webapp.menubutton)initialize(id,value,title)
    this:setstyle("border:0;margin:0 4 0 4;display:none")
    return this


************************************************************************************************
