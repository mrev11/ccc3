:set PREVIEW=dviwin2
set PREVIEW=yap
set SCRIPT=%CCCDIR%\usr\tex\script
 
:%SCRIPT%\tdvi.bat %1
%SCRIPT%\thtm.bat %1
