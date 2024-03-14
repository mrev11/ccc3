##! /usr/bin/env python
# _*_ coding: UTF-8 _*_
 
from . import jtradio
 
class new(jtradio.new):

    def __init__(self):
        jtradio.new.__init__(self)
 
    def classname(self):
        return "jtmenuradio"

