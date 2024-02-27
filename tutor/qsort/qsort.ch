
//#define DEBUG

#define ARRLEN  100000
#define STRLEN  4

#define ASORT   asort
#define QSORT   qsort_mt

// qsort_2      : legegyszerubb elvi implementacio, 2 reszre oszt 
// qsort_2x     : rendezeskor hasznalja az eredeti indexet, 2 reszre oszt 
// qsort_3      : egyenlo elemek elleni vedekezes 3 reszre osztassal (lt,eq,gt)
// qsort_3t     : qsort_3 plusz tail recursion
// qsort_h      : Hoare-fele particionalas (valoszinuleg ez van a libc qsort-ban)
// qsort_mt     : qsort_h tobbszalu valtozata (fut, de baromi lassu)

// qsort_3c     : qsort_3t atirva cpp-re
// qsort_hc     : qsort_h atirva cpp-re  (alkalmas eles programokhoz)

#xtranslate STRING(<x>) => <"x">


/*  
    Hogyan hasznald?

    ARRLEN  ekkora array-t general a rendezes tesztelesehez

    STRLEN  az array-ben ilyen hosszu stringek lesznek,
            ha ez kis szam, akkor sok egyenlo lesz koztuk

    Ket rendezesi modszert vet ossze:

    1) ASORT  altalaban a konyvtari asort, ami libc-beli qsort-ot hiv

    2) QSORT  az itt keszult demo programok valamelyike 

    A #define-okba beirjuk a tesztelni kivant ertekeket, 
    ezutan a  programot ujraforditjuk,  es futtatjuk.

    A rendezes lefutasa utan kiirja a futas idejet.
    Kiirja, hogy hany egyenlo elem volt az array-ben.
    
    A tesztek mindig novekvo sorrendbe rendeznek.
    Ha a teszt futasa utan az array rendezettsege nem jo,
    akkor kiirja, hogy HOPP.

    A demo programok nemelyikeben be van drotozva a novekvo
    sorrendre torteno rendezes, es nem nezi, milyen blokkot kap.

    Az uj rendezo programoknak olyan osszehasonlito blokkot kell
    megadni, aminek a visszateresi erteke -1,0,1 (tehat nem  .t./.f.).
    A CCC konyvtarbeli uj asort valtozat elfogadja az ilyen blokkokat is.
    Megjegyzes: Az -1,0,1 visszateres elonye, hogy az egyenloseg
    megallapitasahoz nem kell oda-vissza kiertekelni a blokkot.

    Megjegyzes: A libc-beli qsort az array elemek swapolasat memmove-val
    vegzi. (Mi massal?)  A CCC VALUE-k ilyen masolasa nem szalbiztos.
    Ezert az asort-nak blokkolnia kell a szemetgyujtest. Az osszehasonlitasok
    kozben viszont megsem lehet blokkolva a szemtegyujtes, mert az 
    osszehasonlitas memoria objektumokat termelhet, ami kikenyszeritheti
    szemetgyujtest. Emiatt az asort-ban vacakolni kell az oda-vissza
    lockolassal. Ezzel szemben a sajat programok a VALUE-k swapolasahoz 
    a specialis (operator overload) VALUE ertekado  operatort hasznaljak, 
    ami szalbiztosra van megirva.
    
    A sajat rendezo programnak ket elonye van:
    
    1) -1,0,1 visszateresi erteku blokkot hasznalnak.

    2) A swap muvelet magatol szalbiztos.
*/

