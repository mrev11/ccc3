@echo off
set LC_COLLATE=C  

set PRINTER=%1

echo %PRINTER%           >log-%PRINTER%
echo WINDOWS            >>log-%PRINTER%

set | grep CCC | sort   >>log-%PRINTER%

cat                     >>log-%PRINTER%



