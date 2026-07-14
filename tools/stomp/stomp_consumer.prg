

******************************************************************************************
// CONSUMER
******************************************************************************************
class stomp.consumer(stomp)

    attrib  buffer
    attrib  ack             // kozos ack mod minden subscriptionban
    attrib  header          // utolso uzenet teljes header-je egyben (X típus)
    attrib  subscriptions   // {dest1,dest2,...}   parhuzamos array
    attrib  subscrids       // {id1  ,id2  ,...}   parhuzamos array

    method  initialize
    method  subscribe
    method  unsubscribe
    method  getmessage
    method  getheader       // header ertekek egyenkent, kulcs alapjan (X tipus)
    method  sendack         // ack-ot kuld a lastheaderbol kilvasott id-vel
    method  cleanup

    // megjegyzes:
    // nem szabad hasznalni az mq:unsubscribe-ot,
    // mert (tevesen) megis kuld uzenetet a sorbol,
    // majd a tevesen kuldott uzenet ack-ja utan ERROR-t kuld  


******************************************************************************************
static function stomp.consumer.initialize(this,dest)
    this:(stomp)initialize(dest)

    this:ack:="client-individual"  // az objektum automatikus ack-ot kuld minden message-re
    //this:ack:="client"           // az alkalmazas kuldi az ack-ot (kumulativ)
    //this:ack:="auto"             // nincs ack, az uzenet elveszhet

    this:subscriptions:={}
    this:subscrids:={}
    this:buffer:=a""

    return this


******************************************************************************************
static function stomp.consumer.subscribe(this,dest)

static subscrid:=0 // minden subscription egyedi id-t kap

local id
local frame
local eol:=x"0a"
local err

    if( dest==NIL )
        dest:=this:destination
    end
    id:=this:subscriptions::ascan(dest)
    if( id>0 )
        err:=stomperrorNew("stomp.consumer.subscribe")
        err:description:="subscription is already used"
        err:args:={this:subscriptions[id]}
        break(err)
    end
    id:=this:subscriptions::ascan(NIL)
    if( id<1 )
        this:subscriptions::aadd(NIL)
        this:subscrids::aadd(NIL)
        id:=this:subscriptions::len
    end
    subscrid++

    frame:=a"SUBSCRIBE"+eol
    frame+=a"destination:"+dest::str2bin+eol
    frame+=a"id:"+subscrid::str::alltrim::str2bin+eol
    frame+=a"ack:"+this:ack::str2bin+eol // kozos
    frame+=eol
    frame+=x"00"
    DEBUG(frame)
    if( this:socket:send(frame)!=len(frame) )
        err:=stomperrorNew("stomp.consumer.subscribe")
        err:description:="send failed"
        err:oscode:=ferror()
        err:args:={this:socket,deleol(frame)}
        break(err)
    end

    this:subscriptions[id]:=dest
    this:subscrids[id]:=subscrid
    return id

******************************************************************************************
static function stomp.consumer.unsubscribe(this,destorid)

local id
local frame
local eol:=x"0a"
local subid
local err

    if( destorid::valtype=="N" )
        id:=destorid
    else
        id:=ascan(this:subscriptions,destorid)
    end

    if( id<1 )
        // kihagy
    elseif( id>len(this:subscriptions) )
        // kihagy
    elseif( this:subscriptions[id]==NIL )
        // kihagy
    else
        subid:=this:subscrids[id]
        frame:=a"UNSUBSCRIBE"+eol
        frame+=a"id:"+subid::str::alltrim::str2bin+eol
        frame+=eol
        frame+=x"00"
        DEBUG(frame)
        if( this:socket:send(frame)!=len(frame) )
            err:=stomperrorNew("stomp.consumer.unsubscribe")
            err:description:="send failed"
            err:oscode:=ferror()
            err:args:={id,this:socket,deleol(frame)}
            break(err)
        end
        this:subscriptions[id]:=NIL
        this:subscrids[id]:=NIL
        return id
    end
    return NIL

******************************************************************************************
static function stomp.consumer.cleanup(this)
local id,err
    //? "BEFORE-cleanup, press any key";inkey(0)
    for id:=1 to len(this:subscriptions)
        if( this:subscriptions[id]!=NIL )
            //? "before CLEANUP", id, "press any key";inkey(0)
            this:unsubscribe(id)
            //?? " OK"
        end
    next
    //? "AFTER-cleanup, press any key";inkey(0)


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

        //memo(++counter,"chunk",chunk)
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

        //memo(++counter,"chunkx",chunk)
        this:buffer+=chunk
    end

    msg:=this:buffer[bompos..eompos]  // command headers body NULL
    header:=this:header:=this:buffer[bompos..hdrpos]
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

    this:destination:=this:getheader("destination")::bin2str

    return body


******************************************************************************************
static function stomp.consumer.getheader(this,hdr)
local hdrpos,eolpos,hdrval
    hdr::=str2bin+a":"
    hdrpos:=at(hdr,this:header)
    if( hdrpos>0  )
        eolpos:=at(x"0a",this:header,hdrpos)
        hdrval:=this:header[hdrpos+len(hdr)..eolpos-1] // eol leszedve
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
        err:description:="No ACK header in the last message: "+this:header::bin2str::deleol::left(32)
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
        err:oscode:=ferror()
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
//static function memo(counter,name,txt)
//local logname:="log-"+counter::str::alltrim::padl(3,"0")+"-"+name
//    memowrit(logname,txt)


******************************************************************************************
static function debug(txt)
//    ? txt


******************************************************************************************
