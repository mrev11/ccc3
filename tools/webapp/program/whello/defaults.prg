
namespace webapp.demo

function defaults()

    addquitblock({||webapp.sessiondel(argv(1))}) //session_id, kilépés előtti takarítás
    webapp.ffsocket(argv(2)) //session_sck, eltárolja a socketet
    webapp.privatepush() //megjegyezi a böngészőbeli stack állását
  
    set date format 'yyyy-mm-dd'
  
    // frame-ek tulajdonságainak beállítása, három frame van:
    // - main    : a gyökér, az alkalmazás nem használja
    // - webapp  : main gyereke, ebben jelenik meg az alkalmazás
    // - frmaux  : main gyereke, teszt kiírásoknak (defaultban nem látszik)
  
    //webapp.frame
    webapp.script('CODE.webapp.frame.frameBorder="0";')       //default: 0 (nincs border)
    webapp.script('CODE.webapp.frame.height="400";')          //frame magassága
    webapp.script('CODE.webapp.frame.width="800";')           //frame szélessége
  
    //aux.frame
    webapp.script('CODE.frmaux.frame.style.display="none";')  //default: "none" (nem látszik)
    webapp.script('CODE.frmaux.frame.height="200";')          //frame magassága
    webapp.script('CODE.frmaux.frame.width="800";')           //frame sszélessége

    webapp.debug(.f.)


    //az alkalmazások általában meghívják ezt a függvényt
    //és utána még tudnak a beállításokon módosítani ezt-azt.    
    