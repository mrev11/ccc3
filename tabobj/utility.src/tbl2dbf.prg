
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

#include "utility.ver"

#include "table.ch"
#include "fileio.ch"
 
******************************************************************************
function table2dbf(*)

local table
local dext:=lower(tabDataExt())
local appname:=substr(dext,2)+"2dbf"
local args:={*},n,ctrl,fname
local mode:=OPEN_EXCLUSIVE

    for n:=1 to len(args)
        if( args[n]=="-c"  )
            ctrl:=args[++n]
        elseif( args[n]=="-r" )
            mode:=OPEN_READONLY
        elseif( args[n]=="-f" )
            fname:=args[++n]
        elseif( n==len(args) )
            fname:=args[n]
        end
    next

    if( fname==NIL )
        ? appname+" "+VERSION+" (C) ComFirm 2001"
        ? @"Usage: "+appname+" [-c ctrl] [-f] fname"
        ?
        errorlevel(1)
        quit
    end

    if( !dext $ fname )
        fname+=dext
    end
    
    if( !file(fname) )
        ? fname, @"not found"
        ?
        errorlevel(1)
        quit
    end
    
    table:=open(fname,ctrl,mode)
    
    if( table==NIL )
        ? fname, @"not available"
        ?
        errorlevel(1)
        quit
    end

    createdbf(table) 

    return NIL


******************************************************************************
static function open(fname,ctrl:=0,mode)
local tab:=tabResource(fname)

    if( valtype(tab)!="A" .or.  empty(tab) )
        tab:=NIL 
    elseif( !tabOpen(tab,mode,{||.f.}) )
        tab:=NIL 
    else
        tabControl(tab,ctrl)
    end
    return tab


******************************************************************************
static function createdbf(table) 

local ext:=lower(tabDataExt())
local mem:=lower(tabMemoExt())
 
local datname:=lower(tabPathName(table))    //adatfile
local dbdname:=lower(tabMemoName(table))    //memofile  
local dbfname:=strtran(datname,ext,".dbf")  //DBF adatfile 
local dbmname:=strtran(datname,ext,".dbm")  //DBM memofile   
 
local err,msg 
local hnd,hnd1
local n,col,buffer 
local name,type,width,dec,blk
local hdrlen:=0,reclen:=1,lastrec:=0
local wblock:={} 
local total:="/"+alltrim(str(tabLastrec(table)))


    if( file(dbfname) )
        ferase(dbfname)
        if( file(dbfname) )
            err:=ioerrorNew()
            err:operation("createdbf")
            err:description(@"ferase failed (data)")
            break(err)
        else
            ?  @"deleted", dbfname
        end
    end

    if( file(dbmname) )
        ferase(dbmname)
        if( file(dbmname) )
            err:=ioerrorNew()
            err:operation("createdbf")
            err:description(@"ferase failed (memo)")
            break(err)
        else
            ? @"deleted", dbmname
        end
    end
 
    hnd:=fcreate(dbfname)
    if( hnd<0 )
        err:=ioerrorNew()
        err:operation("createdbf")
        err:description(@"fcreate failed")
        break(err)
    else
        ? @"created", dbfname
    end

    if( tabMemoCount(table)>0 )
        if( !memoCreate(dbmname) )
            err:=ioerrorNew()
            err:operation("createdbf")
            err:description(@"memoCreate failed")
            break(err)
        else
            ? @"created", dbmname
        end

        hnd1:=memoOpen(dbmname)

        if( hnd1<0 )
            err:=ioerrorNew()
            err:operation("createdbf")
            err:description(@"memoOpen failed")
            break(err)
        end
    end

    
    writeheader(hnd,hdrlen,reclen,lastrec) 

    for n:=1 to tabFcount(table)

        col    := tabColumn(table)[n]
        name   := col[COL_NAME]
        type   := col[COL_TYPE]
        width  := col[COL_WIDTH]
        dec    := col[COL_DEC]
        
        if( type=="X" )
            type:="C"
        end

        buffer := padr(alltrim(str2bin(name))+bin(0),11)
        buffer += str2bin(type)
        buffer += replicate(a" ",4)
        
        //? name,type,width,dec

        if( type=="C" )
            buffer += bin(width%256)
            buffer += bin((width-width%256)/256)
            
            if( !tabMemoField(table,col) )
                blk:=blkchar(reclen,width)
            else
                blk:=blkmemo(reclen,hnd1)
            end
            
        elseif( type=="N" )
            buffer += bin(width)
            buffer += bin(dec)
            blk:=blknumber(reclen,width,dec)
 
        elseif( type=="D" )
            buffer += bin(8)
            buffer += bin(0)
            blk:=blkdate(reclen)
 
        elseif( type=="L" )
            buffer += bin(1)
            buffer += bin(0)
            blk:=blkflag(reclen)
 
        else
            buffer += bin(0)
            buffer += bin(0)
            blk:=blkdummy()
        end

        buffer += replicate(a" ",14)
        if( 32!=fwrite(hnd,buffer,32)  )
            err:=writeerrorNew()
            err:operation("createdbf")
            err:description(@"fwrite failed")
            break(err)
        end
        
        aadd(wblock,blk)
        reclen+=width
    end

    if( 2!=fwrite(hnd,x"0d00",2)  )
        err:=writeerrorNew()
        err:operation("createdbf")
        err:description(@"fwrite failed")
        break(err)
    end
    
    msg:=message(msg,dbfname+@" created")

    tabGotop(table)
    while( !tabEof(table) )
    
        if(lastrec%19==0)
            msg:=message(msg,dbfname+str(lastrec)+total)
        end
 
        buffer:=replicate(a" ",reclen)
        for n:=1 to tabFcount(table)
             eval(wblock[n],buffer,tabEvalColumn(table,n))
        next

        if( reclen!=fwrite(hnd,buffer,reclen)  )
            err:=writeerrorNew()
            err:operation("createdbf")
            err:description(@"fwrite failed")
            break(err)
        end

        lastrec++
        tabSkip(table)
    end


    if( 1!=fwrite(hnd,bin(26),1)  )
        err:=writeerrorNew()
        err:operation("createdbf")
        err:description(@"fwrite failed")
        break(err)
    end
    
 
    hdrlen:=(tabFcount(table)+1)*32+2
    writeheader(hnd,hdrlen,reclen,lastrec) 

    fclose(hnd)
    if( hnd1!=NIL )
        fclose(hnd1)
    end

    msg:=message(msg)
    
    ? "Total number of records written to", dbfname+":", alltrim(str(lastrec))
    ?
    return NIL


******************************************************************************
static function writeheader(hnd,hdrlen,reclen,lastrec)

local err
local buf:=replicate(a" ",32)
local dat:=date()
    
    xvclear(buf)
    xvputbyte (buf, 0,3)                  //  DBF3                 1
    xvputbyte (buf, 1,year(dat)%100)      //  ev                   1
    xvputbyte (buf, 2,month(dat))         //  honap                1
    xvputbyte (buf, 3,day(dat))           //  nap                  1

    xvputlit32 (buf, 4,lastrec)           //  rekordok szama       4
    xvputlit16 (buf, 8,hdrlen)            //  fejlec hossza        2
    xvputlit16 (buf,10,reclen)            //  rekordok hossza      2
    
    fseek(hnd,0,FS_SET) 
    if( 32!=xvwrite(hnd,buf,32) )
        err:=writeerrorNew()
        err:operation:="writeheader"
        err:description:=@"xvwrite failed"
        break(err)
    end

    return NIL

******************************************************************************
static function blkchar(offs,length)
    return {|r,x|xvputchar(r,offs,length,str2bin(x))}

static function blkmemo(offs,hnd)
    return {|r,x|xvputchar(r,offs,10,str2bin(if(empty(x),space(10),str(memoAddValue(hnd,str2bin(x)),10,0))))}
 
static function blknumber(offs,length,dec)
    return {|r,x|xvputchar(r,offs,length,str2bin(str(x,length,dec)))}
    
static function blkdate(offs)
    return {|r,x|xvputchar(r,offs,8,str2bin(dtos(x)))}
 
static function blkflag(offs)
    return {|r,x|xvputchar(r,offs,1,if(x,a"T",a"F"))}

static function blkdummy()
    return {||NIL}

******************************************************************************

    