
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

//TARTALOM  : tabla objektum oszlop metodusok platformfuggetlen resze
//STATUS    : kozos
//
//function tabColNumber(table,colName)   oszlopnevbol oszlopsorszam
//function tabColumn(table)              oszlopok strukturaja
//function tabGetColumn(table,col)       oszlop keresese az objektumban
//function tabEvalColumn(table,col,exp)  oszlop kiertekelese es ertekadasa
//function tabBlock(table,col,block)     oszlop kiertekelo blockja
//function tabFcount(table)              oszlopok szama
//function tabPicture(table,col,pict)    oszlop picture-je

#include "tabobj.ch"

******************************************************************************
function tabColNumber(table,colName) //oszlopnevbol oszlopsorszam
local column:=table[TAB_COLUMN], num
    colName:=upper(alltrim(colName))
    num:=ascan(column,{|x|x[COL_NAME]==colName} )
    if(num<=0)
        taberrOperation("tabColNumber")
        taberrDescription(@"unknown column name")
        taberrArgs(colName)
        tabError(table)
    end
    return num


******************************************************************************
function tabColumn(table) //oszlopok strukturaja
    return table[TAB_COLUMN]


******************************************************************************
function tabGetColumn(table,col) //oszlop keresese az objektumban
    if(valtype(col)=="C")
        col:=tabColNumber(table,col)
    end
    return table[TAB_COLUMN][col]


******************************************************************************
function tabEvalColumn(table,col,exp) //oszlop kiertekelese es ertekadasa
    return eval(tabGetColumn(table,col)[COL_BLOCK],exp)


******************************************************************************
function tabBlock(table,col,block) //oszlop kiertekelo blockja
local column:=tabGetColumn(table,col)
    return if(block==NIL,column[COL_BLOCK],column[COL_BLOCK]:=block)


******************************************************************************
function tabPicture(table,col,pict)  //oszlop picture-je
local column:=tabGetColumn(table, col)
    return if(pict==NIL,column[COL_PICT],column[COL_PICT]:=pict)


******************************************************************************
function tabFcount(table) //oszlopok szama
    return len(table[TAB_COLUMN])


******************************************************************************
