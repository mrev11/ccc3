##! /usr/bin/env python
# _*_ coding: UTF-8 _*_
 
from . import jtutil
from .jtelem import jtelem
 

class new(jtelem):

    def __init__(self,top=None,left=None,bottom=None,right=None,text=None):
 
        if type(top)==type(""):
            jtelem.__init__(self)
            self.text=top
            
        else:
            jtelem.__init__(self,top,left,bottom,right)
            if text:
                self.text=text

        self.name=""
 

    def classname(self):
        return "jtlabel"
 

def jticon(fspec):
    lb=new()
    lb.icon=fspec
    return lb


def jtimage(fspec):
    lb=new()
    lb.image=jtutil.memoread(fspec,True)
    return lb
