#! /usr/bin/env python
# _*_ coding: UTF-8 _*_
 
from jtlib import *


srvfile="jtlib.zip"
trmfile="log-jtlib.zip"
d=dates.date(1990,10,11)
t="00:00:00"

jtdownload.jtdownload(srvfile,trmfile,d,t)
