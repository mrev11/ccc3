#! /usr/bin/env python
# _*_ coding: latin-1 _*_
 
from jtlib import *
from jtlib.jtalert import jtalert

while 1:
    r=jtalert("Pr�ba szerencse;Van, aki forr�n szereti",["Egy","Kett�","H�rom"]) 
    print r
    if r==0:
        break

