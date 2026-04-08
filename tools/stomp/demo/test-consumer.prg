
******************************************************************************************
function main()

local mq
local message

    ? "CONSUMER"

    mq:=stomp.consumerNew(queuename())
    mq:host:=host()
    mq:ack:="client"

    mq:connect
    mq:subscribe

    while( (message:=mq:getmessage)!=NIL  )
        ?  time(), a"["+message+a"]"
        proc(message)
        if( message==a"QUIT" )
            exit
        end
    end

    mq:disconnect

    ?


******************************************************************************************
static function proc(message)
local dom:=xmlparser2New():parse(message)
local hash:=simplehashNew()
    walk(hash,dom,"")
    hash:list


******************************************************************************************
static function walk(hash,this,path)

local n

    if( left(this:type,1)=="?" )
        ?? "<"+this:type
        for n:=1 to len(this:attrib)
            ?? " "+this:attrib[n]:name+"="+this:attrib[n]:value
        next
        ?? "?>" // az eltero "?>" lezaras miatt nem mehet a normal agon

    elseif( this:type=="#TEXT" )
        for n:=1 to len(this:content)
            ?? cdataif(this:content[n])
        next
 
    elseif( this:type=="#CDATA" )
        for n:=1 to len(this:content)
            ?? "<![CDATA["
            ?? this:content[n]
            ?? "]]>"
        next

    else
        ?? "<"+this:type
        for n:=1 to len(this:attrib)
            ?? " "+this:attrib[n]:name+"="+this:attrib[n]:value
        next
        if( empty(this:content) )
            ?? "/>"
        else
            ?? ">"
            for n:=1 to len(this:content)
                this:content[n]:xmloutpre
            next
            ?? "</"+this:type+">"
        end
    end


******************************************************************************************
static function textcontent(node) 

// => .t.
//  ha a content ures, vagy
//  csak #TEXT/#CDATA node-okat tartalmaz

local n
    for n:=1 to len(node:content)
        if( node:content[n]:type::asc!=35 ) // asc("#")==35
            return .f.
        end
    next 
    return .t.


******************************************************************************************
static function cdata(x)
local cd:="", n
    while( .t. )
        n:=at("]]>",x)
        if( n==0 )
            cd+="<![CDATA["+x+"]]>"
            exit
        else
            cd+="<![CDATA["+left(x,n+1)+"]]>" 
            x:=substr(x,n+2)
        end
    end
    return  cd
 

static function cdataif(x)
    if( "<"$x .or. "&"$x )
        return  cdata(x) 
    end
    return x


******************************************************************************************
static function quote(x)
    if( !'"'$x  )
        return '"'+x+'"'
    elseif( !"'"$x  )
        return "'"+x+"'"
    end
    return '"'+x::strtran('"','&quot;')+'"'


******************************************************************************************
