
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
function _zedit_mright(this)

    if( !this:markflg )
        this:markflg:=.t.
        this:markrow:=this:actrow
        this:markcol:=this:actcol
    end

    this:moveright()
    if( this:markmode=="RECT" )
        this:display()
    else
        this:displine()
    end

***************************************************************************
function _zedit_mleft(this)
    this:moveleft()
    if( this:markmode=="RECT" )
        this:display()
    else
        this:displine()
    end

***************************************************************************
function _zedit_mend(this)

    if( !this:markflg )
        this:markflg:=.t.
        this:markrow:=this:actrow
        this:markcol:=this:actcol
    end

    this:end()
    if( this:markmode=="RECT" )
        this:display()
    else
        this:displine()
    end

***************************************************************************
function _zedit_mhome(this)
    this:home()
    if( this:markmode=="RECT" )
        this:display()
    else
        this:displine()
    end

***************************************************************************
function _zedit_mdown(this)

    if( !this:markflg )
        this:markflg:=.t.
        this:markrow:=this:actrow
        this:markcol:=this:actcol
    end

    this:down()
    if( this:actrow>1 )
        this:displine(this:actrow-1)
    end
    this:displine()

***************************************************************************
function _zedit_mup(this)
     this:up() 
     if( this:actrow<len(this:atxt) )
         this:displine(this:actrow+1)
     end
     this:displine()

***************************************************************************
function _zedit_mpagedn(this)

    if( !this:markflg )
        this:markflg:=.t.
        this:markrow:=this:actrow
        this:markcol:=this:actcol
    end

    this:pagedown()
    this:display()

***************************************************************************
function _zedit_mpageup(this)
    this:pageup
    this:display()

***************************************************************************
