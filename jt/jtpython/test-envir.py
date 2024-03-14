#! /usr/bin/env python
# _*_ coding: UTF-8 _*_

from jtlib.jtenvir import *
from jtlib.jtversion import *
from jtlib.jtalert import *
from jtlib.jtsocket import *
 
 
jtalert(jtversion.jtversion())

jtsetenv("proba","szerencse")
jtsetenv("vanaki","forronszereti")
jtsetenv("hoho","fára <hopp> && mászni volna jó")
    
print( "proba",  jtgetenv("proba"))
print( "vanaki", jtgetenv("vanaki"))
print( "hoho",   jtgetenv("hoho"))

print()

jtsetenv("proba")
print( jtgetenv("proba"))
print( jtgetenv("nincsilyen"))
 