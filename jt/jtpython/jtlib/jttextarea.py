##! /usr/bin/env python
# _*_ coding: UTF-8 _*_
 
from . import jtdom
from . import jtutil
from .jtelem import jtelem
 
class new(jtelem):

    def __init__(self,top=None,left=None,bottom=None,right=None):

        jtelem.__init__(self,top,left,bottom,right)
        self.editable=jtutil.true
        self.linewrap=jtutil.false
 
    def classname(self):
        return "jttextarea"


    def xmladd(self):
        x=""
        if not self.editable:
            x+="<editable>"
            x+=jtutil.alt(self.editable,"true","false")
            x+="</editable>"

        if self.linewrap:
            x+="<linewrap>"
            x+=jtutil.alt(self.linewrap,"true","false")
            x+="</linewrap>"
        return x
 

    def xmlput(self,x):
        self.text=jtdom.domtext(x)


    def xmlget(self):
        return jtutil.cdataif(self.text)


    def changed(self):
        return self.laststate!=self.text

    def savestate(self):
        self.laststate=self.text
 
