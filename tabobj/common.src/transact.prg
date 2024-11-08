
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

#include "tabobj.ch"
#include "table.ch"


//#define PUP_TABLE       1  //minden formatumban
//#define PUP_POSITION    2  //minden formatumban 
//#define PUP_RECBUF      3  //minden formatumban 
 
#ifdef _DBFNTX_

function tranNotAllowedInTransaction(table,op,mode)
    return NIL

#else

static debug:="debug"$getenv("TRANCOMMIT")

static trantables:={} //2000.07.16 javitas 
static tranindex:={}
static pendingupdate:={}
static activetransaction:=.f.
static tableid:=0
 

****************************************************************************
function tranIsActiveTransaction()
    return activetransaction 


****************************************************************************
function tranDepth()
    return len(tranindex)


****************************************************************************
function tranAddToPendingUpdates(pup)

local tab:=pup[PUP_TABLE]     
//local pos:=pup[PUP_POSITION]
//local rec:=pup[PUP_RECBUF]

    if( tab[TAB_TRANID]==NIL )
        tab[TAB_TRANID]:=++tableid
        aadd(trantables,tab)
    end

    aadd(pendingupdate,pup)
    return NIL
 

****************************************************************************
function tranRecordLockedInTransaction(table)

    if( table[TAB_TRANID]==NIL )
        table[TAB_TRANID]:=++tableid
        aadd(trantables,table)
    end
    if( table[TAB_TRANLOCK]==NIL )
        table[TAB_TRANLOCK]:=len(table[TAB_LOCKLST])
        //megjegyzi az elso olyan lock indexet,
        //ami a tranzakcion belul lett felteve
    end
    return NIL

****************************************************************************
function tranDeleteOnRollback(table,pos)

    if( table[TAB_TRANID]==NIL )
        table[TAB_TRANID]:=++tableid
        aadd(trantables,table)
    end
    if( table[TAB_TRANDEL]==NIL )
        table[TAB_TRANDEL]:={pos}
    else
        aadd(table[TAB_TRANDEL],pos)
    end
    return NIL
 
****************************************************************************
static function tranClearTransactionID(rb) 

//2000.07.16 javitas
//korabban ez tabObjectList minden elemere tortent,
//ami elengedett minden lockot, olyan filek lockjait is,
//amik nem vettek reszt a tranzakcioban

//2003.03.21 javitas
//csak azokat a lockokat engedjuk el, 
//amik a tranzakcion belul lettek felteve,
//toroljuk a TAB_TRANDEL listaban felsorolt rekordokat

local n, table
local dlst,llst,x,i

    for n:=1 to len(trantables)
    
        table:=trantables[n] 

        // torlendo rekordok (rollback)

        if( rb==.t. .and. NIL!=(dlst:=table[TAB_TRANDEL]) )
            for i:=1 to len(dlst)
                if( tabGoto(table,dlst[i]) )
                    tabDelete(table)
                end
            next
        end
 
        // unlockolando rekordok

        x:=table[TAB_TRANLOCK] 
        if( x==NIL )
            //nincs lock
        elseif( x==1 )
            tabUnlock(table)
        else
            llst:=aclone(tabLocklist(table))
            for i:=x to len(llst)
                tabUnlock(table,llst[i])
            next
        end

        table[TAB_TRANDEL]:=NIL
        table[TAB_TRANLOCK]:=NIL
        table[TAB_TRANID]:=NIL
    next

    trantables:={}
    return NIL
 
 
****************************************************************************
function tranSynchronizeRecord(table,lockflag)  

//ujrairva 2001.12.14
//Kiirja az aktualis rekordot.
//Olyankor van ra szukseg, amikor tranzakcio
//kozben ra kell seekelni egy uj rekordra (pl.insert),
//vagy azonnal lathatova kell tenni egy kozosen
//hasznalt szamlalo tartalmat.

//kiegeszitve 2002.02.16
//Ha lockflag==.t., akkor a rekord lockjat elengedi.
//Enelkul pl. a PARAM tabla ugyszam szamlalot tartalmazo
//rekordjan a tranzakcio egesz ideje alatt lock maradna,
//ami teljesen sorbaallitana a konkurrens programokat.

local pup,t,n
local tranid,recno

    tabCommit(table)
 
    if( activetransaction )

        if( debug )   
            ? replicate("-",79)
            ? @"Synchronized"
            ? replicate("-",79)
        end
 
        tranid:=table[TAB_TRANID] 
        recno:=tabPosition(table)
 
        for n:=1 to len(pendingupdate)
            pup:=pendingupdate[n]
            
            if( pup!=NIL .and.;
                pup[PUP_TABLE][TAB_TRANID]==tranid .and.;
                pup[PUP_POSITION]==recno )

                if( debug )   
                    print_debug_info(pup)
                end

                table[TAB_MODIF]:=.t.
                tabCommit(table,pup)
                pendingupdate[n]:=NIL
            end
        next
 
        if( lockflag==.t. )
            activetransaction:=.f. 
            tabUnlock(table,recno)
            activetransaction:=.t. 
        end
    end
    return NIL


****************************************************************************
function tranLastRecordUpdate(table,info)
 
local n,pup,pos,tid 
 
    if( !empty(tid:=table[TAB_TRANID]) )
        pos:=tabPosition(table) 

        for n:=len(pendingupdate) to 1 step -1
            pup:=pendingupdate[n]

            if( pup!=NIL .and.;
                pos==pup[PUP_POSITION] .and.;
                tid==pup[PUP_TABLE][TAB_TRANID] )

                table[TAB_RECBUF]:=substr(pup[PUP_RECBUF],1)
                info:=pup //2001.12.27 BTBTX-hez
                return .t.
            end
        next
    end
    return .f.


****************************************************************************
function tranNotAllowedInTransaction(table,op,mode)
local err
    if( activetransaction .and. (mode==NIL .or. table[TAB_TRANID]!=NIL) )
        err:=errorNew()
        err:operation:=op
        err:description:=@"not allowed in transaction"
        err:filename:=tabPathName(table)
        break(err)
    end
    return NIL


****************************************************************************
function tranTimeout()
local err
    if( trantimer_timeout(.t.) )
        err:=trantimeouterrorNew()
        err:operation:="tranTimeout"
        err:description:=@"transaction timed out"
        break(err)
    end


****************************************************************************
function tranBegin()
    tabCommitAll()
    if( !activetransaction )
        activetransaction:=.t. 
        if( tranEnforced() )
            tranSemaOn(SEMA_RLOCK)
        end
    end
    aadd(tranindex,len(pendingupdate)+1)
    return len(tranindex)


****************************************************************************
function tranRollback(tx)

local err, n, t

    tabCommitAll() 
 
    if( activetransaction )

        if( tx==NIL )
            tx:=len(tranindex)
        end
    
        if( tx<1 .or. len(tranindex)<tx )
            err:=errorNew()
            err:operation:="tranRollback"
            err:description:=@"invalid transaction ID"
            break(err)
        end
 
        asize(pendingupdate,tranindex[tx]-1)
        asize(tranindex,tx-1)

        for n:=1 to len(trantables)
            t:=trantables[n] 
            tabGoto(t,tabPosition(t))  
            if( tabDeleted(t) )
                tabGoEOF(t)
            end
        next
 
        if( empty(tranindex) )  
            activetransaction:=.f. 
            tranClearTransactionID(.t.)  
            if( tranEnforced() )
                tranSemaOff(SEMA_RLOCK)
            end
        end
    end

    return NIL


****************************************************************************
function tranCommit(tx)

local err,n,pup,table,pos
local savepos


    tranTimeout()
    tabCommitAll() 

    if( activetransaction )
    
        if( tx==NIL )
            tx:=len(tranindex) 
        end

        if( tx<1 .or. len(tranindex)<tx )
            err:=errorNew()
            err:operation:="tranCommit"
            err:description:=@"invalid transaction ID"
            break(err)
        end

        asize(tranindex,tx-1)
     
        if( empty(tranindex) )

            if( tranEnforced() )
                tranSemaOff(SEMA_RLOCK)
            end
    
            if( debug )
                ? replicate("-",79)
                ? @"Pending updates"
                ? replicate("-",79)
            end
            
            savepos:=array(len(pendingupdate))

            set signal disable
 
            for n:=1 to len(pendingupdate)
                pup:=pendingupdate[n] 

                if( pup!=NIL )
                    table:=pup[PUP_TABLE]

                    if( table[TAB_TRANID]!=NIL )
                        savepos[n]:={table,tabPosition(table)}
                        table[TAB_TRANID]:=NIL
                    end
 
                    if( debug )   
                        print_debug_info(pup)
                    end
 
                    table[TAB_MODIF]:=.t.
                    tabCommit(table,pup)
                end
            next

            set signal enable

            for n:=1 to len(savepos)
                //csak miutan minden commit megvan,
                //azutan pozicionalunk az eredeti rekordra
                if( savepos[n]!=NIL )
                    tabGoto(savepos[n][1],savepos[n][2]) 
                end
            next
 
            activetransaction:=.f. 
            tranClearTransactionID()  
            pendingupdate:={}
        end
    end
    
    return NIL

 
*****************************************************************************
function tranListPendingUpdates()
local n,pup
    ? replicate("-",79)
    ? @"Pending updates"
    ? replicate("-",79)
    for n:=1 to len(pendingupdate)
        pup:=pendingupdate[n] 
        if( pup!=NIL )
            print_debug_info(pup)
        end
    next


*****************************************************************************
static function print_debug_info(pup)

local tab:=pup[PUP_TABLE]
local pos:=pup[PUP_POSITION]
local rec:=pup[PUP_RECBUF]
local tid:=tab[TAB_TRANID]

local pos0:=tabPosition(tab)
local rec0:=array(tabFcount(tab)),v0
local rec1:=array(tabFcount(tab)),v1 
local del0
local del1
local n, keyx

    //a tranzakcio elott lemezre irt rekord:
    //tranid torlese miatt tabGoto nem szedi fel
    //a memoriaban tarolt rekordvaltozatot

    tab[TAB_TRANID]:=NIL
    tabGoto(tab,pos)     

    del0:=tabEof(tab).or.tabDeleted(tab)
    if( !del0 )
        for n:=1 to tabFcount(tab)
            rec0[n]:=tabEvalcolumn(tab,n) 
        next
        keyx:=key(tab)
    end
    
    //a tranzakcio kozben modosult rekord:
    //a pup-ban tarolt rekord kozvetlenul betoltve
    
    tab[TAB_RECBUF]:=substr(rec,1)
    del1:=tabDeleted(tab)
    if( !del1 )
        for n:=1 to tabFcount(tab)
            rec1[n]:=tabEvalcolumn(tab,n) 
        next
        keyx:=key(tab)
    end
    
    //az eredeti tablaallapot visszaallitasa,
    //nincs ra szukseg, de biztos, ami biztos
    
    tab[TAB_TRANID]:=tid 
    tabGoto(tab,pos0)    
    
    //az elteresek listazasa:
    //alabb mar nem modositjuk a tablat,
    //es a rekordbuffert sem olvassuk

    ? @"table:", tabFile(tab), @" recno:", pos, @" key:", keyx
    
    if( !del0 .and. del1 )
        ?? @" deleted"
        for n:=1 to tabFcount(tab)
            v0:=rec0[n]
            if( !empty(v0) )
                ? " ", tabColumn(tab)[n][COL_NAME], "[", v0, "]"
            end
        next
 
    elseif( del0 .and. !del1 )
        ?? @" appended"
        for n:=1 to tabFcount(tab)
            v1:=rec1[n]
            if( !empty(v1) )
                ? " ", tabColumn(tab)[n][COL_NAME], "[", v1, "]"  
            end
        next
 
    else
        for n:=1 to tabFcount(tab)
            v0:=rec0[n]
            v1:=rec1[n]
            if( !v0==v1 )
                ? " ", tabColumn(tab)[n][COL_NAME], "[", v0, "] -> [", v1, "]"  
            end
        next
    end
    
    return NIL


*****************************************************************************
static function key(table) 
local key, n 
    if( empty(table[TAB_ORDER]) )
        key:={"recno"}
    else
        key:=aclone(table[TAB_INDEX][table[TAB_ORDER]][IND_COL])
        for n:=1 to len(key)
            key[n]:=tabEvalColumn(table,key[n])
        next
    end
    return key
 

*****************************************************************************
 
#endif

 