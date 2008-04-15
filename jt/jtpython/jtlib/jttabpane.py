##! /usr/bin/env python
# _*_ coding: latin-1 _*_
 

import jtdom
import jtutil
from jtelem import jtelem
 
class new(jtelem):

    def __init__(self,top=None,left=None,bottom=None,right=None):
        jtelem.__init__(self,top,left,bottom,right)
        self.itemlist=[]
        self.selectedindex=1
        self.placement=None
 

    def classname(self):
        return "jttabpane"

    def setdialogid(self,id):
        self.dialogid=id
        for c in self.itemlist:
            c.setdialogid(self.dialogid)
 
    def additem(self,item):
        item.setdialogid(self.dialogid)
        self.itemlist.append(item) 
        return item

 
    def xmladd(self):
        x=""
        for c in self.itemlist:
            x+=c.xmlout()+jtutil.EOL

        if self.selectedindex!=1:
            x+="<selectedindex>"+str(self.selectedindex)+"</selectedindex>"+jtutil.EOL

        if self.placement:
            x+="<placement>"+self.placement+"</placement>"+jtutil.EOL

        return x
 
 
    def xmlput(self,x):
        self.selectedindex=int(jtdom.domtext(x))

    def xmlget(self):
        return str(self.selectedindex)

    def changed(self):
        return self.laststate!=self.selectedindex

    def savestate(self):
        self.laststate=self.selectedindex

    def varput(self,x):
        self.selectedindex=x
        return x

    def varget(self):
        return self.selectedindex

    def select(self,x):
        self.selectedindex=x

