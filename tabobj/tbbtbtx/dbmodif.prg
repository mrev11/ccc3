
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

#define ACLONE(x) if(x==NIL,NIL,aclone(x))
 
******************************************************************************
//Public interface

//function tabCommit(table)                 //módosult rekord kiírása
//function tabDelete(table)                 //töröl + lép
//function tabDeleted(table)                //törölt-e a rekord?
//function tabMAppend(table,userblock)      //append, lockokat megtartja
//function tabAppend(table,userblock,flag)  //append
//function tabInsert(table,key,usrblk,flag) //append egyedi kulccsal

******************************************************************************
function tabCommit(table,pup) 
 
local index,idx,n
local keyold,keynew
local recno,status,modifkey

    if( table[TAB_MODIF] )

        table[TAB_MODIF]:=.f.

        if( tranIsActiveTransaction() ) 
        
            if( pup==NIL ) //rekordállapot mentés

                tranAddToPendingUpdates({;
                    table,;                        //tábla
                    tabPosition(table),;           //pozíció (recno)
                    substr(table[TAB_RECBUF],1),;  //rekord másolat!
                    save_curkey(table),;           //eredeti kulcsok
                    table[TAB_RECPOS],;            //page/index! 
                    table[TAB_MODIFKEY],;          //módosult-e kulcs 
                    table[TAB_MODIFAPP],;          //új-e a rekord
                    ACLONE(table[TAB_MEMODEL])} )  //törlendő memók

                table[TAB_MODIFKEY]:=.f.
                table[TAB_MODIFAPP]:=.f.
                table[TAB_MEMODEL]:=NIL

                //?"<save>",table[TAB_POSITION],_db_recpos2array(table[TAB_RECPOS]) 
                return NIL
 
            else //rekordállapot visszaállítás

                table[TAB_POSITION] := pup[PUP_POSITION] 
                table[TAB_RECBUF]   := substr(pup[PUP_RECBUF],1) //másolat!
                restore_curkey(table,pup[PUP_CURKEY])
                table[TAB_RECPOS]   := pup[PUP_RECPOS]
                table[TAB_MODIFKEY] := pup[PUP_MODIFKEY] 
                table[TAB_MODIFAPP] := pup[PUP_MODIFAPP] 
                table[TAB_MEMODEL]  := ACLONE(pup[PUP_MEMODEL])

                //?"<rest>",table[TAB_POSITION],_db_recpos2array(table[TAB_RECPOS])  
            end
        end
 
        modifkey:=table[TAB_MODIFKEY] //.and. table[TAB_OPEN]<=OPEN_EXCLUSIVE

        set signal disable

        if( table[TAB_LOGGED]!=.f. )
            tabWriteChangeLog(table)
        end
 
        if( modifkey )
        
            _db_header_read(table[TAB_BTREE],.t.) //for writing

            //ki kell törölni az aktuális rekord kulcsait 
            //csak a megváltozott kulcsokat törlöm
            
            index:=tabIndex(table)
            recno:=tabPosition(table)

            for n:=1 to len(index)
                idx:=index[n]
                keyold:=idx[IND_CURKEY]
                keynew:=tabKeyCompose(table,n)
                
                if( !keyold==keynew )
                    idx[IND_CURKEY]:=keynew

                    if( !table[TAB_MODIFAPP] )

                        _db_setord(table[TAB_BTREE],idx[IND_NAME])
                        status:=_db_del(table[TAB_BTREE],keyold)
                        //? "del", idx[IND_NAME], keyold

                        if( 0!=status )
                            taberrOperation("tabCommit")
                            taberrDescription(@"failed deleting key")
                            taberrArgs({"_db_del",status,keyold})
                            tabError(table)
                        end
                    end
                else
                    idx[IND_CURKEY]:=NIL
                end
            next
        end
        
        
        status:=_db_rewrite(table[TAB_BTREE],table[TAB_RECBUF],table[TAB_RECPOS]) 
        if( status!=0 )
            taberrOperation("tabCommit")
            taberrDescription(@"failed writing data record")
            taberrArgs({"_db_rewrite",status})
            tabError(table)
        end

        if( modifkey )
            //be kell tenni az új kulcsokat 

            if( table[TAB_MODIFAPP] )
                keynew:=tabKeyCompose(table,0)

                _db_setord(table[TAB_BTREE],"recno")
                status:=_db_put(table[TAB_BTREE],keynew)
                //? "put", "recno", keynew
 
                if( status!=0 )
                    taberrOperation("tabCommit")
                    taberrDescription(@"failed writing key")
                    taberrArgs({"_db_put",status,keynew})
                    tabError(table)
                end
            end

            for n:=1 to len(index)
                idx:=index[n]
                keynew:=idx[IND_CURKEY]
                if( keynew!=NIL )

                    _db_setord(table[TAB_BTREE],idx[IND_NAME])
                    status:=_db_put(table[TAB_BTREE],keynew)
                    //? "put", idx[IND_NAME], keynew
 
                    if( status!=0 )
                        taberrOperation("tabCommit")
                        taberrDescription(@"failed writing key")
                        taberrArgs({"addkey",status})
                        tabError(table)
                    end
                    
                    idx[IND_CURKEY]:=NIL
                end
            next

            table[TAB_MODIFKEY]:=.f.
            table[TAB_MODIFAPP]:=.f.

            _db_header_write(table[TAB_BTREE])
            tabEstablishPosition(table)
        end

        //megszűnt memók törlése
        tabMemoDel(table)

        set signal enable
    end
    return NIL


******************************************************************************
function tabCommitAll(table)  //összes table objektumra
local n, tlist:=tabObjectList()

    for n:=1 to len(tlist)
        table:=tlist[n]
        if( table[TAB_OPEN]>0 )
            tabCommit(table)
        end
    next
    return NIL


******************************************************************************
function tabDelete(table) // delete + skip
local pos:=tabPosition(table)

    if( pos<=0 ) //a filé nincs pozícionálva
        return NIL

    elseif( !tabIsLocked(table) )
        taberrOperation("tabDelete")
        taberrDescription(@"record lock requiered")
        tabError(table)
    end

    table[TAB_MODIF]:=.t.
    table[TAB_FOUND]:=.f.
    xvputbyte(table[TAB_RECBUF],0,42) //42==asc("*")
 
    tabUnlock(table,pos)

    if( tabGetNext(table,1)<1 )
        //tabGoBottom(table)
        tabGoEOF(table) //1999.02.17
    end
    return NIL


******************************************************************************
function tabDeleted(table) //deleted()
    return 42==xvgetbyte(table[TAB_RECBUF],0)  //'*'


******************************************************************************
function tabMAppend(table,userblock) //append blank, meglévő lockokat maradnak
    return tabAppend(table,userblock,.f.)  


******************************************************************************
function tabAppend(table,userblock,flag) //append blank
local result, recpos, recno

    tabGoEof(table)
    xvputbyte(table[TAB_RECBUF],0,42) //42==asc("*") törölt
    recpos:=_db_append(table[TAB_BTREE],table[TAB_RECBUF],@recno)
    
    //?"<append>",recno,_db_recpos2array(recpos)

    table[TAB_RECPOS]:=recpos
    table[TAB_POSITION]:=recno
    table[TAB_EOF]:=.f.

    result:=tabRecLock(table,if(flag!=.f.,NIL,recno),userblock)

    table[TAB_MODIF]:=.t.
    table[TAB_MODIFKEY]:=.t.
    table[TAB_MODIFAPP]:=.t.
    xvputbyte(table[TAB_RECBUF],0,32) //32==asc(" ") törölt vissza

    return result


******************************************************************************
function tabInsert(table,key,usrblk,flag)

// key   : az aktuális vezérlőindexnek megfelelő kulcskifejezés lista
// usrblk: átadja tabAppend()-nek
// flag  : átadja tabAppend()-nek
//
// tabInsert() rááll a kulcslista (key) által azonosított rekordra.
// Ha ilyen rekord nincs, akkor betesz egyet, ennek kulcsmezőit kitőlti 
// a key-ben megadott értékekkel, majd egy újbóli seek-kel ellenőrzi,
// hogy az első seek és a bevitel között egy másik munkaállomás nem
// vitt-e be egy ugyanolyan kulcsú rekordot. Ha a bevitel után a rekord
// nem egyedi, akkor a rutin törli a frissen bevitt rekordot, és rááll
// a második seek-ben talált rekordra.
//
// Visszatérés:
// NIL, ha a fájlban már benne volt a keresett rekord
// .t., ha a rekord a hívás hatására került be a fájlba
// .f., ha a rekord nem volt benn, és nem is sikerült berakni
//

local ind,n,posapp,posseek

    if( tabSeek(table,key) )
        return NIL
    elseif( !tabAppend(table,usrblk,flag) )
        return .f.
    end

    ind:=table[TAB_INDEX][table[TAB_ORDER]][IND_COL]
    if( valtype(key)!="A" ); key:={key}; end
    for n:=1 to len(key)
        tabEvalColumn(table,ind[n],key[n])
    next

    if( tabIsopen(table)>=OPEN_EXCLUSIVE )
        if( tranIsActiveTransaction() )
            tranDeleteOnRollback(table,tabPosition(table))
        end
        return .t.
    end
    

    tranSynchronizeRecord(table)
    posapp:=tabPosition(table)
    tabSeek(table,key) 
    posseek:=tabPosition(table)
    
    if( posapp!=posseek )
        tabGoto(table,posapp)
        tabDelete(table)
        tranSynchronizeRecord(table)
        tabGoto(table,posseek)
        return NIL
    end
    if( tranIsActiveTransaction() )
        tranDeleteOnRollback(table,posapp)
    end
    return .t.


******************************************************************************
static function save_curkey(table)
local ck,index,n
    ck:=array(len(index:=tabIndex(table)))
    for n:=1 to len(ck)
        ck[n]:=index[n][IND_CURKEY]
        index[n][IND_CURKEY]:=NIL
    next
    return ck 


******************************************************************************
static function restore_curkey(table,ck)
local index,n
    index:=tabIndex(table) 
    for n:=1 to len(ck)
        index[n][IND_CURKEY]:=ck[n] 
    next
    return NIL
 
 
******************************************************************************
 