
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

//TARTALOM  : filé struktúrájának frissítése az objektum szerint
//STATUS    : közös, ifdef
//
//function tabUpgrade(table,force)     //struktúra frissítése
//function tabAutoUpgrade(table,force) //frissít, ha szükséges


#include "tabobj.ch"

//konvertálja a tényleges filét az objektumnak megfelelően,
//ha a híváskor a filé nyitva van, akkor nem csinál semmit,
//hiszen megnyitható filénél nincs szükség konverzióra,
//konverzió után a filé lezárva marad, azaz :isopen nem változik
//
//konverziós szabályok:
//    nem enged mezőt kihagyni
//    mező típusa nem lehet eltérő
//    mezőhosszt hajlandó megváltoztatni (csökkent/növel)
//
//    force==.t.-vel erőszakos konverziót csinál
//
//visszatérés:
//    .t., ha OK
//    .f., ha a szabályok nem engedik a konverziót
//    NIL, ha a filé foglalt


******************************************************************************
function tabUpgrade(table,force) //.t.=OK, NIL=foglalt, .f.:=nem konvertálható

local result
local savefile:=tabFile(table)
local saveindex:=tabIndex(table)

    tranNotAllowedInTransaction(table,"upgrade")

    if( tabIsopen(table)>0 )
        //nyitva van, 
        //nincs szükség konverzióra

        result:=.t. 

    elseif( tabSlock(table,{||0})<=0 )
        //ha nem lehet rá szemafort tenni,
        //akkor másvalaki foglalkozik vele,
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

    //DBFNTX-ben az indexeket ki kell venni az objektumnól, 
    //mert a tmp filénév képzés miatt (+"$") a transzformált
    //indexnevek hosszabbak volnának 8-nál, és ezen elakad

    //DATIDX-ben és Btrieve-ben nem szabad az objektumból kivenni, 
    //mert akkor a filé resource-ába sem kerülnének be az indexek
    
    //DBFCTX-ben mindegy
#endif    

    //a filéből kiolvasott adatok alapján
    //létrehozunk egy (nem statikus) táblát, 
    //amivel megnyitható a filé (tabVerify átengedi)

    tabfil:=tabStructInfo(table)

    if( tabfil==NIL )
        return NIL //foglalt
    elseif( empty(tabfil) )
        return .f. //nem állapítható meg a struktúra, nem konvertálható
    end
    
    //ne tegyen rá szemafor lockot,
    //az ugyanis összeakadna a már meglévő,
    //azonos nevű, de másik objektumban (table)
    //nyilvántartott lockkal:

    tabfil[TAB_SLOCKCNT]:=1 
    
    if( !tabOpen(tabfil,OPEN_EXCLUSIVE,{||.f.}) )
        return NIL //foglalt
    end

    //ideiglenes néven létrehozzuk az objektummal megegyező 
    //struktúrájú üres filét, először töröljük a maradékot
    //meg kell gondolni az NTX-ek ütközését

    logged:=table[TAB_LOGGED]
    table[TAB_LOGGED]:=.f.
 
    tabFile(table,TMPCHR+tabFile(table))
    tabDelTable(table) 
    tabCreate(table)
    tabOpen(table,OPEN_APPEND) 

    //összeszedjük a konvertálandó oszlopokat

    colfil:=tabColumn(tabfil)  //eredeti filé
    colobj:=tabColumn(table)   //új filé az objektum alapján

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
            //akkor konvertálható,
            //ha minden mező megvan az új táblában,
            //egyezik a típusa, 
            //egyébként jelezni kell, hogy nem konvertálható
            //force==.t. erőszakos konverziót ír elő
            
            if( force!=.t. )
                tabClose(table)
                tabClose(tabfil)
                return .f. //nem konvertálható
            end
        end
    next

    //konvertálunk
    
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
            value:=eval(konvtab[n][1]) //olvas a régiből
            eval(konvtab[n][2],value)  //ír az újba
        next
        tabSkip(tabfil)
    end
    msg:=message(msg,toupgrade+str(pos)+total)
    
    tabClose(table)
    tabClose(tabfil)
    
    
    //előállt a konvertált filé ideiglenes néven, 
    //el kell még végezni a backup-ot és az átnevezéseket
    //tabfil : structinfo-ból, name (eredeti filé)
    //table  : program-ból, $name (konvertált filé)
    
    if( !tabBackup(tabfil) )
        //? "nem sikerült elmenteni a régi verziót"
        return NIL 
    end

    if( !tabRename(table,tabFile(tabfil)) )
        //? "nem sikerült átnevezni az új filét"
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



