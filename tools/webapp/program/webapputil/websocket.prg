
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

namespace websocket


#define INDENT     chr(10)+"   "

#define DEBUGINFO  INDENT, "time            :", time(),         ;
                   INDENT, "frame_fin       :", frame_fin,      ;
                   INDENT, "frame_opcode    :", frame_opcode,   ;
                   INDENT, "frame_masked    :", frame_masked,   ;
                   INDENT, "frame_compress  :", frame_compress, ;
                   INDENT, "payload_len     :", payload_len,    ;    
                   INDENT, "timeout         :", timeout
                   

//egyik vagy masik
//#define WRITEMESSAGE_WHOLE      writemessage
#define WRITEMESSAGE_FRAGMENTED writemessage

#define FRGSIZ 8192

#define TIMEOUT 10000 //millisec 

***************************************************************************************
function readmessage(sck)

local err
local fragment,c,n
local frame_fin
local frame_opcode
local frame_masked
local frame_compress
local payload_len
local masking_key
local timeout:=TIMEOUT
local body

    while(.t.)

        frame_fin       :=NIL
        frame_opcode    :=NIL
        frame_masked    :=NIL
        payload_len     :=NIL
        masking_key     :=NIL

        begin
            if( len(c:=sck:recv(1,timeout))<1 )
                break("No opcode")
            else
                c::=asc
            end
            frame_fin:=(c::numand(0b10000000))!=0
            frame_opcode:=c::numand(0b00001111) //1=text 2=binary  8=close 9=ping 10=pong

            if( frame_compress==NIL )
                //(csak) az elso frame-ben
                //lehet beallitva a tomorites bit
                frame_compress:=(c::numand(0b01000000))!=0  //RSV1
            end

            if( len(c:=sck:recv(1,timeout))<1 )
                break("No payload_len1")
            else
                c::=asc
            end
            frame_masked:=(c::numand(0b10000000))!=0
            payload_len:=c::numand(0b01111111)
    
            if( payload_len==126 )
                payload_len:=0
                for n:=1 to 2
                    if( len(c:=sck:recv(1,timeout))<1 )
                        break("No payload_len2("+n::str::alltrim+")")
                    else
                        c::=asc
                    end
                    payload_len:=payload_len*256+c
                next
    
            elseif( payload_len==127 )
                payload_len:=0
                for n:=1 to 8
                    if( len(c:=sck:recv(1,timeout))<1 )
                        break("No payload_len8("+n::str::alltrim+")")
                    else
                        c::=asc
                    end
                    payload_len:=payload_len*256+c
                next
            end

    
            if( frame_masked )
                masking_key:=sck:recv(4,timeout)
                if( len(masking_key)!=4 )
                    break("No masking_key")
                end
            end

            fragment:=a""
            while( fragment::len<payload_len )
                c:=sck:recv(payload_len-(fragment::len),timeout)
                if( c==NIL )
                    break("Not enough data within timeout")
                else
                    fragment+=c
                end
            end
    
            if( frame_masked )
                fragment::=websocket.mask(masking_key)
            end
            
        recover err <C>    
            ? err, DEBUGINFO
            
            //mit adjunk vissza?
            //c: az utolso beolvasott byte vagy NIL
            //frame_opcode==NIL: egyetlen byte sem jott
            
            if( c==NIL .or. frame_opcode!=NIL )
                //megszakadt a kapcsolat
                //de legalabbis kiesett a szinkronbol
                return NIL
            else
                //egy byte sem jott
                //varakozas utan ujra lehet probalkozni
                return ""
            end
        end

        //? DEBUGINFO
        //? 
        //for n:=1 to len(fragment)
        //    ?? n::str(4)+"["+fragment[n]::asc::l2hex+"]"
        //next


        // fragmentation
        //  unfragmented message : A(FIN==1,OP!=0)  
        //  fragmented message   : B(FIN==0,OP!=0)  C(FIN==0,OP==0)*  D(FIN==1,OP==0)
        // control frames (ping, pong) are always unfragmented 
        // control frames may be injected in a fragmented message


        if( frame_opcode==0 ) //continuation
            //C|D eset
            if( body==NIL )  
                //ide nem johet:
                //ha nem eleg nagy a recv timeout-ja
                //(es raadasul rossz a hiba detektalasa)
                //akkor megis elofordul, hogy rafut erre az agra
                //a timeout-ot megnoveltem 1 sec-rol 100 sec-re
                //a recv eredmenyet NIL helyett hosszra kell ellenorizni
                //(a kovetkezo utasitason elszall)
            end
            
            body+=fragment
            if( frame_fin )
                return if(frame_compress,decompress(body),body)
            end

        elseif( frame_opcode==1 ) //text
            //A|B eset
            body:=fragment
            if( frame_fin )
                return if(frame_compress,decompress(body),body)
            end
            
        elseif( frame_opcode==2 ) //binary
            //A|B eset
            body:=fragment
            if( frame_fin )
                return if(frame_compress,decompress(body),body)
            end


        elseif( frame_opcode==8 ) //close
            ? "close", DEBUGINFO
            return NIL

        elseif( frame_opcode==9 ) //ping
            ? "ping", DEBUGINFO
            pong(sck,fragment) //visszakuld egy pongot

            if( body==NIL )
                //tovabb kell varni, de nem itt, hanem a hivo programban
                return "" 
            else
                //kozbeekelt ping, tovabb kell olvasni
            end

        elseif( frame_opcode==10 ) //pong
            ? "pong", DEBUGINFO
            if( body==NIL )
                //szolo pong, tovabb kell varni a hivo programban
                return ""
            else
                //kozbeekelt pong, tovabb kell olvasni
            end

        else
            ? "Invalid opcode",DEBUGINFO
            for n:=1 to len(fragment)
                ?? "  ["+fragment[n]::asc::l2hex+"]"
            next
            return NIL
        end
    end


***************************************************************************************
static function pong(sck,body)
local hdr1:=bin(0x8a)       //FIN=1, OP=pong
local hdr2:=bin(len(body))  //MSK=0, len (len<=125)
    sck:send(hdr1+hdr2+body) //body from the corresponding ping


***************************************************************************************
function WRITEMESSAGE_WHOLE(sck,msg) //egyben kuld
    if( webapp.logmessage() )
        ? "writemessage >>[",msg,"]"
    end
    msg::=str2bin
    writefragment(sck,bin(129),msg)


***************************************************************************************
function WRITEMESSAGE_FRAGMENTED(sck,msg) //darabolva kuld
local frgsiz:=FRGSIZ
local fin:=0, op:=1, def:=0

    if( webapp.logmessage() )
        ? "writemessage >>[",msg,"]"
    end
    msg::=str2bin

    if(use_compress())
        msg:=compress(msg)
        def:=64 //RSV1 bit
    end

    while( len(msg)>0 )
        if(len(msg)<=frgsiz)
            fin:=128
        end
        
        writefragment(sck,bin(fin+def+op),msg[1..frgsiz])
        op:=0
        def:=0
        msg:=msg[frgsiz+1..]
    end


***************************************************************************************
static function writefragment(sck,hdr,msg)
local len, pll, n

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
static function xxmask(x,key) //ezt inkabb C-ben
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
static function use_compress()
static flag:="permessage-deflate"$getenv("Sec-WebSocket-Extensions")
    return flag


***************************************************************************************
static function decompress(x)
static strm:=zlib.inflateinit2(-15) //winbit=15, 32K window, -15=RAW 
    //? "INFLATE", len(x), " ->"
    x:=zlib.inflate(strm,x+x"0000ffff")
    //?? len(x)
    return x


***************************************************************************************
static function compress(x)
static strm:=zlib.deflateinit2(NIL,-15)
static cnt:=0
    //? "DEFLATE", len(x), " ->"
    x:=zlib.deflate(strm,x,3) //Z_FULL_FLUSH
    x:=left(x,len(x)-4)
    //?? len(x)
    return x
    

***************************************************************************************

