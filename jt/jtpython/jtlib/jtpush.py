##! /usr/bin/env python
# _*_ coding: latin-1 _*_
 

import jtutil
from jtelem import jtelem
 
class new(jtelem):

    def __init__(self,top=None,left=None,bottom=None,right=None,txt=None):

        jtelem.__init__(self,top,left,bottom,right)
        self.text=jtutil.alt(txt,txt,"")
 
    def classname(self):
        return "jtpush"

