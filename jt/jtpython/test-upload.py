#! /usr/bin/env python
# _*_ coding: latin-1 _*_
 
from jtlib import *

jtsocket.jtautostart()

trmfile="jtpython.zip"
srvfile="result-up.zip"

jtupload.jtupload(trmfile,srvfile)
