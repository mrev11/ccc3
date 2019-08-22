@echo off
copy metdecl.cpp3 metdecl.cpp
del objmng\metdecl.obj
del error 2>nul
bapp_w320 -mppo2cpp "BUILD_EXE=$(CCCDIR)\usr\bin\$(CCCUNAME)"
