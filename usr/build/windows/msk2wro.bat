@echo off 
echo MSK2WRO.BAT %1 %2 
msk2pge -ur %2\%1 %2\%1.x
if     exist %2\%1.sor pge2wro -r %2\%1.sor %2\%1.x
if not exist %2\%1.sor pge2wro              %2\%1.x
del %2\%1.x

@echo -------------------------------------------------------------------------
 