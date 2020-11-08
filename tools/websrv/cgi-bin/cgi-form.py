#! /usr/bin/env python
# _*_  coding: utf-8 _*_

import os
import cgi

print("Content-Type: text/plain;charset=UTF-8\n")

form=cgi.FieldStorage()

print(form)
print(form.keys())
#print( form["submit"])

for name in form.keys():
    print( name+"="+form[name].value)

#env=os.environ
#for name in env.keys():
#    print( name+"="+env[name])

print( "öt szép szűzlány őrült írót nyúz")


