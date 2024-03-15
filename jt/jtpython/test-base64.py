#! /usr/bin/env python
# _*_ coding: UTF-8 _*_
 
from  jtlib import jtutil

x="Öt szép szűzlány őrült írót nyúz"

b64x=jtutil.base64_encode(x)
print( b64x, type(b64x) )                   # str

y=jtutil.base64_decode(b64x)
print( y, type(y) )                         # bytes


x=jtutil.bin2str(y)
print( x, type(x) )                         # str
