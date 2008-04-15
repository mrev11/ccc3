
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
//jtbrowsearray (segédlet array-k browseolásához)
****************************************************************************
class jtbrowsearray(jttable) 
    method  initialize
    method  xmlname         {|this|"jttable"}
    attrib  _array_
    attrib  _arraypos_
    method  array           {|this,a|if(a==NIL,this:_array_,this:_array_:=a)}
    method  arraypos
    method  ablock
    method  addcolumn
    method  selectedrows
    method  currentrow

****************************************************************************
static function jtbrowsearray.initialize(this,t,l,b,r)  
    this:(jttable)initialize(t,l,b,r)
    this:skipblock:={|s,s0,s1|s0:=this:arraypos,s1:=this:arraypos(s0+s),s1-s0} 
    this:gotopblock:={||0<this:arraypos(1)}
    this:gobottomblock:={||0<this:arraypos(len(this:_array_))} 
    this:saveposblock:={||this:arraypos} 
    this:restposblock:={|p|0<this:arraypos(p)}
    return this


****************************************************************************
static function jtbrowsearray.arraypos(this,pos) 
    if( pos!=NIL )
        if( pos<1 ) 
            pos:=1
        end
        if( pos>len(this:_array_) )
            pos:=len(this:_array_) 
        end
        this:_arraypos_:=pos
    end
    return this:_arraypos_ 


****************************************************************************
static function jtbrowsearray.ablock(this,c) 
    return {|x|if( x==NIL,;
                   this:_array_[this:_arraypos_][c],; 
                   this:_array_[this:_arraypos_][c]:=x) }


****************************************************************************
static function jtbrowsearray.addcolumn(this,h,b,w,p) 
    if( valtype(b)=="N" )
        b:=this:ablock(b) 
    end
    return this:(jttable)addcolumn(h,b,w,p)   


****************************************************************************
static function jtbrowsearray.selectedrows(this)

local sx:=this:varget, x
local sr:=array(len(sx)), r:=0

    for x:=1 to len(sx)
        if( this:restpos(sx[x]) )
            sr[++r]:=this:array[this:arraypos]
        end
    next
    asize(sr,r)
    return sr
    

****************************************************************************
static function jtbrowsearray.currentrow(this)
local cr:=this:selectedrows
    if( len(cr)==1 )
        cr:=cr[1]
    else
        cr:=NIL
    end
    return cr


****************************************************************************
 
 
 
 