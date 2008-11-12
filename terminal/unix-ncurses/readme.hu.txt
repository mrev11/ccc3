CCC terminál ncurses interfészre
================================

A program ugyanazt az infrastruktúrát használja, mint az X-es és windowsos 
CCC terminál. UTF-8 kódolással működik, xterm-ben viszonylag tűrhetően,
Linux konzolban némiképp problematikusan.

A CCC programok sokkal több és bonyolultabb billentyűkombinációt
használnak, mint amit az ncurses könyvtár kezelni tud, ezért a keyboard 
inputot nem az ncurses eszközeivel, hanem saját eszközökkel olvassuk.

Az esc-szekvencia <-> inkey-code megfeleltetés az ~/.INKEYMAP-<termtype>
konfigurációs filékben van leírva. A <termtype> helyére a TERM környezeti 
változó értékét kell írni: xterm, linux.

Az INKEYMAP-xterm az xterm által Ubuntu-Hardyn produkált szekvenciákhoz
tartozó konfig filé.

Ubuntu-Hardyn a Linux konzol eredeti állapotában egy sor billentyűleütésre 
egyáltalán nem reagál. Ezen javít a keymap-ccc filé, amit a Linux konzolban 
kiadott

    sudo loadkeys keymap-ccc

paranccsal lehet betölteni. Ezután a Linux konzolon is működik a terminál 
az INKEYMAP-linux konfigurációs filével.


Segédprogramok:

learnkey
--------
Bekéri sorban a billentyűkombinációkat (K_UP,K_DOWN,...,K_ALT_F12),
megjegyzi, hogy ezekhez milyen esc-szekvenciák tartoznak. Az stdout-ra
írt kimenetből INKEYMAP-<termtype> konfigurációs filé készíthető.

testkey
-------
Mutatja, hogy a különféle billentyűleütésekből milyen inkey-kódok
keletkeznek, amit össze lehet vetni az inkey.ch filével (azaz látszik,
hogy mi működik, mi nem).

showseq
-------
Mutatja a billentyűkombinációkhoz tartozó esc-szekvenciákat.


Hibák:

Az esc-szekvenciák terminálfajtánként változékonyak (egy rendszeren 
belül is, pl. konzol, xterm, gnome-terminal, konsole), ezért nehézkes a 
konfiguráció. Ráadásul a gmome-terminal ugyanúgy TERM=xterm-et állít be, 
mint az xterm, miközben az esc-szekvenciák különböznek. A konsole és
gnome-terminal shortcut-jait kerülgetni kell.

A dumpkeys/loadkeys beállítások a Linux konzolra hatnak. Az X-es 
terminálok (xterm, konsole, gnome-terminal) máshonnan veszik az
esc-szekvenciáikat (nem tudom honnan).

Amikor a szerverprogram és az ncterm ugyanabban az ablakban fut, 
akkor a kilépés után a képernyő gyakran összekutyulódik. Ennek oka,
hogy először a parent (pl. a z) lép ki, ennek észlelése után lép ki 
az ncterm, és ilyenkor endwin() már hatástalan. Az elromlott képernyőt
a reset vagy tset parancsokkal lehet javítani. Lokális xterm-ben ritka 
az összekutyulódás, távoli xterm-ben és Linux konzolban viszont szinte 
mindig bekövetkezik. 

(Megj: Javításként a szerverprogramok először lezárják a socketet, 
várnak 100 msec-t, és azután lépnek ki. A 100 msec alatt a terminálnak 
alkalma van a szervert megelőzően kilépni. Ez azonban az uic könyvtár
módosítását igényli.)

Amikor a szerverprogram és az ncterm ugyanabban az ablakban fut,
akkor a konzol kimenet (QOUT) nem látszik.

Nem jól működnek azok az alkalmazások, amik run-nal elindítanak egy 
child processzt, aminek szintén lesz egy terminálja, pl. savex-ban TxtCmp. 
Ilyenkor két ncterm van egyidejűleg egymás fölött ugyanabban az ablakban,
és a leütések egy részét az alsó, más részét a felső ncterm kapja. Akkor 
is ez a helyzet, ha a felső program nem ncterm, hanem pl. mcedit.

Nem mindenhol villog a kurzor. Linux konzolban és gnome-terminal-ban 
villog, xterm-ben nem villog.

Linux konzolon nincsenek dupla dobozrajzoló karakterek.
Linux konzolon a 80x25-ös felbontásban nincsenek ékezetes karakterek.
A /boot/grub/menu.lst-ben beállított vga=791 opció hatására (azaz nagyobb
felbontásban) viszont ékezetes és cirill karakterek is vannak.

A xterm-nek kellemetlenek a színei (túl világosak), és nem állítható.

A terminál nem alkalmazkodik az xterm ablak átméretezéséhez.

Mindezen hibák miatt az ncterm csak szükségmegoldásként jön számításba, 
ha az X-es terminál nem áll rendelkezésre. 


