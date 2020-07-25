
FreeBSD-n rosszul linkelodott ossze a C es C++ kod,
amikor a konyvtarat a ccc2_tbwrapper-bol dlopen toltotte be. 
Latszolag hibatlan linkeles, dlopen, dlsym utan a C++ modulbol 
(_db_open) nem lehetett meghivni a C modult (__bt_open): nem erkezett 
meg a vezerles, es a program nemdeterminisztukusan SIGSEGV-zett.
Ugyanaz a program jol mukodott, ha a ccc2_btbtx.so konyvtarat
kozvetlenul linkeltem, es nem a ccc2_tbwrapper-bol toltottem be.

Ez valoszinuleg a dlopen (loader) hibaja. A hiba elkerulese erdekeben 
atirtam a C reszeket C++-ra,  ezzel egyebkent is elobbre vagyunk.
