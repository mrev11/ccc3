

******************************************************************************************
// CONSUMER
******************************************************************************************
class stomp.consumer(stomp)

    attrib  buffer
    attrib  ack
    attrib  id
    attrib  lastheader    // utolso uzenet teljes header-je egyben (X típus)

    method  initialize
    method  subscribe
    method  getmessage
    method  getheader     // header ertekek egyenkent, kulcs alapjan (X tipus)
    method  sendack       // ack-ot kuld a lastheaderbol kilvasott id-vel


******************************************************************************************
static function stomp.consumer.initialize(this,dest)
    this:(stomp)initialize(dest)

    this:id:=randbytes()

    this:ack:="client-individual"  // az objektum automatikus ack-ot kuld minden message-re
    //this:ack:="client"           // az alkalmazas kuldi az ack-ot (kumulativ)
    //this:ack:="auto"             // nincs ack, az uzenet elveszhet

    this:buffer:=a""

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
static function stomp.consumer.getmessage(this,header)

local chunk,msg,body,err
local pos,hdrpos,conlen
local bompos,eompos

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

    msg:=this:buffer[bompos..eompos]  // command headers body NULL
    header:=this:lastheader:=this:buffer[bompos..hdrpos]
    body:=this:buffer[hdrpos+2..eompos-1]
    this:buffer:=this:buffer[eompos+1..]

    DEBUG(msg)

    if( "auto"==this:ack )
        // nincs ack
    elseif( "client-individual"==this:ack )
        // automatikus ack
        this:sendack()
    elseif( "client"==this:ack )
        // az alkalmazas kuldi az ack-ot (kumulativ)
    end

    memo(counter,"message",msg)          // debug only
    memo(counter,"xbuffer",this:buffer)  // debug only

    return body


******************************************************************************************
static function stomp.consumer.getheader(this,hdr)
local hdrpos,eolpos,hdrval
    hdr::=str2bin+a":"
    hdrpos:=at(hdr,this:lastheader)
    if( hdrpos>0  )
        eolpos:=at(x"0a",this:lastheader,hdrpos) 
        hdrval:=this:lastheader[hdrpos+len(hdr)..eolpos-1] // eol leszedve
    end
    if( hdrval::empty )
        return NIL
    end
    return hdrval


******************************************************************************************
static function stomp.consumer.sendack(this)
local ackid,frame,eol:=x"0a"
local err

    ackid:=this:getheader("ack")
    if( empty(ackid) )
        err:=stomperrorNew("stomp.consumer.sendack")
        err:description:="No ACK header in the last message: "+this:lastheader::bin2str::deleol::left(32)
        break(err)
    end

    frame:=a"ACK"+eol
    frame+=a"id:"+ackid+eol
    frame+=eol
    frame+=x"00"

    DEBUG(frame)

    if( this:socket:send(frame)!=len(frame) )
        err:=stomperrorNew("stomp.sendack")
        err:description:="send failed"
        err:args:={this:socket,deleol(frame)}
        break(err)
    end


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
        DEBUG("heartbeat"+str(sec))
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
//  ? txt


******************************************************************************************
