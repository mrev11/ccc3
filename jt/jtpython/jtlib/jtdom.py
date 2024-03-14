##! /usr/bin/env python
# _*_ coding: UTF-8 _*_
 
# Egyszerűsített dom interface, 
# ami elkerüli az eredeti csomag hibáit.
# /usr/lib/python/site.py-ban
# encoding-ot át kell írni 'UTF-8'-re,
# máskülönben az ékezetes betűkön elszáll!
#
# Azért is jó saját interfészt használni,
# mert a Python XML csomagjait gyakran változtatják, 
# sőt eleve több változat létezik belőe.
 

import string
import xml.dom.minidom

from . import jtutil


def encoding():
    return ""
    return '<?xml version="1.0" encoding="UTF-8"?>' 


def domparse(txt):
    # encoding nélkül elszáll az ékezetes betűkön
    # ha UTF-8 a kódolás, akkor nem kell az encoding
    txt=jtutil.bin2str(txt)
    return xml.dom.minidom.parseString(encoding()+txt)


def wspace(x):
    x=x.replace(chr(10),'')
    x=x.replace(chr(13),'')
    x=x.replace(chr(9),'')
    return not x.strip()


def domfirst(node):  # kikerüli az üres szövegeket
    c=node.firstChild
    while c:
        if c.nodeType!=c.TEXT_NODE:
            return c
        elif not wspace(c.nodeValue):
            return c
        else:
            c=c.nextSibling
    return None


def domnext(node):  # kikerüli az üres szövegeket
    c=node.nextSibling
    while c:
        if c.nodeType!=c.TEXT_NODE: 
            return c
        elif not wspace(c.nodeValue):
            return c
        else:
            c=c.nextSibling
    return None
 
 
def domecho(node,n=0):
    print( "".rjust(4*n),node)
    c=domfirst(node)
    while c:
        domecho(c,n+1)
        c=domnext(c)

 
def domname(node):
    return node.nodeName


def domattr(node,attr):
    return node.getAttribute(attr)
 

def domtext(node):
    def walk(node,text):
        if node.nodeValue==None:
            pass
        elif not isinstance(node.nodeValue,str):
            pass
        elif wspace(node.nodeValue):
            pass
        else:
            text[0]+=node.nodeValue
        child=node.firstChild
        while child:
            walk(child,text)    
            child=child.nextSibling
    text=[""]
    walk(node,text)
    return text[0]

