##! /usr/bin/env python
# _*_ coding: UTF-8 _*_

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
        return ' '+a+'='+'"'+x.strip()+'"'


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


def str2bin(x):
    if isinstance(x,str):
        x=x.encode("UTF-8")
    return x


def bin2str(x):
    if isinstance(x,bytes):
        x=x.decode("UTF-8")
    return x


def base64_encode(x):
    x=str2bin(x)
    x=base64.b64encode(x)
    x=x.decode("UTF-8")
    return x.replace("\n","")


def base64_decode(x):
    x=str2bin(x)
    x=base64.b64decode(x)
    return x


def memoread(fspec,binopt=False):
    try:
        f=open(fspec,"rb")
        x=f.read()
        f.close()
    except:
        x=b""
    if not binopt:
        x=bin2str(x)
    return x    


def memowrit(fspec,x):
    x=str2bin(x)
    try:
        f=open(fspec,"wb")
        f.write(x)
        f.close()
    except:
        raise


def array(len=0,fill=None):
    if len==0:
        return []
    else:
        return [fill]*len


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


def inspect(o,valflg=False):
    print( o, type(o))
    for a in dir(o):
        try:
            oa=getattr(o,a)
            print( alt(callable(oa),"M","A"), 
                   a.ljust(20), 
                   repr(type(oa)).ljust(48), 
                   alt(valflg,oa,""))
        except:
            pass


class applicationerror(Exception):
    def __init__(self,*value):
        self.value=value
    def __str__(self):
        return repr(self.value)


