
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

//FIGYELEM: ez UTF-8 kodolasu fajl

// Miben kulonbozik ez a Latin valtozattol?
// Lehet hasznalni akar X tipusu akar C tipusu stringet,
// de a mintanak es az elemzett szovegnek passzolnia kell,
// azaz X-X vagy C-C parosokat fogad el. X tipusu stringnel be
// kell allitani az PCRE_UTF8 flaget, maskepp nem illeszkedik.


#include "pcre.ch"


*************************************************************************************
function main()

    test( a"(^|[^Á])Á{2,5}($|[^Á])",;
          a"ÁÁÁ__Á____ÁÁÁÁÁÁÁÁÁÁÁ____ÁÁ____ÁÁÁ")

    test(  "(^|[^Á])Á{2,5}($|[^Á])",;
           "ÁÁÁ__Á____ÁÁÁÁÁÁÁÁÁÁÁ____ÁÁ____ÁÁÁ")


    ?


*************************************************************************************
static function test(regex,text)

local rx
local start
local match

local optcomp
local optexec

    optcomp:=0
    optcomp+=PCRE_UTF8  //X tipusnal be kell allitani

    ? ">>>>",valtype(regex), regex

    rx:=pcre.compile(regex,optcomp)

    //optexec:=0
    //optexec+=PCRE_NOTEMPTY

    while( NIL!=(match:=pcre.exec(rx,text,start,optexec)) )
        show(text,match)
        start:=max(match[2],match[1]+1)
    end
    
    pcre.free(rx)

    ?

*************************************************************************************
static function show(text,match)

    ? "------------------------------------------------------------"
    ? "         1         2         3         4         5         6"
    ? "123456789012345678901234567890123456789012345678901234567890"
    ? text
    ? offsets(text,match)



*************************************************************************************
static function offsets(text,match)

local boffs1:=match[1]
local boffs2:=match[2]
local coffs1:=text::left(boffs1-1)::bin2str::len
local coffs2:=text::left(boffs2-1)::bin2str::len
local x:=""
    x::=padr(coffs1)+"^"
    x::=padr(coffs2)+"^"

    return x

*************************************************************************************

    