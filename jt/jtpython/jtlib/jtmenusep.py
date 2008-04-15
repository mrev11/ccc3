##! /usr/bin/env python
# _*_ coding: latin-1 _*_
 
from jtelem import jtelem
 
class new(jtelem):

    def __init__(self):
        jtelem.__init__(self)
 
    def classname(self):
        return "jtmenusep"
        
    def xmlout(self):
        return "<jtmenusep/>" 

 

