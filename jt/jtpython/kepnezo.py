#! /usr/bin/env python
# _*_ coding: latin-1 _*_ 
# _*_ coding: latin-1 _*_
 
import sys

from jtlib import *
from jtlib.jtfilefilter import jtfilepattern
#from jtlib.jtfilechooser import jtfilechooser 
#from jtlib.jtalert import jtalert


kepnezo=sys.modules[__name__] # az aktu�lis modul objektum
 
wd=None


def main():
    msgloop( makedlg() )


def msgloop(dlg):
    dlg.show()
    while dlg.getmessage():
        pass


def makedlg():
    dlg=jtdialog.new(4,16,24,96)

    dlg.caption("K�pn�z� Dem�")
    dlg.layout="vbox"
   
    htm=dlg.add(jthtmlarea.new())
    htm.bottom=32
    htm.name="htm"

    bar=dlg.add(jtpanel.new())
    bar.layout="hbox"

    get=bar.additem(jtget.new())
    get.name="fdesc"
    get.focusable=0
 
    bar.additem( jthglue.new() )

    but=bar.additem(jtpush.new()) 
    but.text="K�p v�laszt�s"
    but.name="kep"
    but.icon="icons/22/fileopen.png"  
    but.tooltip="Kiv�lasztja az �j megjelen�tend� k�pet"
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

    ch=fc.getchoice()
    
    if ch:
        kep=ch[0]
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

 