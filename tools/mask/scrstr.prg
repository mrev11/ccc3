
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

//keszitette : Csiszar Levente
//javitas    : Vermes 1998.09.09

#include "scrstr.ch"

// Olyan rutinok, amikkel ugy irhatunk egy stringbe,
// mintha egy lap meretu kepernyore irnank.
// Eloszor a createScr()-el el kell kesziteni a lapot,
// az scrOutPict()-el lehet irni, az scrPos()-al lehet a lapon
// mozogni. A lapot leiro stringet az scrStr()-el lehet megkapni.

// Megj: Az scrStr csak azokat a sorokat adja, amikbe irtunk.


*************************************************************************
// Csak egy lapot tud felirni!
*************************************************************************
#define SCR_NROW    1   //lap magassaga
#define SCR_NCOL    2   //lap szelessege
#define SCR_ROW     3   //aktulais sor
#define SCR_COL     4   //aktualis oszlop
#define SCR_STRT    5   //sorok tombje 1-tol az utolso nemuresig

*************************************************************************
function createScr(nrow,ncol)
    return {nrow,ncol,0,0,{}}

*************************************************************************
function scrStr(scr,mogeNe)

// Azokat a sorokat adja, amikbe es amilyen hosszan irtunk.
// Ha a mogeNe igaz, akkor az utolso sor utan nem rak CR_LF-et.

local str:="",i,t:=scr[SCR_STRT]

    for i:=1 to len(t)-1
        str+=t[i]+CR_LF
    next

    if( len(t)>0 )
        str+=t[len(t)]
        if !(mogeNe==.t.)
            str+=CR_LF
        end
    end
    return str

*************************************************************************
function scrStrt(scr)

// Egy tombot ad, ami azokat a sorokat tartalmazza, amikbe irtunk.

    return scr[SCR_STRT]

*************************************************************************
function scrApp(scr1,scr2)

// Az scr2-t az scr1 vegehez fuzi.
// Az aktualis pozicio nem valtozik.
// Ha kilog valahol, levagja.

local t1,t2,nRow,nCol,n,i,w

    t1:=scr1[SCR_STRT]
    t2:=scr2[SCR_STRT]
    nRow:=scr1[SCR_NROW]
    nCol:=scr1[SCR_NCOL]
    
    n:=min(len(t2),nRow-len(t1)) //ennyit adunk hozza, Vermes 98.09.09

    for i:=1 to n
        w:=t2[i]
        if( len(w)>nCol )
            w:=left(w,nCol)
        end
        aadd(t1,w)
    next

    return scr1

*************************************************************************
function scrPos(scr,row,col)

// Pozicional az scr-en.

    scr[SCR_ROW]:=row
    scr[SCR_COL]:=col
    return scr

*************************************************************************
function scrOutPict(scr,str,pict)

// Az aktualis poziciora beirja az str-t. 
// Ha a pict meg van adva, akkor megformaza. 
// Az aktualis poziciot mozgatja.

local i,l,isCR_LF

    if (pict!=NIL)
        str:=transform(str,pict)
    end

    while(len(str)!=0)
        i:=at(CR_LF,str)
        if (i==0)
            i:=len(str)
            isCR_LF:=.f.
            l:=str
            str:=""
        else
            isCR_LF:=.t.
            l:=substr(str,1,i)
            str:=substr(str,i+3)
        end

        if (scr[SCR_ROW]>=scr[SCR_NROW])
            return scr
        end
   
        scr[SCR_STRT]:=xakieg(scr[SCR_STRT],scr[SCR_ROW]+1,"")

        scr[SCR_STRT][scr[SCR_ROW]+1]:=;
                    xreplStr( scr[SCR_STRT][scr[SCR_ROW]+1],;
                                    scr[SCR_COL]+1, l, scr[SCR_NCOL] )

        if (isCR_LF)
            scr[SCR_ROW]++
        end
    end
    return scr

*************************************************************************
static function xaKieg(tomb,size,def)

// Ha a tomb kisebb, akkor kiegesziti a size-re, 
// ha nagyobb vagy egyenlo, akkor nem csinal semmit.
// A kiegeszitett elemek a def-et kapjak ertekul.

local l

    if(len(tomb)<size )
        l:=len(tomb)
        asize(tomb,size)
        for l:=l+1 to size
            tomb[l]:=def
        next
    end
    return tomb

*************************************************************************
static function xreplStr(str,pos,mivel,maxlen)

// Az str pos poziciojara beirja a mivel-t, felulirassal.
// Ha a string hosszabb lenne, mint a maxlen, akkor a veget levagja.
// A pos szamolasa 1-tol indul.

    if( pos>maxlen )
        return str
    end

    if( pos+len(mivel)-1>maxlen )
        mivel:=left(mivel,maxlen+1-pos)
    end
    str:=padr(substr(str,1,pos-1),pos-1)+mivel+substr(str,pos+len(mivel))
    return str

*************************************************************************
static function toStr(val)

// A val-t stringge alakitja

local type:=valType(val)

    if (type=="N")
        return allTrim(str(val))
    elseif (type=="D")
        return dtoc(val)
    elseif (type=="L")
        return if(val,"T","F")
    elseif (type=="C" .or. type=="M")
        return val
    elseif (val==NIL)
        return "NIL"
    end
    alert("toStr: Nem konvertalhato tipus: '"+type+"'")
    return ""

*************************************************************************
function xtrpadr(str,pict,len)

    if !(pict==NIL .or. valtype(pict)=="N")
        str:=transform(str,pict)
    end
    return padr(str,len)

*************************************************************************
function xtrpadl(str,pict,len)

    if !(pict==NIL .or. valtype(pict)=="N")
        str:=transform(str,pict)
    end
    return padl(str,len)

*************************************************************************
function xtrpadc(str,pict,len)

    if !(pict==NIL .or. valtype(pict)=="N")
        str:=transform(str,pict)
    end
    return padc(str,len)

*************************************************************************
