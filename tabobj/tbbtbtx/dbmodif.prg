
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

//function tabCommit(table)                 //modosult rekord kiirasa
//function tabDelete(table)                 //torol + lep
//function tabDeleted(table)                //torolt-e a rekord?
//function tabMAppend(table,userblock)      //append, lockokat megtartja
//function tabAppend(table,userblock,flag)  //append
//function tabInsert(table,key,usrblk,flag) //append egyedi kulccsal

******************************************************************************
function tabCommit(table,pup) 
 
local index,idx,n
local keyold,keynew
local recno,status
local modifkey:=.f.
local modifapp:=.f.
local modifdel:=.f.

    if( table[TAB_MODIF] )

        table[TAB_MODIF]:=.f.

        if( tranIsActiveTransaction() ) 
        
            if( pup==NIL ) //rekordallapot mentes
                
                tranAddToPendingUpdates({;
                    table,;                        //tabla
                    tabPosition(table),;           //pozicio (recno)
                    substr(table[TAB_RECBUF],1),;  //rekord masolat!
                    save_curkey(table),;           //eredeti kulcsok
                    table[TAB_RECPOS],;            //page/index! 
                    table[TAB_MODIFKEY],;          //modosult-e kulcs 
                    table[TAB_MODIFAPP],;          //uj-e a rekord
                    ACLONE(table[TAB_MEMODEL])} )  //torlendo memok

                table[TAB_MODIFKEY]:=.f.
                table[TAB_MODIFAPP]:=.f.
                table[TAB_MEMODEL]:=NIL

                //?"<save>",table[TAB_POSITION],_db_recpos2array(table[TAB_RECPOS]) 
                return NIL
 
            else //rekordallapot visszaallitas

                table[TAB_POSITION] := pup[PUP_POSITION] 
                table[TAB_RECBUF]   := substr(pup[PUP_RECBUF],1) //masolat!
                restore_curkey(table,pup[PUP_CURKEY])
                table[TAB_RECPOS]   := pup[PUP_RECPOS]
                table[TAB_MODIFKEY] := pup[PUP_MODIFKEY] 
                table[TAB_MODIFAPP] := pup[PUP_MODIFAPP] 
                table[TAB_MEMODEL]  := ACLONE(pup[PUP_MEMODEL])

                //?"<rest>",table[TAB_POSITION],_db_recpos2array(table[TAB_RECPOS])  
            end
        end
 
        // App Del Key
        //  0   0   0  kulcsot nem erinto modositas
        //  0   0   1  kulcsot is erinto modositas
        //  0   1   0  normal torles
        //  0   1   1  torles kulcs modositasa utan
        //  1   0   0  *** nincs ilyen eset
        //  1   0   1  normal append
        //  1   1   0  *** nincs ilyen eset
        //  1   1   1  append utan torles


        modifkey:=table[TAB_MODIFKEY]
        modifapp:=table[TAB_MODIFAPP]
        modifdel:=(42==xvgetbyte(table[TAB_RECBUF],0)) .and. NIL!=tabKeepDeleted(table)
        
        // modifdel==.t. <==> ha uj modszeru torles van
        // A regi modszeru torles (ami meghagyja a rekordot)
        // a kozonseges modositasokhoz hasonloan mukodik.
        // Regi modszeru torlesnel az esetleg megvaltozott
        // kulcsokat a modositasokhoz hasonloan kell kezelni.

        //modifapp: korabban nem letezo rekord
        //modifdel: megszuno rekord
        //modifkey: korabban is letezo, megmarado rekord


        set signal disable

        if( table[TAB_LOGGED]!=.f. )
            tabWriteChangeLog(table)
        end


        // 1. REGI KULCSOK TORLESE

        if( modifapp )
            // korabban nem letezo rekord, nincsenek regi kulcsok

            _db_header_read(table[TAB_BTREE],.t.) //for writing
     
        elseif( modifdel )
            // megszuno rekord, minden kulcsot torolni kell, a recno-t is
            // (append nem ide jon -> modifapp)
            // (hagyomanyos torles nem ide jon -> mofidkey)

            _db_header_read(table[TAB_BTREE],.t.) //for writing
                   
            index:=tabIndex(table)
            for n:=0 to len(index)
                //n==0 a recno
                if( table[TAB_ORDER]!=n )
                    deletekey(table,n)
                end
            next
            deletekey(table,table[TAB_ORDER]) // ezt utoljara

        elseif( modifkey )
            // nem ujonnan letrehozott es nem megszunoben levo, tehat
            // megmarado rekord, torolni kell a megvaltozott (regi) kulcsokat
            // (kulcsot is erinto modositas)
            // (modositas + hagyomanyos torles)

            _db_header_read(table[TAB_BTREE],.t.) //for writing
            
            index:=tabIndex(table)
            for n:=1 to len(index)
                idx:=index[n]
                keyold:=idx[IND_CURKEY]
                keynew:=tabKeyCompose(table,n)
                if( !keyold==keynew )
                     //? "del", idx[IND_NAME], keyold::key2str
                    _db_setord(table[TAB_BTREE],idx[IND_NAME])
                    status:=_db_del(table[TAB_BTREE],keyold)
                    if( 0!=status )
                        taberrOperation("tabCommit")
                        taberrDescription(@"failed deleting key")
                        taberrArgs({"_db_del",status,idx[IND_NAME],keyold})
                        tabError(table)
                    end
                    idx[IND_CURKEY]:=keynew  //ezt kell majd kiirni
                else
                    idx[IND_CURKEY]:=NIL
                end
            next
        end
        
        // 2. ADATREKORD KIIRASA
        
        status:=_db_rewrite(table[TAB_BTREE],table[TAB_RECBUF],table[TAB_RECPOS]) 
        if( status!=0 )
            taberrOperation("tabCommit")
            taberrDescription(@"failed writing data record")
            taberrArgs({"_db_rewrite",status})
            tabError(table)
        end


        // 3. UJ KULCSOK KIIRASA

        if( modifdel )
            // megszuno rekord, nincsenek uj kulcsok
            // (hagyomanyos torles nem ide jon -> modifkey/modifapp)

            _db_header_write(table[TAB_BTREE])
  
        elseif( modifapp )
            // korabban nem letezo rekord,  ki kell irni az osszes kulcsot
            // (normal append)
            // (append + hagyomanyos torles)

            keynew:=tabKeyCompose(table,0)
            //? "put", "recno", keynew::key2str
            _db_setord(table[TAB_BTREE],"recno")
            status:=_db_put(table[TAB_BTREE],keynew)
            if( status!=0 )
                taberrOperation("tabCommit")
                taberrDescription(@"failed writing key")
                taberrArgs({"_db_put",status,"recno",keynew})
                tabError(table)
            end

            index:=tabIndex(table)
            for n:=1 to len(index)
                idx:=index[n]
                keynew:=tabKeyCompose(table,n)
                //? "put", idx[IND_NAME], keynew::key2str
                _db_setord(table[TAB_BTREE],idx[IND_NAME])
                status:=_db_put(table[TAB_BTREE],keynew)
                if( status!=0 )
                    taberrOperation("tabCommit")
                    taberrDescription(@"failed writing key")
                    taberrArgs({"_db_put",status,idx[IND_NAME],keynew})
                    tabError(table)
                end
                idx[IND_CURKEY]:=NIL
            next

            _db_header_write(table[TAB_BTREE])
            tabEstablishPosition(table)


        elseif( modifkey )
            // megmarado rekord, ki kell irni a megvaltozott (uj) kulcsokat
            // (kulcsot is erinto modositas)
            // (modositas + hagyomanyos torles)

            index:=tabIndex(table)
            for n:=1 to len(index)
                idx:=index[n]
                keynew:=idx[IND_CURKEY]
                if( keynew!=NIL )
                    //? "put", idx[IND_NAME], keynew::key2str
                    _db_setord(table[TAB_BTREE],idx[IND_NAME])
                    status:=_db_put(table[TAB_BTREE],keynew)
                    if( status!=0 )
                        taberrOperation("tabCommit")
                        taberrDescription(@"failed writing key")
                        taberrArgs({"_db_put",status,idx[IND_NAME],keynew})
                        tabError(table)
                    end
                    idx[IND_CURKEY]:=NIL
                end
            next

            _db_header_write(table[TAB_BTREE])
            tabEstablishPosition(table)
        end

        //megszunt memok torlese
        tabMemoDel(table)

        set signal enable

        table[TAB_MODIFKEY]:=.f.
        table[TAB_MODIFAPP]:=.f.
    end
    return NIL


******************************************************************************
static function deletekey(table,n) //tabDelete()-ben ez torli a kulcsokat
local index:=tabIndex(table)
local idx,keyold,datkey,idxname,status

    if( n==0 )
        if( 0>_db_setord(table[TAB_BTREE],"deleted") )
            taberrOperation("tabCommit")
            taberrDescription(@"failed to set deleted index")
            tabError(table)
        end
        keyold:=tabKeyCompose(table,0)
        datkey:=date()::dtos::str2bin+keyold  // megjegyzi mikor toroltek
        //? "put", "deleted", datkey::key2str //10 byte
        status:=_db_put(table[TAB_BTREE],datkey)
        if( status!=0 )
            taberrOperation("tabCommit")
            taberrDescription(@"failed writing key")
            taberrArgs({"_db_put",status,"recno",datkey})
            tabError(table)
        end
        idxname:="recno"
    else  
        idx:=index[n]
        keyold:=idx[IND_CURKEY]
        if( keyold==NIL )
            keyold:=tabKeyCompose(table,n)
        end
        idx[IND_CURKEY]:=NIL
        idxname:=idx[IND_NAME]
    end

    //? "del", idxname, keyold::key2str
    _db_setord(table[TAB_BTREE],idxname)
    status:=_db_del(table[TAB_BTREE],keyold)
    if( 0!=status )
        taberrOperation("tabCommit")
        taberrDescription(@"failed deleting key")
        taberrArgs({"_db_del",status,idxname,keyold})
        tabError(table)
    end


******************************************************************************
function tabCommitAll(table)  //osszes table objektumra
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
local column,n

    if( pos<=0 ) //a file nincs pozicionalva
        return NIL

    elseif( !tabIsLocked(table) )
        taberrOperation("tabDelete")
        taberrDescription(@"record lock requiered")
        tabError(table)
    end

    table[TAB_MODIF]:=.t.
    table[TAB_FOUND]:=.f.
    xvputbyte(table[TAB_RECBUF],0,42) //42==asc("*")

    if( NIL!=tabKeepDeleted(table) )
        // ha a rekordot tenylegesen toroljuk
        // (azaz nem csak a torolt mezo alapjan szurjuk
        // hanem az indexbol kiveve elerhetetlenne tesszuk)
        // akkor kulon torolni kell a memo mezoket

        column:=tabColumn(table)
        for n:=1 to len(column)
            if( tabMemoField(table,column[n]) )
                tabEvalColumn(table,n,a"")
            end
        next
    end
 
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
function tabMAppend(table,userblock) //append blank, meglevo lockokat maradnak
    return tabAppend(table,userblock,.f.)  


******************************************************************************
function tabAppend(table,userblock,flag) //append blank
local result, recpos, recno

    if( NIL!=tabKeepDeleted(table) )
        if( undelete(table,flag) )
            // uj rekord egy korabban torolt helyen
            return .t.
        end
    end

    tabGoEof(table)
    xvputbyte(table[TAB_RECBUF],0,42) //42==asc("*") torolt
    recpos:=_db_append(table[TAB_BTREE],table[TAB_RECBUF],@recno)
    
    //?"<append>",recno,_db_recpos2array(recpos)

    table[TAB_RECPOS]:=recpos
    table[TAB_POSITION]:=recno
    table[TAB_EOF]:=.f.

    result:=tabRecLock(table,if(flag!=.f.,NIL,recno),userblock)

    table[TAB_MODIF]:=.t.
    table[TAB_MODIFKEY]:=.t.
    table[TAB_MODIFAPP]:=.t.
    xvputbyte(table[TAB_RECBUF],0,32) //32==asc(" ") torolt vissza

    return result


******************************************************************************
static function undelete(table,flag) // uj rekord egy korabban torolt helyen

local key,primarykey
local idxcurr,idxname
local status,recno,recpos
local result:=.f.
 
    tabCommit(table)
 
    idxcurr:=table[TAB_ORDER]
    if( idxcurr==0 )
        idxname:="recno"
    else
        idxname:=tabIndex(table)[idxcurr][IND_NAME]
    end

    if( 0>_db_setord(table[TAB_BTREE],"deleted") )
        // nincs deleted index
        _db_setord(table[TAB_BTREE],idxname)
        return .f.
    end

    key:=_db_first(table[TAB_BTREE])
    while( key!=NIL .and. !keepdeleted(table,key) )

        // a toroltek kozott megy
        // amig sikerul egyet lockolni
        // vagy amig el nem fogynak

        primarykey:=right(key,10) 
        table[TAB_POSITION]:=recno:=_db_rdbig32(left(primarykey,4)) 
        table[TAB_RECPOS]:=recpos:=right(primarykey,6) 

        result:=tabRecLock(table,if(flag!=.f.,NIL,recno),{||.f.})
        if( result )
            //? "UNDELETE",key::key2str

            table[TAB_MODIF]:=.t.
            table[TAB_MODIFKEY]:=.t.
            table[TAB_MODIFAPP]:=.t.
            table[TAB_EOF]:=.f.
            xvputfill(table[TAB_RECBUF],0,table[TAB_RECLEN],32) //space

            // ki kell venni a kulcsot a toroltek kozul
            // nehogy egy masik append megegyszer megtalalja

            status:=_db_del(table[TAB_BTREE],key)
            if( 0!=status )
                taberrOperation("tabCommit")
                taberrDescription(@"failed undelete record")
                taberrArgs({"_db_del",status,key})
                tabError(table)
            end
            exit
        end
        key:=_db_next(table[TAB_BTREE])
    end

    _db_setord(table[TAB_BTREE],idxname)

    return result


******************************************************************************
static function keepdeleted(table,key) 
    return key::left(8)::stod()<date()+tabKeepDeleted(table)


******************************************************************************
function tabKeepDeleted(table,nday)
    if( nday!=NIL )
        table[TAB_KEEPDELETED]:=nday
    end
    return table[TAB_KEEPDELETED]


******************************************************************************
function tabInsert(table,key,usrblk,flag)

// key   : az aktualis vezerloindexnek megfelelo kulcskifejezes lista
// usrblk: atadja tabAppend()-nek
// flag  : atadja tabAppend()-nek
//
// tabInsert() raall a kulcslista (key) altal azonositott rekordra.
// Ha ilyen rekord nincs, akkor betesz egyet, ennek kulcsmezoit kitolti 
// a key-ben megadott ertekekkel, majd egy ujboli seek-kel ellenorzi,
// hogy az elso seek es a bevitel kozott egy masik munkaallomas nem
// vitt-e be egy ugyanolyan kulcsu rekordot. Ha a bevitel utan a rekord
// nem egyedi, akkor a rutin torli a frissen bevitt rekordot, es raall
// a masodik seek-ben talalt rekordra.
//
// Visszateres:
// NIL, ha a fajlban mar benne volt a keresett rekord
// .t., ha a rekord a hivas hatasara kerult be a fajlba
// .f., ha a rekord nem volt benn, es nem is sikerult berakni
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
 