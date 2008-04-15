Stringek automatikus cseréje többnyelvű programokban
====================================================

Egyelőre csak a prg-beli stringekről van szó.

A forrásban be kell jelölni a fordítandó szövegeket, egyúttal 
angolra kell fordítani, hogy kódolásfüggetlen, semleges platformról 
indulhasson a lokalizálás. Ha minden szövegünk angol, akkor ASCII 
és UTF-8 editorban egyformán kezelhető a program. (Sajnos sok magyar 
komment van, azokat is angolra kellene fordítani.)

A fordítandó stringek kijelölése így történik:

    @"Some like hot"

A "ordinary text" kiértékelése (veremre rakása):

    string(L"ordinary text");

A lokalizálandó string veremre rakása:    

    string(nls_text(L"text to localize"));

Az új ppo2cpp ezekhez támogatást ad. 

1) Ha be van állítva a CCC_STRING_TAB környezeti változó 
(egy filéspecifikációra), akkor a nem bejelölt stringeket 
listázza ebbe a filébe.

2) Ha be van állítva a CCC_NLSTEXT_TAB környezeti változó 
(egy filéspecifikációra), akkor a fordításra kijelölt stringeket 
listázza  ebbe a filébe.

A lista formátuma:

"Some like hot"<<"" from  ./proba.prg  (8)

A sor a fordítandó (angol) szöveggel kezdődik,
utána egy '<<' azt jelképezi, hogy ami itt jön,
az fogja helyettesíteni az angol szöveget, ezután "" jön, 
ezek közé kell majd (a tran filében) beírni a fordítást.
Végül komment jön, ami nem tartalmazhat '"' karaktert.
Az egész szigorúan egy sor.

Amikor a ppo2cpp csinálja ezt a filét, akkor  mindig
append módban nyitja meg, tehát akármennyi gyűjtés eredménye
felhalmozódik a filében, pl. az egész CCC könyvtár stringjei.

Az így készült filét átmásoljuk egy tran kiterjesztésű
filébe, ebben dolgozik a fordító: <<"ide beírogatja a fordítást"
mondjuk oroszul, természetesen UTF-8-ban.

A stringek gyűjtését, és az újak (vagy megváltozottak)
hozzáadását a tran filékhez programmal kell támogatni.
A legfontosabb, hogy a tran filékben levő élőmunka ne vesszen el.

Tfh, valahogy megvan a tran filé.
A tran2cpp utility a tran-ból készít egy olyan C++ programot,
ami az egymásnak megfelelő szövegpárokat berakja egy hashtáblába.
Egyetlen függvény készül, aminek neve: hashtable_fill.
Minden lokalizált könyvtárhoz és minden alkalmazáshoz
nyelvenként készül egy so, ami csak ezt a hashtable_fill
függvényt tartalmazza.

A lokalizált program elején be kell tölteni a fordításokat,
például:

    nls_load_translation("sql2") //nincs még ilyen
    nls_load_translation("nlstext-test")

Tfh, a CCC_LANG=hu beállítás van érvényben, akkor a

    libsql2.hu.so
    libnlstext-test.hu.so

könyvtárakban található fordítások töltődnek be.    

A nls_text() függvény megpróbálja helyettesíteni az argumentumát
a lefordított szöveggel. Ha az nls_text() nem találja meg a fordítást,
pl. nincs meg a könyvtár, vagy nincs meg a keresett string,
akkor az eredeti angol szöveg jelenik meg.

A példában angol szöveget fordítok ISO-8859-2 magyarra,
de a fordítás szempontjából most mindegy a kódolás.

A fordításkönyvtár készítésekor és a CCC_LANG változóban
a nyelv mellett megadható a kódolás, pl: hu.UTF-8.

Másik alkalmazási lehetőség: Az eredeti forrásba nem angol
szöveget írunk, hanem egy kulcsot, pl. ékezetlenített
magyar szöveget, a program angol változatához pedig
csinálunk egy xxx.en.so fordításkönyvtárat.
