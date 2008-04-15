
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

//Minimális listener Linuxra és Windowsra.
//
//Indítása: listener port command
//
//A program figyel az első paraméterben magadott porton.
//Ha jelentkezik egy kliens, akkor végrehajtódik a második
//paraméterben kapott parancs (szerver) úgy, hogy megkapja parancssori
//argumentumként a megnyílt socketet. Ezen a socketen a kliens
//és a szerver tetszés szerint kommunikálhat. Egy szerver program 
//indítása után a listener a socketet lezárja, és tovább figyel,
//azaz vár a következő kliensre.

function main(port,torun)

local s,c,r

    while( .t. )

        ?  ">socket:", str( s:=socket()       ,3,0)
        ?? " bind:"  , str( bind(s,val(port)) ,3,0) 
        ?? " listen:", str( listen(s)         ,3,0) 
        ?? " accept:", str( c:=accept(s)      ,3,0) 
        ?? " sclose:", str( sclose(s)         ,3,0) 
        
        #ifdef _UNIX_

            //így lehet a standard inputot és 
            //outputot a socketbe irányítani
            //r:="&"+alltrim(str(c))
            //run  ( torun+str(c)+" <"+r+" >"+r+" &" )

            run( torun+str(c)+" &" )
 
        #else
            run( "start "+torun+str(c) )

        #endif

        ?? " sclose:", str( sclose(c)         ,3,0) 
    end

    return NIL

