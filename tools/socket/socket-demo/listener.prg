
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

//Minimalis listener Linuxra es Windowsra.
//
//Inditasa: listener port command
//
//A program figyel az elso parameterben magadott porton.
//Ha jelentkezik egy kliens, akkor vegrehajtodik a masodik
//parameterben kapott parancs (szerver) ugy, hogy megkapja parancssori
//argumentumkent a megnyilt socketet. Ezen a socketen a kliens
//es a szerver tetszes szerint kommunikalhat. Egy szerver program 
//inditasa utan a listener a kliens socketet lezarja, es tovabb figyel,
//azaz var a kovetkezo kliensre.

function main(port,torun)

local s,c,r

    ?  "socket:", s:=socket()
    ?  "bind:"  , bind(s,val(port))
    ?  "listen:", listen(s)

    while( .t. )

        ? "accept:", c:=accept(s)
        
        #ifdef _UNIX_
            run( torun+str(c)+" &" )
        #else
            run( "start "+torun+str(c) )

        #endif

        ? "sclose:", sclose(c)
    end
