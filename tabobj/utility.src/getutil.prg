
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

#include "inkey.ch"
#include "error.ch"

************************************************************************
function getNever(get)
local never:={||.f.}
    if( valtype(get)=="O" )
        get:preBlock:=never
    end
    return never

************************************************************************
function getWipe(get)
local prev:=get:varGet()
    if(valtype(prev)=="C")
        get:varPut(space(len(prev)))
    elseif(valtype(prev)=="N")
        get:varPut(0)
    elseif(valtype(prev)=="D")
        get:varPut(ctod(""))
    end
    get:display()
    return prev

************************************************************************
function getVerify(get)
local prev:=getWipe(get)
    readmodal( {get} ) 
    return prev==get:varGet()

************************************************************************
function getNumeric(g,dec,val) 
local pict:=replicate(",999",5)

    if( (dec:=if(dec==NIL,2,dec)) > 0 )
        pict+="."+replicate("9",dec) 
    end
    pict:=right(pict,len(g:varGet()))
    if(left(pict,1)=="," )
        pict:="9"+substr(pict,2)
    end
    g:picture:="@R "+pict
    g:varPut(if(val!=NIL,val,0))
    g:display()
    return g

***************************************************************************
function pozitiv(g)
    if(g:varGet()<0)
        alert(@"Only positive number allowed here",{@"Fix"})
        return .f.
    end
    return .t.

***************************************************************************
function getPozitiv(g,dec,val)
    g:postBlock:={||pozitiv(g)}
    getNumeric(g,if(dec==NIL,0,dec),val)
    return g

***************************************************************************
function negativ(g)
    if(g:varGet()>0)
        alert(@"Only negative number allowed here",{@"Fix"})
        return .f.
    end
    return .t.

***************************************************************************
function getNegativ(g,dec,val)
    g:postBlock:={||negativ(g)}
    getNumeric(g,if(dec==NIL,0,dec),val)
    return g

***************************************************************************
function getSText(g, text, option, template)

local n:=alltrim(str(len(g:varGet()),2,0))
local K:=if(option==NIL,"K",option)+" "
local X:=if(template==NIL,"X",left(template,1))

    g:picture:="@S"+n+K+replicate(X,len(text))
    g:varPut(text)
    return g 
/*
    Beallitja g:picture-jet "@S<n>K XXXXXXXXXXXXXXXXXXXXXXXXX"-re,
    ahol <n> g eredeti hossza,
    XX-ek hossza egyenlo text hosszaval,
    g uj erteke text lesz.
*/  

************************************************************************
function getPutText(get,text)
local l:=len(get:varGet())
    get:varPut(padr(text,l))
    return l

************************************************************************
//  getlist  minden elemenek kiertekeli a postBlock-jat, es
//  ujra editaltatja azokat, amelyek nem jol voltak kitoltve.
//
function getValidAll(getlist)
local n, get, pre, post

    for n:=1 to len(getlist)
        get:=getlist[n]
        pre:=get:preBlock
        post:=get:postBlock

        while( lastkey()!=K_ESC .and.;
               (valtype(pre)!="B".or.eval(pre,get)).and.;
               valtype(post)=="B".and.!eval(post,get) )

            readmodal({get})               
        end        
    next
    return lastkey()!=K_ESC

************************************************************************
function getDisplayAll(glist)
    return aeval(glist,{|g|g:display()})

************************************************************************
function getViewOnly(glist)
local never:={||.f.}
    return aeval(glist,{|g|g:preBlock:=never})

************************************************************************
//  Ha sok olyan get mezo van a maszkban, amelyiknek a 
//  preBlock-ja fixen .f.-et ad, akkor a kurzor nehezen mozog 
//  kozottuk, mert mindegyiket ki kell ertekelni menet kozben. 
//  Ezert, ha a preBlock-ok erteke nem fugg(!) a get objectek
//  adattartalmatol, akkor celszeru a getlist-bol elore kiszurni
//  azokat az elemeket, amelyekre ugysem lephet ra a kurzor.
//
//  Ilyenkor a readmodal()-t egyszeruen helyettesitsuk readfilt()-tel.
//
//  Ha a get mezok sorrendjet is kezbe kell venni, akkor ugyanez a
//  modszer alkalmazando, csakhogy ott az elemeket egyenkent kell
//  atmasolni a kivant sorrendben (esetleg kihagyva azokat, amelyekre
//  a kurzor nem lephet ra). Fontos tudni, hogy ez a muvelet nem 
//  valtoztatja az eredeti getlist-et, tehat a validokban levo
//  hivatkozasok az eredeti getlist elemekre tovabbra is jok maradnak.
//  
//  Eredetileg a preBlock-ok mindig egy parameterrel vannak kiertekelve,
//  es ez az egy parameter maga a get object. Abbol a celbol, hogy a 
//  preBlock tudhassa, hogy nem a read van folyamatban, csak a szures,
//  a readfilt megegy parametert atad a preBlock-nak a kiertekeleskor.
//  A masodik parameter erteke megallapodas szerint "readfilt".
//
function readfilt(glist)
local g:={}, n
    for n:=1 to len(glist)
        if( valtype(glist[n]:preBlock)!="B".or.;
            eval(glist[n]:preBlock,glist[n],"readfilt"))
            aadd(g, glist[n])
        end
    next
    return readmodal(g)


************************************************************************
function getTipValue(get,defval,fix)
local never:={||.f.}, errobj

    if( !empty(defval) )
        get:varPut(defval)

        if( "R"$fix )

            if( valtype(get:postBlock)!="B".or.eval(get:postBlock) )
                get:preBlock:=never
            else

                errobj:=errorNew()
                errobj:cargo:=get
                errobj:severity:=ES_WARNING
                errobj:subSystem:="GETUTIL"
                errobj:operation:="getTipValue"
                errobj:description:=@"invalid default value"
                break(errobj)
            end
        end
    end

    return NIL


************************************************************************
