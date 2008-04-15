#! /usr/bin/env python
# _*_ coding: latin-1 _*_
 
from jtlib import *
from jtlib.jtfilefilter import jtfilepattern
#from jtlib.jtfilechooser import jtfilechooser 
from jtlib.jtalert import jtalert
 
def main():

    
    fc=jtfilechooser.new() 

    fc.caption="K�pv�laszt�"
    fc.text="Megjelen�t"
    fc.multiselect=1
    fc.selectmode="F"  # csak fil�ket
    

    ff=jtfilefilter.new()
    ff.description="JPEG f�jlok (*.jpeg *.jpg)"
    ff.addpattern("*.jpeg")
    ff.addpattern("*.jpg")
    ff.regexdir=jtfilepattern("*")
    fc.addfilter(ff)
 

    ff=jtfilefilter.new()
    ff.description="GIF f�jlok (*.gif)"
    ff.addpattern("*.gif")
    ff.regexdir=jtfilepattern("*")
    fc.addfilter(ff)


    ff=jtfilefilter.new() 
    ff.description="PNG f�jlok (*.png)"
    ff.addpattern("*.png")
    ff.regexdir=jtfilepattern("*")
    fc.addfilter( ff )


    ff=jtfilefilter.new()
    ff.description="Minden f�jl"
    ff.addpattern("*")
    ff.regexdir=jtfilepattern("*")
    fc.addfilter( ff )
    
    ch=fc.getchoice()
    
    print ch


main()

 