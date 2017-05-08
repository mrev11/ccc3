
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
    method insert       {|this,c|choice(this,c)}    // c-re keres
    method overstrike   {|this,c|choice(this,c)}    // c-re keres
    method delete       {|this|choice(this)}        // elfedi az editalasi funkciot
    method backspace    {|this|choice(this)}        // elfedi az editalasi funkciot
    method select       {|this,n|select(this,n)}
    method scan         {|this,k|scan(this,k)}
    method item         {|this,i|aadd(this:menu,i)}

    attrib selected
    attrib menu


****************************************************************************
static function listbox.initialize(this,r,c,b,v) 
    this:(get)initialize(r,c,b,v)
    this:picture:=replicate("X",len(this:varget)) //eredeti blokk
    this:selected:=0
    this:menu:={}

    // Blokk kicserelve:

    this:block:={|x|this:menu[this:select(x)]}

    // varget/varput a selected ertekevel dolgozik.
    // A belso mukodesben varget/varput-ot nem hasznaljuk,
    // igy a kliens program a block atirasaval tetszoleges
    // choidx <--> value lekepezest alkalmazhat.
    
    //a default blokkal
    //  varget a kivalasztott item teljes szoveget adja
    //  varput index vagy illeszkedo szoveg alapjan valaszt

    return this


****************************************************************************
static function scan(this,key)
local n, w:=len(key)
    for n:=1 to len(this:menu)
        if( this:menu[n]==key  )
            return n
        end
    next
    for n:=1 to len(this:menu)
        if( !(this:menu[n]!=key)  )
            return n
        end
    next
    return 0


****************************************************************************
static function select(this,key)
    if( key==NIL )
        //lekerdezes

    elseif( valtype(key)=="N" )
        this:selected:=key

    elseif( valtype(key)=="C" )
        key:=this:scan(key) 
        if( key>0 )
            this:selected:=key
        end
    end
    return this:selected


****************************************************************************
static function choice(this,ckey)
 
local color
local t,l,b,r,s
local w:=0,n,ch
local ncho

    for n:=1 to len(this:menu)
        w:=max(w,len(this:menu[n]))
    next

    for n:=1 to len(this:menu)
        if( this:menu[n][1]::lower==ckey )
            ncho:=n
            exit
        end
        //ckey az a karakter, ami kivaltotta a keresest
        //ha van ckey kezdetu item, akkor arra pozicionaljuk a keresest
        //ha nincs, akkor a selected-re pozicionalunk
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

    //a listboxhoz tartozo choicebox 
    //a get:colorspec forditottjaval mukodik
    color:=setcolor(this:colorspec::logcolor(2)+","+this:colorspec::logcolor(1))  
    ch:=choicebox(t,l,b,r,this:menu,,,if(empty(ncho),this:selected,ncho))
    setcolor(color)
    
    if( ch>0 )
        this:select(ch)
        this:reset
    end


****************************************************************************
