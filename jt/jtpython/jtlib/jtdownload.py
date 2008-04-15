##! /usr/bin/env python
# _*_ coding: latin-1 _*_
 

import jtutil 
import jtsocket
import jtdom
import dates
 

def jtdownload(locfile, remfile, date=None, time=None):

    # filé küldés a szerverrõl a terminálra
    # locfile : filéspecifikáció a szerveren
    # remfile : filéspecifikáció a terminálon
    # date    : file date (opcionális)
    # time    : file time (opcionális)
 
    f=file(locfile,"rb")
    f.seek(0,2) #végére
    flen=f.tell()
    f.seek(0,0) #elejére
    
    x="<jtdownload>" 
    x+="<file>"+remfile+"</file>" 
    x+="<length>"+str(flen)+"</length>" 
    if date:
        x+="<date>"+dates.dtos(date)+"</date>" 
        x+="<time>"+time+"</time>" 
    x+="</jtdownload>" 
    
    jtsocket.send(x)

    x=f.read(4096)
    while x:
        jtsocket.send(x)
        x=f.read(4096)
 
    f.close()

    while 1:
        rsp=jtsocket.recv()
        if rsp==None:
            break
        dom=jtdom.domparse(rsp)  
        node=jtdom.domfirst(dom)
        type=jtdom.domname(node) 
        text=jtdom.domtext(node)  
        if type=="download":
            if text=="OK":
                break
            else:
                raise jtutil.applicationerror, ("jtdownload","ioerror",text)

    return flen

