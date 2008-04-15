@echo off 
echo MSK2SAY.BAT %1 %2 
if     exist %2\%1.sor msk2say -r %2\%1.sor  %2\%1
if not exist %2\%1.sor msk2say               %2\%1 

@echo -------------------------------------------------------------------------
 