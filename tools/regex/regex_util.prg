
#ifdef NOT_DEFINED
  A like(), at(), strtran(), split() függvények olyan variánsa,
  ahol a kereső stringek helyén reguláris kifejezést lehet megadni.
  Mivel a reguláris kifejezések csak bytesorozatokra működnek,
  ezért a függvények C típusú bemenetnél oda-vissza konvertálnak
  C és X típus között, amiből furcsaságok származhatnak.
  
  Pl. 1 vagy több é betű keresése: "(é)+"
  (az egyszerű "é+" nem volna jó, mért az é több byteon tárolódik).
  
  Ha regex.at(regex,"text") nem karakterhatáron talál,
  akkor az eredmény 0.

  Ha regex.strtran("text",regex,repl) nem karakterhatáron talál,
  akkor elronthatja az eredmény UTF-8 kódolását.

  Ha a kereső regexp 0 hosszúságú stringhez is illeszkedhet,
  akkor az strtran és split végtelen ciklusba kerülhet.


  CCC2 backport:
    Az #ifdef-ek nélkül is megy CCC2-n (charpos/bytepos-t kivéve),
    de a hatékonyság érdekében ki vannak makrózva a felesleges konverziók.
#endif


#include "regex.ch"

using regex;
    regcomp regexec regfree

using utf8;
    charpos bytepos


#ifndef _CCC3_
#define str2bin(x)  x
#define bin2str(x)  x
#endif

*****************************************************************************
function regex.match(pattern,text) //X és C típusra 

//A $ operátor általánosítása.

local rx,pos

    rx:=regcomp(str2bin(pattern))
    pos:=regexec(rx,str2bin(text))
    regfree(rx)
    return pos!=NIL


*****************************************************************************
function regex.like(pattern,text) //X és C típusra

//Mint a közönséges CA-Tools like(),
//csak az első argumentum string helyett regex pattern.

local rx,pos
local eos:=bin(1) //0 nem jó!

    rx:=regcomp(eos+str2bin(pattern)+eos)
    pos:=regexec(rx,eos+str2bin(text)+eos)
    regfree(rx)
    return pos!=NIL


*****************************************************************************
function regex.at(pattern,text,nstart) //X és C típusra

//Mint a közönséges at(),
//csak az első argumentum string helyett regex pattern.
//Probléma, ha a keresés olyan bytepozíciót talál,
//ahol nem kezdődik karakter, ilyenkor az eredmény 0.

local rx,pos,cnv

#ifdef _CCC3_    
    if( cnv:=valtype(text)=="C" )
        text:=str2bin(text)
        if( nstart!=NIL )
            nstart:=bytepos(text,nstart)
        end
    end
#endif

    rx:=regcomp(str2bin(pattern))
    pos:=regexec(rx,text,nstart)
    regfree(rx)

    if( pos==NIL )
        pos:=0
    else
        pos:=pos[1]
#ifdef _CCC3_    
        if( cnv )
            pos:=charpos(text,pos)
        end
#endif
    end
    return pos

*****************************************************************************
function regex.strtran(text,search,repl,nstart,ncount) //X és C típusra

//Mint a közönséges strtran(),
//csak a második argumentum string helyett regex pattern.

local rx,offset:=1,pos,typ
local occurrence:=0,replaced:=0

#ifdef _CCC3_
    typ:=valtype(text)
    text:=str2bin(text)
    search:=str2bin(search)
#endif

    if(repl==NIL)
        repl:=a""
    else
        repl:=str2bin(repl)
    end
    nstart:=if(nstart==NIL,1,nstart)
    ncount:=if(ncount==NIL,len(text),ncount)

    rx:=regcomp(search)

    while( replaced<ncount .and. NIL!=(pos:=regexec(rx,text,offset)) )
        if( ++occurrence<nstart )
            offset:=pos[1]+1 //!
        else
            ++replaced
            text:=stuff(text,pos[1],pos[2],repl)
            offset:=pos[1]+len(repl)
        end
    end

    regfree(rx)

#ifdef _CCC3_
    return if(typ=="C",bin2str(text),text) //az eredeti típus
#else
    return text
#endif

*****************************************************************************
function regex.split(txt,sep) //X és C típusra

//Mint a közönséges split(),
//csak a második argumentum string helyett regex pattern.

local wlist:={},w,n:=1
local rx,pos

#ifdef _CCC3_
local bin:=valtype(txt)=="X"
#define BIN2STR(x)  if(bin,x,bin2str(x))
#else
#define BIN2STR(x)  x
#endif

    if(sep==NIL)
        sep:=a","
    else
        sep:=str2bin(sep)
    end

    txt:=str2bin(txt)
    rx:=regcomp(sep)
   
    while( n<=len(txt) )

        txt:=substr(txt,n)
        pos:=regexec(rx,txt)
    
        if( pos==NIL )
            aadd(wlist,BIN2STR(txt))
            exit
        elseif(pos[1]==1)
            aadd(wlist,BIN2STR(x""))
        else
            w:=substr(txt,1,pos[1]-1)
            aadd(wlist,BIN2STR(w))
        end

        n:=pos[1]+pos[2]
    end

    regfree(rx)
    return wlist

*****************************************************************************
