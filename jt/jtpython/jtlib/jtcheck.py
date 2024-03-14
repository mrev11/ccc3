##! /usr/bin/env python
# _*_ coding: UTF-8 _*_
 
from . import jtdom
from . import jtutil
from .jtelem import jtelem

class new(jtelem):

    def __init__(self,top=None,left=None,bottom=None,right=None,txt=None):
        jtelem.__init__(self,top,left,bottom,right)
        self.state=jtutil.false
        self.selectedicon=None
        if txt:
            self.text=txt
 

    def classname(self):
        return "jtcheck"
        

    def xmladd(self):
        x=""
        if self.state:
            x+="<selected/>"
        if self.selectedicon:
            x+="<selectedicon>"+self.selectedicon+"</selectedicon>"
        return x
 
 
    def xmlput(self,x):
        self.state=jtdom.domtext(x)=="true"
        return self.state
 

    def xmlget(self):
        return jtutil.alt(self.state,"true","false")
 

    def changed(self):
        return self.laststate!=self.state 


    def savestate(self):
        self.laststate=self.state 
        return self.state  


    def varput(self,x):
        self.state=not not x
        return self.state 


    def varget(self):
        return self.state 


    def select(self,x):
        self.state=not not x
        return self.state 
 

 
