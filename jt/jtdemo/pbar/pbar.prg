
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

#include "pbar.dlg"

******************************************************************************
function main()

local dlg,msg,n
    jtencoding("UTF-8")
  
    alertblock({|t,a|jtalert(t,a)})
    quitblock({||qout(argv(0)+" terminated"+endofline())})
  
//--------------------------------------------------------------------------
// automatikus progress bar
//--------------------------------------------------------------------------

    //Az olyan message-ek,
    //mint amik a táblaobjektum indexelésében, 
    //vagy a packolásban óhatatlanul előjönnek, megtalálják  
    //a felső dialogboxban levő "progressbar" nevű kontrollt,
    //vagy ha nincs ilyen, akkor létrehoznak maguknak
    //agy automatikus ablakot (mint itt).

    pbar1("Türelem rózsát terem")
    pbar1("percent")
 
    msg:=message(msg,"MESSAGE:")
    sleep(3000)
    for n:=1 to 300
        message(msg,"MESSAGE:"+str(n))
        sleep(20)
    next
    sleep(1000)
    message(msg)
    

    //Ha a sleep-eket kiveszem, akkor a messagek
    //gyorsabban lefutnak, mint ahogy a Jáva meg tudná
    //jeleníteni az ablakot.
 
//--------------------------------------------------------------------------
// jtdialogba ágyazott progress bar
//--------------------------------------------------------------------------

    //Eddig minden a terminál által automatikusan
    //létrehozott ablakban jelent meg. Most lérehozunk
    //egy dialogboxot, ameiben van egy "progressbar"
    //és egy "pbar" nevű kontroll. 
    

    dlg:=pbarNew()
    dlg:pbar:minvalue:=200
    dlg:pbar:maxvalue:=500

    dlg:show
    
    //Most a default (progressbar nevű) progressbar
    //kapja meg az üzeneteket, nem jön létre új ablak.

    pbar1("Default progressbar")
    
    //Végül az általános eset:
    //a speciálisan felparaméterezett pbar-t használjuk
    //(a dlg:show előtt kell megadni a paramétereket)
    
    for n:=dlg:pbar:minvalue to dlg:pbar:maxvalue 
        dlg:pbar:setbar(n,"Próba szerencse"+str(n));sleep(10) 
    next
    dlg:pbar:setbar(dlg:pbar:maxvalue,"KÉSZ");sleep(1000) 
    dlg:pbar:clearbar;sleep(1000)
 

    return NIL


******************************************************************************
function pbar1(text)
local n, pb:=jtprogbarNew()

    //Ha a progressbar-t a jterminal automatikusan hozza létre,
    //akkor az csak a setbar message hatására fog létrejönni,
    //azért hiába paraméterezzük itt a pb objektumot,
    //csak azok az adatok mennek át, amiket a setbar átvisz.
    //A pb attribútomok csak akkor hatnak, ha pb be van ágyazva 
    //egy jtdialogba, és a jtdialog üzenet átviszi az adatokat. 
    //Ez sajnos egy csapda. 

    pb:setbar(0,text)
    sleep(3000)

    for n:=1 to 100 
        pb:setbar();sleep(50)
    next

    pb:setbar(0,"HOPP");sleep(1000)
    pb:clearbar;sleep(1000)

    return NIL


******************************************************************************
function message(pb,text)  //egyszerű message implementáció
    if( pb==NIL )
        pb:=jtprogbarNew() 
    elseif( text==NIL )
        pb:clearbar
        return NIL
    end
    pb:setbar(,text)
    return pb


******************************************************************************
function message1(pb,text)  //kicsit komplikáltabb message implementáció 
static sec
    if( pb==NIL )
        pb:=jtprogbarNew()
        pb:caption:=argv(0)
    elseif( text==NIL )
        pb:clearbar
        return NIL
    end
    if( !sec==seconds() )
        pb:setbar(0,text)
        pb:caption:=NIL
        sec:=seconds() 
    end
    return pb

******************************************************************************
 