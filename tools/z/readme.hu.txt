
Hogyan kell hasznalni a Z-EDITOR-t?
===================================

Billentyuk
----------

ESC      : escape

F1       : help
F3       : serach
SH-F3    : serach again
F4       : replace
SH-F4    : replace again
F6       : lower case
SH-F6    : upper case
F7       : edit clipboard
F10      : save
ALT-F10  : save CWI
CTRL-F10 : save Latin2
 
ALT-X    : cut
ALT-C    : copy
ALT-V    : paste

ALT-CRS  : kijeloles
SH-CRS   : kijeloles



Segedfilek
----------

clipbrd.z:
  a clipboard-ot tartalmazza, azert nem a Windows clipboard-ot hasznalja, 
  hogy konnyu legyen portolni UNIX-ra (megtortent)

history.z:  
  a korabban editalt filek poziciojat tartalmazza

error.z:
  az elszallasoknal keletkezo infot gyujti

keymap.z:
  billentyukod atdefinialasokat tartalmaz, csak azok a sorok szamitanak,
  amik ket vesszovel elvalasztott ASCII koddal kezdodnek  


NT-n a segedfileket a program mindig a z.exe-t tartalmazo directoryban
keresi, illetve itt hozza letre, ezert z.exe egy peldanyat egyszerre 
csak egy programozo hasznalhatja, maskulonben osszekeveredik a 
clipboard es a history.  

Linuxon a segedfilek helye ~/.z, ezert ott nincsenek ilyen korlatozasok.



Ekezetes kodkeszlet
-------------------

NT-n a program jelenleg CWI kodkeszletre van konfiguralva. Az ekezetes
betuket a magyar szabvany szeriniti helyen levu billentyukkel plusz
az ALT vagy CTRL lenyomasaval lehet kepezni. Ezenkivul a jelenlegi
keymap.z az ekezetes kisbetuket eloallitja az altalam megszokott
kombinaciokkal (pl. ALT-a=a).

Linuxon a Latin2 kodkeszletet hasznaljuk, a billentyukiosztas
az .Xmodmap es a keymap.z filekben tetszolegesen beallithato.



Kijelolesek
-----------

A kijeloles az ALT es SHIFT kombinaciokkal egyforman mukodik
(Linuxon csak az ALT-os). A Clipper inkey.ch-ban nincsnek K_SH_LEFT stb. 
szimbolumok, ezert a program mindenhol a K_ALT_LEFT stb. szimbolumokat 
hasznalja, de a billentyuzet olvasas (NT-n) ugy van konfiguralva, 
hogy a SHIFT-es kombinacio ugyanazt az erteket adja, mint az ALT-os.



Copy/Paste
----------

A copy funkcio nem lehet CTRL-C, mert az NT-n megallitana a programot,
ezert CTRL helyett ALT-os billentyukombinaciokat hasznalunk.



Alert
-----

Az itteni alert csak abban kulonbozik a standard konyvtari
alert-tol, hogy zold, ezenkivul egyszerubb, esztetikusabb kodja van.






