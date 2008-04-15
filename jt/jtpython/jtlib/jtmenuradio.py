##! /usr/bin/env python
# _*_ coding: latin-1 _*_
 
import jtradio
 
class new(jtradio.new):

    def __init__(self):
        jtradio.new.__init__(self)
 
    def classname(self):
        return "jtmenuradio"

