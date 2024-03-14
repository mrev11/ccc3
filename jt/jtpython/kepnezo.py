#! /usr/bin/env python
# _*_ coding: UTF-8 _*_ 
# _*_ coding: UTF-8 _*_
 
import sys

from jtlib import *
from jtlib.jtfilefilter import jtfilepattern
#from jtlib.jtfilechooser import jtfilechooser 
#from jtlib.jtalert import jtalert


kepnezo=sys.modules[__name__] # az aktuális modul objektum
 
wd=None


def main():
    msgloop( makedlg() )


def msgloop(dlg):
    dlg.show()
    while dlg.getmessage():
        pass


def makedlg():
    dlg=jtdialog.new(4,16,40,200)

    dlg.caption("Képnéző Demó")
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
    but.text="Kép választás"
    but.name="kep"
    but.icon="icons/22/fileopen.png"  
    but.tooltip="Kiválasztja az új megjelenítendő képet"
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

    ch=fc.getchoice()
    
    if ch:
        kep=ch[0]
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

 