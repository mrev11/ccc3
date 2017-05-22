
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
    method  put
    method  remove          :hash:remove   
    method  clear
    method  putlabel
    method  update
    method  upload
    method  list
    method  checksum

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
static function formdata.put(this,x,y,type)
local ctrl:=this:hash[x::bin2str]
    if( ctrl==NIL )
        ctrl:=htmlcontrolNew(xmlnodeNew())
        ctrl:id:=x
        ctrl:type:=if(type==NIL,"text",type)
        ctrl:orig:="?"
        this:hash[x]:=ctrl
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
            upd:='CODE.updatecontrol("id",VALUE); '
            upd::=strtran("id",ctrl:id)
            upd::=strtran("VALUE",ctrl:value::jsstring)
            cmd+=upd
            //? ctrl:orig,"->",ctrl:value,"UPDATE",upd
        end

        ctrl:=this:hash:nextvalue
    end
    script(cmd)


***************************************************************************************
static function formdata.upload(this) //mint update, de nem nézi orig!=value-t
local ctrl,upd,cmd:=""

    ctrl:=this:hash:firstvalue
    while( ctrl!=NIL )
        upd:='CODE.updatecontrol("id",XX); '
        upd::=strtran("id",ctrl:id)
        upd::=strtran("XX",ctrl:value::jsstring)
        cmd+=upd
        ctrl:=this:hash:nextvalue
    end

    script(cmd)


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
          ctrl:id::padr(12),;
          "[",ctrl:value::format,"]",;
          "[",ctrl:orig::format,"]"
          
        if( ctrl:value::len>32 )
            ?? " ..."
        end
    next

static function format(x)
    x::=strtran(chr(10),"")::left(24)::alltrim
    return x


***************************************************************************************
static function formdata.checksum(this)
local x:=":",arr:={},ctrl,n
    ctrl:=this:hash:firstvalue
    while( ctrl!=NIL )
        if( ctrl:type=="label" )
            //kihagy
        elseif( ctrl:type=="radio" .and. ctrl:value=="false" )
            //kihagy
        elseif( ctrl:type=="checkbox" .and. ctrl:value=="false" )
            //kihagy
        elseif( ctrl:type=="select" .and. "Nincs" $ ctrl:value )
            //kihagy
        elseif( empty(ctrl:value) )
            //kihagy
        else
            arr::aadd(ctrl)
        end
        ctrl:=this:hash:nextvalue
    end
    asort(arr,,,{|x,y|x:id<y:id})
    for n:=1 to len(arr)
        ctrl:=arr[n]
        x+=ctrl:id+"="+ctrl:value+":"
    next
    return x


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
local n,child

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
            this:value:=child:gettext
            this:orig:=this:value
        end
    next
    return this


***************************************************************************************
class formdataerror(apperror)


***************************************************************************************
function updatecontrol(id,value) //egyet beállít
local code:='CODE.updatecontrol("id",VALUE); '
    code::=strtran("id",id)
    code::=strtran("VALUE",value::jsstring)
    script(code)


***************************************************************************************
