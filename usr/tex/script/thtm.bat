@echo off

if exist %1.tex goto tex
    echo Igy kell indítani: T TEXFILE (kiterjesztés nélkül)
    goto stop
    
:tex

md html 2>nul

cwi2lat <%SCRIPT%\sethtm.tex      >html\%1.tmp
if "%2"==""  goto begdoc
cwi2lat <.\%2                    >>html\%1.tmp  
:begdoc

echo    \begin{document}         >>html\%1.tmp
echo    \beforeany               >>html\%1.tmp 
cwi2lat <%1.tex                  >>html\%1.tmp
echo    \afterany                >>html\%1.tmp 
echo    \end{document}           >>html\%1.tmp


cd html
 
latex %1.tmp

if not exist %1.toc goto toc
    copy %1.toc %1.toc1
    toc2lat <%1.toc1 >%1.toc
    del %1.toc1 
:toc 

:ennek kéne itt lenni, 
:de nem működik a pipe az új tth-ban???
:tth -v -L%1 <%1.tmp 2>outtth | tth2htm >%1.html 

tth -v -L%1 <%1.tmp >%1.tth 2>outtth 
tth2htm <%1.tth >%1.html  

del %1.tth
del *.tmp
del %1.dvi

start %1.html
:stop
