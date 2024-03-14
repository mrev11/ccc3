##! /usr/bin/env python
# _*_ coding: UTF-8 _*_
 
import os

from . import jtutil
from . import jtdom
from .jtelem import jtelem
 

class new(jtelem):

    def __init__(self,top=None,left=None,bottom=None,right=None):
        jtelem.__init__(self,top,left,bottom,right)
        self.followlink=jtutil.true
 

    def classname(self):
        return "jthtmlarea"


    def xmladd(self):
        x=""
        if not self.followlink:
            x+="<followlink>"
            x+="false"
            x+="</followlink>"
        return x
 

    def xmlput(self,x):
        self.text=jtdom.domtext(x)


    def xmlget(self):
        return jtutil.cdataif(self.text)


    def changed(self): 
        return self.laststate!=self.text


    def savestate(self): 
        self.laststate=self.text


    def changeurl(self,v=None):
        if v:
            self.text=v
        x='<jtmessage'
        x+=jtutil.ATTR("pid",str(os.getpid()))
        x+=jtutil.ATTR("dialogid",self.dialogid)
        x+='>'
        x+="<control>"+self.name+"</control>"
        x+="<changeurl>"
        x+=jtutil.cdataif(self.text)
        x+="</changeurl>"
        x+="</jtmessage>"
        self.send(x)

