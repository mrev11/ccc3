
# Programkészítés a Build-del

_Dr. Vermes Mátyás_

1999\. július - 2003. szeptember - 2017. január

<!---
Megjegyzés: Az '\' nélküli  "1999. július" lista item volna!
--->


[1  Áttekintés](#attekintes)  
[2  Implicit fordítási szabályok](#implicit)  
[3  Build programtípusok](#tipusok)  
[4  Alapvető üzemmódok](#mode)  
[4.1  Egyetlen exe (`-x`) üzemmód](#mode_exe)  
  [4.2  Könyvtár (`-l`) üzemmód](#mode_lib)  
  [4.3  Osztott könyvtár (`-s`) üzemmód](#mode_so)  
  [4.4  Minden main-ből exe (alapértelmezett) üzemmód](#mode_def)   
[5  Paraméter referencia](#param)  
  [5.1  Kapcsolók](#param_opt)  
  [5.2  Build környezeti változók](#param_env)  
  [5.3  Könyvtár és include környezeti változók](#param_inc)  
[6  Példa](#pelda)  


##  1.  Áttekintés<a id="attekintes"></a>

A CCC programok a Build projekt-generátorral készülnek. Build kielemzi a
forráskönyvtárakban talált programokat, megállapítja, hogy azokból milyen 
lib-eket és exe-ket lehet csinálni. Összeveti a források, objectek, lib-ek, exe-k
dátum/idejét, és elvégzi a szükséges fordítást, linkelést. Build ismeri és
kezeli az összes olyan forrástípust, ami a CCC környezetben eddig előfordult:
prg, mnt, msk, pge, c, cpp, lem, lex, stb., így nemcsak Clipper programok
fordítására képes, hanem pl. lemon és lex programokhoz is megfelel. Valójában a
Build olyankor is jó szolgálatot tesz, amikor egyáltalán nincs a projektben
Clipper nyelvű program. Az egész CCC futtatórendszer, könyvtárak, utilityk
(köztük maga a Build) fordítását is a Build vezérli.

> Az egyszerű használathoz nem szükséges tudni róla, de megemlítem, hogy 
> a Build újabb változata párhuzamosítja a fordítási müveleteket, így a most 
> elterjedt többmagos gépeken a nagy projektek fordítása lényegesen felgyorsult.

A támogatott platformokon (Windows, Linux, BSD, Solaris)
ugyanazt a makerendszert használjuk. Platformváltáskor nincs szükség
a források konverziójára, hanem egyszerűen átmásoljuk a projektet tartalmazó
directory struktúrát egyik gépről a másikra. A Build nem keveri össze
különböző fordítókkal készített, különböző platformra szánt binárisokat.



##  2.  Implicit fordítási szabályok<a id="implicit"></a>

Build a forrásprogramok elemzésével megállapítja, hogy azok milyen
összefüggésben vannak egymással, melyikből lesz object, melyik inkludálja
valamelyik másikat, stb., és a fájlidők alapján eldönti, hogy milyen
fordítási műveleteket kell végrehajtani. Ha Build úgy látja, hogy egy `msk`
fájlból elő kell állítani a `say`-t, akkor végrehajtja az `msk2say.bat` scriptet.
Általában is minden fájltípust a fájl kiterjesztése alapján azonosítunk, és
minden fordítási művelethez tartozik egy batch fájl, aminek a nevét az előbbi
példa mintájára képezzük: `prg2obj.bat`, `cpp2obj.bat`, `obj2lib.bat`, stb.. 
Ezáltal a Build működése éppen olyan, mint ahogy a make utility alkalmazza az 
implicit fordítási szabályokat. A szabályokhoz tartozó tevékenységet azonban nem a
makefájlban adjuk meg, hanem az iménti batch scriptekben.

A Build programnak paraméterként kell megadni, hogy hol keresse az adott
platform `xxx2yyy.bat` alakú scriptjeit. A különböző platformokhoz különböző
script készleteket csinálunk, és ezzel elfedjük a platformok közti
eltéréseket.


##  3.  Build programtípusok<a name="tipusok"></a>

A Build-et általában nem indítjuk közvetlenül, hanem olyan scripteken
keresztül, amik megfelelő paraméterezéssel előkészítik Build-et egy-egy
programtípus fordítására. Ezek a scriptek a `$CCCDIR/usr/bin/$CCCUNAME`
könyvtárban találhatók. 


#### A Windowson használható scriptek:


<table>
<tr><td> bapp_w320.bat       </td><td> Windows, CCC könyvtár nélkül                 </td></tr>
<tr><td> bapp_w32_.bat       </td><td> Windows konzol, képernyőkezelés nélkül       </td></tr>
<tr><td> bapp_w32c.bat       </td><td> Windows, karakteres (fullscreen) képernyő    </td></tr>
<tr><td> bapp_w32c_btbtx.bat </td><td> Windows, karakteres képernyő, BTBTX adatbázis</td></tr>
</table>

  
#### A Linux, BSD, Solaris platformon használható scriptek:

<table>
<tr><td> bapp_unix0.b        </td><td> UNIX, CCC könyvtár nélkül                    </td></tr>
<tr><td> bapp_unix_.b        </td><td> UNIX konzol, képernyőkezelés nélkül          </td></tr>
<tr><td> bapp_unixc.b        </td><td> UNIX, karakteres (fullscreen) képernyő       </td></tr>
<tr><td> bapp_unixc_btbtx.b  </td><td> UNIX, karakteres képernyő, BTBTX adatbázis   </td></tr> 
</table>
  
<!---
A dinamikus megjelenítés választás azt jelenti, hogy a program elinduláskor
felderíti (tipikusan környezeti változók alapján), hogy milyen megjelenítéssel
(grafikus vagy karakteres) kell működnie.
--->

A _CCC könyvtár nélkül_ esetben a Build nem linkeli be a projektbe
a CCC könyvtárakat, azaz nem linkelődik be a CCC futtató rendszer, a veremgép,
a szemétgyűjtés, stb.. Ezen a módon tudunk közönéges C++, C programokat
készíteni.

A _konzol, képernyőkezelés nélkül_ esetben egyszerű parancssoros program készül.
A programok  az stdin-t olvassák, az stdout-ot vagy az stderr-t írják, mindezek
a megszokott módon átirányíthatók.

A _karakteres (fullscreen) képernyő_ esetben a programnak ugyanúgy megvan
a lehetősége az stdin, stdout, stderr olvasására/irására, de ezenkívül
rendelkezik egy ablakkal, amiben fullscreen karakteres műveleteket
tud végezni, úgymint: pozícionált írás, savescreen, restscreen.

> Megemlítendő, hogy az előbbi ablak megjelenítését nem maga a CCC program
> végzi, hanem a _CCC terminál_ (egy külön program). A CCC program és a terminál 
> TCP kapcsolaton keresztül kommunikálnak. Ez a szétválasztás lehetővé teszi,
> hogy a programfutás és a megjelenítés helyileg elkülönüljön: a szerver és a 
> terminál-kliens máshol legyen. Emellett a szerver és a kliens platformja is
> eltérhet, pl. Linux szerverhez használhatunk Windows klienst.
> Tulajdonképpen tehát a "rendelkezik egy ablakkal" helyett pontosabb volna azt
> írnunk, hogy rendelkezik egy hálózati kapcsolattal, amin keresztül vezérel
> egy programot, ami a karakteres megjelenítést végzi. 



A felsorolás közel sem teljes. A minták alapján könnyen lehet készíteni
további variációkat, emellett a Build egy adott programtípuson belül,
alkalmazás szinten is rugalmasan paraméterezhető, ahogy azt a következőkben
látni fogjuk.


##  4.  Alapvető üzemmódok<a id="mode"></a>

Build legegyszerűbb használata esetén az aktuális directoryban található
forrásprogramokból készít exe, lib és so fájlokat. A programnak négy üzemmódja
van, amit az `-x`, `-l` és `-s` kapcsolókkal, illetve ezek elhagyásával lehet
beállítani.

###  4.1.  Egyetlen exe (`-x`) üzemmód<a id="mode_exe"></a>

Példa: 

    bapp_unix_.b -xpelda

Ez a parancs arra utasítja Build-et, hogy a `pelda.prg` forrásprogramból hozza
létre `pelda.exe`-t úgy, hogy az aktuális directoryban lévő többi forrást
szintén fordítsa le, és az objecteket linkelje az exe-hez. Részletesebben a
következők történnek.

  * Build megvizsgálja, hogy van-e az aktuális directoryban `pelda.prg`, 
    és hogy az tartalmaz-e `function main`-t, ha nem, akkor hibát jelez, 
    ha igen, akkor beveszi a projektbe. 

  * Build az aktuális directory összes többi prg fájlját megvizsgálja, 
    és azokat, amik nem tartalmaznak `main`-t hozzáveszi a projekthez. 
    Ezek szintén le lesznek fordítva, és hozzá fognak linkelődni `pelda.exe`-hez. 

  * A projektbe bevett prg-ket Build megvizsgálja abból a szempontból is, 
    hogy milyen `#include` direktívákat tartalmaznak. Ha az inkludált fájl 
    megtalálható, vagy az implict fordítási szabályok alkalmazásával valamely
    más fájlból előállítható, akkor azt is beveszi a projektbe, és hozzáveszi 
    a modul függőségi listájához. 

  * Végül a projekthez hozzáveszi az összes c, cpp, lem, lex programot is,
    valamint ezek `#include`-jait. 
    Minden olyan forrásprogramot felhasznál, amihez talál fordítást
    végző (vagyis implicit fordítási szabályt tartalmazó) batch fájlt.

<!--- Régeb ez állt itt:
      "A nem prg típusú források #include-jait Build nem vizsgálja."
      Ez megváltozott, minden elsődleges forrásban keres, elsődleges
      forrás az, amiből object készül, azaz van hozzá xxx2obj.bat. --->

Mint látjuk Build az aktuális directory minden szóbajövő programját
felhasználja `pelda.exe` elkészítéséhez.

###  4.2.  Könyvtár (`-l`) üzemmód<a id="mode_lib"></a>

Példa: 

    bapp_unix_.b -lpelda

Ez a parancs arra utasítja Build-et, hogy készítse el `pelda.lib`-et, amibe 
be kell venni az aktuális directory minden olyan forrásprogramját, ami nem
tartalmaz `function main`-t, ezenkívül az összes olyan prg-ből, ami main-t
tartalmaz készítsen exe programot az előbbi lib hozzálinkelésével. A prg-k
`#include`-jait most is vizsgálja Build, és lehetőség szerint beveszi őket a
projekt függőségi listáiba. A -l üzemmód még az -x-nél is mohóbb, az összes
forrást így vagy úgy felhasználja, hogy programot készítsen belőle.

###  4.3.  Osztott könyvtár (`-s`) üzemmód<a id="mode_so"></a>

Példa: 

    bapp_unix_.b -spelda

Ez az üzemmód UNIX-on alkalmazható, annyival több a `-l` módnál, hogy elkészül
a könyvtár osztott változata (so) is.

###  4.4.  Minden main-ből exe (alapértelmezett) üzemmód<a id="mode_def"></a>

Példa: 

    bapp_unix_.b

Ha az előbbi `-x`, `-l`, `-s` kapcsolók egyikét sem alkalmazzuk, akkor Build
az aktuális directory minden main-t tartalmazó programjából exe-t készít,
amihez hozzálinkeli az összes többi programból készített objectet anélkül,
hogy azokból könyvtárat készítene.

A projektek (könyvtárak, végrehajtható programok) tartalmát a források
megfelelő csoportosításával kell szabályozni. Például, ha nem akarjuk
letörölni egy forrás elavult változatát, de az sem jó, ha jelenlétével zavarja
Build működését, akkor egyszerűen félre kell rakni egy alkönyvtárba. A fent
ismertetett négy üzemmód az alkalmazási programok 90%-ában elegendő. A
bonyolultabb esetekben segítenek az alább ismertetett kapcsolók.


##  5.  Paraméter referencia<a id="param"></a>

###  5.1.  Kapcsolók<a id="param_opt"></a>

- **`-xExeName`**
     ExeName az elkészítendő program neve (lásd fenn).

- **`-lLibName`**
     LibName az elkészítendő könyvtár neve (lásd fenn).

- **`-sLibName`**
     LibName az elkészítendő osztott könyvtár neve (lásd fenn).


- **`-dSrcDir`**
     SrcDir azon directoryk listája, amikben Build a lefordítandó 
     forrásmodulokat keresi. A lista a `,; ` karakterekkel lehet elválasztva. 
     A parancssorban több `-d` paraméter is meg lehet adva, ekkor ezek tartalma 
     összeadódik (additív). Ha `-d` meg van adva, az aktuális directoryban csak 
     akkor keres a program, ha az explicite fel van sorolva, 
     pl. `-d.;srcprg;srccpp`. Ha `-d` nincs megadva, akkor a program csak 
     az aktuális directoryban keres, ami a `-d.` paraméterezéssel egyenértékű. 
     A `-d`-ben felsorolt directorykban Build automatikusan keresi az inkludálandó 
     fájlkokat is, ezért ezeket nem kell a `-i`-ben is megadni.

- **`-mMain`**
     Az `-m` kapcsolóval lehet felsorolni a főprogramot tartalmazó forrásmodulokat. 
     A main modulok listája a `,;` karakterekkel lehet elválasztva. A kapcsoló additív. 
     Az `-m` kapcsolót akkor használjuk, ha a main függvény nem prg típusú forrásban van. 
     Ezzel Build nem Clipper nyelvű programok fordítására is használható. 
     A ppo2cpp program pl. cpp, lem és lex típusú forrásokból készül, azaz egyáltalán 
     nincs is a projektben prg.


- **`-iIncDir`**
     Az include directoryk listája adható meg az `-i` kapcsolóval. 
     A C fordító saját könyvtárait nem itt szoktuk megadni, hanem a fordító 
     konfigurálásánál,  tipikusan az `INCLUDE` környezeti változót 
     szokták erre használni. A lista `,;` karakterekkel szeparálható, 
     a kapcsoló additív. Nem kell olyan directoryt megadni, ami `-d`-ben már szerepelt.


- **`-pLibPath`**
     Azon directoryk listája adható meg a `-p` kapcsolóval, ahol a linker 
     a CCC könyvtárakat keresi. A C fordító saját könyvtárainak helyét nem itt 
     szoktuk megadni, hanem a `LIB` környezeti változóban. A lista `,;` karakterekkel 
     szeparálható, a kapcsoló additív.


- **`-bLibFile`**
     A linkelendő könyvtárak nevét tartalmazó lista. 
     A lista `,;` karakterekkel szeparálható, a kapcsoló additív.

- **`-hHelp`**
     Listát ad az érvényes kapcsolókról.

- **`name=value`**
     A `name=value` paraméter hatására a Build futása alatt a `name` környezeti 
     változó értéke be lesz állítva `value`-ra. Build-et egy sereg `BUILD_XXX` alakú 
     környezeti változóval is paraméterezhetjük. A Build a fordítást 
     végző `xxx2yyy.bat` scriptekkel szintén ilyen alakú környezeti változókon 
     (és paramétereken) keresztül kommunikál. Ez a paraméter megadási forma 
     lehetővé teszi, hogy Build környezeti változóit az operációs rendszertől 
     független szintaktikával állítsuk be.

- **`$(name)`**
     Ha Build a parancssorában `$(name)` alakú kifejezést talál, 
     azt helyettesíti a `getenv(name)` értékkel. Ez lehetővé teszi, 
     hogy a környezeti változó értékét az operációs rendszertől független 
     szintaktikával kapjuk meg.

- **`@parfile`**
     Parfile egy tetszőleges paraméterfájl, amiben a fent leírt paramétereket 
     helyezhetjük el. A paramétereket a fájlban újsor karakterrel választjuk el. 
     A parancssor és a paraméterfájl olvasása folytatólagos, 
     pl. lehet több paraméterfájl is a parancssorban.


###  5.2.  Build környezeti változók<a id="param_env"></a>

- **`BUILD_BAT`**
     Implicit szabályokhoz rendelt batch scriptek directoryja.

- **`BUILD_CPP`**
     Egy directory, ahol a rendszer a C++ kódot gyűjti abból a célból, 
     hogy installáló készletet lehessen előállítani belőle.

- **`BUILD_DBG`**
     Ha e változó értéke `on`, akkor Build kiírja a projekt függőségi listáit, 
     és megmutatja a fájlok időbeli viszonyait.

- **`BUILD_EXE`**
     Az exe directory specifikációja, ide teszi Build az elkészült exe-ket, 
     defaultja az aktuális directory.

- **`BUILD_INC`**
     A statndard include directoryk listája.

- **`BUILD_LEX`**
     A Flex-nek átadott kapcsolók.

- **`BUILD_LIB`**
     A standard libraryk listája.

- **`BUILD_LPT`**
     A standard library path.

- **`BUILD_OBJ`**
     Az aktuális object directory neve (a különböző platformú binárisokat 
     ui. szét kell választani). Főleg könyvtár specifikációban használjuk 
     "átnyúlkálós" linkeléskor. 

- **`BUILD_OPT`**
     A `$CCCDIR/usr/options/$CCCBIN` directoryban található, 
     standard C++ fordítás opcióit tartalmazó fájl neve.

- **`BUILD_PRE`**
     A prg2ppo preprocesszornak átdott paraméterek.

- **`BUILD_SRC`**
     Ha ebben a változóban megadunk egy directoryt, 
     akkor Build a forrásdirectory paramétereket (`-d`) erre a directoryra 
     relatívan értelmezi.

- **`BUILD_SYS`**
     Subsystem azonostó. Tartalma platformfüggő.


###  5.3.  Könyvtár és include környezeti változók<a id="param_inc"></a>

Külön kell szólni a `BUILD_INC`, `BUILD_LIB`, `BUILD_LPT` változókról.

Build összegyűjti az include és library paramétereket, és elhelyezi egy-egy
környezeti változóban úgy (blank elválasztó), hogy később batch fájlból
shiftekkel könnyen fel lehessen dolgozni. A használt környezeti változók:

**`BUILD_INC`**:
     `-d` \+ `-i` kapcsolók tartalma + `$(BUILD_INC)` \+ `$(INCLUDE)`

**`BUILD_LPT`**:
     `-p` kapcsoló tartalma + `$(BUILD_LPT)` \+ `$(LIB)`

**`BUILD_LIB`**:
     `-b` kapcsoló tartalma + `$(BUILD_LIB)`


Ebből megállapítható a különböző szinten előírt paraméterek közötti
összefüggés.

  1. A kapcsolók szintjén adjuk meg a projekt specifikus paramétereket. 

  2. A `BUILD_XXX` változók szintjén adjuk meg egy-egy programtípus 
     standard paramétereit.  Pl. a CCC könyvtárak is így vannak megadva. 
     Ezeket a paramétereket projekt szinten nem tanácsos piszkálni. 
     Ugyancsak ezen a szinten állítunk be olyan paramétereket, 
     amiknek a használata nem gyakori, pl. `BUILD_EXE`, `BUILD_DBG`, 
     `BUILD_LEX`, `BUILD_PRE`. 

  3. Végül az általános környezeti változók szintjén kell magadni a
     fordító normál működéséhez szükséges include és lib directorykat. 



##  6.  Példa<a id="pelda"></a>

Nézzünk egy összetetteb példát. A `CCCDIR/tools/mask/m` script tartalma 
a következő:

    #!/bin/bash
    bapp_unixc.b  -xmask -xpage  @parfile.bld
    bapp_unix_.b  -xmsk2say -xmsk2pge -xpge2wro  @parfile.bld
    
Az inkludált `parfile.bld` tartalma pedig:

    -lmask
    BUILD_EXE=$(CCCDIR)/usr/bin/$(CCCUNAME)


Az `-lmask` opció hatására készülni fog egy könyvtár, amibe belekerül
az aktuális directory minden olyan programja, ami nem tartamaz main-t.

A `BUILD_EXE` változó beállításával megadjuk azt a directoryt, ahová a Build 
a friss exe-ket tenni fogja, jelen esetben a CCC standard bin directoryját.
Enélkül az aktuális directoryban jönnének létre az exe-k. 
A `$(CCCDIR)` és `$(CCCUNAME)` makrókat a Build 
fogja értelmezni.  A Build egyformán megérti a `\` és `/` elválasztó 
karakterrel leírt útvonalakat.



Öt darab exe fog linkelődni. Ezek közül kettő (mask és page) fullscreen
karakteres képernyőkezeléssel működik, másik három (msk2say, msk2pge, msk2wro)
pedig egyszerű parancssoros program lesz.

> Megjegyzés: Ha minden programunk ugyanolyan típusú volna, akkor nem kéne
> megadni a -x opciókat, hiszen a Build maga is ki tudja keresni a főprogramokat.
> A -x-re éppen azért van szükség, hogy a Build ne vegye figyelembe a -x-ben 
> nem felsorolt modulokat. 

A `parfile.bld` paraméterfájlt Windowson sem kell megváltoztatni, 
az `m` script windowsos megfelelője `m.bat`, nagyon hasonló a linuxos változathoz:
    
    @echo off
    call bapp_w32c  -xmask -xpage  @parfile.bld
    call bapp_w32_  -xmsk2say -xmsk2pge -xpge2wro  @parfile.bld
    

Végeredményben két nagyon rövid, egymáshoz nagyon hasonló scriptet kell csak
megírni, ezután bármely platformon az egybetűs `m` parancs hatására elkészül
az adott direktoriban fellelhető összes program. Így működik a Build.
További példák sokasága található a CCC directory struktúrában, ahol minden
projekt, beleértve a runtime libraryk fordítását, a prg forrást egyáltalán nem
tartalmazó programok fordítását a Build-del készül.




