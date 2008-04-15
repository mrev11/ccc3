
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

//TARTALOM  : a táblaobjektumhoz tartozó filék nevei
//STATUS    : közös, ifdef
//
//tabAlias(table,par) alias név 
//tabFile(table,par)  fájl neve path és kiterjesztés nélkül
//tabPath(table,par)  .-ből a fájlhoz vezető relatív út (a végén dirsep)
//tabExt(table,par)   a filé kiterjesztése
//tabNameExt(table)   a filénév kiterjesztéssel
//tabPathName(table)  .-ra relatív fájlspecifikáció
//tabIndexName(table) .-ra relatív indexfájl specifikáció
//tabMemoName()       memófilé neve


#include "tabobj.ch"


#define UAT(x) upper(alltrim(x))

******************************************************************************
function tabAlias(table,par) //alias név 
    return if(par==NIL, table[TAB_ALIAS], table[TAB_ALIAS]:=UAT(par))


******************************************************************************
function tabFile(table,par) //fájl neve path kiterjesztés nélkül
    return if(par==NIL, table[TAB_FILE], table[TAB_FILE]:=UAT(par))


******************************************************************************
function tabPath(table,par) //.-ből a fájlhoz vezető relatív út (a végén dirsep)
    if( par!=NIL )
        par:=UAT(par)
        par:=strtran(par,"/",dirsep()) //2000.09.29
        par:=strtran(par,"\",dirsep()) //2000.09.29 
        if( !empty(par) .and. !right(par,1)$":"+dirsep() )
            par+=dirsep()
        end
        table[TAB_PATH]:=par
    end
    return table[TAB_PATH]


******************************************************************************
function tabExt(table,par) //az adatfilé aktuális kiterjesztése
    return if(par==NIL, table[TAB_EXT], table[TAB_EXT]:=UAT(par))


******************************************************************************
function tabNameExt(table) // filename.ext
    return table[TAB_FILE]+table[TAB_EXT]


******************************************************************************
function tabPathName(table) //.-ra relatív fájlspecifikáció
    return table[TAB_PATH]+table[TAB_FILE]+table[TAB_EXT]


******************************************************************************
function tabIndexName(table) //.-ra relatív fájlspecifikáció
    return table[TAB_PATH]+table[TAB_FILE]+tabIndexExt()


******************************************************************************
function tabMemoName(table)  //.-ra relatív fájlspecifikáció
    return table[TAB_PATH]+table[TAB_FILE]+tabMemoExt()


******************************************************************************

