
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


#define PRIME          1103
#define KEYNAME(t,o)   lower(tabPathName(t)+alltrim(str(o)))

******************************************************************************
#ifdef TABCOPYBT_NOTOPTIMIZED

function tabCopybt(table)

local btname,tfile 
local fd,db,ps,pn
local n,i,rb,recbuf
local msg,total,cnt:=0 

    btname:=lower(tabPathName(table))

    fd:=fopen(btname,FO_READWRITE+FO_EXCLUSIVE)
    if( fd<0 )
        taberrOperation("tabCopybt")
        taberrDescription(@"failed opening file (fd)")
        tabError(table) 
    end

    db:=_db_open(fd)
    if( db==NIL )
        taberrOperation("tabCopybt")
        taberrDescription(@"failed opening file (db)")
        tabError(table) 
    end

    ps:=_db_pagesize(db)
    pn:=fseek(fd,0,FS_END)/ps
    total:="/"+alltrim(str(_db_lastrec(db)))

    tfile:=tabFile(table) 
    tabFile(table,TMPCHR+tfile)
    tabCreate(table)
    tabOpen(table,OPEN_EXCLUSIVE)
    tabZap(table)
    
    //A rekordok sorrendje eltérhet a felvitel időrendi sorrendjétől,
    //ui. a page-ek növekvő sorrendjében haladunk, ami a szabadlista miatt
    //nem feltétlenül lineáris. Nem akarom azonban, hogy a recovery
    //sikere függjön a recno index épségétől, és nem akarok a data
    //page-ek listába fűzésével sem vesződni.

    recbuf:=replicate(x"20",ps) //ebbe biztosan belefér

    for n:=2 to pn-1  //header(0) és resource(1) kihagyva
        i:=0
        while( .t. )
            rb:=_db_read1(db,recbuf,n,i++) 

            if( rb==0 )
                //nincs több rekord, vagy nem is datapage 
                exit 

            elseif( left(recbuf,1)=="*" )
                //törölt rekord

            elseif( rb==table[TAB_RECLEN] )
                tabAppend(table)
                table[TAB_RECBUF]:=left(recbuf,rb)
                tabCommit(table)
                if( ++cnt%1103==0 )
                    msg:=message(msg,@"Pack "+tfile+str(cnt)+total)
                end
            end
        end
    next

    if( msg!=NIL )
        message(msg)
    end
    
    _db_close(db)
    tabClose(table)
    
    ferase(btname)
    frename(lower(tabPathName(table)),btname)
    tabFile(table,tfile) //visszaállít
 
    return .t.
 

******************************************************************************
#else //OPTIMIZED aktuális változat, a kulcsokat rendezi

#define ORDERBY_RECNO     //megtartja a rekordok eredeti sorrendjét
//#define ORDERBY_PAGE      //elveszhet a rekordok eredeti sorrendje
 
//2002.12.18 memók packolása (opcionális)
#define MEMOPACK  //packolja-e a memókat?
 
function tabCopybt(table)

local btname,btxname,tfile 
local fd,db,db1,mh,mh1,ps,pn
local n,i,rb,wb,stat
local msg,total,cnt:=0 
local recno:=0,recbuf,reclen,recpos
local fdkey:={},kfilnam 
local ord,key
local column,memblk,mx,mv

    //-----------------------
    //régi adatfilé
    //-----------------------
 
    btname:=lower(tabPathName(table))
    btxname:=lower(tabMemoName(table))
 
    fd:=fopen(btname,FO_READWRITE+FO_EXCLUSIVE)
    if( fd<0 )
        taberrOperation("tabCopybt")
        taberrDescription(@"failed opening file (fd)")
        tabError(table) 
    end

    db:=_db_open(fd)
    if( db==NIL )
        taberrOperation("tabCopybt")
        taberrDescription(@"failed opening file (db)")
        tabError(table) 
    end

    #ifdef MEMOPACK
    if( 0<tabMemoCount(table) )
        mh:=memoOpen(btxname)
        if( mh<0 )
            taberrOperation("tabCopybt")
            taberrDescription(@"failed opening file (mh)")
            tabError(table) 
        end
    end
    #endif
 
    //-----------------------
    //új adatfilé
    //-----------------------
 
    tfile:=tabFile(table) 
    tabFile(table,TMPCHR+tfile)
    ferase(lower(tabPathName(table)))
    tabCreate(table)
    tabOpen(table,OPEN_EXCLUSIVE)
    tabZap(table)
    db1:=table[TAB_BTREE]
    
    #ifdef MEMOPACK
    if( 0<tabMemoCount(table) )
        mh1:=tabMemoHandle(table)

        memblk:={}
        column:=tabColumn(table)
        for n:=1 to len(column)
            if( tabMemoField(table,column[n]) )
                aadd(memblk,column[n][COL_BLOCK])
            end
        next
    end
    #endif
 
    //-----------------------
    //ideiglenes kulcsfilék
    //-----------------------
 
    for ord:=0 to len(tabIndex(table)) 
        ferase(kfilnam:=KEYNAME(table,ord))
        //aadd(fdkey,fcreate(kfilnam,FO_READWRITE+FO_SHARED))
        aadd(fdkey,fopen(kfilnam,FO_CREATE+FO_TRUNCATE+FO_READWRITE+FO_NOLOCK))
        if( atail(fdkey)<0 )
            taberrOperation("tabCopybt")
            taberrDescription(@"failed creating file (fdkey)")
            tabError(table) 
        end
    next
 
    total:="/"+alltrim(str(_db_lastrec(db)))
    reclen:=table[TAB_RECLEN] 
    recbuf:=table[TAB_RECBUF]  

#ifdef ORDERBY_PAGE
    //Ha tabAppend használja a szabadlistát, akkor a pack utáni
    //rekordsorrend eltérhet a felvitel időrendi sorrendjétől.

    ps:=_db_pagesize(db)
    pn:=fseek(fd,0,FS_END)/ps

    for n:=2 to pn-1  //header(0) és resource(1) kihagyva
        i:=0
        while( .t. )
            rb:=_db_read1(db,recbuf,n,i++) 

            if( rb==0 )
                //nincs több rekord, vagy nem datapage 
                exit 

            elseif( rb!=reclen )
#endif

#ifdef ORDERBY_RECNO

    //Csak akkor működik, ha épségben van a recno index,
    //lassabb is, viszont megtartja a rekordok eredeti sorrendjét.
    //Ez szükséges ahhoz, hogy a tabPack replikálható legyen.

        _db_setord(db,"recno")
        key:=_db_first(db) 

        while( key!=NIL )
            //? _db_rdbig32(left(key,4)) //eredeti recno
            recpos:=right(key,6)  
            rb:=_db_read(db,recbuf,recpos)

            if( rb!=reclen )
#endif

                //sérült filé
                taberrOperation("tabCopybt")
                taberrDescription(@"read failed (rb!=reclen)")
                tabError(table) 

            elseif( left(recbuf,1)==a"*" )
                //törölt rekord
 
            else

                if( ++cnt%PRIME==0 )
                    msg:=message(msg,@"COPY "+btname+str(cnt)+total)
                end

                #ifdef MEMOPACK
                if( memblk!=NIL )
                    set signal block
                    table[TAB_EOF]:=.f.           //EOF törölve
                    for mx:=1 to len(memblk)
                        table[TAB_MEMOHND]:=mh    //régi memó
                        mv:=eval(memblk[mx])      //olvasás a memóból
                        table[TAB_MEMOHND]:=mh1   //új memó
                        eval(memblk[mx],mv)       //írás a memóba
                    next
                    table[TAB_MODIF]:=.f.         //commit törölve
                    table[TAB_MEMODEL]:=NIL       //memodel törölve
                    set signal unblock  
                end
                #endif                

                table[TAB_RECPOS]    :=  _db_append(db1,recbuf) 
                table[TAB_POSITION]  :=  ++recno
 
                for ord:=0 to len(tabIndex(table))
                    key:=tabKeyCompose(table,ord)
                    fwrite(fdkey[1+ord],key)
                next
            end

#ifdef ORDERBY_RECNO
            key:=_db_next(db)  
#endif
        end

#ifdef ORDERBY_PAGE
    next
#endif

    for ord:=0 to len(tabIndex(table)) 
        if( recno>0 ) //2002.11.13
            build_index(table,ord,fdkey[1+ord],msg,btname) 
        end
        fclose(fdkey[1+ord])
        ferase(KEYNAME(table,ord))
    next

    if( msg!=NIL )
        message(msg)
    end
    
    _db_close(db)
    if( mh!=NIL .and. mh>=0 )
        memoClose(mh)
    end
    tabClose(table)
    
    set signal block
    ferase(btname);  frename(lower(tabPathName(table)),btname) 
    #ifdef MEMOPACK
      ferase(btxname); frename(lower(tabMemoName(table)),btxname)
    #else
      ferase(lower(tabMemoName(table))) 
    #endif
    set signal unblock
 
    tabFile(table,tfile)
 
    return .t.

 
******************************************************************************
static function build_index(table,ord,fd,msg,btname)

local keyval,keynam,keylen
local db1:=table[TAB_BTREE]
local rcount:=table[TAB_POSITION] 
local n,rb,stat

    if( ord==0 )
        keynam:="recno"
    else
        keynam:=tabIndex(table)[ord][IND_NAME] 
    end

    if( 0>_db_setord(db1,keynam) )
        taberrOperation("tabCopybt")
        taberrDescription(@"no index (_db_setord<0)")
        taberrArgs({keynam})
        tabError(table) 
    end
    
    keylen:=tabKeyLength(table,ord)  
    keyval:=replicate(x"00",keylen)

    if( ord>0 )
        __bt_sortkey(KEYNAME(table,ord),rcount,keylen)
    end                   

    fseek(fd,0,FS_SET)
    for n:=1 to rcount
    
        if( n%PRIME==0 .and. msg!=NIL )
            message(msg,@"COPY "+btname+" ("+keynam+")"+str(n))
        end

        rb:=fread(fd,@keyval,keylen)

        if( rb!=keylen )
            taberrOperation("tabCopybt")
            taberrDescription(@"read failed (rb!=keylen)")
            taberrArgs({keynam,ferror()})
            tabError(table) 
        end

        stat:=_db_put(db1,keyval)
        if( stat!=0 )
            taberrOperation("tabCopybt")
            taberrDescription(@"failed building index (_db_put!=0)")
            taberrArgs({keynam,stat})
            tabError(table) 
        end
    next
    
    return NIL

******************************************************************************
#endif 
