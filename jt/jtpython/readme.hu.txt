Python interfész Jáva terminálhoz 

http://ok.comfirm.hu/ccc2/download/jtpython.zip

A jtpython csomag célja a Jáva terminál API implementálhatóságának
demonstrálása. Mindamellett a csomag gyakorlati feladatok megoldására
is alkalmas.

Miért érdemes jterminált használni  Tk, Qt, GTK, Wx stb. helyett?

1) A Jáva terminál érdekesebb, mint a felsorolt toolkitek.

2) A pehelysúlyú jtpython könyvtár SOKKAL EGYSZERŰBB, 
   mint a felsorolt toolkitek, vagy akár csak azok interfészei. 
   Ebből adódóan a jtpythonos programok STABILAK.

3) A Jáva terminálnak magasabb szintű interfésze van, 
   ami ügyviteli programokban termelékenyebben használható.

4) A szerver és a megjelenítő külön gépen is futhat, ezáltal
   centralizált, vagy internetes alkalmazás is készíthető.

5) Ha egy böngészős ügyfél gépén installálva van a JRE, akkor
   úgy is elindul nála az alkalmazásunk (klikkre), hogy soha nem 
   hallott rólunk (a Jáva Webstart technológia révén).

 
Telepítés:

1) Szükség van a Python XML moduljára.
2) A site.py modulban encoding='ascii'-t encoding='latin-1'-re cseréljük.
3) A jtlib directoryt berakjuk a PYTHONPATH-ba.


Megjegyzések:

A program nincs felkészítve Unicode/UTF-8 kódolásra,
hanem bedrótozottan Latin-1-et használ.

A program csak felületesen van tesztelve, a mellékágak több helyen
még egyáltalán nem futottak, így hibák, elírások bárhol előadódhatnak. 
Ugyanakkor koncepcionális, vagy nehezen kijavítható hiba valószínűleg 
nincs a programban.

Bizonyos funkciók tesztelése azért maradt el, mert nem találtam
megfelelő Python eszközt. Pl. nem tudom, hogyan lehet Pythonban 
digitális aláírást ellenőrizni (nincs OpenSSL interfész?).

Hiányzik a táblaobjektum browse, mert Pythonban nincs táblaobjektum
könyvtár.

Nincs a jtpython-nal használható dialog editor. A CCC eszközök
használhatók, az msk2dlg könnyen átalakítható úgy, hogy CCC helyett
Python kódot generáljon.

A fenti hiányokon túl a jterminal használata CCC-ből és Python-ból
MEGEGYEZIK. A terminál (természetesen) nem érzékeli, hogy CCC, vagy
Python szerverprogrammal áll-e szemben.

A programokat ugyanúgy futtatjuk, mint CCC környezetben.
A tesztprogramok indításához definiáljuk a JTERMINAL környezeti változót, 
aminek tartalma a jterminal.jar teljes fájlspecifikációja. 
