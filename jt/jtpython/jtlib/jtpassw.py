##! /usr/bin/env python
# _*_ coding: latin-1 _*_

# Olyan text mez�,
# aminek nincs picture-je,
# minden karakter "*"-k�nt jelenik meg,
# az eredm�ny pedig: 
# base64.encode( text ) #ha salt1 �s salt2 sincs megadva
# base64.encode( md5(text+saltX) ) #ha csak saltX van megadva
# base64.encode( md5( md5(text+salt1)+salt2 ) ) #ha salt1 �s salt2 adott
 
# A jelsz� mez�t lehet inicializ�lni (a val�di jelsz�val),
# ez a termin�lban "**...*"-k�nt l�tszik, �s nem j�n vissza,

# Mi�rt nincs egy ellen�rz� met�dus?
#
# 1. Az ellen�rz�s f�gg att�l, hogy a szerver mit t�rol.
#
# 2. Az ellen�rz�s az openssl k�nyvt�rat h�vn�, 
#    amire csak akkor c�lszer� hivatkozni, ha t�nyleg kell,
#    hogy ne akad�lyozza feleslegesen a linkel�st.

# �gy lehet az ellen�rz�st elv�gezni, felt�ve, 
# hogy ismerj�k a jelsz�t, ami az al�bbi p�ld�ban "hopp":
#
# local p:="hopp"
# local x:=pwfield:getpassword(s1,s2)
#     ? p
#     ? p:=crypto_md5( p+s1 )
#     ? p:=crypto_md5( p+s2 )
#     ? p:=base64_encode(p)
#     ? x
#     alert( "Jelsz� "+ if(p==x,"OK","ELT�R") )

# V�ltozott a koncepci�:
# Kor�bban a k�dolt jelsz�t a termin�l akci�kor automatikusan k�ldte
# a kontroll �rt�kek�nt, �s az a varget met�dussal volt lek�rdezhet�.
# Ez azonban nem adott alkalmat a salt be�ll�t�s�ra, ami �ltal�ban a
# felhaszn�l� kil�t�t�l f�gg, ez�rt most a jelsz�t a termin�l egy�ltal�n
# nem k�ldi akci�n�l, hanem csak a getpassword �zenetre v�laszk�nt,
# �gy van alkalom el�z�leg be�ll�tani a salt-okat, �s nem k�ld�nk 
# idejekor�n f�lig rejtett jelszavakat

 

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

        # A termin�l a .keystore-b�l el�veszi az alias-hoz
        # tartoz� priv�t RSA kulcsot, �s azzal al��rja data-t,
        # az al��r�st visszak�ldi base64 k�dolt form�ban.


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

        # ha ez be volna ford�tva,
        # maga ut�n h�zn� az openssl k�nyvt�rat
 
        # alias : a J�va keystore-ban azonos�tja a kulcsot
        # cert  : pem form�tum� CERTIFICATE vagy PUBLIC KEY 

        data=crypto_rand_pseudo_bytes(32) 
        repl=self.sign(alias,data) 
        sign=base64_decode(repl)
 
        return crypto_verify(data,cert,sign)  #true/false
"""
 

"""
Hiteles�t�s digit�lis al��r�ssal

1. A kuncsaft csin�l mag�nak egy RSA kulcsp�rt a J�va keytools
   programj�val. Esetleg k�s�bb ehhez lehet csin�lni frontendet.
   A keystore-b�l export�lja a certificate-ot (vagy a public key-t):

   keytool -export -rfc -storepass ???? -alias vermes1 -file vermes1.cer
   
   Ebb�l egy ilyen fil� lesz (vermes1.cer):
   
-----BEGIN CERTIFICATE-----
MIIDWTCCAkECBD4oB7UwDQYJKoZIhvcNAQEEBQAwcTELMAkGA1UEBhMCSFUxEDAOBgNVBAgTB0h1
...
BDaEmYaZykgRbYl4r/5ylixw6UuPr2k77VTJbMHpnPDUwY6pOxXMSvTcmssgc1m+RHo5PU4E4miC
YXiHOyct
-----END CERTIFICATE-----
   
   A certificate fil�t valahogy bek�ldi a szervernek, ahol azt t�roljuk,
   pl. egy adatb�zis mem�j�ban.
   
2. Egy dialogboxban megadja az alias nev�t (amin�l fogva a keystore-ban
   megtal�lhat� a kulcs)  �s a jelsz�t (ami sz�ks�ges a priv�t kulcs
   el�v�tel�hez a keystore-b�l). A jelsz�t nem k�ldi el a szervernek.
   
3. A szerver gener�l egy v�letlen sorozatot, ezt al��ratja a termin�llal,
   az al��r�st pedig a certificate (public key) birtok�ban ellen�rzi.
   A certificate �rv�nyess�g�t egy�ltal�n nem ellen�rzi, csak azt n�zi,
   hogy a private �s public kulcsok t�nyleg p�rt alkossanak.
"""


