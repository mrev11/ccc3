##! /usr/bin/env python
# _*_ coding: UTF-8 _*_
 
from . import jtcheck
 
class new(jtcheck.new):

    def __init__(self):
        jtcheck.new.__init__(self)
 
    def classname(self):
        return "jtmenucheck"


