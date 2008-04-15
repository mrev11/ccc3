
Hogyan kell használni a Z-EDITOR-t?
===================================

Billentyűk
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

ALT-CRS  : kijelölés
SH-CRS   : kijelölés



Segédfilék
----------

clipbrd.z:
  a clipboard-ot tartalmazza, azért nem a Windows clipboard-ot használja, 
  hogy könnyű legyen portolni UNIX-ra (megtörtént)

history.z:  
  a korábban editált filék pozícióját tartalmazza

error.z:
  az elszállásoknál keletkező infót gyűjti

keymap.z:
  billentyűkód átdefiniálásokat tartalmaz, csak azok a sorok számítanak,
  amik két vesszővel elválasztott ASCII kóddal kezdődnek  


NT-n a segédfiléket a program mindig a z.exe-t tartalmazó directoryban
keresi, illetve itt hozza létre, ezért z.exe egy példányát egyszerre 
csak egy programozó használhatja, máskülönben összekeveredik a 
clipboard és a history.  

Linuxon a segédfilék helye ~/.z, ezért ott nincsenek ilyen korlátozások.



Ékezetes kódkészlet
-------------------

NT-n a program jelenleg CWI kódkészletre van konfigurálva. Az ékezetes
betűket a magyar szabvány szeriniti helyen lévű billentyűkkel plusz
az ALT vagy CTRL lenyomásával lehet képezni. Ezenkívül a jelenlegi
keymap.z az ékezetes kisbetűket előállítja az általam megszokott
kombinációkkal (pl. ALT-a=á).

Linuxon a Latin2 kódkészletet használjuk, a billentyűkiosztás
az .Xmodmap és a keymap.z filékben tetszőlegesen beállítható.



Kijelölések
-----------

A kijelölés az ALT és SHIFT kombinációkkal egyformán működik
(Linuxon csak az ALT-os). A Clipper inkey.ch-ban nincsnek K_SH_LEFT stb. 
szimbólumok, ezért a program mindenhol a K_ALT_LEFT stb. szimbólumokat 
használja, de a billentyűzet olvasás (NT-n) úgy van konfigurálva, 
hogy a SHIFT-es kombináció ugyanazt az értéket adja, mint az ALT-os.



Copy/Paste
----------

A copy funkció nem lehet CTRL-C, mert az NT-n megállítaná a programot,
ezért CTRL helyett ALT-os billentyűkombinációkat használunk.



Alert
-----

Az itteni alert csak abban különbözik a standard könyvtári
alert-től, hogy zöld, ezenkívül egyszerűbb, esztétikusabb kódja van.






