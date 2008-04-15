
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

******************************************************************************
function memoread(fspec,binopt)

//Elter a Clippertol, plusz parameter binopt:
//Ha binopt empty, akkor a beolvasott adatokat "C" string formaban adja.
//Ha binopt !empty, akkor a beolvasott adatokat "X" bytearray formaban adja.
//Tehat a return ertek tipusa "C" vagy "X" lehet.

local fd,len,buffer:=x""

    if( 0<=(fd:=fopen(fspec,FO_SHARED)) .and.;
        0<(len:=fseek(fd,0,FS_END)) .and.;
        len<__maxstrlen() )

        fseek(fd,0)
        buffer:=replicate(x"20",len)
        if( 0>fread(fd,@buffer,len) )
            buffer:=x"" //sikertelen az olvasas
        end
    end
    fclose(fd)
    if( empty(binopt) )
        buffer:=bin2str(buffer) //text file
    end
    return buffer

******************************************************************************
function memowrit(fspec,data)
local success:=.f.,fd,nbyte
    if( 0<=(fd:=fcreate(fspec)) )
        if( valtype(data)=="C" )
            data:=str2bin(data)
        end
        nbyte:=fwrite(fd,data)
        fclose(fd)
        if( nbyte==len(data) )
            success:=.t.
        end
    end
    return success

******************************************************************************
