##! /usr/bin/env python
# _*_ coding: latin-1 _*_
 
# jtfilefilter
#
# Filefilter a jtdirlist és jtfilechooser osztályokhoz.
# Directorykhoz és normál filékhez külön filtert kell magadni.
#
# regexdir  : 1 db reguláris kifejezés directorykra
# regexlist : reguláris kifejezések listája normál filékre 
#
# regexlist az addregex és addpattern metódusokkal bõvíthetõ,
# utóbbi a filémaszkot megpróbálja reguláris kifejezésre alakítani


def jtfilepattern(x):
    
    # Megjegyzés: a Jáva Pattern osztály ennél sokkal többet 
    # tud, ez itt csak emlékeztetõ a legegyszerûbb esetekre.

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


