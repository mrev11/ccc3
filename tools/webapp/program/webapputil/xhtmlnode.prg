

************************************************************************************************
* xhtmlnode
************************************************************************************************
class xhtmlnode(xmlnode)

    method  addattrib    // felüldefiniálva (automatikusan készíti az xmlattrib objektumot)
    method  setattrib    // felüldefiniálva (automatikusan készíti az xmlqttrib objektumot)

    method  setstyle     // berak/felülír egy stílust
    method  delstyle     // töröl egy stílust
    method  getstyle     // kikeres egy stílust
    method  html         // node -> htmlstring
    method  htmlcontent  // node:content -> htmlstring


    method  onclick_formdata
    method  onchange_formdata
    method  onenter_formdata

    // az alábbiak azonnal küldenek,
    // tehát csak korábban feltöltött, 
    // id-vel rendelkező elemekre működnek

    method  disable      // node:disable(.t./.f.)  true-ra letiltva
    method  visible      // node:visible(.t./.f.)  true-ra látható
    method  focus
    method  update       // a megváltozott content-et elküldi a böngészőbe      


************************************************************************************************
static function xhtmlnode.addattrib(this,a,v)
    if( valtype(a)=="O" )
        this:(xmlnode)addattrib(a)
    else
        this:(xmlnode)addattrib(xhtmlnode.attrib(a,v))
    end


************************************************************************************************
static function xhtmlnode.setattrib(this,a,v)
    if( valtype(a)=="O" )
        this:(xmlnode)setattrib(a)
    else
        this:(xmlnode)setattrib(xhtmlnode.attrib(a,v))
    end


************************************************************************************************
static function xhtmlnode.setstyle(this,s)  // pl. setstyle("display:none")

local sname,x,v,n,w

    x:=ascan(this:attrib,{|a|a:name=="style"})
    if(x<=0)
        this:addattrib(xhtmlnode.attrib("style",s))
        return NIL
    end

    sname:=s[1..at(":",s)]
    if( empty(sname) )
        return NIL
    end

    v:=this:attrib[x]:value
    v:=v[2..len(v)-1]  //idézőjelek le
    v::=split(";")
   
    w:=""
    for n:=1 to len(v)
        if( 1!=at(sname,v[n]) )
            w+=v[n]+";"
        end
    end
    w+=s // új vagy felülírt stílus

    this:attrib[x]:=xhtmlnode.attrib("style",w)
    return NIL


************************************************************************************************
static function xhtmlnode.delstyle(this,s)  // pl. delstyle("display:")

local sname,x,v,n,w

    x:=ascan(this:attrib,{|a|a:name=="style"})
    if(x<=0)
        return NIL
    end

    if(!empty(s) .and. right(s,1)!=":")
        s+=":"
    end

    sname:=s[1..at(":",s)]
    if( empty(sname) )
        return NIL
    end

    v:=this:attrib[x]:value
    v:=v[2..len(v)-1]  //idézőjelek le
    v::=split(";")
   
    w:=""
    for n:=1 to len(v)
        if( 1!=at(sname,v[n]) )
            w+=v[n]+";"
        end
    end

    this:attrib[x]:=xhtmlnode.attrib("style",w)
    return NIL



************************************************************************************************
static function xhtmlnode.getstyle(this,s)  // pl. getstyle("height")

local sname,x,v,n
local p1,p2

    x:=ascan(this:attrib,{|a|a:name=="style"})
    if(x<=0)
        return NIL
    end

    if(!empty(s) .and. right(s,1)!=":")
        s+=":"
    end

    sname:=s[1..at(":",s)]
    if( empty(sname) )
        return NIL
    end

    v:=this:attrib[x]:value
    v:=v[2..len(v)-1]  //idézőjelek le
    
    if( 0<(p1:=at(sname,v)) )
        p1+=len(sname)
        if( 0<(p2:=at(";",v,p1)) )
            return v[p1..p2-1]
        else
            return v[p1..]
        end
    end

    return NIL


************************************************************************************************
function xhtmlnode.html(this) // node -> htmlstring
local html:=""
    xmlnode.html1(this,@html) 
    return html


static function xmlnode.html1(this,html) 
local n

    if( this:type=="#TEXT" )
        for n:=1 to len(this:content)
            html+=this:content[n]
        next
 
    elseif( this:type=="#CDATA" )
        for n:=1 to len(this:content)
            html+="<![CDATA["+this:content[n]+"]]>"
        next

    else
        html+=chr(10)+"<"+this:type
        for n:=1 to len(this:attrib)
            html+=chr(10)+"  "+this:attrib[n]:name+"="+this:attrib[n]:value
        next
        
        if( "."+this:type+"." $ ".p.br.input." )
            //egyes tagok elromlanak, ha üres body nélkül lezáródnak (?)
            //más tagok viszont üres bodyval rosszul pozícionálódnak
            html+="/>"
        else
            html+=">"
            for n:=1 to len(this:content)
                xmlnode.html1( this:content[n],@html )
            next
            html+="</"+this:type+">"
        end
    end


************************************************************************************************
static function xhtmlnode.htmlcontent(this)    
local html:="",n
    for n:=1 to len(this:content)
        html+=this:content[n]:html
    next
    return html


************************************************************************************************
static function xhtmlnode.disable(this,flag)
    webapp.disabled( flag, this:getattrib("id"))


************************************************************************************************
static function xhtmlnode.visible(this,flag)
    webapp.style.display( if(flag,"block","none"), this:getattrib("id"))


************************************************************************************************
static function xhtmlnode.focus(this)
    webapp.focus(this:getattrib("id"))


************************************************************************************************
static function xhtmlnode.update(this)

// olyan elemekre használható, amik korábban már 
// fel voltak töltve, és van azonosítójuk (id attrib)

    webapp.innerhtml(this:getattrib("id"),this:htmlcontent)


************************************************************************************************
* helper functions
************************************************************************************************
function xhtmlnode.attrib(a,v) // csinál egy xmlattrib objektumot

local l:=left(v,1)
local r:=right(v,1)
local q

    if( len(v)<2 )
        //nincs idézetben
    elseif( l!=r  )
        //nincs idézetben
    elseif( !l$'"'+"'"  )
        //nincs idézetben
    else
        //eleve idézetben van
        return xmlattribNew(a,v)
    end

    if( '"'$v )
        q:="'"+v+"'"
    else
        q:='"'+v+'"'
    end

    return xmlattribNew(a,q)


************************************************************************************************
function xhtmlnode.createnodehash(node) //hash {key=id,value=node} 
local hash:=simplehashNew()
    xhtmlnode.createnodehash1(node,@hash)
    return hash


static function xhtmlnode.createnodehash1(node,hash)
local id:=node:getattrib("id"),n
    if( id!=NIL )
        hash[id]:=node
    end
    for n:=1 to len(node:content)
        if( !"#"$node:content[n]:type  )
            xhtmlnode.createnodehash1(node:content[n],@hash)
        end
    next

************************************************************************************************
function xhtmlnode.option(txt,sel)  // <option> node (select-be)
local node:=xhtmlnodeNew("option")
    node:addtext(txt)
    if( !empty(sel) )
        node:addattrib(xhtmlnode.attrib("selected","selected"))
    end
    return node


************************************************************************************************
function xhtmlnode.link(href,text) // <a> node (link)
local node:=xhtmlnodeNew("a")
    node:addattrib(xhtmlnode.attrib("href",href))
    node:addtext(text)
    return node


************************************************************************************************
function xhtmlnode.createnode(type)
local node
    if( type=="table" )
        node:=xhtmltableNew()
    else
        node:=xhtmlnodeNew(type)
    end
    return node


************************************************************************************************
function xhtmlnode.onclick_formdata(node,id) //klikkre formdata-t küld
local code:="CODE.onclick_formdata(this.id)"
    if(id!=NIL)
        //ha id meg van adva, akkor az lesz az srcid
        code::=strtran('this.id',"'"+id+"'")
    end
    node:setattrib( xhtmlnode.attrib("onclick",code))


************************************************************************************************
function xhtmlnode.onchange_formdata(node,id) //változásra formdata-t küld
local code:="CODE.onclick_formdata(this.id)"
    if(id!=NIL)
        //ha id meg van adva, akkor az lesz az srcid
        code::=strtran('this.id',"'"+id+"'")
    end
    node:setattrib( xhtmlnode.attrib("onchange",code))


************************************************************************************************
function xhtmlnode.onenter_formdata(node,id) //enter leütésre formdata-t küld
local code:="CODE.evententer(event) && CODE.onclick_formdata(this.id)"
    if(id!=NIL)
        //ha id meg van adva, akkor az lesz az srcid
        code::=strtran('this.id',"'"+id+"'")
    end
    node:setattrib( xhtmlnode.attrib("onkeypress",code))

// Megjegyzés:
// A text mezőkön akkor keletkezik onchange,
// ha megváltozott tartalom mellett elhagyják a mezőt vagy entert ütnek.
// Az onenter_formdata csak enterre küldi a formdatát, 
// az onchange_formdata enterre is és a fókusz elvesztésére is küldi.


************************************************************************************************
    