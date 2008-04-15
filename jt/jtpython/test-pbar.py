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
    # mint amik a t�blaobjektum indexel�s�ben, 
    # vagy a packol�sban �hatatlanul el�j�nnek, megtal�lj�k  
    # a fels� dialogboxban lev� "progressbar" nev� kontrollt,
    # vagy ha nincs ilyen, akkor l�trehoznak maguknak
    # agy automatikus ablakot (mint itt).

    pbar1("T�relem r�zs�t terem")
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
    # gyorsabban lefutnak, mint ahogy a J�va meg tudn�
    # jelen�teni az ablakot.
 
    #--------------------------------------------------------------------------
    # jtdialogba �gyazott progress bar
    #--------------------------------------------------------------------------

    # Eddig minden a termin�l �ltal automatikusan
    # l�trehozott ablakban jelent meg. Most l�rehozunk
    # egy dialogboxot, ameiben van egy "progressbar"
    # �s egy "pbar" nev� kontroll. 
    
    #"""

    dlg=pbar()
    dlg.caption("Progressbar dem�")
    dlg.pbar.minvalue=200
    dlg.pbar.maxvalue=500

    dlg.show()
    
    # Most a default (progressbar nev�) progressbar
    # kapja meg az �zeneteket, nem j�n l�tre �j ablak.

    pbar1("Default progressbar")
    
    # V�g�l az �ltal�nos eset.
    # a speci�lisan felparam�terezett pbar-t haszn�ljuk
    # (a dlg.show el�tt kell megadni a param�tereket)
    
    for n in range(dlg.pbar.minvalue,dlg.pbar.maxvalue):
        dlg.pbar.setbar(n,"Pr�ba szerencse "+str(n))
        time.sleep(0.01) 

    dlg.pbar.setbar(dlg.pbar.maxvalue,"K�SZ")
    time.sleep(1) 
    dlg.pbar.clearbar()
    time.sleep(1)



def pbar1(text):

    pb=jtprogbar.new()

    # Ha a progressbar-t a jterminal automatikusan hozza l�tre,
    # akkor az csak a setbar message hat�s�ra fog l�trej�nni,
    # az�rt hi�ba param�terezz�k itt a pb objektumot,
    # csak azok az adatok mennek �t, amiket a setbar �tvisz.
    # A pb attrib�tomok csak akkor hatnak, ha pb be van �gyazva 
    # egy jtdialogba, �s a jtdialog �zenet �tviszi az adatokat. 
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