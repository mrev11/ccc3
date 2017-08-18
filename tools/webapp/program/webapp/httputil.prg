
***************************************************************************************
function httpheader_crlf(hdr)
    if(  valtype(hdr)=="X" )
        hdr::=strtran(x"0d",x"")
        hdr::=strtran(x"0a",x"0d0a")
    else
        hdr::=strtran(chr(13),"")
        hdr::=strtran(chr(10),chr(13)+chr(10))
    end
    return hdr


***************************************************************************************
function empty_response(xcode)
local CRLF:=x"0d0a"
local code:=xcode::str2bin::alltrim
local head:=a"HTTP/1.1 "+code+CRLF
    head+=a"Content-Type: text/plain"+CRLF
    head+=a"Content-Length: "+code::len::str::alltrim::str2bin+CRLF
    return head+CRLF+code //binary


***************************************************************************************
function line1(x:=a"")  //request első sora
local pos:=at(x'0a',x)
    return left(x,pos)


***************************************************************************************
function requrl(x:=a"") //request -> method + URL
local pos:=at(a' HTTP/',x)
    return left(x,pos)


***************************************************************************************
function geturl(x:=a"") // request -> url
local pos1:=at(a" ",x)
local pos2:=at(a" ",x,pos1+1)
local url:=x[pos1+2..pos2-1]::bin2str
    //? "GETURL["+url+"]"
    return  url


***************************************************************************************
function mkchunk(x)
    x::=str2bin
    x:=str2bin(x::len::l2hex::alltrim+chr(10))+x
    return x


***************************************************************************************
function startswith(x,y)
    return !(x!=y) //a jobbolodal hosszában egyenlők


***************************************************************************************
function commondata(req)
local page:=<<PAGE>>HTTP/1.1 200 Ok
Content-Length: LENGTH

<<PAGE>>
local x,len
local fspec:=geturl(req)
local enc,gzip:=.f.

    if( use_gzip_encoding() )
        enc:=http_getheader(req,"Accept-Encoding")
        gzip:=a"gzip"$enc
    end

    fspec:="common/"+fspec
    if( gzip .and. !empty(x:=memoread(fspec+".gz",.t.)) )
        gzip:=.t.
    elseif( !empty(x:=memoread(fspec,.t.)) )
        if( gzip )
            x::=zlib.deflate
            memowrit(fspec+".gz",x)
            ? "GZIPPED:",fspec
        end
    else
        return NIL
    end

    page::=str2bin
    page::=httpheader_crlf

    if( fspec::right(4)==".css" )
        page::=http_setheader("Content-Type","text/css")
    elseif( fspec::right(3)==".js" )
        page::=http_setheader("Content-Type","text/javascript")
    end
    
    if(gzip)
        page::=http_setheader("Content-Encoding","gzip")
    end
    
    len:=x::len::str::alltrim::str2bin
    page::=strtran(a"LENGTH",len)

    page+=x 

    return page //X típus


***************************************************************************************
function sessiondata(req)

/* req: 
GET /webapp/dnload/SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS/fspec HTTP/
123456789012345678901234567890123456789012345678901234567890
         1         2         3         4         5         6
*/

local page:=<<X>>HTTP/1.1 200 Ok
Content-Type: application/octet-stream
Content-Length: LENGTH

<<X>> //C típus

local sessionid
local pos
local fspec
local content
local enc,gzip:=.f.

    if( use_gzip_encoding() )
        enc:=http_getheader(req,"Accept-Encoding")
        gzip:=a"gzip"$enc
    end

    req::=bin2str

    sessionid:=req[20..51]
    pos:=at(a" HTTP/",req)
    fspec:=req[53..pos-1]
    fspec:=sessiondir(sessionid)+dirsep()+fspec
    content:=memoread(fspec,.t.) //X típus

    if( empty(content) )
        return NIL
    end

    page::=str2bin
    page::=httpheader_crlf

    if(gzip)
        content::=zlib.deflate
        page::=http_setheader("Content-Encoding","gzip")
        ? "GZIPPED:",fspec
    end
    page::=strtran(a"LENGTH",content::len::str::alltrim::str2bin)
    page+=content

    return page


***************************************************************************************
static function sessiondir(sessionid)
local dspec:="session"

    //if( !direxist(dspec) )
    //    dirmake(dspec)
    //end
    
    dspec+=dirsep()+sessionid[1..2]

    //if( !direxist(dspec) )
    //    dirmake(dspec)
    //end

    dspec+=dirsep()+sessionid

    //if( !direxist(dspec) )
    //    dirmake(dspec)
    //end
    
    return dspec


***************************************************************************************
    
    
