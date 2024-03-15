#! /usr/bin/env python
# _*_ coding: UTF-8 _*_
 
from jtlib import *


srvfile="morgo.jpeg"
trmfile="log-morgo.jpeg"
d=dates.date(1990,10,11)
t="10:10:10"

jtdownload.jtdownload(srvfile,trmfile,d,t)
