##! /usr/bin/env python
# _*_ coding: UTF-8 _*_

import os
import sys
#import new
import string
import weakref

from . import jtsocket
from . import jtutil
from . import jtdom

from .jtelem import jtelem

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
            print( v.classname().ljust(24),end="" )
            print( v.name.ljust(24),end="" )
            print( jtutil.alt(v.actionblock==None," ","B"),end="" )
            print( jtutil.alt(v.valid,"V"," "),end="" )
            print( jtutil.alt(v.enabled," ","D"),end="" )
            print( v.xmlget() )


    def getcontrolbyname(self,name):
        name=name.lower()
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

        wg=[] # már kiírt rádiócsoportok

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

        # Az alábbi ciklus inicializálja a kontrollok laststate attribútumait
        # abból a célból, hogy a frissen megjelenített dialogbox tartalmát
        # feleslegesen ne küldjük újra a reaction message-ben.
        # Ugyanezt a műveletet a terminál NEM csinálja, így a terminál az első
        # action message-ben minden kontrollt küldeni fog. Ez viszont
        # azért jó, mert így biztosan összhangba kerül az alkalmazás és
        # a terminál olyan esetekben is, amikor az inicializáláskor
        # küldött érték nem kezelhető a terminálban, pl. a picturenél
        # hosszabb inicializáló szöveg.

        for v in self.varlist():
            v.savestate()  # inicializálja a laststate-eket

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
            # "" , ha lejárt a várakozási idő
            return msg

        dom=jtdom.domparse(msg)
        #jtdom.domecho(dom)
        node=jtdom.domfirst(dom) #<action>,<destroy>
        type=jtdom.domname(node)
        dlgid=jtdom.domattr(node,"dialogid")

        if dlgid!=self.dialogid:
            raise jtutil.applicationerror("jtdialog","dialogid differs", dlgid)

        elif type=="action":
            # a kontrollok új tartalmát
            # betölti a dialog objektumba

            self.mustreact=jtutil.true

            source=jtdom.domfirst(node)
            ctrl=jtdom.domnext(source)

            while ctrl:
                name=jtdom.domname(ctrl)
                for v in self.varlist():
                    if v.name==name:

                        v.xmlput(ctrl)  # új érték tárolva
                        v.savestate()   # ne küldje vissza

                        # Ugyanezt a savestate adminisztrációt a terminál
                        # NEM csinálja, azaz minden új adatot egyszer visszaküld.
                        # Ez azért jó, mert összhangba kerül az alkalmazás
                        # és a terminál. Pl. ha egy picture nagybetűre konvertál,
                        # de kisbetűs adatot töltünk bele, akkor az visszajön
                        # nagybetűre konvertálva.

                ctrl=jtdom.domnext(ctrl)

            # ha a source kontrollnak van blokkja,
            # akkor azt itt végrehajtjuk

            srcnam=jtdom.domtext(source)
            for v in self.blklist():
                if v.name==srcnam:
                    v.actionblock(self)
                    break

            return srcnam

        elif type=="destroy":
            return None # becsukták az ablakot


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
        self._varlist_=None
        self._blklist_=None

        d={}
        for v in self.varlist():
            d[v.name]=v
        cls=type( "jtdialog_"+alias, (object,), d  )
        self.var=cls() # cls instance

        # self.var most egy olyan objektum,
        # aminek a dlg kontrolljainak nevével
        # egyező attribútumai vannak


def _jtdialog_setblk1(self,itemlist):
    for v in itemlist:
        if v.actionblock!=None:
            self._blklist_.append(v)
        if None!=v.itemlist:
            _jtdialog_setblk1(self,v.itemlist)


def _jtdialog_setvar1(self,itemlist):
    for v in itemlist:
        if v.name:
            # csak akkor tesszük be a listába, ha van neve,
            # de nem teszünk bele több egyező nevű kontrollt

            vn=v.name
            #vn=v.name.lower()
            v.name=vn

            for c in self._varlist_:
                if c.name==vn:
                    raise jtutil.applicationerror("jtdialog","multiple control name",vn)
            self._varlist_.append(v)

        if None!=v.itemlist:
            _jtdialog_setvar1(self,v.itemlist)



