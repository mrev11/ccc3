##! /usr/bin/env python
# _*_ coding: latin-1 _*_
 
import string

import jtutil 
import jtsocket
import jtdom
import jtalert
 

def jtversion():
    jtsocket.send("<jtversion/>")

    while 1:
        rsp=jtsocket.recv()
        if rsp==None:
            return ""
        
        dom=jtdom.domparse(rsp)  
        node=jtdom.domfirst(dom)
        type=jtdom.domname(node) 

        if type=="jtversion":
            return jtdom.domtext(node) 
 

def jtcheckversion(v):

    x=jtversion()
 
    ax=string.split(x,".",2)
    s1=0 
    s1+=val(ax[0])*10000
    s1+=val(ax[1])*100
    s1+=val(ax[2])
    print s1
 
    av=string.split(v,".",2)
    s0=0 
    s0+=val(av[0])*10000
    s0+=val(av[1])*100
    s0+=val(av[2])
    print s0
    
    if s1<s0:
        msg='Legalább <font color="red">'+v+'</font> változatszámú terminál kell!'
        msg+='<p>A jelenlegi '+x+' változat nem megfelelô.'
        msg+='<p>Letölthetô innen: <font color="blue">http://ok.comfirm.hu/jnlp/jterminal.jar<font>.'
        if 2>jtalert.jtalert(msg,["Kilép","Tovább"]):
            raise jtutil.applicationerror, ("jtcheckversion","failed",v,x)


def val(x):
    s=""
    x=string.strip(x)
    for c in x:
        if c in string.digits:
            s+=c
        else:
            break
    return int(s)
        
