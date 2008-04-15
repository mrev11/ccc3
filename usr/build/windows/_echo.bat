:beg
if [%1]==[] goto end
   echo %ECHOPRE%%1%ECHOPOST% >>%ECHOOUT%
   shift
goto beg
:end
