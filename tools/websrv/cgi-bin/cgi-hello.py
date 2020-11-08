#! /usr/bin/env python
# _*_  coding: utf-8 _*_

import cgi

print("Content-Type: text/plain;charset=UTF-8\n")

print("Hello!")
print("Kázmér füstölgő fűnyírót húz.")
print(cgi.FieldStorage())


