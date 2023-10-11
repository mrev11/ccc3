
// Vegigkoveti es kiirja egy memo ertek szegmenseit.
// Igy kell hasznalni: pgmemo <btfile> [<recno>] [<memix>]
// ahol <recno> a rekordsorszam, <memix> a memo index (decimalisok).
// Ha <memix> nincs megadva, akkor a memix=0-t veszi.
// Ha <recno> sincs megadva, akkor a memo lapokon levo szabad helyeket listazza.


#define TAB_RECBUF      4   // aktualis rekord buffer

#define COL_NAME        1   // oszlop-, es egyben mezonev
#define COL_TYPE        2   // tipus: C,N,D,L
#define COL_WIDTH       3   // mezoszelesseg
#define COL_DEC         4   // tizedesjegyek (0, ha TYPE!=N)
#define COL_OFFS        8   // mezo offset a rekordon belul

#clang
#include <cccapi.h>
#cend


******************************************************************************************
function main(btfile,recno,memix:="0")

local tab,column,n
local btree,memopos,pgno,indx,page
local memohead,recmix,poslen
local rec,mix,pos,len,memseg

    begin
        if( !".bt"$btfile )
            btfile+=".bt"
        end
        if( empty(btopen(btfile)) )
            break()
        end
        tab:=tabResource(btfile)
        tabOpen(tab)
        btree:=tab[2]
    recover
        usage()
    end

    if( recno==NIL .or. (recno::=val)<=0  )
        freespace( btree )
        quit
    end

    for n:=1 to len(tabColumn(tab))
        column:=tabColumn(tab)[n]
        if( column[COL_NAME]::left(3)=="DBM" .and.;
            column[COL_TYPE]$"XC" .and.;
            column[COL_WIDTH]==10 .and.;
            column[COL_DEC]==val(memix) )
            exit
        else
            column:=NIL
        end
    end

    if( column==NIL )
        ? "cannot find memo field of memix="+memix
        ?
        quit
    end

    tabGoto(tab,recno)
    if( tabEof(tab) )
        ? "recno out of bound"
        ?
        quit
    end
    memopos:=tab[TAB_RECBUF]::substr(column[COL_OFFS]+1,10)


    {pgno,indx}:=parse_memopos(memopos)
    ? "column name   :", column[COL_NAME]
    ? "memo position :", memopos //, "->", {pgno,indx}

    while( pgno>0 )
        page:=_db_pgread(btree,pgno)
        memohead:=page::substr((1+indx)*16+1,16)
        //? memohead::bin2hex

        recmix := memohead[ 1.. 4]::num
        poslen := memohead[ 5.. 8]::num

        {rec,mix}:=parse_recmix(recmix)
        {pos,len}:=parse_poslen(poslen)

        memseg:=page::substr(pos+1,len)

        ? form_recmix(rec,mix,16),;
          form_mempos(pgno,indx,16),;
          memseg::len::str(4),;
          form_memseg(memseg,48)

        pgno   := memohead[ 9..12]::num
        indx   := memohead[13..16]::num
    end
    ?
    ?


******************************************************************************************
static function usage()
    ? "Usage: pgmemo <btfile> [<recno>] [<memix>]"
    callstack()
    ?
    quit


******************************************************************************************
static function parse_memopos(memopos)
local pgno,indx
#clang
    char *memopos=_parb(1);
    unsigned int pgno,indx;
    sscanf(memopos,"%07x%03x",&pgno,&indx);
    number( pgno );
    assign(LOCAL_pgno);
    pop();
    number( indx );
    assign(LOCAL_indx);
    pop();
#cend
    return {pgno,indx}


******************************************************************************************
static function freespace(btree)

local pgno:=0
local page:=_db_pgread(btree,pgno)
local pgnext:=page[25..28]::num
local lower,upper

    while( pgno!=pgnext ) // az utolso lap onmagara mutat
        pgno   := pgnext
        page   := _db_pgread(btree,pgno)
        pgnext := page[ 5.. 8]::num::numand(0x7fffffff)
        lower  := page[ 9..12]::num
        upper  := page[13..16]::num

        ? pgno::l2hex::padl(8), upper-lower
    end    
    ?

******************************************************************************************
