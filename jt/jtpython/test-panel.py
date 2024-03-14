#! /usr/bin/env python
# _*_ coding: UTF-8 _*_
 
from jtlib import *
 
 
def mkdialog(): 

    dlg=jtdialog.new(6,20,24,80)
    dlg.caption('Próba szerencse')
    dlg.layout="vbox"
    dlg.layout="fix"
    
    pnl=jtpanel.new(2,2,14,40)
    pnl.text="Panel"
    #pnl.border="empty"
    dlg.add(pnl)

    pnl1=jtpanel.new()
    pnl1.hscroll=1
    pnl1.vscroll=1
    lb=jtlabel.jtimage("morgo.jpeg")
    pnl1.additem(lb)
    pnl.additem(pnl1)
    
    dlg.varinst("panel")
    return dlg
 

def main():
    dlg=mkdialog()
    dlg.show()

    while 1:
        msg=dlg.getmessage()

        if msg==None:
            break

        elif msg=="x":
            dlg.close()
 
 
main()        

 