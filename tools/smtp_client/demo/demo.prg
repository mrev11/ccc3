
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

