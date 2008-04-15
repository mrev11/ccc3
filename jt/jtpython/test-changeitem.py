#! /usr/bin/env python
# _*_ coding: latin-1 _*_

from jtlib import *

#-----------------------------------------------------------------------------
def main():
    jtversion.jtcheckversion("0.9.11")
    dlg=mkdialog()
    dlg.show()
    msg=1
    while msg!=None:
        msg=dlg.getmessage()


#-----------------------------------------------------------------------------
def mkdialog(): 

    dlg=jtdialog.new(4,16,20,80) 
    dlg.caption="Change Panel Application"  
    dlg.layout="vbox"

    mm=dlg.add(jtmenu.new())
    mm.text="Panelcsere"
    mi=mm.additem(jtmenuitem.new())
    mi.text="Elsô panel"
    mi.actionblock=lambda d:setpanel(d,panel1(),"x1")

    mi=mm.additem(jtmenuitem.new())
    mi.text="Második panel"
    mi.actionblock=lambda d:setpanel(d,panel2(),"x2") 

    mi=mm.additem(jtmenuitem.new())
    mi.text="Lista"
    mi.actionblock=lambda d:d.list()

    dlg.add(panel1())
    dlg.varinst("x1")
    
    return dlg


#-----------------------------------------------------------------------------
def setpanel(d,p,a): 
    d.var.proba.changeitem(p) 
    d.varinst(a) 
 

#-----------------------------------------------------------------------------
def panel1():
    pnl=jtpanel.new()
    pnl.layout="hbox"
    pnl.name="proba"
    pnl.text="Külsô panel (1)"
    pnl.additem(jtlabel.new("HOPP-1"))
    return pnl
    

#-----------------------------------------------------------------------------
def panel2():

    pnl=jtpanel.new()
    pnl.layout="vbox"
    pnl.name="proba"
    pnl.text="Külsô panel (2)"
 
    pnl.additem(jtlabel.new("HOPP-2"))

    pnl1=pnl.additem(jtpanel.new()) 
    pnl1.layout="vbox"
    pnl1.text="Belsô panel"
    pnl2=pnl1.additem(jtpanel.new()) 
    pnl2.hscroll=jtutil.true
    pnl2.vscroll=jtutil.true
    pnl2.additem(jtlabel.jtimage("morgo.jpeg"))
    
    bar=pnl.additem(jttoolbar.new())
   
    get=bar.additem(jtget.new(0,0,0,25))
    get.name="get1"
    get.picture="@R! 99999999-NNNNNNNN-99999999"
    get.varput("111111112222222233333333")
    get.actionblock=lambda d:out(d.var.get1.varget())

    get=bar.additem(jtget.new(0,0,0,12))
    get.name="get2"
    get.picture="@RN 999,999.99999"
    get.varput(3.14159)
    get.actionblock=lambda d:out(d.var.get2.varget())

    push=bar.additem(jtpush.new())
    push.text="Alert"
    push.icon="images/middle.gif"
    push.actionblock=lambda d:jtalert.jtalert("HOPP")

    push=bar.additem(jtpush.new())
    push.text="Exit"
    push.icon="images/exit.gif"
    push.actionblock=lambda d:d.close()
 
    return pnl
 
#-----------------------------------------------------------------------------
def out(x):
    print x
 

#-----------------------------------------------------------------------------

main()        

 
 