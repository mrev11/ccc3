
# CCC-GTK csatoló

_Dr. Vermes Mátyás_

2005\. október


[1  Áttekintés](#sec1)  
[2  GTK változatok](#sec2)  
[3  Névtér konvenció](#sec3)  
[4  Függvényhívási szint](#sec4)  
[5  Objektum szint](#sec5)  
[6  Callback függvények](#sec6)  
[7  Interfészek](#sec7)  
[8  Referenciaszámlálás, memóriakezelés](#sec8)  
[9  Dokumentáció](#sec9)   

##  1.  Áttekintés<a name="sec1"></a>

A CCCGTK csatoló elérhetővé teszi a GTK funkcióit CCC programok számára.
CCCGTK igyekszik minél kevesebbet veszíteni a GTK eredeti lehetőségeiből, de
nem akar semmit hozzátenni:

  * Szó sincs arról, hogy ezután a régi Clipper programok átírás nélkül GTK köntösben tudnának megjelenni. 

  * Nem foglalkozunk adatbázistartalom és a megjelenítés összekapcsolásával. 

  * Nincsenek a Clipperben megszokott (nagyon hasznos) picture-öket pótló eszközeink, stb.. 

Az ilyesmit az alkalmazásfejlesztés feladatai közé soroljuk, ezzel szemben a
CCCGTK egyszerűen csak kivezeti a GTK API-t CCC szintre.

A GTK-ban kb. 200 osztály és 2000 API hívás van. Ez meglehetősen sok
(takarékosnak semmiképp sem mondanám). Az interfészfüggvények kb. 80%-a
automatikusan generálódik (a PyGTK-hoz hasonlóan) defs fájlokból. A maradék
20% esetében nem lehetséges, vagy nem célszerű az automatikus kódgenerálás. Az
arány még változhat, ui. kiderülhet, hogy a generált kód egy (kis) része nem
jó, illetve biztosan javulni fog még a kódgenerátor. A kimaradó
interfészfüggvények egy részére nincs is szükség, az eddig megtalált hiányokat
viszont kézzel pótoltam.

A CCCGTK készültségi fokát úgy jellemezném, hogy valószínűleg jól van
elkezdve. Egyelőre nem tudható több, mint hogy a szokásos példaprogramok
futnak, és feltehető, hogy az eddig nem próbált widgetek többsége is működni
fog. Mindenesetre a widget gallery-ben szereplő widgetek mindegyikére működő
demó van.

##  2.  GTK változatok<a name="sec2"></a>

Jelenleg Ubuntu Hoaryn dolgozom, és GTK-2.6.4 változat van a gépemen. Ezzel
fordul a CCCGTK. Ugyanakkor tudni kell, hogy a GTK elég gyorsan mozgó célpont,
gyorsan deprecateddé nyilvánítanak fontos osztályokat, amiket újakkal
pótolnak, változtatgatják az osztálystruktúrákat. A SuSE 9.0-ás gépemen
(GTK-2.2.3) pl. hiányzik többek között a GtkCellLayout interfész (amibe
átkerült a GtkTreeViewColumn osztály funkcióinak egy része), valamint hiányzik
a GtkComboBox osztály (ami pótolja a depracteddé vált GtkCombo-t). Kérdés,
hogy érdemes-e backportolni a CCCGTK-t régebbi GTK-ra. Windowson is van GTK,
de nem kísérleteztem vele.

##  3.  Névtér konvenció<a name="sec3"></a>

Vegyük példaként a `GtkWindow` osztályt. Ehhez az osztályhoz létezik egy sor
(jónéhány) C-ből hívható API függvény, amik így néznek ki (példaként csak
néhányat veszünk):

    
    
        //ez C program
        gtk_window_new(type); //konstruktor
        gtk_window_set_title(GTK_WINDOW(self),title); //metódus
        gtk_window_get_title(GTK_WINDOW(self)); //metódus
        gtk_window_set_position(GTK_WINDOW(self),position); //metódus
    
    

A CCC-ben minden GTK osztályhoz egy kétszintű névteret társítunk, a GtkWindow
osztályhoz a `gtk.window` névteret. Az osztályhoz tartozó függvényeket ebbe a
névtérbe helyezzük, pl.:

    
    
        //ez CCC program
        gtk.window.new(type) //konstruktor
        gtk.window.set_title(self,title) //metódus
        gtk.window.get_title(self) //metódus
        gtk.window.set_position(self,position) //metódus
    
    

Ez a névkonvenció világosan kifejezi, hogy melyik osztály eljárásairól van
szó, világosabban, mint a C-ben használt nevek.

##  4.  Függvényhívási szint<a name="sec4"></a>

A CCCGTK csatoló az előbbi módon kivezeti a GTK API-t CCC szintre. Ezzel már
tudunk programozni, pl.:

    
    
        window:=gtk.window.new() //default: toplevel
        gtk.window.set_title(window,"GtkListStore Minimal Demo")
        gtk.window.set_default_size(window, 280, 250)
    
    

Az új window-nak beállítottuk a címsorát és a méretét. A GTK (egyszeres
öröklődéses) objektumrendszerében a GtkWindow osztály egyik felmenője a
GtkContainer osztály. Utóbbinak van egy `set_border_width` metódusa a keret
méretének beállítására. Ha konkrétan a mi előző ablakunk keretét akarjuk
beállítani, akkor ezt írjuk:

    
    
        gtk.container.set_border_width(window,8)
    
    

A GtkContainer-ben definiált `set_border_width` metódus működik a GtkWindow
dinamikus osztályú window-ra, mivel az egy GtkContainer leszármazott. Ilyen
egyszerűen működik a GTK-ban az öröklődés C szinten, illetve a CCCGTK
függvényhívási szintjén.

##  5.  Objektum szint<a name="sec5"></a>

Az előző pontban szereplő `window` változó CCC típusa P, azaz egy pointer, ami
közvetlenül a GTK struktúrára mutat. A kényelmesebb és biztonságosabb
használathoz a CCCGTK a legtöbb GTK osztályhoz létrehoz egy burkoló CCC
osztályt,

  * aminek egyetlen adattagja az előbbi pointer, 

  * rendelkezik a GTK-ban definiált metódusokkal, 

  * leszármazás (öröklődés) terén pedig lemásolja a GTK eredeti osztályhierarchiáját. 

A gyakorlatban ezen az objektumszinten fogjuk fejleszteni az alkalmazásainkat.
Az előbbi példa így néz ki objektumszinten:

    
    
        window:=gtkwindowNew()
        window:set_title("GtkListStore Minimal Demo")
        window:set_default_size(280, 250)
        window:signal_connect("destroy",{||gtk.main_quit()})
        window:set_border_width(8)
    
    

Rövidebb, egyszerűbb és biztonságosabb kódot kaptunk. Egyszerűbbet, mert a CCC
az öröklődési viszonyokból ,,magától" tudja, hogy a GtkContainer osztály
`set_border_width` metódusát kell alkalmazni a window-ra. Biztonságosabbat,
mert a CCC ellenőrzi, hogy van-e egyáltalán a window-nak ilyen metódusa.

A két szint közötti összefüggés: A mostani window változónk O (object) típusú.
Van neki egy `gobject` nevű attribútuma, és ez a `window:gobject` éppen az
előző példában szereplő P típusú window változót tartalmazza. Természetesen a
CCCGTK a metódusok paraméterezésében is nyomon követi, hogy függvényhívási
szinten, vagy objektumszinten történnek-e a dolgok.

##  6.  Callback függvények<a name="sec6"></a>

A callback függvények megvalósításának természetes módja CCC-ben a kódblokk.
Lássunk egy példát:

    
    
        ...
        hbox:pack_start(gtklabelNew("Second entry:"))
        hbox:pack_start(entry2:=gtkentryNew())
        entry2:signal_connect("activate",{|w|cb_activate(w,"Entry2")})
        ...
    static function cb_activate(entry,entry_name)
        ? entry_name, entry:get_text
    
    

A kódblokk nagyon rugalmas: Mint a példa mutatja, tetszőleges adatot át tudunk
adni általa a callback függvénynek.

##  7.  Interfészek<a name="sec7"></a>

A GTK egy egyszeres öröklődést és interfészeket kezelő objektumrendszerre épül
(a GObject-re). A CCC ezzel szemben többszörös öröklődést is kezel, nincs
tehát szükségünk interfészekre, ami csak szükségmegoldás az igazi többszörös
öröklődéshez képest. A GTK-beli interfészeknek a CCC-GTK-ban absztrakt
osztályok felelnek meg, amiből egyszerűen örökölnek az interfészt implementáló
osztályok.

##  8.  Referenciaszámlálás, memóriakezelés<a name="sec8"></a>

A GTK az objektumai többségére referenciaszámlálást alkalmaz. Ezzel
kapcsolatban egyetlen szabályt kell megjegyezni: A CCCGTK semmilyen módon nem
avatkozik bele a GTK (GObject) referenciaszámlálásába. A referenciaszámlálást
befolyásoló API-hoz akkor és csak akkor folyamodunk, ha arra a programunk
C-beli megfelelőjében is szükség volna (és persze, ha tudjuk, hogy mit
csinálunk.)

Ugyanez vonatkozik a memóriakezelésre. A CCC pointerek által hivatkozott
memóriaobjektumok pontosan addig léteznek, mint a programunk C-beli
megfelelőjében. A memória felszabadításának szintén ugyanazok a szabályai, a
szabályok áthágásának ugyanazok a következményei.

Szerencsére átlagos programokban elég jól működik a referenciaszámlálás:
Létrehozunk egy ablakot, abba beleteszünk néhány widgetet, azokba újabb
widgeteket, ..., minden alkatrész referenciát tart fenn az általa tartalmazott
komponensekre, így az egész megáll a saját lábán. Végül a program kilép, és
úgyis felszabadul az összes memória. Ennél persze több kell, ha _sokáig futó_
programot akarunk csinálni, pl. egy desktopot, dehát az ilyet úgysem CCC-ben
írjuk.

Egy típuspélda arra az esetre, amikor direkt kezeljük a memóriát:

    
    
    static function dump(model)
    local iter:=gtk.tree_iter.new()
    local positioned:=model:get_iter_first(iter)
        while( positioned )
            ? model:get(iter)
            positioned:=model:iter_next(iter)
        end
        // clean up
        gtk.tree_iter.free(iter)
    
    

A `tree_iter` egy segédosztály, nincs burkoló osztálya. Egy C programban az
iter-t tipikusan nem new-val hoznánk létre, hanem egyszerűen stack
változóként, ami megszűnik, amikor a rutin visszatér. CCC-ben tisztogatni
kell, ha nem akarjuk fogyasztani a memóriát.

##  9.  Dokumentáció<a name="sec9"></a> 

A C és CCC API között 99%-os megfelelés van (figyelembe véve a névtér
konvenciót, és az előbbi összefüggéseket, viszont figyelmen kívül hagyva az
esetleges hiányokat), ami lehetővé teszi, hogy a CCC programozás során
használjuk a meglevő GTK dokumentációkat. Tehát mint annyiszor, most is az a
helyzet, hogy először a C szintű API-val kell tisztába jönni, után nem lesz
probléma a CCC-vel sem. Ezért nincs szükség önálló dokumentációra.

