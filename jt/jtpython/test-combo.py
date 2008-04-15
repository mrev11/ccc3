#! /usr/bin/env python
# _*_ coding: latin-1 _*_
 
from jtlib import *
 
 
def mkdialog(): 

    dlg=jtdialog.new(6,20,12,60)
    dlg.caption('Listbox teszt')
    dlg.layout="fix"
    
    cb=dlg.add(jtcombo.new(2,2,2,30))
    cb.name="cb"
    cb.additem("Els� v�laszt�s")
    cb.additem("M�sodik v�laszt�s")
    cb.additem("Harmadik v�laszt�s")
    cb.additem("Negyedik v�laszt�s")
    cb.additem("�t�dik v�laszt�s")
    cb.additem("Hatodik v�laszt�s")
    cb.additem("Hetedik v�laszt�s")
    cb.additem("Nyolcadik v�laszt�s")
    cb.additem("Kilencedik v�laszt�s")
    cb.actionblock=cbaction

    #cb.varput(0) 
    #cb.select(3)
    cb.selectitem("Hatodik v�laszt�s")


    menu=dlg.add(jtmenu.new())
    menu.text="Listbox teszt"
    mi=menu.additem(jtmenuitem.new())
    mi.text="teszt_app1"
    mi.actionblock=teszt_app1

    mi=menu.additem(jtmenuitem.new())
    mi.text="teszt_app2"
    mi.actionblock=teszt_app2

    mi=menu.additem(jtmenuitem.new())
    mi.text="teszt_ins"
    mi.actionblock=teszt_ins

    mi=menu.additem(jtmenuitem.new())
    mi.text="teszt_del1"
    mi.actionblock=teszt_del1

    mi=menu.additem(jtmenuitem.new())
    mi.text="teszt_del2"
    mi.actionblock=teszt_del2

    mi=menu.additem(jtmenuitem.new())
    mi.text="teszt_csere"
    mi.actionblock=teszt_csere
    
    dlg.varinst("combo")
    
    return dlg



counter=0
def itemid():
    import sys
    m=sys.modules[__name__] # az aktu�lis modul
    m.counter+=1
    return str(m.counter)
 

def teszt_app1(dlg):
    cb=dlg.var.cb 
    cb.changeappend( "appended_"+itemid() )


def teszt_app2(dlg):
    cb=dlg.var.cb 
    cb.changeappend([ "appended_"+itemid(), "appended_"+itemid(), "appended_"+itemid() ])


def teszt_ins(dlg):
    cb=dlg.var.cb 
    cb.changeinsert( "inserted_"+itemid(), 10 )


def teszt_del1(dlg):
    cb=dlg.var.cb 
    cb.changedelete( 10 )
 

def teszt_del2(dlg):
    cb=dlg.var.cb 
    cb.changedelete( cb.getitem(10) )


def teszt_csere(dlg):
    cb=dlg.var.cb 
    cb.choicelist=[]
    cb.additem("ELS� V�LASZT�S")
    cb.additem("M�SODIK V�LASZT�S")
    cb.additem("HARMADIK V�LASZT�S")
    cb.additem("NEGYEDIK V�LASZT�S")
    cb.additem("�T�DIK V�LASZT�S")
    cb.additem("HATODIK V�LASZT�S")
    cb.additem("HETEDIK V�LASZT�S")
    cb.additem("NYOLCADIK V�LASZT�S")
    cb.additem("KILENCEDIK V�LASZT�S")
    cb.changelist()


def cbaction(dlg):
    cb=dlg.var.cb 
    print cb.varget()
    print cb.getitem(cb.varget())
    print cb.selecteditem()

    if cb.varget()==5:
        #cb.varput(9)
        cb.selectitem("Kilencedik v�laszt�s")
        print "changed to", cb.selectedindex


def main():
    dlg=mkdialog()
    dlg.show()
    while dlg.getmessage():
        pass
 

main()        


 
 