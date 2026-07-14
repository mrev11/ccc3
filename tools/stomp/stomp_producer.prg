

******************************************************************************************
// PRODUCER
******************************************************************************************
class stomp.producer(stomp)
    attrib  persistent
    attrib  contenttype
    attrib  sendreceipt

    method  initialize
    method  sendmessage
    method  cleanup


******************************************************************************************
static function stomp.producer.initialize(this,dest)
    this:(stomp)initialize(dest)
    this:persistent:=.t.
    this:contenttype:="text/plain"
    this:sendreceipt:=.t.
    return this


******************************************************************************************
static function stomp.producer.sendmessage(this,msg,header)

local frame
local eol:=x"0a"
local receipt:=randbytes()::str2bin
local n,hdrlen
local err

    msg::=str2bin

    frame:=a"SEND"+eol
    frame+=a"destination:"+this:destination::str2bin+eol
    frame+=a"content-type:"+this:contenttype::str2bin+eol
    frame+=a"content-length:"+(msg::len+0)::str::alltrim::str2bin+eol
    frame+=if(this:persistent,a"persistent:true",a"persistent:false")+eol

    if( this:sendreceipt )
        // opcionalis
        frame+=a"receipt:"+receipt+eol
    end
    for n:=1 to len(header)
        // opcionalis
        frame+=header[n]::str2bin+eol
    next

    frame+=eol
    hdrlen:=len(frame)
    frame+=msg
    frame+=x"00"

    DEBUG(frame)

    if( this:socket:send(frame)!=len(frame) )
        err:=stomperrorNew("stomp.producer.sendmessage")
        err:description:="send failed"
        err:oscode:=ferror()
        err:args:={this:socket,deleol(frame)}
        break(err)
    end
    
    if( this:sendreceipt )
        verify_receipt(this,receipt)
    end


******************************************************************************************
static function stomp.producer.cleanup(this)
    // nothing


******************************************************************************************
static function verify_receipt(this,receipt)
local rsp,arsp,n,header,err

    DEBUG( rsp:=this:socket:recvall(2000) )

    arsp:=split(rsp|a"",bin(10))
    if( empty(arsp) .or. arsp[1]!=a"RECEIPT"  )
        err:=stomperrorNew("stomp.producer.sendmessage")
        err:description:="RECEIPT frame expected"
        err:args:={deleol(rsp)}
        break(err)
    end

    for n:=1 to len(arsp)
        header:=arsp[n]::split(a":")
        if( len(header)!=2 )
            loop
        end
        if( header[1]==a"receipt-id" .and. header[2]==receipt )
            exit
        end
    next

    if( n>len(arsp) )
        err:=stomperrorNew("stomp.producer.sendmessage")
        err:description:="different receipt-id header"
        err:args:={deleol(rsp)}
        break(err)
    end


******************************************************************************************
// DEBUG
******************************************************************************************
static function deleol(txt)
    return txt::split(bin(10))::join


******************************************************************************************
static function join(arr,delim:=a"|")
local x,n
    for n:=1 to len(arr)
        if( n==1 )
            x:=arr[1]
        else
            x+=delim+arr[n]
        end
    next
    return x


******************************************************************************************
static function randbytes(n:=2)
    return crypto_rand_bytes(n)::bin2hex  // C type


******************************************************************************************
static function memo(counter,name,txt)
//local logname:="log-"+counter::str::alltrim::padl(3,"0")+"-"+name
//  memowrit(logname,txt)


******************************************************************************************
static function debug(txt)
  //? txt


******************************************************************************************
