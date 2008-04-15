
FreeBSD-n rosszul linkelődött össze a C és C++ kód,
amikor a könyvtárat a ccc2_tbwrapper-ből dlopen töltötte be. 
Látszólag hibátlan linkelés, dlopen, dlsym után a C++ modulból 
(_db_open) nem lehetett meghívni a C modult (__bt_open): nem érkezett 
meg a vezérlés, és a program nemdeterminisztukusan SIGSEGV-zett.
Ugyanaz a program jól működött, ha a ccc2_btbtx.so könyvtárat
közvetlenül linkeltem, és nem a ccc2_tbwrapper-ből töltöttem be.

Ez valószínűleg a dlopen (loader) hibája. A hiba elkerülése érdekében 
átírtam a C részeket C++-ra,  ezzel egyébként is előbbre vagyunk.
