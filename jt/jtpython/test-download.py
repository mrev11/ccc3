#! /usr/bin/env python
# _*_ coding: latin-1 _*_
 
from jtlib import *

jtsocket.jtautostart()

srvfile="jtpython.zip"
trmfile="result-down.zip"
d=dates.date(1990,10,11)
t="00:00:00"

jtdownload.jtdownload(srvfile,trmfile,d,t)
