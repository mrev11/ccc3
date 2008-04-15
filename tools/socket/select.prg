
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

//wrapper select_sckdesc vagy select_sckobj felé
//korábban  select_sckdesc == select volt.

******************************************************************************
function select(rd,wr,ex,wt)
local x

    if( len(rd)>0 )
        x:=rd[1]
    elseif( len(wr)>0 )
        x:=wr[1]
    elseif( len(ex)>0 )
        x:=ex[1]
    else
        return select_sckdesc(rd,wr,ex,wt)
    end

    if( valtype(x)=="N" )
        return select_sckdesc(rd,wr,ex,wt)
    else
        return select_sckobj(rd,wr,ex,wt)
    end

******************************************************************************
    