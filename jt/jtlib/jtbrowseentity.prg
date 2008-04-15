
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
//jtbrowseentity (segédlet tableentityk browseolásához)
****************************************************************************
class jtbrowseentity(jtbrowsearray) 
    method  initialize
    method  addcolumn
    method  addcolumns
    attrib  __rowset__
    method  rowset
    method  next

****************************************************************************
static function jtbrowseentity.initialize(this,t,l,b,r)  
    this:(jtbrowsearray)initialize(t,l,b,r)
    return this

****************************************************************************
static function jtbrowseentity.addcolumn(this,h,c,p,w) 

local typ,hdr,blk,pic,wid

    if( valtype(h)=="O" )
        c:=h
        hdr:=wid:=pic:=NIL
    else
        hdr:=h
    end
    
    if( hdr==NIL )
        hdr:=if(c:label==NIL,c:name,c:label)
    end

    if( valtype(p)=="C" )
        pic:=p
        wid:=w
    elseif( valtype(w)=="C" )
        pic:=w
        wid:=p
    elseif( valtype(p)=="N" )
        wid:=p
        pic:=NIL
    elseif( valtype(w)=="N" )
        wid:=w
        pic:=NIL
    end

    if( pic==NIL )
        pic:=jtbrowseentity.picture(c)
    end

    blk:=mkupdateblk(this,c)

    return this:(jttable)addcolumn(hdr,blk,pic,wid)

****************************************************************************
static function jtbrowseentity.addcolumns(this,tentity)
local n,entcol,brwcol
    for n:=1 to len(tentity:columnlist)
        entcol:=tentity:columnlist[n]
        brwcol:=this:addcolumn(entcol)
        //brwcol:editable:=.t.
    next
    return NIL

****************************************************************************
static function jtbrowseentity.rowset(this,rs)
    if( rs!=NIL )
        if(this:__rowset__!=NIL)
            this:__rowset__:close
        end
        this:__rowset__:=rs
    end
    return this:__rowset__

****************************************************************************
static function jtbrowseentity.next(this)
local n,e
    this:_array_:=array(this:maxrow)
    for n:=1 to this:maxrow
        e:=this:rowset:next
        if( e==NIL )
            asize(this:_array_,n-1)
            exit
        else
            this:_array_[n]:=e
        end
    next
    return this:pagefirst

*****************************************************************************
static function mkupdateblk(this,c)
local blk
    if( c:type=="M" )
        blk:={|x|updateblk_memo(this,c,x)}
    else
        blk:={|x|updateblk(this,c,x)}
    end
    return blk 

static function updateblk(this,c,x)
local row:=this:_array_[this:_arraypos_]
    return eval(c:block,row,x)

static function updateblk_memo(this,c,x)
local row:=this:_array_[this:_arraypos_]
    return bin2str(eval(c:block,row,if(x==NIL,NIL,str2bin(x))))

//Itt nem kell vizsgálni az értékek eltérését,
//mert a jterminal table már nézi a különbséget,
//és csak akkor küld változást, ha tartalmi eltérés van.


****************************************************************************
function jtbrowseentity.picture(c)

// picture function flagek
//
// C: a get típusa string
// N: a get típusa szám
// L: a get típusa logikai
// D: a get típusa dátum
// R: a template karakterek nélkül adja a tartalmat
// X: akciókor figyelmeztet, ha érvénytelen tartalom van a getben
// E: X ellenére elfogadja az Empty érvénytelen tartalmat
// T: trimelve adja az eredményt
// A: csak betűt enged gépelni (?)
// !: nagybetűre konvertál

local typ:=left(c:type,1)
local wid:=substr(c:type,2),w,d
local funstr:="@"+typ+"RXE",pic

    if( c:picture!=NIL )
        //az oszlopban van picture

        pic:=c:picture
        if( !left(pic,1)=="@" )
            pic:=funstr+" "+pic
        else
            pic:=strtran(pic,"@",funstr) //lehetnek ismétlődések
        end
        
    elseif( typ=="C" )
        pic:=funstr+" "+replicate("X",val(wid))

    elseif( typ=="N" )
        wid:=strtran(wid,".",",")

        if( ","$wid )
            wid:=split(wid) //{w,d}
            w:=val(wid[1])
            d:=val(wid[2])
            pic:="@RN "+replicate("9",w-d)+"."+replicate("9",d)
            pic:=strtran(pic,"9999.","9,999.")
            while("9999,"$pic)
                pic:=strtran(pic,"9999,","9,999,")
            end
        else
            pic:="@RN "+replicate("9",val(wid))+","
            while("9999,"$pic)
                pic:=strtran(pic,"9999,","9,999,")
            end
            pic:=left(pic,len(pic)-1)
        end

    elseif( typ=="L" )
        pic:=funstr+"!"

    elseif( typ=="D" )
        pic:=funstr

    elseif( typ=="M" )
        pic:=24
    end
    
    return pic

*****************************************************************************
