#! /usr/bin/env python
# _*_ coding: UTF-8 _*_

# hasonló test-brwarr.py-hoz,
# csak a terminál jtdirlist szolgáltatásával megy

from jtlib import *


def main():
    msgloop( makedlg() )


def msgloop(dlg):

    dlg.show()
    dlg.var.brw.pagefirst()

    while 1:
        msg=dlg.getmessage()
        if not msg:
            break

        elif msg=="esc":
            dlg.close()
 

def makedlg():

    dir=jtdirlist.jtdirectory("jtlib/*.py") 
 
    for n in range(len(dir)):
        dir[n].append(-1==dir[n][0].find(".py"))
        dir[n].insert( 0, n+1 )
        #print(dir[n])
 
    dlg=jtdialog.new(4,16,24,96) 
    dlg.caption("Array Browse Demó")
    dlg.layout="vbox"
    
    brw=dlg.add(jtbrowsearray.new())
    brw.name="brw"
    brw.array(dir)
    brw.addcolumn("Sorszám",1,"@RN 99999")
    brw.addcolumn("Name",2,24).editable=1
    brw.addcolumn("Size",3,"@NR 999,999,999").editable=1 
    brw.addcolumn("Date",4,"@RDE").editable=1 
    brw.addcolumn("Time",5,10)
    brw.addcolumn("Attr",6,4)
    brw.addcolumn("Flag",7,"@RL").editable=1 
    brw.varput([3,10])
    
    dlg.add(brw.mktoolbar())
        
    dlg.varinst("browsearray")
      
    return dlg


main()
