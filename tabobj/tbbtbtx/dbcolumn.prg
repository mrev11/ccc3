
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

#include "tabobj.ch"

******************************************************************************
//Public interface

//function tabAddColumn(table,column)   //oszlop hozzáadása az objektumhoz
//function tabSetColBlock(table,column) //oszlop block újra beállítása

******************************************************************************
function tabAddColumn(table,column) //oszlop hozzáadása az objektumhoz

// column szerkezete: {name,type,width,dec,pict,block,keyflag,offs}
// az első négy elem megadása kötelező
//
// name     alltrim, upper
// dec      nem számmezőknél 0
// pict     kitöltjük 
// offs     kitöltjük (később változhat)
// block    kitöltjük (változik, ha offs, vagy key változik
// keyflag  kitöltjük (egyelőre nem ismert, default .f.)
//
// a sorszám szerinti oszlophivatkozás mindig a tabAddColumn()
// szerinti sorrendet jelenti, és nem a filé-beli sorrendet

local type  :=column[COL_TYPE]
local width :=column[COL_WIDTH]
local dec   :=column[COL_DEC]
local pict

    if( empty(table[TAB_COLUMN]) )
        table[TAB_FLDNUM]:=0
        table[TAB_RECLEN]:=1 //deleted flag
    end

    asize(column, COL_SIZEOF)

    column[COL_NAME]    := upper(alltrim(column[COL_NAME]))
    column[COL_OFFS]    := table[TAB_RECLEN] //később még változhat
    column[COL_KEYFLAG] := .f. //még nem ismert, változhat
    
    if( type!="N" )
        column[COL_DEC]:=0
    end

    if( type=="C" )
        if( tabMemoField(table,column) )
            pict:=tabMemoPict()
        else
            pict:="@R "+replicate("X",min(width,64))
        end

    elseif( type=="X" )
        pict:="@R "+replicate("X",min(width,64))

    elseif( type=="D" )
        pict:="D"

    elseif( type=="L" )
        pict:="@! L"

    elseif( type=="N" )
        pict:=replicate("9",width)
        if( dec>0 )
            pict+="."+replicate("9",dec)
            pict:=right(pict,width)
            pict:="@R "+pict
        end
    end

    column[COL_PICT]:=pict

    tabSetColBlock(table,column) //kitölti az oszlop kódblokkját
    
    //blokkok további állítgatása tabAddindex/tabVerify-ban
    //
    //Az adatfilében olyan mezők is lehetnek, 
    //amik az objektumból hiányoznak, ezért az objektum alapján
    //számított mezőoffsetek a valódi offsettől eltérhetnek.
    //A már megnyitott dbf-ben a mezők a fejlécből név alapján 
    //kikereshetők, és a pontos helyük szerinti blokk képezhető.
    //
    //A tabAddIndex az oszlopok némelyikét kulcsnak minősíti,
    //ezeknek ki kell cserélni a blokkját olyanra, amelyik a commitban
    //kiváltja az index karbantartását: a régi kulcsértéket törölni, 
    //az újat berakni kell. (TAB_KEYFLAG beállítás)
    //
    //További bonyodalom, hogy a filé további, az objektumból
    //nem ismert indexeket is tartalmazhat, amiket szintén karban 
    //kell tartani, ezért ezeknek a blokkját is cserélni kell.

    aadd(table[TAB_COLUMN],column)

    table[TAB_FLDNUM]+=1
    table[TAB_RECLEN]+=width

    return column


******************************************************************************
function tabSetColBlock(table,column)

local name  :=column[COL_NAME]
local type  :=column[COL_TYPE]
local width :=column[COL_WIDTH]
local dec   :=column[COL_DEC]
local offs  :=column[COL_OFFS]
local key   :=column[COL_KEYFLAG]

    //? name,type,key

    if(type=="C")

        if( tabMemoField(table,column) )
            column[COL_BLOCK]:=blkmemo(table,offs,width)
        else
            column[COL_BLOCK]:=if(key,xblkchar(table,offs,width),blkchar(table,offs,width))
        end

    elseif(type=="X")
        column[COL_BLOCK]:=if(key,xblkbin(table,offs,width),blkbin(table,offs,width))

    elseif(type=="N")
        column[COL_BLOCK]:=if(key,xblknumber(table,offs,width,dec),blknumber(table,offs,width,dec))

    elseif(type=="D")
        column[COL_BLOCK]:=if(key,xblkdate(table,offs),blkdate(table,offs))

    elseif(type=="L")
        column[COL_BLOCK]:=if(key,xblkflag(table,offs),blkflag(table,offs))

    else
        taberrOperation("tabSetColBlock")
        taberrDescription(@"invalid column specification")
        taberrArgs(column)
        tabError(table)

    end

    return NIL


******************************************************************************
static function islocked(table)

    if( !table[TAB_MODIF] )
        table[TAB_MODIF]:=.t.

        //Engedjük-e az írást EOF-ba?
        //Ha kulcsmezőt írnak át EOF-ban, akkor ronda hibát kapunk:
        //nem tudjuk törölni az indexből a kulcs korábbi példányát.
        //Ha viszont itt megállunk, akkor jónak tudott programokról
        //derülhet ki váratlanul, hogy EOF-ba írnak.

        //if( tabEof(table) )
        if( tabPosition(table)==0 ) //2019-10-08
            taberrOperation("tabEvalColumn")
            taberrDescription(@"writing EOF")
            tabError(table)
        end

        if( !tabIsLocked(table) )
            taberrOperation("tabEvalColumn")
            taberrDescription(@"record lock requiered")
            tabError(table)
        end
    end
    return .t.


static function xislocked(table) //kulcsszegmenseknél speciális

local index,ord

    if( !table[TAB_MODIFKEY] )
        table[TAB_MODIFKEY]:=.t.
        islocked(table)

        //meg kell jegyezni, hogy mi volt a kulcs értéke
        //a mező átírása előtt, hogy később (tabCommit)
        //meg lehessen találni az eredeti kulcsokat
        
        //bármely kulcsot alkotó mező módosítása kiváltja
        //az összes kulcs update-jét
        
        index:=tabIndex(table)
        for ord:=1 to len(index)
            index[ord][IND_CURKEY]:=tabKeyCompose(table,ord)
        next
    end
    return .t.


******************************************************************************
static function blkchar(table,offs,width)
    return {|x| if(x==NIL.or.!islocked(table),;
                bin2str(xvgetchar(table[TAB_RECBUF],offs,width)),;
                (xvputbin(table[TAB_RECBUF],offs,width,str2bin(x)),x)) }

static function blkbin(table,offs,width)
//u.a. mint blkchar csak olvasáskor nem konvertál stringre
    return {|x| if(x==NIL.or.!islocked(table),;
                xvgetchar(table[TAB_RECBUF],offs,width),;
                (xvputbin(table[TAB_RECBUF],offs,width,str2bin(x)),x)) }

static function blknumber(table,offs,width,dec)
    return {|x| if(x==NIL.or.!islocked(table),;
                val(xvgetchar(table[TAB_RECBUF],offs,width)),;
                (xvputchar(table[TAB_RECBUF],offs,width,str2bin(str(x,width,dec))),x)) }
    
static function blkdate(table,offs)
    return {|x| if(x==NIL.or.!islocked(table),;
                stod(xvgetchar(table[TAB_RECBUF],offs,8)),;
                (xvputchar(table[TAB_RECBUF],offs,8,str2bin(dtos(x))),x)) }

static function blkflag(table,offs)  //megj: T=84, F=70
    return {|x| if(x==NIL.or.!islocked(table),;
                84==xvgetbyte(table[TAB_RECBUF],offs),;
                (xvputbyte(table[TAB_RECBUF],offs,if(x,84,70)),x)) }

static function blkmemo(table,offs,width)  
    return {|x| if(x==NIL.or.!islocked(table),;
                tabMemoRead(table,xvgetchar(table[TAB_RECBUF],offs,width)),;
                (xvputchar(table[TAB_RECBUF],offs,width,tabMemoWrite(table,xvgetchar(table[TAB_RECBUF],offs,width),str2bin(x))),x))}


// xblk... = blk... (islocked <- xislocked)


static function xblkchar(table,offs,width)
    return {|x| if(x==NIL.or.!xislocked(table),;
                bin2str(xvgetchar(table[TAB_RECBUF],offs,width)),;
                (xvputbin(table[TAB_RECBUF],offs,width,str2bin(x)),x)) }

static function xblkbin(table,offs,width) 
//u.a. mint xblkchar csak olvasáskor nem konvertál stringre
    return {|x| if(x==NIL.or.!xislocked(table),;
                xvgetchar(table[TAB_RECBUF],offs,width),;
                (xvputbin(table[TAB_RECBUF],offs,width,str2bin(x)),x)) }

static function xblknumber(table,offs,width,dec)
    return {|x| if(x==NIL.or.!xislocked(table),;
                val(xvgetchar(table[TAB_RECBUF],offs,width)),;
                (xvputchar(table[TAB_RECBUF],offs,width,str2bin(str(x,width,dec))),x)) }
    
static function xblkdate(table,offs)
    return {|x| if(x==NIL.or.!xislocked(table),;
                stod(xvgetchar(table[TAB_RECBUF],offs,8)),;
                (xvputchar(table[TAB_RECBUF],offs,8,str2bin(dtos(x))),x)) }

static function xblkflag(table,offs)  //megj: T=84, F=70
    return {|x| if(x==NIL.or.!xislocked(table),;
                84==xvgetbyte(table[TAB_RECBUF],offs),;
                (xvputbyte(table[TAB_RECBUF],offs,if(x,84,70)),x)) }


//Megj: egy xvgetnumber/xvputnumber függvénypárral a számmezők 
//kezelése lényegesen felgyorsítható volna!


******************************************************************************
