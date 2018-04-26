#!/bin/bash
#set -x

# Ez nem egy általános utility, hanem a CCC setup alkatrésze.
#
# Hivási formák
#
# 1) make.b lib name               (statikus könyvtár minden cpp-ből)
# 2) make.b so  name lib1 lib2 ... (so könyvtár minden cpp-ből + lib-ek) 
# 2) make.b exe name lib1 lib2 ... (exe program minden cpp-ből + lib-ek) 
#
# A statikus könyvtárak névképzése : name.lib
# A shared könyvtárak névképzése   : libname.so
# Az önálló programok névképzése   : name.exe
#
# Az exe programok mindig $CCCDIR/usr/bin/$CCCUNAME-ban keletkeznek.
# A könyvtárak mindig $CCCDIR/usr/lib/$CCCBIN-ben jönnek létre, 
# ezt a directoryt létre is hozza, ha korábban nem létezett.
#
# A linkeléskor használt lib-eket path nélkül, de teljes névvel
# kell megadni (libMesaGL.so). A könyvtárat az dspec function
# megkeresi a SEARCHDIR-ben megadott helyeken, és teljes filé
# specifikációval adja tovább a linkernek. A SEARCHDIR tartalmát
# az adott Linux installációnak megfelelően módosítani kell.

 
SEARCHDIR="
  $CCCDIR/usr/lib/$CCCBIN
  /usr/lib
  /usr/X11R6/lib
  /usr/X11/lib
"
unset DSPEC

function dspec()
{
    for i in $SEARCHDIR; do
        if [ -e $i/$1 ]; then
            DSPEC=$i
            return
        fi
    done
    echo "***"$1 not found
    unset DSPEC
}


mkdir $CCCDIR/usr/lib          2>/dev/null
mkdir $CCCDIR/usr/lib/$CCCBIN  2>/dev/null
 
LIBPATH=$CCCDIR/usr/lib/$CCCBIN 
EXEPATH=$CCCDIR/usr/bin/$CCCUNAME
TRGTYP=$1
TARGET=$2
 
if ! test -f $CCCDIR/usr/options/$CCCBIN/gccver.opt; then
   gccver.b >$CCCDIR/usr/options/$CCCBIN/gccver.opt 
fi
cat $CCCDIR/usr/options/$CCCBIN/gccver.opt >compopt
cat $CCCDIR/usr/options/$CCCBIN/compile.opt >>compopt 
echo -I$CCCDIR/setup/unix/include >>compopt
echo -I$CCCDIR/usr/include >>compopt
echo -I. >>compopt
 
#mindent lefordítunk 

find *.cpp | while read NAME; do
   if [ ! -e `basename $NAME .cpp`.o ]; then
       if c++ `cat compopt` -c  $NAME 2>>outcpp; then
          echo $NAME OK
       else
          echo $NAME failed
          exit 1
       fi
   fi
done

#szerkesztünk

if [ "$TRGTYP" == "lib" ]; then

    ar -c -q $LIBPATH/$TARGET.lib *.o 

 
elif [ "$TRGTYP" == "so" ]; then

    echo "-L$LIBPATH" >rsplink
    while [ ! "$3" == "" ]; do
        dspec $3
        echo $DSPEC/$3 >>rsplink  
        shift
    done
    echo "-Wl,-soname=lib$TARGET.so" >>rsplink  
    c++ -shared -o $LIBPATH/lib$TARGET.so *.o `cat rsplink` 


elif [ "$TRGTYP" == "exe" ]; then 

    echo "-L$LIBPATH"                           >rsplink
    echo "-Wl,--start-group"                   >>rsplink
 
    find *.o | while read NAME; do
        echo $NAME                             >>rsplink
    done

    while [ ! "$3" == "" ]; do
        dspec $3
        echo $DSPEC/$3                         >>rsplink  
        shift
    done

    echo '-Wl,--end-group'                     >>rsplink 
    cat $CCCDIR/usr/options/$CCCBIN/link.opt   >>rsplink 
 
    c++ -o $EXEPATH/$TARGET.exe `cat rsplink`
fi


 