##! /usr/bin/env python
# _*_ coding: latin-1 _*_

import jtutil 
import jtsocket
import jtdom
 
def jtgetenv(name):

    jtsocket.send("<jtgetenv>"+name+"</jtgetenv>")
    
    # <jtenv>
    #   <name>n</name>
    #   <value>v</value>
    # </jtenv>
    
    while 1:
        rsp=jtsocket.recv()
        if rsp==None:
            return None

        dom=jtdom.domparse(rsp)  
        node=jtdom.domfirst(dom)
        type=jtdom.domname(node)

        if type=="jtenv":
            n=None
            v=None
            node=jtdom.domfirst(node)
            while node:
                if jtdom.domname(node)=="name":
                    n=jtdom.domtext(node) 
                if jtdom.domname(node)=="value":
                    v=jtdom.domtext(node) 
                node=jtdom.domnext(node)
            return jtutil.alt(n==name,v,None)


def jtsetenv(name,value=None):
    x="<jtsetenv>"
    x+="<name>"+name+"</name>" 
    if value:
        x+="<value>"+jtutil.cdataif(value)+"</value>" 
    x+="</jtsetenv>"
    jtsocket.send(x)
 

 
 