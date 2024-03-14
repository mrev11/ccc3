#! /usr/bin/env python
# _*_ coding: UTF-8 _*_
 
from jtlib import *
from jtlib.jtalert import jtalert

while 1:
    r=jtalert("Próba szerencse;Van, aki forrón szereti",["Egy","Kettő","Három"]) 
    print(r)
    if r==0:
        break

