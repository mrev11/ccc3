
#include "webapp.ch"

static option_hash:=load_config()

***************************************************************************************
static function load_config()
local conf:=dirsep()+curdir()+dirsep()+"config_webapp_defaults"
local hash:=webapp.loadconfig(conf)
    ? curdir()+dirsep()+"config_webapp_defaults loaded:"
    hash:list
    return hash


***************************************************************************************
function default_webapp()

local dwa,n

    dwa:=memoread( "config_webapp_start" )

    if( !dwa::empty )
        dwa::=split(chr(10))
        for n:=1 to len(dwa)
            dwa[n]::=strtran(chr(13),"")
            dwa[n]::=strtran(chr(9),"")
            dwa[n]::=strtran(chr(32),"")
            if( dwa[n]::empty )
                loop
            elseif( dwa[n]::left(1)=="#" )
                loop
            else
                return dwa[n]
            end
        next
    end

    dwa:=option_hash["start"]
    if( !empty(dwa) )
        return dwa
    end

    //dwa:= "table.exe"
    //dwa:= "skeleton.exe"
    //dwa:= "wlogin.exe"
    //dwa:= "wltp.exe"
    //dwa:= "wstart.exe"
    //dwa:= "wedit.exe"
    dwa:= "whello.exe"
    //dwa:= "wecho.exe"

    ? "default webapp", dwa

    return dwa


***************************************************************************************
static function default_interface()
local iface:=option_hash["iface"]
    return if(iface==NIL,"localhost",iface)

***************************************************************************************
static function default_port()
local port:=option_hash["port"]
    return if( port==NIL,45678,val(port))

***************************************************************************************
function sck_listener()
static sck
    if(sck==NIL)
        sck:=socketNew()
        sck:reuseaddress(.t.) //élesből kivenni
        sck:bind(default_interface(),default_port())
    end
    return sck

***************************************************************************************
function ssl_context()

static ctx
local keyfile:=option_hash["keyfile"]

    if(keyfile==NIL)
        keyfile:="webappdemo.pem"
    end

    if(ctx==NIL)
        ctx:=sslctxNew("TLSv1_server") 

        ctx:use_certificate_file("keys/"+keyfile)
        ctx:use_privatekey_file("keys/"+keyfile)
        ? "ssl_context use",keyfile
    end
    return ctx

//megjegyzés: csak akkor érdekes, ha use_ssl() true-t ad.


***************************************************************************************
function use_ssl()
static ssl:=if(option_hash["ssl"]=="false",.f.,.t.)
    return ssl  

// false: nem használ SSL-t, true: SSL-t használ, default=true
//
// Az SSL-lel osszhangban levo URL-t kell megadni a bongeszoben, pl.:
//  (plain)   http://localhost:45678/webapp 
//  (ssl)     https://localhost:45678/webapp


***************************************************************************************
function use_gzip_encoding()
static gzip:=if(option_hash["gzip"]=="false",.f.,.t.)
    return gzip

// false: nem tomorit, true: tomorit, default=true

***************************************************************************************

