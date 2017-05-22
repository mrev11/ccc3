
namespace webapp

**************************************************************************************
function opensessionfile(doc) // megnyit egy sessiondirben levő dokumentumot
local url

    url:='webapp/dnload/SESSIONID/'+doc
    url::=strtran("SESSIONID",webapp.session.id())
    webapp.script("window.open('URL')"::strtran("URL",url))

    // Firefox. 
    // Ahhoz, hogy window.open működjön
    // 1) Content-ben engedélyezni kell a pop-up window-kat
    // 2) Applications-ban be kell állítani a document viewer-eket
    //
    // Kellemetlen a feleslegesen megnyíló/becsukódó ablak:
    // Először megnyílik egy üres böngésző ablak.
    // Ha a lekért fájl létezik, akkor az üres ablak becsukódik.
    // Ha a lekért fájl nem létezik, akkor az új ablakban: Error 404.
    // Ha Applications-ban 'Always ask' van beállítva -> Open/Save dialog.
    // Ha Applications-ban egy viewer van beállítva -> elindul.
    //
    // Kipróbálva: txt, jpg, pdf, dvi fájlokra.
    

    // Chromium. 
    // Mindig megjelenik egy üres ablak (magától nem csukódik be).
    // Ha a lekért fájl nem létezik -> Error 404 (az új ablakban),
    // Ha létezik -> az új ablak bal alsó sarkában levő gomb indítja a viewert.
    // Bizonyos típusokra még választani kell: discard/keep.
    // Kipróbálva: txt, jpg, pdf, dvi fájlokra.


    // Explorer. Nincs info.

**************************************************************************************
function loadsessionfile(doc) // megnyit egy sessiondirben levő dokumentumot
local url:='webapp/dnload/SESSIONID/'+doc
local code:="CODE.frmaux.frame.src='URL'; " 
    url::=strtran("SESSIONID",webapp.session.id())
    code::=strtran('URL',url)
    webapp.script(code)
    
    // Ez FF-en van kipróbálva.
    // Elvileg ez megjelenítené frmaux-ban a megadott url-ről letöltődő oldalt.
    // Tapasztalat szerint frmaux tartalma nem változik.
    // Feltételezés szerint azért nem, mert a webapp szerver a session adatokat
    // mindig 'Content-Type: application/octet-stream' fejléccel küldi,
    // ezért az FF bináris adatokra számít, amit külső viewerrel kezel.
    
    // A window.open (az előző függvényben) kellemetlen tulajdonsága,
    // hogy megnyílik egy (üres) FF böngésző ablak, aztán az rögtön eltűnik,
    // és csak ezután jön föl az Open/Save dialog.
    // Az iframe-es letöltésben nincs ez a felesleges ablak.
    // Az iframe-es letöltéshez nem kell a popupok engedélyezése.
    // Nem tudható, hogy lehet-e erre a feature-re számítani.
    // Esetleg lehetne másik hidden iframe-et használni.
    
    // Ha a lekért oldal mégsem létezik, akkor mégsem application/octet-stream
    // válasz jön, hanem Error 404, ami megjelenik frmaux-ban (de legalább nem 
    // a webapp frame romlik el).


    // Chromium. Működik.
    // Explorer. Nem ismeretes, hogyan viselkedik.


**************************************************************************************
function linksessionfile(id,text,doc) 

// Csinál egy linket az id elemben
// a link URL-je a doc-ra  mutat (file a sessiondirben)
// a link szövege text

// Ennek a működése azon múlik, hogy a webapp szerver a session adatokat 
// mindig 'Content-Type: application/octet-stream' fejléccel küldi,
// és ezért az FF nem cseréli az oldalt, hanem menti vagy külső megjelenítővel
// megjeleníti az adatokat. A csere az alkalmazás elromlását jelentené.

// Probléma: Ha a fájl (amire a link mutat) nem létezik,
// akkor mégsem 'Content-Type: application/octet-stream' header jön,
// hanem egy 404-es error page, amire böngésző elhagyja az oldalt.
// Ezért a link target-jét célszerű másik iframe-re állítani.


local link:=text+" <a href='URL' target='frmaux'>"+doc+"</a>"
local url:='webapp/dnload/SESSIONID/'+doc
    url::=strtran("SESSIONID",webapp.session.id())
    link::=strtran("URL",url)
    webapp.innerHTML(id,link)


**************************************************************************************
