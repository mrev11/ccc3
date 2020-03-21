
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

namespace webapp

using webapp;
      script jsstring


***************************************************************************************
class formdata(object)
    attrib  source
    attrib  sourcetype
    attrib  hash

    method  initialize
    method  get
    method  getnumber
    method  getdate
    method  getlogical
    method  put
    method  remove          :hash:remove   
    method  clear
    method  putlabel
    method  update
    method  upload
    method  list
    method  copytohash

    method  save            //minden kulcsra orig:=value 
    method  rest            //minden kulcsra value:=orig

***************************************************************************************
static function formdata.initialize(this,dom:=xmlnodeNew())
    this:hash:=simplehashNew()
    walk(dom,this)
    return this


static function walk(node,this)
local n,child,ctrl,err

    for n:=1 to len(node:content)
        child:=node:content[n]

        if( child:type=="control" )
            ctrl:=htmlcontrolNew(child)
            
            if( this:hash[ctrl:id]!=NIL )
                err:=formdataerrorNew()
                err:operation:="formdata.initialize"
                err:description:="multiple control"
                err:args:={ctrl:id}
                break(err)
                
                //A controlok id-inek egyedinek kell lenni.
                //Nehezen felderíthető hibát okoz, ha nem egyedi,
                //ezért az a biztos, ha a program ellenőrzi,
                //és nem engedi tovább.
            end

            this:hash[ctrl:id]:=ctrl

        elseif( child:type=="source" )
            this:source:=child:gettext

        elseif( child:type=="sourcetype" )
            this:sourcetype:=child:gettext

        else
            walk(child,this)
        end
    next
    

***************************************************************************************
static function formdata.get(this,x)
local ctrl:=this:hash[x::bin2str]
    if( ctrl!=NIL )
        return ctrl:value
    end

//megjegyzés: fdata:get(x) ugyanaz, mint fdata[x]  (rövidítés)

***************************************************************************************
static function formdata.getnumber(this,x)
local ctrl:=this:hash[x::bin2str]
    if( ctrl!=NIL )
        x:=ctrl:value
        //a bongeszo is kiveszi a vesszoket 
        //x::=strtran(",","")::val
        x::=val
        return x
    end


***************************************************************************************
static function formdata.getdate(this,id)
local ctrl:=this:hash[id::bin2str],x,d
    if( ctrl!=NIL )
        x:=ctrl:value
        begin
            x::=strtran("-","")
            if( empty(x) )
                d:=ctod("") //empty
            else
                d:=stod(x)
                if( !x==dtos(d) )
                    d:=NIL  //invalid
                end
            end
        recover
            d:=NIL //invalid
        end
    end
    return d


***************************************************************************************
static function formdata.getlogical(this,x)
local ctrl:=this:hash[x::bin2str]
    if( ctrl!=NIL )
        x:=ctrl:value
        return x=="true"
    end

***************************************************************************************
static function formdata.put(this,x,y,type)
local ctrl:=this:hash[x::bin2str]
    if( ctrl==NIL )
        ctrl:=htmlcontrolNew(xmlnodeNew())
        ctrl:id:=x
        ctrl:type:=if(type==NIL,"text",type) //HTML tipus
        ctrl:orig:="?"
        this:hash[x]:=ctrl
    end
    
    if( valtype(y)=="C" )
        //ok
    elseif( valtype(y)=="N" )
        y::=str
    elseif( valtype(y)=="D" )
        y::=transform("@D 9999-99-99")
    elseif( valtype(y)=="L" )
        y:=if(y,"true","false")
    end
    
    ctrl:value:=y

//megjegyzés: fdata:put(x,y)-ra nincs az előzőhöz hasonló rövidítés


***************************************************************************************
static function formdata.clear(this,x,y:="")
local ctrl:=this:hash[x::bin2str]
    if( ctrl!=NIL )
        ctrl:value:=y
    end

***************************************************************************************
static function formdata.putlabel(this,id,txt)
local lab:=htmlcontrolNew(xmlnodeNew()) //üres node-ból inicializálva
    lab:id:=id
    lab:type:="label"
    lab:orig:="?"
    lab:value:=txt
    this:hash[id]:=lab

#ifdef NOTDEFINED
  A formdata objektumok a getmessage-ből jönnek.
  A böngésző küldi a változtatható értékű kontrollok aktuális értékét.
  Az input (text,hidden,password,checkbox,radio), textarea, select típusok jönnek.
  Visszafelé lehet küldeni label feliratot is, erre való a putlabel.   
#endif

***************************************************************************************
static function formdata.update(this)
local ctrl,upd,cmd:=""

    ctrl:=this:hash:firstvalue
    while( ctrl!=NIL )

        if( !ctrl:orig==ctrl:value )

            // az <input type="file"> kontrollok erteke array
            // az ilyeneket ki kell hagyni (nem modosithatok)

            if( valtype(ctrl:value)=="C" )
                upd:='XCODE.updatecontrol("id",VALUE); '
                upd::=strtran("id",ctrl:id)
                upd::=strtran("VALUE",ctrl:value::jsstring)
                cmd+=upd
                //? ctrl:orig,"->",ctrl:value,"UPDATE",upd
            end
        end

        ctrl:=this:hash:nextvalue
    end
    script(cmd)
    this:save


***************************************************************************************
static function formdata.upload(this) //mint update, de nem nézi orig!=value-t
local ctrl,upd,cmd:=""

    ctrl:=this:hash:firstvalue
    while( ctrl!=NIL )
        if( valtype(ctrl:value)=="C" )
            upd:='XCODE.updatecontrol("id",XX); '
            upd::=strtran("id",ctrl:id)
            upd::=strtran("XX",ctrl:value::jsstring)
            cmd+=upd
        end
        ctrl:=this:hash:nextvalue
    end

    script(cmd)
    this:save


***************************************************************************************
static function formdata.list(this)
local ctrl,arr:={},n
    ? "source:",this:source
    if( this:sourcetype!=NIL )
        ?? "("+this:sourcetype+")"
    end

    ctrl:=this:hash:firstvalue
    while( ctrl!=NIL )
        arr::aadd(ctrl)
        ctrl:=this:hash:nextvalue
    end
    
    asort(arr,,,{|x,y| x:type+"."+x:group+"."+x:id<;
                       y:type+"."+y:group+"."+y:id })
    
    for n:=1 to len(arr)
        ctrl:=arr[n]
        ? ctrl:type::padr(12),;
          ctrl:group::padr(12),;
          ctrl:id::padr(24),;
          "[",ctrl:value::format,"]",;
          "[",ctrl:orig::format,"]"
    next

static function format(x)
    x::=any2str
    x::=strtran(chr(10),"")
    x::=alltrim
    if( len(x)>24  )
        x::=left(20)+" ..."
    end
    return x

***************************************************************************************
static function formdata.copytohash(this)
local hash:=simplehashNew(),item
    item:=this:hash:first
    while( item!=NIL )
        hash[item[1]]:=item[2]:value
        item:=this:hash:next
    end
    return hash

***************************************************************************************
static function formdata.save(this) //minden kulcsra: orig:=value
local item:=this:hash:firstvalue
    while( item!=NIL )
        item:orig:=item:value
        item:=this:hash:nextvalue
    end
   

static function formdata.rest(this) //minden kulcsra: value:=orig
local item:=this:hash:firstvalue
    while( item!=NIL )
        item:value:=item:orig
        item:=this:hash:nextvalue
    end


***************************************************************************************
class htmlcontrol(object)
    attrib  id
    attrib  type
    attrib  group
    attrib  orig
    attrib  value
    
    method  initialize

static function htmlcontrol.initialize(this,node)
local n,x,child,flist

    this:group:=""

    for n:=1 to len(node:content)
        child:=node:content[n]

        if( child:type=="id" )
            this:id:=child:gettext

        elseif( child:type=="type" )
            this:type:=child:gettext

        elseif( child:type=="group" )
            this:group:=child:gettext

        elseif( child:type=="value" )

            if( child:content::empty() .or.;
                child:content[1]:type=="#TEXT" .or.; 
                child:content[1]:type=="#CDATA" )

                this:value:=child:gettext
                this:orig:=this:value

            elseif( child:content[1]:type=="filelist" )
                this:value:={}
                this:orig:=this:value
                flist:=child:content[1]
                for x:=1 to len(flist:content)
                    aadd(this:value,flist:content[x]:gettext)
                next
            end
        end
    next
    return this


***************************************************************************************
class formdataerror(apperror)


***************************************************************************************
function updatecontrol(id,value) //egyet beállít
local code:='XCODE.updatecontrol("id",VALUE); '
    code::=strtran("id",id)
    code::=strtran("VALUE",value::jsstring)
    script(code)


***************************************************************************************
