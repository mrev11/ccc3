
# SQL2 1.1 interfész

_Dr. Vermes Mátyás_

2005\. február


[1  Áttekintés](#sec1)  
[2  Kezdőlépések](#sec2)  
[3  Tableentityk használata](#sec3)  
    [3.1  Fogalmak](#sec3.1)  
    [3.2  Tds referencia](#sec3.2)  
    [3.3  Példa egy táblával](#sec3.3)  
    [3.4  Példa több táblával](#sec3.4)  
[4  Osztály referencia](#sec4)  
    [4.1  Sqlconnection osztály](#sec4.1)  
    [4.2  Sqlquery osztály](#sec4.2)  
    [4.3  Sqlsequence osztály](#sec4.3)  
    [4.4  Absztrakt tableentity osztály](#sec4.4)  
    [4.5  Tableentity leszármazottak](#sec4.5)  
    [4.6  Rowset osztály](#sec4.6)  
    [4.7  Rowentity osztályok](#sec4.7)  
    [4.8  Columnref osztály](#sec4.8)  
    [4.9  Columndef osztály](#sec4.9)  
    [4.10  Indexdef osztály](#sec4.10)  
[A  Összetett tranzakciók](#secA)  
[B  Kompatibilitási kérdések](#secB)  
    [B.1  Adatbázis objektum nevek](#secB.1)  
    [B.2  Autocommit, tranzakcióhatárok](#secB.2)  
    [B.3  Tranzakcióhatáron átnyúló fetch](#secB.3)  
[C  Oracle 10g installálása Linuxra](#secC)  
    [C.1  Szerver installálás](#secC.1)  
    [C.2  Kliens installálás](#secC.2)  
[D  Postgres adatbázis készítése](#secD)  

##  1.  Áttekintés<a name="sec1"></a>

Az SQL2 könyvtár szabványosított adatbáziskezelő API-t nyújt CCC programok
számára. A ,,szabványosított" jelző azt jelenti, hogy ugyanaz a program
ugyanazt a működést produkálja több adatbáziskezelővel is. Jelenleg az Oracle
és PostgreSQL adatbáziskezelőket támogatjuk. Koncepciónk
szerint az Oracle-t azoknak az ügyfeleknek szánjuk, akik nem engedhetnek meg
maguknak alacsony költségvetésű projekteket, a Postgrest pedig azoknak, akik
bíznak a szabad szoftverekben. Természetesen ilyen típusú interfész készíthető
volna más adatbáziskezelőkhöz is (DB2, Interbase, stb.).

> Azóta támogatva van az SQLite, MySQL és DB2 is (2017).

A jelen dokumentáció programozóknak szól, számukra leggyorsabban
példaprogramokkal lehet megvilágítani a lényeget. Lássuk tehát a
lehetőségeket: Az alkalmazások egyidejűleg belinkelhetik az Oracle és Postgres
könyvtárat. A két könyvtár párhuzamosan ugyanolyan függvényneveket definiál,
ámde különböző névterekben, ezért a nevek nem ütköznek.

    
    
        con1:=sql2.oracle.sqlconnectionNew()  //sql2.oracle névtér
        con2:=sql2.postgres.sqlconnectionNew() //sql2.postgres névtér
    
    

Most van két adatbáziskapcsolatunk, egy Oracle és egy Postgres. Hogy az
`sqlconnectionNew()` függvény pontosan milyen felhasználóként, hova
jelentkezik be, az pillanatnyilag nem lényeges.

Tételezzük fel, hogy van egy bankszámlákat tartalmazó táblánk, aminek van egy
számlaszám és egy egyenleg oszlopa. Lekérdezzük ezeket az sqlquery
objektummal:

    
    
        q1:=con1:sqlqueryNew("select * from szamla") // Oracle lekérdezés
        ...
        q1:close
    
        q2:=con2:sqlqueryNew("select * from szamla") // Postgres lekérdezés
        while( q2:next )
            ? q2:getchar("szamlaszam"), q2:getnumber("egyenleg")
        end
        q2:close
    
    

Ugyanaz a lekérdezés tableentity objektummal:

    
    
        t1:=szamla.tableEntityNew(con1) // Oracle tábla
        ...
        t2:=szamla.tableEntityNew(con2) // Postgres tábla
        rowset:=t2:select
        while( (rowentity:=rowset:next)!=NIL )
            ? rowentity:szamlaszam, rowentity:egyenleg 
        end
    
    

Új adatrekord létrehozása tableentity objektummal:

    
    
        rowentity:=t2:instance
        rowentity:szamlaszam:="111111112222222233333333"
        rowentity:egyenleg:=0
        rowentity:insert
    
    

Módosítás tableentity objektummal:

    
    
        rowentity:=t2:find("111111112222222233333333")
        if( rowentity!=NIL )
            rowentity:egyenleg+=100
            rowentity:update
        end
    
    

A példában szereplő `szamla.tableEntityNew()` függvény adatbázisfüggetlen,
azaz ilyen objektumgyártó függvényekből bináris könyvtárat lehet létrehozni,
ami minden adatbáziskezelővel működik. Az objektumgyártó függvények kódját
programmal generáljuk a táblák adatbázisfüggetlen XML leírásából.

Mint látjuk az SQL2 interfész két legfontosabb eleme az sqlquery és
tableentity osztályok. Az sqlquery körülbelül azt tudja, mint ami a JDBC 1.0
specifikációban van. A fejlettebb specifikációkkal kapcsolatban a _J2EE
Útikalauz Java Programozóknak_ (szerk. Nyékyné Gaizler Judit, ELTE TTK
Hallgatói Alapítvány, Budapest, 2002) könyv 475. oldalán olvashatjuk:

_,,JDBC 2.1 alap API: Az előző verzióhoz képest már tetszőleges sorrendben
lehet feldolgozni az eredménytáblákat, melyeket már nem csak olvasni, hanem
módosítani is lehet ..."_

Ehhez képest az Oracle szilárdan kitart amellett, hogy a fetch-ek pontosan
egyszer és csakis előre haladhatnak végig az eredménysorokon. A realitáshoz
alkalmazkodva az SQL2 interfészben csak a next metódust implementáltuk
sqlquery-kben és rowset-ekben való pozícionálásra.

Az előbbi könyv 479. oldalán a JDBC továbbfejlesztési terveiről olvashatjuk:

_,,Relációs adattáblák és Java osztályok direkt megfeleltetése: Egy
adattábla minden sora a táblához rendelt osztály egy objektumpéldánya lesz, a
tábla oszlopainak pedig a sorobjektumok adatmezői felelnek meg. A
sorobjektumokkal történő bármilyen manipuláció esetén az azt megvalósító SQL
utasítások a háttérben automatikusan végrehajtódnak. Ilyen típusú API például
a Java Data Objects (JDO) specifikáció."_

A tableentity objektumok is éppen így működnek, csak Jáva helyett CCC
osztályokkal. A connection objektumból kapjuk a tableentity-ket, ezek select
metódusaival a rowset-eket, ezekből a next metódussal a rowentity-ket
(sorokat), amiknek minden oszlophoz van egy metódusuk, amivel kiolvasható,
vagy átírható az oszlop értéke. Ezzel nagyjából pozícionálni tudjuk, hogy mit
is nyújt az SQL2 interfész.

Megemlítem még, hogy a CCC korszerű rétegeivel dolgozunk: névtereket
használunk, a felépítés teljesen objektumorientált.


<!--- 10 év távlatából ez már nem érdekes
#### Verzió

Az SQL2-1.1.x specifikáció a CCC3 környezetre épül. Az implementáció
alkalmazkodik az UTF-8/unicode kódolás követelményeihez.

Változások történtek a tds-ben. Az oszlodefiníciókban az oszlop valódi
tábláját és nevét nem a `t=tabid` és `c=colid` opciókkal adjuk meg, hanem az
új `x=column_expression` opcióval. Ez szükség esetén az
`x=tab_alias.real_column_name` formával pótolja a korábbi `tabid` és `colid`
opciókat, de sokkal használhatóbb, mivel általánosabb SQL kifejezést is
tartalmazhat.

Újabb attribútumok is megadhatók az oszlopdefiníciókban:

  * `d=default_value`

  * `t=tooltip`

  * `l=label`

  * `p=picture`

utóbbi három a táblafüggetlen megjelenítőprogramok érdekében.
--->



##  2.  Kezdőlépések<a name="sec2"></a>

Itt arról lesz szó, hogyan vegyük birtokba az SQL2 szoftvert.

#### Adatbázis szoftver telepítés

Először is kell legyen tesztelésre alkalmas adatbázisszerverünk. A
függelékekben le van írva, hogyan tudunk Linuxon Oracle-t és/vagy Postgrest
installálni. Aki Windowson akar dolgozni, sajnos magára van utalva. Az Oracle-
lel Windowson sem lehet gond, és a Postgres 8.0 már Windowson is megy.

Akinek már eleve van adatbázisszervere, az is nézze meg a függelékeket, ott
ui. az is le van írva, hogy milyen tablespace-t, user-t, schema-t kell
létrehozni az adatbázisban, hogy a demó programok működhessenek. A demó
programok számítanak a `konto` sémára, és elszállnak, ha az nem létezik.

A CCC programokat fordító/futtató gépen szükségünk lesz az adatbáziskezelők
fejlesztő/kliens környezetére is.

  * Oracle esetén, ha ugyanazon a gépen tesztelünk, mint amin az adatbázisszerver fut, 
    akkor ,,magától" van kliens környezetünk is. Egyébként letöltjük és installáljuk 
    az instant-client szoftvert az Oracle-től. Az SQL2 csomag tartalmazza azokat az 
    include fájlokat, amik az Oracle interfész lefordításához kellenek, tehát speciális 
    fejlesztői készletre nincs szükség. 

  * Postgres esetében szükségünk lesz a kliens könyvtárra, ezt Ubuntu Linuxon
    a libpq5 deb csomag tartalmazza. 

#### CCC környezet

Szükségünk lesz a legfrisebb CCC környezetre, ez letölthető a webről:
[https://github.com/mrev11/ccc3](https://github.com/mrev11/ccc3).
A CCC részeként a Flex és Lemon is installálódik a gépünkre,
ügyelni kell, hogy a pathból a CCC változatok kerüljenek elő,
és ne a Linux disztróval esetleg települt más változatok.
A CCC Windowson való (2017-es állapot szerinti) installálása a 
[http://comfirm.hu/pub/ccchome.zip](http://comfirm.hu/pub/ccchome.zip)-ben
van leírva.



#### Fordítás

Le kell fordítani az egész SQL2 projektet. A fenti előkészületek után Linuxon
ez nem lehet probléma, az sql2 directoryban elindítjuk

    
    
        mkall.b
    
    

Ez mindenhova benéz, és elindítja a fordítást végző Build scripteket
(Linuxon). Aki Windowson dolgozik, mkall.b helyett az mkall.bat scriptet
indítsa el. Meggyőződünk arról, hogy a fordítás hibamentes. 


#### Tesztadatok

Az `sql2/test/testdata` directoryban van néhány bt tábla, amik tesztadatokat
tartalmaznak. A tview programmal meg tudjuk nézni ezek tartalmát.

Az `sql2/test/testdata_import` directoryban megtaláljuk a btimport.exe
programot. Ez az előbbi bt táblákat importálja az SQL adatbázis szerverbe:

  * Az `so` script úgy indítja btimport-ot, hogy az egy Oracle adatbázisba tölti a bt táblákat. 

  * Az `sp` script úgy indítja btimport-ot, hogy az egy Postgres adatbázisba tölti a bt táblákat. 

Ha esetleg valami nem működik első kipróbálásra, akkor szükségesnek
mutatkozhat az so, sp, import.b scriptek _elolvasása_. Az áttöltött adatokat
szemügyre vesszük az sqlplus (Oracle), és psql (Postgres) kliens programokból
is.

#### Példaprogramok

Ha már vannak tesztadataink, akkor átfáradunk az `sql2/test/basicdemo`
directoryba. Itt azt fogjuk tapasztalni, hogy a demóprogramok már mind le
vannak fordulva, méghozzá két verzióban:

  * Az `exe-ora` directoryban az Oracle-lel működő programok vannak. 

  * Az `exe-pg` directoryban az Postgreszel működő programok vannak. 

Ez a párhuzamosság érzékeltetni próbálja, hogy ugyanabból a forrásból kétféle
program készül, amik ugyanazt ugyanúgy csinálják, csak az egyik Oracle-en, a
másik Potgresen.

> Azt is megtehetjük, hogy ugyanabba a programba egyszerre
> belinkeljük az Oracle és Postgres interfészkönyvtárat. Ekkor csak egy
> programváltozatunk lesz, aminek parancssori paraméterrel, vagy környezeti
> változóval mondjuk meg, hogy melyik adatbázist használja. Az is lehet, hogy
> egy alkalmazás több adatbázist használ egyszerre, Oracle-t és Postgrest
> vegyesen.


Vannak programok (programcsoportok), amikhez
találunk `s-*` alakú indítóscriptet, más programokat közvetlenül indíthatunk.

- **binarydata.exe**
     Teszteli, hogy a memó mezők képesek-e bináris adatok tárolására.
- **connect.exe**
     Teszteli a bejelentkezést, kiírja a szerver változatszámát.
- **memleak.exe**
     Teszteli, hogy a programból szivárog-e a memória. 
     Az Oracle kliens bizonyos változatai ebből a szempontból hibásak.
- **s-deadlock-detect**
     Demonstrálja a deadlock kezelést.
- **sequence0.exe**
     Létrehoz egy sequence objektumot.
- **sequence.exe**
     Növeli az előző sequence objektumot.
- **s-query-sqlquery**
     Lekérdezés sqlquery objektummal.
- **s-query-tableentity**
     Lekérdezés tableentity objektummal.
- **s-te-demo**
     Különféle lekérdezések és adatmódosítások tableentity objektummal.
- **s-tran-autolock**
     Demonstrálja a konkurrencia kezelést automatikus lockolással.
- **s-tran-manuallock**
     Demonstrálja a konkurrencia kezelést explicit lockolással.

Hangsúlyozom, hogy _a példaprogramok a dokumentáció lényeges részét képezik_.
Sok munkám van abban, hogy a példákból és a közéjük írt megjegyzésekből
megfelelően domborodjon a mondanivaló. A példaprogramokat tehát el kell
olvasni, és ki kell próbálni, miközben a kódot összevetjük az eredményekkel.
Sajnos ez időt és fáradságot igényel.

Felhívom a figyelmet az SQLDEBUG környezeti változóra. Ha ez be van állítva,

    
    
        export SQLDEBUG=on
    
    

akkor az SQL2 interfész listázza az adatbázisszervernek küldött SQL
utasításokat. Ezek vizsgálata rendkívül sokat segít a program működésének
megértésében, a hibák kijavításában.

#### Jáva terminálos browse

A `sql2/test/entitybrowse` directoryban egy olyan demó van, ami Jáva
terminálban browse-ol egy tableentity objektumot. A program nem bonyolult, de
csak akkor fog lefordulni, ha a CCC környezetben van Jáva terminál támogatás,
ezért kezdetben kihagyjuk ennek a projektnek a fordítását.

##  3.  Tableentityk használata<a name="sec3"></a>

###  3.1.  Fogalmak<a name="sec3.1"></a>

#### tableentity

Egy _tableentity_ objektum SQL select utasításokkal készített, azonos
struktúrájú, de különféleképpen szűrt és rendezett eredménytábla halmazt
képvisel. (Másképp: SQL select utasítások, amikben ugyanazt a joint, különféle
where és order by záradékokkal kombináljuk.) Az SQL select tartalmazhat egy
vagy több elemi táblát, vagy nézetet (view-t).

A tableentity objektumnak vannak _select_ metódusai, ezek egy-egy _rowset_
objektumot adnak. A különféle select metódusok különféle szűréseket végeznek,
ennek megfelelően a rowsetek ugyanannak az (esetleg összetett) alaptáblának
különféle részhalmazait tartalmazzák. A rowset objektum next metódusával lehet
megkapni az eredménysorokat, a sorokat rowentity objektum formájában kapjuk.

A tableentity objektumnak van egy _find_ metódusa, ami egy kulcsokkal
maghatározott sort betölt egy _rowentity_ objektumba. (A select speciális
eseteként egyelemű rowsetet állít elő, és az egyetlen elemből rögtön
rowentityt készít.)

#### rowentity

Az adatbázisrekord, vagy select eredménytábla sorának programbeli leképezése a
_rowentity_ objektum. A rowentity objektum a kulcsmezők értékével (primary
key) kapcsolódik a neki megfelelő adatbázis rekordokhoz. A tableentity minden
oszlopához tartozik a rowentitynek egy azonos nevű metódusa, amivel az oszlop
(mező) értéke lekérdezhető, módosítható. A rowentity nem egy rekordpointer
vagy kurzor, hanem önállóan létező objektum. A program ugyananabból a táblából
egyszerre több rowentityt is készíthet, azokat egymástól függetlenül
módosíthatja, tárolhatja, törölheti.

#### rowset

A _rowset_ objektumokat a tableentity select metódusaival kapjuk. Ugyanabból
a tableentity objektumból származó rowsetekben közös, hogy ugyanazokat az
elemi táblákat tartalmazzák, és a táblák ugyanúgy vannak összekapcsolva. A
közös alaptáblából a különféle select metódusok különféle filterezettségű
(where) és rendezettségű (order by) rowseteket adnak, amikből viszont egyforma
struktúrájú rowentityket kapunk. A `rowset:next` metódushívással lehet
megkapni a sorokat. A next a tábla elejétől a végéig haladva egyesével
adogatja a sorokat (rowentityket), ha a sorok elfogytak, akkor NIL-t.
Visszafelé haladni, vagy bármi egyéb módon pozícionálni nem lehet.

#### primary key

A tableenitynek rendelkeznie kell elsődleges kulccsal (primary key). Ez azon
oszlopok felsorolásából áll, amely oszlopok értékének megadásával egyértelműen
azonosítani lehet a sort, azaz a rowentity objektumot. A primary key-ben
felsorolt oszlopoknak nem szabad null értéket megengedni, ezenkívül az
egyediséget unique indexszel ki kell kényszeríteni.

#### columndef

A tableentity oszlopainak megadására columndef objektumokat használunk.

#### columnref

A columnref objektumokat olyan oszlopok leírására használjuk, amik nem
szerepelnek a tableentity oszlopai között, viszont a tableentity valamilyen
módon hivatkozik rájuk egy from, where, vagy order by záradékban.

#### indexdef

Az indexdef objektumokkal indexek leírását közöljük a tableentityvel. A
`tableentity:create` metódus (a tábla kreálása után) létrehozza a megadott
indexeket is. Ha az indexünk unique minősítésű, akkor azzal kikényszeríthetjük
sorok egyediségét, mint ahogy azt a primary key esetében is megtesszük.

Az SQL-ben az indexek léte, nemléte, nem befolyásolja a select utasítások
eredményét, legfeljebb a végrehajtás hatékonyságát. Az adatbázisszerver mindig
saját hatáskörben dönt egy index használatáról, mellőzéséről, sőt
létrehozásáról.

###  3.2.  Tds referencia<a name="sec3.2"></a>

A Table Definition Script (tds) bekezdésekből áll. Minden bekezdés egy sor
elején álló kulcsszóval kezdődik, amit szóköz nélkül kettőspont követ. Az
érvényes kulcsszavak: `name`, `version`, `table`, `join`, `column`, `colref`,
`primkey`, `index`, `select`, `include`, `type`, `comment`. A bekezdések a
következő bekezdésig, vagy a fájl végéig tartanak. A bekezdések sorrendje nem
kötött. Az elemző a comment bekezdéseket kihagyja.

#### name:

Névtér, amibe a tableentityNew() objektumgyártó függvény kerül.

    
    
        name:  multi.level.namespace
    
    

A tds-ből generált tableentityt így tudjuk legyártani:

    
    
        tableentity:=multi.level.namespace.tableentityNew(con)
    
    

#### version:

A bekezdés tartalma egy tetszőleges tartalmú string (idézőjelekkel), amiből a
tableentity objektum version attribútumának értéke lesz.

    
    
        version:  "arbitrary text"
    
    

#### table:

Legalább egy table bekezdésnek kell lennie, ezek alakja:

    
    
        table:  real.qualified.tablename=aliasname
    
    

A script más részeiben a táblára kizárólag az alias névvel hivatkozunk. Ha
nincs megadva join bekezdés, akkor a table bekezdésekben magadott táblák
Descartes-féle szorzata lesz a tableentity alaptáblája. Ha csak egy table
bekezdés van, akkor triviálisan az abban megadott tábla lesz az alaptábla.

#### join:

Opcionális bekezdés. Ha nincs megadva, akkor a táblák Descartes-féle szorzata
lesz az alaptábla. Ha meg van adva, akkor a join bekezdés tartalmából készül a
tableentity által generált SQL select utasítások from záradéka (tehát
lényegében egy from záradékot írunk a joinba). A from záradék SQL-beli
szintaktikájától annyiban térünk el, hogy a táblákra és oszlopokra kizárólag
aliasokkal hivatkozunk. Példa:

    
    
        join: 
            a
            full join b on id_a=id_b
            left join c on name_a=name_c
    
    

#### column:

A legegyszerűbb példa:

    
    
        column: szamlaszam  C24
    
    

A kettőspont utáni _első_ szóközökkel határolt szó egyszerre

  * metódusnév a rowentity objektumokban, 

  * alias név, amivel a tds más részeiben hivatkozunk az oszlopra. 

A _második_ szóközökkel határolt egység a típusleképezés. Ebben azt a típust
kell megadni, amiben a CCC program kéri/adja az oszlop adatait (függetlenül
attól, hogy mi az oszlop tényleges SQL adattípusa). Az érvényes típusok:


<table>
<tr><td>Cw  </td><td>w hoszúságú karakter string                            </td></tr>
<tr><td>Nw  </td><td>w helyiértéken tárolt egész                            </td></tr>
<tr><td>Nw.d</td><td>w helyiértéken tárolt, d tizedesjegyet tartalmazó szám </td></tr>
<tr><td>Nw,d</td><td>w helyiértéken tárolt, d tizedesjegyet tartalmazó szám </td></tr>
<tr><td>D   </td><td>dátum                                                  </td></tr>
<tr><td>L   </td><td>logikai érték                                          </td></tr>
<tr><td>M   </td><td>memó                                                   </td></tr>
</table>


A karakter stringeket C (unicode) típusban, a memókat X (bináris) típusban
kapja a program.

Az oszlopnevet és típust kiegészítő adatok követhetik. A kiegészítő adatok
opcionálisak, és a sorrendjük nem kötött.

#####    `x=column_expression`

Ezzel a formával adható meg az oszlopkifejezés. Ha nincs megadva, akkor maga a
név lesz a kifejezés:

    
    
        column: szamlaszam C24      ;ez a default: x=szamlaszam
    
    

Amikor az oszlopnév nem egyértelmű, megadjuk a minősített nevét:

    
    
        column: szamlaszam C24      x=ugyfszl.szamlaszam
    
    

Megadhatunk kifejezést:

    
    
        column: EGYENLEG   N17.2    (x=napinyito+napitartoz+napikovet)
                                    (l=Aktuális egyenleg)
    
    

Használhatunk SQL függvényeket:

    
    
        column: devnem     C3       x=lower(devnem)
    
    

##### `l=label  `

Beállítja az oszlop label attribútumát. A labelt táblafüggetlen
megjelenítőprogramok kiírhatják oszlopfejlécbe, vagy az adatot megjelenítő
text mező elé.

##### `t=tooltip  `

Beállítja az oszlop tooltip attribútumát (táblafüggetlen megjelenítőprogramok
számára).

##### `p=picture  `

Beállítja az oszlop picture attribútumát (táblafüggetlen megjelenítőprogramok
számára).

##### `d=default  `

Beállítja az oszlop default érték attribútumát. A defaultot nem az interfész,
hanem az adatbázisszerver használja, ezért csak akkor van hatása, ha a
tableentityvel kreáljuk a táblát (tehát ugyanaz a helyzet, mint a not null-
nál).

##### `nn  `

Jelentése not null. Az attribútum az adatbázisszervernek szól. Az interfész
nem tudja kikényszeríteni a not null-t, hiszen az adatbázist mások is
használhatják, nem feltétlenül a mi SQL2 interfészünkön keresztül. Ha viszont
a táblát a tableenity create metódusával hozzuk létre, akkor az oszlop not
null minősítéssel kreálódik, és a szerver biztosítja a not null feltétel
teljesülését.

Az oszlopdefiníció szóközökkel határolt egységekből áll. Ha valamelyik
paraméterérték szóközt tartalmaz, akkor azt zárójelpárral lehet védeni.

    
    
        column: DEVNEM  C3      l=Dev
                                (t=A számla devizaneme)
                                (x=upper( devnem ))
                                (p=@! AAA)
                                nn
    
    

A védelemre alkalmazott zárójelpáron belül lehetnek kiegyensúlyozott
zárójelek. Ha nem kiegyensúlyozott zárójelet tartalmazó szöveget akarunk
védeni, használjunk másik zárójelfajtát: `[]` vagy `{}`.

#### colref:

Lehetnek olyan oszlopok, amikre hivatkozni akarunk a tds-ben, de nem akarjuk
lekérdezni az értéküket. Az ilyenek leírását helyezzük colref bekezdésbe, ami
ugyanolyan, mint a column, kivéve, hogy nincs benne típus információ, és az
opciók közül csak az x (column expression) megengedett.

#### primkey:

A primkey bekezdés kötelező. Benne vesszőkkel elválasztott listában
felsoroljuk azokat az oszlopokat (column bekezdésben definiált alias neveket),
amik egyértelműen azonosítják a rekordokat. Az alkalmazás felelőssége, hogy az
azonosítás, és ezáltal az adatbázis rekord&lt;-&gt;rowentity objektum
megfeleltetés egyértelmű legyen.

    
    
        
        primkey:  column_alias1,column_alias2,...
    
    

#### index:

Az opcionális index bekezdések formája:

    
    
        
        index:  index_name(column_alias1,column_alias2,...) [unique]
    
    

Az index bekezdésekben indexeket definiálhatunk a táblára, ezzel bizonyos
lekérdezéseket gyorsíthatunk, illetve a unique indexekkel kikényszeríthetjük
rekordok egyediségét.

#### select:

Az opcionális select bekezdések első szóközökkel határolt szavából a
tableentity metódusneve lesz.

A metódusnevet követheti a `where` kulcsszó, majd tetszőleges SQL kifejezés,
amit az SQL a where és order by kulcsszavak között elfogad. Az oszlopokra
kizárólag az oszlop aliasokkal szabad hivatkozni. A kifejezés `:1`, `:2`,...
alakú szimbólumokat tartalmazhat, amik helyére az SQL select parancs
generálásakor paramétereket fogunk helyettesíteni.

A where feltételt követheti az `order` kulcsszó, ami után zárójelek között fel
kell sorolni azokat az oszlopokat, amik szerint rendezni akarjuk az
eredménytáblát. A felsorolásban az oszlopnevek után opcionálisan megjelenhet
az asc/desc kiegészítés, ami előírja, hogy az adott oszlop szerint növekvő
vagy csökkenő rendezettséget akarunk.

A where és order záradék közül legalább az egyiknek léteznie kell.

Példa:

    
    
        
        select: select_a
            where col_a_alias like :1
            order(col_a_alias, col_b_alias desc)
    
    

Ezután a `tableentity:select_a("a%")` metódushívás kiválasztja az alaptábla
azon sorait, melyekben `col_a` első karaktere "a", és a sorokat rendezi
`col_a`, majd csökkenő sorrendben `col_b` szerint.

###  3.3.  Példa egy táblával<a name="sec3.3"></a>

Nézzük az alábbi példát az sql2/test/basicdemo/tds/proba.tds-ből:

    
    
    name: proba
    version: "2,2006-07-18"
    
    table: konto.proba=p
    
    column: szamlaszam      C24             nn x=szamla
    column: devnem          C3
    column: nev             C30             x=megnevezes
    column: egyenleg        N17.2           x=osszeg
    column: tulmenflag      L
    column: konyvkelt       D
    column: megjegyzes      M
    
    primkey: szamlaszam,devnem
    
    index: nev(nev,szamlaszam)
    
    select: select_kk  
        where konyvkelt<:1 or konyvkelt is null 
        order(szamlaszam)
    
    select: select_ge  
        where szamlaszam>=:1 
        order(nev desc,szamlaszam)
    
    select: select_tf
        where tulmenflag=:1
        order(szamlaszam)
    
    select: select_bl
        where egyenleg<:1 
        order(szamlaszam)
    
    

Ebből a scriptből a tds2prg kódgenerátorral programot készítünk:

    
    
        tds2prg.exe proba.tds
    
    

Kapunk egy prg-t, amit a szokásos módon befordítunk a programunkba. A prg-ben
van definiálva a `proba.tableEntityNew()` objektumgyártó függvény. Nézzünk
egy-két programozási mintát, mire használható.

Az objektumgyártó egy tableentity objektumot ad, amivel a con
adatbáziskapcsolaton át elérhető konto.proba táblát manipulálhatjuk. A
konto.proba név a tds script table bekezdéséből jön. Valójában nem tudjuk,
hogy a név mögött tábla van-e, vagy view, mert a két eset formailag nem
különbözik. A tábla (view) neve lehet minősített. A jelen esetben a séma neve
(ami a táblát tartalmazza) ,,konto", a tábla vagy view neve ,,proba". A tds
script name bekezdésében egy névtér van megadva, esetünkben ,,proba". Az itt
megadott névtérbe (ami lehetne többszintű is) kerül az objektumgyártó
tableEntityNew() függvény, amit tehát így kell meghívni:

    
    
        tableentity:=proba.tableEntityNew(con)
    
    

A tableEntityNew()-nak van egy második, opcionális paramétere is. Ha ezt
megadjuk, akkor a konto.proba helyett a paraméterként megadott masik.tabla-hoz
kapunk hozzáférést. Tételezzük fel, hogy ennek a másik táblának hasonló
szerkezete van, mint a konto.proba-nak:

    
    
        tableentity:=proba.tableEntityNew(con,{"masik.tabla"})
    
    

A táblanév egy lista (array) elemeként van megadva. Mint később látni fogjuk
egy tds script több táblára is hivatkozhat, tehát több tábla paraméternek is
értelme lehet, ezért a táblákat egy arrayben felsorolva kell megadni.

Ezen a ponton nem tudjuk, hogy az adatbázisban van-e egyáltalán ilyen tábla,
egyelőre csak egy programbeli objektumunk van. Ha emögött még nincs tábla,
akkor most létre tudjuk hozni:

    
    
        tableentity:create
    
    

Ez persze csak akkor értelmes, ha valóban tábláról van szó, nem pedig view-
ról, ui. az interfész mindenképpen egy create table utasítást fog küldeni az
adatbázisszervernek, view-król mit sem tud. Természetesen a konto.proba, vagy
masik.tabla tábla fog kreálódni, ahogy a tableentity gyártásakor paraméterként
megadtuk.

Itt egy kicsit érdemes elidőzni, megtárgyalni, milyen lesz az új tábla.
Általában olyan nevű oszlopok lesznek benne, mint a tds scriptben az oszlopok
neve, de vannak kivételek. A példában van egy ,,nev" nevű oszlop, amiből a
tableentity sorobjektumainak lesz egy ,,nev" nevű metódusa. A táblában azonban
az `x=megnevezes` előírás alapján ennek az oszlopnak az adatbázisbeli neve
,,megnevezes". Nem tudjuk pontosan, hogy mi az oszlopok SQL adattípusa, de
bízhatunk benne, hogy az interfész olyan adattípust választ, ami kompatibilis
a tds scriptben előírt Clipper típussal. A nev esetében sejthető a
varchar(30), de pl. boolean típus egyes adatbáziskezelőkben van, másokban
nincs, ezért nem egyértelmű, mi a Clipper L típus SQL megfelelője. Az nn-nel
jelölt oszlopok not null minősítést kapnak. Az interfész a tábla
elkészítésekor egyúttal indexeket kreál a primkey és index bekezdések szerint.
A unique indexeknek szerepük lehet sorok egyediségének kikényszerítésében.

Kissé más a helyzet, ha az adatbázistáblát nem a tableentity interfésszel
csináljuk, hanem készen kapjuk. A megrendelő bank alapadatait tartalmazó
táblát pl. biztosan nem mi fogjuk kreálni. Ilyenkor egyáltalán nem tudjuk
befolyásolni az oszlopok típusát, azonban az interfész oda-vissza elvégzi az
SQL típus és a Clipper típus közötti konrverziót, ha egyáltalán lehetséges.
Sajnos ilyenkor az egyediséget nem tudjuk indexekkel biztosítani, sem a not
null feltételeket betartatni, ha az eleve nincs benne az adatdefiníciókban.

Ha a táblát meg akarjuk szüntetni, megtehetjük a

    
    
        tableentity:drop
    
    

metódushívással. Ez egy drop table utasítást küld a szervernek, (view-ra
nyilván nem működik).

Térjünk rá az adatok lekérdezésére. A tableentity objektumnak mindig van egy
select metódusa, ami az alaptábla összes sorát tartalmazó rowset objektumot
ad.

    
    
        rowset:=tableentity:select
    
    

A rowset objektum legfontosabb metódusa a next, ezzel egyesével, előrefelé
haladva lekérhetjük a sorokat:

    
    
        while( (rowentity:=rowset:next)!=NIL )
            ...
        end
        rowset:close
    
    

Amíg van újabb sor, addig rowset:next egy rowentity objektumot ad, ha már
nincs több sor, akkor NIL-t. Ügyelni kell a rowset-ek lezárásra, máskülönben
elfogynak bizonyos erőforrások (handlerek).

Most már soraink is vannak, nézzük a mezőértékeket:

    
    
        r:=rowentity
        ? r:szamlaszam, r:devnem, r:nev, r:egyenleg
    
    

Pontosan mit is írtunk ki? A konto.proba.szamla, konto.proba.devnem,
konto.proba.megnevezes, konto.proba.osszeg nevű adatbázismezőket. A rowentity
objektumok tehát olyan attribútumokkal rendelkeznek, mint amilyen oszlopnevek
vannak a tds scriptben. Ha nem intézkedünk másképp, akkor ezek az adattábla
azonos nevű oszlopát jelentik, de ezt felülbírálhatjuk az
`x=valid_sql_expression` előírással.

A CCC programból nézve a rowentity attribútumoknak olyan típusuk van, mint
amit a tds scriptben előírtunk. Pl. az alábbi programrészlet végrehajtása után

    
    
        rowentity:nev:=""
        ? valtype(rowentity:nev), strtran(rowentity:nev," ","x")
    
    

ezt látjuk kiírva: `C xxx...xxx` (30 darab x). Az adatbázisból kaphatunk SQL
null értékeket is. E tekintetben a Clipper hagyományokat követjük, és az
interfésztől a nullok helyén nem NIL-t kapunk, hanem egy megfelelő típusú
empty értéket. Ha mindenképpen szükség van a nullok vizsgálatára, arra is van
mód, lásd a osztály referenciát és a példaprogramokat.

Tegyük fel, hogy van egy '111111112222222233333333' számlaszámú, 'HUF'
devizanemű sorunk a táblában, ezt a

    
    
        rowentity:=tableentity:find({'111111112222222233333333','HUF'})
    
    

metódushívással tudjuk beolvasni. Ha mégsincs sor a megadott számlaszámmal,
akkor tableentity:find NIL-t ad.

A tds scripttől függetlenül a tableentitynek mindig van egy általános select
metódusa, ami az alaptábla összes sorát tartalmazó rowsetet ad, és egy find
metódusa, ami a primary key alapján kiválaszt egyetlen sort. Lehetnek azonban
más select metódusok is, ha definiálunk ilyeneket a tds-ben. A jelen példában
a

    
    
        rowset:=tableentity:select_kk({stod("20000101")})
    
    

metódushívás kigyűjti azokat a sorokat, amikben a könyvelés dátuma régebbi,
mint 2000-01-01, vagy egyáltalán nem volt rajta könyvelés, és ezért a dátum
null. Az interfész a tds-ben megadott where záradékból SQL where záradékot
készít úgy, hogy a select metódus array paraméterében felsorolt értékeket
behelyettesíti az `:1`, `:2`,... szimbólumok helyére. A tds-ben bármit
megadhatunk a where záradék helyén, amit az SQL elfogad a ,,where" és az
,,order by" kulcsszavak között. A tds-beli order záradékból SQL order by
záradék lesz. Az interfész az order zárójelei közötti szöveget egyszerűen a
generált SQL parancs ,,order by" kulcsszava után írja. A gyakorlatban
általában a zárójelek között felsoroljuk az oszlopokat, amik szerint rendezni
akarunk, esetleg az asc/desc módosítással kiegészítve.

Rátérve a módosítások tárgyalására mégegyszer megjegyezzük, hogy nem minden
tábla módosítható. Ha az alaptábla egy view, vagy több táblából képzett join,
akkor a módosítási kísérlet valószínűleg hibát eredményez. Rakjunk most be egy
új sort a táblába:

    
    
        rowentity:=tableentity:instance
        rowentity:szamlaszam:="XXXXXXXXYYYYYYYYZZZZZZZZ"
        rowentity:devnem:="EUR"
        rowentity:egyenleg:=100000
        rowentity:insert
        con:sqlcommit
    
    

A tableentity objektum instance metódusa gyárt nekünk egy üres rowentityt,
amit feltöltünk adatokkal. A rowentity insert metódusa generál egy insert into
utasítást, amivel kiírja a rekordot. A kiírást a commit véglegesíti. Tegyük
fel, hogy ugyanezt a rekordot módosítani kell:

    
    
        rowentity:=tableentity:find({'XXXXXXXXYYYYYYYYZZZZZZZZ','EUR'})
        rowentity:egyenleg+=1000
        rowentity:update
        con:sqlcommit
    
    

Most az interfész generálni fog egy ilyen utasítást

    
    
        update "KONTO"."PROBA" set "OSSZEG"=101000 
        where "SZAMLA"='XXXXXXXXYYYYYYYYZZZZZZZZ' and "DEVNEM"='EUR'
    
    

amivel módosul a rekord. Rendkívül fontos észrevétel, hogy a rowentity
objektum, a primary key oszlopok egyezése alapján találja meg a hozzá tartozó
rekordot. Mi történik akkor a következők után?

    
    
        rowentity:szamlaszam:="valami más érték" //ROSSZ!
        rowentity:update //ROSSZ!
    
    

Így nem az eredeti rekord módosul, hanem a szerver minden olyan rekordot
módosít, aminek a számlaszáma a "valami más érték". Lehet, hogy semmi sem
módosul, lehet, hogy egy olyan rekord, amire nem számítottunk. A tanulság,
hogy a primary key-t alkotó oszlopokat nem módosíthatjuk közvetlenül.
Szerencsére a gyakorlatban erre ritkán van szükség. Ha mégis, akkor ezt
csináljuk:

    
    
        rowentity:=tableentity:find({'XXXXXXXXYYYYYYYYZZZZZZZZ','EUR'})
        rowentity:delete
        rowentity:szamlaszam:="valami más érték"
        rowentity:insert
        con:sqlcommit
    
    

Mivel a két művelet egy tranzakcióban van, nem fenyeget, hogy csak az egyik
hajtódik végre, a másik pedig nem. A példa alapján világos: az alkalmazásnak
létfontosságú, hogy a primary key egyedisége megmaradjon, így az
adatbázisrekordok és a program rowentity objektumai közötti megfeleltetés ne
sérüljön.

A rowentity lényeges tulajdonsága, hogy igazi objektum, nem pedig csak holmi
rekordpointer vagy kurzor. Az objektum az adatait saját memóriabufferben
tárolja, ami nem szűnik meg attól, hogy végrehajtunk egy újabb rowset:next-et,
rowset:close-t, vagy akár con:rollback-et. A program változóiban tárolhatunk
egyidejűleg akárhány rowentity objektumot.

###  3.4.  Példa több táblával<a name="sec3.4"></a>

Ebben az alfejezetben egy olyan példát elemzünk, amiben a tableentity
alaptáblája több elemi tábla összekapcsolásával keletkező join. Az ilyen
tableentity objektumoknak is vannak módosító metódusai (create, drop, zap,
insert, delete, update), ám ezek meghívása nagy valószínűséggel hibát okoz,
erre többet nem is térünk ki. A példa az
sql2/test/basicdemo/tds/probaszerencse.tds-ből való.

    
    
    name: probaszerencse
    version: "2,2006-07-18"
    
    table: konto.proba=p
    table: konto.szerencse=q
    
    join: p left join q on szamlaszam=qszamlaszam
    
    column: szamlaszam      C24         x=p.szamla
    column: devnem          C3
    column: nev             C30         x=megnevezes
    column: egyenleg        N17.2       x=osszeg
    column: tulmenflag      L
    column: konyvkelt       D
    column: megjegyzes      M
    column: kiegdata        C20
    
    colref: qszamlaszam                 x=q.szamla
    
    primkey: szamlaszam,devnem
    
    

Előzőleg a konto.proba nevű táblával dolgoztunk, most ezt kiegészítjük a
konto.szerencse táblával. A két tábla a `szamla` nevű oszlopon keresztül
kapcsolódik. A szerencse nevű táblából a `kiegdata` oszlopot akarjuk
hozzávenni a tableentityhez (nem túl sok, de most nem az a lényeg, hanem maga
az összekapcsolás).

Először is megfigyeljük, hogy a tableentity objektum gyártó függvény most a
`probaszerencse` névtérbe van helyezve, tehát így lehet meghívni:

    
    
        tableentity:=probaszerencse.tableEntityNew(con)
    
    

Látjuk, hogy a tds-ben két table bekezdés is van. Ezek megadják az alapesetben
használt táblákat, és azok alias neveit (p és q). A script más részeiben a
táblákra kizárólag az alias nevekkel hivatkozunk.

Tudjuk, hogy szükség esetén a tds-ben meghatározott táblákat helyettesíthetjük
más táblákkal, például:

    
    
        tablist:={"masik.proba","masik.szerencse"}
        tableentity:=probaszerencse.tableEntityNew(con,tablist)
    
    

A helyettesítendő táblákat utólag is megadhatjuk:

    
    
        tableentity:=probaszerencse.tableEntityNew(con)
        tableentity:tablist:={"masik.proba","masik.szerencse"}
    
    

A két módszer ugyanarra az eredményre vezet.

A table definition script (tds) join bekezdésében határozzuk meg, hogyan
legyen a két tábla összekapcsolva. Ha ugyanezt a joint közönséges SQL-ben
akarnánk megcsinálni, pl. az sqlplus-ban, akkor valami ilyesmit írnánk
(rövidítésekkel):

    
    
        select 
            p.szamla,
            devnem,
            ...
            kiegdata 
        from 
            konto.proba p 
            left join konto.szerencse q 
            on p.szamla=q.szamla 
        order by   
            p.szamla,devnem
    
    

Koncentráljunk a from záradékra. A tds-beli join bekezdés úgy vezethető le az
SQL from záradékból, hogy a redundáns információt kihagyjuk. A `konto.proba p`
helyett a tds joinban csak annyit írunk: `p`, hiszen a table bekezdésből már
tudjuk, hogy a p alias név a konto.proba táblát jelenti. A `p.szamla` helyett
azt írjuk `szamlaszam`, a `q.szamla` helyett pedig `qszamlaszam`, mert a
column és colref bekezdések meghatározzák, hogy ezek a nevek pontosan melyik
oszlopot jelentik. Látható a column bekezdések kettős szerepe. Egyrészt
metódusneveket jelentenek, másrészt oszlop alias neveket hoznak létre, amiket
a tds scriptben használunk. A colref bekezdéseknek csak oszlop alias szerepe
van. Foglaljuk össze a table és join bekezdésekkel kapcsolatos tudnivalókat:

1) A table bekezdések sorolják fel a tableentityben szereplő elemi táblákat.
Minden táblához rendelünk egy alias nevet.

2) A join bekezdés opcionális (ha csak egy tábla van, akkor a joinnak nem is
volna értelme). Ha nincs join, akkor a tableentity alaptáblája az elemi táblák
Descartes-féle szorzata, vagyis ilyenkor az interfész olyan SQL select
parancsot generál, aminek a from záradékában egyszerűen fel vannak sorolva a
táblák.

3) Ha van join bekezdés, akkor oda egy SQL select from záradékot írunk azzal
az eltéréssel, hogy a táblanevek helyett tábla aliast, az oszlopnevek helyett
pedig mindenhol oszlop aliast írunk.

Az a fajta from záradék, amit itt használunk az SQL92 szabvánnyal került be az
SQL-be. Korábban csak az ún. inner join volt ismert (a where záradékban). Az
újabb szabvány kiegészült az outer joinnal, és a különféle joinok összes
variációinak egységes értelmezésével, de ezeket a from záradékba kell írni.
Sajnos ebben a dokumentációban nincs hely az SQL mélyebb ismertetésére.

Folytassuk az oszlopokkal. Az első column bekezdésben ezt látjuk:

    
    
        column: szamlaszam      C24     x=p.szamla
    
    

Szó volt már a `szamlaszam` név szerepéről. A tableentityből származó
rowentity (sor)objektumoknak lesz egy ilyen nevű attribútuma, egyúttal bevezet
egy oszlop aliast, amivel a tds-ben bárhol (join, where, order) hivatkozni
tudunk az oszlopra.

A `C24` típus értelmezése: Nem érdekel minket, hogy az adott oszlop SQL
adattípusa pontosan micsoda. Akármi is az SQL adattípus, a mi programunk
C24-re konvertálva kéri az adatot a szervertől. Mármost a tényleges típus és a
szerver tudása dönti el, hogy ez az esetleges konverzió értelmes-e,
lehetséges-e egyáltalán. Ha nem értelmes, vagy nem lehetséges, akkor az az
alkalmazás logikai, vagy közvetlen futási hibáját fogja okozni.

A `x=p.szamla` kiegészítő adat azt mondja: A `szamlaszam` metódusnévhez és
oszlop aliashoz a `p` alias névvel azonosított tábla `szamla` oszlopa
tartozik. Ha ez nem volna megadva, akkor az interfész és az adatbázis szerver
`szamlaszam` nevű oszlopot keresne, és hibához vezetne, ha az adott oszlop nem
pontosan egy táblában volna megtalálható (esetünkben két táblában is van
ilyen).

A column adatok sorrendjéről tudni kell, hogy a kettőspont utáni első
szóközökkel határolt szó kötelezően az alias név, a második szó kötelezően a
típus, a további adatok opcionálisak, és sorrendjük tetszőleges.

A colref bekezdésekkel olyan oszlopokhoz készítünk oszlop aliast, amiket nem
akarunk bevenni a tableentity alaptáblájába, de hivatkoznunk kell rá a join-
ban, where-ben, vagy order-ben. A colref szintaktikája lényegében ugyanaz,
mint a columné, csak kimarad belőle a típusmeghatározás.

A további összetevőket, mint a primkey, különféle selectek, már ismerjük.
Indexdefiníciókat helyezni egy többtáblás tds-be értelmetlen, mivel soha nem
fogjuk a táblát kreálni. A lekérdezések ugyanúgy működnek, mint az egytáblás
esetben, például:

    
    
        tableentity:=probaszerencse.tableEntityNew(con)
        rowset:=tableentity:select
        while( (r:=rowset:next)!=NIL )
            ? r:szamlaszam,r:kiegdata
        end
        rowset:close
    
    

##  4.  Osztály referencia<a name="sec4"></a>

###  4.1.  Sqlconnection osztály<a name="sec4.1"></a>

Aszerint, hogy melyik névtérből hívjuk meg az sqlconnectionNew()
objektumgyártó függvényt, Oracle vagy Postgres adatbáziskapcsolathoz jutunk:

    
    
        con_ora:=sql2.oracle.sqlconnectionNew(connect_string)
        con_pg:=sql2.postgres.sqlconnectionNew(connect_string)
    
    

A `connect_string` paraméter opcionális. Oracle esetében a connect string
tartalma a megszokott `user@dbsid/password` alakú, ahogy azt pl. az sqlplus is
várja. Postgres esetén a connect string tartalma pontosan az lehet, mint amit
a `PQconnectdb` függvény (a libpq klienskönyvtárból) elfogad. Ha a connect
string nincs egyáltalán megadva, akkor a program az `ORACLE_CONNECT`, illetve
`POSTGRES_CONNECT` környezeti változók tartalmát használja bejelentkezéshez,
például:

    
    
        export ORACLE_CONNECT=scott@database/tiger
        export POSTGRES_CONNECT="host=HH dbname=DD user=UU password=PP"
    
    

A sqlconnection objektum létrehozásakor azonnal megtörténik a bejelentkezés.
Az attribútum/metódusok:

- **driver**
  Osztályváltozó, ami a konstruktor névterét tartalmazza.

- **duplicate**
  Létrehoz egy másik sqlconnection objektumot, amiben a connect infó ugyanaz, 
  mint az elsőben, tehát ugyanoda is kapcsolódik. Visszatérés: az új `sqlconnection` 
  objektum.

- **sqlcommit**
  Végrehajt egy commit utasítást, egyúttal automatikusan indítja a következő 
  tranzakciót. Visszatérés: NIL.

- **sqldisconnect**
  Megszünteti az adatbáziskapcsolatot. Az alkalmazási programnak ügyelnie 
  kell arra, hogy a kapcsolatok ne halmozódjanak fel, mert akkor elfogynak 
  bizonyos erőforrások (handlerek). Ezért minden feleslegessé váló kapcsolatot 
  explicite meg kell szüntetni. Visszatérés: NIL.

- **sqlexec(stmt,bind)**
  Végrehajt egy tetszőleges SQL utasítást. Az `stmt` utásítás `:1`, `:2`, ... 
  alakú formális paraméterei helyére behelyettesíti az (opcionális) `bind` arrayből 
  vett megfelelő indexű értékeket. Ha az utasítás nem hajtható végre, vagy hibás, 
  akkor `sqlerror`-ból származtatott futási hiba keletkezik. 
  Visszatérés: az érintett (törölt/módosított) rekordok száma.

- **sqlexecx(stmt,bind)**
  Végrehajt egy tetszőleges SQL utasítást. Az `stmt` utásítás `:1`, `:2`, ... alakú 
  formális paraméterei helyére behelyettesíti az (opcionális) `bind` arrayből 
  vett megfelelő indexű értékeket. Ha az utasítás nem hajtható végre, vagy hibás, 
  akkor visszaadja a hiba leírását tartalmazó error objektumot, egyébként NIL-t ad.

- **sqlisolationlevel(level,flag)**
  Beállítja a tranzakció izolációs szintet. Az első paraméter helyén az 
  `ISOL_SERIALIZABLE` vagy `ISOL_READ_COMMITED` konstansokat lehet megadni. 
  A második paraméter egy opcionális flag. Ha `flag==.f.` (ez a default), 
  az izolációs szint csak ideiglenesen, az adott tranzakción belül lesz átállítva. 
  Ha `flag==.t.`, akkor a beállítás hatálya az egész session. Visszatérés: NIL.

- **sqlquerynew(query,bind)**
  A `con:sqlquerynew(query,bind)` metódushívás gyárt egy sqlquery objektumot 
  (lásd alább). A `query` select utasítás `:1`, `:2`, ... alakú formális paraméterei 
  helyére behelyettesíti az (opcionális) `bind` arrayből vett megfelelő indexű 
  értékeket. Ezzel tetszőleges SQL lekérdezés végrehajtható. 
  Visszatérés: az új `sqlquery` objektum.

- **sqlrollback**
  Végrehajt egy rollback utasítást, egyúttal automatikusan indítja a következő 
  tranzakciót. Visszatérés: NIL.

- **sqlsequencenew(name)**
  A `con:sqlsequencenew(name)` metódushívás gyárt egy sqlsequence objektumot 
  (lásd alább). Visszatérés: az új `sqlsequence` objektum.

- **version**
  Megadja az adatbázisszerver verzióját (szövegesen).



###  4.2.  Sqlquery osztály<a name="sec4.2"></a>

Az sqlquery objektumok a `con:sqlqueryNew(select_stmt)` objektumgyártó
metódushívással keletkeznek. A metódusok:

- **close**
  Lezárja az sqlquery objektumot. Az alkalmazásoknak ügyelnie kell arra, 
  hogy a lezáratlan sqlquery objektumok ne halmozódjanak fel, másképp elfogynak 
  bizonyos erőforrások (handlerek). Ezért minden feleslegessé váló sqlquery 
  objektumot explicite le kell zárni. Visszatérés: NIL.

- **connection**
  Tárolja magában az adatbáziskapcsolatot, amivel létrehozták.

- **fcount**
  Megadja a select utasítással keletkező eredménytábla oszlopainak számát.

- **findcolumn(name)**
  Neve alapján megmondja az oszlop indexét az oszlopok listájában. 
  Ha a megadott nevű oszlop nem létezik, az eredmény 0.

- **fname(x)**
  Indexe alapján megmondja az oszlop nevét.

- **isnull(x)**
  A `q:isnull(x)` metódushívás megmondja, hogy az x-szel azonosított oszlop 
  utoljára fetch-elt értéke null volt-e, x az oszlop neve vagy indexe lehet.

- **getbinary(x)**
  A `q:getbinary(x)` metódushívás kiolvassa, és binary string (X) típusban 
  visszaadja az x-szel azonosított oszlop utoljára fetch-elt értékét, 
  x az oszlop neve vagy indexe lehet.

- **getchar(x)**
  A `q:getchar(x)` metódushívás kiolvassa, és stringre (C típusra) konvertálva 
  visszaadja az x-szel azonosított oszlop utoljára fetch-elt értékét, 
  x az oszlop neve vagy indexe lehet.

- **getdate(x)**
  A `q:getdate(x)` metódushívás kiolvassa, és dátumtípusra konvertálva visszaadja az x-szel azonosított oszlop utoljára fetch-elt értékét, x az oszlop neve vagy indexe lehet.

- **getlogical(x)**
  A `q:getlogical(x)` metódushívás kiolvassa, és logikai típusra konvertálva 
  visszaadja az x-szel azonosított oszlop utoljára fetch-elt értékét, 
  x az oszlop neve vagy indexe lehet.

- **getnumber(x)**
  A `q:getnumber(x)` metódushívás kiolvassa, és számtípusra konvertálva 
  visszaadja az x-szel azonosított oszlop utoljára fetch-elt értékét, 
  x az oszlop neve vagy indexe lehet.

- **next**
  Beolvassa (fetch) a lekérdezés következő eredménysorát. 
  Visszatérése `.t.`, ha volt még sor, egyébként (miután a sorok elfogytak) `.f.`. 
  Az eredménytáblán egyszer, előrefelé lehet a `next`-ekkel végighaladni.


###  4.3.  Sqlsequence osztály<a name="sec4.3"></a>

A connection osztály sqlsequencenew metódusával kapunk új sqlsequence
objektumot: `con:sqlsequenceNew(name)`, ahol `name` az adatbázisbeli sequence
objektum neve. Ne feledjük, az objektumgyártó csak programobjektumot készít,
az adatbázisban van, vagy nincs hozzá tartozó sequence objektum. Az
attribútum/metódusok:

- **cache**
  A cache attribútum default értéke 1. A `seq:create` metódus hatására olyan 
  adatbázisbeli sequence keletkezik, ami egyszerre cache darabszámú értéket 
  generál az alkalmazás számára. Ezzel a sequence használata gyorsul, 
  viszont kihasználatlanul maradhatnak értékek.

- **connection**
  Tárolja az adatbáziskapcsolatot.

- **create**
  Létrehozza az adatbázisban a sequence objektumot. A sequence összes 
  jellemzőjének figyelembevételével generál egy `create sequence` utasítást 
  és elküldi azt a szervernek. Visszatérés: NIL.

- **cycle**
  Ha a `cycle` attrubútum értéke `.t.`, akkor a olyan adatbázisbeli sequence 
  keletkezik (a seq:create metódus hatására), ami új kört kezd, ha eléri 
  a minimális/maximális értékét.

- **drop**
  Megszünteti a sequence-t az adatbázisban (küld egy `drop sequence` utasítást 
  a szervernek). Visszatérés: NIL.

- **increment**
  A kreáláskor keletkező sequence növekménye. Az attribútum értékével nő (csökken) 
  a sequence a `nextval` metódus végrehajtásakor, a default érték 1.

- **maxvalue**
  A sequence maximális értéke.

- **minvalue**
  A sequence minimális értéke.

- **name**
  A sequence objektum adatbázisbeli neve. Megadhatjuk az objektumgyártó 
  függvényben, vagy utólag egyszerű értékadással. Az adatbázisban a sequence-ek 
  egyedi névvel kell rendelkezzenek, tehát nem lehet egy sequence-nek és 
  pl. egy adattáblának azonos neve. Ha a sequence már létezik az adatbázisban, 
  akkor azt rögtön használhatjuk (`nextval`), vagy eldobhatjuk (`drop`). 
  Ha még nem létezik, akkor előbb létre kell hozni (`create`).

- **nextval**
  Lépteti a sequence-t, egyúttal szolgáltatja az új értéket.

- **start**
  Beállítja a létrehozandó sequence kezdőértékét. Növekvő sequence-eknél 
  a default kezdőérték `minvalue`. Csökkenő sequence-eknél a default kezdőérték 
  `maxvalue`.


###  4.4.  Absztrakt tableentity osztály<a name="sec4.4"></a>

Az absztrakt tableentity osztály a közös őse minden konkrét tableentitynek. Az
alábbi felsorolás csak az alkalmazási programok számára érdekes
attribútumokat/metódusokat tartalmaza.

- **connection**
  Az adatbáziskapcsolat objektumot tartalmazza.

- **create**
  Kreál egy adatbázistáblát, aminek a struktúrája megegyezik a tableentity 
  struktúrájával. Ugyancsak kreálja a tableentityben definiált indexeket. 
  Értelemszerűen csak akkor alkalmazható, ha a tableentityben nincs join, 
  azaz a tablistnek csak egyetlen eleme van. Visszatérés: NIL.

- **delete(rowentity)**
  Csak akkor alkalmazható, ha a tableentityben nincs join, azaz a tablistnek 
  egyetlen eleme van. Ha ez az egyetlen elem egy view, akkor annak jellegétől 
  függően egyes esetekben működik, más esetekben nem. A `t:delete(r)` törli 
  a tableentity által reprezentált tábla mindazon sorait, melyekben a primary key 
  oszlopok az `r` rowentity objektumból kiolvasható kulccsal egyeznek. 
  Persze a koncepció az, hogy pontosan egy sor törlődjön, de ez csak akkor 
  lesz így, ha a primary key valóban egyedi. Nem volna jó, ha az ilyen hiba 
  rejtve maradna, ezért, ha a törölt sorok száma nem pontosan 1, 
  akkor metódus `sqlrowcounterror` kivételt dob. Látható, hogy milyen fontos 
  a primary key egyediségére ügyelni, máskülönben egy óvatlan update vagy delete 
  könnyen nem várt eredményre vezet. Az egyediséget úgy lehet biztosítani, 
  hogy kreálunk egy unique minősítésű indexet, ami éppen a primary key 
  oszlopaiból áll. Ekkor az adatbázisszerver megakadályozza ismétlődő kulcsok 
  bevitelét. Visszatérés: a törölt sorok száma.

- **drop**
  Megszünteti az adattáblát, amit a tableentity reprezentál. Csak akkor 
  alkalmazható, ha a tablistnek egyetlen eleme van, és az egy valódi tábla 
  (nem pedig view). Visszatérés: NIL.

- **getcolumn(name)**
  Az oszloplistából kikeres egy oszlopdefiníciót a neve alapján. 
  Visszatérés: a `columndef` objektum, vagy NIL.

- **getprimarykey(rowentity)**
  A `key:=t:getprimarykey(r)` hívás kiolvassa az `r` rowentity objektumból 
  az elsődleges kulcsot, és visszaad egy arrayt, ami a klucsszegmenseket 
  tartalmazza. Ezzel a kulccsal hívható a leszármazott tableentity objektumok 
  `find` metódusa.

- **insert(rowentity)**
  A `t:insert(r)` berak a tableentity által reprezentált adattáblába egy új sort, 
  melyet az `r` rowentity objektum adataival tölt fel. Csak akkor alkalmazható, 
  ha a tableentityben nincs join, és a tablist egyetlen tagja egy elemi tábla 
  (nem pedig view). Csak azok az attribútumok (mezők) jelennek meg a szervernek 
  küldött insert utasításban, amiknek a null flagje `.f.` (ezt általában az 
  értékadások állítják be). Visszatérés: a berakott sorok száma 
  (ami normális esetben 1).

- **instance**
  Ad egy üresre inicializált rowentity objektumot. Az új objektum minden 
  attribútuma `.f.` dirty flaggel és `.t.` null flaggel rendelkezik.

- **setdirty(rowentity,flag)**
  A `rowentity` objektum összes attribútumának dirty flagjét beállítja `flag`-ra. 
  A dirty flag jelentősége, hogy az `update` metódus csak azokat a mezőértékeket 
  küldi a szervernek, amiknek a dirty flagje `.t.`-re van állítva. A dirty flag 
  nyilvántartását általában az objektumra bízhatjuk, néha azonban értelme lehet 
  kívülről belenyúlni a nyilvántartásba. Visszatérés: NIL.

- **setnull(rowentity,flag)**
  A `rowentity` objektum összes attribútumának null flagjét beállítja `flag`-ra. 
  A flag `.t.` értéke jelenti, hogy az attribútumok (mezők) null értéken vannak. 
  A null flag nyilvántartását általában rábízhatjuk az objektumra, néha azonban 
  értelme lehet kívülről belenyúlni a nyilvántartásba. Visszatérés: NIL.

- **show(rowentity)**
  A `t:show(r)` hívás kilistázza az `r` rowentity objektumot. Visszatérés: NIL.

- **tablist**
  Egy array, ami a táblák (vagy view-k) felsorolását tartalmazza a következő 
  alakban:        

        t:tablist:={"tab1=alias1","tab2=alias2",...}

  ahol tab1,... az adattáblák valódi (minősített) neve, alias1,... pedig a
  táblák hivatkozási neve. A tableentity objektum többi részében, ahol az
  szükséges (pl. amikor meg kell jelölnünk, hogy egy oszlop melyik táblából
  való) mindig a tábla alias nevét használjuk. Ennek eredményeként egy
  tableentity osztály invariáns a benne szereplő táblákra, azaz a tablist
  attribútum átírásával ugyanaz az objektum és adatstruktúra más fizikai
  táblákra is alkalmazható.
  Az alias nevek alkalmazása nem kötelező, nélkülük azonban elvész az
  invariancia. Ha a tableentity csak egyetlen táblát tartalmaz, akkor a
  tableentity definícióban sehol sincs szükség táblahivatkozásra, hiszen mindig
  a tablist egyetlen eleméről lehet csak szó, ilyenkor sem szükséges alias nevet
  használni.

- **update(rowentity)**
  Csak akkor alkalmazható, ha a tableentityben nincs join, azaz a tablistnek 
  egyetlen eleme van. Ha ez az egyetlen elem egy view, akkor annak jellegétől 
  függően egyes esetekben működik, más esetekben nem. A `t:update(r)` módosítja 
  a tableentity által reprezentált tábla mindazon sorait, melyekben a primary key 
  oszlopok az `r` rowentity objektumból kiolvasható kulccsal egyeznek. 
  Persze a koncepció az, hogy csak egy sor módosuljon, de ez csak akkor fog 
  teljesülni, ha a primary key valóban egyedi. Nem volna jó, ha az ilyen hiba 
  rejtve maradna, ezért, ha a módosult sorok száma nem pontosan 1, akkor 
  a metódus `sqlrowcounterror` kivételt dob. Csak azok az attribútumok (mezők) 
  jelennek meg a szervernek küldött update utasításban, amiknek a dirty 
  flagje `.t.` (ezt általában az értékadások állítják be). 
  Visszatérés: a módosult sorok száma.

- **zap**
  Törli a tableentity által reprezentált adattábla minden sorát. 
  Csak akkor alkalmazható, ha a tablistnek egyetlen eleme van, 
  és az egy valódi tábla (nem pedig view).


###  4.5.  Tableentity leszármazottak<a name="sec4.5"></a>

Az absztrakt tableentity osztályt oszlopokkal és select metódusokkal bővítve
kapjuk a konkrét tableentity osztályokat. Ezek kódját a gyakorlatban nem
kézzel írjuk, hanem XML leírásból, vagy tds scriptből programmal generáljuk. A
generált kód a tableentityre jellemző névtérbe helyezi az objektumgyártó
függvényt, amit így hívhatunk meg:
    
        tableentity:=multi.level.namespace.tableentityNew(con)

A `__method__` alakú metódusokat az alkalmazási programok közvetlenül nem
használják, csak a tanulság kedvéért szerepelnek az ismertetésben.

- **__primarykey__**
  Osztályváltozó, egy array, ami a primary key-t alkotó oszlopokat sorolja fel. 
  A koncepció fontos eleme, hogy a primary key egyedileg azonosítja a rowentity 
  objektumokat. Ha valami miatt ez nem teljesül, akkor egy update, vagy delete 
  metódus egy helyett több objektumot is módosíthat, vagy törölhet. A primary 
  key egyediségét úgy lehet biztosítani, hogy kreálunk egy unique minősítésű 
  indexet, ami éppen a primary key oszlopaiból áll. Ekkor az adatbázisszerver 
  megakadályozza ismétlődő kulcsok bevitelét.

- **__rowclassid__**
  Nem módosítható osztályváltozó, a tableentityhez tartozó rowentity osztály 
  egészszám azonosítóját tartalmazza.

- **__rowclassname__**
  Nem módosítható osztályváltozó, a tableentityhez tartozó rowentity osztály 
  nevét tartalmazza.

- **__tabjoin__**
  Nem módosítható osztályváltozó. Ha a tableentity több táblát tartalmaz, 
  akkor ezeket általában össze kell valahogy kapcsolni. A tabjoin attribútum 
  tartalmazza az SQL from záradék szövegét, ami megadja az összekapcsolás módját. 
  Például a p és q alias nevű táblák összekapcsolása a számlaszám oszlopokkal 
  így nézhet ki:  `p left join q on szamlaszam=qszamlaszam`

- **columnlist**
  Osztályváltozó, az oszlopok leírását tartalmazó array. Minden oszlopot egy 
  `columndef` objektum képvisel az arrayben.

- **find(keylist,lock)**
  Az `r:=t:find({keyseg1,keyseg2,...})` metódushívás veszi az alaptábla azon sorát, 
  ami a megadott kulcshoz illeszkedik, és létrehoz vele egy új rowentity objektumot. 
  Ha nincs sor a megadott kulccsal, akkor az eredmény NIL. A `find` metódus 
  használatának másik módja `r1:=t:find(r0)`, ahol a kulcsot a mintaként 
  használt `r0` objektumból vesszük. Itt `r0` és `r1` egymástól függetlenül létező 
  objektumok, nem csak egymás referenciái. 

  A find és select metódusokkal lehet a tábla kiválasztott sorait lockolni.

  * `r:=t:find(key)` nem lockol. 
  * `r:=t:find(key,0)` várakozás nélkül lockol. 
  * `r:=t:find(key,sec)` sec másodpercnyi várakozással lockol. 
  * `r:=t:find(key,-1)` végtelen várakozással lockol.

  A lockolt sorokat más tranzakció nem lockolhatja, és nem módosíthatja. A
  lockot csak a tranzakció vége (commit/rollback) oldja fel. Ha a lock
  sikertelen, `sqllockerror` vagy `sqldeadlockerror` kivétel keletkezik.

  > Megjegyzés: Postgresben nincs timeout támogatás, ezért minden lock végtelen
  > ideig, vagy a deadlock detektálásáig vár.

- **select(,lock)**
  A tableentityknek mindig van egy automatikus select metódusa, ami az alaptábla 
  minden sorát szolgáltatja szűrés és rendezés nélkül. Minden selectnek két 
  opcionális paramétere van: az első a bind értékeket felsoroló array, a második 
  a lockolást módját előíró szám (mint a find-nál). Speciálisan az automatikus 
  selectnek sosincsenek bind változói, ezért az első paramétert sosem használjuk, 
  és mivel ritkán célszerű egy egész táblát egyszerre lockolni, a másodikat is 
  csak ritkán.

- **select*(bindlist,lock)**
  A kulccsal meghatározott egyetlen sort szolgáltató find és az összes sort 
  szolgáltató select metódus mindig létezik, mert a programgenerátor ezeket 
  automatikusan elkészíti. Emellett fel lehet szerelni a tableentityt ún.
  opcionális selectekkel. Az opcionális selecteket egy where záradékkal, 
  és egy order by záradékkal lehet megadni. A where záradék sorszámozott 
  paramétereket tartalmazhat, pl. `szamlaszam like :1`.
  Legyen az opcionális selectünk neve `select_like`, akkor a metódust így
  hívhatjuk:
    
        rowset:=t:select_like({'1111111122222222%'})

  Ez egy olyan rowsetet ad, amiben a számlaszám 1-16 jegyei a megadott mintához
  illeszkednek.

  A select* metódusok első paramétere egy array, amiben a where záradék
  sorszámozott paraméterei helyére helyettesítendő (bind) értékek vannak
  felsorolva (az automatikus selectnél ezt a paramétert üresen kell hagyni).

  A select* metódusok második paraméterével a lockolás szabályozható:

  * `rowset:=t:select_x(bind)` nem lockol. 
  * `rowset:=t:select_x(bind,0)` várakozás nélkül lockol. 
  * `rowset:=t:select_x(bind,sec)` sec másodpercnyi várakozással lockol. 
  * `rowset:=t:select_x(bind,-1)` végtelen várakozással lockol. 

  Ha a lock sikertelen, `sqllockerror` kivétel keletkezik. Ha a szerver
  deadlockot észlel, `sqldeadlockerror` kivétel keletkezik. A lockolás független
  a sorok beolvasásától, azaz a rowset objektum létrejöttekor (még az első next
  előtt) az összes sor már lockolva van. A lockolt sorokat más tranzakció nem
  lockolhatja és nem módosíthatja. A lockot csak a tranzakció vége
  (commit/rollback) oldja fel, pl. nem oldja fel a lockot a rowset lezárása.

  > Megjegyzés: Postgresben nincs timeout támogatás, ezért minden lock végtelen
  > ideig, vagy a deadlock detektálásáig vár.


- **version**
     Nem módosítható osztályváltozó, tetszőleges szöveget tartalmazhat, általában a tableentity definíció változatszámát tároljuk benne.



###  4.6.  Rowset osztály<a name="sec4.6"></a>

A rowset objektumokat az alkalmazás sosem közvetlenül hozza létre, hanem a
tableentityk select metódusainak értékeként kapja. Egy rowset objektum egy
feldolgozás alatt álló SQL select utasítást képvisel. A select utasítással
(rowsettel) mindössze két dolgot lehet csinálni:

**next**
  A next metódus szolgáltatja az eredménytábla következő sorával feltöltött 
  rowentity objektumot. A nextekkel a select eredménytábla elejétől a végéig 
  egyesével lehet haladni, semmilyen más pozícionálás nem lehetséges. 
  Ha a sorok elfogynak, akkor a rowset automatikusan lezáródik, és a next 
  minden további hívása rowentity helyett NIL-t ad.

**close**
  Lezárja a rowsetet. A lezáratlanul hagyott rowsetek felhalmozódása 
  működésképtelenné teszi a programot, mert elfogynak a handlerek, ezért az 
  alkalmazásnak minden rowsetet le kell zárni.


###  4.7.  Rowentity osztályok<a name="sec4.7"></a>

Az adatbázisrekord, vagy az SQL select eredménytábla egy sorának programbeli
képe a rowentity objektum. Háromféleképpen lehet rowentity objektumhoz jutni:

  * `rowentity:=tableentity:instance`

  * `rowentity:=tableentity:find(key)`

  * `rowentity:=rowset:next`

Az első esetben üresre inicializált objektumot, a másik két esetben az
adatbázisból betöltött (fetch) objektumot kapunk. Egy új rowentity összes
attribútuma (mezeje) kezdetben false dirty flaggel rendelkezik. Az instance
metódussal gyártott rowentityben minden attribútum null értéken van, a másik
két esetben csak azok a mezők maradnak null értéken, amiknek az adatbázisban
is null értéke van.

A tableentity minden oszlopához létezik a rowentity objektumnak egy azonos
nevű metódusa, amivel az adott mező értéke lekérdezhető és módosítható. A
rowentity objektumok mind saját adatbufferrel rendelkeznek, emiatt egyszerre
több (akárhány) azonos típusú rowentity objektumunk lehet, amikkel egymástól
függetlenül végezhetünk műveleteket.

Minden rowentity rendelkezik az alábbi metódusokkal:

- **insert**
  Az `r:insert` metódushívás új sort tesz a tableentity által reprezentált táblába 
  a rowentity objektum adataival feltöltve. Csak azok az oszlopok jelennek meg a 
  kapcsolódó SQL insert utasításban, amiknek a program értéket adott, a többi oszlop 
  null értéken marad. Ez a metódushívás csak alternatív formája a tableentitynél 
  látott `t:insert(r)` alaknak, ahol t az r-hez tartozó tableentity. 
  Visszatérés: az inzertált rekordok száma (1).

- **update**
     Az `r:update` metódushívás módosítja a tableentity által reprezentált tábla 
     azon sorát, amit az r-ből kiolvasható primary key azonosít. Csak azok az oszlopok 
     jelennek meg az kapcsolódó SQL update utasításban, amiket a program megváltoztatott. 
     Ez a metódushívás csak alternatív formája a tableentitynél látott `t:update(r)` 
     alaknak, ahol t az r-hez tartozó tableentity. Ha a módosított rekordok száma nem 1, 
     akkor `sqlrowcounterror` kivétel keletkezik. 
     Visszatérés: a módosított rekordok száma.

- **delete**
     Az `r:delete` metódushívás törli a tableentity által reprezentált tábla 
     azon sorát, amit az r-ből kiolvasható primary key azonosít. Ez a metódushívás 
     csak alternatív formája a tableentitynél látott `t:delete(r)` alaknak, 
     ahol t az r-hez tartozó tableentity. Ha a törölt sorok száma nem 1, 
     akkor `sqlrowcounterror` kivétel keletkezik. Visszatérés: a törölt sorok száma.

- **find**
     Az `r1:=r0:find` metódushívás behozza azt az objektumot, amit a mintaként 
     használt r0-ból kiolvasható primary key azonosít. Ugyanaz, mint az 
     `r1:=t:find(r0)` alak.

- **show**
     Az `r:show` metódushívás kilistázza az objektumot, ugyanaz, mint a `t:show(r)` 
     alak, ahol t az r-hez tartozó tableentity. Visszatérés: NIL.

E metódusok a tableentity azonos nevű metódusaihoz továbbítva hajtódnak végre,
ezért a részletesebb leírást lásd a tableentity osztálynál.


###  4.8.  Columnref osztály<a name="sec4.8"></a>

A columnref objektumok nem kerülnek bele a tableentitybe, csak a
tableentitykben levő SQL utasítások elkészítésekor kapnak segédszerepet
azáltal, hogy tárolják egyes közvetlenül nem használt oszlopok adatbázisbeli
azonosítóját.

- **name**
  A oszlop (mező) programbeli neve.

- **expr**
  Oszlopkifejezés. Tetszőleges SQL kifejezés használható. A columnrefek esetében 
  ugyan nincs értelme számított mezőknek, de a columndef osztály is örökli ezt 
  az attribútumot. Ha nincs megadva, akkor az oszlopkifejezés egyenlő lesz az oszlop 
  nevével. Tipikus eset, hogy az oszlop minősített nevét adjuk meg itt.

- **columnid**
  Az oszlop adatbázisbeli neve, az oszlopkifejezésből állapítja meg az inicializáló, 
  és az update utasítások generálásához használja a rendszer.


###  4.9.  Columndef osztály<a name="sec4.9"></a>

Columndef objektumokkal az alkalmazási programokban ritkán találkozunk, mert
az oszlopok általában csak a tableentityk belső működéséhez kellenek. A
tableentity columndef objektumokkal való feltöltését sem közvetlenül végezzük,
mert ezt az XML definíció alapján generált kód teszi. Ha azonban vizsgálni
kell, hogy a szervertől kapott eredeti érték null, vagy nem null, mégiscsak a
columndef objektumhoz kell fordulnunk. A columndef az előző columnref osztály
leszármazottja, tehát rendelkezik az előbbi metódusokkal. A további metódusok:

- **type**
  Az oszlop Clipper típusát azonosító string: Cw, Nw[.d], D, L, M. 
  A memókat az új M típus jelöli. A típust, szélességet, decimálisok számát 
  egybe kell írni, pl. "N16.2". 

  Ha egy létező Oracle adatbázis egy oszlopát le akarjuk képezni Clipper
  típusra, akkor választanunk kell a Cw, Nw[.d], D, L, M típusok közül. A
  konverziót az adatbázisszerver fogja végezni, ha lehetséges, ha pedig nem
  lehetséges, akkor runtime errort kapunk. Az ,,értelmes" konverziók általában
  lehetségesek.

- **notnull**
  Egy flag, ami mutatja, hogy kötelező-e értéket adni az oszlopnak. 
  A feltételt az adatbázisszerver (nem az interfész!) ellenőrzi az insert/update 
  utasítások végrehajtásakor.

- **default**
  A mező default értéke. Az értéket az adatbázisszerver (nem az interfész!) 
  adja a mezőnek az insert utasítások végrehajtásakor.

- **offset**
  A mező kezdete a rowentity adatbufferében.

- **size**
  A mező mérete a rowentity adatbufferében.

- **block**
  Kódblock, ami kiolvassa/beírja az adatot a bufferből/bufferbe.

- **sqltype**
  Meghatározza a mező SQL típusát. Ha nemlétező táblát kreálunk a tableentityvel, 
  akkor (és csak akkor) kap szerepet az sqltype metódus, ami SQL típust rendel 
  az oszlop Clipper típusához. 

  A típusleképezés szabályai Oracle esetében:

        Cw     --> char(w)         ha w<=8
        Cw     --> varchar(w)      ha w>8
        M      --> blob
        Nw     --> number(w)
        Nw,d   --> number(w,d)  
        Nw.d   --> number(w,d)
        L      --> number(1)       a boolean-t nem ismeri
        D      --> date

  A típusleképezés szabályai Postgres esetében:
    
        Cw     --> char(w)         ha w<=8
        Cw     --> varchar(w)      ha w>8
        M      --> bytea
        Nw     --> numeric(w)
        Nw,d   --> numeric(w,d)  
        Nw.d   --> numeric(w,d)
        L      --> boolean
        D      --> date

  Ez egyúttal behatárolja, hogy a tableentity interfésszel milyen struktúrájú
  adattáblák hozhatók létre.

- **indvar**
     Indikátor változó.

- **isnull(row)**
     A `column:isnull(row)` metódus mutatja, ha a beolvasott mező eredeti értéke null. 
     A rowentityk oszlopmetódusai a null értéket nem NIL-re képezik, hanem egy egyező 
     típusú empty értéket adnak.

- **setnull(row,flag)**
     A `column:setnull(row,flag)` metódus beállítja a rowentity objektum egy mezőjénék 
     null flagjét. Visszatérés: NIL.

- **isdirty(row)**
     A `column:isdirty(row)` metódus mutatja hogy a program módosította-e a mezőt.

- **setdirty(row,flag)**
     A `column:setdirty(row,flag)` metódus beállítja a rowentity objektum egy 
     mezőjénék dirty flagjét. Visszatérés: NIL.

- **eval**
     A `col:eval(rowentity[,x])` metódushívás kiolvassa az oszlop értékét 
     a rowentityből, vagy x-et értékül adja az oszlopnak. Alkalmazási programban 
     inkább ezzel a formával találkozunk: `rowentity:colname[:=x]`.

- **label**
     Szöveges attribútum, amit táblafüggetlen megjelenítőprogramok használhatnak, 
     pl. oszlopfejléc kiírására.

- **tooltip**
     Szöveges attribútum, amit táblafüggetlen megjelenítőprogramok használhatnak.

- **picture**
     Szöveges attribútum, amit táblafüggetlen megjelenítőprogramok használhatnak.


###  4.10.  Indexdef osztály<a name="sec4.10"></a>

Index adatok tárolására használjuk az indexdef objektumokat.

- **name**
     Az Oracle-beli név kiegészítője. A `tableentity:create` metódus a tábla 
     kreálásakor a tableentityben tárolt indexeket is létrehozza. Az indexek 
     adatbázisbeli neve `tabname+'_'+i:name` lesz, ahol tabname 
     a `tableentity:tablist` első eleméből van.

- **seglist**
     Az indexet alkotó oszlopok columndef-jeinek listája.

- **unique**
     Logikai érték, mutatja, hogy egyedi-e az index.


##  A.  Összetett tranzakciók<a name="secA"></a>

Nézzük ezt a (pszeudo)programot:

    
    
        function konyveles1()
            begin
                könyvelgetünk különféle számlákra
                if( sikertelen ) 
                    break(konyverrorNew())
                end
                tovább könyvelgetünk különféle számlákra
                if( sikertelen ) 
                    break(konyverrorNew())
                end
                //minden rendben
                commit
            recover e <konyverror>
                //a hibát elkapjuk
                rollback
            end
    
    

Minden príma, szépen lekezeltük a lehetséges hibákat. Tegyük fel, hogy van egy
hasonló stílusban megírt `konyveles2()` függvényünk is, és a kétféle
tranzakció kombinálásával létre akarunk hozni egy harmadik, összetett (még
összetettebb) tranzakciót.

    
    
        function osszetett_konyveles() //HIBÁS!
            begin
                konyveles1()
                konyveles2()
                commit
            recover e <konyverror>
                rollback
            end
    
    

Rá kell jönnünk, hogy az összetett tranzakció fenti implementációja rossz,
méghozzá a résztranzakciókban levő commitok miatt. Át kell szerveznünk a
programot. Először megírjuk az `alg_konyveles1()` függvényt, ami a könyvelés
algoritmusát (az üzleti logikát) tartalmazza.

    
    
        function alg_konyveles1()
            könyvelgetünk különféle számlákra
            if( sikertelen ) 
                break(konyverrorNew())
            end
            tovább könyvelgetünk különféle számlákra
            if( sikertelen ) 
                break(konyverrorNew())
            end
            //minden rendben (mégsem commitolunk)
    
    

Azután az algoritmust tranzakciós keretek közé tesszük:

    
    
        function trn_konyveles1()
            begin
                alg_konyveles1()
                commit
            recover e <konyverror>
                rollback
            end
    
    

Azaz szétválasztottuk az algoritmust és a tranzakciókezelést. Ha ezt a
módszert alkalmazzuk az összetett könyvelésünk leprogramozására, a következő
eredményhez jutunk.

    
    
        function alg_osszetett_konyveles()
            alg_konyveles1()
            alg_konyveles2()
    
        function trn_osszetett_konyveles() 
            begin
                alg_osszetett_konyveles()
                commit
            recover e <konyverror>
                rollback
            end
    
    

Tehát minden tranzakciónak külön meg kell írni az algoritmikus részét és a
tranzakciókezelő keretét. A tranzakciókat végrehajtó programok nyilván a
`trn_*` függvényeket fogják hívni. Valaki talán azt gondolja, hogy ez plusz
munkával jár, valójában ennek éppen az ellenkezője igaz, így ugyanis újra
felhasználható kódot kapunk.

Azt is érdemes megfontolni, hogy az előző példákban a commit/rollback helyén
nem feltétlenül csak egyetlen adatbáziskapcsolatra kiadott commit/rollback
parancs áll. Az alkalmazás tudja, hogy az általa aktivizált tranzakció milyen
adatbázisokat használ, és _minden_ adatbáziskapcsolatra kiadja a
commit/rollback parancsot. Ezzel a technikával áttekinthető módon lehet
kezelni a több adatbázisra kiterjedő elosztott tranzakciókat.

##  B.  Kompatibilitási kérdések<a name="secB"></a>

###  B.1.  Adatbázis objektum nevek<a name="secB.1"></a>

Az Oracle és a Postgres is támogatja az idézett azonosítókat. Ha Oracleben egy
azonosító ilyen alakú

    
    
        "KONTO"."SZAMLASZAM"
        "KONTO"."UPDATE"
    
    

akkor azokat az Oracle nem tekinti kulcsszónak. Idézőjelek nélkül nem
használhatnánk `update` nevű mezőt, mert az ütközik az update kulcsszóval. Ha
az idézett azonosítókat csupa nagybetűvel írjuk, akkor az azonosító case
insensitive abban az értelemben, hogy

    
    
        "KONTO"."SZAMLASZAM" <=> Konto.Szamlaszam
    
    

egyenértékű. Ha az idézett azonosítóban nagybetűn kívül más is van, akkor az
azonosító case sensitive lesz. A Postgres ugyanígy nem tekinti kulcsszónak az
idézett azonosítókat, az Oraclelel ellentétben azonban a csupa kisbetűs
írásmód eredményez case insensitive azonosítókat, azaz

    
    
        "konto"."szamlaszam" <=> Konto.Szamlaszam
    
    

Az SQL2 interfész alkalmazkodik ehhez. Mindig idézett azonosítókat használ,
ezáltal nincs szükség az SQL kulcsszavak kerülgetésére. Oracle esetében az
idézett azonosítók nagybetűsek, Postgresnél kisbetűsek. Ez azzal az előnnyel
jár, hogy az általunk létrehozott adatbázisokban case insensitive azonosítók
lesznek, így az sqlplus-ban vagy psql-ben érdektelen a kis/nagybetűk
használata, azaz a szokott módon dolgozhatunk. Persze egy kulcsszóval egyező
azonosító esetén interaktív módban is használnunk kell az idézőjeleket.
Hátrány, hogy a mások által létrehozott case sensitive azonosítókat nem lehet
elérni az SQL2 interfészen keresztül.

###  B.2.  Autocommit, tranzakcióhatárok<a name="secB.2"></a>

Az Oracle automatikusan indítja a tranzakciókat. Egyáltalán nincs `begin
transaction` (vagy hasonló) utasítás, az Oracle mindig tranzakció közben van,
a tranzakció a következő commit/rollback utasításig tart, ami után
automatikusan indul a következő tranzakció.

A Postgres is tudott így működni a 7.4 verzió előtt, ez volt az ún. autocommit
off üzemmód. A 7.4-es verzióban azonban megszűnt az autocommit utasítás, ezért
az SQL2 interfészben kénytelenek vagyunk minden commit/rollback után `begin
transaction` utasítást küldeni a szervernek, ezzel pótolva az autocommitot.

Vannak esetek, amikor a szerver saját hatáskörben befejezettnek nyilvánít egy
tranzakciót:

Az Oracle a DDL utasítások (create table, drop table, ...) előtt és után
(belsőleg) automatikusan végrehajt egy commitot. Az SQL2 interfész az egységes
működés érdekében a Postgres esetében is kiadja ezeket a commitokat.

A Postgres bármilyen hiba esetén azonnal és elkerülhetetlenül abortálja a
tranzakciót, és végrehajt (belsőleg) egy rollbacket. Mivel ilyenkor nincs
módunkban automatikusan indítani a következő tranzakciót, előfordulhat (ha nem
vesszük észre a hibát), hogy a következő utasításaink tranzakción kívülre
kerülnek, ezáltal mind hibásak lesznek. Tulajdonképpen ez előnyös, mert így
legalább nem lehet elsiklani a hiba felett, úgy gondolom, éppen ennek
érdekében szűnt meg az autocommit. Az Oracle ezzel szemben úgy működik, mintha
minden SQL utasítás előtt volna egy implicit savepoint, és hiba esetén eddig a
savepointig rollbackelne. A Oracle tehát visszaáll a hibás utasítást megelőző
állapotra, és az alkalmazási programra bízza, hogy rollbackeli-e a tranzakció
egészét. Ezt a különbséget az SQL2 interfész nem egyenlíti ki. Az alkalmazási
programokat a Postgres szigorúbb feltételeihez alkalmazkodva kell megírni.

###  B.3.  Tranzakcióhatáron átnyúló fetch<a name="secB.3"></a>

Az indexszekvenciális rekordkezelőkhöz szokott programozó hajlamos arra, hogy
az SQL select-fetch utasításokat egy iterátor módján képzelje el: Az első
fetch 1 millisec alatt behozza az első rekordot, a következő fetch a
másodikat, stb. Ez az, amiről szó sincs.

Az SQL select még az első fetch előtt összeállítja, lerendezi a teljes (!)
eredménytáblát még akkor is, ha az GB-os nagyságrendű. Emiatt lehet, hogy az
első rekord megérkezéséig percek (órák) is eltelnek, míg a szerver egyre csak
dolgozik az eredménytáblán. Az alkalmazóknak tehát csínján kell bánni a nagy
eredménytáblához vezető lekérdezésekkel, mivel azok igencsak megviselik a
szervert.

Megfigyelésem szerint az Oracle az eredménytáblát a szerveren tartja, és csak
a fetchelt rekordokat küldi át a kliensre.

A Postgres két módszert is kínál a select utasításra. A _közvetlen select_
utasítás az egész eredménytáblát előre átküldi a kliensgépre, ebből a kliens
sor- és oszlopindex alapján (mintha csak egy mátrixot címezne) éri el az
adatokat. Mondani sem kell, milyen nehézségekkel jár egy nagy eredménytábla
kezelése. Emellett a Posgresben kurzort is definiálhatunk:

    
    
        declare crs_id cursor for select ...
        fetch forward 1 in crs_id
        ...
        fetch forward 1 in crs_id
    
    

A _kurzoros select_ csak a ténylegesen fetchelt rekordokat küldi át a
kliensre, ezért hatékonyabban kezeli a nagy eredménytáblákat, viszont
funkcionalitásában korlátozott, pl. nem működik vele a lockolás (`select ...
for update`). Az SQL2 interfész aszerint választ a közvetlen és kurzoros
select között, hogy az alkalmazás akar-e lockolni. Ha lock van előírva, akkor
közvetlen, egyébként kurzoros lesz a select.

Tovább bonyolódik a helyzet a tranzakcióhatárok miatt. Az Oracle képes a
tranzakcióhatárokon átnyúló fetchelésre. Ez a tulajdonság használható a
következő típusú programnál:

    
    
        select 100 ezer darab számla
        while(ciklus 100 ezer darab számlára)
            fetch
            kamatszámítás egy számlán
            if(sikeres)
                commit
            else
                rollback
            end
        end
    
    

A Postgres közvetlen select utasítása elvileg szintén tudná ezt, a
gyakorlatban viszont nagyon megkottyan neki a 100 ezres eredménytábla kliensen
történő kezelése. A kurzoros select (új fejleményként) _félig_ képes a
tranzakcióhatáron átnyúló fetchelésre, nevezetesen a commiton átmegy, a
rollback viszont menthetetlenül lezárja. Nem könnyű tehát összhangba hozni az
Oracle és a Postgres fetchelésre vonatkozó elképzeléseit.

Nézetem szerint azonban egyáltalán nem kell belemenni ebbe a zsákutcába. A
tranzakcióhatárokon átnyúló fetchelés fogalmilag zagyva dolog, jobb elkerülni,
az SQL2 interfész ezért egységesen megakadályozza. Az előző programot
egyszerűen implementálhatjuk _két adatbáziskapcsolattal_: Az egyiket
használjuk a 100 ezer darab számla felsorolásához, a másikat a
kamatszámításhoz. Így a kamatszámítás commit/rollback utasításai nincsenek
hatással a számlák bejárására. Ez tiszta ügy.

##  C.  Oracle 10g installálása Linuxra<a name="secC"></a>

###  C.1.  Szerver installálás<a name="secC.1"></a>

Az itt leírt eljárással Debian Sarge, Ubuntu 4.10, SuSE 9.0, SuSE 10.0
32-bites Linuxokra tudtam Oracle-t installálni.

#### Kezdeti állapot

Ellenőrizzük, hogy az alábbi csomagok installálva legyenek a rendszerünkön:

gcc, make, binutils, motif, lesstif, rpm

A hiányzó csomagokat installáljuk. A libmotif3 csomag Ubuntun a multiverse-ből
installálható. SuSE-n csak libmotif2 van, lesstif pedig csak forrásból volna
beszerezhető. Mindenesetre nem értem, hogy minek lesstif, ha van motif, és
minek egyáltalán akármelyik, amikor a GUI megjelenítését Jáva végzi. SuSE 9.0
esetében a linker jelezni fogja a motif hiányát, de attól a rendszer még
használható lesz. SuSE 10.0-án a telepítő hiányolni fogja a gcc 2.96-ot, de az
installáció a gcc 4.x-szel is működni fog. Kezdetben (a runInstaller
elindításáig) root-ként dolgozunk.

#### Csoportok, felhasználók

Létrehozzuk az alábbi csoportokat és felhasználókat:

    
    
        id nobody  # léteznie kell
        groupadd oinstall
        groupadd dba
        useradd -g oinstall -G dba  -d /opt/oracle oracle
        passwd oracle #jelszót adunk az oracle usernek
    
    

A továbbiakban az installációt az oracle felhasználó nevében csináljuk.

#### Oracle letöltés

Elhozzuk az Oracle-től a `ship.db.cpio.gz` csomagot és alkalmas helyen
kibontjuk.

    
    
        gunzip ship.db.cpio.gz
        cpio -idmv < ship.db.cpio
    
    

#### Base directory

Létrehozzuk az Oracle base directoryt:

    
    
        mkdir /opt/oracle/base
    
    

#### /etc/profile

Beírjuk /etc/profile-ba:

    
    
        export ORACLE_BASE=/opt/oracle/base
        export ORACLE_HOME=$ORACLE_BASE/product/10g
        export TNS_ADMIN=$ORACLE_HOME/network/admin
        export ORA_NLS33=$ORACLE_HOME/nls/data
        export NLS_LANG=AMERICAN_AMERICA.WE8ISO8859P1
        export NLS_DATE_FORMAT="YYYY-MM-DD"
    
        export ORACLE_SID=test
    
        PATH=$PATH:$ORACLE_HOME/bin
        LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ORACLE_HOME/lib
    
        export PATH
        export LD_LIBRARY_PATH
    
    

#### /etc/sysctl.conf

Beírjuk /etc/sysctl.conf-ba:

    
    
        kernel.shmall = 2097152
        kernel.shmmax = 2147483648
        kernel.shmmni = 4096
        kernel.sem = 250 32000 100 128
        fs.file-max = 65536
        net.ipv4.ip_local_port_range = 1024 65000
    
    

Utána futtatjuk: `/sbin/sysctl -p`

#### /etc/security/limits.conf

Beírjuk /etc/security/limits.conf-ba:

    
    
        *               soft    nproc   2047
        *               hard    nproc   16384
        *               soft    nofile  1024
        *               hard    nofile  65536
    
    

#### /etc/pam.d/login

Beírjuk /etc/pam.d/login-ba:

    
    
        session    required     /lib/security/pam_limits.so
    
    

#### Symlinks

Megcsináljuk a következő symlinkeket:

    
    
        ln -s /usr/bin/awk /bin/awk
        ln -s /usr/bin/rpm /bin/rpm
        ln -s /usr/bin/basename /bin/basename
        ln -s /etc /etc/rc.d
    
    

#### RedHat emuláció

Létrehozzuk a `/etc/redhat-release` fájlt a következő tartalommal:

    
    
        Red Hat Linux release 2.1 (drupal)
    
    

#### runInstaller

Eddig root-ként dolgoztunk, most váltunk oracle-re, és oracle-ként elindítjuk
a runInstaller-t:

    
    
        cd .../Disk1
        ./runInstaller
    
    

Itt hosszú ideig dolgozik, fordítgat, eközben adódhatnak hibák, ezek némelyike
figyelmen kívül hagyható.

Az installer felszólít a `root.sh` script futtatására, megtesszük neki. Ezután
vár 10 percet a cssd démon elindulására. Vagy várunk 10 percet, vagy küldünk
egy HUP-ot az init-nek, amire az újraolvassa a konfigurációs fájljait.

A root.sh script beír a /etc/inittab végére egy ilyen sort:

    
    
        h2:35:respawn:/etc/init.d/init.cssd run >/dev/null 2>&1 </dev/null
    
    

A cssd démon az ASM (Automatic Storage Manager) modullal tart fenn valamilyen
kommunikációt. Nálunk nincs ASM, tehát az inittab-ba írt sort kiszedhetjük, ha
az installer túljutott rajta (többet nem kell).

#### /etc/oratab

Beírjuk /etc/oratab-ba:

    
    
        test:/opt/oracle/base/product/10g:Y
    
    

#### /etc/init.d/oracle

Csinálunk egy `/etc/init.d/oracle` fájlt a következő tartalommal:

    
    
    #!/bin/bash
    #
    # Run-level Startup script for the Oracle Instance and Listener
    
    ORA_HOME="/opt/oracle/base/product/10g"
    ORA_OWNR="oracle"
    
    # if the executables do not exist -- display error
    
    if [ ! -f $ORA_HOME/bin/dbstart -o ! -d $ORA_HOME ]
    then
            echo "Oracle startup: cannot start"
            exit 1
    fi
    
    # depending on parameter -- startup, shutdown, restart 
    # of the instance and listener or usage display 
    
    case "$1" in
        start)
            # Oracle listener and instance startup
            echo -n "Starting Oracle: "
            /sbin/sysctl -p
            su - $ORA_OWNR -c "$ORA_HOME/bin/lsnrctl start"
            su - $ORA_OWNR -c $ORA_HOME/bin/dbstart
            touch /var/lock/subsys/oracle
            echo "OK"
            ;;
        stop)
            # Oracle listener and instance shutdown
            echo -n "Shutdown Oracle: "
            su - $ORA_OWNR -c "$ORA_HOME/bin/lsnrctl stop"
            su - $ORA_OWNR -c $ORA_HOME/bin/dbshut
            rm -f /var/lock/subsys/oracle
            echo "OK"
            ;;
        reload|restart)
            $0 stop
            $0 start
            ;;
        *)
            echo "Usage: $0 start|stop|restart|reload"
            exit 1
    esac
    exit 0
    
    

Ezután a szokásos módon vezérelhető a szerver:

    
    
        /etc/init.d/oracle start|stop|restart
    
    

#### Hálózat

A szerveren az `$ORACLE_HOME/network/admin/listener.ora` fájlban van leírva a
listenerek paraméterezése. Az installáció után ez általában ,,magától" jó.

A kliens programok számára az `$ORACLE_HOME/network/admin/sqlnet.ora` fájlban
fel vannak sorolva a protokollok, amikkel hálózati szolgáltatásokat tudnak
keresni. Nálam ez így néz ki:

    
    
    # SQLNET.ORA Network Configuration File
    NAMES.DEFAULT_DOMAIN = comfirm.x
    NAMES.DIRECTORY_PATH= (TNSNAMES, ONAMES, HOSTNAME)
    
    

Tehát elsősorban a tnsnames fájlt nézzük, ha egy adatbázist keresünk a
hálózaton. A `$ORACLE_HOME/network/admin/tnsnames.ora` fájl egy kis adatbázist
tartalmaz a hálózaton található Oracle szolgáltatásokról. Ahhoz, hogy az
Oracle hálózati kliens megtalálja a ,,test" adatbázis szolgáltatást (ez volna
a SID?), el kell helyezni a tnsnames.ora fájlba egy ilyen bekezdést:

    
    
    test.COMFIRM.X =
      (DESCRIPTION =
        (ADDRESS_LIST =
          (ADDRESS = (PROTOCOL = TCP)(HOST = 1g.comfirm.x)(PORT = 1521))
        )
        (CONNECT_DATA =
          (SERVER = DEDICATED)
          (SERVICE_NAME = test)
        )
      )
    
    

A domain, host és service neveket a konkrét esetnek megfelelően kell beírni.

#### Tablespace, konto schema

A jelen demóban az adatbázis objektumok a konto schema-ban jönnek létre.
Legjobb ezt a schema-t mindjárt a telepítés után létrehozni.

Elindítjuk (system-ként) az sqlplus-t, és végrehajtjuk benne a következőket:

    
    
    create tablespace konto logging
        datafile '/opt/oracle/base/oradata/test/konto.dbf'
        size 8M reuse autoextend on next 4M
        maxsize unlimited
        extent management local autoallocate
        segment space management auto;
    
    create user konto
        identified by konto
        default tablespace konto
        quota 100000M on konto;
    
    grant connect to konto;
    
    quit;
    
    

Ezután az Oracle adatbázis alkalmas a demó programok kiszolgálására.

###  C.2.  Kliens installálás<a name="secC.2"></a>

Ha egy gépre Oracle szervert installálunk, azon lesz Oracle kliens is. Ha
azonban csak a kliensre van szükségünk, akkor nem érdemes 100-szoros munkával
szervert telepíteni.

Letöltjük az Oracle-től az _Oracle Instant Client_ csomagokat. A szoftver 4
darab zip fájlból áll (egyes platformokra rpm is van). A 4 közül a CCC-hez
csak két összetevőre van szükség, a basic-re és az sqlplus-ra. A zip-eket
kibontjuk, és a tartalmukat betesszük a `/opt/oracle/instantclient` (vagy egy
tetszés szerint választott) directoryba.

Megcsináljuk a `/opt/oracle/instantclient/network/admin` directoryt, és abban
elhelyezzük az alábbi két fájlt:

A `sqlnet.ora` fájl tartalma:

    
    
    # SQLNET.ORA Network Configuration File
    NAMES.DEFAULT_DOMAIN = comfirm.x
    NAMES.DIRECTORY_PATH= (TNSNAMES)
    
    

A `tnsnames.ora` ilyen bekezdésekből áll:

    
    
    test.COMFIRM.X =
      (DESCRIPTION =
        (ADDRESS_LIST =
          (ADDRESS = (PROTOCOL = TCP)(HOST = 1g.comfirm.x)(PORT = 1521))
        )
        (CONNECT_DATA =
          (SERVER = DEDICATED)
          (SERVICE_NAME = test)
        )
      )
    
    

Természetesen a domain, host, service neveket a saját adatainkkal
helyettesítjük.

A `/etc/profile`-ba beírjuk:

    
    
    export ORACLE_HOME=/opt/oracle/instantclient
    export PATH=$PATH:$ORACLE_HOME
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ORACLE_HOME
    export TNS_ADMIN=$ORACLE_HOME/network/admin
    export NLS_LANG=AMERICAN_AMERICA.WE8ISO8859P1
    #export NLS_LANG=HUNGARIAN_HUNGARY.EE8ISO8859P2
    export NLS_DATE_FORMAT="YYYY-MM-DD"
    
    

Ezután újonnan bejelentkezve fut az sqlplus, és futnak a CCC programok.

Ha az sqlnet.ora és tnsnames.ora fájlok elhelyezkedése az `ORACLE_HOME`-hoz
képest olyan, mint a fenti példában, akkor a `TNS_ADMIN` változó megadása
felesleges (de nem árt).

Az adatbázisok általában Latin-1 (WE8ISO8859P1) kódkészlettel jönnek létre,
mert ez a default. Ha egy ilyen adatbázissal állunk kapcsolatban, de a
kliensen Latin-2 (EE8ISO8859P2) kódkészlet van beállítva, akkor a
szövegmezőkben elromlanak a 128 feletti byteok. (Ha kiírunk egy 128 feletti
betűkből álló stringet, akkor a visszaolvasás a legtöbb helyen kérdőjelet ad.)
Ezért a kliensen kötelezően ugyanazt a kódkészletet kell beállítani, mint ami
a szerveren van, akkor is, ha így a szerver üzeneteit magyar helyett esetleg
angolul kapjuk.

##  D.  Postgres adatbázis készítése<a name="secD"></a>

#### Postgres változatok

A 7.4.x változatban megszűnt a szerver oldali autocommit. Korábban a `set
autocommit off` utasítás hatására egy commit/rollback után automatikusan
indult a következő tranzakció, ami megint csak a következő commit/rollback-ig
tartott. Ehelyett az interfész minden commit/rollback után küld a szervernek
egy `begin transaction` utasítást. A 8.0.8 változat körül megjelentek a
`savepoint`-ok. A 8.1.4-ben megjelent a kétfázisú commit (2PC) és az osztott
rekordzár (`select ... for share`).

#### Új adatbázis cluster készítése

Adatbázis clusternek nevezzük az adatbázisok egy olyan halmazát, amik
ugyanabban a PGDATA könyvtárban vannak, és ugyanaz a Postmaster folyamat
kezeli őket. Csinálunk egy üres directoryt:

    
    
        mkdir pgdata
    
    

Ebben végrehajtjuk:

    
    
        initdb --no-locale -D `pwd` 
    
    

#### Indító/leállító scriptek

Létrehozzuk pgdata-ban az alábbi scripteket. A `pg-start` script indítja az
adatbázist:

    
    
        #!/bin/bash
        pg_ctl start  -D `pwd`  -l PG_LOG
    
    

A `pg-stop` script leállítja az adatbázist:

    
    
        #!/bin/bash
        pg_ctl stop  -D `pwd`  -l PG_LOG
    
    

#### Új adatbázis készítése

Elindítjuk a Postgres-t (az előbbi indítóscripttel), utána elindítjuk psql-t.

    
    
        psql template1
    
    

A psql-ben végrehajtjuk:

    
    
        create database vermes;
    
    

Ezzel a saját home-omban csináltam egy privát adatbázis clustert (adatbázisok
olyan halmazát, amit ugyanaz a Postmaster kezel), ebben a clusterben jelenleg
egy adatbázis van (vermes), amibe azonosítás nélkül (mint lokális UNIX user)
bármikor beléphetek, és amiben bármit csinálhatok.

#### Konto schema

Mivel a jelen demó minden adatbázisobjektumot a konto schema-ban hoz létre,
legjobb ezt a schema-t mindjárt megcsinálni. A psql-ben végrehajtjuk:

    
    
        create schema konto;
    
    

Ezután a Postgres adatbázis alkalmas a demó programok kiszolgálására.






<!---
<table>
<tr><td></td><td></td></tr>
<tr><td></td><td></td></tr>
<tr><td></td><td></td></tr>
<tr><td></td><td></td></tr>
</table>
--->
