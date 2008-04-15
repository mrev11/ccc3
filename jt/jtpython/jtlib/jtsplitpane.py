##! /usr/bin/env python
# _*_ coding: latin-1 _*_
 

import jtutil
from jtelem import jtelem
 
class new(jtelem):

    def __init__(self,top=None,left=None,bottom=None,right=None):

        jtelem.__init__(self,top,left,bottom,right)

        self.name          = ""
        self.itemlist      = [None,None]
        self.orientation   = "ver"         # ver/hor 
        self.divider       = 0             # top/left méret 
 

    def classname(self):
        return "jtsplitpane"

 
    def setdialogid(self,id):
        self.dialogid=id
        for c in self.itemlist:
            if c:
                c.setdialogid(self.dialogid)
        return id


    def setitem(self,x,item):
        item.setdialogid(self.dialogid)
        self.itemlist[x-1]=item
        return item


    def xmladd(self):
        x=""
        x+="<orientation>"+self.orientation+"</orientation>"+jtutil.EOL
        if self.divider!=0:
            x+="<divider>"+str(self.divider)+"</divider>"+jtutil.EOL
        for c in self.itemlist:
            x+=c.xmlout()+jtutil.EOL
        return x

 