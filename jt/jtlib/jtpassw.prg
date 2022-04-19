
/*
 *  CCC - The Clipper to C++ Compiler
 *  Copyright (C) 2005 ComFirm BT.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

//Olyan text mező,
//aminek nincs picture-je,
//minden karakter "*"-ként jelenik meg,
//az eredmény pedig: 
//base64.encode( text ) //ha salt1 és salt2 sincs megadva
//base64.encode( md5(text+saltX) ) //ha csak saltX van megadva
//base64.encode( md5( md5(text+salt1)+salt2 ) ) //ha salt1 és salt2 adott
 
//A jelszó mezőt lehet inicializálni (a valódi jelszóval),
//ez a terminálban "**...*"-ként látszik, és nem jön vissza,
//reaction a jtget-hez hasonlóan küldi a text változásait,
//changetext hatástalan, mert nem kezeli a terminál,
//a clear metódus törli a mezőt (reakcióban).

//Miért nincs egy ellenőrző metódus?
//
//1. Az ellenőrzés függ attól, hogy a szerver mit tárol.
//
//2. Az ellenőrzés az openssl könyvtárat hívná, 
//   amire csak akkor célszerű hivatkozni, ha tényleg kell,
//   hogy ne akadályozza feleslegesen a linkelést.

//Így lehet az ellenőrzést elvégezni, feltéve, 
//hogy ismerjük a jelszót, ami az alábbi példában "hopp":

#ifdef NOT_DEFINED

function passw_verif(dlg)

local p:=a"hopp"
local s1:=a"Próba"
local s2:=crypto_bin2hex(crypto_rand_pseudo_bytes(4))
local x:=dlg:pw:getpassword(bin2str(s1),bin2str(s2))

    ? 1, p
    ? 2, p:=crypto_md5(p+s1)
    ? 3, p:=crypto_md5(p+s2)
    ? 4, p:=base64_encode(p)
    ? 5, p:=bin2str(p)
    ? 6, x
    
    if( p==x  )
        alert( "Jelszó OK" )
        dlg:pw:clear
    else
        alert( "Jelszó eltér" )
    end
    
    return NIL
#endif    

// Változott a koncepció:
// Korábban a kódolt jelszót a terminál akciókor automatikusan küldte
// a kontroll értékeként, és az a varget metódussal volt lekérdezhető.
// Ez azonban nem adott alkalmat a salt beállítására, ami általában a
// felhasználó kilététől függ, ezért most a jelszót a terminál egyáltalán
// nem küldi akciónál, hanem csak a getpassword üzenetre válaszként,
// így van alkalom előzőleg beállítani a salt-okat, és nem küldünk 
// idejekorán félig rejtett jelszavakat

#include "jtelem.ch"

****************************************************************************
//jtpassw
****************************************************************************
class jtpassw(jtelem) 
    method  initialize
    method  changed         {|this|!this:laststate==this:text}
    method  savestate       {|this|this:laststate:=this:text}
    method  clear           {|this|this:laststate:=" ",this:text:=""}
    method  getpassword
    method  sign
  //method  authenticate

****************************************************************************
static function jtpassw.initialize(this,t,l,b,r) 
    this:(jtelem)initialize(t,l,b,r)
    return this

****************************************************************************
static function jtpassw.getpassword(this,salt1,salt2)
local rsp,dom,node,x

    x:='<jtmessage'
    x+=ATTR("pid",alltrim(str(getpid())))
    x+=ATTR("dialogid",this:dialogid)
    x+='>'
    x+="<control>"+this:name+"</control>"
    x+="<getpassword>"

    if( salt1!=NIL )
        x+="<salt1>"+cdataif(salt1)+"</salt1>"
    end

    if( salt2!=NIL )
        x+="<salt2>"+cdataif(salt2)+"</salt2>"
    end

    x+="</getpassword>"
    x+="</jtmessage>"

    this:send(x)

    while( (rsp:=jtsocket():recv)!=NIL  )
        dom:=xmlparser2New():parsestring(rsp)  
        node:=dom//:content[1]
        if( node:type=="password" )
            return node:gettext
        else
            jtsocket():enqueue(rsp)
        end
    end

    return NIL
  

****************************************************************************
/*
Hitelesítés digitális aláírással

1. A kuncsaft csinál magának egy RSA kulcspárt a Jáva keytools
   programjával. Esetleg később ehhez lehet csinálni frontendet.
   A keystore-ból exportálja a certificate-ot (vagy a public key-t):

   keytool -export -rfc -storepass ???? -alias vermes1 -file vermes1.cer
   
   Ebből egy ilyen filé lesz (vermes1.cer):
   
-----BEGIN CERTIFICATE-----
MIIDWTCCAkECBD4oB7UwDQYJKoZIhvcNAQEEBQAwcTELMAkGA1UEBhMCSFUxEDAOBgNVBAgTB0h1
...
BDaEmYaZykgRbYl4r/5ylixw6UuPr2k77VTJbMHpnPDUwY6pOxXMSvTcmssgc1m+RHo5PU4E4miC
YXiHOyct
-----END CERTIFICATE-----
   
   A certificate filét valahogy beküldi a szervernek, ahol azt tároljuk,
   pl. egy adatbázis memójában.
   
2. Egy dialogboxban megadja az alias nevét (aminél fogva a keystore-ban
   megtalálható a kulcs)  és a jelszót (ami szükséges a privát kulcs
   elővételéhez a keystore-ból). A jelszót nem küldi el a szervernek.
   
3. A szerver generál egy véletlen sorozatot, ezt aláíratja a terminállal,
   az aláírást pedig a certificate (public key) birtokában ellenőrzi.
   A certificate érvényességét egyáltalán nem ellenőrzi, csak azt nézi,
   hogy a private és public kulcsok tényleg párt alkossanak.
*/

****************************************************************************
static function jtpassw.sign(this,alias,data)

// A terminál a .keystore-ból előveszi az alias-hoz
// tartozó privát RSA kulcsot, és azzal aláírja data-t,
// az aláírást visszaküldi base64 kódolt formában.

local rsp,dom,node,x

    x:='<jtmessage'
    x+=ATTR("pid",alltrim(str(getpid())))
    x+=ATTR("dialogid",this:dialogid)
    x+='>'
    x+="<control>"+this:name+"</control>"
    x+="<sign>"
    x+="<alias>"+alias+"</alias>"
    x+="<data>"+bin2str(base64_encode(data))+"</data>"
    x+="</sign>"
    x+="</jtmessage>"

    this:send(x)

    while( (rsp:=jtsocket():recv)!=NIL  )
        dom:=xmlparser2New():parsestring(rsp)  
        node:=dom//:content[1]
        if( node:type=="signature" )
            return node:gettext
        else
            jtsocket():enqueue(rsp)
        end
    end

    return NIL


****************************************************************************
#ifdef AUTHENTICATE

// ha ez be volna fordítva,
// maga után húzná az openssl könyvtárat

static function jtpassw.authenticate(this,alias,cert)

// alias : a Jáva keystore-ban azonosítja a kulcsot
// cert  : pem formátumú CERTIFICATE vagy PUBLIC KEY 

local data:=crypto_rand_pseudo_bytes(32) 
local repl:=this:sign(alias,data) 
local sign:=base64_decode(repl)
 
    return crypto_verify(data,cert,sign)  //.t./.f.

#endif

****************************************************************************
 