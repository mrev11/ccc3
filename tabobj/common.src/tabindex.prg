
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

//TARTALOM  : tabla objektum index metodusok platformfuggetlen resze
//STATUS    : kozos, ifdef
//
//function tabAddIndex(table,index)     allando indexet ad table-hoz
//function tabGetIndex(table,ind)       index nev -> sorszam
//function tabIndex(table,change)       indexek strukturaja
//function tabScanIndex(table,index)    index keresese az objektumban

#include "tabobj.ch"


******************************************************************************
function tabAddIndex(table,index) //allando indexet ad table-hoz

// A fajl megnyitasa elott kell hivni, csakis az objektumgeneralo
// fuggvenyben. A betett indexek allandoak, nem valtoztathatok,
// es meg kell egyezniuk a lemezfajlban nyilvantartott indexelessel.
//
// index szerkezete: {name,file,{col1,col2,...},type}
// az elso harom elem kotelezo
//    name: az index logikai neve
//    file: az indexfile(k) neve (ha vannak index filek)
//    coln: az indexet alkoto oszlopok neve/sorszama
//    type: .f. allando, a program automatikusan beallitja

local n, column:=index[IND_COL], cix, col

    asize(index,IND_SIZEOF)

    index[IND_NAME]:=upper(alltrim(index[IND_NAME]))
    index[IND_FILE]:=alltrim(index[IND_FILE])
    index[IND_TYPE]:=!empty(index[IND_TYPE])
    
    for n:=1 to len(column)
        if( valtype(cix:=column[n])=="C" )
            column[n]:=cix:=tabColNumber(table,cix)
        end

        col:=tabColumn(table)[cix]
        if(tabMemoField(table,col))
            taberrOperation("tabAddIndex")
            taberrDescription(@"memo field not permitted")
            taberrArgs(col)
            tabError(table) 
        end

#ifdef _DBFCTX_
        col[COL_KEYFLAG]:=.t.
        tabSetColBlock(table,col)
#endif
#ifdef _BTBTX_
        col[COL_KEYFLAG]:=.t.
        tabSetColBlock(table,col)
#endif
    next

    aadd(table[TAB_INDEX],index)
    return index


******************************************************************************
function tabGetIndex(table,ind) //index nev -> sorszam

// ind lehet 
// 1) az index logikai neve 
// 2) az index szotarbeli sorszama

local aIndex:=table[TAB_INDEX], name

    if( valtype(ind)=="C" )

        name:=upper(alltrim(ind))
        ind:=ascan(aIndex,{|x|x[IND_NAME]==name})

        if( ind==0 )
            taberrOperation("tabGetIndex")
            taberrDescription(@"unknown index name")
            taberrArgs(name)
            tabError(table) 
        end
    end 
    
    if( 0<=ind .and. ind<=len(aIndex) )
        return ind
    end
    return NIL


******************************************************************************
function tabIndex(table,change) //indexek strukturaja
local prev:=table[TAB_INDEX]
    if( change!=NIL )
        table[TAB_INDEX]:=change
    end
    return prev


******************************************************************************
function tabScanIndex(table,index) //index keresese az objektumban

// Megnezi, hogy egy index benne van-e az objektumban.
// Az oszloplistak (kulcsszegmensek) egyezosege szerint keres,
// ha megtalalta visszaadja a kulcs sorszamat, egyebkent NIL-t.

local icol:=index[IND_COL]     // a keresett index oszlopai
local length:=len(icol)        // keresett index oszlopainak szama
local iname:=index[IND_NAME]   // a keresett index neve
local tindex:=tabIndex(table)  // table index struktura
local tcol, tname, n, c
local iseg, tseg

    iname:=upper(alltrim(iname))

    // a ciklust visszafele kell jaratni, hogy
    // eloszor az ideiglenes indexeket talalja meg,
    // ugyanis ezek keresese a tipikus

    for n:=len(tindex) to 1 step -1
    
        tcol:=tindex[n][IND_COL]
        tname:=tindex[n][IND_NAME]

        if( len(tcol)==length .and. tname==iname   )
        
            for c:=1 to length
            
                iseg:=icol[c] 
                if( valtype(iseg)=="C" )
                    iseg:=tabColNumber(table,iseg)
                end

                tseg:=tcol[c] 
                if( valtype(tseg)=="C" )
                    tseg:=tabColNumber(table,tseg)
                end
            
                if( !iseg==tseg )
                    exit
                elseif( c==length )
                    return n  //kulcs sorszam 
                end
            next
        end
    next
    return NIL


******************************************************************************
static function PrintIndex(table,aindex) //teszt celu printeles

local n,s
local indfil,indnam,indcol

    for n:=1 to len(aindex)    
    
        indnam:=aindex[n][IND_NAME]
        indfil:=aindex[n][IND_FILE]
        indcol:=aindex[n][IND_COL]
        
        if( empty(indnam) )
            indnam:="unknown"
        end

        ?  padr(indnam,10),padr(indfil,24)

        ?? " {"
        for s:=1 to len(indcol)
            if(s>1)
                ?? ","
            end
          //?? alltrim(str(indcol[s]))                //sorszamos kiiras
            ?? tabColumn(table)[indcol[s]][COL_NAME]  //nev szerinti kiiras
        next
        ?? "}"
    next
    return NIL

    
******************************************************************************

