#! /usr/bin/env python
# _*_ coding: latin-1 _*_
 
import sys

from jtlib import *
from jtlib.jtfilefilter import jtfilepattern


kepnezo=sys.modules[__name__] # az aktu�lis modul objektum

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

    dlg=jtdialog.new(4,16,24,96)
    dlg.caption("K�pn�z� Dem�")
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
    lst.tooltip="Be�ll�tja a k�pv�lt�s sebess�g�t"
    lst.valid=1
    lst.additem("  4 m�sodperc")
    lst.additem("  8 m�sodperc")
    lst.additem(" 15 m�sodperc")
    lst.additem(" 30 m�sodperc")
    lst.additem(" 60 m�sodperc")
    lst.additem("600 m�sodperc")
 
    chk=bar.additem(jtcheck.new()) 
    chk.name="stop"
    chk.text="V�rakozik"
    chk.tooltip="Meg�ll�tja/tov�bbind�tja a k�pek cser�j�t"
    chk.varput(0)
    chk.valid=1

    but=bar.additem(jtpush.new()) 
    but.text="K�p v�laszt�s"
    but.icon="icons/22/fileopen.png"  
    but.tooltip="Kiv�lasztja a megjelen�tend� k�peket"
    but.actionblock=lambda dlg:valaszt(dlg)
    
    dlg.varinst("kepnezo")
    
    return dlg


def valaszt(dlg):
    #jtutil.inspect(dlg)
    
    fc=jtfilechooser.new() 
    
    if kepnezo.wd:
        fc.workdir=kepnezo.wd

    fc.caption="K�pv�laszt�"
    fc.text="Megjelen�t"
    fc.multiselect=1
    fc.selectmode="F"  # csak fil�ket

    ff=fc.addfilter(jtfilefilter.new()) 
    ff.description="JPEG f�jlok (*.jpeg *.jpg)"
    ff.addpattern("*.jpeg")
    ff.addpattern("*.jpg")
    ff.regexdir=jtfilepattern("*")

    ff=fc.addfilter(jtfilefilter.new()) 
    ff.description="GIF f�jlok (*.gif)"
    ff.addpattern("*.gif")
    ff.regexdir=jtfilepattern("*")

    ff=fc.addfilter(jtfilefilter.new()) 
    ff.description="PNG f�jlok (*.png)"
    ff.addpattern("*.png")
    ff.regexdir=jtfilepattern("*")

    ff=fc.addfilter(jtfilefilter.new()) 
    ff.description="Minden f�jl"
    ff.addpattern("*")
    ff.regexdir=jtfilepattern("*")
    

    kepnezo.ch=fc.getchoice()
    kepnezo.ix=0
    
    if kepnezo.ch:
        kep=kepnezo.ch[0]
        kepnezo.wd=fpath(kep)
        dlg.var.htm.varput('<html><img src="'+fspec2url(kep)+'"></html>')
        dlg.var.fdesc.varput(kep)
 

def fspec2url(fspec):  # abszol�t fspec --> URL
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
 