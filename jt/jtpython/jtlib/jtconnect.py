##! /usr/bin/env python
# _*_ coding: latin-1 _*_

import jtutil 
import jtsocket

def jtconnect(host,port,ssl=None):
    x="<jtconnect>"
    x+="<host>"+host+"</host>"
    x+="<port>"+str(port)+"</port>"
    x+="<ssl>"+jtutil.alt(ssl,"false","true")+"</ssl>"
    x+="</jtconnect>"
    jtsocket.send(x)
