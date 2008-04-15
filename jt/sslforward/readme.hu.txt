
OpenSSL könyvtár készítése Windowson
====================================

Használat MSVC-vel
------------------
 
Az openssl könyvtárat MSVC6.0-val lehet lefordítani,
ahogy az a readme-ben le van írva (Perl-re van szükség).

Megj: A Borlandos fordítás már az elején elakad.
Megj: A MinGW fordítás messzire jut, de végül elakad.

A fordítás után az eredményeket a megfelelő helyre kell másolni:

Az import libeket a compiler lib könyvtárába.
A dll-eket és openssl.exe-t a pathba, pl. winnt-be.
A header filéket include/openssl-be.


Használat Borland C-vel
-----------------------

Az MSVC-vel készített dll-ek használhatók Borland C-vel is,
ehhez import libeket kell csinálni az alábbi parancsokkal:

implib -a libeay32.lib  libeay32.dll 
implib -a ssleay32.lib  ssleay32.dll

Ahol a két dll az MSVC fordítóval készült az előző pont szerint. 
Az alkatrészeket most is a megfelelő helyekre kell másolgatni. 


Használat MinGW-vel
-------------------

Az MSVC-vel készült könyvtárak használhatók MinGW-vel is.
 