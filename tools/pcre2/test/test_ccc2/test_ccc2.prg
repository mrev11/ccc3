
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

//FIGYELEM: ez Latin-2 kodolasu fajl

//Miben kulonbozik ez az UTF-8 valtozattol?
//A karakter string es binaris string esete ugyanaz.
//A regex is es az elemzett szoveg is Latin kodolasu.
//Ezert nem hasznahato a PCRE_UTF8 opcio (hibat ad).

#include "pcre2.ch"

*************************************************************************************
function main()

    test( a"(^|[^?])?{2,5}($|[^?])",;
          a"???__?____???????????____??____???")

    test(  "(^|[^?])?{2,5}($|[^?])",;
           "???__?____???????????____??____???")

    ?

*************************************************************************************
static function test(regex,text)

local rx
local start
local match

local optcomp
local optexec

    optcomp:=0
    //optcomp+=PCRE2_UTF  //nem szabad beallitani (hiba)

    ? ">>>>",valtype(regex), regex

    rx:=pcre2.compile(regex,optcomp)

    //optexec:=0
    //optexec+=PCRE2_NOTEMPTY

    while( NIL!=(match:=pcre2.match(rx,text,start,optexec)) )
        show(text,match)
        start:=max(match[2],match[1]+1)
    end
    
    pcre2.free(rx)

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

    