:beg
if [%1]==[] goto end
   set CONCAT=%CONCAT%%CONCATPRE%%1%CONCATPOST%
   shift
goto beg
:end
