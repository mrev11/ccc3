#!/bin/bash
#C++/CCC environment

. ${CCCDIR}/usr/setenv/colors

CPPVER=$(c++ -v 2>&1 | grep \ version)

echo -e $BOLD
echo -e $RED
echo $CPPVER
echo CCCVER=$CCCVER
echo CCCDIR=$CCCDIR
echo CCCUNAME=${CCCUNAME}
echo CCCBIN=${CCCBIN}
echo CCCTERM_CONNECT=$CCCTERM_CONNECT
echo CCCTERM_INHERIT=$CCCTERM_INHERIT

echo -e $YELLOW
cat $CCCDIR/usr/options/${CCCUNAME}/${CCCBIN}/cppver.exp
echo -e $RESET

