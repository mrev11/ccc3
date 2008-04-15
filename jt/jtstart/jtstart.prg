
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

//Keserves dolog Jáva terminálos programot fejleszteni,
//mert nagyon lassan kászálódik elő a Jáva.
//Ez a kis program arra való, hogy folyamatosan
//benntartsa a Jáva terminált, az éppen fejlesztett 
//(és újra még újra lefordított) programot pedig
//ebből indítjuk egy push buttonnal.

function main(cmd)
local dlg,but,msg

    jtautostart()
    jtencoding("UTF-8")
 
    dlg:=jtdialogNew(10,10,12,50)
    dlg:layout:="vbox"
    dlg:caption:="CCC starter" 

    but:=jtpushNew()
    but:name:="start"
    but:text:=cmd
    but:icon:="icons/32/exec.png"
 
    dlg:add(but)
    dlg:show
    
    while( NIL!=(msg:=dlg:getmessage()) )
        if( msg=="start"  )
            jtrun( cmd )
        end
    end

    return NIL
    