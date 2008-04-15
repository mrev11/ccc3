##! /usr/bin/env python
# _*_ coding: latin-1 _*_
 
import jtutil
from jtelem import jtelem


class new(jtelem):

    def __init__(self,top=None,left=None,bottom=None,right=None):

        jtelem.__init__(self,top,left,bottom,right)
        self.name=""
        self.hscroll=jtutil.false
        self.vscroll=jtutil.false 
        self.layout="hbox" 
        self.itemlist=[]
        self.defaultradiogroup=[]
 

    def classname(self):
        return "jtpanel"


    def xmlname(self):
        return "jtpanel"
 

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

        if self.hscroll:
            x+="<hscroll/>"

        if self.vscroll:
            x+="<vscroll/>"

        if self.layout:
            x+="<layout>"+self.layout+"</layout>"

        x+=jtutil.EOL 

        for c in self.itemlist:
            x+=c.xmlout()+jtutil.EOL

        return x
 
