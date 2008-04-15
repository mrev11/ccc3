#! /usr/bin/env python
# _*_ coding: latin-1 _*_
 
from jtlib import *
 

def main():
    msgloop( makedlg() )


def msgloop(dlg):
    dlg.show()
    while dlg.getmessage():
        pass

def makedlg():

    dlg=jtdialog.new(4,16,24,96) 
    dlg.caption("SplitPane Demó")
    dlg.layout="vbox"
    
    split=dlg.add(jtsplitpane.new())
    split.divider=20
    split.orientation="ver" 
 
    split1=split.setitem(1,jtsplitpane.new())
    split1.divider=50
    split1.orientation="hor" 
 
    pnl1=split1.setitem(1,jtpanel.new())
    pnl1.additem(jtlabel.jtimage("morgo.jpeg"))
    pnl1.hscroll=1
    pnl1.vscroll=1

    pnl2=split1.setitem(2,jtpanel.new()) #üresen marad
    pnl2.text="HOPP"

    txt=split.setitem(2,jttextarea.new())
    txt.text=jtutil.memoread("test-splitpane.py")
    
    return dlg


main()
