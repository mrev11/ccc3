
//FIGYELEM: ez Latin-2 kodolasu fajl

//Miben kulonbozik ez az UTF-8 valtozattol?
//A karakter string es binaris string esete ugyanaz.
//A regex is es az elemzett szoveg is Latin kodolasu.
//Ezert nem hasznahato a PCRE_UTF8 opcio (hibat ad).

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
    //optcomp+=PCRE_UTF8  //nem szabad beallitani (hiba)

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

    