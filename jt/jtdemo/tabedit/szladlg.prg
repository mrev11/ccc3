
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

#include "table.ch"
#include "table.szamla.tdh"

#include "dlg_szamla.dlg"

******************************************************************************
function szladlg()

local dlg:=dlg_szamlaNew()
local msg,result:=.f.

    dlg:recno:picture:="@RN 999999"
    dlg:recno:focusable:=.f.
    dlg:recno:varput(SZAMLA:position)
    
    dlg:szamlaszam:picture:="@R 99999999-NNNNNNNN-99999999"
    dlg:szamlaszam:focusable:=.f.
    dlg:szamlaszam:varput(SZAMLA_SZAMLASZAM)

    dlg:egyenleg:picture:="@RN 999,999,999,999.99"
    dlg:egyenleg:focusable:=.f.
    dlg:egyenleg:varput(SZAMLA_EGYENLEG)

    dlg:nev:picture:="@R "+replicate("X",30)
    dlg:nev:varput(SZAMLA_NEV)

    dlg:tul:varput(SZAMLA_TULMENFLAG)

    dlg:kivdatum:picture:="@D"
    dlg:kivdatum:focusable:=.f.
    dlg:kivdatum:varput(SZAMLA_KIVDATUM)
  
    dlg:show
    while( (msg:=dlg:getmessage)!=NIL )
    
        if( msg=="x" )
            dlg:close
        elseif( msg=="ok" )
            SZAMLA:rlock
            SZAMLA_NEV:=dlg:nev:varget
            SZAMLA_TULMENFLAG:=dlg:tul:varget
            SZAMLA:unlock
            result:=.t.
            dlg:close
        end
    end
    
    return result //.t., ha mentés volt

******************************************************************************
