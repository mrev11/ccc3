

******************************************************************************************
class stomperror(apperror)

******************************************************************************************
// STOMP baseclass for consumer and producer
******************************************************************************************
class stomp(object) new:

    attrib  host
    attrib  port
    attrib  login
    attrib  passcode
    attrib  socket
    attrib  version
    attrib  session
    attrib  destination
    attrib  transaction

    method  connect
    method  disconnect
    method  initialize
    method  begin
    method  commit
    method  abort


******************************************************************************************
static function stomp.initialize(this,dest)
    this:host:="localhost"
    this:port:=61616
    this:destination:=dest
    return this


******************************************************************************************
static function stomp.connect(this)

local frame
local eol:=x"0a"
local rsp,arsp,n,header
local err

    begin
        this:socket:=socketNew()
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
        err:oscode:=ferror()
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

    this:cleanup

    frame:=a"DISCONNECT"+eol
    frame+=a"receipt:"+receipt+eol
    frame+=eol
    frame+=x"00"

    DEBUG(frame)

    if( this:socket:send(frame)!=len(frame) )
        err:=stomperrorNew("stomp.disconnect")
        err:description:="send failed"
        err:oscode:=ferror()
        err:args:={this:socket,deleol(frame)}
        break(err)
    end

    rsp:=this:socket:recvall(2000)
    if( rsp!=NIL )

        // miert van ez az ag?
        // mert a wf embedded artemis nem válaszol

        DEBUG(rsp)

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
    end

    this:socket:close



******************************************************************************************
static function stomp.begin(this)
local frame
local eol:=x"0a"
local err

    if( this:transaction!=NIL )
        err:=stomperrorNew("stomp.begin")
        err:description:="transaction active"
        err:args:={this:transaction}
        break(err)
    end

    this:transaction:=randbytes()
    frame:=a"BEGIN"+eol
    frame+=a"transaction:"+this:transaction::str2bin+eol
    frame+=eol
    frame+=x"00"

    DEBUG(frame)

    if( this:socket:send(frame)!=len(frame) )
        err:=stomperrorNew("stomp.begin")
        err:description:="send failed"
        err:oscode:=ferror()
        err:args:={this:socket,deleol(frame)}
        break(err)
    end


    return this:transaction


******************************************************************************************
static function stomp.commit(this)
local frame
local eol:=x"0a"
local err

    if( this:transaction==NIL )
        err:=stomperrorNew("stomp.commit")
        err:description:="no active transaction"
        break(err)
    end

    frame:=a"COMMIT"+eol
    frame+=a"transaction:"+this:transaction::str2bin+eol
    frame+=eol
    frame+=x"00"
    this:transaction:=NIL

    DEBUG(frame)

    if( this:socket:send(frame)!=len(frame) )
        err:=stomperrorNew("stomp.commit")
        err:description:="send failed"
        err:oscode:=ferror()
        err:args:={this:socket,deleol(frame)}
        break(err)
    end


******************************************************************************************
static function stomp.abort(this)
local frame
local eol:=x"0a"
local err

    if( this:transaction==NIL )
        err:=stomperrorNew("stomp.abort")
        err:description:="no active transaction"
        break(err)
    end

    frame:=a"ABORT"+eol
    frame+=a"transaction:"+this:transaction::str2bin+eol
    frame+=eol
    frame+=x"00"
    this:transaction:=NIL

    DEBUG(frame)

    if( this:socket:send(frame)!=len(frame) )
        err:=stomperrorNew("stomp.abort")
        err:description:="send failed"
        err:oscode:=ferror()
        err:args:={this:socket,deleol(frame)}
        break(err)
    end


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
static function debug(txt)
//    ? txt


******************************************************************************************
