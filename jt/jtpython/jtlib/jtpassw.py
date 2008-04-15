##! /usr/bin/env python
# _*_ coding: latin-1 _*_

# Olyan text mezõ,
# aminek nincs picture-je,
# minden karakter "*"-ként jelenik meg,
# az eredmény pedig: 
# base64.encode( text ) #ha salt1 és salt2 sincs megadva
# base64.encode( md5(text+saltX) ) #ha csak saltX van megadva
# base64.encode( md5( md5(text+salt1)+salt2 ) ) #ha salt1 és salt2 adott
 
# A jelszó mezõt lehet inicializálni (a valódi jelszóval),
# ez a terminálban "**...*"-ként látszik, és nem jön vissza,

# Miért nincs egy ellenõrzõ metódus?
#
# 1. Az ellenõrzés függ attól, hogy a szerver mit tárol.
#
# 2. Az ellenõrzés az openssl könyvtárat hívná, 
#    amire csak akkor célszerû hivatkozni, ha tényleg kell,
#    hogy ne akadályozza feleslegesen a linkelést.

# Így lehet az ellenõrzést elvégezni, feltéve, 
# hogy ismerjük a jelszót, ami az alábbi példában "hopp":
#
# local p:="hopp"
# local x:=pwfield:getpassword(s1,s2)
#     ? p
#     ? p:=crypto_md5( p+s1 )
#     ? p:=crypto_md5( p+s2 )
#     ? p:=base64_encode(p)
#     ? x
#     alert( "Jelszó "+ if(p==x,"OK","ELTÉR") )

# Változott a koncepció:
# Korábban a kódolt jelszót a terminál akciókor automatikusan küldte
# a kontroll értékeként, és az a varget metódussal volt lekérdezhetõ.
# Ez azonban nem adott alkalmat a salt beállítására, ami általában a
# felhasználó kilététõl függ, ezért most a jelszót a terminál egyáltalán
# nem küldi akciónál, hanem csak a getpassword üzenetre válaszként,
# így van alkalom elõzõleg beállítani a salt-okat, és nem küldünk 
# idejekorán félig rejtett jelszavakat

 

import os
import jtutil
import jtsocket
import jtdom
from jtelem import jtelem
 
class new(jtelem):

    def __init__(self,top=None,left=None,bottom=None,right=None):
        jtelem.__init__(self,top,left,bottom,right)
 
    def classname(self):
        return "jtpassw"

    def changed(self):
        return self.laststate!=self.text

    def savestate(self):
        self.laststate=self.text

    def clear(self):
        self.laststate=" "
        self.text=""


    def getpassword(self,salt1,salt2):
        x='<jtmessage'
        x+=jtutil.ATTR("pid",str(os.getpid()))
        x+=jtutil.ATTR("dialogid",self.dialogid)
        x+='>'
        x+="<control>"+self.name+"</control>"
        x+="<getpassword>"
        if salt1:
            x+="<salt1>"+jtutil.cdataif(salt1)+"</salt1>"
        if salt2:
            x+="<salt2>"+jtutil.cdataif(salt2)+"</salt2>"
        x+="</getpassword>"
        x+="</jtmessage>"

        self.send(x)

        while 1:
            rsp=jtsocket.recv()
            if rsp==None:
                return None
            dom=jtdom.domparse(rsp)
            node=jtdom.domfirst(dom)
            type=jtdom.domname(node)
            if type=="password":
                return jtdom.domtext(node) 
 


    def sign(self,alias,data):

        # A terminál a .keystore-ból elõveszi az alias-hoz
        # tartozó privát RSA kulcsot, és azzal aláírja data-t,
        # az aláírást visszaküldi base64 kódolt formában.


        x='<jtmessage'
        x+=jtutil.ATTR("pid",str(os.getpid()))
        x+=jtutil.ATTR("dialogid",self.dialogid)
        x+='>'
        x+="<control>"+self.name+"</control>"
        x+="<sign>"
        x+="<alias>"+alias+"</alias>"
        x+="<data>"+jtutil.base64_encode(data)+"</data>"
        x+="</sign>"
        x+="</jtmessage>"

        self.send(x)

        while 1:
            rsp=jtsocket.recv()
            if rsp==None:
                return None
            dom=jtdom.domparse(rsp)  
            node=jtdom.domfirst(dom)
            type=jtdom.domname(node)
            if type=="signature":
                return jtdom.domtext(node) 



"""
    def authenticate(this,alias,cert)

        # ha ez be volna fordítva,
        # maga után húzná az openssl könyvtárat
 
        # alias : a Jáva keystore-ban azonosítja a kulcsot
        # cert  : pem formátumú CERTIFICATE vagy PUBLIC KEY 

        data=crypto_rand_pseudo_bytes(32) 
        repl=self.sign(alias,data) 
        sign=base64_decode(repl)
 
        return crypto_verify(data,cert,sign)  #true/false
"""
 

"""
Hitelesítés digitális aláírással

1. A kuncsaft csinál magának egy RSA kulcspárt a Jáva keytools
   programjával. Esetleg késõbb ehhez lehet csinálni frontendet.
   A keystore-ból exportálja a certificate-ot (vagy a public key-t):

   keytool -export -rfc -storepass ???? -alias vermes1 -file vermes1.cer
   
   Ebbõl egy ilyen filé lesz (vermes1.cer):
   
-----BEGIN CERTIFICATE-----
MIIDWTCCAkECBD4oB7UwDQYJKoZIhvcNAQEEBQAwcTELMAkGA1UEBhMCSFUxEDAOBgNVBAgTB0h1
...
BDaEmYaZykgRbYl4r/5ylixw6UuPr2k77VTJbMHpnPDUwY6pOxXMSvTcmssgc1m+RHo5PU4E4miC
YXiHOyct
-----END CERTIFICATE-----
   
   A certificate filét valahogy beküldi a szervernek, ahol azt tároljuk,
   pl. egy adatbázis memójában.
   
2. Egy dialogboxban megadja az alias nevét (aminél fogva a keystore-ban
   megtalálható a kulcs)  és a jelszót (ami szükséges a privát kulcs
   elõvételéhez a keystore-ból). A jelszót nem küldi el a szervernek.
   
3. A szerver generál egy véletlen sorozatot, ezt aláíratja a terminállal,
   az aláírást pedig a certificate (public key) birtokában ellenõrzi.
   A certificate érvényességét egyáltalán nem ellenõrzi, csak azt nézi,
   hogy a private és public kulcsok tényleg párt alkossanak.
"""


