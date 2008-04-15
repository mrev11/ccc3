##! /usr/bin/env python
# _*_ coding: latin-1 _*_
 

import jtutil 
import jtsocket
import jtdom
import dates
 

def jtdownload(locfile, remfile, date=None, time=None):

    # fil� k�ld�s a szerverr�l a termin�lra
    # locfile : fil�specifik�ci� a szerveren
    # remfile : fil�specifik�ci� a termin�lon
    # date    : file date (opcion�lis)
    # time    : file time (opcion�lis)
 
    f=file(locfile,"rb")
    f.seek(0,2) #v�g�re
    flen=f.tell()
    f.seek(0,0) #elej�re
    
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

