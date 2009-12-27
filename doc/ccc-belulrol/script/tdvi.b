#!/bin/bash

FNAME=`basename $1 .tex`

if test -f $FNAME.tex; then 
    
    mkdir -p dvi

    cat <$SCRIPT/setdvi.tex              >$FNAME.tmp
   
    echo '\begin{document}'             >>$FNAME.tmp
    cat  <$FNAME.tex                    >>$FNAME.tmp
    echo '\end{document}'               >>$FNAME.tmp

    latex $FNAME.tmp
    
    if test -f $FNAME.dvi; then
        mv $FNAME.* dvi
        mv *.aux dvi
        mv dvi/$FNAME.tex .  #vissza
        
        
        if ! test -f dview; then
            $SCRIPT/dview.b  dvi/$FNAME.dvi &
        fi

    else
        echo 'NO OUTPUT'
    fi

else
    echo 'Usage: t FILE.TEX'
fi    

