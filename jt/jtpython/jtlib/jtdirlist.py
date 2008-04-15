##! /usr/bin/env python
# _*_ coding: latin-1 _*_
 

import jtutil 
import jtsocket
import jtdom
import jtfilefilter
import dates
 

def jtdirectory(mask=None,attr=None):

    # ut�nozza Clipper directory()-t 
    #
    # jtdirectory("*.java")          java fil�k
    # jtdirectory("*.bat|*.java")    bat vagy java fil�k 
    # jtdirectory("getutil/*.java")  java fil�k a getutil directoryb�l
    # jtdirectory("*.bat","D")       bat fil�k plusz directoryk 
    # jtdirectory(,"D")              csak directoryk  

    if mask==None:
        mask=""

    if attr==None:
        attr=""
 
    mask=mask.replace("\\","/")
    workdir=None
    dsep=jtutil.rat("/",mask)+1
    if 0<dsep:
        workdir=mask[:dsep]
        mask=mask[dsep:]
    
    dl=new()
    dl.workdir=workdir
    dl.filter.addpattern(mask)
    dl.filter.regexdir=jtutil.alt("D" in attr,jtfilefilter.jtfilepattern("*"),None)
    
    return dl.getdirlist()



def jtdirlist(workdir=None,fmask=None,dmask=None):

    #egy m�sik utility f�ggv�ny a dirlist objektumhoz
    #
    #workdir : ezt a directoryt list�zza (empty==curdir)
    #fmask   : illeszked� fil�k maszkja, vagy egy jtfilefilter
    #dmask   : illeszked� directoryk maszkja, ha �res, nem ad directorykat

    if dmask==None:
        dmask=""
 
    dl=new()
    dl.workdir=workdir

    if type(fmask)==type(""):
        #fmask: fil�maszk
        #dmask: directory maszk

        dl.filter.addpattern(fmask)
        dl.filter.regexdir=jtfilefilter.jtfilepattern(dmask)
  
    elif type(fmask)==type([]):
        #fmask: fil�maszk lista
        #dmask: directory maszk
        
        for fm in fmask:
            dl.filter.addpattern(fm)
        dl.filter.regexdir=jtfilefilter.jtfilepattern(dmask)

    elif type(fmask)==type(jtfilefilter.new()):
        #fmask: jtfilefilter objektum
        #dmask: nem haszn�ljuk

        dl.filter=fmask

    return dl.getdirlist()



class new:
    def __init__(self):
        self.workdir=None
        self.filter=jtfilefilter.new() 


    def xmlout(self):
        x="<jtdirlist>"
        if self.workdir:
            x+="<workdir>"+self.workdir+"</workdir>" 
        x+=self.filter.xmlout()
        x+="</jtdirlist>"
        return x
 
 
    def getdirlist(self):
        jtsocket.send(self.xmlout())
        dlist=[]
        while 1:
            rsp=jtsocket.recv()
            if not rsp:
                return dlist
            dom=jtdom.domparse(rsp)
            node=jtdom.domfirst(dom)
            type=jtdom.domname(node)
            if type=="dirlist":
                node=jtdom.domfirst(node) 
                while node:
                    if jtdom.domname(node)=="file":
                        dlist.append(_getitem(node))
                    node=jtdom.domnext(node) 
                return dlist


def _getitem(node):
    item=[None,None,None,None,""]
    node=jtdom.domfirst(node)
    while node:
        type=jtdom.domname(node)
        text=jtdom.domtext(node)
        if   type=="name": item[0]=text
        elif type=="size": item[1]=int(float(text))
        elif type=="date": item[2]=dates.stod(text)
        elif type=="time": item[3]=text 
        elif type=="attr": item[4]=text 
        node=jtdom.domnext(node) 
    return item
