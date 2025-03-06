
#include "ssl.ch"
#include "smtp.ch"

******************************************************************************************
class smtp(object)

    attrib  sock
    attrib  header_list
    attrib  address_list
    attrib  attachment_list
    attrib  timeout
    attrib  cafile
    attrib  debug

    method  open
    method  auth
    method  header_add
    method  address_add
    method  attachment_add_path
    method  attachment_add_mem
    method  mail
    method  close

    method  initialize


******************************************************************************************
static function smtp.initialize(this)

    this:sock:=NIL
    this:header_list:={}
    this:address_list:={}
    this:attachment_list:={}
    this:timeout:=20000 //20sec
    this:cafile:=NIL
    this:debug:=.f.

    return this


******************************************************************************************
static function smtp.open(this,ip,port,security,cafile)

local ctx

    this:sock:=socketNew()
    this:sock:connect(ip,port)

    if( security==SMTP_SECURITY_TLS )
        ctx:=sslctxNew("TLS_client")
        set_cafile(ctx,cafile)
        this:sock:=sslconConnect(ctx,this:sock) //socket -> sslcon
    end

    smtp.read(this,SMTP_READY)
    smtp.ehlo(this)

    if( security==SMTP_SECURITY_STARTTLS )
        smtp.write(this,"STARTTLS")
        smtp.read(this)
        ctx:=sslctxNew("TLS_client")
        set_cafile(ctx,cafile)
        this:sock:=sslconConnect(ctx,this:sock) //socket -> sslcon
        smtp.ehlo(this)
    end

    smtp.read(this)


static function set_cafile(ctx,cafile)
    if( cafile!=NIL )
        ctx:set_verify( SSL_VERIFY_PEER_CERT)
        ctx:set_verify_depth(1)
        ctx:load_verify_locations(cafile)
    end


******************************************************************************************
static function smtp.auth(this,auth_method,user,pass)
local e

    if( auth_method==SMTP_AUTH_PLAIN )
        smtp.auth_plain(this,user,pass)

    //elseif( auth_method==SMTP_AUTH_LOGIN )
    //    smtp.auth_login(this,user,pass)

    elseif( auth_method==SMTP_AUTH_CRAM_MD5 )
        smtp.auth_cram_md5(this,user,pass)

    elseif( auth_method==SMTP_AUTH_NONE )
        //ok
    else
        e:=apperrorNew()
        e:subsystem:="smtp"
        e:operation:="smtp.auth"
        e:description:="unknown authorization method"
        e:args:={auth_method}
        break(e)
    end


******************************************************************************************
static function smtp.auth_plain(this,user,pass)
local login,rsp
    login:=bin(0)+str2bin(user)+bin(0)+str2bin(pass)
    smtp.write(this,a"AUTH PLAIN "+base64_encode(login))
    rsp:=smtp.read(this, SMTP_AUTH_SUCCESS)


******************************************************************************************
static function smtp.auth_cram_md5(this,user,pass)

local rsp
local challenge
local hmac
local b64_auth

    smtp.write(this,"AUTH CRAM-MD5")
    rsp:=smtp.read(this, SMTP_AUTH_CONTINUE)

    rsp::=strtran(bin(13),a"")
    rsp::=strtran(bin(10),a"")
    rsp::=split(bin(32))[2]
    challenge:=base64_decode(rsp)
    hmac:=hmac(str2bin(pass),str2bin(challenge))
    b64_auth:=base64_encode(str2bin(user)+a" "+str2bin(hmac::bin2hex))

    smtp.write(this,b64_auth)
    rsp:=smtp.read(this, SMTP_AUTH_SUCCESS)


******************************************************************************************
static function smtp.address_add(this,type,addr,name)
    this:address_list::aadd( smtp.addressNew(type,addr,name) )


******************************************************************************************
static function smtp.header_add(this,key,value)
    this:header_list::aadd( smtp.headerNew(key,value) )


******************************************************************************************
static function smtp.attachment_add_mem(this,name,data)
    this:attachment_list::aadd( smtp.attachmentNew(name,base64_encode(data)) )


******************************************************************************************
static function smtp.attachment_add_path(this,name,path)
local e,data:=memoread(path,.t.)
    if( empty(data) )
        e:=apperrorNew()
        e:subsystem:="smtp"
        e:operation:="smtp.attachment_add_path"
        e:description:="file not found"
        e:args:={name,path}
        break(e)
    end
    this:attachment_list::aadd( smtp.attachmentNew(name,base64_encode(data)) )


******************************************************************************************
static function smtp.mail(this,body)

local rsp
local n,h,a
local domain
local bnd:=gen_mime_boundary()

    smtp.mail_envelope_header_from(this)
    smtp.mail_envelope_header_to(this)

    smtp.write(this,"DATA")
    rsp:=smtp.read(this,SMTP_BEGIN_MAIL)

    if( 0==ascan(this:header_list,{|x|x:key=="Message-ID"}) )
        if( 0<(n:=ascan(this:address_list,{|x|x:type==SMTP_ADDRESS_FROM})) )
            if( 0<(domain:=at("@",this:address_list[n]:email)) )
                domain:=this:address_list[n]:email::substr(domain+1)
                this:header_add("Message-ID",gen_message_id(domain))
            end
        end
    end
    if( 0==ascan(this:header_list,{|x|x:key=="Date"}) )
        this:header_add("Date",smtp.time())
    end
    smtp.append_address_to_header(this, SMTP_ADDRESS_FROM, "From")
    smtp.append_address_to_header(this, SMTP_ADDRESS_TO, "To")
    smtp.append_address_to_header(this, SMTP_ADDRESS_CC, "Cc")

    for n:=1 to len(this:header_list)
        h:=this:header_list[n]
        smtp.write(this,h:key+": "+h:value)
    next

    body::=str2bin
    body::=strtran(x"0a2e",x"0a2e2e") // '\n.' -> '\n..'

    if( 0<ascan(this:header_list,{|x|x:key=="Content-Type"}) )
        smtp.print_nomime_email(this, body)
    else
        smtp.print_mime_email(this,bnd,body)
    end

    for n:=1 to len(this:attachment_list)
        a:=this:attachment_list[n]
        smtp.print_mime_attachment(this,bnd,a)
    next

    smtp.print_mime_end(this,bnd);


    smtp.write(this,".")
    smtp.read(this,SMTP_DONE)


******************************************************************************************
static function smtp.print_nomime_email(this, body)
    smtp.write(this,body)


******************************************************************************************
static function smtp.print_mime_email(this,bnd,body)

local msg
local eol:=x"0d0a"

    msg:=a"MIME-Version: 1.0"+eol
    msg+=a"Content-Type: multipart/mixed; boundary="+bnd+eol+eol
    msg+=a"Multipart MIME message."+x"0d0a"
    msg+=a"--"+bnd+eol
    msg+=a'Content-Type: text/plain; charset="UTF-8"'+eol+eol
    msg+=body+eol+eol

    smtp.write(this,msg)


******************************************************************************************
static function smtp.print_mime_attachment(this,bnd,attachment)
local msg
local eol:=x"0d0a"

    msg:=a"--"+bnd+eol
    msg+=a"Content-Type: application/octet-stream"+eol
    msg+=a'Content-Disposition: attachment; filename="'+str2bin(attachment:name)+a'"'+eol
    msg+=a"Content-Transfer-Encoding: base64"+eol+eol
    msg+=attachment:b64_data+eol
    
    smtp.write(this,msg)


******************************************************************************************
static function smtp.print_mime_end(this,bnd)
local msg
local eol:=x"0d0a"
    msg:=a"--"+bnd+a"--"
    smtp.write(this,msg)


******************************************************************************************
static function gen_mime_boundary()
static seed:=rand(seconds())
local bnd:=a"mime",n
    for n:=1 to 10
        bnd+=bin(asc("A")+random()%26)
    end
    return bnd


******************************************************************************************
static function gen_message_id(domain)
static seed:=rand(seconds())
local id,n
    id:=date()::dtos
    id+=time()::strtran(":","")
    id+="."
    for n:=1 to 10
        id+=chr(asc("a")+random()%26)
    next
    id+="@"+domain
    id:="<"+id+">"
    
    return id


******************************************************************************************
static function smtp.append_address_to_header(this, type, key)
local n,a,value
    for n:=1 to len(this:address_list)
        if( this:address_list[n]:type==type )
            a:=this:address_list[n]
            if( a:name==NIL )
                value:=""
            else
                value:='"'+a:name+'"'
            end
            value+=' <'+a:email+'>'
            this:header_add(key,value)
        end
    next


******************************************************************************************
static function smtp.mail_envelope_header_from(this)
local n,header,rsp
    for n:=1 to len(this:address_list)
        if( this:address_list[n]:type!=SMTP_ADDRESS_FROM  )
            loop
        end
        header:="MAIL FROM:"
        header+="<"+this:address_list[n]:email+"> SMTPUTF8"
        smtp.write(this,header)
        rsp:=smtp.read(this,SMTP_DONE)
        exit
    next

static function smtp.mail_envelope_header_to(this)
local n,header,rsp
    for n:=1 to len(this:address_list)
        if( this:address_list[n]:type==SMTP_ADDRESS_FROM )
            loop
        end

        // minden cimre, ami nem SMTP_ADDRESS_FROM
        header:="RCPT TO:"
        header+="<"+this:address_list[n]:email+">" // itt nem lehet SMTPUTF8
        smtp.write(this,header)
        rsp:=smtp.read(this,SMTP_DONE)
    next


******************************************************************************************
static function smtp.close(this)
    smtp.write(this,"QUIT")
    smtp.read(this) // SMTP_CLOSE  (221 Bye)
    this:sock:close


******************************************************************************************
static function smtp.ehlo(this)
    smtp.write(this,"EHLO smtp")


******************************************************************************************
static function smtp.write(this,x)
local nbyte,e
    x::=str2bin

    nbyte:=this:sock:send(x)
    if( nbyte!=len(x) )
        e:=apperrorNew()
        e:subsystem:="smtp"
        e:operation:="smtp.write"
        e:description:="cannot send data"
        e:args:={nbyte,len(x)}
        break(e)
    end
    
    if( 2!=this:sock:send(x"0d0a") )
        e:=apperrorNew()
        e:subsystem:="smtp"
        e:operation:="smtp.write"
        e:description:="cannot send EOL"
        break(e)
    end

    if( this:debug )
        ?? "client:    ",x;?
    end


******************************************************************************************
static function smtp.read(this,expected)
local e,rsp,arsp,i

    if( this:sock:waitforrecv(this:timeout) )
        rsp:=this:sock:recvall(this:timeout)
    else
        e:=apperrorNew()
        e:subsystem:="smtp"
        e:operation:="smtp.read"
        e:description:="no response"
        break(e)
    end
    if( this:debug )
        arsp:=rsp::strtran(bin(13),a"")::split(bin(10))
        for i:=1 to len(arsp)
            ?? "server:",arsp[i];?
        next
    end

    if( expected!=NIL .and. expected!=val(rsp) )
        e:=smtp.errorNew(expected,rsp)
        break(e)
    end

    return rsp


******************************************************************************************


