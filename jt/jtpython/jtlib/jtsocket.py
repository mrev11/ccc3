##! /usr/bin/env python
# _*_ coding: latin-1 _*_
 
import os
import sys
import select
import socket
import string

import jtutil 

jtsocket=sys.modules[__name__] # az aktuális modul objektum
 
sck=None
debug=0


def jttermsck():
    if jtsocket.sck:
        return jtsocket.sck

    prev=None 
    for a in sys.argv:
        #print a
        if prev=="-jtsocket":
            jtsocket.sck=socket.fromfd(int(a),socket.AF_INET,socket.SOCK_STREAM) 
            prev=None
        elif a=="-jtsocket":
            prev=a
        elif a=="-jtauto":
            jtautostart()
        elif a=="-jtdebug":
            jtsocket.debug=1

    if not jtsocket.sck and os.getenv("JTSOCKET"):
        jtsocket.sck=fromfd(int(os.getenv("JTSOCKET")))

    if not jtsocket.sck:
        jtautostart()
       
    if "on" == os.getenv("JTDEBUG"):
        jtsocket.debug=1

    if not jtsocket.sck:
        raise jtutil.applicationerror,("jtsocket","-jtsocket option not set")
    
    return jtsocket.sck
 


def jtautostart(p1=None,p2=None):

    jterminal=os.getenv("JTERMINAL")
    if not jterminal:
        raise jtutil.applicationerror,("jtsocket","JTERMINAL environment variable not set")
    
    if not p1:
        p1=46321
    if not p2:
        p2=p1+64

    srv=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    for p in range(p1,p2):
        try:
            srv.bind( ('127.0.0.1',p) )
            srv.listen(1)
            break
        except:
            pass
    else:
        raise jtutil.applicationerror,("jtsocket","no free port")
        
    if os.getenv("wInDiR"):
        #Windows
        os.system( "start /b java -jar "+jterminal+" 127.0.0.1 "+str(p) )
    else:
        #UNIX
        os.system( "java -jar "+jterminal+" 127.0.0.1 "+str(p)+" &" )
            
    jtsocket.sck, (remotehost, remoteport)=srv.accept()
    srv.close()
    

def send(x):

    if not jtsocket.sck:
        jtsocket.sck=jttermsck()
 
    if jtsocket.debug:
        print ">>>>>send:",x

    hdr1=("00000000"+str(len(x)))[-8:] 
    hdr2=("00000000"+str(crc(x)))[-8:]  
    x=hdr1+hdr2+x

    nbyte=0
    sent=0

    while sent<len(x):
        nbyte=jtsocket.sck.send(x[sent:])
        if nbyte<0:
            raise jtutil.applicationerror,("jtsocket","send failed")
        sent=sent+nbyte


def recv(wtime=None):
    if not jtsocket.sck:
        jtsocket.sck=jttermsck()

    if wtime and not select.select([jtsocket.sck],[],[],wtime/float(1000))[0]:
        return ""
 
    hdr1=recv1(jtsocket.sck,8)
    hdr2=recv1(jtsocket.sck,8)

    if not hdr1 or not hdr2: 
        return None
        
    x=recv1(jtsocket.sck,int(hdr1))
    if not hdr2==("00000000"+str(crc(x)))[-8:]:
        raise jtutil.applicationerror,("jtsocket","recv failed")

    if jtsocket.debug:
        print "<<<<<recv:",x
 
    return x 


def recv1(s,n):
    x=""
    lx=0
    while lx<n:
        r=s.recv(n-lx)
        if not r:
            return None
        x=x+r
        lx=lx+len(r)
    return x


def crc(x):
    sum=0
    for c in x:
        sum=sum+ord(c)
    return sum

 

    