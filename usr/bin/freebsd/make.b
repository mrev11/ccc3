#!/bin/bash
#set -x

# Ez nem egy altalanos utility, hanem a CCC setup alkatresze.
#
# Hivasi formak
#
# 1) make.b lib name               (statikus konyvtar minden cpp-bol)
# 2) make.b so  name lib1 lib2 ... (so konyvtar minden cpp-bol + lib-ek)
# 2) make.b exe name lib1 lib2 ... (exe program minden cpp-bol + lib-ek)
#
# A statikus konyvtarak nevkepzese : name.lib
# A shared konyvtarak nevkepzese   : libname.so
# Az onallo programok nevkepzese   : name.exe
#
# Az exe programok mindig $CCCDIR/usr/bin/$CCCUNAME-ban keletkeznek.
# A konyvtarak mindig $CCCDIR/usr/lib/$CCCBIN-ben jonnek letre,
# ezt a directoryt letre is hozza, ha korabban nem letezett.
#
# A linkeleskor hasznalt lib-eket path nelkul, de teljes nevvel
# kell megadni (libMesaGL.so). A konyvtarat az dspec function
# megkeresi a SEARCHDIR-ben megadott helyeken, es teljes file
# specifikacioval adja tovabb a linkernek. A SEARCHDIR tartalmat
# az adott Linux installacionak megfeleloen modositani kell.


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

if ! test -f $CCCDIR/usr/options/$CCCBIN/cppver.opt; then
   cppver.b
fi
cat $CCCDIR/usr/options/$CCCBIN/cppver.opt >compopt
cat $CCCDIR/usr/options/$CCCBIN/compile.opt >>compopt
echo -I$CCCDIR/setup/unix/include >>compopt
echo -I$CCCDIR/usr/include >>compopt
echo -I. >>compopt

#mindent leforditunk

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

#szerkesztunk

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


