##! /usr/bin/env python
# _*_ coding: UTF-8 _*_
 
import os

from . import jtutil
from . import jtdom
from .jtelem import jtelem
 
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

# jtcombo:changelist()           elküldi (az egész) choicelistet
# jtcombo:changelist(v)          kicseréli choicelistet, és küldi 
# jtcombo:changelist(v,"app")    bővíti choicelistet, és küldi a bővítést
# jtcombo:changelist(v,"ins",i)  beszúr i-nél, és küldi a bővítést
# jtcombo:changelist(v,"del",i)  törli v/i-t, és küldi a törölt indexet
 

    # először végrehajtjuk lokálisan

    if not mode:
        if not v:
            v=self.choicelist       # újraküldi choicelistet
        else:
            self.choicelist=v       # kicseréli és küldi choicelistet 
 
    elif mode=="app":
        if type(v)!=type([]):
            v=[v]
        self.choicelist+=v          # bővíti choicelistet, küldi a bővítést 

    elif mode=="ins":
        self.insertitem(v,i)        # beszúr, és küldi a bővítést

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
            # eredeti i paraméter

        if i<1 or len(self.choicelist)<1:
            return

        self.deleteitem(i)          # törli i-t, és küldi a törölt indexet
 
    else:
        raise jtutil.applicationerror("jtcombo","invalid changelist mode", mode)
    

    # azután elküldjük a terminálnak

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

