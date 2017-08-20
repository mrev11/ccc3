
namespace websocket


***************************************************************************************
function handshake(hsreq) //handshake request

local hsrsp:=<<HANDSHAKE>>HTTP/1.1 101 Switching Protocols
Upgrade: websocket
Connection: Upgrade
Sec-WebSocket-Accept: ACCEPTKEY

<<HANDSHAKE>>::str2bin

local magic:=a"258EAFA5-E914-47DA-95CA-C5AB0DC85B11"
local wsv,wse,key,akey

    wsv:=http_getheader(hsreq,"Sec-WebSocket-Version")::bin2str
    wse:=http_getheader(hsreq,"Sec-WebSocket-Extensions")::bin2str
    key:=http_getheader(hsreq,"Sec-WebSocket-Key")

    putenv("Sec-WebSocket-Version="+wsv)
    putenv("Sec-WebSocket-Extensions=")

    akey:=key
    akey+=magic
    akey::=crypto_sha1()
    akey::=base64_encode

    hsrsp::=strtran("ACCEPTKEY",akey)
    
    hsrsp::=strtran(x"0d",x"")
    hsrsp::=strtran(x"0a",x"0d0a")  // Chromium!

    if( use_permessage_deflate() .and. "permessage-deflate"$wse )
        //akkor jon ide, ha a bongeszo engedi a tomoritest
        //az alabbi valasszal a szerver beleegyezik a tomoritesbe 
        //a tomorites RSV1 bitben uzenetenkent kibekapcsolhato

        hsrsp::=http_setheader("Sec-WebSocket-Extensions","permessage-deflate; client_no_context_takeover; server_no_context_takeover")
        putenv("Sec-WebSocket-Extensions="+wse)

        //nem tudom megoldani azt a problemat
        //hogy a tomorites folytatolagosan mukodik (a bongeszoben)
        //de a tomorites allapotat (a zstream strukturat es nyulvanyait)
        //nem lehet atadni a child processeknek
        //ezert egyelore ki van kapcsolva a tomorites
    end
    
    return hsrsp  //handshake response  (X típus)


***************************************************************************************
