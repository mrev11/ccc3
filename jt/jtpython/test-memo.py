#! /usr/bin/env python
# _*_ coding: UTF-8 _*_
 
from jtlib import *

input_txt=jtutil.memoread("readme.hu.txt") 
output_txt=jtmemo.jtmemoedit(2,5,20,80,input_txt)

if output_txt and output_txt != input_txt:
    jtutil.memowrit("log",output_txt)
