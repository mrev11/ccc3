#! /usr/bin/env python
# _*_ coding: latin-1 _*_
 
from jtlib import *
from jtlib.jtalert import jtalert
from jtlib.jtlabel import jticon


#ICON_MIDDLE   =  "images/middle.gif" 
ICON_MIDDLE    =  "icons/22/exec.png" 
#ICON_EXIT     =  "images/exit.gif" 
ICON_EXIT      =  "icons/22/exit.png" 

#ICON_NETWORK  =  "images/network.gif" 
ICON_NETWORK   =  "icons/22/editcopy.png" 
 
ICON_GREEN     =  "images/green.gif" 
ICON_RED       =  "images/red.gif" 
ICON_STEAM     =  "images/steam.gif" 
 
ICON_TOP       =  "icons/22/top.png" 
ICON_BOTTOM    =  "icons/22/bottom.png"
ICON_DOWN      =  "icons/22/down.png" 
ICON_UP        =  "icons/22/up.png"  
ICON_RELOAD    =  "icons/22/reload.png"  

ICON_EXEC      =  "icons/22/exec.png"  
ICON_COLORIZE  =  "icons/22/colorize.png"  
ICON_CONFIGURE =  "icons/22/configure.png"  
 

def main():
    msgloop( makedlg() )


def msgloop(dlg):
    dlg.show()
    while 1:
        msg=dlg.getmessage()
        if not msg:
            break

        elif msg=="esc":
            dlg.close()

        elif msg=="tpane":
            jtalert("kiválasztva:"+str(dlg.var.tpane.varget()))

        elif msg=="b1":
            dlg.var.tpane.select(1)

        elif msg=="b2":
            dlg.var.tpane.select(2)
 

def makedlg():

    dlg=jtdialog.new(4,16,24,96) 
    dlg.caption("TabPane Demó")
    dlg.layout="vbox"
    
    tpane=dlg.add(jttabpane.new())
    tpane.name="tpane"
    tpane.valid=1
    #tpane.placement="r"
 
    p=tpane.additem(jtpanel.new())
    p.name="p1"
    p.text="Elsõ panel"
    p.mnemonic="E"
    p.bottom=32
    p.tooltip="Elsõ panel tooltipje"
    p.additem(jticon(ICON_STEAM))
    p.additem(pd1())

    p=tpane.additem(jtpanel.new())
    p.name="p2"
    p.text="Második panel"
    p.mnemonic="M"
    p.tooltip="Második panel tooltipje"
    p.additem(jticon(ICON_STEAM))
    p.additem(jticon(ICON_STEAM))
    p.additem(pd2())


    tbar=dlg.add( jttoolbar.new() )
 
    b=tbar.additem(jtpush.new())
    b.name="b1"
    b.text="Elsõ"
    b.tooltip="Kiválasztja az elsõ panelt."

    b=tbar.additem(jtpush.new())
    b.name="b2"
    b.text="Második"
    b.tooltip="Kiválasztja a második panelt."

    tbar.additem(jthglue.new())

    b=tbar.additem(jtpush.new())
    b.name="esc"
    b.text="Kilép"
    b.tooltip="Program vége."
    b.icon=ICON_EXIT 
       
        
    dlg.varinst("tpane")    
       
    return dlg


def pd1():

    p=jtmenu.new()
    p.text="Próba szerencse"    
    p.name="pd1"
    p.mnemonic="P"

    m=p.additem(jtmenuitem.new()) 
    m.text="Próba szerencse 1" 
    m.name="pd11"
    
    m=p.additem(jtmenuitem.new()) 
    m.text="Próba szerencse 2" 
    m.name="pd12"

    m=p.additem(jtmenuitem.new()) 
    m.text="Próba szerencse 3" 
    m.name="pd13"
    m.accelerator="ctrl alt A"
    m.actionblock=lambda dlg:jtalert("Próba szerencse 3")

    return p


def pd2():

    p=jtmenu.new()
    p.text="Van aki forrón"    
    p.name="pd2"
    p.mnemonic="V"

    m=p.additem(jtmenuitem.new())
    m.text="Van aki forrón 1"
    m.name="pd21"
    m.accelerator="ctrl shift A"
    m.actionblock=lambda dlg:jtalert("Van aki forrón 1")

    m=p.additem(jtmenuitem.new())
    m.text="Van aki forrón 2"
    m.name="pd22"

    m=p.additem(jtmenuitem.new())
    m.text="Van aki forrón 3"
    m.name="pd23"

    return p



main()
