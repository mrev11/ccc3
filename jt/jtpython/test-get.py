#! /usr/bin/env python
# _*_ coding: UTF-8 _*_
 
from jtlib import *
 
 
def mkdialog(): 

    dlg=jtdialog.new(6,20,24,80)
    dlg.caption('Próba szerencse')
    dlg.layout="fix"


    b=jtpush.new(2,4,3,15)
    b.name="x"
    b.text="Exit"
    b.icon="images/exit.gif"
    b.valid=1
    dlg.add(b)
 
    b=jtpush.new(2,19,3,30)
    b.name="list"
    b.text="List"
    b.icon="images/middle.gif"
    b.valid=1
    dlg.add(b)

 
    g=jtget.new(5,4,5,29)
    g.name="g1"
    g.picture="@R! 99999999-NNNNNNNN-XXXXXXXX"
    g.valid=1
    g.varput("11111111AAAABBBB88888888")
    dlg.add(g)

    lb=jtlabel.new(5,32,5,64)
    lb.name="lb1"
    lb.text="X"
    dlg.add(lb)
 

    g=jtget.new(6,4,6,17)
    g.name="g2"
    g.picture="@RN 999,999,999.99"
    g.valid=1
    g.varput(123123.99)
    dlg.add(g)

    lb=jtlabel.new(6,32,6,64)
    lb.name="lb2"
    lb.text="X"
    dlg.add(lb)
 
    
    g=jtget.new(7,4,6,13)
    g.name="g3"
    g.picture="@RDXE"
    g.valid=1
    g.varput( dates.today() )
    dlg.add(g)

    lb=jtlabel.new(7,32,7,64)
    lb.name="lb3"
    lb.text="X"
    dlg.add(lb)

 
    g=jtget.new(8,4,6,4)
    g.name="g4"
    g.picture="@RL"
    g.valid=1
    g.varput( 0 )
    dlg.add(g)

    lb=jtlabel.new(8,32,8,64)
    lb.name="lb4"
    lb.text="X"
    dlg.add(lb)
    
    dlg.varinst("test")
 
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

        elif msg=="list":
            dlg.list()
 
        elif msg=="g1":
            pr(dlg)
            dlg.var.lb1.changetext( dlg.var.g1.varget() )
 
        elif msg=="g2":
            pr(dlg)
            dlg.var.lb2.changetext( str(dlg.var.g2.varget()) )
 
        elif msg=="g3":
            pr(dlg)
            dlg.var.lb3.changetext(repr(dlg.var.g3.varget())+' '+dlg.var.g3.varget().cweekday())
 
        elif msg=="g4":
            pr(dlg)
            dlg.var.lb4.changetext( jtutil.alt(dlg.var.g4.varget(),"True","False") )
 

def pr(dlg):
    print( "g1 =", dlg.var.g1.varget())
    print( "g2 =", dlg.var.g2.varget())
    print( "g3 =", dlg.var.g3.varget())
    print( "g4 =", dlg.var.g4.varget())
 
 
main()        

