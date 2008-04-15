
Hiányosságok az XML-RPC implementációkban (TODO)
================================================


I. CCC  (Vermes M., version 0.9.00)

//Nincs base64 támogatás. Az XML-RPC szabvány szerint a string
//a '<' és '&' kivételével mindent tartalmazhat (pl. 0 byte-ot is),
//ezért szerintem nincs nagy szükség a base64-re. Azért megcsináljuk.
//Kész van.

//A string típusban védeni kell a '<' (&lt)  és '&' (&amp) karaktereket.
//Ez jelenleg még hiányzik.
//Kész van.

//Támogatni kellene a hostname<-->ipaddr konverziót, a mostani
//változat csak az ip címeket fogadja el.
//Kész van.


A CCC xml elemzője trimeli a stringeket (egyelőre nem nyúlok
az xml elemzőhöz).

A  dateTime.iso8601 típus idő része mindig 00:00:00 azért, 
mert a CCC dátum típusában nincs idő információ.

A programok jelenleg nem figyelik a partner http verziószámát
és a fejlécben esetlegesen küldött "Connection:" fejlécet.
A későbbiekben megoldandó, hogy a socket kapcsolat életben tartása
vagy lezárása a verziószámnak és fejlécnek megfelelő legyen.

 

II. PHP (Edd Dumbill, version 1.0b8)

A PHP nem engedi meg a string típusban az ékezetes karaktereket.
Ez szerintem nélkülözhetetlen. Az XML-RPC egyszerűsége és használhatósága 
ui. nagy mértékben az üzenetek olvashatóságán múlik. Ezért nem
volna szerencsés, ha a stringeket base64-re kellene cserélni.
Meg kell nézni, hogy milyen szinten történik a hibaágra térés,
pl. lehet, hogy már az alapkönyvtárból használt xml elemző
kidobja az ékezetes karaktereket, ebben az esetben az <?xml?>
tagban megadott karakterkészlettel is kéne kísérletezni.
Küldeni hajlandó az ékezetes betűket, csak fogadni nem.

A PHP a '<' és '&' karaktereken kívül másokat is véd, 
ami zavart okoz, és egyébként is az xml szabvány világosan megmondja, 
hogy csak az előbbi kettőt kell védeni. Minek a túlbuzgóság?

A PHP kliens bután olvassa a http üzeneteket, ui. nem addig olvas,
amíg meg nem jön a Content-Length mennyiségű adat (a Content-Length
fejléc a szabvány szerint kötelező, és kötelezően pontos), hanem
addig, amíg a szerver le nem zárja a socketet. Ezért a CCC szervereket
jelenleg a keepalive:=.f. attribútummal kell futtatni.

A PHP-beli xmlrpc kliens a CCC-hez képest túlságosan alacsony szintű,
ezért körülményes használni. Minden rpc híváshoz létre kell hozni egy 
message objektumot, és annak  ki/becsomagolásával küldés/fogadásával
alkalmazás szinten kell foglalkozni. A CCC-ben egysoros távoli
hívás kódolásához a PHP-ben kb. 10 sor kell.

A fentiek miatt az egész PHP XML-RPC implementációt felül kellene
vizsgálni, vagy keresni egy fejlettebbet.



