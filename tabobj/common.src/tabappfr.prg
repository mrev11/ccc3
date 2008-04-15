
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

//TARTALOM  : append from (delimited)
//STATUS    : közös
//
//function tabAppendFrom(table,fileName,fieldList)


#include "fileio.ch"
#include "tabobj.ch"

#define CRLF   crlf()

******************************************************************************
function tabAppendFrom(table,fileName,fieldList)

local hnd, buffer:=""
local count:=0,line,toklist
local flist:={},n,type,value
local err, msg

    tranNotAllowedInTransaction(table,"appendfrom")

    hnd:=fopen(fileName,FO_READ+FO_SHARED)

    if( hnd<0 )
        taberrOperation("tabAppendFrom")
        taberrDescription(@"open failed")
        taberrFilename(fileName)
        tabError(table)
    end

    if( empty(fieldList) )
        flist:=tabColumn(table)
    else
        for n:=1 to len(fieldList)
            aadd(flist,tabGetColumn(table,fieldList[n]))
        next
    end
    
    msg:=message(msg,@"Imported:"+str(count))

    while( len(line:=getLine(hnd,@buffer))>1 ) // CR/LF mindig van benne
        
        if( len(toklist:=parse(line))!=len(flist) )
        
            taberrOperation("tabAppendFrom")
            taberrDescription(@"different number of fields")
            taberrArgs(fieldList)
            tabError(table)

        else
            count++
            tabAppend(table)
            msg:=message(msg,@"Imported:"+str(count))
    
            for n:=1 to len(flist)

                if( (type:=flist[n][COL_TYPE])=="C" )
                    value:=toklist[n]

                elseif( type=="N" )
                    value:=val(toklist[n])

                elseif( type=="D" )
                    if( empty(toklist[n]) )
                        value:=ctod("")
                    else
                        value:=stod(toklist[n])
                    end

                elseif( type=="L" )
                    value:=toklist[n]$"YyTt"

                elseif( type=="M" )
                    value:=toklist[n]

                end

                eval(flist[n][COL_BLOCK],value) //írás az adatbázismezőbe
            end
            tabUnlock(table)
        end
    end
    fclose(hnd)
    tabUnlock(table)

    message(msg)
    return count


******************************************************************************
static function parse(line)
local toklist:={}, s,t,c
    line:=strtran(line,CRLF,"")+","
    while(.t.)
        if( left(line,1)=='"' )
            s:=2
          //t:=at('",',line) //nem jól kezeli a "," mezőket!! 1997.09.22
            t:=at('",',substr(line,2))+1
            c:=t+2
        else
            s:=1
            t:=at(',',line)
            c:=t+1
        end
        
        if( t>=s )
            aadd(toklist,substr(line,s,t-s))
            line:=substr(line,c)
        else
            exit
        end
    end
    return toklist


******************************************************************************
#define BUFSIZE  256

static function getLine(hnd,pBuffer)

local line, buffer
local count, lfpos
local readok:=.t.

    while( 0==(lfpos:=at(chr(10),pBuffer)) .and. readok )

        buffer:=replicate(x"20",BUFSIZE)

        if( (count:=fread(hnd,@buffer,BUFSIZE)) < BUFSIZE )
            pBuffer+=left(buffer,count)
            readok:=.f.
        else
            pBuffer+=buffer
        end
    end
    
    if( lfpos>0 )
        line:=left(pBuffer,lfpos)
        pBuffer:=substr(pBuffer,lfpos+1)
    else
        line:=pBuffer
        pBuffer:=""
    end
    return line 


******************************************************************************
