##! /usr/bin/env python
# _*_ coding: latin-1 _*_
 
import os
import jtutil
import jtdom
from jtelem import jtelem
 
class new(jtelem):

    def __init__(self,top=None,left=None,bottom=None,right=None):
        jtelem.__init__(self,top,left,bottom,right)
        self.choicelist=[]
        self.selectedindex=1

 
    def classname(self):
        return "jtcombo"

 
    def xmladd(self):
        x=jtutil.EOL
        for c in self.choicelist:
            x+="<item>"+jtutil.cdataif(c)+"</item>"+jtutil.EOL
        x+="<selectedindex>"+str(self.selectedindex)+"</selectedindex>"+jtutil.EOL
        return x


    def xmlput(self,x):
        self.selectedindex=int(jtdom.domtext(x))
 

    def xmlget(self):
        return str(self.selectedindex)


    def changed(self):
        return self.laststate!=self.selectedindex


    def savestate(self):
        self.laststate=self.selectedindex


    def varput(self,x):
        self.selectedindex=x
        return self.selectedindex


    def varget(self):
        return self.selectedindex
 

    def additem(self,item):
        self.choicelist.append(item)
        return item


    def insertitem(self,item,idx):
        self.choicelist.insert(idx-1,item)


    def deleteitem(self,idx):
        del self.choicelist[idx-1]


    def select(self,x):
        self.selectedindex=x
 

    def getitem(self,x):
        return self.choicelist[x-1]


    def selecteditem(self):
        sx=self.selectedindex 
        lx=len(self.choicelist)
        if 0<sx and sx<=lx:
            return self.choicelist[sx-1]
        return None


    def selectitem(self,txt):
        try:
            self.select(1+self.choicelist.index(txt))
        except:
            self.select(0)
        return self.selectedindex


    def changelist(self,x=None,mode=None,i=None):
        _jtcombo_changelist(self,x,mode,i)
 

    def changedelete(self,x):
        _jtcombo_changelist(self,x,"del")


    def changeappend(self,x):
        _jtcombo_changelist(self,x,"app")


    def changeinsert(self,x,i):
        _jtcombo_changelist(self,x,"ins",i)



def _jtcombo_changelist(self,v=None,mode=None,i=None):

# jtcombo:changelist()           elk�ldi (az eg�sz) choicelistet
# jtcombo:changelist(v)          kicser�li choicelistet, �s k�ldi 
# jtcombo:changelist(v,"app")    b�v�ti choicelistet, �s k�ldi a b�v�t�st
# jtcombo:changelist(v,"ins",i)  besz�r i-n�l, �s k�ldi a b�v�t�st
# jtcombo:changelist(v,"del",i)  t�rli v/i-t, �s k�ldi a t�r�lt indexet
 

    # el�sz�r v�grehajtjuk lok�lisan

    if not mode:
        if not v:
            v=self.choicelist       # �jrak�ldi choicelistet
        else:
            self.choicelist=v       # kicser�li �s k�ldi choicelistet 
 
    elif mode=="app":
        if type(v)!=type([]):
            v=[v]
        self.choicelist+=v          # b�v�ti choicelistet, k�ldi a b�v�t�st 

    elif mode=="ins":
        self.insertitem(v,i)        # besz�r, �s k�ldi a b�v�t�st

    elif mode=="del":
    
        if type(v)==type(0):
            i=v
        elif type(v)==type(""):
            try: 
                i=1+self.choicelist.index(v)
            except:
                i=0
        else:
            pass
            # eredeti i param�ter

        if i<1 or len(self.choicelist)<1:
            return

        self.deleteitem(i)          # t�rli i-t, �s k�ldi a t�r�lt indexet
 
    else:
        raise jtutil.applicationerror, ("jtcombo","invalid changelist mode", mode)
    

    # azut�n elk�ldj�k a termin�lnak

    x='<jtmessage'
    x+=jtutil.ATTR("pid",str(os.getpid()))
    x+=jtutil.ATTR("dialogid",self.dialogid)
    x+='>'
    x+="<control>"+self.name+"</control>"
    x+="<changelist>"
    
    if not mode:
        x+="<removeall/>"+jtutil.EOL
        for c in v:
            x+="<app>"+jtutil.cdataif(c)+"</app>"+jtutil.EOL

    elif mode=="app":
        for c in v:
            x+="<app>"+jtutil.cdataif(c)+"</app>"+jtutil.EOL

    elif mode=="ins":
        x+="<ins>"
        x+="<at>"+str(i-1)+"</at>"+v 
        x+="</ins>"

    elif mode=="del":
        x+="<del>"+str(i-1)+"</del>"

    x+="</changelist>"
    x+="</jtmessage>"
    self.send(x)

