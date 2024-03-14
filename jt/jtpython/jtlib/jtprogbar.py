##! /usr/bin/env python
# _*_ coding: UTF-8 _*_


import os
import string

from . import jtutil
from .jtelem import jtelem
 
class new(jtelem):

    def __init__(self,top=None,left=None,bottom=None,right=None,txt=None):

        jtelem.__init__(self,top,left,bottom,right)
        self.name="progressbar" 
        self.text=jtutil.alt(txt,txt,"")
        self.caption=""
        self.value=0
        self.minvalue=0
        self.maxvalue=100

    def classname(self):
        return "jtprogbar"

    def xmladd(self):
        x=""
        if self.minvalue!=0:
            x+="<min>"+str(int(self.minvalue))+"</min>"
        if self.maxvalue!=0:
            x+="<max>"+str(int(self.maxvalue))+"</max>"
        if self.caption:
            x+="<caption>"+jtutil.cdataif(self.caption)+"</caption>"
        return x
 
    def setbar(self,v=None,t=None,c=None):
        if v:
            self.value=int(v)
        if t:
            self.text=t
        if c:
            self.caption=c
 
        x='<jtmessage'
        x+=jtutil.ATTR("pid",str(os.getpid()))
        x+=jtutil.ATTR("dialogid",self.dialogid)
        x+='>'

        x+="<control>"+self.name+"</control>"
        x+="<setbar>"
        x+="<value>"+str(self.value%self.maxvalue)+"</value>" 
        if t:
            x+="<text>"+jtutil.cdataif(self.text.strip())+"</text>" 
        if c:
            x+="<caption>"+jtutil.cdataif(self.caption.strip())+"</caption>" 
        x+="</setbar>"
        x+="</jtmessage>"

        self.send(x)
        self.value+=1

 
    def clearbar(self):
        x='<jtmessage'
        x+=jtutil.ATTR("pid",str(os.getpid()))
        x+=jtutil.ATTR("dialogid",self.dialogid)
        x+='>'
        x+="<control>"+self.name+"</control>"
        x+="<clearbar/>"
        x+="</jtmessage>"
        self.send(x)
 