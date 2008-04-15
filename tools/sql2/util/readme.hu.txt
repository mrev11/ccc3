
bt2tds
    bt2ted.exe

    BT táblához tableentity definíciós filét (ted) készít.
    Az eredményt általában még kézzel editálni kell, 
    ui. nincsenek benne az opcionális select metódusok.
    Nem mindig van olyan index, ami megfelel primarykey-nek.
    
    bt2tds.exe

    Lényegében ugyanaz, mint a régebbi bt2ted,
    csak nem XML szintaktikájú ted kimenetet készít,
    hanem az olvashatóbb table definition scriptet (tds).
    

btimport (átkerült a test-be)
    Egy bt (dat/dbf) táblát áttölt SQL adatbázisba.
    Csak olyan táblákra működik, amik benne vannak egy entitylib
    könyvtárban (lásd mkentitylib-et). Az entitylib könyvtárat
    bele kell linkelni a btimport programba.
    
    Megjegyzés: 
    Az importálandó táblákhoz csinálunk egy entitylib könyvtárat
    (a bt2tds, tds2prg és mkentitylib utilitykkel), 
    és ennek a könyvtárnak a linkelésével csinálunk egy speciális, 
    az adott import feladathoz alkalmas btimport.exe-t. Azaz nem 
    paraméterehzető, hogy mit importálunk, hanem alkalmanként el 
    kell végezni a bedrótozást.


mkentitylib
    Az aktuális directory *.tds és *.ted filéire lefuttatja
    tsd2prg-t vagy ted2prg-t, azaz elkészíti belőlük a prg-t.
    (A prg-kből temészetesen a Builddel könyvtárat készítünk.)
    Ha meg van adva egy argumentum, akkor hozzárak egy további
    függvényt (entitylib.arg(name,con)), amivel név szerint is
    meg lehet kapni a könyvtár tableentity osztályait.


tds2prg
    tds2prg.exe: Tableentity Definition Scriptből prg-t készít.
    ted2prg.exe: TableEntity Definition XML-ből prg-t készít.
