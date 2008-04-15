##! /usr/bin/env python
# _*_ coding: latin-1 _*_
 
import os
import string

import dates
import jtdom
import jtutil  

from jtelem import jtelem


class new(jtelem):

    def __init__(self,top=None,left=None,bottom=None,right=None):
        jtelem.__init__(self,top,left,bottom,right)
        self.picture=""
        self._valtype_=None
        self._decimal_=None
 
    def classname(self):
        return "jtget"

    def xmladd(self):
        if self.picture:
            return "<picture>"+jtutil.cdataif(self.picture)+"</picture>"
        return ""
    
    def xmlput(self,x):
        self.text=jtdom.domtext(x)

    def xmlget(self):
        return jtutil.cdataif(self.text)
        
    def changed(self):
        return self.laststate!=self.text
   
    def savestate(self):
        self.laststate=self.text


    def valtype(self):
        if self._valtype_==None:

            if not self.picture or not self.picture.startswith("@"):
                self._valtype_="C"
            else:
                p=self.picture.find(" ") 
                if 0>p:
                    funcstr=self.picture
                else:
                    funcstr=self.picture[:p]
                    
                if "N" in funcstr:
                    self._valtype_="N"
                elif "D" in funcstr:
                    self._valtype_="D"
                elif "L" in funcstr:
                    self._valtype_="L"
                else:
                    self._valtype_="C"

        return self._valtype_


    def decimal(self):
        if self._decimal_==None:
            if self.valtype()!="N":
                self._decimal_=0 
            else:
                p=self.picture.find(".")
                if p<0:
                    self._decimal_=0 
                else:
                    self._decimal_=len(self.picture)-p-1
        return self._decimal_
 

    def varget(self):
        t=self.valtype()
        if t=="C":
            return self.text
        elif t=="N":
            return float(self.text);
        elif t=="D":
            return dates.stod(self.text)
        elif t=="L":
            return self.text in "TtYy"
        else:
            return None


    def varput(self,x):
        t=self.valtype()
        if t=="C":
            self.text=x
        elif t=="N":
            self.text=string.strip("%32.*f" % (self.decimal(),x))
        elif t=="D":
            self.text=dates.dtos(x)
        elif t=="L":
            self.text=jtutil.alt(x,"T","F")
        return x


    def changepicture(self,v=None):
        if v:
            self.picture=v
            self._valtype_=None

        x='<jtmessage'
        x=x+jtutil.ATTR("pid",str(os.getpid()))
        x=x+jtutil.ATTR("dialogid",self.dialogid)
        x=x+'>'
        x=x+"<control>"+self.name+"</control>"
        x=x+"<changepicture>"
        x=x+jtutil.cdataif(self.picture)
        x=x+"</changepicture>"
        x=x+"</jtmessage>"
        self.send(x)

