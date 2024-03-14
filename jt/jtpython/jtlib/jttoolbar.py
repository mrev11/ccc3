##! /usr/bin/env python
# _*_ coding: UTF-8 _*_
 
from . import jtutil
from .jtelem import jtelem


class new(jtelem):

    def __init__(self):

        jtelem.__init__(self)

        self.name=""
        self.orientation=None
        self.itemlist=[]
        self.defaultradiogroup=[]
 

    def classname(self):
        return "jttoolbar"


    def xmlname(self):
        return "jttoolbar"
 

    def setdialogid(self,id):
        self.dialogid=id
        for c in self.itemlist:
            c.setdialogid(self.dialogid)
 

    def additem(self,item):
        item.setdialogid(self.dialogid)
        self.itemlist.append(item) 
        if item.classname()=="jtradio" and not item.group:
            item.setgroup(self.defaultradiogroup)
        return item
 

    def xmladd(self):
        x=""

        if self.orientation:
            x+="<orientation>"+self.orientation+"</orientation>"

        x+=jtutil.EOL 

        for c in self.itemlist:
            x+=c.xmlout()+jtutil.EOL

        return x

