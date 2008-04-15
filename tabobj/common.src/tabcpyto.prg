
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

//TARTALOM  : copy to
//STATUS    : közös
//
//function tabCopyTo(table,fileName,fieldList)


#include "fileio.ch"
#include "tabobj.ch"

#define  CRLF   crlf()

******************************************************************************
function tabCopyTo(table,fileName,fieldList)

local state:=tabSave(table)
local hnd:=fcreate(fileName)
local count:=0,line,toklist
local flist:={},n,type,value
local err, msg

    if( hnd<0 )

        taberrOperation("tabCopyTo")
        taberrDescription(@"create failed")
        taberrArgs({fileName})
        tabError(table)
    end

    if( empty(fieldList) )
        flist:=tabColumn(table)
    else
        for n:=1 to len(fieldList)
            aadd(flist,tabGetColumn(table,fieldList[n]))
        next
    end
    
    msg:=message(msg,@"Exported:"+str(count))
    
    tabGotop(table)
    while( !tabEof(table) ) 
        count++
        line:=""
        msg:=message(msg,@"Exported:"+str(count))
    
        for n:=1 to len(flist)

            value:=eval(flist[n][COL_BLOCK]) //adatbázismező kiolvasása
            
            if( (type:=flist[n][COL_TYPE])=="C" )
                if( !tabMemoField(table,flist[n]) )
                    line+='"'+trim(value)+'"'
                else
                    line+='"'+trim(bin2str(value))+'"'
                end

            elseif( (type:=flist[n][COL_TYPE])=="X" )
                line+='"'+trim(bin2str(value))+'"'

            elseif( type=="N" )
                line+=alltrim(str(value,flist[n][COL_WIDTH],flist[n][COL_DEC]))

            elseif( type=="D" )
                line+=alltrim(dtos(value))

            elseif( type=="L" )
                line+=if(value,"T","F")

            end

            if( n<len(flist) )
                line+=","
            end
        end
        fwrite(hnd,line+CRLF)
        tabSkip(table)
    end
    fwrite(hnd,chr(26)) //EOF
    fclose(hnd)

    message(msg)
    tabRestore(table,state)
    return count

******************************************************************************
