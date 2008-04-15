##! /usr/bin/env python
# _*_ coding: latin-1 _*_
 

import jtutil 
import jtsocket
import jtdom
 

def jtfilechooser(fc):

    if type(fc)==type(""):
        mask=fc.replace("\\","/")
        dsep=jtutil.rat("/",mask)
        if dsep>=0:
            wdir=mask[:dsep]
            mask=mask[dsep:]

        fc=new()
        fc.workdir=wdir 
        ff=jtfilefilter.new() 
        ff.description=mask
        ff.addpattern(mask)
        ff.regexdir=jtfilepattern("*")
        fc.addfilter( ff )

    elif type(fc)==type([]):
        mask=fc
        fc=new()
        for m in mask:
            ff=jtfilefilter.new() 
            ff.description=m
            ff.addpattern(m)
            ff.regexdir=jtfilepattern("*")
            fc.addfilter( ff )
    
    return fc.getchoice()


 
class new:
    def __init__(self):
        self.caption=""
        self.text=""
        self.workdir=None
        self.filterlist=[]
        self.selectmode="FD"  # "F", "D", "FD"
        self.multiselect=0    # .t., .f.
 
    def xmlout(self):
        x="<jtfilechooser>"

        if self.caption:
            x+="<caption>"+jtutil.cdataif(self.caption)+"</caption>" 

        if self.text:
            x+="<text>"+self.text+"</text>" 
 
        if self.workdir:
            x+="<workdir>"+self.workdir+"</workdir>" 

        if self.multiselect:
            x+="<multiselect/>"
 
        if self.selectmode:
            x+="<selectmode>"+self.selectmode+"</selectmode>" 
    
        x+=jtutil.EOL

        if self.filterlist:
            for f in self.filterlist:
                x+=f.xmlout()+jtutil.EOL
    
        x+="</jtfilechooser>"
        return x

 
    def addfilter(self,ff): 
        self.filterlist.append(ff)
        return ff
 

    def getchoice(self): 
        jtsocket.send(self.xmlout())
        
        while 1:
            rsp=jtsocket.recv()
            if rsp==None:
                return None
            dom=jtdom.domparse(rsp) 
            node=jtdom.domfirst(dom)
            type=jtdom.domname(node)
            if type=="filechooser":
                choice=[]
                node=jtdom.domfirst(node)
                while node:
                    choice.append(jtdom.domtext(node))
                    node=jtdom.domnext(node)
                return choice
 
