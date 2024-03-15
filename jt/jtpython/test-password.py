#! /usr/bin/env python
# _*_ coding: UTF-8 _*_

import hashlib
from jtlib import *

passw="Próba szerencse!"
salt1="SALT1"
salt2="SALT2"
#salt1=None
#salt2=None
pwenc=None
pwver=None


class passw_dialog(jtdialog.new):
    # ezt msk-bol lehetne generálni

    def __init__(self,t=6,l=17,b=11,r=58):
        jtdialog.new.__init__(self,t,l,b,r)

        self.name='passw'
        self.layout='fix'

        self.add(jtlabel.new(1,3,1,12,'Password :'))

        self.passw=jtpassw.new(1,14,1,38)
        self.passw.name='passw'
        self.add(self.passw)

        self.ok=jtpush.new(3,14,3,21)
        self.ok.name='ok'
        self.ok.text='OK'
        self.add(self.ok)


dlg=passw_dialog()
dlg.varinst("passw")
dlg.var.passw.text=passw # előre kitölti
dlg.show()

while( True ):
    msg=dlg.getmessage()

    if( msg==None ):
        break

    elif( msg=="ok" ):

        pwenc=dlg.var.passw.getpassword(salt1,salt2) # XML-ből kapott string

        # az eredmény:
        # base64.encode( text ) //ha salt1 és salt2 sincs megadva
        # base64.encode( md5(text+saltX) ) //ha csak saltX van megadva
        # base64.encode( md5( md5(text+salt1)+salt2 ) ) //ha salt1 és salt2 adott

        pwver=passw

        if( None==salt1==salt2 ):
            pwver=jtutil.base64_encode(pwver)

        elif( None==salt2 ):
            pwver=jtutil.str2bin(pwver)
            pwver+=jtutil.str2bin(salt1)
            pwver=hashlib.md5(pwver).digest()
            pwver=jtutil.base64_encode(pwver)

        else:
            pwver=jtutil.str2bin(pwver)
            pwver+=jtutil.str2bin(salt1)
            pwver=hashlib.md5(pwver).digest()
            pwver+=jtutil.str2bin(salt2)
            pwver=hashlib.md5(pwver).digest()
            pwver=jtutil.base64_encode(pwver)


    print("passw",passw)
    print("salt1",salt1)
    print("salt2",salt2)
    print("pwenc",pwenc, type(pwenc))
    print("pwver",pwver, type(pwver))

    if( pwver==pwenc ):
        print("You are welcome")
    else:
        print("Wrong password")

