#!/bin/bash

# ezek kellenek:
#   procinc.exe
#   toc2utf.exe
#   tth
#   tth2htm-utf8.exe

BROWSER=firefox
#BROWSER=mozilla

FNAME=`basename $1 .tex`

if test -f $FNAME.tex; then 

    mkdir html 2>/dev/null

    cat <$SCRIPT/sethtm.tex               >html/$FNAME.tmp

    if test -f $2; then
        cat <$2                          >>html/$FNAME.tmp
    fi

    echo         '\begin{document}'      >>html/$FNAME.tmp
    echo         '\beforeany'            >>html/$FNAME.tmp
    procinc.exe   <$FNAME.tex            >>html/$FNAME.tmp
    echo         '\afterany'             >>html/$FNAME.tmp
    echo         '\end{document}'        >>html/$FNAME.tmp

    cd html
    
    latex $FNAME.tmp

    if test -f $FNAME.toc; then 
       mv $FNAME.toc $FNAME.toc1
       toc2utf.exe <$FNAME.toc1 >$FNAME.toc
       rm $FNAME.toc1 
    fi

    cat <$SCRIPT/head.html >$FNAME.html    
    #tth -v -L$FNAME <$FNAME.tmp >$FNAME.xxx
    tth -v -L$FNAME <$FNAME.tmp 2>outtth | tth2htm-utf8.exe >>$FNAME.html 
    cat <$SCRIPT/foot.html >>$FNAME.html    
 
    rm $FNAME.tmp
    rm $FNAME.dvi

    ps -A | grep $BROWSER | if ! read PID; then
        #echo 'MÉG NEM FUT'
        $BROWSER "$(pwd)/$FNAME.html" &
    else
        #echo 'MÁR FUT'
        echo $PID
    fi

    cd ..
 
else
    echo 'Usage: t FILE.TEX'
fi    

 