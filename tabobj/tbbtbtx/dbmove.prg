
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

#include "fileio.ch"
#include "tabobj.ch"

#define INDORDER    table[TAB_INDEX][table[TAB_ORDER]] 
#define RECORDER    "recno"
#define KEYORDER    if(table[TAB_ORDER]==0,RECORDER,INDORDER[IND_NAME])
 
******************************************************************************
// Public interface

//function tabSkip(table,stp)          //skip elore/hatra
//function tabSeek(table,exp)          //nagyobbegyenlore
//function tabSeekLE(table,exp)        //kisebbegyenlore (vagy legkisebbre)
//function tabSeekGE(table,exp)        //nagyobbegyenlore (vagy legnagyobbra)
//function tabGoTop(table)             //gotop
//function tabGoBottom(table)          //gobottom
//function tabGetNext(table,stp)       //elore index szerint (belso)
//function tabGetPrev(table,stp)       //hatra index szerint (belso)
//function tabGoto(table,pos)          //goto
//function tabEstablishPosition(table) //prev/next beallitasa (belso)
//function tabPosition(table)          //recno() vagy 0, ha EOF-on all
//function tabLastRec(table)           //rekordok szama
//function tabEof(table)               //eof().or.bof()
//function tabFound(table)             //found()


******************************************************************************
//EOF beallitasa:
//
//  tabEOF() ketfele szituacioban ad .t.-t
//    
//  1) ha kiserlet tortent top ele pozicionalni (skip -1),
//     ilyenkor tabEOF()==.t., es tabPosition()==1.
//
//  2) ha nemletezo rekordra (pos<=0 .or. lastrec<pos) akarnak
//     pozicionalni, ilyenkor tabEOF()==.t., es tabPosition()==0.
//       
//  Tehat a fajl pozicionalatlansagat (utolso utani fiktiv rekordon
//  allasat) a tabPosition()==0 relacio mutatja. 


******************************************************************************
// Szures
******************************************************************************
static function tabInscope(t)
    if( 42==xvgetbyte(t[TAB_RECBUF],0) )
        //deleted
        return .f.

    elseif( t[TAB_FILTER]!=NIL.and.!eval(t[TAB_FILTER]) )
        //filtered out
        return .f. 
    end
    return .t.


******************************************************************************
function tabSkip(table,stp)  //skip elore/hatra

    if(table[TAB_MODIF]); tabCommit(table); end
    if(stp==NIL); stp:=1; end
    table[TAB_FOUND]:=.f.

    if( stp>0 )
        if( stp>tabGetNext(table,stp) )
            tabGoEOF(table) // EOF-ra all
        else
            table[TAB_EOF]:=.f.
        end

    elseif( stp<0 )
        if( -stp>tabGetPrev(table,-stp) )
            tabGoTop(table)
            table[TAB_EOF]:=.t.
        else
            table[TAB_EOF]:=.f.
        end

    elseif( tabEof(table) )
        //??

    else
        //ujraolvassuk a rekordot
        tabSetPos(table, _db_wrbig32(table[TAB_POSITION])+table[TAB_RECPOS] )
    end   
    return !table[TAB_EOF]


******************************************************************************
function tabSeek(table,exp)  //kereses nagyobbegyenlore

// osszetett indexkifejezest {}-ban felsorolva kell megadni,
// csak TAB_ORDER>0 eseten (azaz beallitott indexszel) alkalmazhato

local ord:=table[TAB_ORDER]
local key,keyf,pos

    tabCommit(table)
    table[TAB_EOF]:=.f.

    if( ord<=0 )
        taberrOperation("tabSeek")
        taberrDescription(@"no control index")
        tabError(table)

    elseif( valtype(exp)=="A" )
        key:=tabExpIndex(table,exp)
    else
        key:=tabExpIndex(table,{exp})
    end
    
    _db_setord(table[TAB_BTREE],KEYORDER)
    keyf:=_db_seek(table[TAB_BTREE],key)

    if( !tabSetPos(table,keyf) )  
        //EOF-ra allt

    elseif( tabInscope(table) )
        table[TAB_EOF]:=.f.

    elseif( 1>tabGetNext(table,1) )
        tabGoEOF(table)
    
    else
        table[TAB_EOF]:=.f.
    end

    if( table[TAB_EOF] )
        table[TAB_FOUND]:=.f.
    else
        keyf:=tabKeyCompose(table,table[TAB_ORDER])
        table[TAB_FOUND]:=keyf<=key
    end

    return table[TAB_FOUND]
    
    //Megjegyzes: a talalt kulcs egyezoseget csak a megadott 
    //hosszban (key hosszaban) kell vizsgalni (<= operator).


******************************************************************************
function tabSeekLE(table,exp) //seek kisebbegyenlore (vagy legkisebbre)
    if( tabSeek(table,exp) )
        return .t.
    elseif( tabEof(table) )
        tabGoBottom(table)
    else
        tabSkip(table,-1)
    end
    return .f.
 

******************************************************************************
function tabSeekGE(table,exp) //seek nagyobbegyenlore (vagy legnagyobbra)
    if( tabSeek(table,exp) )
        return .t.
    elseif( tabEof(table) )
        tabGoBottom(table)
    end
    return .f.


******************************************************************************
static function tabExpIndex(table,aexp) //tombbol indexkifejezes

// az aexp kifejezeslistabol kulcserteket keszit seek szamara
// (column az aktualis indexet alkoto oszlopok sorszamanak listaja)

local column:=table[TAB_INDEX][table[TAB_ORDER]][IND_COL],n
local col,type,width,dec,segval,key:=x""

    if( len(column)<len(aexp) )
        taberrOperation("tabExpIndex")
        taberrDescription(@"key list longer")
        taberrArgs(aexp)
        tabError(table)
    end
    
    //megengedjuk, hogy aexp rovidebb legyen
    
    for n:=1 to len(aexp)

        col    := tabGetColumn(table,column[n])
        type   := col[COL_TYPE]
        width  := col[COL_WIDTH]
        dec    := col[COL_DEC]
        segval := aexp[n]

        if( type=="C" )
            key+=padr(str2bin(segval),width)

        elseif( type=="X" )
            key+=padr(segval,width)

        elseif( type=="N" )
            key+=_db_numseg(segval,width,dec) 

        elseif( type=="D" )
            key+=str2bin(dtos(segval))

        elseif( type=="L" )
            key+=if(segval,a"T",a"F")
        end
    next

    return key 
    
    //az itteni key vegen nincs a recno-bol kepzett suffix,
    //ezert az mindig rovidebb, mint amit tabKeyCompose ad,
    //egyebkent a ket fuggveny nagyon hasonlo


******************************************************************************
function tabGoTop(table)  //gotop

    tabCommit(table)
    table[TAB_FOUND]:=.f.
    
    _db_setord(table[TAB_BTREE],KEYORDER)

    if( !tabSetPos(table,_db_first(table[TAB_BTREE])) )
        //EOF-ra allt
    elseif( tabInscope(table) )
        table[TAB_EOF]:=.f.
    elseif( 1>tabGetNext(table,1) )
        tabGoEOF(table)
    else
        table[TAB_EOF]:=.f.
    end

    return !table[TAB_EOF]


*****************************************************************************
function tabGoBottom(table)  //gobottom

    tabCommit(table)
    table[TAB_FOUND]:=.f.

    _db_setord(table[TAB_BTREE],KEYORDER)
 
    if( !tabSetPos(table,_db_last(table[TAB_BTREE])) )
        //EOF-ra allt
    elseif( tabInscope(table) )
        table[TAB_EOF]:=.f.
    elseif( 1>tabGetPrev(table,1) )  
        tabGoEOF(table)
    else
        table[TAB_EOF]:=.f.
    end

    return !table[TAB_EOF]


******************************************************************************
function tabGetNext(table,stp) //elore index szerint 
local n:=0,nextpos
    if( tabPosition(table)==0 )
        // EOF-rol nem lehet elore lepni
        return 0 
    end

    while( n<stp .and.;
           NIL!=(nextpos:=_db_next(table[TAB_BTREE])) .and.;
           tabSetPos(table,nextpos) )

        if( tabInscope(table) )
            n++                    
        end
    end
    return n


******************************************************************************
function tabGetPrev(table,stp) //hatra index szerint 
local n:=0,prevpos
    if( tabPosition(table)==0 )
        //EOF-rol eloszor BOTTOM-ra kell visszalepni
        if( tabGobottom(table) .and. tabInscope(table) ) 
            n++                    
        end
    end
    while( n<stp .and.;
           NIL!=(prevpos:=_db_prev(table[TAB_BTREE])) .and.;
           tabSetPos(table,prevpos) )

        if( tabInscope(table) )
            n++                    
        end
    end
    return n


******************************************************************************
function tabGoto(table,pos) //goto
local key,keyf,pup

    tabCommit(table)
    table[TAB_EOF]:=.f.
    table[TAB_FOUND]:=.f.
    table[TAB_POSITION]:=pos
    
    _db_setord(table[TAB_BTREE],RECORDER)
    key:=_db_wrbig32(pos) 
    keyf:=_db_seek(table[TAB_BTREE],key)
 
    if( keyf!=key )

        if( table[TAB_TRANID]!=NIL .and. tranLastRecordUpdate(table,@pup) )
            //Ez az az eset, amikor egy tranzakcioban
            //appendalt rekordra visszapozicionalunk,
            //ilyenkor BTBTX-ben nem eleg a recno-t tudni,
            //hanem a recpos-t is vissza kell allitani.
        
            table[TAB_RECPOS]:=pup[PUP_RECPOS]
        else
            tabGoEOF(table)
        end
    else
        table[TAB_RECPOS]:=right(keyf,6)
        if( tabReadRecord(table) )
            if( table[TAB_ORDER]!=0 ) 
                tabEstablishPosition(table)
            end
            if( table[TAB_TRANID]!=NIL )
                tranLastRecordUpdate(table) 
            end
        end
    end
    
    return !table[TAB_EOF]


******************************************************************************
function tabEstablishPosition(table) //prev/next beallitasahoz (belso)

local key,keyf,n:=0

    _db_setord(table[TAB_BTREE],KEYORDER)
    
    while( !tabEof(table) )
    
        key:=tabKeyCompose(table,table[TAB_ORDER])
        keyf:=_db_seek(table[TAB_BTREE],key)
    
        if( keyf!=key )
            if( ++n<10 )
                sleep(100)
                tabReadRecord(table) 
                loop
            else
                taberrOperation("tabEstablishPosition")
                taberrDescription(@"file not positioned")
                taberrArgs({KEYORDER,key,keyf}) 
                tabError(table)
            end
        end
        exit
    end
    return NIL


******************************************************************************
static function tabReadRecord(table) //rekord olvasas
    if( table[TAB_RECLEN]!=;
        _db_read(table[TAB_BTREE],table[TAB_RECBUF],table[TAB_RECPOS]) )
        tabGoEOF(table)
        return .f.
    end
    return .t.


******************************************************************************
static function tabSetPos(table,key) 
local primarykey

    if( key==NIL )
        tabGoEOF(table)
        return .f.
    end

    primarykey:=right(key,10) 
    table[TAB_POSITION]:=_db_rdbig32(left(primarykey,4)) 
    table[TAB_RECPOS]:=right(primarykey,6) 

    if( table[TAB_TRANID]!=NIL .and. tranLastRecordUpdate(table) )
        return .t.
    end
    return tabReadRecord(table)  



******************************************************************************
function tabPosition(table) //recno() vagy 0, ha EOF-on all
    return table[TAB_POSITION]


******************************************************************************
function tabLastRec(table)  //rekordszam
    return _db_lastrec(table[TAB_BTREE])


******************************************************************************
function tabEof(table)  //eof().or.bof()
    return table[TAB_EOF]


******************************************************************************
function tabFound(table)  //found()
    return table[TAB_FOUND]


******************************************************************************
function tabReadOriginalRecordFromDisk(table) //naplozashoz
local err,buffer
    buffer:=replicate(x"20",table[TAB_RECLEN]) 
    if( table[TAB_RECLEN]!=_db_read(table[TAB_BTREE],buffer,table[TAB_RECPOS]) )
        err:=readerrorNew()
        err:operation:="tabReadOriginalRecordFromDisk"
        err:description:=@"_db_read failed"
        err:filename:=tabPathName(table)
        err:oscode:=ferror()
        break(err)
    end
    return buffer
 
 
******************************************************************************
