
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


//A jtconnect hibaágainak tesztelése.
//Fontos, hogy a jtconnect minél értelmesebben reagáljon a hibákra, 
//mert elég nehéz átlátni a helyzetet. Ez a program végigpróbálja a 
//lehetséges hibákat.

******************************************************************************
function main()
    jtencoding("UTF-8")
    alertblock({|t,a|jtalert(t,a)})
    msgloop( makedlg() )

******************************************************************************
static function msgloop(dlg)
    dlg:show
    while( NIL!=dlg:getmessage )
    end

******************************************************************************
static function makedlg()

local dlg:=jtdialogNew()
local m,mi

    dlg:caption:="Menu Application" 

    m:=jtmenuNew()
    m:text:="Egy pulldown menü"
    m:mnemonic:="M"

    m:additem( mi:=jtmenuitemNew() )
               mi:text:="listen 46001 plain <- connect plain  OK"
               mi:actionblock:={||jtconnect("localhost",46001)}
               //OK

    m:additem( mi:=jtmenuitemNew() )
               mi:text:="listen 46002 ssl <- connect ssl  OK"
               mi:actionblock:={||jtconnect("localhost",46002,.t.)}
               //OK

    m:additem( mi:=jtmenuitemNew() )
               mi:text:="listen 46001 plain <- connect ssl  ERROR: jtsocket.recv, unrecognized SSL"
               mi:actionblock:={||jtconnect("localhost",46001,.t.)}

               //a terminál SSL kapcsolatot akar csinálni
               //a szerver a jtsocket protokollt ellenőrzi
               //=> jtsocket.recv hibára fut

    m:additem( mi:=jtmenuitemNew() )
               mi:text:="listen 46002 ssl <- connect plain  ERROR: SSL_accept timeout"
               mi:actionblock:={||jtconnect("localhost",46002)}

               //a terminál konnektál (plain) majd vár
               //a szerver az SSL kapcsolat felépítésére vár
               //=> a kommunikáció beragad, SSL_accept timeout


    m:additem( mi:=jtmenuitemNew() )
               mi:text:="listen 46003 no exe <- connect plain  ERROR: exec failed"
               mi:actionblock:={||jtconnect("localhost",46003)}

               //a terminál konnektál 
               //a listener el akarja indítani a nem létező exe-t
               //=> a spawn->fork child ágából exec failed jön
               //=> a terminál kapcsolata megszakad


    m:additem( mi:=jtmenuitemNew() )
               mi:text:="listen 46003 no exe <- connect ssl  ERROR: exec failed, connection reset"
               mi:actionblock:={||jtconnect("localhost",46003,.t.)}

               //u.a. mint az előző
               //a terminál konnektál 
               //a listener el akarja indítani a nem létező exe-t
               //=> a spawn->fork child ágából exec failed jön
               //=> a terminál kapcsolata megszakad: connection reset


    m:additem( mi:=jtmenuitemNew() )
               mi:text:="port 46004 no listener <- connect plain  ERROR: connection refused"
               mi:actionblock:={||jtconnect("localhost",46004)}
               //a terminál nem tud konnektálni
               //=> connection refused


    m:additem( mi:=jtmenuitemNew() )
               mi:text:="port 46004 no listener <- connect ssl  ERROR: connection refused"
               mi:actionblock:={||jtconnect("localhost",46004,.t.)}
               //a terminál nem tud konnektálni
               //=> connection refused


    dlg:add(m) 


    return dlg

******************************************************************************
