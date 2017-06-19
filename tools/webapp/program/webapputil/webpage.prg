
namespace webapp

#define MENUWIDTH 140
#define FSMARGIN    4

************************************************************************************************
//page
************************************************************************************************
class page(xhtmlnode)

    attrib  caption          // <#TEXT>, az oldal címe
    attrib  menu             // <div>, főmenü az oldal bal szélén, egymás alatti gombok
    attrib  form             // <div>, amiben a formok vannak, egyszerre egy látható
    attrib  tabbut           // <div>, a látható formot kiválasztó buttonok
    attrib  action           // <div>, a formok alatt vizszintesen sorakozó gombok
    attrib  status           // <div>, a formok alatt egy üres hely üzenetek számára

    attrib  menuid           // azonosítók listája
    attrib  formid           // azonosítók listája
    
    attrib  actionhash
    
    method  initialize
    method  addmenu
    method  addpdmenu
    method  addsubmenu
    method  addform
    method  addaction
    method  setstatus        {|t,x|webapp.innerhtml(t:status:getattrib("id"),x)}
                             

    method  switch_to_form
    attrib  active_form
    
    attrib  formdata         // minden formdata message frissíti
    attrib  formcheck        // formdata:checksum-ot tárolja a változás detektálásához
    method  savecheck        // kiszámítja formcheck-et
    method  verifycheck      // ellenőrzi a változást  (sajnos ez nem jó, mindig jelez)

    attrib  nodehash         // hash a kontrollokból, item={id,ctrl}, nem feltétlenül uptodate
    
    attrib  cargo            // tetszőleges adat
    attrib  initblock        // page:loop értékeli ki az oldal feltöltés után, de a loop előtt

    method  createnodehash   {|this|this:nodehash:=xhtmlnode.createnodehash(this)}

    method  upload           {|this| webapp.uploaddisplay(this:html)} //az egészet elküldi
    method  update           :upload

    method  loop
    

************************************************************************************************
static function page.initialize(this,caption)
local fs

    this:(xhtmlnode)initialize("div")

    this:createnodehash

    this:menuid:={}
    this:formid:={}
    
    this:actionhash:=simplehashNew()

    this:formdata:=webapp.formdataNew(xmlnodeNew())  //egy üres formdata

    this:menu:=xhtmlnodeNew("div")
    this:addcontent(this:menu)
    this:menu:addattrib( xhtmlnode.attrib("class","menu") )
    this:menu:setstyle("float:left;margin-top:64")
    
    fs:=xhtmlnodeNew("fieldset")
    fs:setstyle("border:0;margin-left:FORMMARGIN"::strtran("FORMMARGIN",(MENUWIDTH+FSMARGIN)::str::alltrim)  )
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
    elseif( id=="quit" )
        button:=quitbuttonNew(id,value,title)
    elseif( id=="close" )
        button:=closebuttonNew(id,value,title)
    else
        button:=menubuttonNew(id,value,title)
    end
    this:menuid::aadd(button:getattrib("id"))
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
    this:menuid::aadd(button:getattrib("id"))
    this:menu:addcontent(button)


************************************************************************************************
static function page.addsubmenu(this,id,value,title,blk)
local button
    if( valtype(id)=="O" )
        button:=id //kész objektum
    else
        button:=submenubuttonNew(id,value,title)
    end
    this:menuid::aadd(button:getattrib("id"))
    this:menu:addcontent(button) 
    if(blk!=NIL)
        this:actionhash["formdata."+id]:=blk
    end


************************************************************************************************
static function page.addform(this,form)
local fid,bid,but

    fid:=form:getattrib("id")
    this:form:addcontent(form)
    this:formid::aadd(fid)
    
    if( this:form:content::len==1 )
        form:visible:=.t.
        this:active_form:=fid
    end

    if( this:form:content::len>1 .and. form:visible )
        this:form:content[1]:visible:=.f.
        this:active_form:=fid
    end

    if( form:tabtext!=NIL )
        bid:=fid::strtran("form_","tabbut_")  //pl. form_formid_szer -> tabbut_formid_szer
        but:=tabbuttonNew(bid,form:tabtext)
        this:tabbut:addcontent(but)
        this:actionhash["tabbutton."+bid]:={||this:switch_to_form(fid)}
    end


************************************************************************************************
static function page.switch_to_form(this,fid)
local par:={},n
    par::aadd("none")
    for n:=1 to len(this:formid)
        if( !this:formid[n]==fid )
            par::aadd(this:formid[n])
        end
    next
    par::aadd("block")
    par::aadd(fid)
    evalarray({|*|webapp.style.display(*)},par)
    this:active_form:=fid


************************************************************************************************
static function page.addaction(this,id,value,title)
    if(  valtype(id)=="O" )
        this:action:content::aadd(id) //kész objektum
    else
        this:action:addcontent(buttonNew(id,value,title))
    end


************************************************************************************************
static function page.loop(this)

local data,msg,tab,blk,res,item
local key:="page"+gettickcount()::str::alltrim
local n,pdx,visible

    webapp.savedisplay(key) 
    webapp.emptydisplay()
    this:upload  //feltölti az oldalt (mint stringet innerHTML-be)

    if( this:initblock!=NIL )
        eval(this:initblock,this)
    end

    while( NIL!=(msg:=webapp.getmessage(@data)) )
        //? "MESSAGE:", msg

        if( msg::startswith("formdata.") )
            
            if( msg=="formdata.quit" )
                if( webapp.alert("Kilép a programból?",{"Mégsem","Kilép"})==2 )
                    webapp.innerhtml("display","<h3>Köszönjük, hogy használta a programot</h3>")
                    quit
                end
            end

            //data:list

        elseif( msg=="tabbutton" )
            tab:=data:gettext  //pl. tabbut_formid_szer (a button id-je)
            //item:=this:actionhash:first
            //while( item!=NIL )
            //    ? item
            //    item:=this:actionhash:next
            //end
            blk:=this:actionhash["tabbutton."+tab]
            if( blk!=NIL )
                eval(blk,tab::strtran("tabbut_","form_"))
            end

        elseif( msg=="pdbutton" )
            visible:={}
            pdx:=ascan(this:menuid,{|id|id==data:gettext})
            for n:=1 to len(this:menu:content)
                if( this:menu:content[n]:classname=="webapp.pdmenubutton" )
                    if( n==pdx ) 
                        if( !this:menu:content[pdx]:visible )
                            this:menu:content[pdx]:visible:=.t.
                            visible::aadd("block")
                        else
                            this:menu:content[pdx]:visible:=.f.
                            visible::aadd("none")
                        end
                    else
                        this:menu:content[n]:visible:=.f.
                        visible::aadd("none")
                    end
                elseif( this:menu:content[n]:classname=="webapp.submenubutton" )
                    visible::aadd(this:menuid[n])
                end
            next
            evalarray({|*|webapp.style.display(*)},visible)
            
        elseif( msg=="close" )
            if( webapp.alert("Bezárja az oldalt?",{"Mégsem","Bezár"})==2 )
                exit  //kilép a page:loop-ból
            end

        elseif( msg=="quit" )
            if( webapp.alert("Kilép a programból?",{"Mégsem","Kilép"})==2 )
                webapp.innerhtml("display","<h3>Köszönjük, hogy használta a programot</h3>")
                quit //kilép a programból
            end

        elseif( msg=="html" )
            //az oldal aktuális HTML tartalma (debug célra)
            memowrit("debug.html","<html>"+data:gettext+"</html>")
        end
        
        res:=NIL
        blk:=this:actionhash[msg]
        if( blk!=NIL )

            //res:=eval(blk,data)
            //!!!! változás 2012.08.30 
            //data helyett this az argumentum, this:formdata-ban van a korábbi data

            this:formdata:=data
            res:=eval(blk,this)  

            if( res::valtype=="B" )
                exit //kilép a page:loop-ból
            end
        end

        //Érdemes ezt iderakni?
        if( msg::startswith("formdata.") )
            data:update
        end
    end
    
    webapp.restoredisplay(key)
    
    if( res::valtype=="B" )
        eval(res,data)
    end


************************************************************************************************
static function page.savecheck(this)
    return this:formcheck:=this:formdata:checksum

************************************************************************************************
static function page.verifycheck(this)
    return this:formcheck==this:formdata:checksum
    
    // Sajnos ez nem jó, 
    // szinte mindig eltérést jelez,
    // mert nem lehet megkülönböztetni az üres
    // és az inicializálatlan értékeket,
    // egyelőre nem látok megoldást,
    // nem érdemes erőltetni.

************************************************************************************************
//form
************************************************************************************************
class form(xhtmlnode)
    method  initialize
    method  visible
    method  upload
    attrib  tabtext
    
    attrib  formaction
    method  addformaction


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

static function form.visible(this,visible)
local prev:=this:getstyle("display")
    if( visible!=NIL )
        this:setstyle("display:VISIBLE"::strtran("VISIBLE",if(visible,"block","none")))
    end
    return !prev=="none"


static function form.upload(this)
    webapp.innerhtml(this:getattrib("id"),this:htmlcontent)


static function form.addformaction(this,id,value,title)
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
//quitbutton
************************************************************************************************
class quitbutton(webapp.menubutton)
    method  initialize

static function quitbutton.initialize(this,id,value,title)
local msg:="<quit/>"::webapp.jsstring
    this:(webapp.menubutton)initialize(id,value,title)
    this:setattrib(xhtmlnode.attrib("onclick","CODE.echo(MSG)"::strtran("MSG",msg)   ))
    return this


************************************************************************************************
//closebutton
************************************************************************************************
class closebutton(webapp.menubutton)
    method  initialize

static function closebutton.initialize(this,id,value,title)
local msg:="<close/>"::webapp.jsstring
    this:(webapp.menubutton)initialize(id,value,title)
    this:setattrib(xhtmlnode.attrib("onclick","CODE.echo(MSG)"::strtran("MSG",msg)   ))
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
//htmldebugbutton
************************************************************************************************
class htmldebugbutton(webapp.button)
    method  initialize

static function htmldebugbutton.initialize(this,id:="html",value:="Print HTML",title:="Kiírja az oldal aktuális HTML tartalmát")
local code:="CODE.send('<html>'+CODE.cdata(CODE.webapp.display.innerHTML)+'</html>')"
    this:(webapp.button)initialize(id,value,title)
    this:setattrib(xhtmlnode.attrib("onclick",code))
    return this

************************************************************************************************







