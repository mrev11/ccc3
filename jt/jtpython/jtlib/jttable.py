##! /usr/bin/env python
# _*_ coding: latin-1 _*_

import os
import string

import dates
import jtdom
import jtutil
import jttoolbar
import jtpush
import jtcolumn

from jtelem import *
 
 
class new(jtelem):

    def __init__(self,top=None,left=None,bottom=None,right=None,txt=None):

        jtelem.__init__(self,top,left,bottom,right)

        self.skipblock       = None
        self.gotopblock      = None 
        self.gobottomblock   = None 
        self.saveposblock    = None 
        self.restposblock    = None 
        self.column          = []      # oszlopok listája
        self.maxrow          = 16      # max ennyi sor lehet
        self.row2pos         = []      # a sorok pozíciói az adatforrásban
        self.selectedindices = []      # kiválasztott sorok indexe


    def classname(self):
        return "jttable"

 
    def savepos(self,p):
        self.row2pos[p-1]=self.saveposblock()

 
    def restpos(self,p):
        if 0<p<=len(self.row2pos):
            x=self.row2pos[p-1]
            if x!=None:
                return self.restposblock(x)
        return jtutil.false

 
    def colcount(self):
        return len(self.column)


    def addcolumn(self,h,b=None,w=None,p=None):
        if b==w==p==None:
            c=h
        else:
            c=jtcolumn.new(h,b,w,p) 
        self.column.append(c)
        return c


    def getcolumn(self,n):
        return self.column[n-1]
 

    def pageprev(self):
        if not self.row2pos:
            return
 
        page=""
        self.restpos(1) 
        self.row2pos=jtutil.array(self.maxrow)

        for n in range(self.maxrow):
            if -1!=self.skipblock(-1):
                jtutil.asize(self.row2pos,n)
                break
            self.savepos(n+1)
            page=_jttable_row_xmlout(self)+page

        self.row2pos.reverse()
        self.xmlpage(page)
 
 
    def pagenext(self):
        if not self.row2pos:
            return

        page=""
        self.restpos(len(self.row2pos))
        self.row2pos=jtutil.array(self.maxrow)
 
        for n in range(self.maxrow):
            if 1!=self.skipblock(1):
                jtutil.asize(self.row2pos,n)
                break
            self.savepos(n+1)
            page+=_jttable_row_xmlout(self)

        self.xmlpage(page)

 
    def pagefirst(self):
        page=""
        self.row2pos=jtutil.array(self.maxrow)
        for n in range(self.maxrow):
            if n==0:
                ok=self.gotopblock()
            else:
                ok=1==self.skipblock(1) 

            if not ok:
                jtutil.asize(self.row2pos,n)
                break

            self.savepos(n+1)
            page+=_jttable_row_xmlout(self)

        self.xmlpage(page)


    def pagelast(self):
        page=""
        self.row2pos=jtutil.array(self.maxrow)
 
        for n in range(self.maxrow):
    
            if n==0:
                ok=self.gobottomblock()
            else:
                ok=-1==self.skipblock(-1)

            if not ok:
                jtutil.asize(self.row2pos,n)
                break

            self.savepos(n+1)
            page=_jttable_row_xmlout(self)+page

        self.row2pos.reverse()
        self.xmlpage(page)

 
    def pagereload(self):
        page=""
        ok=self.restpos(1)  
        self.row2pos=jtutil.array(self.maxrow) 

        for n in range(self.maxrow):
            if n>0:
                ok=1==self.skipblock(1) 
            if not ok:
                jtutil.asize(self.row2pos,n)
                break
            self.savepos(n+1)
            page+=_jttable_row_xmlout(self)

        self.xmlpage(page)

 
    def pagecurrent(self):
        self.row2pos=[None]
        self.savepos(1)
        self.pagereload()

 
    def pagerefresh(self):
        x=self.selectedindices
        if len(x)==1:
            self.skipblock(1-x[0])
        self.pagecurrent()


    def rowcount(self):
        return len(self.row2pos)


    def empty(self):
        return not self.row2pos
        

    def xmladd(self):
        x=jtutil.EOL
        for c in self.column:
            x+=c.xmlout()+jtutil.EOL
        if self.selectedindices:
            x+="<sel>"+self.xmlget()+"</sel>"+jtutil.EOL
        return x


    def xmlput(self,x):
        c=jtdom.domfirst(x)
        while c:
            if jtdom.domname(c)=="sel":
                txt=jtdom.domtext(c)
                if not txt:
                    self.selectedindices=[]
                else:
                    self.selectedindices=txt.split(",") 
                for i in range(len(self.selectedindices)):
                    self.selectedindices[i]=int(self.selectedindices[i])
                
            elif jtdom.domname(c)=="change":
                _jttable_chngcell(self,c)

            c=jtdom.domnext(c)
    
 
    def xmlget(self):
        x=""
        for i in self.selectedindices:
            if x:
                x+=","
            x+=str(i)
        return x

 
    def xmlpage(self,page):
        x='<jtmessage'
        x+=jtutil.ATTR("pid",str(os.getpid()))
        x+=jtutil.ATTR("dialogid",self.dialogid)
        x+='>'
        x+="<control>"+self.name+"</control>"+jtutil.EOL
        x+="<setpage>"+jtutil.EOL
        x+=page
        x+="</setpage>"+jtutil.EOL
        x+="</jtmessage>"
        self.send(x)

 
    def changed(self):
        return self.laststate!=self.selectedindices  # oref!


    def savestate(self):
        self.laststate=self.selectedindices  # oref!


    def varput(self,x):
        self.selectedindices=x
        return x


    def varget(self):
        return self.selectedindices
 

    def mktoolbar(self,panel=None):

        ICON_TOP      =  "icons/22/top.png" 
        ICON_BOTTOM   =  "icons/22/bottom.png"
        ICON_DOWN     =  "icons/22/down.png" 
        ICON_UP       =  "icons/22/up.png"  
        ICON_RELOAD   =  "icons/22/reload.png"  
 
        if not panel:
            panel=jttoolbar.new()

        name=self.name

        button=panel.additem(jtpush.new()) 
        button.name=name+"top"
        button.actionblock=lambda dlg:self.pagefirst()
       #button.text="Elejére"
        button.icon=ICON_TOP
        button.tooltip="A tábla elejére pozícionál."
        button.mnemonic="home"
        button.border="null"

        button=panel.additem(jtpush.new()) 
        button.name=name+"nxt"
        button.actionblock=lambda dlg : self.pagenext()
       #button.text="Következõ"
        button.icon=ICON_DOWN
        button.tooltip="Elõre lapoz."
        button.mnemonic="page_down"
        button.border="null"
 
        button=panel.additem(jtpush.new()) 
        button.name=name+"prv"
        button.actionblock=lambda dlg : self.pageprev()
       #button.text="Elõzõ"
        button.icon=ICON_UP
        button.tooltip="Hátra lapoz."
        button.mnemonic="page_up"
        button.border="null"
 
        button=panel.additem(jtpush.new())
        button.name=name+"bot"
        button.actionblock=lambda dlg : self.pagelast()
       #button.text="Végére"
        button.icon=ICON_BOTTOM
        button.tooltip="A tábla végére pozícionál."
        button.mnemonic="end"
        button.border="null"
        
 
        button=panel.additem(jtpush.new()) 
        button.name=name+"rel"
        button.actionblock=lambda dlg : self.pagereload()
       #button.text="Újraolvas"
        button.icon=ICON_RELOAD
        button.tooltip="Újraolvassa a lapot."
        button.border="null"
    
        return panel
 

def _jttable_chngcell(self,x):

    row=col=valold=valnew=None
 
    node=jtdom.domfirst(x)
    while node:
        name=jtdom.domname(node) 
        if name=="r":
            row=int(jtdom.domtext(node))
        elif name=="c":
            col=int(jtdom.domtext(node))
        elif name=="from":
            valold=jtdom.domtext(node)
        elif name=="to":
            valnew=jtdom.domtext(node)

        node=jtdom.domnext(node)
        
    if not self.restpos(row):
        raise jtutil.applicationerror,(jttable,"_jttable_chngcell","restpos failed")

    # Ez a megoldás nem ellenõrzi valcur==valold fennállását,
    # ehelyett továbbadja valold-ot az oszlopblocknak, ami azután
    # elvégezheti az ellenõrzést, ha akarja.

    column=self.getcolumn(col) 
 
    if column.type=="C":
        column.block(valnew,valold)

    elif column.type=="N":
        column.block(float(valnew),float(valold))

    elif column.type=="D":
        column.block(dates.stod(valnew),dates.stod(valold))

    elif column.type=="L":
        column.block(valnew=="true",valold=="true")


def _jttable_row_xmlout(self):

    # koncepció VÁLTOZÁS:
    # nem az adat, hanem az oszlop típusát nézzük,
    # ui. egyes nyelvekben nem jók típusok, pl. Pythonban 
    # nem lehet felismerni a dátum és logikai típust
 
    x="<r>"
    for c in self.column:
        t=c.type
        d=c.block()

        if t=="C":
            d=jtutil.cdataif(d.strip())
        elif t=="N":
            d=str(d)
        elif t=="D":
            d=dates.dtos(d)
        elif t=="L":
            d=jtutil.alt(d,"t","f")
        else:
            d=""
        x+="<c>"+d+"</c>" 
    x+="</r>"+jtutil.EOL
    return x
 
