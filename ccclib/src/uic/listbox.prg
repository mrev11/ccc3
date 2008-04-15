
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

****************************************************************************
class listbox(get) 
    method initialize
    method choice       {|this|choice(this)}
    method insert       {|this|choice(this)}
    method overstrike   {|this|choice(this)}
    method delete       {|this|choice(this)}
    method backspace    {|this|choice(this)}
    method select       {|this,n|select(this,n)}
    method scan         {|this,k|scan(this,k)}
    method item         {|this,i|aadd(this:menu,i)}
    attrib selected
    attrib menu

****************************************************************************
function listboxIni(this,r,c,b,v) //compatibility
    return this:(listbox)initialize(r,c,b,v)

****************************************************************************
static function listbox.initialize(this,r,c,b,v) 
    this:(get)initialize(r,c,b,v)
    this:picture:=replicate("X",len(this:varget))
    this:selected:=0
    this:menu:={}
    return this

****************************************************************************
static function scan(this,key)
local n, w:=len(key)
    for n:=1 to len(this:menu)
        if( key==left(this:menu[n],w) )
            return n
        end
    next
    return 0
 
****************************************************************************
static function select(this,k)
    if( valtype(k)=="C" )
        k:=this:scan(k) 
    end
    if( 1<=k .and. k<=len(this:menu) )
        this:varput(this:menu[k])
    else
        this:varput("")
    end
    this:selected:=k
    this:reset
    return NIL

****************************************************************************
static function choice(this)
 
local color:=revcolor()
local t,l,b,r,s
local w:=0,n,ch
 
    for n:=1 to len(this:menu)
        w:=max(w,len(this:menu[n]))
    next

    t:=this:row+1 
    l:=this:col
    b:=t+min(16,len(this:menu)+1)
    r:=l+min(64,w+1)
    
    if( r>maxcol() )
        l-=r-maxcol()
        r:=maxcol()
        if( l<0 )
            l:=0
        end
    end
    
    if( b>maxrow() )
        if( maxrow()-t>5 )
            b:=maxrow()
        else
            s:=b-t+2
            t-=s
            b-=s
            if( t<0 )
                t:=0
            end
        end
    end

    ch:=choicebox(t,l,b,r,this:menu,,,this:selected)
    
    if( ch>0 )
        this:select(ch)
    end
    
    setcolor(color)
    return NIL

****************************************************************************
