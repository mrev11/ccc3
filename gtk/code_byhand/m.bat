@echo off
pushd ..\codegen 
    call m.bat
    run.exe
popd

mkdir obj%CCCBIN%
::pkg-config --cflags gtk+-2.0  >obj%CCCBIN%\gtk-cflags
::pkg-config --libs   gtk+-2.0  >obj%CCCBIN%\gtk-libs
echo -Wno-deprecated-declarations >>obj%CCCBIN%\gtk-cflags

call bapp_w32_.bat @gtk.bld  @gtk-win.bld -lccc3_gtk 

copy include\gtk.ch     %CCCDIR%\usr\include\gtk.ch
copy include\gdk.ch     %CCCDIR%\usr\include\gdk.ch
copy include\cccgtk.h   %CCCDIR%\usr\include\cccgtk.h

copy obj%CCCBIN%\ccc3_gtk.lib %CCCDIR%\usr\lib\%CCCBIN%\ccc3_gtk.lib

