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


nl() vs. nonl() mód
-------------------

Azt írja a man, hogy nl() bekapcsolja, nonl() kikapcsolja
a kimeneten az nl->crnl konverziót:

   The  nl and nonl routines control whether the underlying
   display device translates the return key into newline on
   input, and whether it translates newline into return and
   line-feed on output.  Initially, these  translations  do
   occur.

Nem így van! Minden esetben az ncurses-es programok induláskor
KIKAPCSOLJÁK az nl->crnl konverziót. Azt hogy egy terminálban
be van-e kapcsolva a konverzió az stty programmal lehet megnézni.

   ssty -F /dev/pts/n  -a | grep onlcr
   
(n-edik pts). Ha be van kapcsolva, akkor 'onlcr' van a kimeneten,
ha nincs bekapcsolva, akkor '-onlcr'. Ellenőrizhető, hogy akár
meg van híva nl() vagy nonl(), akár nincs, az ncurses-es program 
pszeudo terminálja -onlcr állapotban van. Az ncurses-es program
kilépéskor visszaállítja a terminált a default onlcr módba.
(Szintén az ssty-vel ellenőrizhető). Ha a visszaállítás elmarad,
akkor lép fel az ismert jelenség, amikor is a parancsor kurzora 
nem talál vissza balra, hanem mindig csak jobbra és lefele halad.

Az nl() és nonl() igazi jelentése: 

nl módban a kurzor lefele mozgatására olyan kód generálódik,
ami használja a \n vezérlő karaktert, és FELTÉTELEZI, hogy a 
terminál nem végez \n->\r\n konverziót. Ha mégis végez, akkor 
a generált kód rossz lesz. Például az ilyen kódot fájlba mentve, 
majd a fájlt konvertáló terminálba cat-olva hibás képet kapunk.

nonl módban a könyvtár a kurzor mozgatására NEM HASZNÁL \n-t,
hanem konkrétan megadott sorokra pozicionál. Ennek az az előnye, 
hogy nem számít, vajon a terminál végez-e \n->\r\n-t. Az ilyen 
kimenetet el lehet menteni, majd cat-olni, nem romlik el. 

Célszerű tehát nonl módot használni.



K_ALT_* billentyűk vs ékezetes karakterek
-----------------------------------------
  
Az xterm alapállapotban ALT+betűre UTF-8 szekvenciákat küld.
Ezek az UTF-8 karakterek összevissza helyeken vannak
(ezért lényegében nem lehet őket használni) emellett elfedik
az alt-os kombinációkat, amik kellenek a z-ben editáláshoz.
Ezért az INKEYMAP_xtrem fájlban ilyen sorok voltak

    K_ALT_A       c3a1,-1
    K_ALT_B       c3a2,-2
    K_ALT_C       c3a3,-3
    ...

amik UTF-8 szekvenciák helyett a K_ALT_* inkey kódokat adták. 
Választani kellett, hogy inkey kódokat akarunk-e inkabb, 
vagy ékezetes karaktereket. Az inkey kódokat választottam.

Van azonban jobb megoldás.  Létre kell hozni a ~/.Xdefaults
fájlt az alábbi tartalommal (vagy, ha már van, akkor beleírni):

    xterm*metaSendsEscape: true

Ennek hatására az xterm ALT-a-ra \Ea szekvenciát (stb) küld. 
Ha tehát az előbbi sorokat kicseréljük

    K_ALT_A       1b61,-1
    K_ALT_B       1b62,-2
    K_ALT_C       1b63,-3
    ...
    
akkor megvannak az K_ALT_* inkey kódok. Plusz berakjuk a
következő sorokat:

    á c3a1,225
    é c3a9,233
    í c3ad,237
    ó c3b3,243
    ...
   
és akkor megvannak az ékezetes betűink is. Jelen állapotában
a readkey nem konvertál tetszőleges UTF-8 szekvenciát, csak
azokat, amiket beírunk az INKEYMAP fájlba.

Megj: Az .Xdefaults új tartalma akkor válik hatásossá, ha az 
X-et újraindítjuk, vagy a fájlt xrdb-vel explicite betöltjük.

Megj: Xfce4-ben a keyboard layout átállítása 'system defaults'-ról
(bármire) azt okozza, hogy az ALT-navigáció szekvenciák elromlanak,
és csak az X újraindításával állnak helyre.















