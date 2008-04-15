
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

//A minimális listener program olyan módosítása,
//ami UNIX-on helyettesíti a socket utilityt.


function main(port,torun)

local s,c,r,e

    while( .t. )

        s:=socket() 
        setsockopt(s,"REUSEADDR",.t.)
        
        if( bind(s,val(port))<0 )
            ? "bind failed" 
            quit
        end

        listen(s)     
        
        c:=accept(s);  ? "acccept:", getpeername(c)

        sclose(s) //server socket    

        r:="&"+alltrim(str(c))
        run  ( torun+str(c)+" <"+r+" >"+r+" &" )
 
        sclose(c) //client socket
    end
 
    return NIL


#ifdef MEGJEGYZESEK 

    Ez is működik: 

    s:=socket() 
    bind(s,val(port)) 
    listen(s)     
 
    while( .t. )
        c:=accept(s)   
        r:="&"+alltrim(str(c))
        run  ( torun+str(c)+" <"+r+" >"+r+" &" )
        sclose(c)      
    end
    
    Így azonban az s socket is öröklődik
    (nem csak a c), ami esetleg galibát okoz,
    ha a kliens hibás működéssel véletlenül
    beletrafál a socketbe. A hiba javítható 
    threadekkel, forkkal, fcntl-lel, stb., 
    a legbiztosabb azonban,  ha egyszerűen 
    lezárjuk a socketet. Az NT-s remstart 
    is így működik.
    
    Minden eddigi UNIX-os remstart komoly
    hibája, hogy a remstart lelövése miatt
    a child processzek is kilépnek, holott
    az volna kívánatos, hogy a remstart 
    leállítasa csak az új bejelentkezéseket
    akadályozza meg, a korábbiak pedig
    zavartalanul fussanak, a remstart
    újraindítása pedig újra engedélyezze 
    a kliensek belépését.
#endif 
