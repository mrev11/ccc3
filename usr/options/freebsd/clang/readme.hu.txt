----------------------------------------------------------------------------
CLANG <-> GCC fordítási opciók 

  Meg kell csinálni az alábbi linkek egyikét
    ln -s compile-gcc.opt compile.opt 
        vagy
    ln -s compile-clang.opt compile.opt 
 
  clang optimalizálás
    -O2-t kell használni 

    Az -O4-es objecteket csak az LLVM linkerével lehetne linkelni
    (ami linkelés közben optimalizál), az ld nem ismeri a formátumot.
    -O2-es objecteket a régi (c++/ld) linkerrel is lehet linkelni.

  clang warningok (gcc nem ismeri)
    -Wno-empty-body
    -Wno-constant-logical-operand

----------------------------------------------------------------------------
Linkelés FreeBSD-n

1)  libdl.so

  FreeBSD-ben nincs libdl.so.


2)  -rpath  (régen kellett, most nem)

  FreeBSD-ben a linkernek meg kell adni az

  -rpath $CCCDIR/usr/lib/$CCCBIN  
    
  opciót. A környezeti változók helyettesítését az envsubst
  programmal lehet elvégezni, pl:
    
  cat $CCCDIR/usr/options/$CCCBIN/link.opt | envsubst >>$RSPLNK
    
----------------------------------------------------------------------------
