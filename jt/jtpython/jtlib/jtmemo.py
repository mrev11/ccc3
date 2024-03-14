##! /usr/bin/env python
# _*_ coding: UTF-8 _*_
 
from . import jtdialog
from . import jttoolbar
from . import jthglue
from . import jtpush
from . import jttextarea


def jtmemoedit(t=None,l=None,b=None,r=None,text="",editable=1):

    dlg=jtdialog.new(t,l,b,r)
    dlg.layout="vbox"
    
    bar=jttoolbar.new() 
    bar.additem(jthglue.new())
    
    but=jtpush.new() 
    but.name="ok" 
    but.text="Ok" 
    but.icon="images/middle.gif"
    bar.additem(but) 
 
    but=jtpush.new() 
    but.name="esc" 
    but.text="Esc"
    but.icon="images/exit.gif"
    bar.additem(but) 
 
    txt=jttextarea.new() 
    txt.name="txt"
    txt.bottom=32
    txt.focusable=editable
    txt.text=text

    dlg.add(bar)
    dlg.add(txt)
    
    dlg.show()
    
    while 1:
    
        msg=dlg.getmessage()

        if not msg:
            break
        
        elif msg=="ok":
            text=txt.varget()
            dlg.close()

        elif msg=="esc":
            text=None
            dlg.close()
    
    return text

