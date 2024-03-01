
//#define DEBUG

#define TEST_ARRLEN         1500000
#define TEST_STRLEN         8

//#define TEST_ASCEND
//#define TEST_DESCEND

#define PIVOT_MEDIAN        median of 3 random elements
#define PIVOT_RANDOM        1 random element
#define PIVOT_MIDDLE        fallback

#define ISORT_TRESHOLD      10



/*  
    Hogyan hasznald?

    TEST_ARRLEN  ekkora array-t general a rendezes tesztelesehez

    TEST_STRLEN  az array-ben ilyen hosszu stringek lesznek,
                 ha ez kis szam, akkor sok egyenlo lesz koztuk
                 
    TEST_ASCEND  ha ez definialva van, akkor a bemeneti array
                 rendezetlen helyett novekvo sorrendu             

    TEST_DESCEND ha ez definialva van, akkor a bemeneti array
                 rendezetlen helyett csokkeno sorrendu             

    Tobb rendezesi modszert vet ossze:

    isort     - insertion sort
    asort     - konyvtari asort
    qsort_2   - legegyszerubb elvi implementacio
    qsort_2x  - legegyszerubb elvi implementacio indexekkel
    qsort_3   - particionalas 3 reszre
    qsort_h   - Hoare-fele particionalas
    qsort_hs  - Hoare-fele particionalas, rekurzio helyett stack

    qsortc_3  - qsort_3  atirva C-be
    qsortc_h  - qsort_h  atirva C-be
    qsortc_hs - qsort_hs atirva C-be


    A #define-okba beirjuk a tesztelni kivant ertekeket, 
    ezutan a  programot ujraforditjuk,  es futtatjuk.

    A rendezes lefutasa utan kiirja a futas idejet.
    Kiirja, hogy hany egyenlo elem volt az array-ben.
    
    A tesztek mindig novekvo sorrendbe rendeznek.
    Ha a teszt futasa utan az array rendezettsege nem jo,
    akkor kiirja, hogy WRONG.

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
    
    A sajat rendezo programoknak ket elonye van:
    
    1) -1,0,1 visszateresi erteku blokkot hasznalnak.

    2) A swap muvelet magatol szalbiztos.
*/

