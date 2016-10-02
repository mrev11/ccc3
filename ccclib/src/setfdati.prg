
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

*****************************************************************************
function setfdati(fspec,da,ti)  //CA-tools

local modtime

    if( da==NIL )
        da:=date()
    end

    if( ti==NIL )
        ti:=time()
    elseif( !timevalid(ti) )
        return .f.
    end
 
#ifdef _UNIX_
    modtime:=dati2ostime(da,ti)
#else    
    modtime:=__localtimetofiletime(da,ti)    // local time
#endif    

    if( modtime==NIL )
        return .f.
    end
 
    return setfiletime(fspec,NIL,NIL,modtime) //cre,acc,mod


*****************************************************************************

