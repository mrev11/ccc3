
//#define DEBUG


#define TEST_ARRLEN         2000
#define TEST_STRLEN         5

//#define TEST_ASCEND
//#define TEST_DESCEND

#define PIVOT_MEDIAN        median of 3,5,7 elements
//#define PIVOT_MIDDLE        middle element of the region
//#define PIVOT_RANDOM        1 random element

#define ISORT_TRESHOLD      10


#define   TEST_ASORT

#define   TEST_HSORTC
#define   TEST_QSORTC_3
#define   TEST_QSORTC_H
#define   TEST_QSORTC_HS

#define   TEST_HSORT
#define   TEST_HSORT_B
#define   TEST_QSORT_2
#define   TEST_QSORT_2X
#define   TEST_QSORT_3
#define   TEST_QSORT_H
#define   TEST_QSORT_HS
#define   TEST_QSORT_MT




#ifdef EZEK_VANNAK
#define   TEST_ASORT
#define   TEST_ISORT

#define   TEST_HSORTC
#define   TEST_QSORTC_3
#define   TEST_QSORTC_H
#define   TEST_QSORTC_HS

#define   TEST_HSORT
#define   TEST_HSORT_B
#define   TEST_QSORT_2
#define   TEST_QSORT_2X
#define   TEST_QSORT_3
#define   TEST_QSORT_H
#define   TEST_QSORT_HS
#define   TEST_QSORT_MT
#endif


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

    asort     - konyvtari asort
    isort     - insertion sort
    hsort     - heapsort
    hsort_b   - heapsort with bounce
    qsort_2   - quicksort, legegyszerubb elvi implementacio
    qsort_2x  - quicksort, legegyszerubb elvi implementacio indexekkel
    qsort_3   - quicksort, particionalas 3 reszre
    qsort_h   - quicksort, Hoare-fele particionalas
    qsort_hs  - quicksort, Hoare-fele particionalas, rekurzio helyett stack

    hsortc    - hsort    atirva C-be
    qsortc_3  - qsort_3  atirva C-be
    qsortc_h  - qsort_h  atirva C-be
    qsortc_hs - qsort_hs atirva C-be


    A #define-okba beirjuk a tesztelni kivant ertekeket,
    ezutan a  programot ujraforditjuk,  es futtatjuk.

    A rendezes lefutasa utan kiirja a futas idejet.
    Kiirja, hogy hany egyenlo elem volt az array-ben.
    Kiirja, hogy hany osszehasonlitast csinalt.

    A tesztek mindig novekvo sorrendbe rendeznek.
    Ha a teszt futasa utan az array rendezettsege nem jo,
    akkor kiirja, hogy WRONG.

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


