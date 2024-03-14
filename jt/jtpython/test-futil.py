#! /usr/bin/env python
# _*_ coding: UTF-8 _*_
 
from jtlib import *
from jtlib.jtfileutil import *
 
jtsocket.jtautostart()

print( 'jtmakedir("hopp")                   ', jtmakedir("hopp")                     )
print( 'jtmakedirs("hopp1/proba/szerencse") ', jtmakedirs("hopp1/proba/szerencse")   )
print( 'jtexists("hopp")                    ', jtexists("hopp")                      )
print( 'jtdelete("hopp")                    ', jtdelete("hopp")                      )
print( 'jtexists("hopp")                    ', jtexists("hopp")                      )
print( 'jtexists("hopp1")                   ', jtexists("hopp1")                     )
print( 'jtisfile("hopp1")                   ', jtisfile("hopp1")                     )
print( 'jtisdirectory("hopp1")              ', jtisdirectory("hopp1")                )
print( 'jtrename("hopp1","hopp2")           ', jtrename("hopp1","hopp2")             )
print( 'jtdelete("hopp2")                   ', jtdelete("hopp2")                     )
 
 