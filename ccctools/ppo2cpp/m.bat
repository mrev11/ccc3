@echo off
del error 2>nul
bapp_w320 -mppo2cpp "BUILD_EXE=$(CCCDIR)\usr\bin\$(CCCUNAME)"
