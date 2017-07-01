

namespace webapp


function defaults()

//main paraméterezése: main(session_id,session_sck,session_user,*)

    addquitblock({||webapp.sessiondel(argv(1))})  //session_id, kilépés előtti takarítás
    webapp.ffsocket(argv(2)) //session_sck, eltárolja a socketet
    addquitblock( {||qout("QUITBLOCK")} )
    webapp.privatepush() //megjegyezi a böngészőbeli stack állását

    set date format 'yyyy-mm-dd'


    webapp.debug(.f.)
    frmaux.clear()  


    // három frame van:
    // - main    : a gyökér, az alkalmazás nem használja
    // - webapp  : main gyereke, ebben jelenik meg az alkalmazás
    // - frmaux  : main gyereke, teszt kiírásoknak (defaultban nem látszik)


    //webapp frame beállításai

        webapp.visible(.t.)
        webapp.border(.f.)
        webapp.size(1000,800)

    //frmaux frame beállításai

        frmaux.visible(.f.)
        frmaux.border(.t.)
        frmaux.size(1000,400)




