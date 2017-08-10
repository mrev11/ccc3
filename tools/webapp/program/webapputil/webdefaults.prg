

namespace webapp


function defaults()

//main paraméterezése: main(session_id,session_sck,session_user,*)

    set date format 'yyyy-mm-dd'

    addquitblock({||webapp.sessiondel(argv(1))})  //session_id, kilépés előtti takarítás
    webapp.ffsocket(argv(2)) //session_sck, eltárolja a socketet
    addquitblock( {||qout("QUITBLOCK")} )
    webapp.privatepush() //megjegyezi a böngészőbeli stack állását


