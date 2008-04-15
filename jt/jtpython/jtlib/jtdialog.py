##! /usr/bin/env python
# _*_ coding: latin-1 _*_
 
import os
import sys
import new
import string
import weakref

import jtsocket
import jtutil
import jtdom
 
from jtelem import jtelem

dlgcounter=0


class new(jtelem):

 
    def __init__(self,top=None,left=None,bottom=None,right=None):

        global dlgcounter

        dlgcounter+=1
 
        if not top and not left and not bottom and not right:
            top=0
            left=0
            bottom=16
            right=64
        
        jtelem.__init__(self,top,left,bottom,right)
        
        self.pid=str(os.getpid())       # process id 
        self.layout=None                # fix,vbox,hbox,flow 
        self.itemlist=[]                # list of controls (structured) 
        self.defaultradiogroup=[]       # radiogroup 
        self.mustreact=jtutil.false     # must answer the last action 
        self._blklist_=None             # these have block (flat list) 
        self._varlist_=None             # these have name (flat list)  
        self.var=None                   # _varlist_ as object 

        self.dialogid=self.pid+"_"+str(dlgcounter)


    def classname(self):
        return "jtdialog"
 

    def caption(self,text=None):
        if text:
            self.text=text
        return text


    def list(self):
        for v in self.varlist():
            print string.ljust(v.classname(),24),
            print string.ljust(v.name,24),
            print jtutil.alt(v.actionblock==None," ","B"),
            print jtutil.alt(v.valid,"V"," "),
            print jtutil.alt(v.enabled," ","D"),
            print v.xmlget()


    def getcontrolbyname(self,name):
        name=string.lower(name)
        for v in self.varlist():
            if v.name==name:
                return v
        return None
 

    def add(self,item):
        item.setdialogid(self.dialogid)
        self.itemlist.append(item)
        if item.classname()=="jtradio" and not item.group:
            item.setgroup(self.defaultradiogroup)
        return item


    def xmlout(self):

        x="<jtdialog"
        x+=jtutil.ATTRI("top",self.top)
        x+=jtutil.ATTRI("left",self.left)
        x+=jtutil.ATTRI("bottom",self.bottom)
        x+=jtutil.ATTRI("right",self.right)
        x+=jtutil.ATTR("name",self.name)
        x+=jtutil.ATTR("dialogid",self.dialogid)
        x+=jtutil.ATTR("pid",self.pid)
        x+=">"+jtutil.EOL
        x+="<caption>"+jtutil.cdataif(self.text)+"</caption>"+jtutil.EOL
        
 
        if self.layout:
            x+="<layout>"+self.layout+"</layout>"+jtutil.EOL

        wg=[] # m�r ki�rt r�di�csoportok
        
        for c in self.itemlist:
            if c.classname()=="jtradio" and c.group:
                if c.group not in wg:
                    wg.append(c.group)
                    x+="<jtradiogroup>"+jtutil.EOL
                    for g in c.group:
                        x+=g().xmlout()+jtutil.EOL
                    x+="</jtradiogroup>"+jtutil.EOL
            else:
                x+=c.xmlout()+jtutil.EOL

        x+="</jtdialog>"
        return x


    def send(self,x):
        jtsocket.send(x)


    def recv(self,wtime=None):
        return jtsocket.recv(wtime)

    def show(self):
    
        # Az al�bbi ciklus inicializ�lja a kontrollok laststate attrib�tumait
        # abb�l a c�lb�l, hogy a frissen megjelen�tett dialogbox tartalm�t
        # feleslegesen ne k�ldj�k �jra a reaction message-ben.
        # Ugyanezt a m�veletet a termin�l NEM csin�lja, �gy a termin�l az els�
        # action message-ben minden kontrollt k�ldeni fog. Ez viszont 
        # az�rt j�, mert �gy biztosan �sszhangba ker�l az alkalmaz�s �s
        # a termin�l olyan esetekben is, amikor az inicializ�l�skor
        # k�ld�tt �rt�k nem kezelhet� a termin�lban, pl. a picturen�l
        # hosszabb inicializ�l� sz�veg.

        for v in self.varlist():
            v.savestate()  # inicializ�lja a laststate-eket 
 
        self.mustreact=jtutil.false
        self.send(self.xmlout()) 


    def exit(self):
        self.mustreact=jtutil.false
        self.send("<exit/>") 
 

    def close(self):
        self.mustreact=jtutil.false
        self.send('<close dialogid="'+self.dialogid+'"/>') 
 


    def getmessage(self,wtime=None):

        if self.mustreact:
            self.response()

        msg=self.recv(wtime) 

        if not msg:
            # None, ha megszakadt a kapcsolat
            # "" , ha lej�rt a v�rakoz�si id�
            return msg   

        dom=jtdom.domparse(msg) 
        #jtdom.domecho(dom)
        node=jtdom.domfirst(dom) #<action>,<destroy>
        type=jtdom.domname(node)
        dlgid=jtdom.domattr(node,"dialogid")
    
        if dlgid!=self.dialogid:
            raise jtutil.applicationerror, ("jtdialog","dialogid differs", dlgid)
 
        elif type=="action":
            # a kontrollok �j tartalm�t
            # bet�lti a dialog objektumba

            self.mustreact=jtutil.true

            source=jtdom.domfirst(node)
            ctrl=jtdom.domnext(source)

            while ctrl:
                name=jtdom.domname(ctrl)
                for v in self.varlist():
                    if v.name==name:

                        v.xmlput(ctrl)  # �j �rt�k t�rolva 
                        v.savestate()   # ne k�ldje vissza 

                        # Ugyanezt a savestate adminisztr�ci�t a termin�l
                        # NEM csin�lja, azaz minden �j adatot egyszer visszak�ld.
                        # Ez az�rt j�, mert �sszhangba ker�l az alkalmaz�s
                        # �s a termin�l. Pl. ha egy picture nagybet�re konvert�l,
                        # de kisbet�s adatot t�lt�nk bele, akkor az visszaj�n
                        # nagybet�re konvert�lva.

                ctrl=jtdom.domnext(ctrl)
            
            # ha a source kontrollnak van blokkja,
            # akkor azt itt v�grehajtjuk
            
            srcnam=jtdom.domtext(source)
            for v in self.blklist():
                if v.name==srcnam:
                    v.actionblock(self)
                    break

            return srcnam
 
        elif type=="destroy":
            return None # becsukt�k az ablakot 


    def response(self):
        x=""
        for v in self.varlist():
            if v.changed():
                x+="<"+v.name+">"+v.xmlget()+"</"+v.name+">" 
                v.savestate()

        if not x:
            x='<reaction dialogid="'+self.dialogid+'"/>'
        else:
            x='<reaction dialogid="'+self.dialogid+'"><set>'+x+'</set></reaction>'

        self.send(x)
        self.mustreact=jtutil.false
 

    def blklist(self):
        if self._blklist_==None:
            self._blklist_=[]
            _jtdialog_setblk1(self,self.itemlist) 
        return self._blklist_ 


    def varlist(self):
        if self._varlist_==None:
            self._varlist_=[]
            _jtdialog_setvar1(self,self.itemlist) 
        return self._varlist_  


    def varinst(self,alias):

        m=sys.modules["new"] # new modul objektum (n�vegyez�s miatt!)
 
        self._varlist_=None
        self._blklist_=None
 
        d={}
        for v in self.varlist():
            d[v.name]=v
        c=m.classobj("jtdialog_"+alias,(),{})
        self.var=m.instance(c,d)
        
        # self.var most egy olyan objektum,
        # aminek a dlg kontrolljainak nev�vel
        # egyez� attrib�tumai vannak
        

def _jtdialog_setblk1(self,itemlist):
    for v in itemlist:
        if v.actionblock!=None:
            self._blklist_.append(v)
        if None!=v.itemlist:
            _jtdialog_setblk1(self,v.itemlist) 
 

def _jtdialog_setvar1(self,itemlist):
    for v in itemlist:
        if v.name:
            # csak akkor tessz�k be a list�ba, ha van neve,
            # de nem tesz�nk bele t�bb egyez� nev� kontrollt

            vn=v.name
            #vn=string.lower(v.name)
            v.name=vn

            for c in self._varlist_:
                if c.name==vn:
                    raise jtutil.applicationerror, ("jtdialog","multiple control name",vn)
            self._varlist_.append(v)
                
        if None!=v.itemlist:
            _jtdialog_setvar1(self,v.itemlist)


 