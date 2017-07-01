
namespace webapp.demo

function defaults()

    addquitblock({||webapp.sessiondel(argv(1))}) //session_id, kilépés előtti takarítás
    webapp.ffsocket(argv(2)) //session_sck, eltárolja a socketet
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
        webapp.size(800,400)

    //frmaux frame beállításai

        frmaux.visible(.f.)
        frmaux.border(.t.)
        frmaux.size(800,200)


    //az alkalmazások általában meghívják ezt a függvényt
    //és utána még tudnak a beállításokon módosítani ezt-azt.    
    