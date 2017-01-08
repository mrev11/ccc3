
# CCC belülről

_Dr. Vermes Mátyás_

2009\. december


[1  Bevezetés][1]  
[2  Telepítés][2]  
[3  Hello World][3]    
[4  Változók][4]  
[5  Függvényhívás][5]  
[6  Objektumok][6]  
[7  Kivételkezelés][7]  
[8  Többszálúság][8]  
[9  Unicode][9]  
[A  Régebbi dokumentációk][A]  
    A.1  [Eredeti Clipper doksi](http://ccc.comfirm.hu/pub/ng)   
    A.2  [CCC projekt manager](http://ccc.comfirm.hu/ccc3/build.html)   
    A.3  [Jáva terminál](http://ccc.comfirm.hu/ccc3/jterminal.html)   
    A.4  [SQL2 interfész](http://ccc.comfirm.hu/ccc3/sql2.html)   
    A.5  [GTK interfész](http://ccc.comfirm.hu/ccc3/cccgtk.html)   

[1]: #1
[2]: #2
[3]: #3
[4]: #4
[5]: #5
[6]: #6
[7]: #7
[8]: #8
[9]: #9
[A]: #A


##  1.  Bevezetés<a name="1"></a>

A Clipper praktikus, egyszerű, általános célra használható eszköz volt. Nem
véletlen a rendkívüli népszerűség, amire a maga idejében szert tett. A DOS-
szal együtt azonban a Clipper kihalt, az utána keletkezett űr betöltetlen
maradt. A Clipper utódok, mint a Clip, FlagShip, Harbour nem terjedtek el
széles körben, nálam egyik sem ,,nyerő", mint ahogy az új nyelvek sem. A Jáva
termelékenység helyett tudálékos, a Python túlságosan script ...

A CCC-t a banki programjainkkal párhuzamosan, saját célra fejlesztettük, azzal
az elgondolással, hogy a DOS korszak után a programokat ezzel fogjuk életben
tartani. Volt idő, amikor egyszerre DOS-on, Windowson és UNIX-(ok)on
futottunk. Minden platformra ugyanabból a forrásból fordítottunk, DOS-on
Clipperrel, máshol CCC-vel. Ugyanabból a forrásból, ez nem egy verziókezelő
rendszerből elővett különféle változatokat jelent, hanem ténylegesen
ugyanazokat a forrásfájlokat.

A CCC nem tud akármilyen Clipper kódot lefordítani. A programjainkat eleve egy
szűkített Clipperre írtuk. A legfontosabb szűkítés, hogy a CCC-nek (mint
nyelvnek) nem része az adatbáziskezelés. Mindenesetre a Clipper és a CCC közös
része elég volt egy komplex számlavezető rendszer elkészítéséhez. Amúgy a
nyelv alkalmas akármilyen adatbáziskelő szoftver (manapság leginkább SQL
interfész) megírására.

Az eredeti Clipper a mostani igényeknek már nem felelne meg. Idők során a
Clipperen túllépő fejlesztések kerültek a CCC-be: objektumok, kivételkezelés,
névterek, Unicode támogatás, SSL interfész, effélék. A CCC-t elég modernnek és
jónak tartjuk ahhoz, hogy az új projektjeinkhez se keressünk más nyelvet.

A CCC történetének fő állomásai:

  * 1996 - Már működik a CCC1. 

  * 1999 - Először a BB-ben használják éles számlavezetésre. 

  * 2002 - Többszál támogatás (CCC2=CCC1+multithreading). 

  * 2004 - 64-bit támogatás. 

  * 2005 - [LGPL](http://www.fsf.org/licensing/licenses/lgpl.txt) hatálya alá kerül. 

  * 2006 - Unicode/UTF-8 támogatás (CCC3=CCC2+Unicode). 

A jelen dokumentáció a CCC3-mal foglalkozik. A dokumentációt olyan
programozóknak szánom, akik szeretnek beszélgetni programokról,
programozásról. Nem kezdőknek. A dokumentum nem ,,egyenszilárd". Van benne
Hello World, de nem szól fejezet a for ciklusról és társairól. A Clippert
meghaladó, új részekre fókuszálok, ezen belül is elsősorban magára a nyelvre,
és nem a nyelven megírt könyvtárakra vagy interfészekre. A dokumentum végére
belinkeltem néhány régi doksit. A Clipper eredeti HTML leírása egyes részeiben
még mindig használható.

##  2.  Telepítés<a name="2"></a>

A CCC többféle rendszeren fut: Windowson MinGW vagy Microsoft-C fordítóval.
Különféle Linuxokon, BSD-ken, Solarison GCC fordítóval. Mi most az Ubuntu
(Debian) Linuxon történő telepítést vesszük át. Más platformokon (Windowson
is) analóg módon kell eljárni.

Először installáljuk a CCC-hez szükséges infrastruktúrát az alábbi scripttel:

    
    
    #!/bin/bash
    
    # Egy szokásos Ubuntu telepítés után
    # ezeket a csomagokat kell felrakni,
    # hogy a CCC2/CCC3 leforduljon.
    # + a jt-hez kell a Sun Java.
    # + az SQL2-höz kell a PostgreSQL.
    
    sudo apt-get install \
        g++ \
        libncurses5-dev \
        libncursesw5-dev \
        manpages-dev \
        glibc-doc \
        libx11-dev \
        libxft-dev \
        libssl-dev \
        libpcre3-dev \
        libreadline6-dev \
        git-core
    #    libgtk2.0-dev \
    #    libpangox-1.0-dev \
    
    

Végrehajtjuk az alábbi parancsot:

    
    
    git clone  git://comfirm.hu/ccc3.git
    
    

Ehhez internet kapcsolat kell. Ha a parancsot a home-unkban adtuk ki, akkor
létrejön a `$HOME/ccc3` directory, benne a CCC forrással.

A `.bashrc` fájlunkba beírjuk az alábbiakat:

    
    
    export CCCVER=3
    export CCCDIR=$HOME/ccc3
    export CCCBIN=lin
    export CCCUNAME=linux
    export CCCTERM_CONNECT="$CCCDIR/usr/bin/$CCCUNAME/terminal-xft.exe"
    export CCCTERM_INHERIT=no
    export CCCTERM_SIZE=80x40
    export CCCTERM_XFTFONTSPEC=Monospace-11
    export OREF_SIZE=50000
    
    PATH=$CCCDIR/usr/bin/$CCCUNAME:$PATH
    PATH=.:$PATH  #fontos
    LD_LIBRARY_PATH=$CCCDIR/usr/lib/$CCCBIN:$LD_LIBRARY_PATH
    export PATH 
    export LD_LIBRARY_PATH
    export LANG=en_GB.UTF-8  #valamilyen UTF-8-as locale!
    
    

Egyéb lehetséges variációk:

FreeBSD

    
    
    ...
    export CCCBIN=fre
    export CCCUNAME=freebsd
    ...
    
    

NetBSD

    
    
    ...
    export CCCBIN=net
    export CCCUNAME=netbsd
    ...
    
    

BSD-ken telepíteni kell a bash-t, és átlinkelni `/bin/bash`-be (hogy a
`#!/bin/bash` kezdetű scriptek fussanak). FreeBSD-n gondoskodni kell róla,
hogy legyen használható `malloc.h`.

Windows, MinGW

    
    
    ...
    set CCCBIN=mng
    set CCCUNAME=windows
    ...
    
    

Windows, Microsoft-C

    
    
    ...
    set CCCBIN=msc
    set CCCUNAME=windows
    ...
    
    

A Debiantól különböző rendszereken természetesen másképp kell megszerezni a
CCC függőségeit (nincs apt-get), de aki ilyeneket használ, az legyen
tájékozott a kérdésben.

Ha most elindítunk egy terminált, abban a fent beállított környezet lesz
érvényben (ellenőrizzük). Bemegyünk a CCCDIR-be, és elindítjuk az `i.b`
scriptet. Ez lefordítja az egész CCC-t (kivéve a Jáva terminált, amihez Jáva
kell, és az SQL2 könyvtárat, amihez Postgres kell.) A CCC fordításának minden
platformon warning mentesen kell futnia.

Ha a fordítás alapjaiban nem megy, akkor ellenőrizzük a környezet beállítását.

Ha egyes komponensek nem fordulnak, annak oka lehet, hogy hiányzik valami
függőség. Ilyenkor meg kell keresni, hogy konkrétan mi hiányzik, pótlólag
telepíteni, majd újraindítani az `i.b` scriptet.

Időről időre mégis megjelennek warningok, ez amiatt van, hogy a C++ fordító
ellenőrzéseit szigorítják. A CCC karbantartása során ezek rendszeresen
javításra kerülnek.

##  3.  Hello World<a name="3"></a>

Készítünk egy directoryt, mondjuk `$HOME/temp/hello`, és abban egy `hello.prg`
nevű fájlt.

    
    
    function main()
        ? "Hello World"
    
    

Kiadjuk az alábbi parancsot:

    
    
    bapp_unix_.b
    
    

amire létrejön (egyebek mellett) a `hello.exe` végrehajtható fájl. Ha ezt
elindítjuk, a terminálban megjelenik a "Hello World" szöveg.

Nagyszerű!

De ne elégedjünk meg ennyivel, nézzünk szét a fájlok között. Lett egy új
directory, a `ppo`. Ide került a `hello.ppo` (PreProcessed Output) fájl, amit
a `prg2ppo.exe` makróprocesszor készített. Minden prg fájl átmegy az
előfeldolgozáson. A prg2ppo a C-ből ismerthez hasonló, de annál bonyolultabb
és nagyobb tudású előfeldolgozó. Az eredeti Clipperben szintén megvan ez az
előfeldolgozás. A mi előfeldolgozónk - amennyire csak lehetséges -
kompatibilis az eredetivel.

A `ppo` directoryban találjuk még a `hello.cpp` fájlt. Ezt a ppo-ból készíti a
`ppo2cpp.exe` program, a tulajdonképpeni Clipper -&gt; C++ fordító. Később
tanulmányozni fogjuk a generált cpp kódot.

A szintén újonnan létrejött `objlin` directoryba került a C fordítás
eredménye, a `hello.obj` fájl. Ha a projektben könyvtárak (lib, so)
készülnének, azok is itt, az `objlin` directoryban jönnének létre.

Próbáljuk ki a következőt. Újra kiadjuk a `bapp_unix_.b` parancsot. Megjelenik
a ,,CCC Program Builder 1.2.25 Copyright (C) ComFirm Bt." felirat, de
egyébként nem történik semmi. Módosítsuk a `hello.prg` fájlt, és próbálkozzunk
újra. Látjuk, hogy a program most újra lefordul. Akkor is beindul a fordítás,
ha letöröljük az `objlin` directoryt, vagy csak egyik-másik obj fájlt. Ha az
exe-t töröljük le, akkor viszont beindul a linkelés.

Amire ki akarok lyukadni: A programkészítés elég komplex művelet. A prg
fájlokat át kell hajtani az előfeldolgozáson, a C fordításon, végül össze kell
őket linkelni más objectekkel és különféle statikus és dinamikus
könyvtárakkal. A CCC fejlesztő környezet ehhez igyekszik segítséget adni. A
programozónak nem kell leírnia, hogy melyik forrásfájlon milyen műveleteket
akar végrehajtani. Nincsenek make fájlok.

Projektben gondolkodunk. Egy directoryba beömlesztjük a projekthez tartozó
forrásfájlokat. A `build.exe` program átvizsgálja a forrásokat. A
kiterjesztésekből eleve tudja, hogy melyikkel milyen fordítási műveletet lehet
végezni. A fájlidőkből megállapítja, hogy mely fordítási műveletek időszerűek.
És ha már ilyen okos, akkor el is végzi a szükséges műveleteket.

A `bapp_unix_.b` script a `build.exe`-t indítja olyan paraméterezéssel, hogy
az összes forrás lefordításával konzolos programot készítsen. A build
széleskörűen paraméterezhető. Meg lehet mondani neki, hogy a working directory
helyett honnan vegye a forrásokat, honnan vegye az include-okat, honnan vegye
a statikus és dinamikus libeket, ha van statikus és dinamikus lib is, akkor
melyiket preferálja. Csináljon-e az objectekből libeket, ha készül exe, azt
hova tegye.

Akárhogy is, a build specialitása, hogy a forrásokat nem fájlonként, hanem
directorynként kell megadni neki. Ebből persze az következik, hogy a
munkadirectory(k)ban nem lehetnek más forrásfájlok, csak amik ténylegesen
részei a projektnek. De ez nem baj. A nem odavaló fájlokat egyszerűen
félretesszük pl. egy `nemkell` nevű subdirectoryba, így legalább tiszta marad
a kép. Az is jó, hogy a fordítás során keletkező rengeteg részeredmény
subdirectorykba kerül, így a sok szemét nem borítja el a fájlokat, amikkel
ténylegesen dolgozunk.

További lényeges sajátossága a build (CCC projekt manager) programnak, hogy
nem csak prg, hanem cpp (sőt Lemon és Flex) forrásokat is automatikusan áthajt
a fordítási műveleteken. Tehát, ha egy directoryba összegyűjtünk egy rakás
Clipper, C++, Lemon, Flex forrást, azokból egy mozdulattal tudunk libeket,
exeket fordítani/linkelni. Ennek filozófiai jelentősége van. Mutatja ugyanis,
hogy a CCC nem szakadt el a C/C++ gyökerektől, hanem a Clipper és a C
projektszinten keverhető.

Végül, szokássá vált, hogy a build-et indító parancsot (script nevet) beírjuk
egy `m` nevű fájlba (scriptbe). A CCC programkészítés így az egybetűs `m`
(make) parancsra indul.

##  4.  Változók<a name="4"></a>

###  4.1.  Deklaráció

Minden változót deklarálni kell. A deklaráció végrehajtható utasítás, helyet
csinál a változónak, és végrehajtja a változó inicializátorát. Az
inicializátor tetszőleges kifejezés lehet, ha nincs megadva explicit
inicializátor, akkor a változó NIL-re inicializálódik.

Kétféle deklaráció lehetséges, `local` és `static`.

    
    
    /*
    namespace  ...          // itt állhatna
    using      ...          // itt állhatna
    */
    
    static k1               // külső, NIL-re inicilizálódik
    static k2:=init_k2()    // a visszatérési értékkel inicializálódik
    
    function f1()
    local a, b:=1           // egyszerre több, némelyik inicializálva
    static c, d             // belső 
        ? a,b,c,d,k1,k2     // kiírja az értéküket
        ...
    
    function f2(a1,a2,a3)
        //? a,b,c,d         // ezek nem láthatók
        ? a1,a2,a3          // nem kell őket külön deklarálni (local)
        ? k1,k1             // ok, ezek láthatók
        ...
    
    

A `static` deklarációk is kétfélék:

- **külsők**
     a forrásmodul elején, az esetleges `namespace` és `using` után, de az első `function` vagy `class` utasítás előtt állhatnak,

- **belsők**
     függvények belsejében vannak, közvetlenül a `function` utasítás után, esetleg keveredve a `local` deklarációkkal, de megelőzve az összes nem deklarációs utasítást.

A külső static változók csak a forrásmodulon belül, de ott minden függvényből
láthatók. A belső static változók csak az adott függvényen belül láthatók.
Egyáltalán nincsenek az egész programra kiterjedő globális láthatóságú
változók. A static változók inicializátora a program futása során egyszer
hajtódik végre. A static változók a program futása alatt nem vesztik el
értéküket (vagyis mindig őrzik az utolsó értékadással kapott értéket). A belső
static változók a függvény első hívásakor a leírt sorrendben inicializálódnak.
A külső static változók akkor inicializálódnak, amikor a program először
hivatkozik az értékükre. A külső static változók inicializálása szinkronizált.
A szinkronizáció biztosítja, hogy a külső static-ok többszálú programban se
inicializálódjanak többször. A belső static-oknál a szinkronizáció az
alkalmazásra van bízva.

Egy local deklaráció mindig belső. A local deklarációk a belső static
deklarációk helyén (azokkal esetleg keveredve) fordulhatnak elő. A local
változók csak az adott függvényen belül láthatók. A local változók a függvény
minden hívásakor inicializálódnak, ha másra nem, hát NIL-re. Egyszerűen
szólva, a `local` utasítás közönséges stack változókat deklarál.

Ha egy változót deklaráció nélkül próbálnánk használni, a fordító hibát jelez.

A függvények argumentum változóit nem kell (nem is lehet) külön deklaráni,
ugyanúgy viselkednek mint a local változók.

Névegyezés esetén a local és a belső static változók eltakarják a külső static
változókat.

A változónevekben a kis- és nagybetűk egyformának számítanak. Valójában az
egész nyelv case insensitive, ami Clipper örökség, és a kompatibilitás
kényszere folytán nem változtatható. A CCC-ben megszokott, hogy túlnyomóan
kisbetűket használunk.

A változó- és függvényneveket ugyanúgy képezzük, mint C-ben. Néhány
fenntartott kulcsszót (`if`, `while`, `for`, ...) kerülni kell. A változó- és
függvénynevek nem zavarják egymást (nem tudnak ütközni).

###  4.2.  Értékek

A Clipper/CCC-ben nem a változóknak, hanem elsősorban az _értékeknek_ van
típusa. Ez alapján persze utólag mondhatjuk, hogy egy változónak az a típusa,
ami a benne tárolt értéknek. Az így értelmezett típus azonban minden
értékadáskor megváltozhat. A változók uniformok: Akármelyik változó képes
tartalmazni akármilyen értéket. Ennek megfelelően a fordító nem foglalkozik a
változók típusának ellenőrzésével.

Nézzük, mi van egy értékben (teljes infó a variable.h-ban):

  * Tartalmazza az érték típusát. 

  * Fix méretű adatoknál (mint szám, dátum, logikai) tartalmazza magát az adatot. 

  * Változó méretű adatoknál (mint string, array) egy memóriaobjektum referenciát (OREF). 

  * Referencia változóknál egy VALUE referenciát (VREF). 

Úgy kell elképzelni, hogy egy változó a számára fenntartott memóriában
tartalmazza az előbb leírt struktúrájú _értéket_. Amikor a program végrehajtja
az

    
    
        a:=b
    
    

_értékadást_, akkor a `b`-hez tartozó memóriaterületen tárolt _érték_
átmásolódik az `a`-hoz tartozó memóriaterületre. Vagyis `a` átveszi `b`
típusát és minden adatát. Különösen érdekes, amikor az adat egy referencia.
Ilyenkor a két változó közösködik ugyanazon a tartalmon.

###  4.3.  Típusok

Akármi is van a változóban, a `valtype()` függvénnyel lekérdezhető az aktuális
típusa. `valtype()` visszatérési értéke karakter típusú. A következő típusok
vannak: NIL, logikai, szám, dátum, pointer, karakter (Unicode string), binary
(bájt string), array (érték tömb), kódblokk, objektum, referencia. Ezeket
vesszük sorra az alábbiakban.

####  4.3.1.  NIL

    
    
        valtype(NIL)    // --> "U"
        len(NIL)        // --> 0
        empty(NIL)      // --> .t.
        NIL==3.141592   // --> .f.
        NIL==NIL        // --> .t.
    
    

Az explicite nem inicializált változók értéke NIL, típusjele U. A `return`
utasítás nélkül befejeződő függvények visszatérési értéke NIL. A NIL hossza 0,
a NIL üres, a NIL bármivel (bármilyen típussal) összehasonlítható, de csak
saját magával egyenlő. (Általában csak azonos típusú változók hasonlíthatók
össze, a NIL ebben kivételes.) A NIL-t már a típusa azonosítja, nem tartalmaz
semmilyen adatot.

####  4.3.2.  Logikai

    
    
        valtype(.t.)    // --> "L"  (logikai true literál)
        valtype(.f.)    // --> "L"  (logikai false literál)
        empty(.t.)      // --> .f.
        empty(.f.)      // --> .t.
    
    

Logikai értéket adnak az összehasonlító operátorokkal képzett kifejezések. A
logikai értékekkel használható operátorok:

    
    
        x .and. y    // --> .t., ha x==.t. és y==.t.
                     // ha x==.f., akkor y nem értékelődik ki
    
        x .or.  y    // --> .t., ha x==.t. vagy y==.t.
                     // ha x==.t., akkor y nem értékelődik ki
                     
        ! x          // --> .t., ha x==.f.
        .not. x      // --> .t., ha x==.f. (ugyanaz bőbeszédűen)
    
    

A logikai műveletek precedenciája a szokásos, lehet zárójelezni.

####  4.3.3.  Szám

    
    
        valtype(3.141592)   // --> "N"  (szám literál)
        empty(0)            // --> .t.  (csak a 0 üres)
        empty(1)            // --> .f.
    
    

A számok 64 bites lebegőpontos formában (double) tárolódnak. Többféleképpen is
be lehet írni a programba szám literálokat, de a megadás módjától függetlenül
a tárolás mindig double.

    
    
        0xffff              // hexadecimális (mint C-ben)
        0b11111111          // bináris (255)
    
    

A számokra működnek a szokásos összehasonlító műveletek.

    
    
        x == y              // --> .t., ha egyenlőek
        x != y              // --> .t., ha eltérnek
        x <  y              // kisebb
        x <= y              // kisebbegyenlő
        x >  y              // nagyobb
        x >= y              // nagyobbegyenlő
    
    

Megvannak a szokásos aritmetikai operátorok.

    
    
        x +  y              // összeadás
        x -  y              // kivonás
        x *  y              // szorzás
        x /  y              // osztás
        x %  y              // moduló
        x ** y              // hatványozás
        ++x                 // növelés (mint C-ben)
        --x                 // csökkentés (mint C-ben)
        x++                 // növelés utólag (mint C-ben)
        x--                 // csökkentés utólag (mint C-ben)
    
    

A műveletek precedenciája ugyanaz, mint C-ben, és természetesen ugyanúgy
alkalmazható a zárójelezés.

A C-hez hasonlóan az aritmetikai operátoroknak van értékadással kombinált
változata:

    
    
        x += y              // x:=x+y (hozzáad)
        x -= y              // x:=x-y (levon)
        x *= y              // x:=x*y
        x /= y              // x:=x/y
        x %= y              // x:=x%y
    
    

Vannak számokon működő matematikai függvények: `power()`, `exp()`, `log()`,
`sqrt()`, trigonometrikus függvények, `round()`, `random()`.

Van néhány függvény bitek manipulálására: `isbit()`, `setbit()`, `clearbit()`,
`numand()`, `numor()`, `numxor()`, `numnot()`.

Az `str()` és `transform()` függvények számot karakter stringre konvertálnak.
A `val()` függvény a string elején álló decimális számból kiolvassa a
számértéket.

####  4.3.4.  Dátum

    
    
        set date format "yyyy-mm-dd"
        valtype(ctod("2009-11-20"))     // --> "D"  (nincs dátum literál)
        valtype(stod("20091120"))       // --> "D"
        empty(ctod(""))                 // --> .t.
        empty(date())                   // --> .f.
    
    

Dátumokat nem tudunk közvetlenül (literálként) beírni a programba, hanem a
`ctod()` vagy `stod()` konverziós függvénnyel állítjuk elő a string alakból.
(E függvényeknek az inverze is létezik: `dtoc()`, `dtos()`.)

A dátumkezelés 1900-tól 2100-ig működik jól. Ebben az időszakban helyesen
kezeli a szökőéveket.

A dátumokra értelemszerűen működnek az összehasonlító operátorok.

A dátumokon korlátozottan lehet aritmetikai műveleteket végezni. Az alábbi
példában `n` szám típusú, `d1` és `d2` dátum típusú:

    
    
        n  := d2 - d1   // --> a két dátum különbsége napokban
        d2 := d1 + n    // --> d1 dátum plusz n nap
        d2 := d1 - n    // --> d1 dátum minusz n nap
    
    

Van egy rakás dátumokon működő függvény: `doy()`, `eom()`, `eoy()`, `bom()`,
`boy()`, `day()`, `dow()`, `cdow()`, `month()`, `addmonth()`, `cmonth()`,
`year()`.

####  4.3.5.  Pointer

    
    
        valtype(p)      // --> "P"  (nincs pointer literál)
        empty(p)        // --> .t.  (csak a null pointer üres)
    
    

A pointereket interfészekben használjuk. Arra való, hogy C könyvtárak adatait
(tipikusan egy struktúrára mutató pointert) tároljunk benne Clipper szinten.
Példa: Az Oracle minden SQL utasításhoz rendel egy ún. statement handle-t
(pointer). A program erre a statement handle-re kell hivatkozzon, amikor
műveleteket akar végezni az SQL utasítással, pl. le akarja kérdezni egy select
eredménysorait. Egy ilyen statement handle tárolása oldható meg a P típusú
változóval.

####  4.3.6.  Karakter (Unicode string)

    
    
        valtype("Van, aki forrón szereti")  // --> "C"
        len("")                             // --> 0
        len("123")                          // --> 3
        empty("")                           // --> .t.
        empty("  ")                         // --> .t. (csak blank)
        empty("x")                          // --> .f.
    
    

Példák:

    
    
    local x:='ТЕРМИНЫ И УСЛОВИЯ КОПИРОВАНИЯ'
    local y:=@"Some like it hot"  //nlstext
    
    local text:=<<tetszoleges_symbol>>
        Itt tetszőleges (UTF-8 kódolású) szöveg lehet,
        idézőjelek, tab, soremelés, akármi,
        kivéve a kezdő <<tetsz...>> (nem írhatom oda) jelet,
        mert az lezárja a string literált.
    <<tetszoleges_symbol>> //lezárva
    
    

A karakterváltozók (stringek) Unicode karakterek sorozatát tartalmazzák. A
karakterváltozók tudják a saját hosszukat. Nincs lezáró 0, nincs vizsgálva a
karakterek érvényessége, ezért a karakterek között akármilyen kódérték
előfordulhat. A karakterváltozók hossza csak azért van korlátozva, hogy az
elszabadult programok ne fektessék ki a rendszert. Jelenleg egy karakterstring
maximális mérete 64MB.

A karakterliterálokat UTF-8 kódolással kell beírni. A fordító végzi el a
konverziót UTF-8-ról Unicode (`wchar_t`) tömbre. Ha az UTF-8 kódolás hibás, a
fordító INVALIDENCODING hibát ad.

A stringeket aposztróf vagy macskaköröm határolja. Aposztróffal határolt
string tartalmazhat macskakörmöt, és fordítva. A stringben nem lehet escape
szekvenciákkal trükközni.

Alapesetben a stringek egysorosak. Hosszabb stringeket részeiből összeadással
és folytatósorokkal lehet képezni.

A hosszabb (többsoros) stringek egyszerű beírását teszi lehetővé a
`<<SYMBOL>>` típusú határoló.

A `@"..."` alakú stringekből (nlstext) a fordító készít egy hash táblát,
amiben a string értéke a kulcs. A kulcsokhoz különféle nyelvű szövegeket
(fordításokat) lehet kapcsolni, amiket a program futás közben felszed, és
automatikusan behelyettesít, így ugyanaz a program különféle nyelveken
jelenhet meg.

Bárhogy is hoztuk létre a stringet, ugyanazokat a dolgokat lehet csinálni
vele.

Összehasonlítás:

    
    
        x == y      // egyenlő-e (ez az egy normális)
        x != y      // a jobboldal hosszában eltér-e
        x <= y      // a jobboldal hosszában! 
        x <  y      // a jobboldal hosszában! 
        x >= y      // a jobboldal hosszában! 
        x >  y      // a jobboldal hosszában! 
    
    

A stringek rendezése a Unicode kódértékek szerint lexikografikusan történik. A
`==` kivételével a többi összehasonlító operátor úgy működik, hogy először a
baloldalt levágja a jobboldal hosszára, és az így kapott x-szel végzi az
összehasonlítást, tehát:

    
    
        "abc" != "ab"   // --> .f.
        "ab"  != "abc"  // --> .t.
        "abc" >  "ab"   // --> .f.
        "abc" <= "ab"   // --> .t.
    
    

Sajnos ezek elég zavaró dolgok, de Clipper örökség, és a kompatibilitás
kényszere miatt nem lehet rajta változtatni.

Összeadás:

    
    
        y:="Some like "+"it hot"
        x:="Some like "
        x+="it hot"
        x==y  // --> .t.
    
    

Indexelés, szeletek:

    
    
        "Some like it hot"[1]       // --> "S", indexelhető, 1-től indul
        "Some like it hot"[2..4]    // --> "ome", szelet
        "Some like it hot"[11..]    // --> "it hot"
        "Some like it hot"[..11]    // --> "Some like i"
        "Some like it hot"[..]      // --> másolat az egészről
    
    

A túlindexelés runtime errort okoz. A szeletek túllógó indexei módosulnak a
tényleges méretekhez alkalmazkodva. Nincs trükközés, hátulról számolás, meg
effélék.

Részstring tartalmazás:

    
    
        "like" $ "Some like it hot" // --> .t.
    
    

A stringeken működő fontosabb függvények: `strtran()`, `stuff()`, `substr()`,
`left()`, `right()`, `padr()`, `padl()`, `ltrim()`, `rtrim()`, `alltrim()`,
`at()`, `rat()`, `len()`, `replicate()`, `upper()`, `lower()`, `isalpha()`,
`isdigit()`, `isalnum()`, `isupper()`, `islower()`.

`upper()`, `isupper()` és társaik értik a Unicodeot, ezért cirill betűs
stringre is jól működnek.

A `chr(code)` függvény visszaad egy egy hosszúságú stringet, ami a megadott
kódértékű (Unicode) karaktert tartalmazza. Az `asc(str)` függvény visszaadja a
bemeneti string első karakterének kódértékét.

A karakterstring értékekben közvetlenül tárolódó adat (ahogy korábban már szó
esett róla) egy OREF. Az `a:=b` értékadás után az `a` és `b` változó
közösködik az objektumreferencián. Ugyanaz az értékük, ráadásul a string csak
egy példányban létezik a memóriában. Mi történik, ha az egyik változót
módosítjuk?

    
    
        b+="próba szerencse"
    
    

Változik-e `b`-vel együtt az `a`-is? Nem, a változók útja szétválik. Lesz egy
külön memóriaobjektuma `a`-nak és egy másik a `b`-nek. Ez az értelme annak a
más nyelvek dokumentációiban olvasható, kissé rejtélyes kijelentésnek, hogy a
,,karakterstring (érték) nem módosítható".

####  4.3.7.  Binary (bájt string)

    
    
        valtype(a"Próba szerencse")     // --> "X"
        valtype(x"0d0a")                // --> "X" (CR/LF)
        len(a"")                        // --> 0
        len(a"123")                     // --> 3
        empty(a"")                      // --> .t.
        empty(a"  ")                    // --> .t. (csak blank)
        empty(a"x")                     // --> .f.
    
    

A binary változók (bájt stringek) bájtok sorozatát tartalmazzák. Tudják a
saját hosszukat. Nincs lezáró 0, ezért a bájtok között akármilyen érték
előfordulhat. A binary változók hossza csak azért van korlátozva, hogy az
elszabadult programok ne fektessék ki a rendszert. Jelenleg egy binary string
maximális mérete 64MB.

Legegyszerűbben az `a"..."` alakban írhatók be egy programba:

    
    
        x:=a"Van, aki 'forrón' szereti"
        y:=a'Van, aki "forrón" szereti'
    
    

A karakterliterálokhoz képest az a különbség, hogy most nincs UTF-8 -&gt;
Unicode konverzió, a tartalom nem karaktertömb, hanem bájttömb.

A stringeket aposztróf vagy macskaköröm határolja. Aposztróffal határolt
string tartalmazhat macskakörmöt, és fordítva. Nem értelmezünk semmilyen
escape szekvenciát.

Hexadecimális kódokkal is megadhatjuk a bájtsorozatot a `x"..."` formában.
Ennek kötelezően páros számú betűt kell tartalmaznia (minden bájt egy kétjegyű
hexa szám: 00-ff), a kis-nagybetű nem számít.

A binary változókra ugyanazok az operátorok és függvények működnek, mint a
karakterváltozókra, csak értelemszerűen karakterek helyett bájtokkal. Pl.
`asc()` most nem az első karakter, hanem az első bájt kódértékét adja. A
`bin(code)` függvény ad egy egyelemű bájtsorozatot, melyben az egyetlen elem
értéke a `code`.

    
    
        binvar:=str2bin(chrvar)
        chrvar:=bin2str(binvar)  //visszaadja az eredetit
    
    

Az `str2bin()` függvény a bemeneti karaktersorozatból előállít egy
bájtsorozatot, ami a stringet UTF-8 kódolásban ábrázolja.

A `bin2str()` függvény _feltételezi_, hogy a bemenete egy UTF-8 kódolású
szöveg, és UTF-8 -&gt; Unicode konverzióval előállítja a bájtsorozatnak
megfelelő karaktersorozatot. Ha a bemenet mégsem kifogástalan UTF-8 kódolású,
akkor a hibák helyén ? karakterek jelennek meg a kimeneten. Emiatt az str2bin
és bin2str nem egymás inverzei. Pl. egy png képet tartalmazó binary változót
nem lehet oda-vissza karakterre konvertálni, mert elromlik a kép.

A bájtsorozatok és karakterek között nincs automatikus konverzió, ezért pl.
nem lehet őket összeadni vagy összehasonlítani.

A karakterekhez hasonlóan a bájt string értékekben is a közvetlenül tárolódó
adat egy OREF. Ugyanolyan értelemben most is mondhatjuk, hogy (első
közelítésben) a bájt stringek nem módosíthatók. Igazából természetesen minden
módosítható. Van rá API, hogy a programok dogozhassanak a bufferen belül.

####  4.3.8.  Array

    
    
        valtype({1,"2",.f.,{}})     // --> "A"
        len({})                     // --> 0
        len(array(1000))            // --> 1000
        empty({})                   // --> .t.
        empty(array(1000))          // --> .f.
    
    

Az array (tömb) típus Clipper értékek sorozatát tartalmazza. A tömbelemek
típusa bármi lehet, bármilyen értéket tartalmazhat elemként, akár saját magát
is (ami persze végtelen rekurziót okoz a tömb kiprintelésekor).

    
    
        a:={}               // üres array
        {1,2,3,4}[3]        // --> 3, az indexek 1-től indulnak
        {1,2,3,4}[2..3]     // --> {2,3}, array szelet
        len({1,2,3,4})      // --> 4, tudja a saját hosszát
        array(10)           // NIL-ekkel inicializált, 10 elemű
        a[i]:=x             // értékadás egy tömbelemnek
        a[i][j]             // a i-edik elemének j-edik eleme
        aadd(a,x)           // a végéhez ad egy új elemet
        asize(a,len(a)+1)   // hossz növelése
    
    

A futtatórendszer minden indexelést ellenőriz, túlindexelés esetén runtime
error keletkezik.

A stringekhez hasonlóan alkalmazható a szeletelés, ami a tömb megadott
részéről sekély másolatot készít. A szeletekben túllógó indexek nem okoznak
runtime errort, hanem automatikusan alkalmazkodnak a tényleges méretekhez.

Az inicializálatlan tömbelemek értéke NIL.

A tömbökön használható fontosabb függvények: `array()`, `asize()`, `adel()`,
`aadd()`, `atail()`, `ascan()`, `asort()`.

Az array típusú értékekben a közvetlenül tárolt adat egy OREF. Az OREF-hez
tartozó memóriaobjektumban a tömbelemek szépen, katonásan egymás után
sorakoznak. A stringekre azt mondtuk, hogy nem változtathatók. A tömbök ezzel
szemben igen, a különbséget az alábbi példa szemlélteti.

    
    
        a:=array(10)
        b:=a
        b[5]:="HOPP"
        ? a[5]              // kiírja: HOPP
    
    

Láttuk, hogy a tömbök mérete változhat. Emiatt a futtatórendszer időnként az
egész tömböt kénytelen áthelyezni új memóriacímre.

####  4.3.9.  Kódblokk

    
    
        valtype({||NIL})    // --> "B"
        len({||x})          // --> 1    (ref változók száma)
        empty({||NIL})      // --> .f.  (sosem üres)
    
    

Amit más nyelvekben (Lisp, Python, Smalltalk,...) úgy hívnak, hogy closure
vagy lambda-függvény, az a Clipperben a kódblokk. Általános alakja:

    
    
        blk:={|p1,p2,...|expr1,expr2,...}
    
    

A `||` jelek között vannak felsorolva a kódblokk paraméterei (lehet üres).
Ezután kifejezések vesszővel elválasztott listája következik. A kifejezésekben
a kódblokk paraméterei, plusz a kódblokk definiálásának helyéről látható,
érvényes programelemek (literálok, változók, függvények) szerepelhetnek.

A kódblokk értelme, hogy ki lehet őt értékelni. Az előbbi `blk` változót
átadjuk az `eval` függvénynek:

    
    
        eval(blk,a1,a2,...)  // --> az utolsó kifejezés értéke
    
    

Az a1, a2, ... értékek behelyettesítődnek, a p1, p2, ... változókba, majd
kiértékelődnek az expr1,expr2,... kifejezések. Az utolsó kifejezés értéke lesz
az eval függvény visszatérési értéke.

A Clipper/CCC-ben nincs olyan, hogy függvénypointer. Ha a programban leírunk
egy függvénynevet zárójelpár (azaz függvényhívás operátor) nélkül, akkor az
szándékainkkal ellentétben nem a függvényt jelenti, hanem egy változónevet, és
hibát kapunk, ha az adott néven nincs változó deklarálva.

A kódblokkok legegyszerűbb alkalmazása függvények paraméterként való átadása.
Nézzünk egy összeadó függvényt:

    
    
    function osszead(a,b)
        return a+b
    
    

Ebből készítünk egy kódblokkot:

    
    
        blk:={|p1,p2|osszead(p1,p2)}
    
    

A blk változó értéke átkerül a program egy másik helyére, pl. visszatérési
értékként, vagy függvényparaméterként. Ezen a másik helyen így értékelhető ki:

    
    
        eval(blk,1,2) // --> 3
    
    

Rendkívül érdekes tulajdonsága a kódblokkoknak, hogy a blokk
kifejezéslistájában szerepelhetnek változók abból a láthatósági körből, ahol a
kódblokkot definiáltuk. A kódblokk révén ezek a változók láthatóvá válnak
olyan helyen, ahol egyébként normálisan nem volnának láthatók: Külső static
változó egy másik modulban, vagy belső változó egy másik függvényben. Úgy
szoktuk mondani, hogy a kódblokkba ,,belerefesednek" a változók (lásd a
referencia változókat).

    
    
    function main()
    local x,blk:={|p|x+=p}
    
        x:="a"
        ? proba1(blk)   //kiírja: a-proba1
        ? x             //kiírja: a-proba1
    
        x:="b"
        ? proba1(blk)   //kiírja: b-proba1
        ? x             //kiírja: b-proba1
        ?
        
    function proba1(blk)    
        return eval(blk,"-proba1")
    
    

Most van min tűnődni: Kétszer (ugyanúgy?) meghívtuk a `proba1` függvényt, ám a
két alkalommal más-más eredményt kaptunk. Ráadásul, hogyan változhat meg az
`x` értéke, ami a `main`-en belül lokális, és így máshol nem látható?

A kódblokk egy másik tulajdonságára világít rá a következő példa:

    
    
    function main()
    local blk:=proba1()
        ? eval(blk,"HOPP")  // kiírja "Próba szerencse:HOPP"
        ?
    
    function proba1()    
    local x:="Próba szerencse:"
        return {|p|x+p}
    
    

A nagy kérdés itt, hol tárolódik a "Próba szerencse:" érték? A kódblokk
kiértékelésekor (`main`-ben) a `proba1` már visszatért, tehát az `x` változó
már nem létezik. A válasz: az érték a kódblokkban tárolódik.

A kódblokkban közvetlenül tárolódó adatok:

  * kódpointer a kifejezéslistára (erre adja a vezérlést az `eval()`), 

  * OREF a kifejezéslistában szereplő változókból képzett tömbre. 

A kódblokkba kerülő változók referenciák. Ez azt jelenti, hogy az eredeti és a
kódblokkban tárolt példányok együtt változnak (ez a ,,belerefesedés").

A kódblokk a Clipper nagyon sokoldalúan használható eszköze. Többek között a
kódblokkokon alapul az objektum-metódusok implementációja.

####  4.3.10.  Objektum

Vannak ún. _objektum alapú_ nyelvek. Ezekben egy objektumot úgy képzelhetünk
el, mint egy hashtáblát. Az objektum-hashtáblában az attribútumok/metódusok
neve a kulcs. A hash a kulcs mellé az attribútum értékét, illetve a metódus
implementációját képviselő kódblokkot rendeli. A metódushívás a kódblokk
automatikus kiértékelésével történhet. Minden objektum egyedi, bármikor
bővíthető új attribútum/metódussal.

Ezzel az egyszerű megközelítéssel szemben a CCC-ben _osztályok_ vannak.
Objektumok helyett az osztályok leírására használunk hashtáblát. A hashben
most is az attribútumok/metódusok neve a kulcs, az attribútum kulcsokhoz
azonban most egy indexet rendelünk. Ennél az indexnél található meg az érték
az objektum attribútumai között. Maga az objektum csak az attribútumaiból áll.
A lényeg, hogy _megkülönböztetjük_, és elkülönítve tároljuk _az osztály- és
objektum-információt_.

    
    
        valtype(o:=errorNew())  // --> "O"
        len(o)                  // --> 14   (attribútumok száma)
        empty(o)                // --> .f.  (len(o)==0)
        o:classname             // --> "error"
    
    

Objektumokat nem operátorral gyártunk (nincs new operátor), hanem
objektumgyártó függvénnyel. Ezek nevét az osztály nevéből (a példában `error`)
és a `New` szóból rakjuk össze. Az xNew függvény visszatérési értéke az x
osztályú objektum. A régi Clipperben is ez volt a helyzet, az error
objektumokat az `errorNew()` függvény adta. A kompatibilitás érdekében
megtartottuk a sémát. Az objektumgyártó függvényt a fordító generálja az
osztálydefinícióból.

Az objektumok `valtype()` szerinti típusa osztályuktól függetlenül mindig O.

Minden osztály az `object` osztály leszármazottja, ezért mindnek van
`classname` metódusa, amivel lekérdezhető az osztály neve.

A futtatórendszer statikusan tárolja az osztályokra vonatkozó infót:

  * a leszármazási viszonyokat (többszörös öröklődés), 

  * az osztályok szerkezetét (milyen metódusai, attribútumai vannak egy osztálynak, mit honnan örökölt), 

  * az attribútum indexeket (melyik attribútum, hanyadik az attribútumok tömbjében), 

  * a metódusok kódját (a kód kódblokk formájában adatként tárolható). 

A fentiek tehát osztályadatok.

Az objektumokban tárolódó adatok:

  * osztály azonosító, 

  * OREF az objektum attribútumait tartalmazó tömbre. 

Ha a fordítóprogram az `obj:slot` kifejezéssel találkozik, akkor felismeri,
hogy attribútum kiértékelésről vagy metódushívásról van szó. Elkészíti a
megfelelő kódot, de nem vizsgálja `obj` típusát/osztályát, sem a `slot`
attribútum/metódus létezését.

Futásidőben a kifejezés kiértékelése többféle eredményre vezethet. Ha `obj`
típusa nem objektum, akkor azonnal runtime error keletkezik. A rendszer
megkeresi `obj` osztályában a `slot` kulcsot. Ha nem találja, akkor megintcsak
runtime error keletkezik. Ha a kulcsnál attribútum indexet talál, akkor
előveszi az attribútum értékét. Ha kódblokkot talál, akkor azt automatikusan
kiértékeli.

Talán már nem is kéne külön említeni, hogy a stringekkel szemben az objektumok
változékonyak (teljesen ugyanaz a helyzet, mint az array típusnál):

    
    
        e1:=errorNew()          // minden tag üres
        e2:=e1
        e2:description:="Próba szerencse"
        ? e1:description        // kiírja: "Próba szerencse"
    
    

Az osztálydefiníciókkal külön fejezetben fogunk részletesen foglalkozni.

####  4.3.11.  Referencia változók

Nézzük az alábbi példát:

    
    
    function main()
    local a:="A"
    local b:="B"
        felkialt(@a,b)
        ? a,b               // kiírja: A! B
        
    function felkialt(x,y)
        x+="!"
        y+="!"
        varstack()          // kiírja a stacket
        ? valtype(x)        // kiírja: C (x típusa)
        return NIL
    
    

Közönséges esetben a függvényhívás értékek átadásával történik. A hívó kód a
veremre rakja a paramétereket (a-t, aztán b-t) és meghívja a függvényt
(esetünkben felkialt-ot). A hívott függvény csinál, amit csinál, majd
rendbeteszi maga után a stacket. Az összes local változóját és paraméterét
leszedi a stackről. Ekkor a stacken az első üres hely ott van, ahol a függvény
első paramétere volt (esetünkben az x). Ezután ráteszi a stackre a
visszatérési értékét (esetünkben NIL-t), és visszatér.

Nade, akkor mitől változik meg az `a` változó értéke? A magyarázat, hogy a
tárgyalt eset nem ,,közönséges". Figyeljük meg a `felkialt(@a,b)`
függvényhívásban az `a` előtti `@` karaktert. Ennek hatására az `a` változó
_referenciává_ alakul.

A referencia változók az értéküket nem közvetlenül tartalmazzák. Amit
közvetlenül tartalmaznak, az egy VREF (VALUE referencia). Ez direkt azt a célt
szolgálja, hogy több változó közösködni tudjon egy értéken, és ennek az
értéknek a változásával a változók együtt változzanak.

Nézzük az előbbi példaprogram tényleges kiírásait:

    
    
    -----------------------------------------------------------
     Variable Stack
    -----------------------------------------------------------
    ***** function main
    0: REFSTRING length=2 oref=7fd95b61b058 "A!"
    1: STRING length=1 oref=7fd95b61b028 "B"
    ***** function felkialt
    2: REFSTRING length=2 oref=7fd95b61b058 "A!"
    3: STRING length=2 oref=7fd95b61b088 "B!"
    -----------------------------------------------------------
    C
    A! B
    
    

Gyönyörűen látszik, hogy `a` és `x` együtt változnak, míg `b` és `y` külön
életet élnek. (Honnan? `a` és `x` oref-je azonos, és a `main`-beli `a` már a
`felkialt` visszatérése előtt tartalmazza a ! jelet. `b` és `y` viszont külön
oref-fel rendelkeznek.)

Még egy kérdés: A `varstack` kiírása szerint `x` típusa REFSTRING, a
`valtype()` szerint viszont a típus C (közönséges karakter). Hogy is van ez?
Éppen ebben nyilvánul meg, hogy a futtatórendszer támogatja a referencia
változókat. Amikor úgy látja, hogy a változó (aminek az értékét elő kell
venni) referencia típusú, akkor nem a közvetlenül tárolt referenciát adja,
hanem ,,derefeli", azaz eggyel tovább nyúl, és a valódi értéket veszi elő.
Ezért a `valtype()` a ,,derefelt" értékkel hívódik meg.

Automatikusan kezeli a rendszer a referenciákat az értékadások mindkét
oldalán.

    
    
        refvar:=x
    
    

Az `x` változó (az értéket tartalmazó memóriaterület) nem `refvar`
memóriaterületére másolódik, hanem oda, ahová `refvar` hivatkozik. Ezért
`refvar` referencia típusa megmarad.

    
    
        x:=refvar
    
    

Hasonlóképp, `refvar` derefelt értéke íródik `x`-be, ezért az `x` változó nem
válik referenciává.

###  4.4.  Változótér

A következőkben egy gráfot fogunk vizsgálni.

Vegyük fel a csúcsok közé a program statikus változóinak tömbjét. A programban
nem találkozunk ilyen tömbbel, mégsem értelmetlen beszélni róla, ui. a
statikus változók szakasztott ugyanúgy tárolódnak, mint egy array: az értékek
szépen, katonásan egymás után sorakoznak a memóriában.

Vegyük fel a csúcsok közé a program stackjeit (vermeit). Hogyhogy több? Igen,
minden szál külön stackkel rendelkezik. Ezen tárolódnak a local változók, a
függvényparaméterek, a kifejezések részeredményei. Egy stacket is tekinthetünk
tömbnek, csak éppen a hossza változik, ahogy a stackpointer szuszog. (A
félreértések elkerülése végett: Nem a C program stackjéről van szó. A
futtatórendszernek saját stackje van, amire CCC értéket tesz a push, és CCC
értéket vesz le róla a pop.)

Vegyük fel a csúcsok közé mindazon memóriaobjektumokat, amiket a program
valaha létrehozott, és még nem szabadított fel: tömbök, objektumok,
kódblokkok, referencia változók, stringek.

A stringek kivételével az összes eset a tömbök mintájára tárgyalható. Az
objektumok esetében az attribútumok tömbjéről van szó. Kódblokkoknál a blokkba
refesedett változók alkotnak tömbszerű képződményt. A referencia változók
kicsit speciálisak, de ezeket is tekinhetjük egyelemű tömböknek, amiket a
futtatórendszer automatikusan indexel. Ezek a csúcsok tehát minden esetben
értéktömbök. Memóriaterület, amiben a korábban tárgyalt típusú _értékek_
helyezkednek el egymás után.

A string memóriaobjektumok viszont biztosan nem tartalmaznak _értékeket_,
hiszen tudjuk róluk, hogy csak bájtokat vagy Unicode karaktereket
tartalmaznak.

Látjuk tehát, hogy a csúcsaink egy részében értékek vannak, és ezek között
lehetnek referencia típusúak, amikben a közvetlenül tárolt adat egy OREF vagy
VREF. Vegyünk fel a gráfban irányított éleket, amik a referenciát tartalmazó
csúcsokból (memóriaobjektumokból) a hivatkozott memóriaobjektumokba
(csúcsokba) mutatnak.

Összefoglalva: A gráf csúcsai a program memóriaobjektumai, beleértve a
statikus változók tömbjét, a stackeket, a tömböket, objektumokat,
kódblokkokat, referencia változókat és stringeket. Az irányított élek
megfelelnek a hivatkozásoknak. Hivatkozik, értsd: olyan elemet tartalmaz, ami
nem közvetlenül tartalmazza az értékét, hanem egy memóriaobjektumban. A
stringek olyan csúcsok, amikből nem indul él. Az egyszerű típusok (szám,
dátum, logikai, pointer, NIL) a gráf szempontjából érdektelenek.

###  4.5.  Szemétgyűjtés

Sokadszor, újra nézzük meg az értékadást.

    
    
    local x:="Próba"+" "+"szerencse"
    
        //most van egy "Próba szerencse" tartalmú memóriaobjektum,
        //amire az x változó hivatkozik, következésképp a stackből 
        //(mint csúcsból) él mutat erre a memóriaobjektumra
    
        x:=NIL
    
        //az előbbi él törölve, mi lesz a memóriaobjektummal?
    
    

A fenti példa mutatja a ,,szemét" képződésének legegyszerűbb esetét. A
programból a továbbiakban már sehol sem látszik a `"Próba szerencse"` érték,
nincs mód hozzáférni, ha megint ugyanez az érték kell, akkor újra le kell
gyártani. Az ilyen elérhetetlenné (és így feleslegessé) vált memóriaobjektumok
megszüntetését nevezik szemétgyűjtésnek.

####  4.5.1.  Referencia számlálás

Az idők hajnalán a CCC-nek is volt referencia számlálással működő kísérleti
változata. Nem véletlenül. A referencia számlálás egyszerűnek látszik, ez az,
ami először eszébe jut a dilettáns programozónak.

A változótér minden csúcsában nyilvántartjuk a befutó élek számát. Az előbb
láttuk, hogy az éleket a legegyszerűbben az értékadó utasítások módosítják.
Egyes élek törlődnek, mások létrejönnek. Vannak más esetek is, amikor az élek
módosulnak. Akárhogy is, megtehetjük, hogy minden módosuláskor a befutó élek
számát (referenciaszám) aktualizáljuk. Amikor ez a szám nullára csökken, akkor
az adott memóriaobjektum törölhető. (Persze a stackeket sosem töröljük.)

Ezen az elven működik a Python szemétgyűjtése.

A referencia számlálás sajnos több sebből vérzik. Gondot okoznak a körök. A
változótérben lehetnek körök, nagyon egyszerű ilyet csinálni, pl.

    
    
    local a:={NIL}
        a[1]:=a         // ez itt egy hurok
    
    

A körben résztvevő csúcsok referenciaszáma sosem csökken nullára. Ez egy elvi
probléma.

Gyakorlati probléma, hogy nehézkes a referencia számlálós rendszerekben a
programozás. A referenciaszám karbantartása ui. az API részévé válik, és sok
esetben nem világos, hogy kinek a feladata a referenciaszámot módosítani, és
milyen időzítéssel kell azt végrehajtani.

Bár előnyei is lehetnek, a szakemberek körében a referenciaszámlálás
presztízse nem áll valami magasan, inkább más módszereket preferálnak. Sokan a
referenciaszámlálást nem is tekintik ,,igazi" szemétgyűjtésnek.

####  4.5.2.  Mark and sweep

Az igazi szemétgyűjtő algoritmusok legegyszerűbb változata a _mark and sweep_
algoritmus. A program időről időre (amikor fogytán van a memória, amikor éppen
ráér, amikor úgy gondolja, hogy már régen nem csinálta) beindítja a
szemétgyűjtést.

  * A _mark_ (=bejelöl) szakaszban a kezdő csúcsokból (esetünkben a static változókból és a stackekből) kiindulva bejárja a gráfot és útközben bejelöli, hogy mely csúcsokba (memóriaobjektumokba) jutott el. Ezek a program élő adatai. 

  * A _sweep_ (=kisöpör) szakaszban végigmegy az összes csúcson (memóriaobjektumon), és kitörli azokat, amiket a mark szakasz nem jelölt be élőnek. 

Ez van a CCC-ben, ennek is a legegyszerűbb magvalósítása. A szemétgyűjtés bele
van építve a futtatórendszerbe, ezért tudja, hogyan kell bejárni a gráfot, és
hogyan kell végigmenni az összes memóriaobjektumon. A memóriafoglalás és
felszabadítás a `malloc` és `free` (Windowson `GlobalAlloc` és `GlobalFree`)
függvényhívásokkal történik. Vagyis a memóriakezelés egyszerűen rá van
lőcsölve az operációs rendszerre.

Igen, mielőtt először kipróbáltam, én is aggódtam, nem fogja-e a primitív
memóriakezelés túlterhelni az operációs rendszert. Nem terheli túl. A
pentiumos korszaktól kezdve a CCC gyorsan és vidáman fut.

Egy átlagos CCC program memóriafoglalása nem kirívóan nagy. Miközben ezt a
szöveget írom, megnéztem a top-ban, mennyi a `z.exe` (CCC-ben írt editor)
memóriafoglalása. A legtöbb memóriát a `firefox-bin` foglalja (55M), a `z.exe`
(8M) a tizedik helyen áll, az `xfce4-menu-plugin` után és az `xterm` előtt.
Ugyanakkor van CCC program, amelyik egyszerre többmillió memóriaobjektummal
rendelkezik, és gigabájtnyi helyet foglal. Mindezt nem dicsekvésnek szánom,
csak annyit mondok, hogy a modern operációs rendszerek elég jól kezelik a
memóriát, nem érdemes azt alkalmazásszinten újraírni.

A mark and sweep algoritmusnak is vannak hátrányai. A szemétgyűjtés
kampányszerűen történik, ilyenkor a program minden más tevékenységet
felfüggeszt. Átlagos méretű programoknál a szünet tizedmásodpercekben mérhető,
amit interaktív használatban nem lehet észrevenni. A legnagyobb (többmillió
objektumos) programokban a szünet 2-3 másodperc. Mindenesetre lehetnek olyan
feladatok, robotvezérlés, effélék, ahol semmilyen szünet nem megengedhető,
ilyesmire a CCC nem alkalmas. (Egyébként a Jáva licencében is leírják, hogy
atomerőművek és repülőgépek vezérlésére nem jó.)

##  5.  Függvényhívás<a name="5"></a>

###  5.1.  Független modulok

Függvény és függvényhívás a Clipper/CCC legfontosabb építőkövei. Mielőtt
azonban a kövek részleteit vizsgálnánk, nézzünk az épület egészére.

Egy projekt általában sok forrásmodulból áll. A modulok neve legyen mondjuk

    
    
     
        code1.prg
        code2.prg
        ...
        code100.prg
    
    

A fordító ezeket egyesével lefordítja, és kapjuk a

    
    
     
        code1.obj
        code2.obj
        ...
        code100.obj
    
    

object (gépi kód) fájlokat. Lehet, hogy a prg források egy részével nem
találkozunk közvetlenül, mert egy másik projektben készülnek, és mi már csak a
lefordított objecteket kapjuk. Utóbbi esetben az a tipikus, hogy az objectek
nem külön-külön, hanem könyvtárakba (statikus lib, vagy dinamikus so)
összecsomagolva állnak rendelkezésre. Ez a helyzet a futtatórendszer
alapkönyvtáraival is, amit minden program használ. Akárhogy is, a lényeg, hogy
rendelkezésünk áll egy rakás object fájl. Ezekből lesz a program.

A _linker_ (link editor) feladata, hogy az egymástól függetlenül létrehozott,
egymásról mit sem tudó nagy rakás object fájlból futtatható programot
szerkesszen (linkeljen).

Tegyük fel, hogy a projektünk végterméke egy közvetlenül elindítható program
(nem pedig könyvtár). Akkor a modulok valamelyikében kell legyen `main`
függvény, ahol elindul a program. Mondjuk a `code1.prg`-ben.

    
    
     
    function main()
    local x,a,b,c
        ...
        x:=fuggveny1(a,b,c)
        ...
    
    

Program nem létezhet függvényhívás nélkül. Már a `main`-re is függvényhívással
kerül a vezérlés a futtatórendszer alapkönyvtárából. A main aztán meghívhat
további függvényeket, mint a példában `fuggveny1`-et, aminek a belsejében
további függvényhívás lehet, és így tovább.

    
    
     
    function fuggveny1(a,b,c,d)
        ...
        fuggveny2()
        ...
    
    

A körnek végül záródnia kell, az összes meghívott függvény kódja meg kell
legyen valahol az összeszerkesztett modulokban: az alapkönyvtárakban, plusz a
`code1.obj`... modulokban.

Az előbb ,,egymásról mit sem tudó" modulokról beszéltünk. Ez azt jelenti, hogy
a fordítóprogram semmit (a nevükön kívül semmi egyedit) nem tud a
függvényekről. A fordítóprogram a `fuggveny1` fordításakor látja, hogy kódot
kell generálnia a `fuggveny2` meghívására. Miközben ezt megteszi nem tudja,
hogy a `fuggveny2` hol van definiálva, definiálva van-e egyáltalán, milyen
paraméterezéssel kell meghívni, milyen visszatérési értéket ad.

Persze nem tudnánk értelmes programot írni, ha nem volnánk tisztában a
függvények paraméterezésével, visszatérési értékével, de ezt nem a fordító
tudja, hanem a programozó. A dokumentációból vagy a forrásprogram
elolvasásából. A fordítóprogram szempontjából minden függvényhívás ugyanolyan,
mindegyik ugyanarra a kaptafára húzható.

C-ből nézve minden Clipper függvény

    
    
    extern void _clp_fuggveny1(int argno); //C++ kód
    
    

deklarációval rendelkezik, azaz C szinten nincs visszatérési értéke (void), és
egyetlen int paramétere van, ami megmondja, hány paramétert kapott Clipper
szinten. Clipper szinten minden függvénynek van visszatérési értéke, ha más
nincs megadva, akkor NIL.

Ha a Clipper/CCC programozó kap egy bináris object fájlt (vagy lib/so
könyvtárat) és tudja, hogy mi a fájl tartalma, akkor minden további nélkül
belinkelheti a programjába, használhatja. A C programozók számára ez merőben
szokatlan. C/C++-ban egy könyvtár használatához múlhatatlan szükség van az ún.
header fájlokra (forrás típusú fájlok), amik segítik a fordítót a
kódgenerálásban és a függvényhívások ellenőrzésében.

A gyakorlatban a változók, függvények, objectek, könyvtárak (egymásra épülő,
egymást feltételező) uniform mivolta azt eredményezi, hogy egymástól
függetlenül fordított modulok, könyvtárak összelapátolásával rendkívüli
termelékenységgel hozhatunk létre óriási programokat.

###  5.2.  Láthatóság

Eddig csak globális láthatóságú függvényekről beszéltünk. Természetesen nem
szerencsés, ha egy belső használatra szánt függvény mindenhonnan látszik, és
ki van téve a tervezettől eltérő használatnak vagy akár csak véletlen
névütközésnek. A függvényeinket forrásmodulon belül eldughatjuk `static`
definícióval:

    
    
    static function fuggveny1()
        ...
    
    

Egy static függvény csak abban a forrásmodulban látható, amiben definiálták.
Clipper/CCC-ben és C-ben a `static` szó ugyanazt jelenti, változó
deklarációban és függvény definícióban egyaránt. A static függvények C-ben is
static-ok:

    
    
    static void _clp_fuggveny1(int argno); //C++ kód
    
    

###  5.3.  Függvényhívás a veremgépen

Most megnézzük a részleteket, hogyan valósul meg a ,,uniform" függvényhívás a
CCC veremgépén.

    
    
    local x,a,b,c,d
        ...
        x:=fuggveny1(a,b,c)
        fuggveny1()
        fuggveny1(,,c,d)       //ua. mint fuggveny1(NIL,NIL,c,d)
        ...
    
    

A függvényeket akárhány darab és akármilyen típusú paraméterrel meg lehet
hívni. A függvény mindig ad visszatérési értéket, amit viszont nem kötelező
felhasználni. A fenti programrészlet talán furcsának látszik, de formailag
hibátlan. Hogy jó-e, az csak futáskor dől el. Lehetséges, hogy `fuggveny1` úgy
van megírva, hogy megvizsgálja a paramétereit, és a konkrét esettől függően
csinál ezt vagy azt.

Nézzük a dolgokat a hívott függvényből.

    
    
    function fuggveny1(a,b,c)
    local x:=0
        x+=if(a==NIL,0,a)       //NIL helyett 0
        x+=if(b==NIL,0,b)
        x+=if(c==NIL,0,c)
        return x
    
    

Itt egy példa `fuggveny1` viszonylag értelmes implementációjára. Akkor működik
jól, ha NIL vagy szám típusú paramétereket kap. Összeadja a paraméterek
számértékét (a NIL-ek helyett nullát vesz), és visszaadja az összeget.

Ha egy paraméter nincs megadva, annak a futtatórendszer NIL értéket ad. Nincs
megadva: a paraméterlista rövid vagy hézagos. A NIL értékeket a példaprogram
nullával helyettesíti.

Ha a paraméterlista hosszabb 3-nál, akkor a fölös paramétereket a
futtatórendszer eldobja. Az előző példában `d` mintha ott se lenne.

Ha a paraméterek között valamilyen más típus van, pl. logikai, az valamelyik
összeadásban fog kiderülni. A program ,,elszáll", és egyúttal kiírja, hogy
melyik sorban milyen értékeket nem lehetett összeadni, valamint kiírja az
egész stacket. Ilyen a CCC hibakezelése.

Ha már a stacknél tartunk, egészítsük ki a példaprogramot, és nézzük meg a
stacket:

    
    
    function main()
    local x,a:=1,b:=2,c:=10,d:="d"
        x:=fuggveny1(a,b+b)
    
    function fuggveny1(a,b,c)
    local x:=0
        x+=if(a==NIL,0,a)
        x+=if(b==NIL,0,b)
        x+=if(c==NIL,0,c)
        varstack()
        return x
    
    

A `varstack()` a futtatórendszer beépített függvénye, kiírja a program összes
static (most egy sincs) és local változóját.

    
    
    -----------------------------------------------------------
     Variable Stack
    -----------------------------------------------------------
    ***** function main
    0: NIL
    1: NUMBER 1
    2: NUMBER 2
    3: NUMBER 10
    4: STRING length=1 oref=b79b6008 "d"
    ***** function fuggveny1
    5: NUMBER 1
    6: NUMBER 4
    7: NIL
    8: NUMBER 5
    -----------------------------------------------------------
    
    

A rendszer tudja, hogy a stacken hol vannak a függvényhívási határok. Azt
remélem, az olvasó bonyolult magyarázat nélkül is azonnal érti, amit lát. A
`fuggveny1` szintjét nézve vegyük át, hogyan zajlik le a függvényhívás,
végrehajtás, visszatérés.

A hívó program sorban egymás után a stackre rakja a paramétereket. Egy
paraméter akármilyen bonyolult kifejezés lehet, szépen kiszámolódik, a
végeredmény (a kifejezés értéke) a stack tetején marad. Az 5-ös és 6-os stack
elemek a paraméterek.

Meghívódik `fuggveny1`. Meg van mondva neki, hogy 2 darab paramétert kapott. A
stack állásából és a kapott paraméterek számából tudja, hogy a saját szintje
az 5-ös elemtől kezdődik, egyúttal megvan a paraméterek értéke. Azokat az
argumentum változókat, amikre nem jutott paraméter, NIL-re inicializálja. Így
kerül `c` értekeként NIL a 7-es stack elembe. Az esetleges fölös paramétereket
(most nincs ilyen) kipucolja.

A `fuggveny1` további helyeket foglal magának a stacken a local változók
számára (amiket inicializál is, bár ez most nem látszik). A 8-as stack elemben
tárolódik az `x` változó.

A hívott függvény elvégzi, amit kell. Eközben a stack ,,szuszog".
Részeredmények tárolódnak rajta, mélyül majd visszacsökken a függvényhívások
szintje.

Elérkezik a visszatérés ideje. `fuggveny1` az 5-ös elem helyére beírja a
visszatérési értékét, majd beállítja a stackpointert, hogy a stack első szabad
helyeként a 6-os elemet mutassa. Visszatér.

A hívó program szempontjából a függvényhívás egy _kifejezés_ volt. Minden
kifejezés úgy működik, hogy ,,kiszámolja magát", és az értékét a stack tetején
hagyja. Esetünkben a kifejezés értéke a visszatérési érték. Ezzel azt csinál a
hívó program, amit akar. Ha semmit sem csinál, akkor az érték automatikusan
lekerül a stackről, és elvész.

###  5.4.  Referencia paraméterek

Más nyelvekről szóló dokumentációkban találhatunk ilyen kijelentést: ,,A
paraméterátadás érték szerint történik". Ez van a Clipper/CCC-ben is.

Írjuk át az előző példaprogramot.

    
    
    function fuggveny1(a,b,c)
        if( a==NIL )
            a:=0
        end
        ...
        return a+b+c
    
    

Így `fuggveny1` működése ugyanaz marad. Felvetődik viszont a kérdés: Az `a:=0`
értékadás miatt nem fordul-e elő, hogy az `a` változó értéke a hívó programban
is megváltozik? Nem. Aki figyelmesen olvasta az előző pontot, és követte, mi
történik a vermen, annak ez nyilvánvaló.

Bonyolultabb a referenciát tartalmazó típusok esete. String, array, objektum,
kódblokk esetén is érték szerint történik a paraméterátadás, csakhogy ilyenkor
az értékben közvetlenül tárolt adat egy OREF (memóriaobjektum referencia).
Emiatt a hívó és hívott program ,,közösködik" ugyanazon a tartalmon.

Stringek esetében ez a közösködés readonly, csak addig tart, amíg a hívott
program nem akar változtatni a stringen. Amikor változtat, a hívó és hívott
program változóinak tartalma szétválik.

Array, objektum, kódblokk esetén a hívott program megváltoztathatja a
memóriaobjektum _belsejét_ (array esetén az array hosszát is).

Az eddigi ,,normál", és magától értetődő eseteken túl előfordul, hogy
kifejezetten arra van szükség, hogy a hívott függvényben végrehajtott
változtatás a hívó program változójára is hasson. Ezt szolgálja a referencia
szerinti paraméterátadás.

    
    
    function main()
    local x,a,b:=2,c:=10,d:="d"     // a==NIL
        x:=fuggveny1(@a,b+b)        // @a referencia
        ? a                         // kiírja: 0
    
    function fuggveny1(a,b,c)
        if( a==NIL )
            a:=0
        end
        ? valtype(a)                // kiírja: N
        ...
        return a+b+c
    
    

Most az `a` változók `main`-ben és `fuggveny1`-ben együtt változnak. A `@a`
paraméterátadás hatására az eredetileg NIL típusú változó referenciává alakul,
és ez a referencia adódik át a hívott függvénynek. A referencia típusú
változók kiolvasását/értékadását a futtatórendszer speciálisan támogatja:
Automatikusan eggyel ,,tovább nyúl" a tényleges értékért anélkül, hogy ezt a
programban jelölni kellene. Úgy képzelhetjük el, mint egy egy hosszúságú
tömböt, aminek az indexelését a rendszer automatikusan elvégzi.

Külön említendő, hogy a hívott program _nem tudja_, hogy az argumentumai
referenciák-e vagy sem. Nem tudja? Mit mond róla a `valtype()`? Amikor
`valtype(a)` meghívódik, akkor is működik a referencia típusok speciális
támogatása, azaz a rendszer eggyel tovább nyúlva előveszi `a` tényleges
tartalmát, ezért `valtype()` úgy látja, hogy a kérdéses típus szám.

Eddig tartott a régi Clipper tudománya. Az eddig tárgyalt dolgokban CCC és
Clipper között tökéletesnek mondható a kompatibilitás. A következők már a CCC
újításai.

###  5.5.  Default értékek

A kényelmesebb programírás érdekében a függvénydefinícióban default értéket
adhatunk az argumentum változóknak. Még mindig az előző példánál maradva, ezt
is írhatjuk:

    
    
    function fuggveny1(a:=0,b:=0,c:=0)
        return a+b+c
    
    

Általánosságban

    
    
    function fuggveny(...,a:=expr,...)
        ...
    
    

pontosan ugyanazt jelenti, mint

    
    
    function fuggveny(...,a,...)
        if( a==NIL )
            a:=expr
        end
        ...
    
    

ahol `expr` tetszőleges olyan kifejezés, amit az adott helyen ki lehet
értékelni.

###  5.6.  Változó számú paraméter

    
    
    function fuggveny1(a,b,c)
        ...
    
    

Ez a függvény legfeljebb 3 darab paramétert tud átvenni. Ha kevesebbet kap,
akkor NIL-re inicializálja a paraméter nélkül maradt argumentum változókat, ha
többet kap, akkor a fölös paramétereket (esetünkben a 3 felettieket) kipucolja
(mintha nem is lettek volna).

Olyan függvényre is szükség van, ami előre nem ismert számú paramétert vesz
át.

    
    
    function fuggveny1(a,b,c,*)
        ...
    
    

Az _utolsó_ argumentum változó helyén szereplő `*` azt jelöli, hogy a
függvény akárhány (további) paramétert átvesz.

Minden korábbi szabály érvényes, kivéve, hogy nincsenek ,,kipucolódó"
paraméterek. Nem tudjuk, hogy a hívó küldött-e akár csak 1 darab paramétert.
Ha igen, akkor az első, második, harmadik paraméter behelyettesítődik az
`a`,`b`,`c` argumentum változókba. Ha nem, akkor a rendszer NIL-re
inicializálja a paraméter nélkül maradtakat. A hívott program a kapott
paraméterek számát 3-nál nagyobbegyenlőnek fogja látni.

Nem szükséges, hogy legyenek névvel ellátott argumentum változók.

    
    
    function fuggveny1(*)
        ...
    
    

Ez a változat egyszerűen minden paramétert átvesz.

No jó, ez a dolog egyik oldala, de hogyan férünk hozzá az ,,átvett", de
változóhoz esetleg nem rendelt értékekhez? Az alábbi kifejezésekben

    
    
        {*}                 // array az összes paraméterből
        fuggveny2(*)        // függvényhívás
        object:method(*)    // metódushívás
    
    

a `*` helyére behelyettesítődik a függvény összes paramétere. Elsőre talán
furcsa, de a helyzet világos lesz a következő összehasonlítás után.

    
    
    function fuggveny1(a,b,c)
    local array1:={a,b,c}
    local array2:={*}
    local array3:={*,1,*}   // {a,b,c,1,a,b,c}
        ...
        fuggveny2(a,b,c)
        fuggveny2(*)        // ugyanaz
    
    

Hogyan készül az `array1` tömb? A rendszer a stackre rakja az `a`, `b`, `c`
változók értékét, majd meghívja a veremgép egy primitívjét, hogy a stack
tetején levő három elemből készítsen tömböt. Ez a primitív leveszi a három
elemet, elkészíti a tömböt, és az eredményt a stack tetején hagyja. Na,
pontosan ugyanígy készül `array2` is, az egyetlen különbség, hogy az elemek
konkrét felsorolása helyett csak annyit mondtunk: az összes paraméter. Ezzel
meg is vagyunk. `len({*})` megadja az összes paraméter számát (jelen esetben
fix 3), `{*}[n]` megadja az `n`-edik paraméter értékét (a túlindexelés hiba).

Külön szólni kell a kódblokkokról.

    
    
    local blk1:={|p1,*|...}
    local blk2:={|*|fuggvény(*)}
    
    

A `||` jeleken belüli `*` a függvényekhez hasonlóan azt jelenti, hogy a
kérdéses kódblokk minden paramétert átvesz. Itt is rendelhetünk
argumentumváltozót az elől álló paraméterekhez. A kódblokk kifejezéslistájában
szereplő (tehát a `||` jeleken kívüli) `*` az összes kódblokk paraméter
felsorolását jelenti.

A `*` (nem kifejezés, csak) jelölés minden olyan kifejezésben működik, ahol
értelme van a paraméterek felsorolásának. Nézzünk néhány fontosabb esetet.

    
    
    function fuggveny1(*)
        return fuggveny2(*)
    
    

Itt `fuggveny1` továbbítja a hívást `fuggveny2`-nek, anélkül, hogy bármit
tudna annak paraméterezéséről. A `*` felsorolás függvény- és metódushívásban a
referencia változók referencia tulajdonságát megtartja, ezzel szemben a `{*}`
kifejezésben a referenciák derefelődnek.

    
    
        {|*|fuggveny(*)}
    
    

A fenti kódblokk meghív egy függvényt továbbítva neki a blokk összes
paraméterét.

A paraméterek felsorolásának vannak további esetei:

    
    
        *[x1..x2]  // paraméterek x1-től x2-ig
        *[x1..]    // paraméterek x1-től (ameddig van)
        *[..x2]    // paraméterek x2-ig (1-től)
        *[..]      // összes paraméter (*)
    
    

A szintaktika a string szeletekhez hasonló. A túllógó indexek módosulnak a
tényleges méretekhez alkalmazkodva. Magyarázat helyett néhány példa:

    
    
    function fuggveny1(a,b,c)
    local array1:={a,b,c}
    local array2:={*[..]}    // ua. mint array1 vagy {*}
    local array3:={b,c}
    local array4:={*[2..3]}  // ua. mint array3
    
    

A függvényhívás továbbítás (esetleg kódblokkon keresztül) fontos szerepet kap
a metódushívások implementációjában.

###  5.7.  Névterek

Korszerű programnyelv nem nélkülözheti a névtereket. A forrásmodulok legelején
állhat az opcionális `namespace` utasítás, például:

    
    
    namespace aa.bb.cc
    
    

aminek hatására a modulban definiált összes függvény az `aa.bb.cc`
(többszintű) névtérbe kerül. A `namespace` utasítás nélkül, egyedileg is
névtérbe helyezhetünk függvénydefiníciókat a következő módon:

    
    
    function  aa.bb.cc.f()
        ...
    
    

A kétféle (globális és egyedi) minősítés (névtérbe helyezés) egyszerre is
jelen lehet, ebben az esetben a hatásuk összegződik. A modulon belül definiált
függvények meghívásakor nincs szükség teljes minősítésre.

A modul függvényeire (pl. `f`-re) kívülről a _minősített_ névvel, esetünkben
az `aa.bb.cc.f()` formával hivatkozhatunk. A kívülről történő hivatkozások
megkönnyítésére szolgál a `using` utasítás. A `using` utasítások a modul
elején, közvetlenül az esetleges `namespace` után állhatnak. A `using` olyan
rövidítést vezet be, amivel elkerülhető a teljesen minősített függvénynevek
túl sokszori kiírása.

    
    
    // alternatív using-ok               így hívjuk meg f-et
    
       using aa.bb.cc=alias           // alias.f()
       using aa.bb=x                  // x.cc.f()
       using aa.bb.cc  f g            // f(), g()
       using aa.bb  cc.f              // cc.f()
    
    

A globális (gyökér) névteret (kezdő) pont jelöli. Ha pl. a `using aa.bb.cc  f`
utasítás után `aa.bb.cc.f` helyett a globális névtérben definiált `f`-et
akarjuk meghívni, akkor ezt kell irni: `.f()`.

A CCC névterek közvetlenül C++ névterekre vannak leképezve.

###  5.8.  Postfix függvényhívás

Nézzük ezt a kifejezést:

    
    
        padl(alltrim(str(round(x,2))),10,"0")
    
    

  * Az `x` változóban egy szám van, 

  * azt kerekítjük 2 tizedes jegyre, 

  * a számértéket karakter stringre konvertáljuk, 

  * levágjuk az elől/hátul esetleg rajta levő szóközöket, 

  * balról kiegészítjük "0" karakterekkel 10 szélességűre. 

Rengetegszer kell hasonló kifejezésekkel küszködni. Az a baj, hogy a
sorozatosan egymásba ágyazott függvényhívásokat középről (az `x` változóból)
kifelé haladva, hol balról, hol jobbról kell írni. Egy ilyet visszafejteni
végképp fárasztó.

Adódik a postfix függvényhívás ötlete. Értelmezzük a `::` (dupla kettőspont)
operátort a következőképp:

    
    
        x::fuggveny1()  // ua. mint fuggveny1(x) 
    
    

A postfix jelző arra utal, hogy a függvénynevet nem előre, hanem hátra, az
első argumentum után írjuk.

Nyilvánvaló, hogy a nyelv ,,tudása" nem változik a postfix függvényhívás
bevezetésével, csak a programírás kényelme növekszik. A hagyományos (prefix)
és a postfix függvényhívásból pontosan ugyanaz a kód generálódik.

Hogy igazán használható legyen, még egy-két általánosított formára szükség
van.

    
    
        x::fuggveny1        // üres zárójelpár elhagyva
        (x+y)::fuggveny1    // ua. mint fuggveny1(x+y)  
        x::fuggveny1(y,z)   // ua. mint fuggveny1(x,y,z) 
    
    

Megállapodunk abban, hogy a `::` oprátor precedenciája magas, ugyanolyan, mint
a metódushívás operátoré.

Az előző kifejezésünket most így írhatjuk.

    
    
        x::round(2)::str::alltrim::padl(10,"0")
    
    

Itt akár meg is állhatnánk, ha nem ismernénk a `+=`, `-=` (hozzáadó, stb.)
típusú operátorokat. Ezek mintájára kézenfekvő bevezetni a `::=` operátort a
következő értelmezéssel:

    
    
        x::=fuggveny1()     // ua. mint x:=fuggveny1(x) 
    
    

az összes variációjával együtt. Megállapodunk abban, hogy a `::=` operátor
precedenciája alacsony, ugyanolyan, mint a `:=`, `+=` (értékadás, stb.)
operátoroké.

Ha egyszer van egy alacsony precedenciájú értékadó operátorunk, felvetődik a
kérdés, van-e értelme zárójelezni a jobboldalon álló kifejezést. Itt egy
példa, ami mutatja, hogy van:

    
    
        ? x:="1"                        // kiírja: 1 (karakter)
        ? x::=(val()+1)::str::alltrim   // kiírja: 2 (karakter)
        ? x::=(val()+1)::str::alltrim   // kiírja: 3 (karakter)
        ? x::=val+1                     // kiírja: 4 (szám)
    
    

Amikor a függvényhívás operátort (`::=` vagy `::`) nem egy egyszerű
függvénynév követi, hanem egy zárójeles kifejezés, azt még mindig
értelmezhetjük függvényhívásnak, ha a zárójeles kifejezés nyelvtani
elemzőfájának bal szélén függvényhívás van. A gyakorlatban ritkán fordul elő
ez az eset, inkább csak azért foglalkozunk vele, hogy ne maradjon elvarratlan
szál a nyelvtanban.

A nyelvtani elemző onnan ismer fel egy függvényhívást, hogy

  * egy szimbólumot zárójelpár között felsorolt (esetleg üres) kifejezéslista követ (ez a hagyományos eset), vagy 

  * függvényhívás operátort egy szimbólum követ (postfix eset). 

Amikor a függvényhívás operátort nem közvetlenül követi a függvénynév (mint
ahogy a példában egy balzárójel ékelődik `::=` és `val` közé), akkor az üres
zárójelpárt nem lehet elhagyni.

##  6.  Objektumok<a name="6"></a>

###  6.1.  Alapok

Az alábbi példában majdnem minden együtt van.

    
    
    class derived(base1,base2)
    
        attrib  a1
        attrib  a2
    
        method  m1              {|this,p1,p2|expr(this,p1,p2)}
        method  m2              {|*|derived.m2(*)}
        method  m3
        method  m4              {|this,*|this:a2:m(*[2..])}
        method  m5              :a2:m
    
        method  initialize
    
    static function derived.m2(this)
        ...
    
    static function derived.m3(this,a,b,c)
        ...
    
    static function derived.initialize(this,a,b,c)
        this:(base1)initialize(a,b,c)
        this:(base2)initialize(a,b,c)
        ...
        return this  //kötelező visszaadni a this-t
    
    

A `class` kulcsszóval induló osztálydefiníciók a forrásban ugyanott állhatnak,
ahol a függvények. Az osztálydefiníció a következő `class`-ig, `function`-ig
vagy a fájl végéig tart.

A példa egy `derived` nevű osztályt definiál, ami a `base1` és `base2`
osztályokból van származtatva. Mindig meg kell adni legalább egy alaposztályt,
amiből az új osztály örököl, ha mást nem, akkor a mindig létező `object`
osztályt.

Az osztálydefiníció eredménye két függvény: `derivedClass()` és
`derivedNew()`, általában az x nevű osztály esetén xClass és xNew. A
programban e két függvény képviseli az osztályt.

    
    
        classid:=derivedClass()
    
    

`derivedClass()` visszatérési értéke az osztályazonosító. Maga az osztály a
`derivedClass()` függvény első hívásakor jön létre. A `base1` és `base2`
osztályoknak is megvan a maguk class függvénye, amik `derivedClass()`-ból
meghívódnak, és amik szintén meghívják az ősosztályuk class függvényét, stb..

A `derivedNew()` függvénnyel példányosítjuk az osztályt.

    
    
        object:=derivedNew(p1,p2,p3)  //derived osztályú objektum
    
    

A `derivedNew()` előállít egy `derived` osztályú objektumot, amihez szüksége
van a `classid`-re, meghívja tehát `derivedClass()`-t. Ha még nem létezett,
akkor ennek hatására minden szükséges osztály létrejön az `object` osztályig
bezárólag. A new függvény automatikusan végrehajtja az új objektum
`initialize` metódusát, továbbadva neki minden paraméterét.

A `derived` osztály rendelkezik a `base1` és `base2`-ből örökölt minden
attribútummal és metódussal, plusz a `derived` osztályban definiált
`a1`...,`m1`... attribútumokkal és metódusokkal.

A objektum felhasználója így hivatkozhat az attribútumokra és metódusokra:

    
    
        object:a1           // attribútum kiolvasás
        object:a1:=x        // attribútum értékadás
        object:a1++         // értékadás minden variációban
        object:a1+=1
        object:m1(x,y)      // metódushívás
    
    

A `class`-ban kizárólag attribútum és metódus definíciók állhatnak. A
sorrendjük lényegtelen.

Az attribútumoknak egyszerűen megadjuk a nevét az `attrib` kulcsszó után.

A `method` utasítások ennél bonyolultabbak. Alapesetben a metódus neve után
egy kódblokk van, ez a kódblokk jelenti a metódus implementációját. A
metódushívás a kódblokk kiértékelésével történik. Nézzük részleteiben. A
rendszer megállapítja, hogy `object` osztálya `derived`. Az osztályok
nyilvántartásából előszedi a `derived` osztály `m1` metódusához rendelt
kódblokkot. Ezt kiértékeli úgy, hogy a blokk első (`this`) paraméterébe
helyettesítődik maga az objektum, a `p1`-be `x`, `p2`-be `y`. A metódus
visszatérési értéke a kódblokk utolsó kifejezésének - esetünkben
`expr(this,p1,p2)` \- értéke.

A példában szereplő `this` nem kulcsszó, csak konvenció, akármilyen szimbólum
megfelelne. Szabály viszont, hogy mindig a kódblokk első paraméterébe kerül az
objektum (this, self, ki hogyan szereti).

Aha, ezek szerint az `m2` metódus implementációja a `derived.m2` függvény. A
metódus kódblokkja minden paramétert továbbít a benne meghívott függvénynek,
és mint tudjuk, az első paraméter a `this`.

Az `m3` metódus sorában a kódblokk helyén semmi sincs. Ilyenkor a fordító úgy
jár el, mint az előző esetben, odateszi (odaérti) az

    
    
        {|*|osztalyneve.metodusneve(*)}
    
    

default kódblokkot, ami minden paraméter továbbadásával meghívja az osztály
nevével minősített, a metódus nevével egyező nevű függvényt.

Ezt a függvényt valahol implementálnunk kell. Ha a függvényt `static`-nak
definiáljuk, akkor az a modulon kívülről függvényhívással nem érhető el, csak
az objektumon keresztül metódushívással. Ha a metódus implementációt
(kényszerűségből) más modulba tesszük, akkor nem lehet `static`, de legalább a
névtér csökkenti a véletlen névütközés lehetőségét.

A függvénynek mindig van legalább egy paramétere, hiszen az első helyen
megkapja a `this`-t. Ezt ugyanúgy ki kell írni, mint minden más normális
paramétert. (Nincs olyan bosszantó kétértelműség, mint amit C++-ban a ki nem
írt this okoz).

Az `m4` metódus kódblokkja kicsit bonyolultabb. Feltételezzük, hogy az
objektum `a2` attribútuma egy beágyazott objektumot tartalmaz, méghozzá olyat,
aminek van `m` nevű metódusa. A kódblokk az `m4` metódushívást (minden
paraméter továbbadásával) továbbítja a beágyazott objektum `m` metódusának. Ha
nem érthető, akkor az olvasónak újra át kell néznie a változó számú
paraméterrel történő függvényhívást.

Az `m5` megint új eset? Nem egészen. Ez csak az `m4` kódblokk rövidített
írásmódja. A metódushívás-továbbítás olvashatóbb formája.

Az objektumokat általában inicializáljuk. Egy tipikus lehetőséget mutat be a
példában szereplő `initialize` metódus. Mindez azonban nem szabály. Az
alkalmazás konkrét körülményeiből adódik, hogy mikor milyen inicializálásra
van szükség. A

    
    
        this:(base1)initialize(a,b,c)
    
    

sor a (`derived` osztályú) `this` objektumra meghívja a `base1` osztályban
definiált `initialize` metódust. Ez általában lehetséges, hiszen a leszármazás
miatt `this` egyúttal `base1` osztályú is. A speciális jelölést nevezzük
metódus cast-nak.

Az inicializátornak kötelezően vissza kell adnia az objektumot (a `this`-t).

Megjegyzendő, hogy minden objektumnak van `initialize` metódusa. Ha a saját
osztályában nincs definiálva, akkor örökli valamelyik felmenőjétől, ha
máshonnan nem, akkor az `object` osztálytól. Az `object` osztály
inicializátora egyébként nem csinál semmit, minthogy az `object`-ben nincs
definiálva egyetlen attribútum sem.

Álljunk meg ezen a ponton egy kis összegzésre. Azt szeretném hangsúlyozni,
hogy az eddigiek nagyon egyszerűek, mivel kevés szabály logikus alkalmazásából
adódnak. Hogyan definiálunk egy osztályt?

  * Megadjuk az osztály nevét a `class` utasításban. 

  * Ugyanitt felsoroljuk az ősosztályok nevét. 

  * A `attrib` utasításokkal felsoroljuk az attribútumokat. 

  * A `method` utasításokkal felsoroljuk a metódusokat. 

  * Tipikus esetben a metódushoz nem mellékelünk kódblokkot, hanem a metódus implementációját egy `osztalyneve.metodusneve()` függvénybe helyezzük. 

  * A beágyazott objektumokat és a metódushívás-továbbítást a fordító egyszerűen és szemléletesen támogatja. 

  * Néha tényleg annyira egyszerű a metódus, hogy az egész implementáció belefér egy kódblokkba. Ilyenkor valósul meg az alapeset. 

Nem ritka, hogy egy osztálydefiníció az attribútumok és metódusok puszta
felsorolásából áll. Egyszerűbb már nem lehetne. Vannak azonban részletek, amik
fölött eddig átsiklottunk, ezeket vesszük sorra a következő pontokban.

###  6.2.  Öröklődési szabályok

Az öröklődés többszörös, C++ terminológiát használva: public, virtual. Ez azt
jelenti, hogy az öröklés elől nem lehet eldugni az attribútum/metódusokat,
azaz mindig minden öröklődik (public). A metódusok közül mindig az objektum
tényleges osztályának megfelelő hívódik meg (virtual). Nincsenek olyan
nyakatekert szabályok, mint a C++-ban vagy Jávában.

A rendszer minden osztály részére létrehoz egy hashtáblát, amiben az
attribútum/metódus név a kulcs, az érték pedig

  * attribútum esetén egy tömbindex (ezen a helyen található az attribútum értéke az objektum tartalmát hordozó tömbszerű memóriaobjektumban), 

  * metódus esetén egy kódblokk. 

A rendszer a névhez (kulcshoz) rendelt érték típusából tudja, hogy
attribútumról vagy metódusról van-e szó.

A rendszer a kezdetben üres hashtáblát feltölti. Először balról jobbra haladva
végigmegy az ősosztályokon, és összegyűjti az ezekből örökölhető tagokat. Ha
olyan névvel találkozik, ami már korábban bekerült a hashbe, akkor azt
kihagyja. Ebből adódnak a következő szabályok:

Ha a `derived` osztály `base1`-ből és `base2`-ből is örökölhetne egy tagot,
akkor `base1`-ből örököl.

Ha `base1`-ben és `base2`-ben is van attribútum ugyanazon a néven, akkor
ezeknek egyetlen közös attribútum felel meg `derived`-ben.

Ezután a rendszer berakja a hashbe a `derived`-ben definiált
attribútumokat/metódusokat, azaz a származtatott osztály új attribútumokkal és
metódusokkal bővül az ősosztályhoz képest.

Eközben is előfordul névegyezés, most azonban a rendszer mindig a felülírja a
korábbi értéket. Ez megfelel annak az objektumorientált programozási
eljárásnak, miszerint a származtatott osztály felüldefiniálja az
ősosztályoktól örökölt metódusok egyikét-másikát.

Előfordulnak azonban olyan esetek is, amikor

  * attribútum definiál felül attribútumot, hatástalan, az attribútum nem többszöröződik meg, 

  * attribútum definiál felül metódust, a metódus megszűnik, helyette új attribútum, 

  * metódus definiál felül attribútumot, attribútum megszűnik, helyette új metódus (az attribútumindexek újraszámolódnak). 

Ezeknek az öröklődési szabályoknak az az előnyük, hogy egyszerűek. Vannak
nyelvek, amik bonyolult szabályrendszerrel lekezelik a többszörös öröklődés
minden konfliktusát. Ezekkel rejtvényszerűen bonyolult programokat lehet írni.
Más nyelvek - ettől visszariadva - inkább egyszeres öröklődésre szorítkoznak.
Vannak szerzők, akik szerint már az egyszeres öröklődés is túl bonyolult, amit
nem tanácsos programozók kezébe adni (Trey Nash, C# 2008).

A mi hozzáállásunk praktikus. Megmaradunk a többszörös öröklődésnél, de nem
bonyolítjuk túl a dolgokat. Ha a fenti szabályok nem megfelelőek egy
feladatban, akkor valószínűleg nem érdemes az öröklődéses programozási modellt
erőltetni. Ilyenkor célszerű lehet beágyazott objektumokhoz és metódushívás-
továbbításhoz folyamodni.

Végül mutatunk egy példát virtuális metódusvégrehajtásra.

    
    
    ************************************************************
    function main()
        baseNew(12345):print        //kiírja: 12345
        derivedNew(12345):print     //kiírja: 12,345.00
    
    ************************************************************
    class base(object)
        attrib  number
        method  initialize
        method  print
        method  format
    
    static function base.initialize(this,x)
        this:number:=x
        return this                 //kötelező
    
    static function base.print(this)
        ? this:format               //hogyan formattál?
    
    static function base.format(this)
        return str(this:number)
    
    ************************************************************
    class derived(base)
        method  initialize
        method  format              //felüldefiniálja
    
    static function derived.initialize(this,x)
        this:(base)initialize(x)
        return this                 //kötelező
    
    static function derived.format(this)
        return transform(this:number,"999,999,999.99")
    
    ************************************************************
    
    

A példában mindkét kiírás a `base`-ben definiált `print` metódussal történik.
A nagy kérdés, hogyan történik a formattálás. A `base` osztályú objektum a
`base`-beli metódussal, a `derived` osztályú objektum viszont a `derived`-ben
definiált metódussal formázódik. Ha a `base` osztályt nem akarjuk
példányosítani, akkor a `base.format` metódusra egyáltalán nincs szükség.

###  6.3.  Attribútum/metódus invariancia

A fordító és a futtatórendszer szándékosan úgy van megírva, hogy egy objektum
felhasználójának ne kelljen feltétlenül tudni róla, hogy metódushívással,
attribútum kiolvasással, netán attribútum értékadással van-e dolga.

Először is rögzítsük: Metódushíváskor ugyanolyan szabadságunk van a
paraméterezésben (a paraméterek darabszámát és típusát illetően), mint a
függvényhívásban. A hívó akárhány darab, akármilyen típusú paramétert küldhet.
A hívott kód saját hatáskörben dönti el, hogy egy konkrét paraméteregyüttesre
mit felel.

Metódushíváskor az üres zárójelpárt nem kell kiírni.

    
    
        obj:meth            //nem kell kiírni a zárójelpárt
        obj:meth()          //ugyanaz
    
    

Ha nincs zárójelpár, akkor formailag nincs különbség a metódushívás és az
attribútum kiértékelés között. A ,,rendszer" belül azért tudja, miről van szó.
Honnan? Onnan, hogy attrubútum esetén egy index (szám), metódus esetén viszont
egy kódblokk kerül elő az osztály hashtáblájából.

A dolog meg is fordítható.

    
    
        obj:attr()          //odaírható a zárójelpár (érdektelen)
        obj:attr            //ugyanaz
    
    

Tehát attribútumokat is elláthatunk üres zárójelpárral, mintha ott sem lenne.
Természetesen a háttérben az áll, hogy a paraméter nélküli metódushívásnak és
az attribútum kiolvasásnak ugyanaz a kódja a CCC veremgépén.

Célszerű az invarianciát teljessé tenni, kiterjeszteni az attribútum
értékadásra.

    
    
        obj:attr:=x
        obj:attr(x)         //ugyanaz
    
        obj:meth(x)
        obj:meth:=x         //ugyanaz
    
    

Azért előnyös ez, mert így az objektum belső implementációjában váltani lehet
attribútum és metódus között anélkül, hogy a kliens kódban mindenhol
cserélgetni kellene a zárójeles paraméterlistákat és értékadásokat.

Az invarianciát kifejező legáltalánosabb forma:

    
    
        obj:meth(x,y,...):=z 
        obj:meth(x,y,...,z) //ugyanaz
    
    

###  6.4.  Metódus cast

A virtuális metódushívást bemutató példában láttuk, hogy alapesetben mindig az
objektum tényleges osztályában definiált metódus hívódik meg. Néha ehelyett
valamelyik ősosztály metódusára volna szükség, amit azonban ,,eltakar" a
származtatott osztályban definiált azonos nevű metódus. Ilyen esetben
folyamodunk a metódus-cast-hoz. A leggyakoribb példa, amikor az inicializátor
végrehajtja az ősosztály inicializátorát.

    
    
    static function derived.initialize(this,p1...)
        this:(base)initialize(p1...)    //a base osztály inicializátora
        ...
        return this
    
    

A `(base)initialize` jelölés mutatja, hogy a `base`-ből kell venni a metódust,
nem pedig az aktuális osztályból. Ha a `(base)` hiányozna, akkor végtelen
rekurzió volna az eredmény.

További két formája van a metódus-cast-nak:

    
    
        obj:(super@clsname)method
    
    

Ez a `clsname` nevű osztály (valamelyik) közvetlen ősosztályában definiált
metódust hívja meg. A `super` ebben a formában kulcsszó.

    
    
        obj:(parent@child)method
    
    

Ez a `parent` nevű osztályban definiált metódust hívja meg, feltéve, hogy a
`child` nevű osztály közvetlenül `parent`-ből származik. Ha nem, akkor runtime
error keletkezik.

A metódus-cast koncepciója: Az adott objektumra meghívjuk valamelyik
_ősosztály metódusát_. Az ettől eltérő használat hibákhoz vezet:

A metódus-cast-ban ne adjunk meg olyan osztályt, aminek nincs köze az
objektumhoz. Ha a rendszer úgy találja, hogy az `obj:(base)method`
kifejezésben `base` nem felmenője `obj` osztályának, akkor runtime errort
generál: `"prohibited method cast"`.

Ne alkalmazzunk metódus-cast-ot attribútumokra. Sok tekintetben a metódusok és
attribútumok egyformán viselkednek, ez azonban egy kivétel. Ha az
`obj:(base)method` kifejezés kiértékelésekor kiderül, hogy `base`-ben `method`
mégsem metódus, hanem attribútum, akkor runtime errort kapunk: `"prohibited
attribute cast"`. (Legalább nem engedi tovább. Ha a rendszer továbbengedné,
akkor a program a `derived` osztályú objektum attribútumainak tömbjében a
`base`-beli indexszel akarná megcímezni a keresett elemet. Ez mutatja, hogy a
logikánk nem terjeszthető ki attribútumokra, legalábbis nem egyszerűen.)

###  6.5.  Láthatóság

####  6.5.1.  Static osztályok

A függvényekhez hasonlóan az osztályokat is definiálhatjuk `static`-nak.

    
    
    static class derived(base)
    
    

A nem `static` esethez képest az a különbség, hogy a definícióból (belsőleg)
generálódó két függvény most `static` lesz,

    
    
    static function derivedClass()
        ...
    static function derivedNew()
        ...
    
    

így ezekre nem lehet kívülről (másik modulból) hivatkozni.

A static osztályok azonban mégsincsenek teljesen eltemetve. A
`classidbyname()` függvény neve alapján előkeresi az osztályazonosítót:

    
    
        classid:=classidbyname("derived")
    
    

A ,,rendszer" semmire sem használja az osztályok nyilvántartásában tárolt
nevet. Az objektumrendszer működését ezért nem érinti, ha a nyilvántartásban
két különböző osztály esetleg azonos névvel szerepel. ,,Alkalmazások" azonban
alapozhatnak a `classidbyname()` függvényre. Az ilyen alkalmazásoknál ügyelni
kell rá, hogy az osztálynevek ne ütközzenek. Különösen static osztályoknál,
ahol a linker nem figyelmeztet az ütközésre.

####  6.5.2.  Névterek és osztályok

Hogyan kombinálódnak a névterek és az osztálydefiníciók? Az alábbi példa
választ ad a kérdésre.

    
    
    namespace nsp
    
    static class base(object)
    
    class proba.szerencse.derived(nsp.base)
        method hopp
    
    static function proba.szerencse.derived.hopp(this)
        ? "HOPP"
    
    

A `namespace` utasítás az egész modult az `nsp` névtérbe teszi. A `derived`
osztályban ez még tovább mélyül a `proba.szerencse` többszintű névtérrel. Az
ősosztály megadásakor ki kell írni a minősített osztálynevet: `nsp.base`.

Próbáljuk ki a programot az alábbi főprogrammal. A `namespace` utasítás miatt
ez most szükségszerűen külön modulban kell legyen, mert a `main` nem lehet
minősítve.

    
    
    function main()
    local o
        ? "1. lista"
        classListAll()
        o:=nsp.proba.szerencse.derivedNew()
        ? "2. lista"
        classListAll()
        o:hopp
        ? classidbyname("nsp.base")
    
    

A program ezeket írja ki:

    
    
    1. lista
    
    2. lista
       1 object                         0   14   64
       2 nsp.base                       0   14   64
       3 nsp.proba.szerencse.derived    0   15   64
    
    HOPP
             2
    
    

Az osztályok akkor jönnek létre, amikor a program hivatkozik rájuk. Az 1.
lista azért üres, mert a program nem csinált még egy objektumot sem. A 2.
lista tartalma:

  1. oszlop: osztályazonosító index (`classidbyname("object")==1`) 

  2. oszlop: az osztály minősített neve 

  3. oszlop: attribútumok száma 

  4. oszlop: attribútumok+metódusok száma 

  5. oszlop: hashtábla mérete 

A `base` osztályt hiába definiáltuk `static`-nak, mégis megjelenik a listában,
és az azonosítója is megkapható (2).

####  6.5.3.  Hivatkozás a class függvényre

Mint látjuk, az xClass és xNew függvényekkel minden megeshet, ami a
függvényekkel általában megesik. Névtérbe kerülhetnek, `static`-ok lehetnek.
Az xNew (objektumgyártó) függvénynél ennek következményei nyilvánvalók, mert
érvényesek rá a függvényekre vonatkozó általános szabályok.

Az xClass függvényt a programok általában nem használják közvetlenül. Az
alábbi három szituációban azonban rejtve mégis a `baseClass()` függvényre
történik hivatkozás:

    
    
        1) class derived(base)
        2) this:(base)initialize
        3) recover err <base>
    
    

Ha viszont így van, akkor itt is felvetődik a láthatóság és a névtér kérdése:

Ha a `base` osztály `static`-nak van definiálva, akkor más modulból nem tudunk
rá hivatkozni. Linkeléskor bukik ki az ilyen hiba, a linker nem találja a
`baseClass()` függvényt.

Ha az alaposztály névtérből van, akkor azt teljes útvonallal jelölni kell:

    
    
        1) class derived(multi.level.namespace.base)
        2) this:(multi.level.namespace.base)initialize
        3) recover err <multi.level.namespace.base>
    
    

###  6.6.  Defaulttól eltérő new függvény

    
    
    class derived(base) new:symbol
        ...
    
    

A `new:symbol` toldalék opcionális. Ha hiányzik, akkor a default `derivedNew`
nevű konstruktor készül. Ha van new toldalék, de a symbol tagja üres (tehát
ilyen alakú `new:`), akkor egyáltalán nem keletkezik konstruktor függvény.
Teljes new toldalék esetén a `symbol`-ban megadott névvel képzett
`derivedSymbol` konstruktort kapjuk.

###  6.7.  Metódushívás-továbbítás

    
    
    class proba(object)
        attrib  a1
        attrib  a2
        method  m1      :a1
        method  m2      :a2:b:c:m
    
    function main()
    local p:=probaNew()
        p:a1:="Próba szerencse"
        ? p:m1      //kiírja: "Próba szerencse"
    
    

A példában `m1` lényegében egy alias az `a1` attribútumra, set-get metódusokat
lehet így implementálni.

Az `m2` metódus feltételezi, hogy az `a2` (beágyazott objektum) attribútumnak,
van egy `b` attribútuma, annak egy `c` attribútuma és annak egy `m` metódusa.
Ennek a metódusnak továbbítódik a metódushívás. Nem kell ismernünk `m`
implementációját, automatikusan minden paraméter továbbításra kerül. Ráadásul
a fordító ügyesen rendezgeti a stacket, nem jönnek létre felesleges
függvényhívási szintek.

###  6.8.  A könyvtári object osztály

    
    
    class template(object)
        attrib cargo        //teljesen üres is lehetne
    
    function main()
        templateNew():liststruct
    
    

Az objektumorientált programozás erejét mutatja, hogy már az egyszerű
`template` osztály is említésre méltó tudással rendelkezik, ugyanis egy csomó
dolgot örököl az `object`-től. Ki tudja listázni, hogy milyen metódusai és
attribútumai vannak, ki tudja listázni az attribútumainak az értékét, meg
tudja mondani az osztályának és a szülő osztályainak a nevét. Ezzel a
képességgel _minden_ osztály rendelkezik. Az `object`-ből öröklődő
metódusokat vesszük most sorra.

- **`ancestors`**
     Ad egy listát az ősosztályok nevével.
- **`asarray`**
     Egy tömbben visszaadja az összes attribútumot.
- **`attrnames`**
     Ad egy listát az attribútumok nevével.
- **`attrvals`**
     Visszad egy array-t, melynek elemei kételemű tömbök, az összes attribútum nevéből és értékéből képzett pár.
- **`baseid`**
     Ad agy arrayt, ami a közvetlen ősosztályok azonosítóit tartalmazza.
- **`classname`**
     Visszaadja az objektum osztályának nevét.
- **`evalmethod`**
     Név szerinti metódushívás (`o:evalmethod("methname",{a,b,c})`)
- **`initialize`**
     Inicializálja az objektumot. Valójában egy object osztályú objektumon nincs mit inicializálni, mert az osztályban nincs egyetlen attribútum sem, csak metódusok.
- **`isderivedfrom(clid/obj)`**
     Megmondja, hogy this (osztálya) leszármazottja-e az osztályazonosítóval/objektumpéldánnyal megadott másik osztálynak.
- **`length`**
     Megmondja az attribútumok számát.
- **`list`**
     Kilistázza magát (az attribútumait) a konzolra.
- **`liststruct`**
     Kilistázza, hogy milyen attribútumai, metódusai vannak, és melyiket honnan örökölte.
- **`methnames`**
     Ad egy listát a metódusok nevével.
- **`struct`**
     Ad egy tömböt, ami azt a struktúrát tartalmazza, amit liststruct kilistáz.

Felsorolunk néhány további objektumokkal kapcsolatos függvényt, amik azonban
nem metódusai az object osztálynak:

- **`classListAll()`**
     Listázza a program összes osztályát.
- **`classIdByName(classname)`**
     Név alapján kikeresi és visszaadja az osztályazonosító számot. Ha a megadott névvel nincs osztály, akkor 0-t ad.
- **`getClassId(obj)`**
     Az objektumpéldányból megadja annak (szám) osztályazonosítóját.
- **`getObjectAsArray(obj)`**
     Egy tömbben visszaadja az összes attribútumot. Ezen a függvényen alapul az asarray metódus.
- **`iniObjectFromArray(obj,arr)`**
     Inicializálja az objektumot egy olyan arrayből, amit korábban a getobjectasarray (vagy asarray metódussal) kaptunk, enélkül a getobjectasarray nem is volna értelmesen használható.
- **`objectNew(clid)`**
     A függvény paramétere az osztályazonosító (szám). Visszaad egy megadott osztályú, új, inicializálatlan objektumpéldányt. Ezen alapul minden konstruktor.

A példaprogram a következőket írja ki:

    
    
             1 ancestors                M object
             2 asarray                  M object
             3 attrnames                M object
             4 attrvals                 M object
             5 baseid                   M object
             6 classname                M object
             7 evalmethod               M object
             8 initialize               M object
             9 isderivedfrom            M object
            10 length                   M object
            11 list                     M object
            12 liststruct               M object
            13 methnames                M object
            14 struct                   M object
            15 cargo                    A template
    
    

###  6.9.  Függvény interfész

Többször volt már említve, hogy az osztálydefiníció eredménye az xClass és
xNew függvények. A programban ez a két függvény képviseli az osztályt.
Általában a fordítóprogram generálja ezeket az osztálydefinícióból.

Talán nem meglepő, hogy ,,kézzel" is írhatunk xClass és xNew függvényeket. Az
alábbi példa létrehozza a `template` osztályt (kibővítve egy `initialize`
metódussal).

    
    
    static clid_template:=templateRegister()
    
    static function templateRegister()
    local clid:=classRegister("template",{objectClass()})
        classMethod(clid,"initialize",{|this|template.initialize(this)})
        classAttrib(clid,"cargo")
        return clid
    
    static function template.initialize(this)
        ...
        return this
    
    function templateClass()
        return clid_template
    
    function templateNew()
    local clid:=templateClass()
        return objectNew(clid):initialize
    
    

A `classRegister` függvény első argumentuma tartalmazza az új osztály nevét, a
második argumentum egy array, amiben az új osztály szülő osztályait kell
felsorolni. A legegyszerűbb esetben az új osztály az objectClass-tól (minden
osztály közös ősétől) származik.

A `classMethod` függvény egy metódust ad a clid-vel azonosított osztályhoz. A
metódus nevét a második paraméterben adjuk át, jelen esetben a név
,,initialize". A metódus végrehajtása a harmadik argumentumban átadott
kódblokk kiértékelésével történik. A metódusblokkok első paramétere mindig
maga az objektum, amit általában ,,this" névvel illetünk, de itt ez nem
kulcsszó, mint a C++-ban, vagy a Jávában.

A `classAttrib` függvény egy attribútumot ad a clid-vel azonosított
osztályhoz.

Nyilvánvaló a megfelelés a `class` osztálydefiníció és a függvényinterfész
között. A fordítóprogram egyébként úgy működik, hogy a `class` definícióból
belsőleg előállítja a függvényinterfész kódot, és azt a szokásos módon
lefordítja.

##  7.  Kivételkezelés<a name="7"></a>

###  7.1.  Mikor kapunk el kivételt?

Képzeljünk el egy tranzakció végrehajtó programot. Tegyük fel, hogy a
tranzakció viszonylag bonyolult, sok külső feltételtől függ, végrehajtható-e.
Például egy betétlekötésnél kell legyen leköthető pénz, kell legyen kamatláb,
stb.. A program elkezdi a végrehajtást, ám egyszercsak kiderül, hogy egy
feltétel nem teljesül. Hiába minden erőlködés, nem lehet továbbmenni.

Mit csináljon a program?

Egy lehetőség, hogy a függvény, ami észleli a hibát kiírja (csak a példa
kedvéért) ,,nincs pénz", és kilép.

    
    
        if( nincs_penz )
            ? "nincs pénz"
            quit
        end
    
    

A legrosszabb. Tegyük fel, hogy egy ilyen programot kell javítanunk. Tudni
akarjuk, hol nincs pénz, rákeresünk tehát a hiba szövegére, és azt találjuk, a
programozó következetes volt, a szöveg 10 helyen fordul elő a kódban. Rémálom.

Másik lehetőség, hogy a hibát észlelő függvény hibakóddal tér vissza. Ezzel
sajnos nincs elintézve a dolog, mert bonyolult tranzakcióról lévén szó, a
kérdéses függvény akár 10-20 függvényhívási szint mélységben lehet. Tehát a
programot úgy kell megírni, hogy a hívó mindenhol felkészül a hibakód
,,feljebb adására". Az ilyen program zavarossá válik, eluralkodik benne a
hibakezelés, megnehezül a karbantartás.

A kényes szituáció kezelésére szolgál (egy harmadik lehetőség) a kivétel
dobás. A CCC-ben a

    
    
        break(x)
    
    

utasítással dobunk kivételt. Az `x` változó típusa bármi lehet.

Más nyelveknél (pl. Jáva) ezen a helyen a kivétel elkapásával folytatódna a
leírás, én szándékosan más sorrendet választok. Azt szeretném ezzel
hangsúlyozni, hogy

  * a kivételnek nem az a célja és értelme, hogy elkapjuk, hanem 

  * a kivétel egyszerűen azt fejezi ki, hogy a program nem futhat tovább. 

Mire számíthatunk, ha nem kapunk el egy kivételt? Nézzünk egy példaprogramot:

    
    
    function main()
        proba1()
    
    function proba1()    
    local v:="x"
        proba2()
    
    function proba2()    
    local v:="y"
        proba3()
    
    function proba3()    
    local v:="z"
        break("HOPP")
    
    

A `break("HOPP")` hatására a program ,,elszáll" a következő hibaüzenettel:

    
    
    default error block evaluated
    errorclass: C HOPP
      called from deferror(215)
      called from _blk__2(0)
      called from proba3(14)
      called from proba2(10)
      called from proba1(6)
      called from main(2)
    -----------------------------------------------------------
     Variable Stack
    -----------------------------------------------------------
    0: BINARY length=24 oref=b7949048 "^^^^^^^^^^^^^^^^^^^^^^^^"
    1: BLOCK oref=NULL
    ***** function main
    ***** function proba1
    0: STRING length=1 oref=b7949008 "x"
    ***** function proba2
    1: STRING length=1 oref=b7949018 "y"
    ***** function proba3
    2: STRING length=1 oref=b7949028 "z"
    3: STRING length=4 oref=b7949038 "HOPP"
    ***** function _blk__2
    4: BLOCK oref=NULL
    5: STRING length=4 oref=b7949038 "HOPP"
    ***** function deferror
    6: STRING length=4 oref=b7949038 "HOPP"
    7: FLAG .T.
    8: NIL
    9: STRING length=0 oref=b7949078 ""
    10: ARRAY length=0 oref=b7949088
    11: NIL
    -----------------------------------------------------------
    
    

Kiíródik a callstack, minden függvényhívási szinten feltüntetve az aktuális
programsor száma. Kiíródik az összes static változó (main fölött), majd a
függvényhívási szintek megjelölésével az egész local stack. A gyakorlott
programozó számára ez az infó az esetek többségében elegendő egy hiba
azonosítására.

Térjünk vissza a tranzakcióhoz, próbálkozzunk ilyen hibakezeléssel:

    
    
        if( nincs_penz )
            break("nincs pénz") //quit helyett
        end
    
    

Máris beljebb vagyunk. Még mindig nem foglalkozunk a hiba elkapásával. Azért
vagyunk lényegesen beljebb, mert bár a program most sem fut tovább, nem
veszítjük el a hibára vonatkozó infót, mint a `quit` után. A programozó a
hibalista elemzéséből debugolás nélkül is látja, hol nem volt pénz.

Tegyük fel, hogy a tranzakció a 4. függvényhívási szinten indul, a
`break("nincs pénz")` kivétel dobása a 10. függvényhívási szintről jön, mi
pedig éppen egy 7. szinten levő függvény kódjában kotorászunk. Meghívni
készülünk egy függvényt, amiről tudjuk, hogy `break("nincs pénz")` kivételt
dobhat. Mit tegyünk, kapjuk-e el a kivételt?

A legnagyobb baklövés:

    
    
        begin
            ...
            fuggveny8()    // break("nincs pénz") jöhet belőle
            ...
        recover hiba <C>   // elkapja
            //elkaptam a kivételt,
            //mert lelkiismeretes munkaerő vagyok,
            //és úgy tanították, hogy a hibákat le kell kezelni,
            //csak azt tudnám, most mi a fenét kezdjek vele?
            //ez a legrosszabb        
            ? hiba //kiírja: nincs pénz
            quit
        end
    
    

A program idejekorán elkap egy kivételt, amivel nem tud mit kezdeni, és ezzel
megsemmisíti a hiba eredeti környezetét. Sajnos a Jáva nyelv erőteljesen
tereli a programozót ebbe az irányba, ráadásul a Jáva tankönyvek szinte
kivétel nélkül a fenti értelemben káros hibakezelést tanítják.

A helyes hozzáállás:

  * Észlelésekor nem a hiba elnyomására kell törekedni, hanem kivételt kell dobni (a program nem folytatódhat). 

  * Csak olyan kivételt szabad elkapni, amivel direkt kezdeni akarunk valamit. Kevés olyan hely van a programban, ahol a hiba orvosolható, következésképp az esetek többségében az a jó, ha a kivételt nem kapjuk el. Ha a hibát idejekorán elkapjuk, azzal megakadályozzuk, hogy a kivétel eljusson a hibakezelésre ténylegesen felkészített kódhoz. Mindezek miatt az alapállás, hogy nem kapkodunk kivételek után, hanem engedjük a hibát eljutni a felsőbb szintekre. 

  * A _tranzakció logikájának megfelelő helyen_ (ha egyáltalán) felkészülünk a kivétel kezelésére. 

Ha egy kivétel sehol sincs elkapva, az nem feltétlenül baj. A program kilép,
és pontos infót ad a kilépés okáról. Az esetek többségében éppen erre van
szükség. Mindez azonban nem szabály, inkább _szempont_.

A tranzakció logikája mellett még egy gyakorlati szempontot tudok ajánlani
kivétel elkapás (elkapjam-nekapjam) kérdésében. Ne kapjunk el _programhibát_,
vagyis olyan kivételt, amit inkább a program kijavításával kell megszüntetni.

A CCC kivételkezelése nagyon hasonlít a Jávához. CCC-ben azonban nincs külön
throwable osztály, bármit lehet dobni, és bármit el is lehet kapni. Logikus,
hogy így van, hiszen `break()` közönséges függvény, akármilyen
paraméterezéssel meg lehet hívni. Az meg végképp nem volna szép, ha valamit
dobni lehet, de elkapni nem.

Kialakult az a konvenció, hogy a programozási hibákból `error` osztályú
kivétel objektum keletkezik, amiket nem kapunk el. Ahol felmerülhet, hogy
hasznos a kivétel elkapása, ott az `apperror` osztályt vagy annak
leszármazottait dobjuk. Tehát valahogy így készül a kivétel:

    
    
        if( nincs_penz )
            error:=apperrorNew()
            error:description:="nincs pénz"
            break(error)
        end
    
    

Ha differenciáltabb hibakezelésre van szükség, akkor az alkalmazás definiál
magának speciális `apperror` leszármazottakat.

Az alábbi vázlat mutatja, hogyan gondolom a kivételkezelést összehangolni a
tranzakció logikájával:

    
    
        while( van_meg )
            begin               
                tranzakcio()
                //sikerült
                commit()
            recover error <apperror>
                //nem sikerült
                error:list
                rollback()
            end
        end
    
    

###  7.2.  A begin...recover utasítás

A következő példán tanulmányozzuk a `begin...recover` utasítás technikai
részleteit. Tanulságos a program lefordítása és próbálgatása különféle
variációkban.

    
    
    function main(x)
    local e
        if( x==NIL )
            //NIL
        elseif( isdigit(x) )
            x:=val(x)
        elseif( x=='e'  )
            x:=errorNew()
            x:description:="próba"
        elseif( x=='a'  )
            x:=apperrorNew()
            x:description:="szerencse"
        else
            //karakter
        end
            
        begin    
            fuggveny1(x)
        recover e <N>
            ? "szám",e
        recover e <error>
            ? "error",e:description
        finally
            ? "finally-main"
        end
        ? "OK"
        ?
    
    function fuggveny1(x)    
    local e
        begin
            fuggveny2(x)    
        recover e <apperror>
            ? "apperror",e:description
        finally
            ? "finally-fuggveny1"
        end
    
    function fuggveny2(x)    
        //errorblock({||qout("ERROR")}) //kikapcsolja a hibakezelést
        break(x)
        ? "break után"
    
    

A program az `x` argumentumtól függően különféle típusú kivételt dob. A
`break(x)`-ben `x` típusa bármi lehet, mi most csak néhány variációt nézünk a
példa kedvéért (NIL, szám, error, apperror, karakter).

A `break(x)` megszakítja a végrehajtás normál sorrendjét, a rendszer elkezdi
keresni a kivételt elkapó `recover` utasítást.

    
    
        recover e [type_expr]
    
    

A `recover` kulcsszót egy változó majd egy opcionális típuskifejezés követi. A
`recover` akkor kapja el a `break`-kel dobott kivételt, ha a `break`
paraméterének típusa megfelel a `recover`-beli típuskifejezésnek. Mi állhat a
típuskifejezés helyén?

  * Üres. Az ilyen `recover` mindent elkap. 

  * Tetszőleges kifejezés, ami az adott helyen kiértékelhető. A kifejezésnek csak a típusa számít, az értéke nem hozzáférhető (de mellékhatásai lehetnek). A kifejezés már a `begin...recover` elején kiértékelődik. A különböző `recover` kifejezések kiértékelésénék sorrendje nincs meghatározva. A `recover` akkor kapja el a kivételt, ha a típusok megegyeznek. 

  * `<U>`, `<L>`, `<N>`, `<D>`, `<P>`, `<C>`, `<X>`, `<A>`, `<B>`, `<O>`, azaz a különféle típusok kódja hegyes zárójelek között. Például: `<C>` jelöli a karakter típust, a `<C>` típusú `recover` elkapja a karakter kivételeket. 

  * `<osztaly>`, vagyis osztálynév hegyes zárójelek között. Az ilyen `recover` azokat az objektum típusú kivételeket kapja el, amiknek az osztálya megegyezik a `recover` osztályával, vagy annak leszármazottja. 

A `recover` ,,elkapja" a kivételt: Azt jelenti, hogy visszaállítódik a stack,
a kivétel (`break` paramétere) behelyettesítődik a `recover` változóba (a
példában `e`-be), és a végrehajtás a `recover` utáni sorral folytatódik.
Végrehajtódik a `recover` ág, ami a következő `recover`-ig, vagy az opcionális
`finally`-ig, vagy a `begin...recover`-t lezáró `end`-ig tart. Ha van
`finally` ág, akkor az is végrehajtódik. A végrehajtás ezután az `end`-et
követő soron folytatódik.

Hol és milyen sorrendben keresi a rendszer a kivételt elkapó `recovert`?
Először is teszünk egy észrevételt: A `begin...recover` utasítások egymásba
lehetnek ágyazva. A keresés a `break`-et tartalmazó legbelső `begin...recover`
utasításban kezdődik. (A példában a `fuggveny1`-beli a legbelső.) Itt a
rendszer felülről lefelé haladva keres a `recover`-ek között. Az első
illeszkedő típus nyer.

Ha nem talál, akkor - mint héjakon - belülről kifelé haladva keres a többi
`begin...recover`-ben. Például a szám típusú kivételt a `main`-beli első
`recover` fogja elkapni.

Miután megvan a kivételt elkapó `recover`, a rendszer megnézi, hogy mely
`begin...recover` utasításokon (héjakon) kellett átvágnia magát, és
végrehajtja ezek esetleges `finally` ágait. A sorrend természetesen belülről
kifelé. Ezután a végrehajtás a nyertes `recover` ágra kerül, a többit már
ismerjük.

A `begin...recover` specialitása a többi vezérlési struktúrához képest, hogy
átlépi a függvényhatárokat. Éppen ez kell a tranzakció-orientált
hibakezeléshez.

De miért mondtuk, hogy csak miután megvan a `recover`, azután hajtódnak végre
az átlépett/elhagyott `begin...recover`-ek `finally` ágai? Miért nem a keresés
közben? Mert nem tudható előre, lesz-e egyáltalán megfelelő `recover`. Ha
semmi sem kapja el a kivételt, akkor a `begin...recover`-ek mintha ott sem
lennének, az eset a magában álló `break`-hez hasonlít. Ilyenkor sehova sem
tevődik át a vezérlés (következésképp a `finally` ágak sem játszanak), hanem a
hiba _eredeti környezetében_ kiértékelődik az `errorblock`. Az eredményt már
láttuk.

Hátra van még néhány speciális eset:

Ha a `begin...recover`-t nem szakítja meg `break`, akkor a végrehajtás
átugorja a `recover` ágakat, belemegy az esetleges `finally`-ba, majd az `end`
után folytatódik.

Lehetséges, hogy nincs egy `recover` ág sem:

    
    
        begin
            ...
        finally
            ...
        end
    
    

Az ilyen struktúra nem kap el semmit, de végrehajtódik a `finally` ág, ha
nincs kivétel, vagy ha van, de azt elkapja egy külső `begin...recover`.

Lehetséges, hogy nincs `finally` sem:

    
    
        begin
            ...
        end
    
    

Ez viszont egyenértékű azzal, mintha az `end` előtt állna egy mindent elkapó
(üres) `recover` ág.

A `begin...recover`-ből szabad kiugrani `return`, `loop`, `exit`
utasításokkal. Ilyenkor végrehajtódnak az elhagyott `begin...recover`-ek
`finally` ágai.

Kezdetleges formában már a régi Clippernek is volt `begin...recover`
utasítása. A CCC ezt kiterjesztette, és teljessé tette.

###  7.3.  Az errorblock

Még egy eszköz áll a hibakezelés szolgálatában, ami a régi Clipperben is
megvolt, az errorblock. Volt ilyen mondásunk: Az el nem kapott kivétel
hatására a program ,,elszáll". Mit jelent ez részleteiben?

A `break()` próbál olyan `recover`-t keresni, ami elkapja a kivételt, ám
lehet, hogy nincs ilyen. Mi mást tehetne ilyenkor, valahogy be kell fejezni a
programot, kiértékeli hát az errorblockot. Az erroblock egy kódblokk, ami
direkt arra szolgál, hogy ez hajtódjon végre kezeletlen hiba esetén.

Már láttuk hogyan működik a beépített hibakezelő: Kiírja a callstacket,
varstacket, majd kilépteti a programot. A hibakezeleő blokkot azonban az
alkalmazás a saját igényei szerint lecserélheti, láncba fűzheti.

    
    
    local defblk:=errorblock()
        errorblock({|x|naplo(x),eval(defblk,x)})
        ...
    
    

Ez a program először lekérdezi a default hibakezelőt az `errorblock()`
függvény paraméter nélküli hívásával, majd ugyanezzel beállít egy új
hibakezelő kódblokkot, amiben először naplózza a hibát, majd végrehajtja az
eredeti hibakezelést. Csak a példa kedvéért.

A `begin...recover` és `break` működését tanulmányozhatjuk kikapcsolt
hibakezelés mellett, ha a `fuggveny2`-ben megszüntetjük az `errorblock()`
hívás kikommentezését.

##  8.  Többszálúság<a name="8"></a>

###  8.1.  Pthread API

A CCC2-től kezdve van multithread támogatás. Az alább felsorolt API áll
rendelkezésre szálak indítására és szinkronizálására:

    
    
    thread_create(codeblock,p1,...) --> threadid
    thread_self() --> threadid 
    thread_detach(threadid) --> status
    thread_exit() --> NIL
    thread_join(threadid) --> status
    thread_mutex_init() --> xMutex
    thread_mutex_lock(xMutex) --> status
    thread_mutex_trylock(xMutex) --> status 
    thread_mutex_unlock(xMutex) --> status 
    thread_mutex_destroy(xMutex) --> status 
    thread_cond_init() --> xCond
    thread_cond_signal(xCond) --> status
    thread_cond_wait(xCond,xMutex[,nMillis]) --> status 
    thread_cond_destroy(xCond) --> status
    
    

A CCC szintre kivezetett egyszerűsített pthread API CCC-ből ugyanúgy működik,
mint C-ből. Nincs értelme most referenciaszerű leírást adni róla, mert több
ilyen található az interneten. [Itt van pl. egy a számos
közül](http://cs.pub.ro/~apc/2003/resources/pthreads/uguide/document.htm). A
man is használható a _pthread_ címszavaknál. Magam is a man oldalak alapján
dolgozom, pl.

    
    
    man 3 pthread_cond_signal
    
    

Linuxon nyilvánvaló megfelelés van a pthread könyvtár és a CCC között.
Windowson ugyanez az interfész vissza van vezetve Windows API-ra, nem
különösebben bonyolult.

Új szálakat kódblokk végrehajtással indítunk. A `thread_create(blk,p1,...)`
függvényt pontosan úgy kell meghívni, mint az `eval()`-t, a különbség, hogy
`thread_create()` azonnal visszatér, miközben az új szál futásnak indul.

A szálak ugyanabban a változótérben dolgoznak. A static változók (külsők és
belsők) közösek, egy példányban léteznek. Minden szál külön local stackkel
rendelkezik. Bármelyik szálból kiindulhat a szemétgyűjtés.

###  8.2.  Egyszerű példa - mutex

Az alábbi példa elindít 5 darab szálat. Minden szál ugyanazt csinálja:
100,000-szer hozzáad 1-et a `sum` változóhoz, a helyes végösszeg tehát 500,000
volna. A program azonban szándékosan el van rontva, ki van kommentezve a
`sum++` sort védő mutex lock.

    
    
    static mutex:=thread_mutex_init()
    static sum:=0
    
    function main()
    local blk:={||addtosum()}
    local tid:={},i
    
        aadd(tid,thread_create(blk))    //új szál, az azonosítót megőrzi
        aadd(tid,thread_create(blk))
        aadd(tid,thread_create(blk))
        aadd(tid,thread_create(blk))
        aadd(tid,thread_create(blk))
        
        for i:=1 to len(tid)
            ? i, tid[i]
            thread_join(tid[i])         //megvárja, hogy befejeződjön
        next
        ? "végösszeg",sum               //a helyes eredmény 500000
        ?
        
    function addtosum()
    local i
        for i:=1 to 100000
            //thread_mutex_lock(mutex)  //kellene!
            sum++
            //thread_mutex_unlock(mutex)
        next
    
    

A mutex (_mutually exclusive_) olyan dolog, amit lockolni (zárolni,
megfogni) és unlockolni (elengedni) lehet. A lényeg, hogy egyszerre legfeljebb
egy szál foghatja a mutexet. Amíg egy szál fogva tartja, addig a többi szálból
meghívott `thread_mutex_lock` vár a mutex felszabadulására. A mutex
mechanizmussal tehát biztosítani lehet, hogy egy kódrész végrehajtásával
egyszerre legfeljebb egy szál foglalkozzon.

Fontos észrevétel, hogy a `sum++` művelet végrehajtása nem atomi. Atomi
nagyjából azt jelenti, hogy felbonthatatlan egység. 32-bites processzoron egy
32-bites mennyiség memóriából történő kiolvasása atomi. 2 darab 32-bites
mennyiség kiolvasása már nem atomi. Lehet, hogy közben a processzor más
tevékenységre vált, pl. folytatja egy másik szál végrehajtását. `sum++` ehhez
képest a static változó értékét (eleve több mint 64 bit) átrakja a local
stackre, hozzáad 1-et, majd az eredményt visszamásolja az eredeti helyre.
Sokszorosan nem atomi.

A saját gépemen 250 ezer körüli véletlenszerű eredményt kapok. Kikommentezett
mutex lock/unlockkal a példaprogram azért működik rosszul, mert egyszerre több
szál is kiolvashatja `sum`-ból _ugyanazt_ a pillanatnyi értéket, és ilyenkor
valamelyik szál növekménye elvész.

Vigyázzunk, hogy a mutexet ne lockoljuk ugyanabból a szálból többszörösen, ui.

    
    
        thread_mutex_lock(mutex)
        thread_mutex_lock(mutex)  //deadlock
    
    

deadlockot eredményez.

Egy további észrevétel. A példa a mutexet külső static változóként deklarálja.
Az világos, hogy static-nak kell lennie. Ha local volna, akkor minden szálnak
külön példánya volna belőle, nem tudná kifejteni a működését. De lehetne-e
belső static `addtosum`-ban? Az a nehézség, hogy a static változók (elvileg
csak egyszer futó) inicializálását is szinkronizálni kell. Szinkronizáció
híján előfordul, hogy az inicializátor néha mégis többször fut. Éppen ezért a
CCC a külső static változók inicializátorát mindig szinkronizálja, hogy legyen
biztos kiindulópont. A belső static változók inicializátora nincs automatikus
mutex védelem alatt (ritkán kell, viszont költséges).

###  8.3.  Egyszerű példa - cond

A következő program sok szálat hoz létre. A szálak véletlen hosszú ideig,
átlagosan 1 másodpercig élnek, az egyszerre életben levő szálak száma
`level<=MAXTHREAD`. A program folyamatosan listázza a létrejövő és megszűnő
szálakat, mindaddig, amíg ESC-et nem ütünk neki. Végül megvárja az összes
thread kilépését.

    
    
    #include "inkey.ch"
    
    #define MAXTHREAD  16
    
    static mutex:=thread_mutex_init()
    static cond:=thread_cond_init()
    static level:=0
    static count:=0
    
    function main()
    local th
    
        while( inkey(0.05)!=K_ESC  )
            th:=thread_create({|x,r|dothread(x,r)},count,rand())
            thread_detach(th)
            
            //A threadeket vagy el kell engedni (thread_detach)
            //vagy meg kell várni (thread_join), máskülönben
            //elfogynak a létrehozható threadek (Linuxon kb. 90).
    
            thread_mutex_lock(mutex)
            //A level változót a threadek módosítgatják,
            //ezért csak mutex védelem alatt biztonságos a kiolvasása.
            ? padl(l2hex(th),8), count, level
            ++level
            ++count
            while( level>MAXTHREAD )
                thread_cond_wait(cond,mutex)
            end
            thread_mutex_unlock(mutex)
        end
    
        thread_mutex_lock(mutex)
        while( level>0 )
            thread_cond_wait(cond,mutex)
            ? "wait",level
        end
        thread_mutex_unlock(mutex)
    
    static function dothread(x,r)
        sleep(r*2000)  //átlagosan 1 másodpercet vár
        thread_mutex_lock(mutex)
        --level
        ? "quit",x,r
        thread_cond_signal(cond)
        thread_mutex_unlock(mutex)
    
    

A példa fő tanulsága, hogyan várunk arra `main`-ben, hogy a `level` változó (a
többi szál tevékenységének következtében) lecsökkenjen egy kívánt értékre. A
program elején egy mutex és egy cond objektumot hoztunk létre. Általában egy
cond  (_condition_) objektumot mindig egy mutexszel együtt használunk.

Az alábbi kódrészletben a `thread_cond_wait(cond,mutex)` híváskor `mutex`-nek
lockolva kell lennie. A `thread_cond_wait` automatikusan elengedi a mutexet,
és vár, amíg valamelyik másik száltól szignált nem kap. A várakozás alatt a
szál futása fel van függesztve, semennyi CPU időt nem fogyaszt. Miután megjött
a szignál `thread_cond_wait` újra megfogja `mutex`-et, majd visszatér.

    
    
        thread_mutex_lock(mutex)
        while( level>0 )
            thread_cond_wait(cond,mutex)
        end
        thread_mutex_unlock(mutex)
    
    

Eközben a többi szál minden alkalommal, amikor a `level` változó csökken,
szignált küld, hogy a várakozó szál értesüljön az eseményről.

    
    
        thread_mutex_lock(mutex)
        --level
        thread_cond_signal(cond)
        thread_mutex_unlock(mutex)
    
    

A `thread_cond_signal(cond)` hívás ,,szignált küld" a `cond` objektumnak. Ha
egyetlen szál sincs, amelyik éppen `cond`-ban várakozna, akkor a szignál
hatástalan. Ha több szál is várakozik `cond`-ban, akkor ezek közül az egyik
továbbindul, de hogy melyik, az nincs meghatározva.

###  8.4.  Thread-local storage

Tudjuk, hogy a program static változói csak egy példányban léteznek, és az az
egy példány minden szálra közös. Ezzel szemben minden szálnak saját local
stackje van, a stack változók ezért szálanként elkülönülnek. De nem csupán
szálanként. A local változók csak egy-egy függvényen belül léteznek, és minden
függvényhívásban külön létrejönnek. Hol tudunk akkor olyan adatot tárolni, ami
szálanként egyedi, de egy szálon belül közös. Az ilyen adatok kezelésére
szolgáló mechanizmust nevezik ,,thread-local storage"-nak.

CCC-ben a `localstack` függvénnyel lehet egyszerű TLS-t csinálni. Nézzük az
alábbi programot:

    
    
    function main(a,b,c)
    local x:="x", y:="y"
        ? localstack(1)
        ? localstack(2)
        ? localstack(3)
        ? localstack(4)
        ? localstack(5)
    
    

Ha a programot így indítjuk

    
    
    proba.exe q w
    
    

akkor ezt a kimenetet kapjuk:

    
    
    q
    w
    NIL
    x
    y
    
    

Világos, hogy `localstack(x)` előveszi (akár egy tömbből) a local stack
`x`-edik elemét. Kicsit vigyázni kell vele, de általában tudható, van-e elég
érték a stacken, a példaprogramban biztosan megvan legalább 5 darab.

Egyszerű ötlet: A thread közösnek szánt adatait tegyük be a local stack
aljára. Tulajdonképpen egyetlen érték is elég, hiszen lehet az egy hashtábla
(vagy array, vagy objektum), amiben aztán annyi további adatot tárolhatunk,
amennyi kell, és akár név szerint is hivatkozhatunk rájuk.

    
    
    local blk:={|p1,p2|dothread(p1,p2)} 
    local a,b,c
        ...
        thread_create(blk,a:=simplehashNew(),b,c)
        ...
    
    

A szálban hívott `localstack()` értékei:

    
    
        localstack(1)  // -->  blk
        localstack(2)  // -->  a
        localstack(3)  // -->  b
        localstack(4)  // -->  nem definiált (dothread-től függ)
        localstack(5)  // -->  nem definiált, stb.
    
    

A kódblokkot és a blokknak átadott paramétereket lehet megkapni a szálból
bárhonnan, legfeljebb olyan számban, ahány `p1`, `p2`... paramétere van a
blokknak. A példában `localstack(2)` egy szálanként egyedi, de szálon belül
közös hashtáblát ad.

###  8.5.  Szálbiztonság

A szálbiztonság első kritériuma: biztonság a szemétgyűjtéssel szemben. Minden
olyan pillanatban, amikor egy másik szálból szemétgyűjtés indulhat, a vermeken
kell legyen minden élő változó, de nem lehet ott semmi más, pl. keletkezőben
vagy megszűnőben levő változók. Ha egy változó nincs rajta a stacken, akkor a
hozzá tartozó memóriaobjektumot kitakaríthatja a szemétgyűjtés. A keletkezőben
vagy megszűnőben levő változók érvénytelen pointereket jelentenek, amik
elrontják a szemétgyűjtésben levő gráfbejárást. Ha nem használnak saját C
kódot, akkor az alkalmazásoknak ezzel nem kell törődniük, mert ilyen hibát
akármilyen rossz alkalmazáslogika sem okozhat.

A szálbiztonság második kritériuma: a static-ok szinkronizálása. A szálak
által közösen használt static változókat szinkronizálni kell akár C++, akár
CCC szinten. A CCC alapkönyvtárakben levő néhány static változó szinkronizálva
van, a saját static-jaikat viszont az alkalmazásoknak maguknak kell
szinkronizálni.

E kritériumok teljesítése csak a ccc3 és ccc3_ui_ könyvtáraknál kitűzött cél.
Árnyaltan fogalmazva ,,kitűzött", nem pedig elért célról beszélünk.

Szálbiztos a karakteres fullscreen megjelenítő könyvtár (ccc3_uic), ha csak
egy szál foglalkozik a képernyővel.

Szálbiztos a Jáva terminál könyvtár, ha csak egy szál használja a terminált, a
többi szál mással foglalkozik.

Szálbiztos az sql2 könyvtár, ha minden szál külön adatbáziskapcsolaton
keresztül dolgozik.

A különféle interfészek szálbiztonsága attól függ, hogy az adott könyvtár
(amit az interfész közzétesz) szálbiztos-e.

A szálbiztonság ellenőrzésére nincs általános módszer. Egy lehetőség a
hibahalászat. Véletlenszerűen mindenfélét csináló programokat hagyunk futni
napokig, hetekig. Ha a program hibázik, akkor megpróbáljuk behatárolni a
hibát, ami egyáltalán nem könnyű feladat. Képzeljünk el egy olyan hibát, ami
egy folyamatosan futó tesztprogramot átlagosan hetente akaszt meg...
Szerencsére ilyen eset már évek óta nem volt. Mérget azonban nem lehet rá
venni.

##  9.  Unicode<a name="9"></a>

###  9.1.  Unicode támogatás

A régi Clipperben és a CCC1-CCC2-ben nem volt megkülönböztetve a tetszőleges
(akár bináris) adatokat tartalmazó bájtsorozat és a karaktersorozatot
tartalmazó string. Az ilyen típust egységesen karakternek (stringnek)
neveztük, a típus kódja "C" volt. Hasonló volt a helyzet a 2.3 előtti
Pythonban is.

Az idők azonban változnak, igény támadt az egyidejűleg többféle nyelven is
értő programokra. Világossá vált, hogy a többnyelvűség igényeit legjobban a
Unicode elégíti ki, továbbá, hogy a Unicode problémáit (az operációs
rendszerrel való kompatibilitást illetően) legjobban az UTF-8 kódolás oldja
meg. A Unicode/UTF-8 kódolás univerzálisan elfogadottá vált, az operációs
rendszerek sorra áttértek a használatára. A változást a CCC-vel is követnünk
kellett. A CCC3 fő újdonsága a Unicode támogatás.

Az XMLRPC esete mutatja, mennyire elkerülhetetlen a változás követése. Egy
1999-es XMLRPC leírás azt mondja, hogy a `string` adattípusban bámilyen adatot
küldhetünk (binárisat is), csak arra kell ügyelnünk, hogy az XML formázásban
szerepet játszó karakterek/bájtok (`<`, `&`) megfelelően védve legyenek. A pár
évvel ezelőtti XML tankönyvekben fel sem vetődik a kérdés: Miből áll az XML
dokumentum?

  * Bájtok sorozatából, 

  * vagy karakterek sorozatából? 

A mai XML szabvány szerint karakterekből. Az XMLRPC string tehát nem
tartalmazhat bináris adatot, mert akkor elbukik az XML elemzésen. Hogy mik a
karakterek, az sem triviális, pl. a 0x00-0x20 intervallumban csak a TAB, CR,
LF számít karakternek, és máshol is vannak érvénytelen (nem karakter) kódok,
amikre a mai XML elemzők kivételt dobnak.

A Unicode támogatás megvalósítására két út kínálkozott. A Pythonban úgy jártak
el, hogy bevezettek (mint új dimenziót) egy új típust, a Unicodeot, ami minden
mást érintetlenül hagyott. A kompatibilitás szempontjából ez tökéletes
megoldás, azonban semmivel nem visz közelebb a régebbi programok
Unicodeosításához.

A CCC-ben a Jáva mintáját követve radikálisabb utat választottunk. Bevezettünk
egy új típust a bájtsorozatok számára. Ezt bájtarraynek, bájtsorozatnak, vagy
bináris stringnek nevezzük, a típuskódja "X" (sajnos a B betű már foglalt a
kódblokkok számára). A binary string (X) átveszi a régi (C) stringek szerepét,
amikor azok bináris adatot tárolnának. A bináris stringekre működnek a
szokásos string kezelő függvények és operátorok: `at`, `rat`, `strtran`,
`left`, `right`, `padr`, `padl`, `substr`, `+`, `==`, `$`, stb.

A korábbi (C) stringek értelmezése megváltozott, a CCC3-ban Unicode
karaktersorozatot jelentenek. Természetesen az ismert string függvények ezekre
is működnek. A két string fajtát azonban nem lehet keverni, azaz nincs
feltétlen, automatikus konverzió. Érdemes tudni, hogy az egyes karakterek C
szinten `wchar_t` típusban tárolódnak, ami a mai C fordítókban 32 bites
mennyiség.

Nagyon fontos megérteni a karakter string és a binary string közötti
kapcsolatot. A karakter string (Unicode vagy UCS kódok sorozata) szöveget tud
tárolni. Ha a szöveget binary stringbe akarom átírni, akkor előállítom a
Unicode karakterek UTF-8 kódját (karakterenként a karaktertől függő hosszúságú
bájtsorozat), ezeket konkatenálom, az eredmény egy bájtsorozat, amit a szöveg
UTF-8 kódolású bináris reprezentációjának nevezek. Bármely szöveg (karakter
string) ezen a módon infóveszteség nélkül bináris stringre konvertálható, és a
bináris reprezentációból maradék nélkül visszanyerhető. Általában a szöveg
UTF-8 reprezentációja több bájt, mint ahány karakter van az eredeti szövegben.
Ennek oka, hogy pl. a magyar ékezetes betűk vagy a cirill betűk UTF-8 kódja
két bájt. Más karakterek még hosszabbak lehetnek, a létező leghosszabb UTF-8
kód hat bájtos.

Ha a karakter string memóriabeli tárolását vizsgáljuk, azt tapasztaljuk, hogy
sok 0 értékű bájt van benne. Nyilván, ui. az ASCII kódok a 0-127 intervallumba
esnek, azaz egy bájtot foglalnak el, a string azonban 32-bitet használ minden
karakterhez. A Unicode karakter stringekre ezért nem működnek a C könyvtár
hagyományos string kezelő függvényei, amik a 0 bájtot a string végének
tekintik. Ugyanezért nem célszerű egy Unicode stringet bájtonként kiírni egy
fájlba, vagy egy socketba. Ezzel szemben a string UTF-8 reprezentációja
rendelkezik azzal a tulajdonsággal, hogy csakis a 0 Unicodenak felel meg benne
0 bájt. Az UTF-8 bináris string így alkalmas arra, hogy a program ezzel a
típussal adjon meg egy fájlspecifikációt az OS számára, amire a Unicode string
nem felelne meg.

E megfontolásokból adódik, hogy mikor melyik string fajtát érdemes/kell
használni a programokban. Alapszabály, hogy a program szövegeit karakter
stringben tároljuk, és ebben a formában manipuláljuk. Vannak persze esetek,
amikor ettől el kell térnünk.

  * A fájlokból, socketekből általában bájtokat lehet olvasni. 

  * Az operációs rendszer számára UTF-8 kódolással (tehát bináris string formájában) kell megadni a fájlspecifikációkat. 

A koncepció, hogy az alkalmazási programokban minél kevesebbet kelljen
váltogatni a bináris és karakter reprezentáció között, ehelyett a CCC könyvtár
függvényei alkalmas helyen automatikusan elvégzik a konverziót. A
`memoread`-et pl. általában arra használjuk, hogy egy szövegfájlt egy
mozdulattal beemeljünk egy karakterváltozóba. Ezért a `memoread` automatikusan
karakter stringre konvertálja, amit olvas. Néha azonban más kell, pl. amikor
egy png képfájlt olvasunk be, ezért a `memoread` kiegészült egy opcionális
paraméterrel, amivel kikapcsolható ez a konverzió. Ilyenkor a `memoread`
eredménye nem karakter, hanem binary string. Az `fopen` a filénevet UTF-8-ra
konvertálva adja lejjebb a C szintnek. Azokon a helyeken, ahol a stringtípusok
találkoznak, az alkalmazásnak mindenképpen explicite kell konvertálnia, ezért
a programok elkerülhetetlenül bonyolultabbak lesznek, mint a CCC2-ben voltak.

Megemlítendő, hogy a Unicode/UTF-8 kódolás a CCC3-ban kizárólagos. Ezen azt
értem, hogy nincs támogatás semmilyen más kódolásra, pl. Latin-1-re. Ezek a
(hagyományos) kódolások elavultak, és rendkívül megbonyolódik az élet, ha
különféle kódolásokat kell egyszerre kezelni. Mindez azt jelenti, hogy a CCC3
használata során az ember szövegfájljai szépen átkonvertálódnak UTF-8-ra. A
jelen sorokat a CCC3-mal fordított (tehát Unicode-os) z editorral írom, és a
saját terminálomban az angol, magyar és orosz szöveget egyformán helyesen
látom (és tudom gépelni), mint ahogy helyesen látszik a TEX kimentetén és a
böngészőben is. Mindehhez nincs szükség bütykölt fontokra és billentyű
driverekre. Vannak tehát előnyök, amik kárpótolnak a bonyodalmakért. Bízzunk
benne, hogy az UTF-8 kódolás hosszabb nyugvópont lesz a gyorsan változó
informatikában.

###  9.2.  További megfontolások, kompatibilitás

Azt szeretném itt leírni, miért úgy van a Unicode string használat a CCC3-ban,
ahogy van, és hogyan kell választani a karakter és bináris string között.

A 2.4.x Python támogatja a Unicode/UTF-8 kódolást. Próbáljuk ki ezt a Python
programot:

    
    
    #! /usr/bin/env python
    # _*_ coding: UTF-8 _*_
    
    a="öt szép szűzlány őrült írót nyúz"   # bájtsorozat
    u=u"öt szép szűzlány őrült írót nyúz"  # Unicode string
    
    print 
    print a[0:1]
    print a
    print u[0:1]
    print u
    
    

Ha lefuttatjuk a programot, ezt a kimenetet kapjuk:

    
    
    ?
     öt szép szűzlány őrült írót nyúz
    ö 
    öt szép szűzlány őrült írót nyúz
    
    

Az első '?' valójában egy érvénytelen UTF-8 kód, egy fél 'ö' betű! Ebből
következtetek az alábbiakra: Az `a` változóban egy bájtsorozat van, ami UTF-8
kódolással ábrázolja az "öt szép..." szöveget. Az `u` változóban egy (Unicode)
karaktersorozat van, ami ugyanazt a szöveget ábrázolja. Amikor a stringek első
elemét vesszük, akkor az első esetben az első _bájtot_ a második esetben az
első _karaktert_ kapjuk. Mivel az 'ö' betű UTF-8 kódolásban 2 bájton
tárolódik, azért kapjuk a fél 'ö' betűt, ami érvénytelen kód lévén '?'
formában jelenik meg. Ugyanez a program CCC3-ban így néz ki:

    
    
    function main()
    local a:=a"öt szép szűzlány őrült írót nyúz" //bájtsorozat
    local u:="öt szép szűzlány őrült írót nyúz"  //Unicode string
        ? left(a,1)
        ? a
        ? left(u,1)
        ? u
    
    

Itt nem a Unicode stringet jelöljük `u"..."`-val, hanem fordítva, a
bájtsorozatot kell megkülönböztetni `a"..."`-val. Az eredmény egyébként
ugyanaz. A Python és a CCC3 Unicode támogatása közötti eltérés:

A Python a Unicode-dal új területet nyit, de nem lép be erre az új területre.
A programozóra bízza a Unicode stringek bejelölését. A kompatibilitás
szempontjából ez tökéletes megoldás, hiszen a régi programokat egyáltalán nem
érinti. Szerintem azonban döntő hátrány, hogy nem segíti elő az UTF-8
kódolást. Ha pl. egy régi Python programot Latin-1-ről átkonvertálunk
UTF-8-ra, szintaktikailag semmi sem változik, mégis elromlik a program, mert
mint láttuk, megjelennek a félbevágott UTF-8 kódok. Az új programoknál a
Unicode stringek használatát kellene előnyben részesíteni, a Python
megközelítésében mégis ezekhez kell többet írni, mindig jelölgetni kell az
`u"..."` stringeket.

A CCC3 készítésekor először én is hetekig a Python útján haladtam, de egyre
kevésbé tetszett a dolog. Végül úgy döntöttem, hogy áttérek a radikálisabb
megvalósításra: Nem csak létrehozom az új területet, hanem be is lépek rá,
azaz a Unicode string lesz a default. Ugyanez van a Jávában is. A string
literálok Unicode karaktersorozatot jelentenek, emellett használható a
bájtarray, amikor arra van szükség. Utólag biztos vagyok abban, hogy a
Jáva/CCC3 megoldás a jobb, így vannak a helyükön a dolgok, bár elismerem, hogy
ez csak egy szubjektív vélemény.

Még egy fontos kérdés van: Legyen-e feltétlen és automatikus konverzió a
karaktersorozat és a bájtsorozat között? A Pythonban van. Azt írják, hogy a
két típus találkozásánál a bájtsorozat automatikusan a ,,pontosabb" Unicode
sorozatra konvertálódik. Úgy gondolják, hogy a Unicode 32-bites lévén
pontosabb, mint a 8-bites bájt. Ez azonban egy melléfogás. Az UTF-8 kódolással
információveszteség nélkül tárolható bármely Unicode string, fordítva azonban
nem. Ha egy png formátumú képet tartalmazó bájtsorozatot Unicode stringre
konvertálunk, akkor kép elromlik! Tehát a Unicode sorozat egyáltalán nem
,,pontosabb", mint a bájtsorozat, hanem fordítva, de hasznosabb azt gondolni,
hogy más. Ezért a CCC3-ban nincs feltétlen típuskonverzió.

A tapasztalat azt mutatja, hogy az a jó, ha a program a lehető legszélesebb
körben Unicode stringeket használ, és csak akkor tér át bájtsorozatra, amikor
tényleg bináris adatokkal dolgozik.

Amikor olvasunk egy fájlból, azt kell feltételeznünk, hogy bájtokat kapunk.
Még ha tudjuk is, hogy a fájl mit tartalmaz, a POSIX API bájtok olvasásához ad
eszközöket. Ezt a szituációt úgy jellemzem, hogy a kétféle típus találkozik,
és az alkalmazásnak kell eldönteni, hogy legyen-e konverzió, vagy ne. Ilyen a
CCC2-ben nem volt, tehát a CCC3 mindenképpen bonyolultabb lesz, sajnos.

Emlékeztetek rá, hogy a szabvány szerint az XML nem bájtok sorozatából, hanem
karakterek sorozatából áll. Amikor a programok XML dokumentumot cserélnek,
akkor valahogy sorosítani kell a dokumentumot, azaz a karaktereket
bájtsorozatra kell konvertálni, ehhez valamilyen kódolás kell. Az XML szabvány
az UTF-8-at jelöli ki default kódolásnak. Ahogy a CCC3 használja a
Unicode/UTF-8 kódolást, úgy minden magától a helyén van. A `ccc3_jt` könyvtár
Unicode string formájában dolgozik az XML szöveggel, majd közvetlenül küldés
előtt az `str2bin`-nel UTF-8-ra konvertálja. A Jáva XML elemzője a DOM
felépítésekor az UTF-8 kódolású dokumentumot Unicodera konvertálja, a DOM-ból
már Unicode stringeket lehet kiolvasni. Hasonló a helyzet a fordított
irányban. A `ccc3_jt` portolásához ezért lényegében semmit sem kellett
csinálni.

A GTK mindig is UTF-8 kódolással dolgozott, azaz egy editbox szövegét UTF-8
kódolással kell beállítani, és úgy lehet megkapni. A CCC-GTK csatolóba be van
építve, hogy paraméter átadás/átvételkor automatikusan végezze a
Unicode&lt;-&gt;UTF-8 konverziót. A CCC3 program tehát kényelmesen dolgozhat a
Unicode stringekkel.

Vannak függvények, amik természetüknél fogva bináris adatokkal dolgoznak, pl.
`base64_encode`, `base64_decode`, `crypto_md5`, `crypto_sha1`,
`crypto_rand_bytes`, `savescreen`, stb..

A fentiek alapján világos, hogy a CCC3 nem tud kompatibilis lenni a korábbi
verziókkal, ezért a CCC3 nem tudja egyszerűen leváltani a CCC2-t. Képtelenség
minden régi programot egyszerre ,,felhozni" az új verzióra, egyúttal mindent
újratesztelni. Mégha ez lehetséges volna, az sem volna elegendő, ui. a CCC3
kizárólag Unicode/UTF-8 kódolással dolgozik. Ha egy bank adatai Latin-2
kódolásúak, nem valószínű, hogy a kedvünkért hajlandók mindent átkonvertálni
UTF-8-ra.

Érdemes-e esetleg a CCC3-ba beépíteni más kódrendszerek támogatását? A
véleményem határozott nem. Az Unicode/UTF-8 ui. nem arra lett kitalálva, hogy
még eggyel több kódrendszer legyen, amik között ide-oda lehet konvertálgatni.
(Hogy ezzel is több legyen a különböző kódrendszerek miatti szenvedés.) Az
UTF-8 az az univerzális sín, aminek mindent el kell vinnie.

Az ellentmondó szempontok feloldása, hogy a CCC2-t és a CCC3-at is fenn kell
tartani, előreláthatóan még hosszú ideig. A kezelendő adatok kódolása alapján
kell választani egyiket vagy a másikat. Természetesen új projektekhez UTF-8
kódolást és CCC3-at választunk.

###  9.3.  Karakter/binary string literálok

####  9.3.1.  Karakter string

    
    
        x1:="Kázmér füstölgő fűnyírót húz."
        x2:="Копирование и распространение"
    
    

A fenti értékadások szövegének kötelezően UTF-8 kódolásúnak kell lennie,
másképp fordítási hiba keletkezik: `INVALIDENCODING`. Ebből adódóan nem
nélkülözhető az UTF-8/Unicode környezet. A programokat UTF-8 editorral kell
írni (pl. a z-vel), a régi szövegeket át kell konvertálni. A fordító maga nem
konvertál, csak hibát jelez, ha rossz a kódolás. A fordító az UTF-8 kódolású
szövegből előállítja a Unicode karakterek sorozatát, és ez a sorozat (vagyis a
C típusú string) lesz a változók új értéke. C++ szinten a Unicode (UCS)
karakterek `wchar_t` típusban tárolódnak, ami általában 32 bites.

####  9.3.2.  Binary string

    
    
        x:=a"öt szép szűzlány őrült írót nyúz"
    
    

A fenti értékadás eredményeképpen `x` típusa binary string (X), tartalma pedig
a szöveget UTF-8 kódolással reprezentáló bájtsorozat.

###  9.4.  Karakter/binary string függvények

Új függvények:

- **`bin(code)`**
     A `chr(code)` bináris párja. Egy 0-255 közé eső kódból egy bájt hosszú bináris stringet készít.
- **`arr2bin(a)`**
     A korábbi `_arr2chr`-t pótolja. Most nyilván a karakter stringeket is sorosítani kell, az eredmény egy bináris string (bájtsorozat).
- **`bin2arr(x)`**
     `arr2bin(a)` inverze.
- **`str2bin(c)`**
     Előállítja a `c` karakter string UTF-8 kódolású bináris reprezentációját. Ebből információveszteség nélkül visszanyerhető az eredeti string. A bináris reprezentáció sok helyen helyettesítheti is `c`-t.
- **`bin2str(x)`**
     `str2bin(c)` inverze. Tudni kell azonban, ha `x` nem érvényes UTF-8 kódolású szöveget tartalmaz, akkor információ vész el, pl. egy png képfájl elromlik.
- **`split(v,sep)`**
     Helyettesíti a megszűnt `wordlist`-et. Karakteres és bináris stringekre is működik.

Módusult függvények.

- **`chr(code)`**
     Egy 32 bites UCS kódból egy egy karakter hosszú stringet készít.
- **`asc(v)`**
     Ha `v` karakter string, akkor az első karakter UCS kódját adja. Ha `v` bináris string, akkor az első bájt értékét adja.
- **`left(v,n)`**
     Ha `v` karakter string, akkor `v` első `n` karakteréből álló részstringet adja. Ha `v` bináris string, akkor `v` első `n` bájtjából álló bináris részstringet adja. Utóbbi esetben, ha `v` egy szöveg UTF-8 kódolású bináris reprezentációja, akkor ez a tulajdonság elromolhat, amennyiben a `left` elvág egy több bájtos UTF-8 kódot.
- **`len(v)`**
     Ha `v` karakter string, akkor a `v`-ben levő karakterek számát adja. Ha `v` bináris string, akkor a `v`-ben levő bájtok számát adja.
- **`replicate(v,n)`**
     A `v` változó karakter és bináris string is lehet, az eredmény ennek függvényében C vagy X típusú. A rekordbuffereket régen a `space` függvénnyel hoztuk létre. Mivel ennek az eredménye C típus, ez most általában nem jó, helyette ilyesmit írunk: `replicate(x"20",n)`.
- **`fread(fd,@buf,n)`**
     Az `fread` nem karaktereket, hanem bájtokat olvas, ezért `buf`-ot X típusúra _kell_ inicializálni.
- **`fwrite(fd,buf,n)`**
     Az `fwrite` nem karaktereket, hanem bájtokat ír, ezért, ha C típusú `buf`-ot adunk meg neki, azt automatikusan átkonvertálja X típusra `str2bin`-nel.
- **`convertfspec2nativeformat(f)`**
     Az eredményét mindig átkonvertálja binárisra, ui. az operációs rendszernek UTF-8 kódolású fájlspecifikációkat lehet megadni.
- **`hashcode(v)`**
     Karakteres és bináris stringekre is működik.
- **`isalpha(v)`**
     Karakteres és bináris stringekre is működik. C szinten az `iswalpha`, illetve az `isalpha` hívódik meg. Karakter string esetén az ékezetes és cirill betűkre is jó eredményt ad.
- **`qout(c,...)`**
     A karakter stringek kinyomtatás előtt automatikusan átkonvertálódnak UTF-8-ra (vagyis binárisra), ui. az operációs rendszerek ezt értik.
- **`savescreen()`**
     A képernyő bináris stringként mentődik, egy screen cella a korábbiaktól eltérően most 4 bájt, mert UCS kódokat kell tárolni. A függvénycsalád összes tagja ehhez alkalmazkodik.
- **`upper(v)`**
     Karakteres és bináris stringekre is működik. C szinten a `towupper`, illetve a `toupper` hívódik meg. Karakter string esetén az ékezetes és cirill betűkre is jó eredményt ad.
- **`val(x)`**
     Karakteres és bináris stringekre is működik.
- **`valtype(v)`**
     Bináris stringre "X"-et ad.
- **`like()`**
     Karakteres és bináris stringekre is működik.
- **`memoread(fspec [,binopt])`**
     Ha a `binopt` empty, akkor `bin2str`-rel karakterre konvertálja a beolvasott fájl tartalmát. Ez csak akkor jó, ha a fájl UTF-8 kódolású szöveget tartalmaz. Ha egy png képfájlt akarunk beolvasni, akkor azt `binopt:=.t.`-vel tesszük, az eredmény ilyenkor egy bináris string.
- **`memowrit(fspec,v)`**
     Ha `v` egy karakteres string, akkor azt kiírás előtt átkonvertálja binárisra.
- **`inkey() `**
     Az inkey kódok megváltoztak, lásd az `inkey.ch`-t.

###  9.5.  Internacionalizálás

Internacionalizálásnak sok összetevője van, mi itt csak egy dologgal
foglalkozunk: Hogyan lehet többnyelvű CCC programot írni, amiben a string
konstansok egyszerűen cserélhetők különféle nyelvi változatokra. Egy működő
példa található a $CCCDIR/tutor/nlstext directoryban, ezt a példát magyarázom
el részletesen az alábbiakban.

Az nlstext.prg program:

    
    
    static x:=@"Some like it hot"
    
    function main()
        nls_load_translation("nlstext")
        fun()
        ?
    
    static function fun()
    static y:=@'Gentlemen prefer blondes'
    local z:=@"Star war"
        ? x
        ? y
        ? z
        ? @"Matrix"
        ?
    
    

Először is azokat a stringeket, amiket a program különböző nyelvű verzióiban
fordításban akarunk látni, meg kell jelölnünk. Erre szolgál a speciális
`@"..."` szintaktika. A programfordítás idejére beállítjuk az alábbi
környezeti változót:

    
    
    export CCC_NLSTEXT_TAB=$(pwd)/nlstext.tran
    
    

Ennek hatására a `ppo2cpp` fordító kigyűjti nekünk a kukaccal megjelölt
stringeket egy szövegfájlba, esetünkben nlstext.tran-ba:

    
    
    "Some like it hot"<<"" from  ./nlstext.prg  (21)
    "Gentlemen prefer blondes"<<"" from  ./nlstext.prg  (33)
    "Star war"<<"" from  ./nlstext.prg  (34)
    "Matrix"<<"" from  ./nlstext.prg  (39)
    
    

Itt soronként egy stringet találunk. A sor a lefordítandó stringgel kezdődik,
utána jön egy `<<` jel, majd egy üres idézet, ahová a fordítást kell majd
beírni. Az eddigiek azt jelölik, hogy a bal oldali stringet helyettesíteni
fogja a jobb oldalra írt fordítás. A sor végén fel van tüntetve, hogy az adott
string melyik forrásfájl melyik sorából származik. Természetesen, ha a project
sok forrásfájlból áll, akkor az egyes fájlokból jövő járulék halmozódik, ezért
egy nagyobb program esetén ezres nagyságrendű sor lehet az eredmény.

Minden nyelvhez készítünk egy-egy directoryt, esetünkben

    
    
        translation/hu
        translation/ru
    
    

ezekbe átmásoljuk az nlstext.tran egy-egy példányát, ezeken fognak dolgozni a
fordítók. A fordító munkájának eredménye egy ilyen fájl:

    
    
    "Some like it hot"<<"Несколько мужчин любят горячо" from  ./proba.prg  (21)
    "Gentlemen prefer blondes"<<"Господа любят лучше блондинок" from ./proba.prg (33)
    "Star war"<<"Война эвёэд" from  ./proba.prg  (34)
    
    

Ebből a fájlból a `tran2cpp` utility C++ forrást generál, amit lefordítunk, és
dinamikus könyvtárat linkelünk belőle. Elvégezzük ugyanezeket a műveleteket a
magyar változatra is. A dinamikus könyvtárak neve:

    
    
        translation/libnlstext.hu.so
        translation/libnlstext.ru.so
    
    

Természetesen ugyanez megy Windowson is, csak ott dll-eket kapunk.

Namost, ha az nlstext.exe programot egy ilyen scripttel indítjuk:

    
    
    #!/bin/bash
    export CCC_LANG=ru
    export LD_LIBRARY_PATH=./translation:$LD_LIBRARY_PATH
    nlstext.exe
    
    

akkor a program elején található

    
    
        nls_load_translation("nlstext")
    
    

függvényhívás (amiről eddig nem szóltunk) a `CCC_LANG` változó értékéből és a
paraméterként kapott "nlstext" szövegből összerak egy könyvtárnevet, és a
könyvtárat megpróbálja betölteni. Ha ez a betöltés sikeres, akkor a program a
`@"..."` stringek helyett azok fordításait fogja megjeleníteni. Ha a
fordításkönyvtár dinamikus betöltése nem sikeres, vagy a könyvtár nem
tartalmaz fordítást egyik vagy másik stringre, attól még működni fog a
program, csak ekkor a fordítással nem rendelkező stringek eredeti szövege
jelenik meg.

##  A.  Régebbi dokumentációk<a name="A"></a>

Összegyűjtöttem és belinkeltem néhány régről meglevő dokumentációt.

###  A.1.   [Eredeti Clipper doksi](http://ccc.comfirm.hu/pub/ng)

Még mindig használható az eredeti [ Clipper 5.x dokumentációjának
HTML](http://ccc.comfirm.hu/pub/ng) változata. Persze tudni kell, mik az
elavult, és a még mindig érvényes szakaszok.

  * [Functions](http://ccc.comfirm.hu/pub/ng/Clipper-guide/ng3ca.html)

A dBase adatbáziskezeléssel kapcsolatos függvények a CCC-ből hiányoznak. Pl.
az `asize()` leírása érvényes, de `dbdelete()` nincs.

  * [Commands](http://ccc.comfirm.hu/pub/ng/Clipper-guide/ng6fdf7.html)

A dBase adatbáziskezeléssel kapcsolatos parancsok a CCC-ből hiányoznak.
Vannak: `?`, `??`, `@...box`, `@...clear`, `@...get`, `@...say`, `copy file`,
`erase`, `keyboard`, `quit`, `rename`, `run`, `set...`, és talán még egyebek
is, nem emlékszem mindenre.

  * [Classes](http://ccc.comfirm.hu/pub/ng/Clipper-guide/ngb495e.html)

A régi Clipperben csak ez a négy előre beépített objektum létezett, ezek a
CCC-ben is megvannak. A CCC egyik nagy vívmánya, hogy komplett
objektumrendszer került bele.

  * [Statements](http://ccc.comfirm.hu/pub/ng/Clipper-guide/ngb4a83.html)

Vannak: `begin sequence`, `do case`, `do while`, `for`, `function`, `if`,
`local`, `static`, `return`. Innen meg lehet tanulni, hogyen kell `if`
szerkezetet vagy `for` ciklust írni. A `begin [sequence]` utasítás (vagyis a
kivételkezelés) lényegesen bővült. A CCC-ben a Jávához hasonló kivételkezelés
van.

  * [Operators](http://ccc.comfirm.hu/pub/ng/Clipper-guide/ngc8ba2.html)

A `&` (makró) és az `=` kivételével minden megvan a CCC-ben is.

  * [Directives](http://ccc.comfirm.hu/pub/ng/Clipper-guide/ngd8973.html)

Az `#error` és `#stdout` kivételével minden.

  * [Get System](http://ccc.comfirm.hu/pub/ng/Clipper-guide/nge36fa.html)

Ezek vannak: `getactive()`, `getapplykey()`, `getpostvalidate()`,
`getprevalidate()`, `getreader()`.

###  A.2.   [CCC projekt manager](http://ccc.comfirm.hu/ccc3/build.html)

###  A.3.   [Jáva terminál](http://ccc.comfirm.hu/ccc3/jterminal.html)

###  A.4.   [SQL2 interfész](http://ccc.comfirm.hu/ccc3/sql2.html)

###  A.5.   [GTK interfész](http://ccc.comfirm.hu/ccc3/cccgtk.html)


