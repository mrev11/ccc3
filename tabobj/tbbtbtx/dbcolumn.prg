
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

//function tabAddColumn(table,column)   //oszlop hozzaadasa az objektumhoz
//function tabSetColBlock(table,column) //oszlop block ujra beallitasa

******************************************************************************
function tabAddColumn(table,column) //oszlop hozzaadasa az objektumhoz

// column szerkezete: {name,type,width,dec,pict,block,keyflag,offs}
// az elso negy elem megadasa kotelezo
//
// name     alltrim, upper
// dec      nem szammezoknel 0
// pict     kitoltjuk 
// offs     kitoltjuk (kesobb valtozhat)
// block    kitoltjuk (valtozik, ha offs, vagy key valtozik
// keyflag  kitoltjuk (egyelore nem ismert, default .f.)
//
// a sorszam szerinti oszlophivatkozas mindig a tabAddColumn()
// szerinti sorrendet jelenti, es nem a file-beli sorrendet

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
    column[COL_OFFS]    := table[TAB_RECLEN] //kesobb meg valtozhat
    column[COL_KEYFLAG] := .f. //meg nem ismert, valtozhat
    
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

    tabSetColBlock(table,column) //kitolti az oszlop kodblokkjat
    
    //blokkok tovabbi allitgatasa tabAddindex/tabVerify-ban
    //
    //Az adatfileben olyan mezok is lehetnek, 
    //amik az objektumbol hianyoznak, ezert az objektum alapjan
    //szamitott mezooffsetek a valodi offsettol elterhetnek.
    //A mar megnyitott dbf-ben a mezok a fejlecbol nev alapjan 
    //kikereshetok, es a pontos helyuk szerinti blokk kepezheto.
    //
    //A tabAddIndex az oszlopok nemelyiket kulcsnak minositi,
    //ezeknek ki kell cserelni a blokkjat olyanra, amelyik a commitban
    //kivaltja az index karbantartasat: a regi kulcserteket torolni, 
    //az ujat berakni kell. (TAB_KEYFLAG beallitas)
    //
    //Tovabbi bonyodalom, hogy a file tovabbi, az objektumbol
    //nem ismert indexeket is tartalmazhat, amiket szinten karban 
    //kell tartani, ezert ezeknek a blokkjat is cserelni kell.

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

        //Engedjuk-e az irast EOF-ba?
        //Ha kulcsmezot irnak at EOF-ban, akkor ronda hibat kapunk:
        //nem tudjuk torolni az indexbol a kulcs korabbi peldanyat.
        //Ha viszont itt megallunk, akkor jonak tudott programokrol
        //derulhet ki varatlanul, hogy EOF-ba irnak.

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


static function xislocked(table) //kulcsszegmenseknel specialis

local index,ord

    if( !table[TAB_MODIFKEY] )
        table[TAB_MODIFKEY]:=.t.
        islocked(table)

        //meg kell jegyezni, hogy mi volt a kulcs erteke
        //a mezo atirasa elott, hogy kesobb (tabCommit)
        //meg lehessen talalni az eredeti kulcsokat
        
        //barmely kulcsot alkoto mezo modositasa kivaltja
        //az osszes kulcs update-jet
        
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
//u.a. mint blkchar csak olvasaskor nem konvertal stringre
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
//u.a. mint xblkchar csak olvasaskor nem konvertal stringre
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


//Megj: egy xvgetnumber/xvputnumber fuggvenyparral a szammezok 
//kezelese lenyegesen felgyorsithato volna!


******************************************************************************
