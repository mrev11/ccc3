
#include "smtp.ch"


******************************************************************************************
function main()

local smtp:=smtpNew()

local body:=<<BODY>>
Öt szép szűzlány őrült írót nyúz. Öt szép szűzlány őrült írót nyúz.
Öt szép szűzlány őrült írót nyúz. Öt szép szűzlány őrült írót nyúz.
Öt szép szűzlány őrült írót nyúz. Öt szép szűzlány őrült írót nyúz.
Öt szép szűzlány őrült írót nyúz. Öt szép szűzlány őrült írót nyúz.
<<BODY>>

    smtp:debug:=.t.

    smtp:open("mail.comfirm.hu",465,SMTP_SECURITY_TLS)
    smtp:auth(SMTP_AUTH_CRAM_MD5,"vermes","********")

    smtp:address_add(SMTP_ADDRESS_FROM,"vermes@mail.comfirm.hu","Vermes Mátyás")
    smtp:address_add(SMTP_ADDRESS_TO,"vermes.matyas@comfirm.hu","Vermes Mátyás")
    smtp:address_add(SMTP_ADDRESS_TO,"vermes@comfirm.hu","drvermes")
    
    smtp:header_add("Subject","Próba szerencse")
    
    smtp:attachment_add_mem("attach1","Van, aki forrón szereti")
    smtp:attachment_add_path("attach2","demo.prg")
    smtp:mail(body)
    smtp:close

    ?

******************************************************************************************

    
