Linkelés FreeBSD-n

1)  libdl.so

  FreeBSD-ben nincs libdl.so.


2)  -rpath

  FreeBSD-ben a linkernek meg kell adni az

  -rpath $CCCDIR/usr/lib  
    
  opciót. A környezeti változók helyettesítését az envsubst
  programmal lehet elvégezni, pl:
    
  cat $CCCDIR/usr/options/${CCCBIN}/link.opt | envsubst >>$RSPLNK
    
