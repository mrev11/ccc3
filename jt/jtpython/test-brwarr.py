#! /usr/bin/env python
# _*_ coding: latin-1 _*_

import os
import glob
import time


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

    dir=directory("*","D") 
    for n in range(len(dir)):
        dir[n].append(-1==dir[n][0].find(".py"))
        dir[n].insert( 0, n+1 )
        #print dir[n]
 
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
    brw.addcolumn("Flag",7,"@RL").editable=1 
    brw.varput([3,10])
    
    dlg.add(brw.mktoolbar())
        
    dlg.varinst("browsearray")
      
    return dlg



def directory(dspec,flags=""):
    dlst=[]
    
    for g in glob.glob(dspec):
        attr=""
        if os.path.isdir(g):
            attr+="D"

        if "D" in attr and "D" not in flags:
            pass
        else:
            base=os.path.basename(g)
            size=os.path.getsize(g) 
            t=time.localtime(os.path.getmtime(g)) 
            da=dates.date(t[0],t[1],t[2])
            ti="%02d:%02d:%02d"%(t[3],t[4],t[5])
            print [base,size,da,ti,attr] 
            dlst.append([base,size,da,ti,attr])
    return dlst
 

 

main()
