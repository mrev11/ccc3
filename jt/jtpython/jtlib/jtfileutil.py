##! /usr/bin/env python
# _*_ coding: latin-1 _*_

# különféle filémûveletek,
# amik a terminál filérendszerében hajtódnak végre

import jtutil 
import jtsocket
import jtdom
 

def jtmakedir(name):

    x="<jtfileutil><makedir>"
    x+="<name>"+name+"</name>"
    x+="</makedir></jtfileutil>"

    jtsocket.send(x)

    while 1:
        rsp=jtsocket.recv()
        if rsp==None:
            break
        dom=jtdom.domparse(rsp)  
        node=jtdom.domfirst(dom)
        type=jtdom.domname(node) 
        text=jtdom.domtext(node)  
        if type=="makedir":
            return text=="true"

    return jtutil.false



def jtmakedirs(name): 

    x="<jtfileutil><makedirs>"
    x+="<name>"+name+"</name>"
    x+="</makedirs></jtfileutil>"
 
    jtsocket.send(x)

    while 1:
        rsp=jtsocket.recv()
        if rsp==None:
            break
        dom=jtdom.domparse(rsp)  
        node=jtdom.domfirst(dom)
        type=jtdom.domname(node) 
        text=jtdom.domtext(node)  
        if type=="makedirs":
            return text=="true"

    return jtutil.false



def jtdelete(name):

    x="<jtfileutil><delete>"
    x+="<name>"+name+"</name>"
    x+="</delete></jtfileutil>"
 
    jtsocket.send(x)

    while 1:
        rsp=jtsocket.recv()
        if rsp==None:
            break
        dom=jtdom.domparse(rsp)  
        node=jtdom.domfirst(dom)
        type=jtdom.domname(node) 
        text=jtdom.domtext(node)  
        if type=="delete":
            return text=="true"

    return jtutil.false
 


def jtexists(name):

    x="<jtfileutil><exists>"
    x+="<name>"+name+"</name>"
    x+="</exists></jtfileutil>"
 
    jtsocket.send(x)

    while 1:
        rsp=jtsocket.recv()
        if rsp==None:
            break
        dom=jtdom.domparse(rsp)  
        node=jtdom.domfirst(dom)
        type=jtdom.domname(node) 
        text=jtdom.domtext(node)  
        if type=="exists":
            return text=="true"

    return jtutil.false
 


def jtisfile(name):

    x="<jtfileutil><isfile>"
    x+="<name>"+name+"</name>"
    x+="</isfile></jtfileutil>"
 
    jtsocket.send(x)

    while 1:
        rsp=jtsocket.recv()
        if rsp==None:
            break
        dom=jtdom.domparse(rsp)  
        node=jtdom.domfirst(dom)
        type=jtdom.domname(node) 
        text=jtdom.domtext(node)  
        if type=="isfile":
            return text=="true"

    return jtutil.false
 
 

def jtisdirectory(name):

    x="<jtfileutil><isdirectory>"
    x+="<name>"+name+"</name>"
    x+="</isdirectory></jtfileutil>"
 
    jtsocket.send(x)

    while 1:
        rsp=jtsocket.recv()
        if rsp==None:
            break
        dom=jtdom.domparse(rsp)  
        node=jtdom.domfirst(dom)
        type=jtdom.domname(node) 
        text=jtdom.domtext(node)  
        if type=="isdirectory":
            return text=="true"

    return jtutil.false
 
 

def jtrename(oldname,newname):

    x="<jtfileutil><rename>"
    x+="<oldname>"+oldname+"</oldname>"
    x+="<newname>"+newname+"</newname>"
    x+="</rename></jtfileutil>"
 
    jtsocket.send(x)

    while 1:
        rsp=jtsocket.recv()
        if rsp==None:
            break
        dom=jtdom.domparse(rsp)  
        node=jtdom.domfirst(dom)
        type=jtdom.domname(node) 
        text=jtdom.domtext(node)  
        if type=="rename":
            return text=="true"

    return jtutil.false


 