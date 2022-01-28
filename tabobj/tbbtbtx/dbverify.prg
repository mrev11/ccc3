
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

******************************************************************************
//Public interface
//
//function tabVerify(table,upgrade)  //objektum <--> file (belso)
 
******************************************************************************
function tabVerify(table,upgrade:=.f.,resource) 

// egyezteti a bt fajl es a table objektum adatait
// a table objektum strukturaja (col/ind) megvaltozhat
// az eredeti bt file es a tdc-beli struktura uniojara

local uniocol,upgcol
local unioind,upgind
local err,n

    // ? "tabVerify",upgrade,tabFile(table),tabAlias(table),oref(table)
    // tabPrintStruct(table)

    {uniocol,upgcol}:=tabVerifyColumn(table,resource)
    {unioind,upgind}:=tabVerifyIndex(table,resource,uniocol) 

    // ide csak akkor jon
    // ha a strukturakat lehet egyesiteni
    // egyebkent mar kivetelt dobott
    
    // uniocol - az egyesített oszlop struktura 
    // unioind - az egyesített index struktura 
    // upgcol  - az upgrade-et kikenyszerito elso oszlop a tdc-ben
    // upgind  - az upgrade-et kikenyszerito elso index a tdc-ben
    
    if( !upgrade .and. upgcol!=NIL )
        taberrOperation("tabVerify")            
        taberrDescription(@"different table/column struct (needs upgrade)")
        taberrArgs(upgcol)            
        taberrDefault(.t.)
        tabStructError(table) //break
    end

    if( !upgrade .and. upgind!=NIL )
        taberrOperation("tabVerify")            
        taberrDescription(@"different table/index struct (needs upgrade)")
        taberrArgs(upgind)            
        taberrDefault(.t.)
        tabIndexError(table) //break
    end
    
    // ide akkor jon
    // ha a tabla upgrade nelkul megnyithato
    // vagy tabUpgrade(table,force:=.t.)-ban van
    
    // ujraepiti az oszlopokat
    table[TAB_COLUMN]:={}
    for n:=1 to len(uniocol)
        tabAddcolumn(table,uniocol[n])
    next

    // ujraepiti az indexeket
    table[TAB_INDEX]:={}
    for n:=1 to len(unioind)
        tabAddindex(table,unioind[n])
    next

    // ? "RESULT(",upgcol!=NIL,upgind!=NIL,")"
    // tabPrintStruct(table,"ic")
    // ? "@"

******************************************************************************
static function tabVerifyColumn(table,resource) //egyezteti a mezoket

local columnsFile,colhashFile
local columnsProg,colhashProg
local columnsUnio,colhashUnio
local upgrade:=NIL

    if( resource==NIL )
        columnsFile:=tabReadColumn(table)   // beolvassa a bt fajlbol
    else
        columnsFile:=resource[1]::bin2arr   // eloveszi a resourcebol (table nincs megnyitva!)
    end

    columnsProg:=tabColumn(table)           // program objektum (tdc)

    setorder(columnsFile,0)                 // mezoket rendezesehez beszamozza
    setorder(columnsProg,1000)              // mezoket rendezesehez beszamozza

    colhashFile:=colhash(columnsFile)       // array -> hash
    colhashProg:=colhash(columnsProg)       // array -> hash

    colhashUnio:=colhashProg:clone

    if( !unio(colhashUnio,colhashFile,@upgrade) )
        // nem kepezheto az unio
        taberrOperation("tabVerifyColumn")            
        taberrDescription(@"different table struct")
        taberrArgs(upgrade)            
        tabStructError(table) //break
    end

    columnsUnio:=hashvalues2array(colhashUnio)
    columnsUnio::asort({|x,y|x[COL_OFFS]<y[COL_OFFS]})

    // rendezes
    // elore kerulnek a fajlban meglevo mezok, sorrendjuk ahogy a fajlban vannak
    // hatulra kerulnek a programbol jovo plusz mezok, sorrendjuk ahogy a tdc-ben vannak

    return {columnsUnio,upgrade}


******************************************************************************
static function unio(hprog,hfile,upgrade)
local colp,colf

    // ciklus a file oszlopaira

    colf:=hfile:firstvalue
    while( colf!=NIL )
        colp:=hprog[colf[COL_NAME]]
        if( colp==NIL )
            // a progam nem ismeri, be kell venni 
            hprog[colf[COL_NAME]]:=colf
        else
            // a program is ismeri, tipus egyeztetes
            if( colf[COL_TYPE]!=colp[COL_TYPE] .or.;
                colf[COL_WIDTH]!=colp[COL_WIDTH] .or.;
                colf[COL_DEC]!=colp[COL_DEC] )

                upgrade:=colp  // upgrade(force) szukseges
                return .f. // nem kepezheto az unio
            end
            
            colp[COL_OFFS]:=colf[COL_OFFS] //rendezeshez
        end
        colf:=hfile:nextvalue
    next

    // ciklus a program oszlopaira

    colp:=hprog:firstvalue
    while( colp!=NIL )
        colf:=hfile[colp[COL_NAME]]
        if( colf==NIL )
            upgrade:=colp // upgrade szukseges
            //? "unio>UPGRADE-MISSING",colp
        end
        colp:=hprog:nextvalue
    next
    
    return .t.

// ha  hProg<=hFile es a tipusok egyeznek => .t., upg=.f. (minden mezo megvan a fajlban)
// ha !hProg<=hFile de a tipusok egyeznek => .t., upg=.t. (nincs meg minden mezo, upgrade szukseges) 
// ha a tipusok elternek                  => .f.          (bovites nem lehetseges)


******************************************************************************
static function setorder(columns,offset) // ideiglenes sorszam a mezok rendezesehez
local n
    for n:=1 to len(columns)
        columns[n]::asize(COL_SIZEOF)
        columns[n][COL_OFFS]:=offset+n
    next


******************************************************************************
static function colhash(col)  // oszlop array -> hash 
local hash:=simplehashNew(),n
    for n:=1 to len(col)
        hash[col[n][COL_NAME]]:=col[n]
    next
    return hash


******************************************************************************
static function hashvalues2array(hash)
local array:=array(hash:itemcount),n:=0
local value:=hash:firstvalue
    while(value!=NIL)
        array[++n]:=value
        value:=hash:nextvalue
    next
    return array


******************************************************************************
static function tabVerifyIndex(table,resource,colUnio) //egyezteti az indexeket

local indFile,colFile 
local indProg,colProg
local indUnio,upg
local n,ind,i,j,p,colname,u,x 

    if( resource==NIL )
        //table megnyitva
        colFile:=tabReadColumn(table)
        indFile:=tabReadIndex(table)
    else
        //table nem megnyithato
        colFile:=resource[1]::bin2arr
        indFile:=resource[2]::bin2arr
    end
    
    colProg:=tabColumn(table)
    indProg:=tabIndex(table)


    // az oszlopok ugy vannak rendezve
    // hogy a bt-ben levo oszlopok elol legyenek
    // es megmaradjon az eredeti sorendjuk
    // ezert indFile egyszeruen atmasolhato

    indUnio:=aclone(indFile)

    for n:=1 to len(indProg)
        ind:=aclone(indProg[n]) // aclone (egyelore ne valtozzon)

        // megkeressuk a tdc-bol vett index szegmensek
        // helyet az egyesitett oszlop listaban (nev szerint)
        
        for i:=1 to len(ind[IND_COL])
            p:=ind[IND_COL][i] // oszlopindex colProg-ban
            colname:=colProg[p][COL_NAME]
            u:=ascan(colUnio,{|c|c[COL_NAME]==colname}) // oszlopindex colUnio-ban
            if( u==0 )
                //hiba (nem lehet ilyen)
                taberrOperation("tabVerifyIndex")            
                taberrDescription(@"invalid column index")
                taberrArgs(ind)            
                tabIndexError(table) //break
            else
                ind[IND_COL][i]:=u // p helyere u
            end
        end

        x:=ascan(indUnio,{|i|i[IND_NAME]==ind[IND_NAME]})
        if( x==0 )
            // az index nincs benne az unioban -> bevesszuk
            aadd(indUnio,ind)
            upg:=ind // upgradelni kell
        else
            // ilyen index mar van az unioban -> ellenorizzuk
            // ha mas a szerkezete -> nem kepezheto az unio
            
            if ( len(ind[IND_COL]) != len(indUnio[x][IND_COL]) )
                taberrOperation("tabVerifyIndex")            
                taberrDescription(@"incompatible index")
                taberrArgs(ind)            
                tabIndexError(table) //break
            else
                for i:=1 to len(ind[IND_COL])
                    if( ind[IND_COL][i] != indUnio[x][IND_COL][i] )
                        taberrOperation("tabVerifyIndex")            
                        taberrDescription(@"incompatible index")
                        taberrArgs(ind)            
                        tabIndexError(table) //break
                    end
                next
            end
        end
    next
  
    return {indUnio,upg}


******************************************************************************
static function tabReadColumn(table)
local buffer:=replicate(x"00",4096)
    _db_read1(table[TAB_BTREE],buffer,1,0)
    return bin2arr(buffer)

******************************************************************************
static function tabReadIndex(table)
local buffer:=replicate(x"00",4096)
    _db_read1(table[TAB_BTREE],buffer,1,1)
    return bin2arr(buffer)

******************************************************************************
