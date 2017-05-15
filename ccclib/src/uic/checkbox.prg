
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
class radiobutton(get) 
    method initialize
    method left         {|this|this}
    method right        {|this|this}
    method home         {|this|this}
    method end          {|this|this}
    method toggle       {|this|toggle(this)}
    method insert       {|this|toggle(this)}
    method overstrike   {|this|toggle(this)}
    method delete       {|this|setfalse(this)}
    method backspace    {|this|setfalse(this)}
    method display      {|this|display(this,"(*)")}
    method varput
    method addto
    attrib group


****************************************************************************
static function radiobutton.initialize(this,r,c,b,v) 
    this:(get)initialize(r,c,b,v)
    this:varput(.f.)
    this:picture:="XXX"
    return this

****************************************************************************
static function radiobutton.varput(this,x)
local n,g
    eval(this:block,x)
    if( this:hasfocus .and. x .and. this:group!=NIL )
        for n:=1 to len(this:group)
            g:=this:group[n]::eval
            if( !g:hasfocus .and. g:varget )
                g:toggle
            end
        next
    end
    return x

****************************************************************************
static function radiobutton.addto(g,group)
    aadd(group,{||g})
    g:group:=group
    return NIL
    
****************************************************************************
class checkbox(get)  //compatibility
    method initialize
    method left         {|this|this}
    method right        {|this|this}
    method home         {|this|this}
    method end          {|this|this}
    method toggle       {|this|toggle(this)}
    method insert       {|this|toggle(this)}
    method overstrike   {|this|toggle(this)}
    method delete       {|this|setfalse(this)}
    method backspace    {|this|setfalse(this)}
    method display      {|this|display(this,"[X]")}

****************************************************************************
static function checkbox.initialize(this,r,c,b,v) 
    this:(get)initialize(r,c,b,v)
    this:picture:="XXX"
    this:varput(.f.)
    return this

****************************************************************************
static function display(this,c)

local l:=left(c,1)
local r:=right(c,1)
local flg:=if(this:varget,substr(c,2,1)," ")
local color_normal:=logcolor(this:colorspec,1)
local color_invers:=logcolor(this:colorspec,2)
local color_flag:=if(this:hasfocus,color_invers,color_normal)
    
    @ this:row,this:col   say l   color color_flag
    @ this:row,this:col+1 say flg color color_flag
    @ this:row,this:col+2 say r   color color_flag

    setpos(this:row,this:col+1)

    return NIL

****************************************************************************
static function toggle(this)
    if( this:varget )
        setfalse(this)
    else
        settrue(this)
    end
    return NIL

****************************************************************************
static function setfalse(this)
    this:varput( .f. )
    this:display
    return NIL

****************************************************************************
static function settrue(this)
    this:varput( .t. )
    this:display
    return NIL

****************************************************************************
    