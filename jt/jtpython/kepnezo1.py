#! /usr/bin/env python
# _*_ coding: UTF-8 _*_
 
import sys

from jtlib import *
from jtlib.jtfilefilter import jtfilepattern


kepnezo=sys.modules[__name__] # az aktuális modul objektum

wd=None
ch=None
ix=0


def main():
    #jtsocket.jtautostart()
    msgloop(makedlg())
 

def msgloop(dlg):

    dlg.show()

    while 1:

        timeout=float(dlg.var.speed.selecteditem()[:3]) 

        msg=dlg.getmessage(timeout*1000)

        if msg==None:
            break

        elif not msg:
            if not dlg.var.stop.state and kepnezo.ch: 
                forward(dlg)
            
        elif msg=="stop":
            if not dlg.var.stop.state and kepnezo.ch:  
                forward(dlg)
 


def forward(dlg):
    kepnezo.ix=(kepnezo.ix+1) % len(kepnezo.ch)
    kep=kepnezo.ch[kepnezo.ix]
    dlg.var.htm.changeurl('<html><img src="'+fspec2url(kep)+'"></html>')
    dlg.var.fdesc.changetext(kep)
        

def makedlg():

    dlg=jtdialog.new(4,16,48,200)
    dlg.caption("Képnéző Demó")
    dlg.layout="vbox"
   
    htm=dlg.add(jthtmlarea.new())  
    #htm.bottom=32
    htm.name="htm"

    bar=dlg.add(jttoolbar.new())
    #bar=dlg.add(jtpanel.new())
    #bar.layout="hbox"

    get=bar.additem(jtget.new()) 
    get.name="fdesc"
    get.focusable=0

    lst=bar.additem(jtcombo.new()) 
    lst.name="speed"
    lst.tooltip="Beállítja a képváltás sebességét"
    lst.valid=1
    lst.additem("  4 másodperc")
    lst.additem("  8 másodperc")
    lst.additem(" 15 másodperc")
    lst.additem(" 30 másodperc")
    lst.additem(" 60 másodperc")
    lst.additem("600 másodperc")
 
    chk=bar.additem(jtcheck.new()) 
    chk.name="stop"
    chk.text="Várakozik"
    chk.tooltip="Megállítja/továbbindítja a képek cseréjét"
    chk.varput(0)
    chk.valid=1

    but=bar.additem(jtpush.new()) 
    but.text="Kép választás"
    but.icon="icons/22/fileopen.png"  
    but.tooltip="Kiválasztja a megjelenítendő képeket"
    but.actionblock=lambda dlg:valaszt(dlg)
    
    dlg.varinst("kepnezo")
    
    return dlg


def valaszt(dlg):
    #jtutil.inspect(dlg)
    
    fc=jtfilechooser.new() 
    
    if kepnezo.wd:
        fc.workdir=kepnezo.wd

    fc.caption="Képválasztó"
    fc.text="Megjelenít"
    fc.multiselect=1
    fc.selectmode="F"  # csak filéket

    ff=fc.addfilter(jtfilefilter.new()) 
    ff.description="JPEG fájlok (*.jpeg *.jpg)"
    ff.addpattern("*.jpeg")
    ff.addpattern("*.jpg")
    ff.regexdir=jtfilepattern("*")

    ff=fc.addfilter(jtfilefilter.new()) 
    ff.description="GIF fájlok (*.gif)"
    ff.addpattern("*.gif")
    ff.regexdir=jtfilepattern("*")

    ff=fc.addfilter(jtfilefilter.new()) 
    ff.description="PNG fájlok (*.png)"
    ff.addpattern("*.png")
    ff.regexdir=jtfilepattern("*")

    ff=fc.addfilter(jtfilefilter.new()) 
    ff.description="Minden fájl"
    ff.addpattern("*")
    ff.regexdir=jtfilepattern("*")
    

    kepnezo.ch=fc.getchoice()
    kepnezo.ix=0
    
    if kepnezo.ch:
        kep=kepnezo.ch[0]
        kepnezo.wd=fpath(kep)
        dlg.var.htm.varput('<html><img src="'+fspec2url(kep)+'"></html>')
        dlg.var.fdesc.varput(kep)
 

def fspec2url(fspec):  # abszolút fspec --> URL
    fspec=fspec.replace("\\","/")
    if fspec[0]!="/":
        fspec="/"+fspec
    return "file:"+fspec


def fpath(name):  # path
    slashpos=max(jtutil.rat("/",name),jtutil.rat("\\",name))
    if 0<=slashpos:
        return name[:slashpos]
    return ""


main()
 