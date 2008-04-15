
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

***************************************************************************
function tempfile(cPath,cExt,nAttr) //CA-tools

local n:=0, fname, fspec, fd

    if( cPath==NIL )
        cPath:=""
    end

    if( empty(cExt) )
        cExt:=""
    elseif( !"."$cExt )
        cExt:="."+cExt
    end

    fname:=alltrim(str(getpid()))+"_"+alltrim(str(gettickcount()))+"_"
    
    while( .t. )
        fspec:=cPath+fname+alltrim(str(++n))+cExt
        if( !file(fspec) )
            exit  //OK, nincs ilyen
        end
    end
    
    if( 0<=(fd:=fcreate(fspec,nAttr)) ) 
        fclose(fd)
    else
        fspec:=""
    end
    
    return fspec

***************************************************************************
 