
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
 
****************************************************************************
//jtdialog
****************************************************************************
class jtdialog(jtelem) 

    method  initialize

    attrib  pid                 // process id
    attrib  layout              // fix,vbox,hbox,flow
    attrib  defaultradiogroup   // radiogroup
    attrib  parser              // xml parser
    attrib  mustreact           // must answer the last action
    attrib  _blklist_           // these have block (hash table)
    attrib  _blkcount_          // items in blklist
    attrib  _varlist_           // these have name (hash table)
    attrib  _varcount_          // items in varlist
    attrib  var                 // _varlist_ as an object

    method  caption             {|this,x|if(x==NIL,this:text,this:text:=x)}
    method  list
    method  getcontrolbyname
    method  add
    method  xmlout
    method  send                {|this,x|jtsocket():send(x)}
    method  recv                {|this,wtime|jtsocket():recv(wtime)}
    method  show
    method  exit
    method  close
    method  getmessage
    method  response 
    method  alert

    method  blklist
    method  varlist
    method  varinst


****************************************************************************
static function jtdialog.initialize(this,t,l,b,r) 
static dialogid:=0
    if(t==NIL.and.l==NIL.and.b==NIL.and.r==NIL)
        t:=0
        l:=0
        b:=16
        r:=64
    end
    this:(jtelem)initialize(t,l,b,r)
    this:itemlist:={}
    this:pid:=alltrim(str(getpid()))
    this:dialogid:=this:pid+"_"+alltrim(str(++dialogid))
    this:defaultradiogroup:=jtradiogroup()
    this:parser:=xmlparserNew()  
    this:mustreact:=.f.
    return this

function jtdialogIni(this,t,l,b,r)//compatibility
    return this:(jtdialog)initialize(t,l,b,r)

****************************************************************************
static function jtdialog.add(this,item)
    item:setdialogid(this:dialogid)
    aadd(this:itemlist,item)
    if( item:classname=="jtradio" .and. item:group==NIL  )
        item:setgroup(this:defaultradiogroup)
    end
    return item

****************************************************************************
static function jtdialog.xmlout(this)

local x,n,c,g:={},grp,i

    x:="<jtdialog"
    x+=ATTRI("top",this:top)
    x+=ATTRI("left",this:left)
    x+=ATTRI("bottom",this:bottom)
    x+=ATTRI("right",this:right)
    x+=ATTR("name",this:name)
    x+=ATTR("dialogid",this:dialogid)
    x+=ATTR("pid",this:pid)
    x+=">"+EOL
    x+="<caption>"+cdataif(this:text)+"</caption>"+EOL
 
    if( this:layout!=NIL )
        x+="<layout>"+this:layout+"</layout>"+EOL
    end

    for n:=1 to len(this:itemlist)
        c:=this:itemlist[n] 
        if( c:classname=="jtradio" .and. c:group!=NIL )
        
            grp:=eval(c:group)

            for i:=1 to len(g)
                if( grp==g[i] )
                    exit
                end
            next

            if( i>len(g) )
                aadd(g,grp)
                x+="<jtradiogroup>"+EOL
                for i:=1 to len(grp)
                    x+=grp[i]:xmlout+EOL
                next
                x+="</jtradiogroup>"+EOL
            end

        else
            x+=c:xmlout+EOL
        end
    next

    x+="</jtdialog>"

    return x

****************************************************************************
static function jtdialog.show(this)        
local n
    
    //Megjegyzés:
    //Az alábbi ciklus inicializálja a kontrollok laststate attribútumait
    //abból a célból, hogy a frissen megjelenített dialogbox tartalmát
    //feleslegesen ne küldjük újra a reaction message-ben.
    //Ugyanezt a műveletet a terminál NEM csinálja, így a terminál az első
    //action message-ben minden kontrollt küldeni fog. Ez viszont 
    //azért jó, mert így biztosan összhangba kerül az alkalmazás és
    //a terminál olyan esetekben is, amikor az inicializáláskor
    //küldött érték nem kezelhető a terminálban, pl. a picturenél
    //hosszabb inicializáló szöveg.

    for n:=1 to len(this:varlist)
        if( this:varlist[n]!=NIL )
            this:varlist[n]:savestate  //inicializálja a laststate-eket 
        end
    next
 
    this:mustreact:=.f. 
    this:send(this:xmlout) 

    return NIL


****************************************************************************
static function jtdialog.exit(this)
    this:mustreact:=.f. 
    this:send("<exit/>") 
    return NIL
 

****************************************************************************
static function jtdialog.close(this)
    this:mustreact:=.f. 
    this:send('<close dialogid="'+this:dialogid+'"/>') 
    return NIL


****************************************************************************
static function jtdialog.getmessage(this,wtime)
 
local msg,dom,node,type,dlgid,source
local n,value,name,i,blk 

    if( this:mustreact )
        this:response
    end

    if( empty(msg:=this:recv(wtime)) )
        //NIL, ha megszakadt a kapcsolat
        //"" , ha lejárt a várakozási idő
        return msg   
    end

    dom:=this:parser:parsestring(msg) 
    node:=dom:content[1]
    type:=node:type
    dlgid:=node:getattrib("dialogid")
    
    if( !dlgid==this:dialogid )
        //alert( "DIALOGID ELTÉR!"  )
        ? "INVALID DIALOGID,", "  expected:",this:dialogid, "  recieved:",dlgid
    end
 
    if( type=="action" )
        //a kontrollok új tartalmát
        //betölti a dialog objektumba

        this:mustreact:=.t.

        source:=node:content[1]:gettext
 
        for n:=2 to len(node:content)
            name:=node:content[n]:type 

            i:=hash_index(this:varlist,name)
            if( this:varlist[i]!=NIL )
                this:varlist[i]:xmlput(node:content[n])   //új érték tárolva
                this:varlist[i]:savestate                 //ne küldje vissza

                //Megjegyzés:
                //Ugyanezt a savestate adminisztrációt a terminál
                //NEM csinálja, azaz minden új adatot egyszer visszaküld.
                //Ez azért jó, mert összhangba kerül az alkalmazás
                //és a terminál. Pl. ha egy picture nagybetűre konvertál,
                //de kisbetűs adatot töltünk bele, akkor az visszajön
                //nagybetűre konvertálva.
            else
                ? "Unknown control:",name
            end
        next
        
        //ha a source kontrollnak van blokkja,
        //akkor azt itt végrehajtjuk

        i:=hash_index(this:blklist,source)
        if( this:blklist[i]!=NIL )
            eval(this:blklist[i]:actionblock,this)
        end
        
        return source
 
    elseif( type=="destroy" ) 
        return NIL //becsukták az ablakot 

    end
   
    return NIL
 

****************************************************************************
static function jtdialog.response(this)
local n,v,x:=""
    for n:=1 to len(this:varlist)
        v:=this:varlist[n]
        if( v!=NIL .and. v:changed )
            x+="<"+v:name+">"+v:xmlget+"</"+v:name+">" 
            v:savestate
        end
    next
    if( empty(x) )
        x:='<reaction dialogid="'+this:dialogid+'"/>'
    else
        x:='<reaction dialogid="'+this:dialogid+'"><set>'+x+'</set></reaction>'
    end
    this:send(x)
    this:mustreact:=.f.
    return NIL

 
****************************************************************************
static function jtdialog.getcontrolbyname(this,name)
    return this:varlist[ hash_index(this:varlist,lower(name)) ]
 

****************************************************************************
static function jtdialog.blklist(this)
local n

    if( this:_blklist_==NIL  )
        this:_blklist_:=array(64)
        this:_blkcount_:=0
        jtdialog.setblk1(this,this:itemlist) 
    end
    return this:_blklist_ 


static function jtdialog.setblk1(this,itemlist)
local n,x,it

    for n:=1 to len(itemlist)
        it:=itemlist[n] 
        if( NIL!=it:actionblock )
            x:=hash_index(this:_blklist_,it:name)
            this:_blklist_[x]:=it
            if( ++this:_blkcount_>0.66*len(this:_blklist_) )
                this:_blklist_:=hash_rebuild(this:_blklist_,2*len(this:_blklist_))
            end
        end
        if( NIL!=it:itemlist )
            jtdialog.setblk1(this,it:itemlist) 
        end
    next
    return NIL


****************************************************************************
static function jtdialog.varlist(this)
local n
    if( this:_varlist_==NIL )
        this:_varlist_:=array(64)
        this:_varcount_:=0
        jtdialog.setvar1(this,this:itemlist)
    end
    return this:_varlist_


static function jtdialog.setvar1(this,itemlist)
local n,x,v,vn,e

    for n:=1 to len(itemlist)

        //csak akkor tesszük be a listába, ha van neve,
        //de nem teszünk bele több egyező nevű kontrollt.

        v:=itemlist[n] 
 
        if( !empty(vn:=v:name) .and. left(vn,6)!="_ctrl_" )
            x:=hash_index(this:_varlist_,vn)
            if( this:_varlist_[x]==NIL )
                this:_varlist_[x]:=v
                if( ++this:_varcount_>0.66*len(this:_varlist_) )
                    this:_varlist_:=hash_rebuild(this:_varlist_,2*len(this:_varlist_))
                end
            else
                e:=errorNew()
                e:operation:="jtdialog.varlist"
                e:description:="multiple control name"
                e:args:={vn}
                break(e)
            end
        end
    
        if( NIL!=v:itemlist )
            jtdialog.setvar1(this,v:itemlist) 
        end
    next
    return NIL

 
****************************************************************************
static function jtdialog.list(this)
local n,a:={}
    for n:=1 to len(this:varlist)
        if( this:varlist[n]!=NIL )
            aadd(a,this:varlist[n])
        end
    next
    asort(a,,,{|x,y|x:name<y:name})
    for n:=1 to len(a)
        ? padr(a[n]:classname,24),; 
          padr(a[n]:name,24),; 
          if(a[n]:actionblock==NIL," ","B"),; 
          if(a[n]:valid,"V"," "),; 
          if(a[n]:enabled," ","D"),; 
          a[n]:xmlget
    next
    return NIL
 

****************************************************************************
static function jtdialog.alert(this,msg,opt)
local rsp,dom,node
    this:send(jtalertNew(msg,opt):xmlout)
    while( (rsp:=this:recv)!=NIL  )
        dom:=this:parser:parsestring(rsp)  
        node:=dom:content[1]
        if( node:type=="alert" )
            return val(node:gettext) 
        end
    end
    return 0 
    

****************************************************************************
static function jtdialog.varinst(this,alias) 


//Készít egy objektumot:
//
//az osztály neve: varlist_alias
//attribútumainak neve: varlist[i]:name
//attribútumainak értéke: varlist[i] (objektum)
//
//Ezt az objektumot betesszük a jtdialog var attribútumába,
//ami lehetővé teszi, hogy a komponenseket név szerint érjük el,
//
//pl: dialog:var:field:varput("FFFFFFFFUUUUUUUUAAAAAAAA")
//
//Probléma, hogy a kontrollokhoz csak azután lehet így
//hozzáférni, miután véglegesen elkészült a dialogbox, 
//és teljes a varlist, azaz minden kontroll ismert.
//
//Az alábbi metódusok elkészítik varlist-et, ami bajt okozhat, 
//ha a híváskor a komponenesek még nincsenek hiánytalanul meg:
//
//  show
//  getmessage
//  getcontrol
//  list
//  response


local clnm:="varlist_"+alias
local clid:=classidbyname(clnm)
local attrlist,n,i:=0

    this:_varlist_:=NIL  //ez kell!
    this:_blklist_:=NIL  //ez kell!
 
    if( empty(clid) )
        clid:=classRegister(clnm,{objectClass()})
        for n:=1 to len(this:varlist)
            if( this:varlist[n]!=NIL )
                classAttrib(clid,this:varlist[n]:name)  
            end
        end
    end

    this:var:=objectNew(clid) 
    attrlist:=this:var:asarray

    for n:=1 to len(this:varlist)
        if( this:varlist[n]!=NIL )
            attrlist[++i]:=this:varlist[n]
        end
    end
    
    #ifdef HASH_PRINT //teszt
        hash_print(this:varlist)
        hash_print(this:blklist)
    #endif
 
    return NIL

****************************************************************************
//hash algoritmus
****************************************************************************
static function hash_rebuild(hash,len)
local hash1:=array(len),n,x
    for n:=1 to len(hash)
        if( hash[n]!=NIL )
            x:=hash_index(hash1,hash[n]:name)
            hash1[x]:=hash[n]
        end
    next
    return hash1

// A hash tábla egy array: {item1,item2,...},
// ahol item==NIL, vagy item egy name attribútummal rendelkező object,
// object:name játssza a kulcs szerepét.

****************************************************************************
static function hash_index(hash,key)

local hlen:=len(hash)
local hcode:=hashcode(key)
local hidx:=hcode%hlen
local item

    while( .t. )
        item:=hash[1+hidx]
        if( item==NIL )
            return 1+hidx
        elseif( item:name==key )
            return 1+hidx
        elseif( ++hidx>=hlen )
            hidx:=0
        end
    end
    return NIL

// Keresés a hash táblában:
// A ciklus véget ér, ui. a táblának van NIL eleme.
// visszatérés: hashidx
// Ha hash[hasidx]==NIL, akkor a keresett elem nincs a táblában,
//                       és éppen a hashidx helyre kell/lehet betenni.
// Ha hash[hasidx]!=NIL, akkor az a keresett elem.

****************************************************************************
#ifdef HASH_PRINT //csak teszteléshez

static function hash_print(hash)

local hidx,hidx0,coll
local elemcnt:=0,collcnt:=0

    for hidx:=1 to len(hash)
        if( hash[hidx]!=NIL )
            hidx0:=1+hashcode(hash[hidx]:name)%len(hash)
            coll:=(hidx-hidx0+len(hash))%len(hash)
            collcnt+=coll
            elemcnt++
            ?  hidx, padr(hash[hidx]:name,20), hidx0, replicate("!",coll)
        end
    next

    ?
    ? "tab length :",  len(hash)
    ? "item count :",  elemcnt
    ? "collisions :",  collcnt
    ? 

#endif    

****************************************************************************

