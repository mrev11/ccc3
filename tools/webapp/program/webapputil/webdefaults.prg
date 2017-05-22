

namespace webapp


function defaults()

//main paraméterezése: main(session_id,session_sck,session_user,*)

    addquitblock({||webapp.sessiondel(argv(1))})  //session_id, kilépés előtti takarítás
    webapp.ffsocket(argv(2)) //session_sck, eltárolja a socketet
    //argv(3) session_user, a bejelentkezett kontó felhasználó azonosítója
    webapp.privatepush() //megjegyezi a böngészőbeli stack állását

    addquitblock( {||qout("QUITBLOCK")} )
    set date format 'yyyy-mm-dd'

    // frame-ek tulajdonságainak beállítása, három frame van:
    // - main    : a gyökér, az alkalmazás nem használja
    // - webapp  : main gyereke, ebben jelenik meg az alkalmazás
    // - frmaux  : main gyereke, teszt kiírásoknak (defaultban nem látszik)
    


    //a százalékban megadott méretezés megszűnt

    //webapp.frame
    //webapp.script('CODE.webapp.frame.frameBorder="1";')       //default: 0 (nincs border)
    //webapp.script('CODE.webapp.frame.height="100%";')         //frame magassága a böngészőablakhoz képest
    //webapp.script('CODE.webapp.frame.width="75%";')           //frame sszélessége a böngészőablakhoz képest

    webapp.script('CODE.webapp.frame.height="800";')            //frame magassága
    webapp.script('CODE.webapp.frame.width="1000";')            //frame szélessége

    //aux.frame
    //webapp.script('CODE.frmaux.frame.style.display="block";') //default: none (nem látszik)
    //webapp.script('CODE.frmaux.frame.frameBorder="1";')       //default: 0 (nincs border)
    //webapp.script('CODE.frmaux.frame.height="10%";')          //frame magassága a böngészőablakhoz képest
    //webapp.script('CODE.frmaux.frame.width="50%";')           //frame sszélessége a böngészőablakhoz képest
    //frmaux.clear()

