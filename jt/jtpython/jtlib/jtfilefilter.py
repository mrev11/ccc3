##! /usr/bin/env python
# _*_ coding: latin-1 _*_
 
# jtfilefilter
#
# Filefilter a jtdirlist �s jtfilechooser oszt�lyokhoz.
# Directorykhoz �s norm�l fil�khez k�l�n filtert kell magadni.
#
# regexdir  : 1 db regul�ris kifejez�s directorykra
# regexlist : regul�ris kifejez�sek list�ja norm�l fil�kre 
#
# regexlist az addregex �s addpattern met�dusokkal b�v�thet�,
# ut�bbi a fil�maszkot megpr�b�lja regul�ris kifejez�sre alak�tani


def jtfilepattern(x):
    
    # Megjegyz�s: a J�va Pattern oszt�ly enn�l sokkal t�bbet 
    # tud, ez itt csak eml�keztet� a legegyszer�bb esetekre.

    if x:
        x=x.replace(".","\.")
        x=x.replace("*",".*")
        x=x.replace("?",".")
    return x
 


class new:
    def __init__(self):
        self.description = ""
        self.regexdir    = None   # regular exp for dirs 
        self.regexlist   = []     # regular exps for files 


    def addregex(self,rx):
        self.regexlist.append(rx)
        return rx
        
    def addpattern(self,p):
        fp=jtfilepattern(p) 
        self.regexlist.append(fp)
        return fp
        
    def xmlout(self):
        x="<filter>"
        if self.description:
            x+="<description>"+self.description+"</description>" 
        if self.regexdir:
            x+="<dirmask>"+self.regexdir+"</dirmask>"

        for e in self.regexlist:
            x+="<mask>"+e+"</mask>"
        x+="</filter>"
        return x


