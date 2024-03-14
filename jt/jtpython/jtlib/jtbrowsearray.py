##! /usr/bin/env python
# _*_ coding: UTF-8 _*_

#from . import jtutil
from . import jttable
#from jtelem import jtelem
 
class new(jttable.new):

    def __init__(self,top=None,left=None,bottom=None,right=None):

        jttable.new.__init__(self,top,left,bottom,right)

        self._array_    = None
        self._arraypos_ = 0
 
    def classname(self):
        return "jtbrowsearray"


    def xmlname(self):
        return "jttable"


    def array(self,a):
        if a:
            self._array_       = a
            self.skipblock     = lambda s : _jtbrowsearray_skip(self,s)
            self.gotopblock    = lambda   : 0<=self.arraypos(0)
            self.gobottomblock = lambda   : 0<=self.arraypos(len(self._array_)-1)
            self.saveposblock  = lambda   : self.arraypos()
            self.restposblock  = lambda p : 0<=self.arraypos(p)
        return self._array_


    def arraypos(self,pos=None):
        if pos!=None:
            if pos<0:
                pos=0
            if pos>len(self._array_)-1:
                pos=len(self._array_)-1
            self._arraypos_=pos
        return self._arraypos_

 
    def ablock(self,c):
        return lambda newval=None, oldval=None : _jtbrowsearray_eval(self,c,newval,oldval)
        

    def addcolumn(self,h,b=None,w=None,p=None):
        if type(b)==type(0): # block helyett oszlop sorszám
            b=self.ablock(b) 
        return jttable.new.addcolumn(self,h,b,w,p)   

 
    def selectedrows(self):
        selrows=[]
        sx=self.varget()
        for x in sx:
            if self.restpos(x):
                 selrows.append( self.array()[self.arraypos()] )
        return selrows
 

    def currentrow(self):
        cr=self.selectedrows
        if len(cr)==1:
            cr=cr[0]
        else:
            cr=None
        return cr

 
def _jtbrowsearray_skip(self,s=0): 
    s0=self.arraypos()
    s1=self.arraypos(s0+s) 
    return s1-s0


def _jtbrowsearray_eval(self,c,valnew=None,valold=None):

    # módosításkor a terminál küldi a régi és az új érrtéket is,
    # itt ellenőrizni lehetne, hogy a régi érték nem változott

    if valnew!=None:
        self._array_[self._arraypos_][c-1]=valnew
    return self._array_[self._arraypos_][c-1] 

