
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

******************************************************************************
function scroll(top,lef,bot,rig,vert)
local buf

    if(top==NIL);top:=0;end
    if(lef==NIL);lef:=0;end
    if(bot==NIL);bot:=maxrow();end
    if(rig==NIL);rig:=maxcol();end
    
    if( vert==NIL .or. vert>bot-top .or. vert<top-bot )
        buf:=devoutbuffer(space((bot-top+1)*(rig-lef+1)))
        restscreen(top,lef,bot,rig,buf)
    elseif( vert==0 )
    elseif( vert>0 )
        buf:=savescreen(top+vert,lef,bot,rig)
        restscreen(top,lef,bot-vert,rig,buf)
        buf:=devoutbuffer(space(vert*(rig-lef+1)))
        restscreen(bot-vert+1,lef,bot,rig,buf)
    elseif( vert<0 )
        buf:=savescreen(top,lef,bot+vert,rig)
        restscreen(top-vert,lef,bot,rig,buf)
        buf:=devoutbuffer(space(-vert*(rig-lef+1)))
        restscreen(top,lef,top-vert-1,rig,buf)
    end
    return NIL

******************************************************************************
function inverserect(top,lef,bot,rig)
local buf:=savescreen(top,lef,bot,rig)
    buf:=screeninv(buf)
    restscreen(top,lef,bot,rig,buf)
    return NIL

******************************************************************************

