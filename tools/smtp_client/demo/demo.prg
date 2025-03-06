
#include "smtp.ch"


******************************************************************************************
function main()

local smtp:=smtpNew()

local body:=<<BODY>>
Öt szép szűzlány őrült írót nyúz.
<<BODY>>

    smtp:debug:=.t.

    // connect
    smtp:open("comfirm.hu",465,SMTP_SECURITY_TLS)
    //smtp:open("i3x",465,SMTP_SECURITY_TLS)
    smtp:auth(SMTP_AUTH_CRAM_MD5,"vermes","*********")

    // from
    smtp:address_add(SMTP_ADDRESS_FROM,"vermes@comfirm.hu","Vermes Mátyás")

    // to
    smtp:address_add(SMTP_ADDRESS_TO,"vermes@comfirm.hu","Vermes Mátyás")        // comfirm
    //smtp:address_add(SMTP_ADDRESS_TO,"mrev1011@gmail.com","Vermes Mátyás")       // gmail
    //smtp:address_add(SMTP_ADDRESS_TO,"check-auth@verifier.port25.com")           // port25
    //smtp:address_add(SMTP_ADDRESS_TO,"vermes@i3x")                               // i3x


    smtp:header_add("Subject","Próba szerencse")
    smtp:attachment_add_mem("attach1","Van, aki forrón szereti")
    smtp:attachment_add_path("attach2","demo.prg")

    smtp:mail(body)
    smtp:close

    ?

******************************************************************************************

