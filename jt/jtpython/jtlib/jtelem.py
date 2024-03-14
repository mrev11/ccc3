##! /usr/bin/env python
# _*_ coding: UTF-8 _*_
 
import os

from . import jtutil
from . import jtsocket
 
class jtelem:

    def __init__(self,top=None,left=None,bottom=None,right=None):
 
        self.dialogid    = ""

        self.top         = top
        self.left        = left
        self.bottom      = bottom
        self.right       = right

        self.halign      = None
        self.valign      = None
        self.alignx      = None
        self.aligny      = None
        self.name        = jtutil.jtcontrolid()
 
        self.text        = ""
        self.tooltip     = None
        self.icon        = None
        self.image       = None
        self.border      = None
        self.mnemonic    = None
        self.accelerator = None
 
        self.valid       = jtutil.false
        self.escape      = jtutil.false
        self.enabled     = jtutil.true
        self.focusable   = jtutil.true
 
        self.itemlist    = None
        self.actionblock = None
        self.laststate   = None
 

    def classname(self):
        return "jtelem"


    def setdialogid(self,x):
        self.dialogid=x   
        

    def xmlout(self):

        x="<"+self.xmlname()
        x+=jtutil.ATTRI("top",self.top)
        x+=jtutil.ATTRI("left",self.left)
        x+=jtutil.ATTRI("bottom",self.bottom)
        x+=jtutil.ATTRI("right",self.right)
        x+=jtutil.ATTR("halign",self.halign)
        x+=jtutil.ATTR("valign",self.valign)
        x+=jtutil.ATTR("alignx",self.alignx)
        x+=jtutil.ATTR("aligny",self.aligny)
        x+=jtutil.ATTR("name",self.name)
        x+=">"

        if self.tooltip:
            x+="<tooltip>"+jtutil.cdataif(self.tooltip)+"</tooltip>"

        if self.icon:
            x+="<icon>"+self.icon+"</icon>"

        if self.image:
            x+="<image>"+jtutil.base64_encode(self.image)+"</image>" 

        if self.border:
            x+="<border>"+self.border+"</border>" 
 
        if not self.enabled:
            x+="<enabled>"
            x+=jtutil.alt(self.enabled,"true","false")
            x+="</enabled>"

        if self.escape:
            x+="<escape>"
            x+=jtutil.alt(self.escape,"true","false")
            x+="</escape>"

        if not self.focusable:
            x+="<focusable>"
            x+=jtutil.alt(self.focusable,"true","false")
            x+="</focusable>"

        if self.mnemonic:
            x+="<mnemonic>"
            x+=self.mnemonic      #pl. "X"
            x+="</mnemonic>"
 
        if self.accelerator:
            x+="<accelerator>"
            x+=self.accelerator   #pl. "alt X", vagy "control alt X"
            x+="</accelerator>"

        if self.valid or self.actionblock:
            x+="<valid>true</valid>"
        
            if not self.name:
                # A komponens akciót akar jelenteni,
                # ami nem lehetséges név nélkül,
                # ha itt nem jelentenénk a hibát,
                # akkor később az XML elemzés akadna meg.
                raise jtutil.applicationerror ("jtelem","valid field without name",self.xmlname())
    
        x+=self.xmladd() #bővítmények

        if self.text:
            x+="<text>"+jtutil.cdataif(self.text)+"</text>"
 
        x+="</"+self.xmlname()+">"

        return x


    def xmlname(self):
        return self.classname()


    def xmladd(self):
        return ""


    def xmlput(self,x):
        self.text=x.gettext()
        return self.text


    def xmlget(self):
        return self.text


    def savestate(self):
        pass


    def changed(self):
        return jtutil.false
        

    def varget(self):
        return self.text


    def varput(self,x):
        self.text=x
 

    def send(self,x):
        jtsocket.send(x)

 
    def changetext(self,v=None):
        if v:
            self.text=v

        x='<jtmessage'
        x+=jtutil.ATTR("pid",str(os.getpid()))
        x+=jtutil.ATTR("dialogid",self.dialogid)
        x+='>'
        x+="<control>"+self.name+"</control>"
        x+="<changetext>"
        x+=jtutil.cdataif(self.text)
        x+="</changetext>"
        x+="</jtmessage>"
        self.send(x)
        

    def changetooltip(self,v=None):
        if v:
            self.tooltip=v

        x='<jtmessage'
        x+=jtutil.ATTR("pid",str(os.getpid()))
        x+=jtutil.ATTR("dialogid",self.dialogid)
        x+='>'
        x+="<control>"+self.name+"</control>"
        x+="<changetooltip>"
        x+=jtutil.cdataif(self.tooltip)
        x+="</changetooltip>"
        x+="</jtmessage>"
        self.send(x)
 

    def changeicon(self,v=None):
        if v:
            self.icon=v

        x='<jtmessage'
        x+=jtutil.ATTR("pid",str(os.getpid()))
        x+=jtutil.ATTR("dialogid",self.dialogid)
        x+='>'
        x+="<control>"+self.name+"</control>"
        x+="<changeicon>"
        x+=jtutil.cdataif(self.icon)
        x+="</changeicon>"
        x+="</jtmessage>"
        self.send(x)
 

    def changeimage(self,v=None):

        if v:
            self.image=v

        x='<jtmessage'
        x+=jtutil.ATTR("pid",str(os.getpid()))
        x+=jtutil.ATTR("dialogid",self.dialogid)
        x+='>'
        x+="<control>"+self.name+"</control>"
        x+="<changeimage>"
        x+=jtutil.base64_encode(self.image) 
        x+="</changeimage>"
        x+="</jtmessage>"
        self.send(x)
 

    def changeenabled(self,v=None):
        if v:
            self.enabled=v

        x='<jtmessage'
        x+=jtutil.ATTR("pid",str(os.getpid()))
        x+=jtutil.ATTR("dialogid",self.dialogid)
        x+='>'
        x+="<control>"+self.name+"</control>"
        x+="<enabled>"
        x+=jtutil.alt(self.enabled,"true","false")
        x+="</enabled>"
        x+="</jtmessage>"
        self.send(x)
 

    def changefocusable(self,v=None):
        if v:
            self.focusable=v

        x='<jtmessage'
        x+=jtutil.ATTR("pid",str(os.getpid()))
        x+=jtutil.ATTR("dialogid",self.dialogid)
        x+='>'
        x+="<control>"+self.name+"</control>"
        x+="<focusable>"
        x+=jtutil.alt(self.focusable,"true","false")
        x+="</focusable>"
        x+="</jtmessage>"
        self.send(x)
 

    def setfocus(self):
        x='<jtmessage'
        x+=jtutil.ATTR("pid",str(os.getpid()))
        x+=jtutil.ATTR("dialogid",self.dialogid)
        x+='>'
        x+="<control>"+self.name+"</control>"
        x+="<setfocus/>"
        x+="</jtmessage>"
        self.send(x)
 

    def changeitem(self,ctrl):

        if self.classname()!=ctrl.classname():
            #vakon cseréljük az objektum attribútumait,
            #ami csak egyező struktúrákra engedhető meg
            raise jtutil.applicationerror("jtelem","different classes",self.classname(),ctrl.classname())
    
        for attr in dir(self):
            a=getattr(ctrl,attr)
            if not callable(a):
                try:
                    setattr(self,attr,a)
                except:
                    pass
    
        x='<jtmessage'
        x+=jtutil.ATTR("pid",str(os.getpid())) 
        x+=jtutil.ATTR("dialogid",self.dialogid)
        x+='>'
        x+="<control>"+self.name+"</control>"
        x+="<changeitem>"
        x+=self.xmlout()
        x+="</changeitem>"
        x+="</jtmessage>"
        self.send(x)
        