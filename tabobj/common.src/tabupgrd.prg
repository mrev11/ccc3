
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

//TARTALOM  : file strukturajanak frissitese az objektum szerint
//STATUS    : kozos, ifdef
//
//function tabUpgrade(table,force)     //struktura frissitese
//function tabAutoUpgrade(table,force) //frissit, ha szukseges


#include "tabobj.ch"

//konvertalja a tenyleges filet az objektumnak megfeleloen,
//ha a hivaskor a file nyitva van, akkor nem csinal semmit,
//hiszen megnyithato filenel nincs szukseg konverziora,
//konverzio utan a file lezarva marad, azaz :isopen nem valtozik
//
//konverzios szabalyok:
//    nem enged mezot kihagyni
//    mezo tipusa nem lehet eltero
//    mezohosszt hajlando megvaltoztatni (csokkent/novel)
//
//    force==.t.-vel eroszakos konverziot csinal
//
//visszateres:
//    .t., ha OK
//    .f., ha a szabalyok nem engedik a konverziot
//    NIL, ha a file foglalt


******************************************************************************
function tabUpgrade(table,force) //.t.=OK, NIL=foglalt, .f.:=nem konvertalhato

local result
local savefile:=tabFile(table)
local saveindex:=tabIndex(table)

    tranNotAllowedInTransaction(table,"upgrade")

    if( tabIsopen(table)>0 )
        //nyitva van, 
        //nincs szukseg konverziora

        result:=.t. 

    elseif( tabSlock(table,{||0})<=0 )
        //ha nem lehet ra szemafort tenni,
        //akkor masvalaki foglalkozik vele,
        //nem lehet upgradelni 
       
        result:=NIL        

    else

        result:=_upgrade(table,force)
 
        tabFile(table,savefile)
        tabIndex(table,saveindex)
        tabSunlock(table)
    end

    return result


******************************************************************************
static function _upgrade(table,force) 

local tabfil
local colfil,colobj
local konvtab:={}, n, i
local fld,len,typ,kiolvas,beir,value
local toupgrade,total,pos,msg
local name1,name2
local logged
 
#ifdef _DBFNTX_    
    tabDelIndex(table) 
    tabIndex(table,{})

    //DBFNTX-ben az indexeket ki kell venni az objektumnol, 
    //mert a tmp filenev kepzes miatt (+"$") a transzformalt
    //indexnevek hosszabbak volnanak 8-nal, es ezen elakad

    //DATIDX-ben es Btrieve-ben nem szabad az objektumbol kivenni, 
    //mert akkor a file resource-aba sem kerulnenek be az indexek
    
    //DBFCTX-ben mindegy
#endif    

    //a filebol kiolvasott adatok alapjan
    //letrehozunk egy (nem statikus) tablat, 
    //amivel megnyithato a file (tabVerify atengedi)

    tabfil:=tabStructInfo(table)
    
    if( tabfil==NIL )
        return NIL //foglalt
    elseif( empty(tabfil) )
        return .f. //nem allapithato meg a struktura, nem konvertalhato
    end
    
    //ne tegyen ra szemafor lockot,
    //az ugyanis osszeakadna a mar meglevo,
    //azonos nevu, de masik objektumban (table)
    //nyilvantartott lockkal:

    tabfil[TAB_SLOCKCNT]:=1 
    
    if( !tabOpen(tabfil,OPEN_EXCLUSIVE,{||.f.}) )
        return NIL //foglalt
    end

    //ideiglenes neven letrehozzuk az objektummal megegyezo 
    //strukturaju ures filet, eloszor toroljuk a maradekot
    //meg kell gondolni az NTX-ek utkozeset

    logged:=table[TAB_LOGGED]
    table[TAB_LOGGED]:=.f.

    if( NIL!=tabKeepDeleted(tabfil).and.NIL==tabKeepDeleted(table) )
        tabKeepDeleted(table,tabKeepDeleted(tabfil))
    end
 
    tabFile(table,TMPCHR+tabFile(table))
    tabDelTable(table) 
    tabCreate(table)
    tabOpen(table,OPEN_APPEND) 

    //osszeszedjuk a konvertalando oszlopokat

    colfil:=tabColumn(tabfil)  //eredeti file
    colobj:=tabColumn(table)   //uj file az objektum alapjan

    for n:=1 to len(colfil)

        fld:=colfil[n][COL_NAME]  
        typ:=colfil[n][COL_TYPE]  
        len:=colfil[n][COL_WIDTH] 
        
        i:=ascan(colobj,{|c|c[COL_NAME]==fld})
        
        if( 0<i .and. colobj[i][COL_TYPE]==typ )

            kiolvas:=colfil[n][COL_BLOCK]
            beir   :=colobj[i][COL_BLOCK]
            aadd(konvtab,{kiolvas,beir})
        
        else
            //akkor konvertalhato,
            //ha minden mezo megvan az uj tablaban,
            //egyezik a tipusa, 
            //egyebkent jelezni kell, hogy nem konvertalhato
            //force==.t. eroszakos konverziot ir elo
            
            if( force!=.t. )
                tabClose(table)
                tabClose(tabfil)
                return .f. //nem konvertalhato
            end
        end
    next

    //konvertalunk
    
    toupgrade:=@"Copy  "+tabPathName(tabfil)
    total:="/"+alltrim(str(tabLastrec(tabfil)))
    pos:=0
    msg:=message(msg,toupgrade+str(pos)+total)

    tabGoTop(tabfil)
    while( !tabEof(tabfil) )
        if( ((++pos)%20)==0 )
            msg:=message(msg,toupgrade+str(pos)+total)
        end
        
        tabAppend(table) 

        for n:=1 to len(konvtab)
            value:=eval(konvtab[n][1]) //olvas a regibol
            eval(konvtab[n][2],value)  //ir az ujba
        next
        tabSkip(tabfil)
    end
    msg:=message(msg,toupgrade+str(pos)+total)
    
    tabClose(table)
    tabClose(tabfil)
    
    
    //eloallt a konvertalt file ideiglenes neven, 
    //el kell meg vegezni a backup-ot es az atnevezeseket
    //tabfil : structinfo-bol, name (eredeti file)
    //table  : program-bol, $name (konvertalt file)
    
    if( !tabBackup(tabfil) )
        //? "nem sikerult elmenteni a regi verziot"
        return NIL 
    end

    if( !tabRename(table,tabFile(tabfil)) )
        //? "nem sikerult atnevezni az uj filet"
        return NIL 
    end

    sleep(100)
    message(msg)

    table[TAB_LOGGED]:=logged
    tabWriteChangeLogUpgrade(table) 

    return .t.


******************************************************************************
function tabAutoUpgrade(table,force)

local err, result:=.t.

    begin sequence
        tabOpen(table)
        tabClose(table)

    recover err <tabstructerror>
        tabClose(table)
        result:=tabUpgrade(table,force)

    recover err <tabindexerror>
        tabClose(table)
        result:=tabUpgrade(table,force)

    end sequence

    return result


******************************************************************************



