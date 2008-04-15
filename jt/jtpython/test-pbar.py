#! /usr/bin/env python
# _*_ coding: latin-1 _*_

import time
from jtlib import *


class pbar(jtdialog.new):
    def __init__(self):
        jtdialog.new.__init__(self,6,17,11,68) 
        self.name="pbar"
        self.layout="fix"

        self.progressbar=self.add(jtprogbar.new(1,16,1,48))
        self.progressbar.name='progressbar' 
        
        self.pbar=self.add(jtprogbar.new(3,16,3,48)) 
        self.pbar.name='pbar'

        self.add(jtlabel.new(1,3,1,14,'progressbar:'))
        self.add(jtlabel.new(3,3,3,14,'pbar       :'))


def main():

    #x="""

    #--------------------------------------------------------------------------
    # Automatikus progress bar
    #--------------------------------------------------------------------------
 
    # Az olyan message-ek,
    # mint amik a táblaobjektum indexelésében, 
    # vagy a packolásban óhatatlanul elôjönnek, megtalálják  
    # a felsô dialogboxban levô "progressbar" nevû kontrollt,
    # vagy ha nincs ilyen, akkor létrehoznak maguknak
    # agy automatikus ablakot (mint itt).

    pbar1("Türelem rózsát terem")
    pbar1("percent")

    msg=None
    msg=message(msg,"MESSAGE: ")
    time.sleep(3)
    for n in range(1,300):
        message(msg,"MESSAGE: "+str(n))
        time.sleep(0.02)
    time.sleep(1)
    message(msg)
    
    # Ha a time.sleep-eket kiveszem, akkor a messagek
    # gyorsabban lefutnak, mint ahogy a Jáva meg tudná
    # jeleníteni az ablakot.
 
    #--------------------------------------------------------------------------
    # jtdialogba ágyazott progress bar
    #--------------------------------------------------------------------------

    # Eddig minden a terminál által automatikusan
    # létrehozott ablakban jelent meg. Most lérehozunk
    # egy dialogboxot, ameiben van egy "progressbar"
    # és egy "pbar" nevû kontroll. 
    
    #"""

    dlg=pbar()
    dlg.caption("Progressbar demó")
    dlg.pbar.minvalue=200
    dlg.pbar.maxvalue=500

    dlg.show()
    
    # Most a default (progressbar nevû) progressbar
    # kapja meg az üzeneteket, nem jön létre új ablak.

    pbar1("Default progressbar")
    
    # Végül az általános eset.
    # a speciálisan felparaméterezett pbar-t használjuk
    # (a dlg.show elôtt kell megadni a paramétereket)
    
    for n in range(dlg.pbar.minvalue,dlg.pbar.maxvalue):
        dlg.pbar.setbar(n,"Próba szerencse "+str(n))
        time.sleep(0.01) 

    dlg.pbar.setbar(dlg.pbar.maxvalue,"KÉSZ")
    time.sleep(1) 
    dlg.pbar.clearbar()
    time.sleep(1)



def pbar1(text):

    pb=jtprogbar.new()

    # Ha a progressbar-t a jterminal automatikusan hozza létre,
    # akkor az csak a setbar message hatására fog létrejönni,
    # azért hiába paraméterezzük itt a pb objektumot,
    # csak azok az adatok mennek át, amiket a setbar átvisz.
    # A pb attribútomok csak akkor hatnak, ha pb be van ágyazva 
    # egy jtdialogba, és a jtdialog üzenet átviszi az adatokat. 
    # Ez sajnos egy csapda. 

    pb.setbar(0,text)
    time.sleep(3)

    for n in range(1,100):
        pb.setbar()
        time.sleep(0.05)

    pb.setbar(0,"HOPP")
    time.sleep(1)
    pb.clearbar()
    time.sleep(1)


def message(pb,text=None):
    if pb==None:
        pb=jtprogbar.new() 

    elif text==None:
        pb.clearbar()
        return

    pb.setbar(None,text)
    return pb
 
 
main()