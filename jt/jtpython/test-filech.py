#! /usr/bin/env python
# _*_ coding: latin-1 _*_
 
from jtlib import *
from jtlib.jtfilefilter import jtfilepattern
#from jtlib.jtfilechooser import jtfilechooser 
from jtlib.jtalert import jtalert
 
def main():

    
    fc=jtfilechooser.new() 

    fc.caption="Képválasztó"
    fc.text="Megjelenít"
    fc.multiselect=1
    fc.selectmode="F"  # csak filéket
    

    ff=jtfilefilter.new()
    ff.description="JPEG fájlok (*.jpeg *.jpg)"
    ff.addpattern("*.jpeg")
    ff.addpattern("*.jpg")
    ff.regexdir=jtfilepattern("*")
    fc.addfilter(ff)
 

    ff=jtfilefilter.new()
    ff.description="GIF fájlok (*.gif)"
    ff.addpattern("*.gif")
    ff.regexdir=jtfilepattern("*")
    fc.addfilter(ff)


    ff=jtfilefilter.new() 
    ff.description="PNG fájlok (*.png)"
    ff.addpattern("*.png")
    ff.regexdir=jtfilepattern("*")
    fc.addfilter( ff )


    ff=jtfilefilter.new()
    ff.description="Minden fájl"
    ff.addpattern("*")
    ff.regexdir=jtfilepattern("*")
    fc.addfilter( ff )
    
    ch=fc.getchoice()
    
    print ch


main()

 