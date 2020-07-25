
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

//TARTALOM  : a tablaobjektumhoz tartozo filek nevei
//STATUS    : kozos, ifdef
//
//tabAlias(table,par) alias nev 
//tabFile(table,par)  fajl neve path es kiterjesztes nelkul
//tabPath(table,par)  .-bol a fajlhoz vezeto relativ ut (a vegen dirsep)
//tabExt(table,par)   a file kiterjesztese
//tabNameExt(table)   a filenev kiterjesztessel
//tabPathName(table)  .-ra relativ fajlspecifikacio
//tabIndexName(table) .-ra relativ indexfajl specifikacio
//tabMemoName()       memofile neve


#include "tabobj.ch"


#define UAT(x) upper(alltrim(x))

******************************************************************************
function tabAlias(table,par) //alias nev 
    return if(par==NIL, table[TAB_ALIAS], table[TAB_ALIAS]:=UAT(par))


******************************************************************************
function tabFile(table,par) //fajl neve path kiterjesztes nelkul
    return if(par==NIL, table[TAB_FILE], table[TAB_FILE]:=UAT(par))


******************************************************************************
function tabPath(table,par) //.-bol a fajlhoz vezeto relativ ut (a vegen dirsep)
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
function tabExt(table,par) //az adatfile aktualis kiterjesztese
    return if(par==NIL, table[TAB_EXT], table[TAB_EXT]:=UAT(par))


******************************************************************************
function tabNameExt(table) // filename.ext
    return table[TAB_FILE]+table[TAB_EXT]


******************************************************************************
function tabPathName(table) //.-ra relativ fajlspecifikacio
    return table[TAB_PATH]+table[TAB_FILE]+table[TAB_EXT]


******************************************************************************
function tabIndexName(table) //.-ra relativ fajlspecifikacio
    return table[TAB_PATH]+table[TAB_FILE]+tabIndexExt()


******************************************************************************
function tabMemoName(table)  //.-ra relativ fajlspecifikacio
    return table[TAB_PATH]+table[TAB_FILE]+tabMemoExt()


******************************************************************************

