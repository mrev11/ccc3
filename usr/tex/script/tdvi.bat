@echo off
if exist %1.tex goto tex
    echo Igy kell indítani: T TEXFILE (kiterjesztés nélkül)
    goto stop
    
:tex
md dvi 2>nul

cwi2lat  <%SCRIPT%\setdvi.tex     >dvi\%1.tmp
cwi2lat  <.\%2                   >>dvi\%1.tmp
echo     \begin{document}        >>dvi\%1.tmp
cwi2lat  <%1.tex                 >>dvi\%1.tmp
echo     \end{document}          >>dvi\%1.tmp

cd dvi 
 
latex %1.tmp
del *.tmp

if not exist %1.dvi goto stop

start %PREVIEW% -1 %1.dvi
 
:stop
