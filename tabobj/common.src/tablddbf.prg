
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

//TARTALOM  : DBF betöltése DBM memóval együtt
//STATUS    : közös
//
//function tabLoadDBF(tab,dbf)


#include "fileio.ch"
#include "tabobj.ch"

//#define DEBUG

#ifndef DEBUG
#command ?  [ <list,...> ]      => 
#command ?? [ <list,...> ]      => 
#endif


*************************************************************************
function tabLoadDBF(tab,dbf)

local hnd,hnd1,dbm
local buffer:=replicate(x"20",32)
local hdrlen,reclen,reccnt,fldcnt
local name,type,length,dec
local konvtab:={},c,blk
local n,i,l,offs:=2 //első byte=deleted flag
local msg,msgtotal,msgdbnam

    tranNotAllowedInTransaction(tab,"loaddbf")

    tabCommit(tab)

    //az exkluzív open megkövetelése megakadályozza,
    //hogy a dbf alapú rendszerekben egy táblába önmagát
    //importáljuk (!)

    if( tabIsopen(tab)<OPEN_EXCLUSIVE )
        taberrOperation("tabLoadDBF")
        taberrDescription(@"exclusive open requiered")
        tabError(tab) 
    end
    
    dbf:=lower(alltrim(dbf))
    
    if( right(dbf,4)==".dbf" )
        dbm:=left(dbf,len(dbf)-4)+".dbm"
    else
        dbm:=dbf+".dbm"
        dbf:=dbf+".dbm"
    end
    
    //dbf: filename.dbf
    //dbm: filename.dbm
    
    hnd:=fopen(dbf,FO_READ)
    hnd1:=memoOpen(dbm,FO_READ)  //nem feltétlenül létezik

    if( hnd<0 )
        taberrOperation("tabLoadDBF")
        taberrDescription(@"DBF open failed")
        taberrFilename(dbf)
        tabError(tab)
    end

    if( 32>fread(hnd,@buffer,32) )
        taberrOperation("tabLoadDBF")
        taberrDescription(@"DBF invalid header")
        taberrFilename(dbf)
        tabError(tab)
    end

    reccnt:=xvgetlit32(buffer,4,0)  
    hdrlen:=xvgetlit16(buffer,8,0)  
    reclen:=xvgetlit16(buffer,10,0) 
    fldcnt:=(hdrlen-32-(hdrlen%32))/32

    ? @"record count  :", reccnt
    ? @"header length :", hdrlen
    ? @"record length :", reclen
    ? @"field count   :", fldcnt 
    
    for n:=1 to fldcnt

        if( 32!=fread(hnd,@buffer,32) )
            taberrOperation("tabLoadDBF")
            taberrDescription(@"DBF read error in header")
            taberrFilename(dbf)
            tabError(tab)
        end
        
        l:=at(chr(0),buffer)-1
        
        name   := bin2str(padr(substr(buffer,1,l),10))
        type   := bin2str(substr(buffer,12,1))
        length := asc(substr(buffer,17,1))
        dec    := asc(substr(buffer,18,1))
        
        ? name,type,offs,length,dec
        
        if( type=="C" )
            length+=256*dec
            blk:=blkchar(offs,length)

            if( left(name,3)=="DBM" .and. length==10 )
                if( hnd1>=0 )
                    blk:=blkmemo(offs,hnd1) //memó field
                else
                    //nincs meg a memófilé
                    blk:={||a""}
                end
            end

        elseif( type=="N" )
            blk:=blknumber(offs,length)

        elseif( type=="D" )
            blk:=blkdate(offs,length)

        elseif( type=="L" )
            blk:=blkflag(offs,length)

        else
            blk:={||NIL}
        end

        i:=ascan(tabColumn(tab),{|x|alltrim(x[COL_NAME])==alltrim(name)})

        if( i==0 ) 
            //nincs meg a mező

        elseif( type!=tabColumn(tab)[i][COL_TYPE] ) 
            //eltér a típusa
            taberrOperation("tabLoadDBF")
            taberrDescription(@"same field name with different type")
            taberrArgs(name)
            tabError(tab)

        else
            //konvertáljuk
            aadd(konvtab,{blk,tabColumn(tab)[i][COL_BLOCK]})
        end

        offs+=length
    next

    if( offs-1!=reclen )
        taberrOperation("tabLoadDBF")
        taberrDescription(@"DBF invalid format")
        taberrFilename(dbf)
        tabError(tab)
    end

    n:=0
    msgtotal:="/"+alltrim(str(reccnt))
    msgdbnam:=dbf+" (loaded/all)"
    msg:=message(msg,msgdbnam+str(n)+msgtotal)

    buffer:=xvalloc(reclen)
    fseek(hnd,hdrlen,FS_SET) 

    while( reclen==xvread(hnd,buffer,0,reclen) )

        if( 0==(++n%20) )
            message(msg,msgdbnam+str(n)+msgtotal)
        end
        
        if( !left(buffer,1)==a"*" )  //nem  törölt

            tabAppend(tab)

            for c:=1 to len(konvtab)
                eval(konvtab[c][2],eval(konvtab[c][1],buffer))
            next
        end
    end
    message(msg,msgdbnam+str(n)+msgtotal)

    tabCommit(tab)
    
    fclose(hnd)
    if( hnd1>=0 )
        memoClose(hnd1)
    end
    xvfree(buffer)
    ? @"Records loaded:",n

    sleep(500)
    msg:=message(msg)
    return n //rekordszám


*************************************************************************
/*
function tabDumpWorkArea(tab)
local i

    ? len(tab[TAB_RECBUF]), tabPosition(tab)
    ?
            
    for i:=1 to len(tab[TAB_RECBUF])
         ?? str(asc(substr(tab[TAB_RECBUF],i,1)),4,0)
    next
    inkey(0)

    return NIL
*/

*************************************************************************
static function blkchar(offs,length)
    return {|r|xvgetchar(r,offs-1,length)}

static function blknumber(offs,length)
    return {|r|val(xvgetchar(r,offs-1,length))}
    
static function blkdate(offs,length)
    return {|r|stod(xvgetchar(r,offs-1,length))}

static function blkflag(offs,length)
    return {|r|a"T"==xvgetchar(r,offs-1,1)}

static function blkmemo(offs,h)
    return {|r,m|m:=xvgetchar(r,offs-1,10),if(empty(m),a"",memoGetValue(h,val(m)))}


*************************************************************************
