
//Ez nem ugyanaz, mint ami a wutil-ban van.
//Ki vannak hagyva azok a metódusok, amik a kódgeneráláshoz nem kellenek,
//de egy csomó dolgot behúznának a linkeléskor.


************************************************************************************************
* xhtmlnode
************************************************************************************************
class xhtmlnode(xmlnode)

    method  addattrib    // felüldefiniálva (automatikusn készíti az xmlattrib objektunot)
    method  setattrib    // felüldefiniálva (automatikusn készíti az xmlattrib objektunot)

    method  setstyle     // berak/felülír egy stílust
    method  delstyle     // töröl egy stílust
    method  getstyle     // kikeres egy stílust
    method  html         // node -> htmlstring
    method  htmlcontent  // node:content -> htmlstring


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
* xhtmltable
************************************************************************************************
class xhtmltable(xhtmlnode)
    
    attrib  colinfo

    method  initialize
    method  addcolumn
    method  addrow

    method  thead           {|this|this:content[1]}
    method  tbody           {|this|this:content[2]}
    method  tfoot           {|this|this:content[3]}

************************************************************************************************
static function xhtmltable.initialize(this,id)

    this:(xhtmlnode)initialize("table")
    
    this:addcontent( xhtmlnodeNew("thead") )
    this:addcontent( xhtmlnodeNew("tbody") )
    this:addcontent( xhtmlnodeNew("tfoot") )
    
    this:colinfo:={}

    this:setattrib( xhtmlnode.attrib("cellspacing","0") )
    this:setattrib( xhtmlnode.attrib("cellpadding","5") )
    this:setattrib( xhtmlnode.attrib("width","100%") )
    this:setattrib( xhtmlnode.attrib("border","0") )
    
    if( id!=NIL )
        this:setattrib( xhtmlnode.attrib("id",id) )
    end

    return this


************************************************************************************************
static function xhtmltable.addcolumn(this,h,p,s)
local colinfo,th

    if( valtype(h)=="O" )
        colinfo:=h  //kész colinfo objektum
    else
        colinfo:=xhtmltable.colinfoNew(h,p,s)
    end
    this:colinfo::aadd(colinfo)
    
    th:=xhtmlnodeNew("th")
    th:addtext(colinfo:header)
    this:thead:addcontent(th)
    
    return colinfo


************************************************************************************************
static function xhtmltable.addrow(this,row)
local tr,rowcnt,rowid,td,n

    tr:=xhtmlnodeNew("tr")
    this:tbody:addcontent(tr)
    rowcnt:=this:tbody:content::len
    rowid:="ROWID"+rowcnt::str::alltrim

    tr:setattrib( xhtmlnode.attrib("id",rowid) )
    tr:setattrib( xhtmlnode.attrib("class",if(rowcnt%2==0,"even","odd" )))
    tr:setattrib( xhtmlnode.attrib("onclick","XCODE.onclick_row(this)"))

    for n:=1 to len(row)
        td:=xhtmlnodeNew("td")
        tr:addcontent(td)
        
        if( this:colinfo[n]:picture==NIL )
            td:addtext(row[n])
        else
            td:addtext(row[n]::transform(this:colinfo[n]:picture) )
        end
        if( this:colinfo[n]:style!=NIL )
            td:setattrib( xhtmlnode.attrib("style",this:colinfo[n]:style) )
        end
    next


************************************************************************************************
class xhtmltable.colinfo(object)
    attrib  header
    attrib  picture
    attrib  style
    method  initialize

static function xhtmltable.colinfo.initialize(this,h,p,s)
    this:header :=h
    this:picture:=p
    this:style  :=s
    return this


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
local code:="XCODE.onclick_formdata(this.id)"
    if(id!=NIL)
        //ha id meg van adva, akkor az lesz az srcid
        code::=strtran('this.id',"'"+id+"'")
    end
    node:setattrib( xhtmlnode.attrib("onclick",code))


************************************************************************************************
function xhtmlnode.onchange_formdata(node,id) //változásra formdata-t küld
local code:="XCODE.onclick_formdata(this.id)"
    if(id!=NIL)
        //ha id meg van adva, akkor az lesz az srcid
        code::=strtran('this.id',"'"+id+"'")
    end
    node:setattrib( xhtmlnode.attrib("onchange",code))


************************************************************************************************
function xhtmlnode.onenter_formdata(node,id) //enter leütésre formdata-t küld
local code:="XCODE.evententer(event) && XCODE.onclick_formdata(this.id)"
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
    