##! /usr/bin/env python
# _*_ coding: latin-1 _*_
 

import jtutil
from jtelem import jtelem
 
class new(jtelem):

    def __init__(self):
        jtelem.__init__(self)
        self.itemlist=[]
        self.defaultradiogroup=[]
 

    def classname(self):
        return "jtmenu"


    def setdialogid(self,id):
        self.dialogid=id
        for c in self.itemlist:
            c.setdialogid(self.dialogid)
        return id


    def additem(self,item):
        item.setdialogid(self.dialogid)
        self.itemlist.append(item) 
        if item.classname=="jtmenusep":
            self.defaultradiogroup=[]
        elif item.classname=="jtmenuradio" and not item.group:
            item.setgroup(self.defaultradiogroup)
        return item
 

    def xmladd(self):
        x=jtutil.EOL
        for c in self.itemlist:
            x+=c.xmlout()+jtutil.EOL
        return x
 
