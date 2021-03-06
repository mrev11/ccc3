
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

************************************************************************************************
* xhtmlnode
************************************************************************************************
class xhtmlnode(xmlnode)

    method  initialize

    method  addattrib    // felüldefiniálva (automatikusan készíti az xmlattrib objektumot)
    method  setattrib    // felüldefiniálva (automatikusan készíti az xmlattrib objektumot)

    method  setstyle     // berak/felülír egy stílust
    method  delstyle     // töröl egy stílust
    method  getstyle     // kikeres egy stílust
    method  html         // node -> htmlstring
    method  htmlcontent  // node:content -> htmlstring


    method  onclick_formdata
    method  onchange_formdata
    method  onenter_formdata

    method  input_date
    method  input_number
    method  input_picture
    method  input_accountnumber
    method  input_pattern

    method  clear        {|this|this:content::asize(0)}

    // az alábbiak azonnal küldenek,
    // tehát csak korábban feltöltött, 
    // id-vel rendelkező elemekre működnek

    method  disable      // node:disable(.t./.f.)  true-ra letiltva
    method  visible      // node:visible(.t./.f.)  true-ra látható
    method  focus
    method  update       // a megváltozott content-et elküldi a böngészőbe      

************************************************************************************************
static function xhtmlnode.initialize(this,type,*)
local attr:={*[3..]},n,a
    this:(xmlnode)initialize(type)
    for n:=1 to len(attr)
        a:=attr[n]
        a::=split("=")
        if( '"'$a[2]  )
            this:addattrib(a[1],"'"+a[2]+"'")
        else
            this:addattrib(a[1],'"'+a[2]+'"')
        end
    next
    return this


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
            //html+="<![CDATA["+this:content[n]+"]]>"
            //a böngészők commentnek értelmezik a CDATA-t!
            html+=this:content[n]::webapp.htmlstring
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
local hash:=nodehashNew(node)
    xhtmlnode.createnodehash1(node,hash)
    return hash


static function xhtmlnode.createnodehash1(node,hash)
local id:=node:getattrib("id"),n
    if( id!=NIL .and. !'ROWID'$id )
        hash[id]:=node
    end
    for n:=1 to len(node:content)
        if( !"#"$node:content[n]:type  )
            xhtmlnode.createnodehash1(node:content[n],hash)
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
    node:setattrib( xhtmlnode.attrib("onkeyup",code))

// Megjegyzés:
// A text mezőkön akkor keletkezik onchange,
// ha megváltozott tartalom mellett elhagyják a mezőt vagy entert ütnek.
// Az onenter_formdata csak enterre küldi a formdatát, 
// az onchange_formdata enterre is és a fókusz elvesztésére is küldi.


************************************************************************************************
function xhtmlnode.input_date(node)
local onblur:=node:getattrib("onblur")
    if(onblur==NIL)
        onblur:=""
    end
    node:setattrib("onfocus","XCODE.edit_in_progress(this)")
    node:setattrib("onblur","XCODE.datsettlevalue(this);"+onblur)
    node:setattrib("onkeypress","XCODE.datkeypress(event)")
    node:setattrib("pattern","^[0-9]{4}-[0-9]{2}-[0-9]{2}$")


************************************************************************************************
function xhtmlnode.input_number(node,dec,flags:='r')
local code:="XCODE.numsettlevalue(this,DEC,ZERO);"
local onblur:=node:getattrib("onblur")
    if(onblur==NIL)
        onblur:=""
    end

    if( dec!=NIL )
        code::=strtran("DEC",dec::str::alltrim)
    end
    if( 'z'$flags )
        code::=strtran("ZERO","'blank'")
    end
    code::=strtran(",ZERO","")
    code::=strtran("DEC","null")
    code::=strtran(",null)",")")

    node:setattrib("onfocus","XCODE.edit_in_progress(this)")
    node:setattrib("onblur",code+onblur) 
    node:setattrib("onkeypress","XCODE.numkeypress(event)")
    node:setattrib("pattern","^[0-9\+\-\.,]*$")

    if( "r"$flags )
        node:setstyle("text-align:right")
    elseif( "l"$flags )
        node:setstyle("text-align:left")
    elseif( "c"$flags )
        node:setstyle("text-align:center")
    else
        node:setstyle("text-align:right")
    end


************************************************************************************************
function xhtmlnode.input_picture(node,pic)
local onblur:=node:getattrib("onblur")
    if(onblur==NIL)
        onblur:=""
    end

    node:setattrib("onfocus","XCODE.edit_in_progress(this)")
    node:setattrib("onblur","XCODE.picsettlevalue(this);"+onblur) 
    node:setattrib("onkeypress","XCODE.pickeypress(event)") 
    node:setattrib("data-picture",pic)


************************************************************************************************
function xhtmlnode.input_pattern(node,pat)
local onblur:=node:getattrib("onblur")
    if(onblur==NIL)
        onblur:=""
    end

    if( !left(pat,1)=="^" )
        pat:="^"+pat
    end
    if( !right(pat,1)=="$" )
        pat+="$"
    end
    node:setattrib("onfocus","XCODE.edit_in_progress(this)")
    node:setattrib("onblur","XCODE.patsettlevalue(this);"+onblur)
    node:setattrib("onkeypress","XCODE.patkeypress(event)") 
    node:setattrib("pattern",pat)


************************************************************************************************
function xhtmlnode.input_accountnumber(node,opt:="FUA")
local pic:=""
    if( "F"$opt ); pic+="-99999999"; end
    if( "U"$opt ); pic+="-NNNNNNNN"; end
    if( "A"$opt ); pic+="-00000000"; end
    pic::=substr(2)
    xhtmlnode.input_picture(node,pic)
    node:setstyle("font-family:monospace")


************************************************************************************************
static class xhtmlnode.nodehash(simplehash)

    method  initialize

    attrib  nodeblk     //a node, aminek az elemei a hash-ben vannak
                        //a rekurzio elkerulese erdekeben blokkban

    method  node        {|this|eval(this:nodeblk)}  
    
    method  get         //feluldefinialva
                        //ha eloszor nem talal, ujrageneralja a hash-t
                        //ha akkor sem talal, kivetelt dob


static function xhtmlnode.nodehash.initialize(this,node)
    this:(simplehash)initialize
    this:nodeblk:={||node}
    return this
    

static function xhtmlnode.nodehash.get(this,key)
local err,val
    if( NIL==(val:=this:(simplehash)get(key)) )
        xhtmlnode.createnodehash1(this:node,this)
        if( NIL==(val:=this:(simplehash)get(key)) )
            err:=apperrorNew()
            err:operation:="nodehash.get"
            err:description:="Undefined node ID"
            err:args:={key}
            break(err)
        end
    end
    return val


************************************************************************************************
    