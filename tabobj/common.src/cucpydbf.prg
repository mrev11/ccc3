
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

//TARTALOM  : DBF atmasolasa toroltek kihagyasaval
//STATUS    : kozos utility
//
//function copydbf(dbfsrc,dbfdest)

#include "fileio.ch"

//#define DEBUG

#ifndef DEBUG
#command ?  [ <list,...> ]      => 
#command ?? [ <list,...> ]      => 
#endif


*************************************************************************
function copydbf(db1,db2)

local hnd1,hnd2
local buffer, header, buf4
local hdrlen,reclen,reccnt,fldcnt
local name,type,length,dec
local n,l,offs:=2 //elso byte=deleted flag
local msg,msgtotal,msgdbnam

    hnd1:=fopen(db1,FO_READ+FO_EXCLUSIVE)
    if( hnd1<0 )
        taberrOperation("copydbf")
        taberrDescription(@"DBF open failed")
        taberrFilename(db1)
        tabError()
    end

    hnd2:=fcreate(db2)
    if( hnd2<0 )
        taberrOperation("copydbf")
        taberrDescription(@"DBF create failed")
        taberrFilename(db2)
        tabError()
    end

    buffer:=replicate(x"20",32) 

    if( 32>fread(hnd1,@buffer,32) )
        taberrOperation("copydbf")
        taberrDescription(@"DBF read error in header")
        taberrFilename(db1)
        tabError()
    end
    if( 32!=fwrite(hnd2,buffer) )
        taberrOperation("copydbf")
        taberrDescription(@"DBF write error in header")
        taberrFilename(db2)
        tabError()
    end

    reccnt:=xvgetlit32(buffer,4,0)  
    hdrlen:=xvgetlit16(buffer,8,0)  
    reclen:=xvgetlit16(buffer,10,0) 
    fldcnt:=(hdrlen-32-(hdrlen%32))/32

    ? @"rekordszam   :", reccnt
    ? @"fejlec hossz :", hdrlen
    ? @"rekord hossz :", reclen
    ? @"mezok szama  :", fldcnt 
    
    header:=replicate(x"20",hdrlen-32)

    if( hdrlen-32>fread(hnd1,@header,hdrlen-32) )
        taberrOperation("copydbf")
        taberrDescription(@"DBF read error in header")
        taberrFilename(db1)
        tabError()
    end

    if( hdrlen-32!=fwrite(hnd2,header) )
        taberrOperation("copydbf")
        taberrDescription(@"DBF write error in header")
        taberrFilename(db2)
        tabError()
    end
    
    for n:=1 to fldcnt
   
        buffer:=substr(header,(n-1)*32+1,32)
        
        l:=at(chr(0),buffer)-1
        
        name   := padr(substr(buffer,1,l),10)
        type   := substr(buffer,12,1)
        length := asc(substr(buffer,17,1))
        dec    := asc(substr(buffer,18,1))

        if( type=="C" )
            length+=256*dec
            dec:=0
        end
        
        ? name,type,offs,length,dec

        offs+=length
    next

    if( offs-1!=reclen )
        taberrOperation("copydbf")
        taberrDescription(@"DBF invalid format")
        taberrFilename(db1)
        tabError()
    end

    n:=0
    msgtotal:="/"+alltrim(str(reccnt))
    msgdbnam:="Pack  "+upper(db1)
    msg:=message(msg,msgdbnam+str(n)+msgtotal)
    buffer:=replicate(x"20",reclen)
    reccnt:=0

    while( reclen==fread(hnd1,@buffer,reclen) )

        if( 0==(++n%1000) )
            message(msg,msgdbnam+str(n)+msgtotal)
        end
        
        if( !left(buffer,1)=="*" ) //nem torolt
            if( fwrite(hnd2,buffer)!=reclen )
                taberrOperation("copydbf")
                taberrDescription(@"DBF write failed")
                taberrFilename(db2)
                tabError()
            end
            reccnt++
        end
    end
    
    fwrite(hnd2,chr(26)) //EOF=1A
    fseek(hnd2,4,FS_SET)
    xvputlit32(buf4:=replicate(x"20",4),0,reccnt)
    fwrite(hnd2,buf4) //fejlec: rekordszam

    message(msg,msgdbnam+str(n)+msgtotal)

    fclose(hnd1)
    fclose(hnd2)

    sleep(100)
    msg:=message(msg)
    return n //rekordszam


*************************************************************************
