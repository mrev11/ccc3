##! /usr/bin/env python
# _*_ coding: UTF-8 _*_
 
from . import jtutil
from .jtelem import jtelem
 
class new(jtelem):

    def __init__(self):
        jtelem.__init__(self)
        self.name=jtutil.jtcontrolid()
 
    def classname(self):
        return "jtmenuitem"

