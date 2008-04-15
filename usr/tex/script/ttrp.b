#!/bin/bash

FNAME=`basename $1 .trp`

if test -f $FNAME.trp; then 
    
    rm -f dvi
    mkdir dvi 2>/dev/null

    cat  <$FNAME.trp >$FNAME.tex
    latex   $FNAME.tex
    
    if test -f $FNAME.dvi; then

        rm $FNAME.log
        rm $FNAME.tex
        rm $FNAME.aux
        mv $FNAME.dvi dvi
        
        if ! test -f dview; then
            $CCCDIR/usr/tex/script/dview.b dvi/$FNAME.dvi &
        fi

    else
        echo 'NO OUTPUT'
    fi

else
    echo 'Usage: t FILE.TRP'
fi    
