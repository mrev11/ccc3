
2011.10.20
    paintline tárolja a képernyőt, és csak a változásokat írja ki,
    ez csökkenti az képernyő műveleteket (és a hunyorgást) z-ben.

2011.08.25
    setwsize-ban: cursor_focus=1;

    Enélkül mask.exe-ben (setwsize-zal indít) kezdetben nem villog a kurzor. 
    A villogáshoz előbb le kellett venni, majd újra ráadni a fókuszt az ablakra.
    (Így viszont esetleg előállhat a fordított szituáció.)
 

2010.03.08
    setcursor és blink szinkronizálva.

2009.05.01
    invalidate és paint szinkronizálva.

2008.10.15
    Javítva a képrnyőfrissítés (kisebb területeket rajzol újra). 
    Hardver-gyorsításos Xorg-gal a kurzor mozgatásakor hunyorgott 
    a z-editor képernyője. A letakart terminál kitakarásakor túl 
    sok CPU-t fogyasztott az újrarajzolás.

2008.08.25
    Kiszedve az 1 órás timeout.
    
2008.05.07

    Az újabb libxcb-s X környezetben szükséges az XInitThreads()
    hívás, noha a korábbi man szerint az nem kellene:

        It is only necessary to call this function if multiple threads 
        might use Xlib concurrently. If all calls to Xlib functions are 
        protected by some other access mechanism (for example, a mutual 
        exclusion lock in a toolkit or through explicit client programming), 
        Xlib thread initialization is not required. It is recommended that 
        single-threaded programs not call this function. 

    XInitThreads() nélkül ez a hiba keletkezik:

    terminal.exe: ../../src/xcb_lock.c:32: _XCBUnlockDisplay: Assertion `dpy->xcb->partial_request == 0' failed.

    A z-ben jobbra-balra mozgatva a kurzort, elég hamar kijön a hiba.
    Szerintem ez a libxcb implementáció belső hibája.
