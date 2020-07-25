
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
//function tabVerify(table)               //objektum <--> file (belso)
 
******************************************************************************
function tabVerify(table) //egyezteti az objektum es a file adatait
    tabVerifyColumn(table)
    tabVerifyIndex(table) 
    return NIL

******************************************************************************
static function tabVerifyColumn(table) //egyezteti a mezoket
 
local fld  //a fileben talalt oszlopok tombje
local col  //az objektumban levo oszlopok tombje
local c,n,m
 
    fld:=tabReadColumn(table)   
    col:=tabColumn(table)  
 
    //for n:=1 to len(fld)
    //    ? padr("'"+fld[n][COL_NAME]+"'",12),fld[n][COL_TYPE],fld[n][COL_WIDTH],fld[n][COL_DEC]
    //next

    for n:=1 to len(col)

        //nem okoz hibat, ha a fld bovebb
        
        c:=col[n]
        m:=ascan(fld,{|f|f[COL_NAME]==c[COL_NAME]})

        //if( m!=0 )
        //    ? n, padr(c[COL_NAME],10),;
        //        c[COL_TYPE]  ,fld[m][COL_TYPE],;
        //        c[COL_WIDTH] ,fld[m][COL_WIDTH],;
        //        c[COL_DEC]   ,fld[m][COL_DEC]
        //else
        //    ? n, padr(c[COL_NAME],10), "hianyzik"
        //end

        if( m==0.or.;
            c[COL_TYPE]!=fld[m][COL_TYPE].or.;
            c[COL_WIDTH]!=fld[m][COL_WIDTH].or.;
            c[COL_DEC]!=fld[m][COL_DEC] )

            taberrOperation("tabVerify")            
            taberrDescription(@"different table struct")
            taberrArgs(c)            
            tabStructError(table) //break van benne
        end
    next 
    
    //az oszlopstrukturat ujraepitjuk
    
    asize(tabColumn(table),0) //kiuriti
    for n:=1 to len(fld)
        tabAddColumn(table,fld[n])
    next

    return NIL


******************************************************************************
static function tabVerifyIndex(table) //egyezteti az indexeket

local aCtxInd:=tabReadIndex(table)      //a fajlban talalt indexek
local aTabInd:=tabIndex(table,aCtxInd)  //objektum szerinti indexek
local n, i, indnam, rebuild:={}

    //Jelenleg az objektumban a file-resource-bol kiolvasott 
    //index definicio van, ezt egyeztetjuk az eredeti objektumnal.

    for n:=1 to len(aTabInd)
        if( NIL==tabScanIndex(table,aTabInd[n]) )

            //A fileben vagy nincs meg aTabInd[n],
            //vagy ha megvan, elter a szerkezete.

            aadd(rebuild,indnam:=aTabInd[n][IND_NAME])
            i:=ascan(tabIndex(table),{|x|x[IND_NAME]==indnam})

            if( i>0 )
                adel(tabIndex(table),i)
                asize(tabIndex(table),len(tabIndex(table))-1)
                //egyezo nevu, eltero szerkezetu index torolve
            end
            tabAddIndex(table,aTabInd[n])
        end
    next
    
    //Most az objektumban, a file es az eredeti objektum indexeinek
    //unioja van, es azonos nevu, de elteru tartalmu indexek eseten
    //az objektumbeli definicio van megtartva (kesz a konverziora).
    //A rebuild array tartalmazza az ujraepitendo indexek nevet.
    
    if( !empty(rebuild) )
        taberrOperation("tabVerifyIndex")
        taberrDescription(@"incompatible index")
        taberrArgs(rebuild)
        tabIndexError(table) //break van benne
    end

    //Ezen a ponton teljesul, hogy a fileben levo indexek 
    //kompatibilisek az objektummal, de lehet, hogy a fileben
    //tobb index is van, es a sorrendjuk is elterhet.
    //A programnak minden meglevo indexet karban kell tartania,
    //a fileben ervenyes index sorrendet kell hasznalnia,
    //ezert a legegyszerubb, ha az index strukturat lecsereljuk.
    //Az index strukturat a tabAddindex-szel kell ujraepiteni,
    //hogy a kulcs oszlopok megfelelo blockot kapjanak.
    
    //? "obj info:", aTabInd
    //? "res info:", aCtxInd
    
    tabIndex(table,{}) //kiuriti
    
    for n:=1 to len(aCtxInd)
        tabAddIndex(table,aCtxInd[n])
    next

    return NIL

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
