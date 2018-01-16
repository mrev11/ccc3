
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

*************************************************************************
function dbBrowse(this,top,left,bottom,right,def) //menuzo browse

local browse:=brwCreate(top,left,bottom,right)
local n, col

    browse:skipBlock:={|n|skipBrowse(this,n)}
    browse:goTopBlock:={||_dbaseiii_gotop(this)}
    browse:goBottomBlock:={||_dbaseiii_gobottom(this)}
    browse:PercentBlock:={|p|_dbaseiii_percent(this,p)}

    if(def==.t.)
        for n:=1 to len(this:dbstruct)
            brwColumn(browse,this:dbstruct[n][1],this:fldblk[n])
        next
    end

    return browse
   

*************************************************************************
static function skipBrowse(this,stp) //skip browse-okhoz
local n:=0

    if( stp>0 )
        if( (n:=_dbaseiii_skip(this,stp))<stp )
            _dbaseiii_gobottom(this)
        end

    elseif( stp<0 )
        if( (n:=_dbaseiii_skip(this,stp))>stp )
            _dbaseiii_gotop(this)
        end
    end   

    return n


*************************************************************************
static function _dbaseiii_percent(this,p)

    if( p==NIL )
        if( this:reccnt>0 )
            p:=this:recno/this:reccnt*100
        else
            p:=100
        end

    else
        p:=min(p,100)
        p:=max(p,0)
        
        if( !this:goto( 1+p*this:reccnt/100 ) )
            this:gobottom()
        end
    end

    return p


*************************************************************************
 