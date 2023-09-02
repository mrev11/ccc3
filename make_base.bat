@echo off

call make_verf.bat 3

:-------------------
: initial setup
:-------------------

pushd setup\setup-flex    &  call m.bat & popd
pushd setup\setup-lemon   &  call m.bat & popd
pushd setup\setup-windows &  call m.bat & popd
pushd ccctools\ppo2cpp    &  call m.bat & popd

flex -V
lemon -x
prg2ppo.exe -v
ppo2cpp.exe -v
build.exe -v 

:-------------------
: ccclib
:-------------------

pushd ccclib & call m.bat & popd

:-------------------
: ccctools
:-------------------
 
pushd ccctools\removecr &  call m.bat & popd
pushd ccctools\ccomp    &  call m.bat & popd
pushd ccctools\build    &  call m.bat & popd
pushd ccctools\prg2ppo  &  call m.bat & popd


:-------------------
: terminal
:-------------------

pushd terminal\windows & call m.bat & popd
pushd terminal\windows-console & call m.bat & popd
pushd terminal\sslforw & call m.bat & popd

if exist %MSYS%\%MSYSTEM%\include\gtk-2.0\gtk\gtk.h (
    pushd terminal\gtk2 & call m.bat & popd
)
if exist %MSYS%\%MSYSTEM%\include\gtk-3.0\gtk\gtk.h (
    pushd terminal\gtk3 & call m.bat & popd
)

:-------------------
: msk2say.exe-t elore
:-------------------

pushd tools\mask & call m.bat & popd

:-------------------
: tabobj
:-------------------

pushd tabobj\tbbtbtx & call m.bat & popd

:-------------------
: tools
:-------------------
 
pushd tools\crypto      & call m.bat & popd
pushd tools\pcre2       & call m.bat & popd
pushd tools\regex       & call m.bat & popd
pushd tools\socket      & call m.bat & popd
pushd tools\tdc2prgch   & call m.bat & popd
pushd tools\textview    & call m.bat & popd
pushd tools\xmldom      & call m.bat & popd
pushd tools\xmlrpc      & call m.bat & popd
pushd tools\xstart      & call m.bat & popd
pushd tools\z           & call m.bat & popd


