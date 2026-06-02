
******************************************************************************************
class stomperror(apperror)

******************************************************************************************
// STOMP baseclass for consumer and producer
******************************************************************************************
static class stomp(object) new:

    attrib  host
    attrib  port
    attrib  login
    attrib  passcode
    attrib  socket
    attrib  version
    attrib  session
    attrib  destination

    method  connect
    method  disconnect
    method  initialize


******************************************************************************************
static function stomp.initialize(this,dest)
    this:host:="localhost"
    this:port:=61616
    this:destination:=dest
    this:socket:=socketNew()
    return this


******************************************************************************************
static function stomp.connect(this)

local frame
local eol:=x"0a"
local rsp,arsp,n,header
local err

    begin
        this:socket:connect(this:host,this:port)
    recover err <socketError>
        err:=stomperrorNew("stomp.connect")
        err:description:="connect failed"
        err:args:={this:socket,this:host,this:port}
        break(err)
    end

    frame:=a"CONNECT"+eol
    frame+=a"accept-version:1.2"+eol
    frame+=a"heart-beat:30000,30000"+eol
    if( this:login!=NIL )
        frame+=a"login:"+str2bin(this:login)+eol
        frame+=a"passcode:"+str2bin(this:passcode)+eol
    end
    frame+=eol
    frame+=x"00"

    DEBUG(frame)

    if( this:socket:send(frame)!=len(frame) )
        err:=stomperrorNew("stomp.connect")
        err:description:="send failed"
        err:args:={this:socket,deleol(frame)}
        break(err)
    end

    DEBUG( rsp:=this:socket:recvall(2000) )

    arsp:=split(rsp|a"",bin(10))
    if( empty(arsp) .or. arsp[1]!=a"CONNECTED" )
        err:=stomperrorNew("stomp.connect")
        err:description:="CONNECTED frame expected"
        err:args:={deleol(rsp)}
        break(err)
    end

    for n:=1 to len(arsp)
        header:=arsp[n]::split(a":")
        if( len(header)!=2 )
            loop
        end
        if( header[1]==a"version" )
            this:version:=header[2]::bin2str
        elseif( header[1]==a"session" )
            this:session:=header[2]::bin2str
        end
    next



******************************************************************************************
static function stomp.disconnect(this)

local frame
local eol:=x"0a"
local receipt:=randbytes()::str2bin
local rsp,arsp,n,header
local err

    frame:=a"DISCONNECT"+eol
    frame+=a"receipt:"+receipt+eol
    frame+=eol
    frame+=x"00"

    DEBUG(frame)

    if( this:socket:send(frame)!=len(frame) )
        err:=stomperrorNew("stomp.disconnect")
        err:description:="send failed"
        err:args:={this:socket,deleol(frame)}
        break(err)
    end

    DEBUG( rsp:=this:socket:recvall(2000) )

    if( rsp==NIL )
        // wf embedded artemis nem válaszol
        return NIL
    end

    arsp:=split(rsp|a"",bin(10))
    if( empty(arsp) .or. arsp[1]!=a"RECEIPT"  )
        err:=stomperrorNew("stomp.disconnect")
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
        err:=stomperrorNew("stomp.disconnect")
        err:description:="different receipt-id header"
        err:args:={deleol(rsp)}
        break(err)
    end




******************************************************************************************
// PRODUCER
******************************************************************************************
class stomp.producer(stomp)
    attrib  persistent
    attrib  contenttype

    method  initialize
    method  sendmessage


******************************************************************************************
static function stomp.producer.initialize(this,dest)
    this:(stomp)initialize(dest)
    this:persistent:=.t.
    this:contenttype:="text/plain"
    return this


******************************************************************************************
static function stomp.producer.sendmessage(this,msg)

local frame
local eol:=x"0a"
local receipt:=randbytes()::str2bin
local rsp,arsp,n,header,hdrlen
local err

    msg::=str2bin

    frame:=a"SEND"+eol
    frame+=a"destination:"+this:destination::str2bin+eol
    frame+=a"content-type:"+this:contenttype::str2bin+eol
    frame+=a"content-length:"+(msg::len+0)::str::alltrim::str2bin+eol
    frame+=a"receipt:"+receipt+eol
    frame+=if(this:persistent,a"persistent:true",a"persistent:false")+eol
    frame+=eol
    hdrlen:=len(frame)
    frame+=msg
    frame+=x"00"

    DEBUG(frame)

    if( this:socket:send(frame)!=len(frame) )
        err:=stomperrorNew("stomp.producer.sendmessage")
        err:description:="send failed"
        err:args:={this:socket,deleol(frame)}
        break(err)
    end

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
// CONSUMER
******************************************************************************************
class stomp.consumer(stomp)

    attrib  buffer
    attrib  ack
    attrib  id

    method  initialize
    method  subscribe
    method  getmessage


******************************************************************************************
static function stomp.consumer.initialize(this,dest)
    this:(stomp)initialize(dest)
    this:buffer:=a""
    this:ack:="auto" // auto vagy client
    this:id:=randbytes()
    return this


******************************************************************************************
static function stomp.consumer.subscribe(this)

local frame
local eol:=x"0a"
local rsp,arsp,n,header
local err

    frame:=a"SUBSCRIBE"+eol
    frame+=a"destination:"+this:destination::str2bin+eol
    frame+=a"id:"+this:id::str2bin+eol
    frame+=a"ack:"+this:ack::str2bin+eol
    frame+=eol
    frame+=x"00"

    DEBUG(frame)

    if( this:socket:send(frame)!=len(frame) )
        err:=stomperrorNew("stomp.consumer.subscribe")
        err:description:="send failed"
        err:args:={this:socket,deleol(frame)}
        break(err)
    end



******************************************************************************************
static function stomp.consumer.getmessage(this)

local chunk,msg,body,err
local pos,hdrpos,conlen
local bompos,eompos
local ackpos
local frame
local eol:=x"0a"

static counter:=0
local  logname

    bompos:=1
    skip_heartbeat(this,@bompos)

    while( (pos:=at(x"0a0a",this:buffer))==0 )
        chunk:=this:socket:recvall(10000)

        if( empty(chunk) )
            if( chunk==NIL )
                // lezarodott a socket
                if( this:buffer::len>bompos )
                    // a bufferben csonka uzenet maradt
                    err:=stomperrorNew("stomp.consumer.getmessage")
                    err:description("recv failed")
                    break(err)
                end
                return NIL
            else
                send_heartbeat(this)
                loop
            end
        end

        memo(++counter,"chunk",chunk)
        this:buffer+=chunk
        skip_heartbeat(this,@bompos)
        send_heartbeat(this)
    end
    hdrpos:=pos //;? "HDRPOS", hdrpos // end of header

    if( at(a"ERROR",this:buffer)==bompos )
        err:=stomperrorNew("stomp.consumer.getmessage")
        err:description:=bin2str( this:buffer[bompos..hdrpos]::strtran(x"0a",a"|") )
        break(err)
    end

    if( at(a"MESSAGE",this:buffer)!=bompos )
        err:=stomperrorNew("stomp.consumer.getmessage")
        err:description:="MESSAGE frame expected: "+bin2str(deleol(this:buffer[bompos..hdrpos]))::left(32)
        break(err)
    end


    pos:=at(a"content-length:",this:buffer)
    if( pos==0 .or. hdrpos<pos )
        err:=stomperrorNew("stomp.consumer.getmessage")
        err:description("no content-length header")
        break(err)
    end
    conlen:=this:buffer::substr(pos+15,15)::val  //;? "CONLEN", conlen
    eompos:=hdrpos+2+conlen                      //;? "EOMPOS", eompos

    while( this:buffer::len<eompos )
        chunk:=this:socket:recvall(1000)

        if( empty(chunk) )
            if( chunk==NIL )
                // lezarodott a socket
                if( this:buffer::len>bompos )
                    // a bufferben csonka uzenet maradt
                    err:=stomperrorNew("stomp.consumer.getmessage")
                    err:description("recv failed")
                    break(err)
                end
                return NIL
            else
                loop
            end
        end

        memo(++counter,"chunkx",chunk)
        this:buffer+=chunk
    end

    msg:=this:buffer[bompos..eompos]           // command headers body NULL
    body:=this:buffer[hdrpos+2..eompos-1]
    this:buffer:=this:buffer[eompos+1..]

    DEBUG(msg)

    if( "client"$this:ack )
        ackpos:=at(a"ack:",msg)
        pos:=at(x"0a",msg,ackpos)
        if( 0<ackpos<pos )
            frame:=a"ACK"+eol
            frame+=a"id:"+msg[ackpos+4..pos] // eol
            frame+=eol
            frame+=x"00"
            this:socket:send(frame)    
            DEBUG(frame)
        end
    end

    memo(counter,"message",msg)          // debug only
    memo(counter,"xbuffer",this:buffer)  // debug only

    return body



******************************************************************************************
static function skip_heartbeat(this,bompos) // a heartbeat bajtokat kihagyjuk
    while( bompos<=len(this:buffer) .and. this:buffer[bompos]==x"0a" )
        bompos++
    end
    if( bompos>len(this:buffer) )
        this:buffer:=a""
        bompos:=1
    end


static function send_heartbeat(this) // heartbeat bajtot kuldunk
static sec:=seconds()
    if( seconds()-sec>=9 )
        sec:=seconds()
        this:socket:send(x"0a")
        ? "heartbeat",sec
    end


******************************************************************************************
// DEBUG

******************************************************************************************
static function debug(txt)
//  ? txt
//  ? deleol(txt)


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
static function memo(counter,name,txt)
//local logname:="log-"+counter::str::alltrim::padl(3,"0")+"-"+name
//  memowrit(logname,txt)


******************************************************************************************
static function randbytes(n:=2)
    return crypto_rand_bytes(n)::bin2hex  // C type



******************************************************************************************
