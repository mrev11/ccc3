
A Gtk#-ból települő GTK-t használtam, 
ezek voltak telepítve:

    Microsoft.NET Framework 1.1
    Microsoft.NET Framework SDK 1.1
    Gtk# for Windows 2.7.1

Ebből lesz egy c:\gtk\2.8, 
a helyet betesszük a GTKDIR környezeti változóba.


Borland C-vel nem fordul 
(a GTK-s include-ok túl bonyolultak neki).

MinGW-vel fordul, 
de szükség van a -mms-bitfields opcióra.

MSC-vel fordul,
de az appwindow demó elszáll a text.iter.new()-ban.
Látszólag a text.iter.new() nem függ a környezettől
(nincsenek paraméterei), máshol nem száll el,
az appwindow-ban azonban elszáll (SIGSEGV).

Tehát jelenleg csak a MinGW-ben nem látszik hiba.


Az 1.2.21-nél régebbi build-del a ccc3_gtk.lib-et nem lehet 
a szokásos módon elkészíteni, mert túl sok filét kell megadni 
obj2lib.bat-nak a parancssorban.


gtk-win.bld
===========

Windowson statikus könyvtárakat használunk. A windowsos programok 
linkelésekor ezért minden könyvtárat fel kell sorolni (amik Linuxon
nem az exe-kbe, hanem a ccc3_gtk.so-ba vannak linkelve). Emiatt a GTK 
alkatrészeket megadó bld filére a későbbiekben is minden projektben 
szükség lesz. Hogy ne kelljen ezt a filét sok példányban lemásolni, 
van belőle egy példány itt: %CCCDIR%\usr\build\windows\gtk-win.bld. 
Ezt a filét meg kell editálni, hogy a GTK minden alkatrésze elérhető 
legyen az itt megadott helyen. A filét beírjuk a build parancssorába:

    build ... @gtk-win.bld ...

A build (1.2.24 változattól) az ilyen filéket a getenv("BUILD_BAT")
helyen is keresi, így elég belőle egy példányt tartani.

