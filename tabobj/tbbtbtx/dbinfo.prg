
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

#include "fileio.ch"
#include "tabobj.ch"


//table alapjan keszit egy olyan masik nem statikus tarolasu
//objektumot, ami a leheto leginkabb konzisztens a lemezfilevel
//az igy keszult objektum alkalmas kell legyen a filek megnyitasara,
//igy a struktura elteresenek vizsgalatara (tabVerify, KVERIF), 
//es a struktura konverziojara (tabUpgrade)
//
//pelda: tabOpen DBSTRUCT elteres miatt nem tudja megnyitni a filet,
//ekkor tabStructInfo-val kiolvassuk a file tenyleges strukturajat,
//ez osszehasonlithato az objektummal, es elvegezheto a konverzio.
//
//visszateres:
//1. !empty: sikerult hasznalhato (kompatibilis) infot gyujteni
//2. {}    : a file strukturaja nem allapithato meg (inkompatibilis)
//3. NIL   : a file foglalt, nem lehetett beleolvasni


******************************************************************************
function tabStructInfo(table) //megnyithato objektum a file info alapjan

//table alapjan keszit egy olyan masik nem statikus tarolasu
//objektumot, ami a leheto leginkabb konzisztens a lemezfilevel
//az igy keszult objektum alkalmas kell legyen a filek megnyitasara,
//igy a struktura elteresenek vizsgalatara (tabVerify, KVERIF), 
//es a struktura konverziojara (tabUpgrade)

    return tabResource( tabPathName(table) )


******************************************************************************
function tabResource(dbfspec,alias:="")

local table,n
local column,index
local db:=_db_open(fopen(dbfspec,FO_READ+FO_SHARED))
local path,file,ext
local poffs:=max(rat(dirsep(),dbfspec),rat(":",dbfspec))
local eoffs:=rat(".",dbfspec)

    if( db!=NIL )
        path:=substr(dbfspec,1,poffs)
        file:=substr(dbfspec,poffs+1,if(eoffs>poffs,eoffs-poffs-1,NIL))
        ext:=if(eoffs>poffs,substr(dbfspec,eoffs),"")
        
        table:=tabNew0(file)
        tabPath(table,path)
        tabFile(table,file)
        tabExt(table,ext)
        
        // Inkompatibilis valtozas!
           tabAlias(table,alias) 
        // Korabban automatikus aliast kapott a tabla.
        // Az ilyenkor keszulo (alias->field) => fldblk tablazat 
        // utkozik a statikus TABLE:open altal keszitett tablazattal.
        // Ezert most csak akkor keszulnek alias->field blockok, 
        // ha tabResource-ban meg van adva egy nemures alias.
        // Kovetkezmeny: Nem static tarolasu tablakban csak akkor
        // lehet alias->field formaval hivatkozni a mezokre, 
        // ha kulon aliast adunk a tablanak.
        
        column:=readColumn(db)
        for n:=1 to len(column)
            tabAddColumn(table,column[n])
        next

        index:=readIndex(db)
        for n:=1 to len(index)
            index[n][2]:=file
            tabAddIndex(table,index[n])
        next

        if( _db_srcord(db,"deleted")>=0 )
            // letezik a delete index
            // de nem tudjuk a keep erteket
            // beallitjuk a default 1 napot
            tabKeepDeleted(table,1)
        end
        
        _db_close(db)
    end

    return table


******************************************************************************
static function readColumn(btree)
local buffer:=replicate(x"00",4096)
    _db_read1(btree,buffer,1,0)
    return bin2arr(buffer)


******************************************************************************
static function readIndex(btree)
local buffer:=replicate(x"00",4096)
    _db_read1(btree,buffer,1,1)
    return bin2arr(buffer)


******************************************************************************
