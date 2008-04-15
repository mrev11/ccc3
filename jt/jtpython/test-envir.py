#! /usr/bin/env python
# _*_ coding: latin-1 _*_

from jtlib.jtenvir import *
from jtlib.jtversion import *
from jtlib.jtalert import *
from jtlib.jtsocket import *
 
#jtautostart()
 
jtalert(jtversion())

print jtsetenv("proba","szerencse")
print jtsetenv("vanaki","forronszereti")
print jtsetenv("hoho","fara <hopp> && maszni volna jo")
    
print jtgetenv("proba")
print jtgetenv("vanaki")
print jtgetenv("hoho")
print jtgetenv("nincsilyen")

print jtsetenv("proba")
print jtgetenv("proba")
 