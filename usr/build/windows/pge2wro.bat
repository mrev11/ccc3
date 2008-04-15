@echo off 
echo PGE2WRO.BAT %1 %2 
if     exist %2\%1.sor pge2wro -r %2\%1.sor %2\%1
if not exist %2\%1.sor pge2wro              %2\%1 

@echo -------------------------------------------------------------------------
 