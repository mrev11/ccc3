#! /usr/bin/env python
# _*_ coding: latin-1 _*_
 
from jtlib import *
 
 
def mkdialog(): 

    dlg=jtdialog.new(6,20,24,80)
    dlg.caption('Próba szerencse')
    dlg.layout="vbox"

    r=jtradio.new()
    r.name="r1"
    r.state=1
    r.text="Rádió button 1"
    dlg.add(r)

    r=jtradio.new()
    r.name="r2"
    r.text="Rádió button 2"
    dlg.add(r)

    r=jtradio.new()
    r.name="r3"
    r.text="Rádió button 3"
    dlg.add(r)

    l=jtlabel.new() 
    l.icon="images/middle.gif"
    l.text="""<html><font face="ariel" color="black" size="-1">
        A jelszó (jelmondat) legalább 12 karakterbõl áll, és tartalmaznia kell
        <ul>
        <li>kisbetûket,</li>
        <li>nagybetûket,</li>
        <li>nem betû (pl. szám)</li>
        </ul>
        karaktereket.
        Az új jelszót kétszer egyformán kell beírni.
        A jó jelszóválasztáson alapszik a banki tranzakciók biztonsága.
        Az Ön jelszavát egyedül Ön ismerheti. </html>
        """
    dlg.add(l)

    dlg.add(jtlabel.new("új csoport"))

    rg=[]

    r=jtradio.new()
    r.name="r4"
    r.state=1
    r.text="Próba (r4)"
    r.setgroup(rg)
    dlg.add(r)

    r=jtradio.new()
    r.name="r5"
    r.text="szerencse (r5)"
    r.setgroup(rg)
    dlg.add(r)
    
    dlg.add(jtlabel.new("új csoport"))

    rg=[]
 
    r=jtradio.new()
    r.name="r6"
    r.text="Van (r6)"
    r.setgroup(rg)
    dlg.add(r)

    r=jtradio.new()
    r.name="r7"
    r.text="aki (r7)"
    r.setgroup(rg)
    dlg.add(r)

    r=jtradio.new()
    r.name="r8"
    r.text="forrón (r8)"
    r.setgroup(rg)
    r.actionblock=hopp
    dlg.add(r)

    r=jtradio.new()
    r.name="r9"
    r.text="szereti (r9)"
    r.setgroup(rg)
    r.valid=1
    dlg.add(r)
    
    pnl=jtpanel.new()

    chk=jtcheck.new()
    chk.name="chk1"
    chk.text="Check-1"
    pnl.additem(chk)

    chk=jtcheck.new()
    chk.name="chk2"
    chk.text="Check-2"
    pnl.additem(chk)

    chk=jtcheck.new()
    chk.name="chk3"
    chk.text="Check-3"
    pnl.additem(chk)

    dlg.add(pnl)

    
    
    b=jtpush.new()
    b.name="x"
    b.text="Exit"
    b.icon="images/exit.gif"
    b.valid=1
    dlg.add(b)
    
    dlg.varinst("test")
    
    #jtutil.inspect(dlg)
    #jtutil.inspect(dlg.var) 
 
    return dlg
 


def hopp(dlg):
    print "HOPP"
    print "dialog objektum", dlg
    # üzleti logika
    
    dlg.var.r1.state=1


def main():
    dlg=mkdialog()
    dlg.show()

    while 1:
        msg=dlg.getmessage(10000)

        if msg==None:
            print "BREAK"
            break

        elif msg=="":
            print "TIMEOUT"
 
        elif msg=="r9":
            dlg.list()

        elif msg=="x":
            dlg.close()
 

main()        

