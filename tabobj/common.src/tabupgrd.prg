
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
local origname
local error


    //a filebol kiolvasott adatok alapjan
    //letrehozunk egy (nem statikus) tablat,
    //amivel megnyithato a file (tabVerify atengedi)

    tabfil:=tabStructInfo(table)

    if( tabfil==NIL )
        return NIL //foglalt
    elseif( empty(tabfil) )
        return .f. //nem allapithato meg a struktura, nem konvertalhato
    end
    tabfil[TAB_ALIAS]:="upgrade" //megkulonboztetes


    //ne tegyen ra szemafor lockot,
    //az ugyanis osszeakadna a mar meglevo,
    //azonos nevu, de masik objektumban (table)
    //nyilvantartott lockkal:

    tabfil[TAB_SLOCKCNT]:=1

    if( !tabOpen(tabfil,OPEN_EXCLUSIVE,{||.f.}) )
        return NIL //foglalt
    end


    // ideiglenes neven letrehozzuk az objektummal
    // kompatibilis strukturaju ures filet

    if( force==.t. )
        // hard konverzio:
        // ezen az agon nincs vegrehajtva tabVerify()
        // a strukturat kicsereljuk a tdc-beli strukturara
        // mindegy, milyen a bt struktura, csak a tdc szamit
        // a fajlban levo plusz mezok megszunnek
        // az eltero tipusok magvaltoznak
    else
        // soft konverzio:
        // a strukturat konvertaljuk
        // az eredeti fajl struktura es
        // a tdc-beli struktura uniojara
        // tabVerify() az egyesitett strukturat
        // beteszi a table objektumba
        // (ami most MEGVALTOZIK a tdc-hez kepest)

        begin
            tabVerify(table,.t.,{tabColumn(tabfil)::arr2bin,tabIndex(tabfil)::arr2bin})
        recover error <tabobjerror>
            // soft modszerrel nem konvertalhato
            return .f.
        end
    end

    logged:=table[TAB_LOGGED]
    table[TAB_LOGGED]:=.f.

    if( NIL!=tabKeepDeleted(tabfil).and.NIL==tabKeepDeleted(table) )
        tabKeepDeleted(table,tabKeepDeleted(tabfil))
    end

    origname:=tabFile(table)
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


    //feltoltes elott titkositunk
    //kezdetben a fajl lenyegeben ures
    tabCrypt(table,tabCrypt(tabfil))


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

    tabFile(table,origname)
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



