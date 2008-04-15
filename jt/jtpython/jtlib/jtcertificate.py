##! /usr/bin/env python
# _*_ coding: latin-1 _*_

import jtutil 
import jtsocket
import jtdom
 

def jtcertificate(alias):

    # Elk�ri a termin�lt�l a keystore-ban alias-szal
    # azonos�tott bejegyz�s tan�s�tv�ny�t (nyilv�nos kulcs�t).

    NL="\n"
    LW=76
 
    x="<jtcertificate>"
    x+=alias
    x+="</jtcertificate>"
 
    jtsocket.send(x)

    while 1:
        rsp=jtsocket.recv()
        if rsp==None:
            return None
        dom=jtdom.domparse(rsp)
        node=jtdom.domfirst(dom)
        type=jtdom.domname(node)
        if type=="certificate":
            x=jtdom.domtext(node)+NL 
            cert="-----BEGIN CERTIFICATE-----"+NL
            while x:
                cert+=x[:LW]
                x=x[LW:]
                if not cert.endswith(NL):
                    cert+=NL
            cert+="-----END CERTIFICATE-----"+NL
            return cert

