##! /usr/bin/env python
# _*_ coding: latin-1 _*_
 
import jtcheck
 
class new(jtcheck.new):

    def __init__(self):
        jtcheck.new.__init__(self)
 
    def classname(self):
        return "jtmenucheck"


