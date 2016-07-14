#!/bin/bash

#ezek átkerülhetnének .git/hooks/pre-commit-ba,
#de nem tudnak átkerülni, mert a pre-commit-ban 
#végrehajtott 'git add' már nem hat a folyamatban levő commit-ra
#amúgy is a commit message felszedését bele akarom írni a commit
#indításába, tehát mindenképpen script kell, nem érdemes ezért
#a pre-commit hookal bajlódni 


#ez most durva, 
#mert egyből minden változást commitol,
#(hogy gyorsabban menjen a tesztelés)
#git add --all


filetime-save.exe
git add .FILETIME_$USER
firstpar.exe  CHANGELOG >commit-message
git commit -F commit-message
rm commit-message

