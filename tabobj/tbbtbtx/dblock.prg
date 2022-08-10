
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


******************************************************************************
//Public interface

//function tabLock(table,userblock)           //fajl lock
//function tabALock(table,recarr,userblock)   //array lock
//function tabMLock(table,rec,userblock)      //tobbszoros rekord lock
//function tabRLock(table,userblock)          //egyszeres rekord lock
//function tabRecLock(table,record,userblock) //rekord lock
//function tabUnlockAll(table)                //osszes table objektumra
//function tabUnlock(table,record)            //fajl es single/multiple unlock
//function tabIsLocked(table)                 //kereses locklist-ben
//function tabLocklist(table)                 //lockolt rekordok listaja  




******************************************************************************
function tabLockCount(table,inc)

static lkcount:=0
static semafd:=semafd()

    if( inc==1 )
        lkcount+=inc
        //?  "LK",lkcount,tabFile(table),table[TAB_LOCKLST]

        if(semafd!=NIL .and. lkcount==1)
            //elsot megfogja
            fwaitlock(semafd,1,1,.t.) //exclusive
            fwaitlock(semafd,0,1,.f.) //shared
            funlock(semafd,1,1)
        end

    elseif( inc==-1 )
        lkcount+=inc
        //?  "UN",lkcount,tabFile(table),table[TAB_LOCKLST]

        if(semafd!=NIL .and. lkcount==0)
            //utolsot elengedi
            funlock(semafd,0,1)
        end
    end
    return lkcount


******************************************************************************
static function semafd()
local sema,fd,e 
    if( !empty(sema:=getenv("CCC_LOCK_SEMAPHOR")) )
        fd:=fopen(sema,FO_NOLOCK+FO_READWRITE)
        if( fd<0 )
            e:=fnferrorNew()
            e:operation:="tabLockCount"
            e:description:=@"CCC_LOCK_SEMAPHOR open failed"
            e:filename:=sema
            e:oscode:=ferror()
            break(e)
        end
    end
    return fd // fd vagy NIL


******************************************************************************
function tabLock(table,userblock) //fajl lock

local mode:=tabIsOpen(table)
local state:=tabSave(table)

    if( mode>=OPEN_EXCLUSIVE )
        return .t.
    end

    while( .t. )
        if( tabOpen(table,OPEN_EXCLUSIVE,{||.f.}) )
            //tabOpen() tartalmazza a szukseges varakozast
            table[TAB_LOCKFIL]:=.t.
            table[TAB_LOCKLST]:={}
            tabRestore(table,state)
            return .t.
        end

        tabOpen(table,mode)
        table[TAB_LOCKFIL]:=.f.
        table[TAB_LOCKLST]:={}
        tabRestore(table,state)

        taberrOperation("tabLock")
        tabErrDescription(@"file lock failed")

        if( valtype(userblock)=="B" )
            taberrUserBlock(userblock)
            return tabError(table)
        else
            taberrUserBlock("PUK")
            tabError(table)
        end
    end
    return .f.


******************************************************************************
function tabALock(table,recarr,userblock) //array lock
// elengedi a korabbi rekordlockokat, lockolja recarr elemeit,
// ha valamelyik lock sikertelen, elengedi az addigi lockokat

    return tabRecLock(table,recarr,userblock)


******************************************************************************
function tabMLock(table,rec,userblock) //tobbszoros rekord lock
// lockol egy rekordot, a meglevo lockok megmaradnak
// rec defaultja az aktualis rekord

    return tabRecLock(table,if(rec==NIL,tabPosition(table),rec),userblock)


*****************************************************************************
function tabRLock(table,userblock) //egyszeres rekord lock
// lockolja az aktualis rekordot, elozoleg a tobbi lockot feloldja

    return tabRecLock(table,,userblock)


*****************************************************************************
static function _sleep()
    Sleep(100)
    return NIL


*****************************************************************************
function tabRecLock(table,record,userblock)  //rekord lock

local n,s,timeout
   
    tabCommit(table)

    if( userblock::valtype=="N" )
        timeout:=userblock
        if( tabIsOpen(table)==OPEN_EXCLUSIVE )
            return .t.
        elseif( record==NIL )
            return 0==lockCurrent(table,timeout)
        elseif( valtype(record)=="N" )
            return 0==lockPosition(table,record,timeout)
        elseif( valtype(record)=="A" )
            return 0==lockArray(table,record,timeout)
        end
    else
        while( .t. )
    
            if( tabIsOpen(table)==OPEN_EXCLUSIVE )
                return .t.
    
            elseif( record==NIL )
                for n:=1 to 10
                    if( 0==(s:=lockCurrent(table)) )
                        return .t.
                    end
                    _sleep()
                next
    
            elseif( valtype(record)=="N" )
                for n:=1 to 10
                    if( 0==(s:=lockPosition(table,record)) )
                        return .t.
                    end
                    _sleep()
                next
    
            elseif( valtype(record)=="A" )
                for n:=1 to 10
                    if( 0==(s:=lockArray(table,record)) )
                        return .t.
                    end
                    _sleep()
                next
            end
           
            taberrOperation("tabRecLock")
            taberrDescription(@"record lock failed")
           
            if( valtype(userblock)=="B" )
                taberrUserblock(userblock)
                return tabError(table)
            else
                taberrUserblock("PUK")
                tabError(table)
            end
        end
    end    
    return .f.


*****************************************************************************
static function lockCurrent(table,timeout)  //Lock Current Record
local status, pos:=tabPosition(table)

    if( pos<=0 )
        status:=-1

    elseif( tranIsActiveTransaction() )
        return lockPosition(table,pos,timeout) 
    
    else
        dbunlocklist(table)
        status:=dblock(table,pos,timeout)

        if( status==0 )
            tabReRead(table,pos)
            table[TAB_LOCKLST]:={pos}
        end
    end
    return status  //szam, 0==OK


*****************************************************************************
static function lockPosition(table,pos,timeout)  //Lock Record by Position
local status

    if( pos<0 )  //pos==0==EOF-ot meg lehet lockolni, de negativot nem
        status:=-1 

    elseif( ascan(table[TAB_LOCKLST],pos)!=0 )  //mar lockolva volt, OK
        status:=0

    else  //most lockoljuk       

        if( (status:=dblock(table,pos,timeout) )==0 )
            aadd(table[TAB_LOCKLST],pos)
            if( tranIsActiveTransaction() )
                tranRecordLockedInTransaction(table)
            end
            
            if( 0<pos .and. pos==tabPosition(table) )
                tabReRead(table,pos)
            end
        end
    end
    return status  //szam, 0==OK


*****************************************************************************
static function lockArray(table,arr,timeout)  //Lock Record Array

local status:=0,n,i
local pos,larr:=len(arr)
local curr:=tabPosition(table)

    if( tranIsActiveTransaction() )
        for n:=1 to larr
            status:=lockPosition(table,arr[n],timeout)
            if( status!=0 )
                return status
            end
        next
        return status
    end
 

    dbunlocklist(table)

    for n:=1 to larr

        if( (pos:=arr[n])<=0 )
            status:=-1
        else
            status:=dblock(table,pos,timeout)
        end

        if( status==0 )
            aadd(table[TAB_LOCKLST],pos)
        else
            dbunlocklist(table)
            exit
        end
    next

    if( 0!=ascan(table[TAB_LOCKLST],curr) )
        tabReRead(table,curr) 
    end
    return status


*****************************************************************************
static function dblock(table,pos,timeout) //low level lock
local result
    tabLockCount(table,1)
    if( pos==NIL )
        pos:=tabPosition(table)
    end
    //result:=fsetlock(table[TAB_FHANDLE],pos,LK_OFFSET_RECORD,1)
    result:=ftimeoutlock(table[TAB_FHANDLE],pos,LK_OFFSET_RECORD,1,,timeout)
    if( result!=0 )
        tabLockCount(table,-1)
    end
    return result

*****************************************************************************
static function dbunlock(table,pos) //low level unlock
local result
    if( pos==NIL )
        pos:=tabPosition(table)
    end
    result:=funlock(table[TAB_FHANDLE],pos,LK_OFFSET_RECORD,1)
    if( result==0 )
        tabLockCount(table,-1)
    end
    return result
 

*****************************************************************************
static function dbunlocklist(table) //unlock records in locklist
local apos:=table[TAB_LOCKLST],n
    for n:=1 to len(apos)
        dbunlock(table,apos[n])
    next
    table[TAB_LOCKLST]:={}
    return NIL


*****************************************************************************
static function tabReRead(table) //rekord ujraolvasas
local len:=_db_read(table[TAB_BTREE],table[TAB_RECBUF],table[TAB_RECPOS])
    if( len!=table[TAB_RECLEN] )
        taberrOperation("tabReRead")
        taberrDescription(@"failed rereading record")
        tabError(table)
    end
    return NIL


*****************************************************************************
function tabUnlockAll(table)  //osszes table objektumra
local n, tlist:=tabObjectList()

    for n:=1 to len(tlist)
        table:=tlist[n]
        if( table[TAB_OPEN]>0 )
            tabUnlock(table)
        end
    next
    return NIL


*****************************************************************************
function tabUnlock(table,pos) //file es single/multiple rekord
local state

    tabCommit(table) 

    if( tranIsActiveTransaction() )
        //megtartjuk a lockokat

    elseif( tabIsOpen(table)>=OPEN_EXCLUSIVE )
        //ok
 
    elseif( pos==NIL ) // osszes rekordlock vagy fajllock 

        if( table[TAB_LOCKFIL] )
            //Az alabbi utasitas kell, hogy tabUnlock() 
            //es tabClose()  ne valhassanak rekurzivva.
            table[TAB_LOCKFIL]:=.f.

            state:=tabSave(table)
            tabOpen(table)  
            tabRestore(table,state)
        else
            dbunlocklist(table)            
        end

    elseif( 0==dbunlock(table,pos) ) // egy rekordlock 

        lockDelete(table,pos)
    end
    return NIL


*****************************************************************************
static function lockDelete(table,record) //lock kivetele locklist-bol
local n:=ascan(table[TAB_LOCKLST],record)
    if( n!=0 )
        adel(table[TAB_LOCKLST],n)
        asize(table[TAB_LOCKLST],len(table[TAB_LOCKLST])-1)
    end
    return NIL


*****************************************************************************
function tabIsLocked(table) //kereses locklist-ben
    return table[TAB_OPEN]==OPEN_EXCLUSIVE .or.;
           ascan(table[TAB_LOCKLST],tabPosition(table))>0
   

******************************************************************************
function tabLocklist(table)
   return table[TAB_LOCKLST]


******************************************************************************
function tabUnlockEOF(table) 

//A minden mas unlock funkcio tranzakcio kozben hatastalan,
//azonban EOF-ot tranzakcio alatt is el kell tudni engedni.

    if( 0==dbunlock(table,0) ) 
        lockDelete(table,0)
    end
    return NIL

 
*****************************************************************************
 

