##! /usr/bin/env python
# _*_ coding: latin-1 _*_
 

import jtutil
 
class new:

    def __init__(self,hdr,blk,pic=None,wid=None):

        # jtcolumn.new(hdr,blk,pic,wid)
        # jtcolumn.new(hdr,blk,wid)
    
        # Koncepci� v�ltoz�s:
        # az oszlop a picture-b�l (vagy annak hi�ny�b�l)
        # azonnal meghat�rozza a t�pus�t (C,N,D,L),
        # �s azt t�rolja a type attrib�tumban.
 
        if type(pic)==type(0):
            # ford�tva is elfogadjuk
            pic,wid=wid,pic

        self.heading  = hdr
        self.block    = blk
        self.picture  = pic
        self.width    = wid
        self.type     = "C"
        self.editable = jtutil.false
        
        if not self.picture:
            if not self.width:
                self.picture="X"*max(len(self.heading),10)
            else:
                self.picture="X"*max(len(self.heading),self.width) 

        if not self.picture.startswith("@"):
            funcstr=""                        #function string
            tmplstr=self.picture              #template string
        else:
            p=self.picture.find(" ") 
            if p<0:
                funcstr=self.picture
                tmplstr=""
            else:
                funcstr=self.picture[:p]
                tmplstr=self.picture[p+1:] 
            
        if "C" in funcstr:
            self.type="C"
        elif "N" in funcstr:
            self.type="N"
        elif "D" in funcstr:
            self.type="D"
        elif "L" in funcstr:
            self.type="L"

        if not self.width:
            self.width=max(len(self.heading),len(tmplstr))
            if self.type=="D":
                self.width=max(10,self.width)
 

    def classname(self):
        return "jtcolumn"


    def xmlout(self):
        x="<jtcolumn>"
        x+="<name>"+self.heading+"</name>"
        x+="<type>"+self.type+"</type>"
        x+="<width>"+str(self.width)+"</width>"
        x+="<picture>"+self.picture+"</picture>"
        if self.editable:
            #az oszlop edit�lhat�, 
            #ha a picture function stringj�ben 
            #be van �ll�tva az E flag.
            x+="<editable>true</editable>"
        x+="</jtcolumn>"
        return x

