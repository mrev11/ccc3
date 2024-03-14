##! /usr/bin/env python
# _*_ coding: UTF-8 _*_
 
import sys

from . import jtutil 
from . import jtsocket
from . import jtdom
 

def jtalert(msg,opt=[]):
    msg="<html><p>"+msg.replace(";","<p>")
    if not opt:
        opt=["OK"]
    jtsocket.send( new(msg,opt).xmlout() )

    while 1:
        rsp=jtsocket.recv()
        if rsp==None:
            return 0
        dom=jtdom.domparse(rsp) 
        node=jtdom.domfirst(dom) #<alert>
        type=jtdom.domname(node)
        if type=="alert":
            return int(jtdom.domtext(node))
        

class new:

    def __init__(self,msg,opt=[]):

        self.message = msg
        self.caption = sys.argv[0]
        self.options = opt
        self.type    = jtutil.alt(len(opt)>1,"q","w")
        

    def xmlout(self):
        x="<jtalert>"
        x+="<message>"+jtutil.cdataif(self.message)+"</message>" 
        x+="<caption>"+jtutil.cdataif(self.caption)+"</caption>" 
        x+="<options>"
        for o in self.options:
            x+="<opt>"+jtutil.cdataif(o)+"</opt>" 
        x+="</options>"
        x+="<type>"+self.type+"</type>" 
        x+="</jtalert>"
        return x

 