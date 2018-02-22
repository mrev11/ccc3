@echo off

set CCCVER=3

:-------------------
: initial setup
:-------------------

pushd setup\setup-windows 
call m.bat
popd

pushd setup\setup-flex
call m.bat
popd

pushd setup\setup-lemon
call m.bat
popd

pushd ccctools\ppo2cpp
call m.bat
popd

flex -V
lemon -x
prg2ppo.exe -v
ppo2cpp.exe -v
:build.exe -v 


:-------------------
: ccclib
:-------------------

pushd ccclib
call m.bat
popd


:-------------------
: ccctools
:-------------------
 
pushd ccctools\removecr
call m.bat
popd

pushd ccctools\ccomp
call m.bat
popd
 
pushd ccctools\buildp
call m.bat
popd

pushd ccctools\prg2ppo
call m.bat
popd

:-------------------
: terminal
:-------------------

pushd terminal\windows
call m.bat
popd

pushd terminal\sslforw
call m.bat
popd

if not exist %CMPDIR%\include\gtk-2.0\gtk\gtk.h goto terminal-gtk
  pushd terminal\gtk
  call m.bat
  popd
:terminal-gtk

if not exist %CMPDIR%\include\gtk-3.0\gtk\gtk.h goto terminal-gtk3
  pushd terminal\gtk3
  call m.bat
  popd
:terminal-gtk3

:-------------------
: msk2say.exe-t elore
:-------------------

pushd tools\mask
call m.bat
popd

:-------------------
: tabobj
:-------------------

pushd tabobj\tbbtbtx
call m.bat
popd

:-------------------
: tools
:-------------------
 
pushd tools\crypto
call m.bat
popd

pushd tools\dbaseiii
call m.bat
popd

pushd tools\dbfview
call m.bat
popd

pushd tools\ddict2
call m.bat
popd

pushd tools\list
call m.bat
popd

pushd tools\regex
call m.bat
popd

pushd tools\savex
call m.bat
popd

pushd tools\socket
call m.bat
popd

pushd tools\tran2cpp
call m.bat
popd

pushd tools\websrv
call m.bat
popd

pushd tools\xmldom
call m.bat
popd

pushd tools\xmlrpc
call m.bat
popd

pushd tools\xstart
call m.bat
popd

pushd tools\z
call m.bat
popd

pushd tools\zgrep
call m.bat
popd

pushd tutor\dtree
call m.bat
popd

pushd tutor\rename
call m.bat
popd

pushd tutor\fpath
call m.bat
popd

pushd jt\jtlib
call m.bat
popd


:stop
 
