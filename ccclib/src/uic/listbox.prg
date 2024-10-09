
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

#include "box.ch"
#include "inkey.ch"
#include "setcurs.ch"

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
    attrib changeblock

****************************************************************************
static function listbox.initialize(this,r,c,b,v) 
    this:(get)initialize(r,c,b,v)
    this:picture:=replicate("X",len(this:varget)) //eredeti blokk
    this:selected:=0
    this:menu:={}

    // Blokk kicserelve:

    this:block:={|x,s|s:=this:select(x),if(s>=1,this:menu[s],"")::padr(len(this:picture))}

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
local prev:=this:selected

    for n:=1 to len(this:menu)
        w:=max(w,len(this:menu[n]))
    next

    for n:=1 to len(this:menu)
        if( this:menu[n][1..1]::lower==ckey )
            ncho:=n
            exit
        end
        //ckey az a karakter, ami kivaltotta a keresest
        //ha van ckey kezdetu item, akkor arra pozicionaljuk a keresest
        //ha nincs, akkor a selected-re pozicionalunk
    next
    if( ncho==NIL )
        ckey:=""
        ncho:=prev
    end

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
    ch:=chbox(t,l,b,r,this:menu,ncho,ckey)
    setcolor(color)
    
    if( ch>0 )
        this:select(ch)
        if( prev!=this:selected .and. this:changeblock!=NIL )
            eval(this:changeblock,this)
        end
        this:reset
    end


****************************************************************************
static function chbox(top,left,bottom,right,menu,ini,ckey)
local posr:=row(), posc:=col()
local screen:=DrawBox(top,left,bottom,right,B_SINGLE)
local choice:=xchoice(top+1,left+1,bottom-1,right-1,menu,ini,ckey)
    restscreen(top,left,bottom,right,screen)
    setpos(posr,posc)
    return choice


****************************************************************************
static function xchoice(top,left,bottom,right,item,inich,pattern:="")

local crs:=setcursor(SC_NONE)
local choice:=inich
local toppos:=1
local leni:=len(item)
local height:=min(leni,bottom-top+1)
local key,pos

    if( height<1 ) //1998.12.06
        setcursor(crs)
        return choice:=0
    end

    bottom:=top+height-1
    
    if( valtype(choice)!="N" )
        choice:=1
    elseif( choice<1 )
        choice:=1
    elseif( choice>leni )
        choice:=leni
    end

    toppos::=top(leni,height,1,choice)
    chdraw(top,left,bottom,right,item,toppos,choice)
    
    while(.t.)
    
        key:=inkey(0)
        
        if( key==K_ESC  )
            choice:=0
            exit

        elseif( key==K_LEFT )
            choice:=0
            exit

        elseif( key==K_RIGHT )
            choice:=0
            exit
        
        elseif( key==K_ENTER )
            exit

        elseif( key==K_HOME )
            pattern:=""
            toppos::=top(leni,height,choice,choice:=1)
            chdraw(top,left,bottom,right,item,toppos,choice)

        elseif( key==K_END )
            pattern:=""
            toppos::=top(leni,height,choice,choice:=leni)
            chdraw(top,left,bottom,right,item,toppos,choice)

        elseif( key==K_UP )
            pattern:=""
            if( choice>1 )
                toppos::=top(leni,height,choice,--choice)
                chdraw(top,left,bottom,right,item,toppos,choice)
            end

        elseif( key==K_PGUP )
            pattern:=""
            toppos::=top(leni,height,choice,choice:=max(1,choice-height))
            chdraw(top,left,bottom,right,item,toppos,choice)

        elseif( key==K_DOWN )
            pattern:=""
            if( choice<leni )
                toppos::=top(leni,height,choice,++choice)
                chdraw(top,left,bottom,right,item,toppos,choice)
            end

        elseif( key==K_PGDN )
            pattern:=""
            toppos::=top(leni,height,choice,choice:=min(leni,choice+height))
            chdraw(top,left,bottom,right,item,toppos,choice)

        elseif( key>=32 )
            key::=chr
            pos:=scan2(item,pattern+key) //hosszabbitva keres
            if( pos==0 )
                pattern:=""
                pos:=scan2(item,pattern+key) // ujrakezdve keres
            end
            if( pos!=0 )
                pattern+=key
                toppos::=top(leni,height,choice,choice:=pos)
                chdraw(top,left,bottom,right,item,toppos,choice)
            end
        end
    end
   
    setcursor(crs)
    return choice


****************************************************************************
static function top(top1,l,h,pos1,pos2)

// top1  a choice elso sora (aktualis top)
// l     osszes elem szama a choiceban
// h     a choice magassaga (ennyi jelenitheto meg)
// pos1  a kurzor aktualis pozicioja
// pos2  ide akarunk pozicionalni
// top2  kimenet: ez lesz a choice uj felso sora
//
// 1 ----
// 2 ----
//   ---- top1       felso sor
//   ----
//   ----
//   ---- pos1       aktualis kurzor
//   ----
//   ---- top1+h-1   also sor
// l ----

local top2:=top1

    if( top1<=pos2 .and. pos2<top1+h )
        //nem valtozik
    elseif(  pos2-pos1==1 )
        top2++
    elseif(  pos1-pos2==1 )
        top2--
    else
        top2:=(pos2-int(h/3)) // kozepre
    end
    return top2::min(l-h+1)::max(1)


****************************************************************************
static function chdraw(top,left,bottom,right,item,toppos,choice)

local color:=setcolor()
local stColor:=LogColor(color,1)
local hiColor:=LogColor(color,2)
local r,w:=right-left+1
local pos:=toppos
local screen:=a""
local outstr

    for r:=top to bottom
        outstr:=padr(item[pos],w)
        screen+=devoutbuffer(outstr,if(pos==choice,hiColor,stColor))
        pos++
    next
    
    restscreen(top,left,bottom,right,screen)
    setpos(top+choice-toppos,right+1)
    //achoice a kurzort a kiemelt sor után kell hagyja!
    return NIL


****************************************************************************
static function scan2(item,pattern)
local n, w:=len(pattern)
    pattern::=upper
    for n:=1 to len(item)
        if( item[n]::upper==pattern  )
            return n
        end
    next
    for n:=1 to len(item)
        if( !(item[n]::upper!=pattern)  )
            return n
        end
    next
    return 0


****************************************************************************

