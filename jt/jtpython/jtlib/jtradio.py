##! /usr/bin/env python
# _*_ coding: UTF-8 _*_
 
import weakref

from . import jtutil
from . import jtdom
from .jtelem import jtelem


class new(jtelem):

    def __init__(self,top=None,left=None,bottom=None,right=None,txt=None):
        jtelem.__init__(self,top,left,bottom,right)
        self.group=None
        self.state=jtutil.false
        self.selectedicon=None
        if txt:
            self.text=txt
        
 
    def classname(self):
        return "jtradio"


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


    def varput(self):
        self.state=not not x
        return self.state


    def varget(self):
        return self.state


    def setgroup(self,grp):
        wrs=weakref.ref(self) 
        if self.group  and  wrs in self.group:
            self.group.remove(wrs)
        self.group=grp
        self.group.append(wrs)
 

    def select(self):
        if self.group:
            wrs=weakref.ref(self) 
            for x in self.group:
                x().state=wrs==x
        else:
            self.state=jtutil.true

