
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
function _zedit_displine(this,x)

local actrow:=this:actrow
local actcol:=this:actcol
local markrow:=this:markrow
local markcol:=this:markcol

    if( x==NIL )
        x:=actrow
    elseif( x>len(this:atxt) )
        return NIL
    end

    //csak előrefelé lehet kijelölni

    if( !this:markflg .or. x<markrow .or. actrow<x )
        disp(this,x,1)
    
    elseif( markrow<x .and. x<actrow )

        if( this:markmode=="CONT" )
            disp(this,x,1,,.t.)
        elseif( this:markmode=="RECT" )
            disp(this,x,1,markcol-1)
            disp(this,x,markcol,actcol-1,.t.)
            disp(this,x,actcol)
        end
        
    elseif( x==markrow )

        if( this:markmode=="CONT" )
            disp(this,x,1,markcol-1)
            if( x==actrow )
                disp(this,x,markcol,actcol-1,.t.)
                disp(this,x,actcol)
            else
                disp(this,x,markcol,,.t.)
            end
        elseif( this:markmode=="RECT" )
            disp(this,x,1,markcol-1)
            disp(this,x,markcol,actcol-1,.t.)
            disp(this,x,actcol,NIL)
        end
        
    elseif( x==actrow )  //markrow<actrow

        if( this:markmode=="CONT" )
            disp(this,x,1,actcol-1,.t.)
            disp(this,x,actcol)
        elseif( this:markmode=="RECT" )
            disp(this,x,1,markcol-1)
            disp(this,x,markcol,actcol-1,.t.)
            disp(this,x,actcol)
        end
    end
    

***************************************************************************   
static function disp(this,x,tbeg,tend,color)

local line,pos
local text:=this:atxt[x]
local markcolor:=zcolor_2()
local ws:=this:sftcol
local ww:=this:width
local twid

    line:=this:top+x-this:sftrow-1

    if( tend==NIL )
        twid:=ws+ww
    else
        twid:=tend-tbeg+1
    end

    if( ws+ww<tbeg  .or. tbeg+twid<ws )
        return NIL
    end

    pos:=tbeg-ws-1

    if( pos<0 )
        tbeg-=pos
        twid+=pos
        pos:=0
    end
    
    twid:=min(twid,ww-pos)
    pos+=this:left
    
    if( !empty(color) )
        @ line,pos SAY padr(substr(text,tbeg,twid),twid) COLOR markcolor
    else
        @ line,pos SAY padr(substr(text,tbeg,twid),twid)
    end


***************************************************************************   


