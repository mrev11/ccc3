
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

#include "sign.dlg"

******************************************************************************
function main()
    ? jtversion()
    alertblock({|t,a|jtalert(t,a)})
    quitblock({||qout(argv(0)+" terminated"+endofline())})
    
    msgloop( signNew() )
    return NIL

******************************************************************************
static function msgloop(dlg)
local msg
    dlg:show
    while( NIL!=(msg:=dlg:getmessage)  )
        if( msg=="esc" )
            dlg:close

        elseif( msg=="ok" )
            authenticate(dlg)

        end
    end
    return NIL

******************************************************************************
static function  authenticate(dlg)

local alias:=dlg:alias:varget
local cert:=jtcertificate(alias)
local data:=crypto_rand_pseudo_bytes(32) 
local repl:=dlg:passw:sign(alias,data) 
local sign:=base64_decode(repl)

    memowrit(alias+".cer",cert) 
 
    if( crypto_verify(data,cert,sign) )
        alert( "Success" )
    else
        alert( "Failed" )
    end
    
    return NIL

#ifdef MEGJEGYZES

  Ha meg tudnánk győződni a cert tanúsítvány érvényességéről,
  akkor ez a módszer abszolút hitelesítést tenne lehetővé.
  A program a jelen formájában csak azt ellenőrzi, hogy a 
  public és private kulcsok megfelelnek-e egymásnak. 

  Hitelesítésre csak úgy alkalmazható a módszer, ha valami más,
  megbízható módon beszerezzük az ügyfél nyilvános kulcsát.
  Pl. amikor már jelszóval azonosította magát, akkor elkérjük
  tőle (mint a programban), és letároljuk.

#endif

******************************************************************************
