##! /usr/bin/env python
# _*_ coding: latin-1 _*_

import jtutil 
import jtsocket
import jtdom
 
 
def jtexec(cmd):

    jtsocket.send("<jtexec>"+jtutil.cdataif(cmd)+"</jtexec>")
    
    # <exitvalue>value</exitvalue>
    #  vagy
    # <execerror>error</execerror>

    while 1:
        rsp=jtsocket.recv()
        if rsp==None:
            return None

        dom=jtdom.domparse(rsp)  
        node=jtdom.domfirst(dom)
        type=jtdom.domname(node) 
        value=jtdom.domtext(node) 
 
        if type=="execerror":
            raise jtutil.applicationerror, ("jtexec", "failed", value)
        elif type=="exitvalue":
            return value
 
