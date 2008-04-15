
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

#include "jtelem.ch"

#ifdef NOT_DEFINED
  A jttree node-jai jttreenode objektumok.
  A jttree objektum egyúttal a gyökér node.
  A többi node-nak nincs önálló jtelem léte, 
    azaz nem az itemlistek, 
    hanem a nodelistek tárolják a fastruktúrát.

  A jttree kontroll értéke a selectedkey.
  A selectedkey azonosítójú node van kiválsztva a terminálban.
  A selectedkey beállítása kiválasztja a nodeot a terminálban.
  A selectedkey alapján kikereshető a node.
#endif

****************************************************************************
//jttree
****************************************************************************
class  jttree(jtelem,jttreenode) 

    method  initialize

    method  xmladd
    method  xmlput          {|this,x|this:selectedkey:=x:gettext}
    method  xmlget          {|this|this:selectedkey}

    method  changed         {|this|!this:laststate==this:selectedkey}
    method  savestate       {|this|this:laststate:=this:selectedkey}
    method  varput          {|this,x|this:selectedkey:=x}
    method  varget          {|this|this:selectedkey}

    method  xmlout          {|this|this:(jtelem)xmlout}

    attrib  selectedkey     //a jttree éttéke

    method  changetext      
    method  changeaddnode
    method  changeinsnode
    method  changedelnode

****************************************************************************
static function jttree.initialize(this,t,l,b,r,x) 
    if( valtype(t)=="C"  )
        this:(jtelem)initialize()
        this:(jttreenode)initialize(t)
    else
        this:(jtelem)initialize(t,l,b,r)
        this:(jttreenode)initialize(if(x==NIL,"TreeNode",x) )
    end 
    this:nodelist:={} //fastruktúra
    return this

****************************************************************************
static function jttree.xmladd(this) 
    return this:(jttreenode)xmlout

****************************************************************************
static function jttree.changetext(this,key,text)
local x,node:=this:findnode(key)
    if( node!=NIL )
        node:text:=text
        x:='<jtmessage'
        x+=ATTR("pid",alltrim(str(getpid())))
        x+=ATTR("dialogid",this:dialogid)
        x+='>'
        x+="<control>"+this:name+"</control>"
        x+="<changetext>"
        x+="<key>"+key+"</key>"
        x+="<text>"+text+"</text>"
        x+="</changetext>"
        x+="</jtmessage>"
        this:send(x)
    end

****************************************************************************
static function jttree.changeaddnode(this,key,node)
local x,parent:=this:findnode(key)

    if( NIL!=parent )
        parent:addnode(node) //a végére

        x:='<jtmessage'
        x+=ATTR("pid",alltrim(str(getpid())))
        x+=ATTR("dialogid",this:dialogid)
        x+='>'
        x+="<control>"+this:name+"</control>"
        x+="<changeaddnode>"
        x+="<key>"+key+"</key>"
        x+=node:(jttreenode)xmlout
        x+="</changeaddnode>"
        x+="</jtmessage>"
        this:send(x)
    end
    return node //ezt rakta be

****************************************************************************
static function jttree.changeinsnode(this,key,node)
local x,parent:=this:findparent(key)

    if( NIL!=parent )
        parent:addnode(node,key) //key elé

        x:='<jtmessage'
        x+=ATTR("pid",alltrim(str(getpid())))
        x+=ATTR("dialogid",this:dialogid)
        x+='>'
        x+="<control>"+this:name+"</control>"
        x+="<changeinsnode>"
        x+="<key>"+key+"</key>"
        x+=node:(jttreenode)xmlout
        x+="</changeinsnode>"
        x+="</jtmessage>"
        this:send(x)
    end
    return node //ezt rakta be

****************************************************************************
static function jttree.changedelnode(this,key)
local x,parent:=this:findparent(key),node

    if( NIL!=parent )
        node:=parent:delnode(key) //lokálisan kész
        x:='<jtmessage'
        x+=ATTR("pid",alltrim(str(getpid())))
        x+=ATTR("dialogid",this:dialogid)
        x+='>'
        x+="<control>"+this:name+"</control>"
        x+="<changedelnode>"
        x+="<key>"+key+"</key>"
        x+="</changedelnode>"
        x+="</jtmessage>"
        this:send(x)
    end
    return node //ezt törölte ki


****************************************************************************
//jttreenode
****************************************************************************
class jttreenode(object)

    attrib  key
    attrib  text
    attrib  icon
    attrib  tooltip
    attrib  nodelist

    method  initialize
    method  addnode
    method  delnode
    method  findnode
    method  findparent
    method  clone
    method  xmlout

#ifdef NOT_DEFINED

    attrib  _text_
    method  text
   
static function jttreenode.text(this,x)    
    if( x!=NIL )
        this:_text_:=x
    end
    return this:key
#endif    
    
****************************************************************************
static function nodekey()
static cnt:=0
    return "node"+alltrim(str(++cnt))

****************************************************************************
static function jttreenode.initialize(this,text)
    this:(object)initialize
    this:key:=nodekey()
    this:text:=if(text==NIL,this:key,text)
    this:nodelist:={}
    return this
    
****************************************************************************
static function jttreenode.addnode(this,node,key)
local pos
    if( key==NIL )
        //a végére
        aadd(this:nodelist,node) //a végére
    else
        //a key kulcs elé 
        pos:=ascan(this:nodelist,{|x|x:key==key})
        if( pos>0 )
            asize(this:nodelist,len(this:nodelist)+1)
            ains(this:nodelist,pos)
            this:nodelist[pos]:=node
        end
    end
    return node

****************************************************************************
static function jttreenode.delnode(this,key)
local node,pos:=ascan(this:nodelist,{|x|x:key==key})
    if( pos>0 )
        node:=this:nodelist[pos]
        adel(this:nodelist,pos)
        asize(this:nodelist,len(this:nodelist)-1)
    end
    return node

****************************************************************************
static function jttreenode.findnode(this,key)
local n,node
    if( this:key==key )
        return this
    end
    for n:=1 to len(this:nodelist)
        if( NIL!=(node:=this:nodelist[n]:findnode(key)) )
            return node
        end
    next

****************************************************************************
static function jttreenode.findparent(this,key)
local n,node
    for n:=1 to len(this:nodelist)
        if( this:nodelist[n]:key==key )
            return this
        end
    next
    for n:=1 to len(this:nodelist)
        if( NIL!=(node:=this:nodelist[n]:findparent(key)) )
            return node
        end
    next

****************************************************************************
static function jttreenode.clone(this)
local clone,n
    clone:=jttreenodeNew() //új kulcs!
    clone:text:=this:text
    clone:icon:=this:icon
    clone:tooltip:=this:tooltip
    clone:nodelist:=array(len(this:nodelist))
    for n:=1 to len(this:nodelist)
        clone:nodelist[n]:=this:nodelist[n]:clone
    next
    return clone

****************************************************************************
static function jttreenode.xmlout(this)
local n,x:=EOL+"<jttreenode>"
    x+="<key>"+this:key+"</key>"
    if( !empty(this:text) )
        x+="<text>"+cdataif(this:text)+"</text>"
    end
    if( !empty(this:icon) )
        x+="<icon>"+this:icon+"</icon>"
    end
    if( !empty(this:tooltip) )
        x+="<tooltip>"+cdataif(this:tooltip)+"</tooltip>"
    end
    for n:=1 to len(this:nodelist)
        x+=this:nodelist[n]:xmlout
    next
    x+="</jttreenode>"
    return x

****************************************************************************
