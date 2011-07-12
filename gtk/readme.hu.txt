
Installáció
===========

1. GTK fejlesztő környezet kell.

2. Bemegyünk gtk/codegen-be,
   elindítjuk az m (Windowson m.bat) scriptet,
   lefordulnak a kódgeneráló programok.   

3. Még mindig gtk/codegen-ben
   elindítjuk az s (s.bat) scriptet,
   létrejön a gtk/code_generated directory,
   és abban kb. 1MB generált cpp és prg kód.

4. Átmegyünk a gtk/code_byhand directoryba,
   itt megtaláljuk a gtk-ubuntu.bld, gtk-freebsd.bld, stb. filéket.
   Ezek az én gépeimen levő konfigurációt tükrözik.
   Meg kell írni ezek helyett a saját konfigurációnkhoz
   passzoló bld filét (azaz meg kell keresnünk, hogy hol
   vannak az include filék és a könyvtárak).
   Az aktualizált bld filé nevét be kell írni az m scriptbe.

5. Elindítjuk az előbb előkészített m scriptet,
   lefordul és installálódik a ccc3_gtk.so könyvtár.
   Itt kezdetben hibák adódhatnak, aminek valószínű oka, 
   hogy a bld-ben rosszul adtuk meg az include és lib directorykat.
   Később (amikor már csak CCC szinten dolgozunk) nincs szükség 
   a GTK környezet megadására, mert csak a ccc3_gtk.so-t kell 
   linkelni a CCC környezetből.

6. Kipróbáljuk a példaprogramokat.


Projekt státusz
===============

A CCC-GTK interfész nincs fejlesztés alatt. 
Egyszerűbb dolgokat meg lehet vele írni, 
de egy csomó dolog még csak ki sincs próbálva.
A GTK-ban meglehetősen gyakran változnak az API-k,
ezért meglevő programok is idővel elromolhatnak,
ezek javításával nem foglalkozom:
Ha valami nem fordul le, azt egyszerűen kihagyom.
Azért van ez így, mert jelenleg nincs szükségem a GTK-ra,
és belátható időben nem is tervezem a használatát.


GTK környezet
=============

A GTK hektikusan változik. A CCC-GTK interfész fejlesztésekor a 2.8-as
verziót használtam. A régebbi kiadásokból hiányoznak  olyan API-k, 
amikre a CCC hivatkozik. Újabb verziókban viszont az azóta megváltozott
vagy megszűnt API-k miatt lehetséges, hogy nem fordul le egy s más.

Linuxon mindenesetre a disztribúcióval jövő GTK környezetet kell használni.

Windowson az idők során állandóan változott, honnan lehetett GTK-hoz jutni. 
A legutolsó kipróbált konfigurációban a windowsos mono-ból sikerült GTK 
könyvtárakat szerzni. Nálam ez van installálva:

    mono-2.0.1-gtksharp-2.10.4-win32-1.exe

Ez viszont nem jó:

    mono-2.6.3-gtksharp-2.12.10-win32-4.exe

Ezzel az újabb mono-val készült CCC programok ismeretlen okból nem indulnak el. 
Depends.exe mutatja egy APPHELP.DLL hiányát, de nem ez az ok, mert ez DLL a 
korábbi változattal linkelt programoknál is hiányzik (amik azonban elindulnak).

A mono-t nem a default "C:\Program Files"-ba kell installálni, mert a CCC 
prerocesszor az ilyen spéci nevű directorykban hibásan működik, hanem
egyszerűen pl. c:\mono-ba. A környezetben megadjuk: GTKDIR=c:\mono


Windows változat
================

Windows 2000 SP4-et használok. Újabb Windowsokon nem tesztelek, aki ilyesmin 
próbálkozik, magára van utalva. A CCC Windowson nem támogatja a 64 bitet.


C compiler
==========

Linuxon (és egyéb UNIX-okon) a disztribúcióval jövő gcc-t használjuk.

Windowson a GCC (MinGW) és Microsoft C is megfelel, ezeket használtam:

  gcc version 3.4.5 (mingw-vista special r3)
  Microsoft (R) 32-bit C/C++ Optimizing Compiler Version 13.10.3077 for 80x86


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


CCC2
====

Installálás/konfiguráció ugyanaz, mint CCC3-nál.

A CCC2-es GTK még kevésbé kurrens, mint a CCC3-as.

A CCC2-es GTK interfész specialitása a karakterkódolás.
A GTK eleve mindig is UTF-8 kódolást használt, a CCC2-ben azonban
a régi Latin és CWI kódolás van. A CCC2-GTK interfész a kapcsolódási 
pontokon automatikus karakterkonverziót végez.

