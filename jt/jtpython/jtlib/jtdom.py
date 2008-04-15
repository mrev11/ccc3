##! /usr/bin/env python
# _*_ coding: latin-1 _*_
 
# Egyszer�s�tett dom interface, 
# ami elker�li az eredeti csomag hib�it.
# /usr/lib/python/site.py-ban
# encoding-ot �t kell �rni 'latin-1'-re,
# m�sk�l�nben az �kezetes bet�k�n elsz�ll!
#
# Az�rt is j� saj�t interf�szt haszn�lni,
# mert a Python XML csomagjait gyakran v�ltoztatj�k, 
# s�t eleve t�bb v�ltozat l�tezik bel�e.
 

import string
import xml.dom.minidom

def encoding():
    return '<?xml version="1.0" encoding="iso-8859-1"?>' 


def domparse(txt):
    # encoding n�lk�l elsz�ll az �kezetes bet�k�n
    return xml.dom.minidom.parseString(encoding()+txt)


def wspace(x):
    x=x.replace(chr(10),'')
    x=x.replace(chr(13),'')
    x=x.replace(chr(9),'')
    return not x.strip()


def domfirst(node):  # kiker�li az �res sz�vegeket
    c=node.firstChild
    while c:
        if c.nodeType!=c.TEXT_NODE:
            return c
        elif not wspace(c.nodeValue.encode('latin-1')):
            return c
        else:
            c=c.nextSibling
    return None


def domnext(node):  # kiker�li az �res sz�vegeket
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

    # az XML elemz� unicode-ot ad,
    # amit �t kell konvert�lni 8 bites stringre,
    # a default konvezi� (ascii) elsz�llna az �kezetes bet�k�n,
    # site.py-ban encoding-ot 'ascii'-r�l 'latin-1'-re kell �t�rni,
    # a biztons�g kedv��rt itt is explicite konvert�lunk
        
    return text


