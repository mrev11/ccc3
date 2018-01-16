
//FIGYELEM: ez UTF-8 kodolasu fajl

// Miben kulonbozik ez a Latin valtozattol?
// Lehet hasznalni akar X tipusu akar C tipusu stringet,
// de a mintanak es az elemzett szovegnek passzolnia kell,
// azaz X-X vagy C-C parosokat fogad el. X tipusu stringnel be
// kell allitani az PCRE_UTF8 flaget, maskepp nem illeszkedik.


#include "pcre2.ch"


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
    optcomp+=PCRE2_UTF  //X tipusnal be kell allitani

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

    