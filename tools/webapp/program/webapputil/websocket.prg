
namespace websocket
                  
***************************************************************************************
function readmessage(sck)

local err
local fragment,c,n
local frame_fin
local frame_opcode
local frame_masked
local payload_len
local masking_key
local body

    while(.t.)

        begin
            if( NIL==(c:=sck:recv(1,1000)) )
                break("Nincs kezdőbájt")
            else
                c::=asc
            end
            frame_fin:=(c::numand(0b10000000))!=0
            frame_opcode:=c::numand(0b00001111) //1=text 2=binary  8=close 9=ping 10=pong

            if( NIL==(c:=sck:recv(1,1000)) )
                break("Nincs payload_len-1")
            else
                c::=asc
            end
            frame_masked:=(c::numand(0b10000000))!=0
            payload_len:=c::numand(0b01111111)
    
            if( payload_len==126 )
                payload_len:=0
                for n:=1 to 2
                    if( NIL==(c:=sck:recv(1,1000)) )
                        break("Nincs payload_len-2")
                    else
                        c::=asc
                    end
                    payload_len:=payload_len*256+c
                next
    
            elseif( payload_len==127 )
                payload_len:=0
                for n:=1 to 8
                    if( NIL==(c:=sck:recv(1,1000)) )
                        break("Nincs payload_len-8")
                    else
                        c::=asc
                    end
                    payload_len:=payload_len*256+c
                next
            end
    
    
            if( frame_masked )
                masking_key:=sck:recv(4,1000)
                if( len(masking_key)!=4 )
                    break("Nincs masking_key")
                end
            end

            fragment:=a""
            while( fragment::len<payload_len )
                c:=sck:recv(payload_len-(fragment::len),1000)
                if( c==NIL )
                    break("Nem jött elég adat")
                else
                    fragment+=c
                end
            end
    
            if( frame_masked )
                fragment::=websocket.mask(masking_key)
            end

        recover err <C>    
            ? err
            return NIL
        end

        //? frame_fin, frame_opcode, frame_masked, payload_len 
        //for n:=1 to len(fragment)
        //    ?? "  ["+fragment[n]::asc::l2hex+"]"
        //next


        // fragmentation
        //  unfragmented message : (FIN==1,OP!=0)  
        //  fragmented message   : (FIN==0,OP!=0)  (FIN==0,OP==0)*  (FIN==1,OP==0)
        // control frames (ping, pong) are always unfragmented 
        // control frames may be injected in a fragmented message

        if( frame_opcode<=2 ) //0=continuation, 1=text, 2=binary
            if( body==NIL )
                body:=fragment
            else
                body+=fragment
            end
            if( frame_fin )
                return body
            end

        elseif( frame_opcode==8 ) //close
            ? "close"
            return NIL

        elseif( frame_opcode==9 ) //ping
            pong(sck,fragment) //visszaküld egy pongot

            ? "ping"
            if( body==NIL )
                //tobább kell várni, de nem itt, hanem a hívó programban
                return "" 
            else
                //közbeékelt ping, tovább kell olvasni
            end

        elseif( frame_opcode==10 ) //pong
            ? "pong"
            if( body==NIL )
                //szóló pong, tobább kell várni a hívó programban
                return "" 
            else
                //közbeékelt pong, tovább kell olvasni
            end

        else
            //ide nem jöhet
            ? frame_fin, frame_opcode, frame_masked, payload_len 
            for n:=1 to len(fragment)
                ?? "  ["+fragment[n]::asc::l2hex+"]"
            next
        end
    end


***************************************************************************************
static function pong(sck,body)
local hdr1:=bin(0x8a)       //FIN=1, OP=pong
local hdr2:=bin(len(body))  //MSK=0, len (len<=125)
    sck:send(hdr1+hdr2+body) //body from the corresponding ping


***************************************************************************************
function writemessage(sck,msg)

local hdr:=bin(129)
local len, pll, n

    msg::=str2bin
    len:=len(msg)

    if( len<126 )
        hdr+=bin(len) //payload length

    elseif( len<=0xffff )
        hdr+=bin(126)
        pll:=a""
        for n:=1 to 2
            pll:=bin(mod(len,256))+pll
            len:=int(len/256)
        next
        hdr+=pll

    else
        hdr+=bin(127)
        pll:=a""
        for n:=1 to 8
            pll:=bin(mod(len,256))+pll
            len:=int(len/256)
        next
        hdr+=pll
    end

    sck:send(hdr+msg)



***************************************************************************************
function close(sck)
    sck:send(x"8800")


***************************************************************************************
static function xxmask(x,key) //ezt inkább C-ben
local y:=a"",i,j
    for i:=1 to len(x)
        j:=i%4
        if( j==0 )
            j:=4
        end
        y+=numxor(key[j]::asc,x[i]::asc)::bin
    next
    return y


***************************************************************************************
function handshake(hsreq) //handshake request

local hsrsp:=<<HANDSHAKE>>HTTP/1.1 101 Switching Protocols
Upgrade: websocket
Connection: Upgrade
Sec-WebSocket-Accept: ACCEPTKEY

<<HANDSHAKE>>::str2bin

local magic:=a"258EAFA5-E914-47DA-95CA-C5AB0DC85B11"
local key,akey

    key:=http_getheader(hsreq,"Sec-WebSocket-Key")

    akey:=key
    akey+=magic
    akey::=crypto_sha1()
    akey::=base64_encode

    hsrsp::=strtran("ACCEPTKEY",akey)

    hsrsp::=strtran(x"0d",x"")
    hsrsp::=strtran(x"0a",x"0d0a")  // Chromium!
    
    return hsrsp  //handshake response  (X típus)


***************************************************************************************
