
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

//TARTALOM  : a memofile muveletei
//STATUS    : kozos
//
//function tabMemoField(table,col)         memo-e a megadott oszlop
//function tabMemoHandle(table)            memofile handlere
//function tabMemoActive(table)            van-e nyitva memofile
//function tabMemoCount(table)             a memo mezok szama
//function tabMemoWrite(table,memo,value)  memo beirasa (memo=C10 offset)
//function tabMemoRead(table,memo)         memo kiolvasasa (memo=C10 offset)
//function tabMemoPict()                   memo picture


#include "fileio.ch"
#include "tabobj.ch"

/*
Hogyan lehet letrehozni memo mezot?
===================================

A memo mezo neve DBM-mel kell kezdodjom,
es C10 tipusa kell legyen, pl. DBMPROBA C10.
Clipperben (es ezert mindenhol) a memo mezok nevenek
mar a DBM utani elso karakterben kulonbozniuk kell.

A memo ertek egy kulon fileben tarolodik
a DATIDX(DBD) formatumban ennek kiterjesztese DBD
a DBFCTX(DBM) es DBFNTX(DBM) formatumokban a kiterjesztes DBM.

Maga a formatum (a kiterjesztestol eltekintve) azonos,
a jelenlegi formatumot azonosito nev: "DBM Format 1.0".
A formatum kulonbozo blokkmertu filek egyideju kezelesere kepes,
a blokkmeret a headerben tarolodik, 
a legkisebb lehetseges meret 64 byte, a default 256 byte.

Amikor egy memo mezonek erteket adunk, akkor a memo filebe az uj
ertek azonnal kiirodik, egyuttal a rekordbufferbe beirodik a memo 
elso blokkjanak uj offsete C10 formatumban. 
Ha ezutan a rekord commitolodik akkor az uj offseten levo memo ertek
fog a rekordhoz tartozni. Ha a commit elmarad, akkor a DBF (DAT)
altal tarolt offset nem valtozik, es igy a memo erteke is valtozatlan
(a korabbi memoertek a commit elott sosem irodik felul).
A memo felulirasaval feleslegesse valo blokkok a commit utan 
bekerulnek a memofile szabadlistajaba. Ha a commit elmarad 
(pl. ALT-C kilepeskor), akkor a kiirt blokkok zarvannya valnak,
es csak a file packolasakor szunnek meg.


Hol kell modositani a tobbi forrast?
====================================

Tablaobjektum:

 1. fel kell venni a TAB_MEMOHND attributumot a tablaobjektumba
 2. fel kell venni a TAB_MEMODEL attributumot a tablaobjektumba
 3. tabCreate-ban letre kell hozni a memo filet (ha van memo mezo)
 4. tabUse-ban meg kell nyitni a memo filet (ha van memo mezo)
 5. tabClose-ban le kell zarni a memo filet, ha nyitva van
 6. tabAddColumn-ban specialis blokkot kell kesziteni a memo mezoknek
 7. tabAddColumn-ban a memo mezoknek "@S30 XXX..." picture-t adunk
 8. tabCommit-ban a TAB_MEMODEL lista memoit torolni kell
 9. tabPack-ot ki kell egesziteni a memo file packolasaval (megy enelkul is)
10. tabZap-ot ki kell egesziteni a memo zapolasaval (megy enelkul is)
11. tabAppendRecord-ot ki kell egesziteni a memok atmasolasaval


Alkalmazasok:

1. kdirmodi.prg-ban az editalast kicsit meg kell valtoztatni (megy enelkul is)

*/


#define MEMO_WIDTH    10


****************************************************************************
function tabMemoField(table,col) //memo-e a megadott mezo?

    if( valtype(col)!="A" )
        col:=tabGetColumn(table,col)
    end

    return left(col[COL_NAME],3)=="DBM" .and.;
           col[COL_TYPE]$"CX" .and.;
           col[COL_WIDTH]==10 


****************************************************************************
function tabMemoHandle(table)  //az objektum memofilejenek handlere
    return table[TAB_MEMOHND]


****************************************************************************
function tabMemoActive(table)  //van-e nyitva memofile
local memohnd:=table[TAB_MEMOHND]
    return valtype(memohnd)=="N" .and. memohnd>=0


****************************************************************************
function tabMemoCount(table)  //a memo mezok szama

local column:=tabColumn(table),n
local count:=0

    for n:=1 to len(column)
        if( tabMemoField(table,column[n]) )
            count++
        end
    next
    return count
        

****************************************************************************
function tabMemoDel(table)
local n,tmd,ltmd
    //? "MEMODEL  ",table[TAB_MEMODEL]
    if( (tmd:=table[TAB_MEMODEL])!=NIL )
        ltmd:=len(tmd)
        for n:=1 to ltmd
            _db_memodel(table[TAB_BTREE],tmd[n])
            //alert("HOPP "+ tmd[n]::bin2str)
        next
        table[TAB_MEMODEL]:=NIL
    end
    


****************************************************************************
function _v1_tabMemoDel(table)

local n,tmd,ltmd,mhnd

    if( table[TAB_MEMODEL]!=NIL )
        tmd:=table[TAB_MEMODEL]
        mhnd:=table[TAB_MEMOHND]
        ltmd:=len(tmd)
        for n:=1 to ltmd
            memoDeleteValue(mhnd,tmd[n])
        next
        table[TAB_MEMODEL]:=NIL
    end
    return NIL

    
****************************************************************************
function tabMemoRead(table,memo)
local value:=a""
    //? "MEMOREAD ","memo",memo
    if( !empty(memo))
        value:=_db_memoread(table[TAB_BTREE],memo)
    end
    //?? " value",value
    return value


****************************************************************************
function _v1_tabMemoRead(table,memo)

local value:=a""
local offset:=val(memo)

    if( offset!=0 )
        value:=memoGetValue(tabMemoHandle(table),offset)
    end
    return value

    
****************************************************************************
function tabMemoWrite(table,memo,value)
local vlen:=len(value)
    //? "MEMOWRITE","memo",memo,"value",value
    if( !empty(memo) )
        if( table[TAB_MEMODEL]==NIL )
            table[TAB_MEMODEL]:={memo}
        else
            aadd(table[TAB_MEMODEL],memo)
        end
    end
    memo:=a""
    if( vlen>0 )
        memo:=_db_memowrite(table[TAB_BTREE],value)
    end
    //?? "",memo
    return memo


****************************************************************************
function _v1_tabMemoWrite(table,memo,value)

local vlen:=len(value)
local offset

    if( !empty(memo) )
        if( table[TAB_MEMODEL]==NIL )
            table[TAB_MEMODEL]:={val(memo)}
        else
            aadd(table[TAB_MEMODEL],val(memo))
        end
    end
    memo:=""

    if( vlen>0 )
        offset:=memoAddValue(tabMemoHandle(table),value)
        memo:=str(offset,MEMO_WIDTH,0)
    end
    return str2bin(memo)


****************************************************************************
function tabMemoPict()
    return "@RS48 "+replicate("X",256)
                         

****************************************************************************
