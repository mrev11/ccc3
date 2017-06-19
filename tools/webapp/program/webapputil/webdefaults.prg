

namespace webapp


function defaults()

//main paraméterezése: main(session_id,session_sck,session_user,*)

    addquitblock({||webapp.sessiondel(argv(1))})  //session_id, kilépés előtti takarítás
    webapp.ffsocket(argv(2)) //session_sck, eltárolja a socketet
    addquitblock( {||qout("QUITBLOCK")} )
    webapp.privatepush() //megjegyezi a böngészőbeli stack állását

    set date format 'yyyy-mm-dd'

    // frame-ek tulajdonságainak beállítása, három frame van:
    // - main    : a gyökér, az alkalmazás nem használja
    // - webapp  : main gyereke, ebben jelenik meg az alkalmazás
    // - frmaux  : main gyereke, teszt kiírásoknak (defaultban nem látszik)
    
    //webapp.frame
    //webapp.script('CODE.webapp.frame.frameBorder="1";')       //default: 0 (nincs border)
    webapp.script('CODE.webapp.frame.height="800";')            //frame magassága
    webapp.script('CODE.webapp.frame.width="1000";')            //frame szélessége

    //aux.frame
    //webapp.script('CODE.frmaux.frame.style.display="block";') //default: none (nem látszik)
    //webapp.script('CODE.frmaux.frame.frameBorder="1";')       //default: 0 (nincs border)
    //webapp.script('CODE.frmaux.frame.height="400";')          //frame magassága
    //webapp.script('CODE.frmaux.frame.width="1000";')          //frame sszélessége
    //frmaux.clear()

