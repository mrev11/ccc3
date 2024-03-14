#! /usr/bin/env python
# _*_ coding: UTF-8 _*_

from jtlib import *
from jtlib.jtalert import jtalert 
 
def mkdialog(): 

    dlg=jtdialog.new(6,20,20,80)
    dlg.caption('Menü teszt')
    dlg.layout="vbox"
    dlg.layout="fix"
    

    ### Első pulldown (file)
    
    menu=dlg.add(jtmenu.new()) 
    menu.text="File"
    menu.icon="images/middle.gif"
    menu.tooltip="Egy szokványos fájl menü"
    menu.mnemonic="F"

    mi=menu.additem(jtmenuitem.new())
    mi.text="New"

    mi=menu.additem(jtmenuitem.new())
    mi.text="Open"
 
    mi=menu.additem(jtmenuitem.new()) 
    mi.text="Save"
    mi.accelerator="ctrl S"
 
    mi=menu.additem(jtmenuitem.new()) 
    mi.text="Save as"

    menu.additem(jtmenusep.new()) 

    mi=menu.additem(jtmenuitem.new()) 
    mi.text="Quit"
    mi.icon="images/exit.gif" 
    mi.accelerator="ctrl Q"
    mi.actionblock=lambda dlg:dlg.close()
    mi.tooltip="Kilép a programból"
    

    ### Második pulldown (radio, többszintű) 
 
    menu=dlg.add(menu1()) 
    menu.text="Összetett menü"
    menu.tooltip="Egy összetett menü"
    menu.mnemonic="M"
    m1=menu.additem(menu1())
    m1.text="Belső menü"
    m1.mnemonic="B"

    menu.additem(jtmenusep.new()) 
 
    mc=menu.additem(jtmenucheck.new())  
    mc.name="csekk"
    mc.text="Nicsak, egy csekkbox!"
   
    menu.additem(jtmenusep.new()) 

    mr=menu.additem(jtmenuradio.new())  
    mr.name="mr1"
    mr.text="Ez az egyik lehetőség"
 
    mr=menu.additem(jtmenuradio.new())  
    mr.text="Vagy próbáld ezt"
    mr.name="mr2"

    mr=menu.additem(jtmenuradio.new())  
    mr.text="Vagy talán inkább ezt"
    mr.name="mr3"

    menu.additem(jtmenusep.new()) 
 
    mr=menu.additem(jtmenuradio.new())  
    mr.name="mr4"
    mr.text="Ez az egyik lehetőség"
 
    mr=menu.additem(jtmenuradio.new())  
    mr.text="Vagy próbáld ezt"
    mr.name="mr5"

    mr=menu.additem(jtmenuradio.new())  
    mr.text="Vagy talán inkább ezt"
    mr.name="mr6"

    mr=menu.additem(jtmenuradio.new())  
    mr.text="De ez a legjobb!"
    mr.name="mr7"
    mr.tooltip="Non plus ultra"
 

    ### Harmadik pulldown (check)
 
    menu=dlg.add(jtmenu.new()) 
    menu.text="Checkbox menü"
    menu.tooltip="Checkbox menü demó"
    menu.mnemonic="C"
 
    mc=menu.additem(jtmenucheck.new())
    mc.text="Első checkmenü"
    mc.name="mc1"
    mc.varput(1)
 
    mc=menu.additem(jtmenucheck.new())
    mc.text="Második checkmenü"
    mc.name="mc2"
    mc.varput(1)
 
    mc=menu.additem(jtmenucheck.new())
    mc.text="Harmadik checkmenü"
    mc.name="mc3"
 
    ### Negyedik pulldown (help)

    menu=dlg.add(jtmenusep.new()) 
    menu=dlg.add(jtmenu.new()) 
    menu.text="Help"
    menu.tooltip="Help menü demó"
    menu.icon="icons/16/help.png"
    menu.mnemonic="H"

    mi=menu.additem(jtmenuitem.new()) 
    mi.text="Getting started"
    mi.accelerator="F1"
    mi.actionblock=lambda dlg:jtalert("Getting started")

    mi=menu.additem(jtmenuitem.new()) 
    mi.text="About"
    mi.actionblock=lambda dlg:jtalert("Menü demó (C) ComFirm 2003.")
   
    dlg.varinst("menu")

    return dlg


def menu1():

    menu=jtmenu.new()
    mi=menu.additem(jtmenuitem.new())
    mi.text="Első menüpont"
    mi.mnemonic="E"
    mi.actionblock=mkblock(mi.text) 

    mi=menu.additem(jtmenuitem.new())
    mi.text="Második menüpont"
    mi.mnemonic="M"
    mi.actionblock=mkblock(mi.text) 

    mi=menu.additem(jtmenuitem.new())
    mi.text="Harmadik menüpont"
    mi.mnemonic="H"
    mi.actionblock=mkblock(mi.text)

    mi=menu.additem(jtmenuitem.new())
    mi.text="Negyedik menüpont"
    mi.mnemonic="N"
    mi.actionblock=mkblock(mi.text) 

    return menu
    

def mkblock(text):
    return lambda x:jtalert(text) 



def main():
    dlg=mkdialog()
    dlg.show()
    while dlg.getmessage():
        pass
 
 
main()        


 