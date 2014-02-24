@echo off 
grep -i undefined   log-install 
grep -i unresolved  log-install 
grep -i error       log-install 
grep -i warning     log-install
