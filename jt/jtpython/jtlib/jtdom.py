##! /usr/bin/env python
# _*_ coding: latin-1 _*_
 
# Egyszerûsített dom interface, 
# ami elkerüli az eredeti csomag hibáit.
# /usr/lib/python/site.py-ban
# encoding-ot át kell írni 'latin-1'-re,
# máskülönben az ékezetes betûkön elszáll!
#
# Azért is jó saját interfészt használni,
# mert a Python XML csomagjait gyakran változtatják, 
# sôt eleve több változat létezik belôe.
 

import string
import xml.dom.minidom

def encoding():
    return '<?xml version="1.0" encoding="iso-8859-1"?>' 


def domparse(txt):
    # encoding nélkül elszáll az ékezetes betûkön
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
        elif not wspace(c.nodeValue.encode('latin-1')):
            return c
        else:
            c=c.nextSibling
    return None


def domnext(node):  # kikerüli az üres szövegeket
    c=node.nextSibling
    while c:
        if c.nodeType!=c.TEXT_NODE: 
            return c
        elif not wspace(c.nodeValue.encode('latin-1')):
            return c
        else:
            c=c.nextSibling
    return None
 
 
def domecho(node,n=0):
    print string.rjust("",4*n),node
    c=domfirst(node)
    while c:
        domecho(c,n+1)
        c=domnext(c)

 
def domname(node):
    return node.nodeName


def domattr(node,attr):
    return node.getAttribute(attr).encode('latin-1')
 

def domtext(node):
    text=""
    c=domfirst(node)
    while c:
        if c.nodeType == c.TEXT_NODE:
            text=text+c.nodeValue.encode('latin-1') 
        c=domnext(c) 

    # az XML elemzô unicode-ot ad,
    # amit át kell konvertálni 8 bites stringre,
    # a default konvezió (ascii) elszállna az ékezetes betûkön,
    # site.py-ban encoding-ot 'ascii'-ról 'latin-1'-re kell átírni,
    # a biztonság kedvéért itt is explicite konvertálunk
        
    return text


