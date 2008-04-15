##! /usr/bin/env python
# _*_ coding: latin-1 _*_
 
import jtutil 
import jtsocket
import jtdom

 
def jtupload(remfile, locfile):

    # remfile: fil�specifik�ci� a termin�lon
    # locfile: fil�specifik�ci� a szerveren

    # �zenetet k�ld a termin�lnak, amiben kezdem�nyezi
    # a (termin�lon tal�lhat�) remfile fil� �tk�ld�s�t
    # a szerverre. A fil�t a locfile fil�be �rja.

    jtsocket.send("<jtupload>"+remfile+"</jtupload>")
    
    # <uploadbegin>content_length</uploadbegin>
    #    nyers (nem xml) csomagok, 
    #    am�g a tartalmak hossza
    #    ki nem adja content_length-t
    # <uploadend/>
    #
    # vagy
    #
    # <uploaderror>error</uploaderror>

    clen=0

    while 1:
        rsp=jtsocket.recv()
        if rsp==None:
            break
        dom=jtdom.domparse(rsp)  
        node=jtdom.domfirst(dom)
        type=jtdom.domname(node) 
        text=jtdom.domtext(node)  
        if type=="uploaderror":
            raise jtutil.applicationerror, ("jtupload","uploaderror",text)
        if type=="uploadbegin":
            clen=int(float(text))
            break
 
    f=file(locfile,"wb")

    nbyte=0
    while nbyte<clen:
        x=jtsocket.recv()
        f.write(x)
        nbyte+=len(x) 
    
    f.close()
    
    if nbyte!=clen:
        raise jtutil.applicationerror, ("jtupload","content length differs")
    
    rsp=jtsocket.recv()
    dom=jtdom.domparse(rsp)  
    node=jtdom.domfirst(dom)
    type=jtdom.domname(node) 

    if type!="uploadend":
        raise jtutil.applicationerror, ("jtupload","<uploadend> tag expected",rsp)
    
    return clen

 