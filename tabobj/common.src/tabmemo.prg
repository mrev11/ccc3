
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

//TARTALOM  : a memófilé műveletei
//STATUS    : közös
//
//function tabMemoField(table,col)         memó-e a megadott oszlop
//function tabMemoHandle(table)            memófilé handlere
//function tabMemoActive(table)            van-e nyitva memófilé
//function tabMemoCount(table)             a memó mezők száma
//function tabMemoWrite(table,memo,value)  memó beírása (memo=C10 offset)
//function tabMemoRead(table,memo)         memó kiolvasása (memo=C10 offset)
//function tabMemoPict()                   memó picture


#include "fileio.ch"
#include "tabobj.ch"

/*
Hogyan lehet létrehozni memó mezőt?
===================================

A memó mező neve DBM-mel kell kezdődjöm,
és C10 típusa kell legyen, pl. DBMPROBA C10.
Clipperben (és ezért mindenhol) a memó mezők nevének
már a DBM utáni első karakterben különbözniük kell.

A memó érték egy külön filében tárolódik
a DATIDX(DBD) formátumban ennek kiterjesztése DBD
a DBFCTX(DBM) és DBFNTX(DBM) formátumokban a kiterjesztés DBM.

Maga a formátum (a kiterjesztéstől eltekintve) azonos,
a jelenlegi formátumot azonosító név: "DBM Format 1.0".
A formátum különböző blokkmértű filék egyidejű kezelésére képes,
a blokkméret a headerben tárolódik, 
a legkisebb lehetséges méret 64 byte, a default 256 byte.

Amikor egy memó mezőnek értéket adunk, akkor a memó filébe az új
érték azonnal kiíródik, egyúttal a rekordbufferbe beíródik a memó 
első blokkjának új offsete C10 formátumban. 
Ha ezután a rekord commitolódik akkor az új offseten lévő memó érték
fog a rekordhoz tartozni. Ha a commit elmarad, akkor a DBF (DAT)
által tárolt offset nem változik, és igy a memó értéke is változatlan
(a korábbi memóérték a commit előtt sosem íródik felül).
A memó felülírásával feleslegessé váló blokkok a commit után 
bekerülnek a memófilé szabadlistájába. Ha a commit elmarad 
(pl. ALT-C kilépéskor), akkor a kiírt blokkok zárvánnyá válnak,
és csak a filé packolásakor szűnnek meg.


Hol kell módosítani a többi forrást?
====================================

Táblaobjektum:

 1. fel kell venni a TAB_MEMOHND attribútumot a táblaobjektumba
 2. fel kell venni a TAB_MEMODEL attribútumot a táblaobjektumba
 3. tabCreate-ban létre kell hozni a memó filét (ha van memó mező)
 4. tabUse-ban meg kell nyitni a memó filét (ha van memó mező)
 5. tabClose-ban le kell zárni a memó filét, ha nyitva van
 6. tabAddColumn-ban speciális blokkot kell készíteni a memó mezőknek
 7. tabAddColumn-ban a memó mezőknek "@S30 XXX..." picture-t adunk
 8. tabCommit-ban a TAB_MEMODEL lista memóit törölni kell
 9. tabPack-ot ki kell egészíteni a memó filé packolásával (megy enélkül is)
10. tabZap-ot ki kell egészíteni a memó zapolásával (megy enélkül is)
11. tabAppendRecord-ot ki kell egészíteni a memók átmásolásával


Alkalmazások:

1. kdirmodi.prg-ban az editálást kicsit meg kell változtatni (megy enélkül is)

*/


#define MEMO_WIDTH    10


****************************************************************************
function tabMemoField(table,col) //memó-e a megadott mező?

    if( valtype(col)!="A" )
        col:=tabGetColumn(table,col)
    end

    return left(col[COL_NAME],3)=="DBM" .and.;
           col[COL_TYPE]=="C" .and.;
           col[COL_WIDTH]==10 


****************************************************************************
function tabMemoHandle(table)  //az objektum memófiléjének handlere
    return table[TAB_MEMOHND]


****************************************************************************
function tabMemoActive(table)  //van-e nyitva memófilé
local memohnd:=table[TAB_MEMOHND]
    return valtype(memohnd)=="N" .and. memohnd>=0


****************************************************************************
function tabMemoCount(table)  //a memó mezők száma

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
local offset:=val(memo)

    if( offset!=0 )
        value:=memoGetValue(tabMemoHandle(table),offset)
    end
    return value

    
****************************************************************************
function tabMemoWrite(table,memo,value)

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
/*
function tabMemoPack(table)

//vázlat arra, 
//  hogyan kell a memó filét packolni,
//  a hatékonyság kedvéért bele fogom szőni
//  a kódot a tabPack-ba, hogy ne kelljen 
//  kétszer végigmenni a filén

local mname:=tabMemoName(table)                                  //eredeti
local tname:=tabPath(table)+TMPCHR+tabFile(table)+tabMemoExt(table) //temporális
local bname:=tabPath(table)+tabFile(table)+"_DBM"+".BAK"         //backup

local mhnd:=tabMemoHandle(table), thnd
local column:=tabColumn(table),n
local blk:={},v

    memoCreate(tname)
    thnd:=memoOpen(tname)
    
    for n:=1 to len(column)
        if( tabMemoField(table,column[n]) )
            aadd(blk,column[n][COL_BLOCK])
        end
    next
    
    tabGoTop(table)
    while( !tabEof(table) )
    
        for n:=1 to len(blk)
            v:=eval(blk[n])            //olvasás a memóból
            table[TAB_MEMOHND]:=thnd   //temporális handler 
            eval(blk[n],v)             //írás a temporális memóba
            table[TAB_MEMOHND]:=mhnd   //memo handler vissza
        next
        
        tabSkip(table)
    end
    
    fclose(mhnd); ferase(bname); frename(mname,bname)
    fclose(thnd); ferase(mname); frename(tname,mname)

    table[TAB_MEMOHND]:=fopen(tabMemoName(table),FO_READWRITE+FO_SHARED)
    #ifdef _UNIX_   
      setcloexecflag(table[TAB_MEMOHND],.t.)
    #else
      table[TAB_MEMOHND]:=fdup(table[TAB_MEMOHND],.f.,.t.)
    #endif
    
    return NIL

*/
****************************************************************************
