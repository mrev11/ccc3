##! /usr/bin/env python
# _*_ coding: latin-1 _*_
 
import sys
import string
import base64

 
true=1
false=0
EOL="\n"

controlid=0 


def jtcontrolid():
    global controlid
    controlid+=1
    return "ctrl_"+str(controlid)


def ATTR(a,x):
    if not x:
        return ""
    else:
        return ' '+a+'='+'"'+string.strip(x)+'"' 


def ATTRS(a,x):
    if not x:
        return ""
    else:
        return  ' '+a+'='+'"'+str(x)+'"'
    

def ATTRI(a,x):
    if not x:
        return ""
    else:
        return  ' '+a+'='+'"'+str(int(x))+'"'


def alt(x,y,z):
    if x: 
        return y 
    else: 
        return z



def html(x):
    return  "<html>"+x+"</html>" 
 

def cdata(x):
    cd="" 
    while 1:
        n=x.find("]]>")
        if n<0:
            cd=cd+"<![CDATA["+x+"]]>"
            break
        else:
            cd=cd+"<![CDATA["+x[:n+1]+"]]>" 
            x=x[n+1:]
    return  cd
 

def cdataif(x):
    if x.find("<")>=0 or x.find("&")>=0:
        return cdata(x) 
    return x
 

def base64_encode(x):
    return base64.encodestring(x).replace("\n","")


def base64_decode(x):
    return base64.decodestring(x)
 

def memoread(fspec):
    try:
        f=open(fspec,"rb")
        x=f.read() 
        f.close()
        return x
    except:
        return ""


def memowrit(fspec,x):
    try:
        f=open(fspec,"wb")
        f.write(x) 
        f.close()
    except:
        raise


def array(len=0,fill=None):
    return map(lambda x:fill,range(len))


def asize(a,size):
    l=len(a)
    if l<size:
        a+=array(size-l)
    else:
        a[size:]=[]
    return a


def at(s,x):
    return x.find(s)


def rat(s,x):
    p=-1
    while 1:
        p1=x.find(s,p+1)
        if p1>p:
            p=p1
        else:
            break
    return p
        

def inspect(o):
    print o, type(o)
    for a in dir(o):
        oa=getattr(o,a) 
        print alt(callable(oa),"M","A"), string.ljust(a,24), type(oa)


class applicationerror(Exception):
    def __init__(self,*value):
        self.value=value
    def __str__(self):
        return `self.value`
 