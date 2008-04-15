
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

//A tutorból áhozva.
//Név hashtable --> gladehashtable.
//Bővítve a list metódussal.
//Debug célból listázza a nem találó kereséseket.
//A get {key,value} helyett csak value-t adja.

#define  HASHTAB_INITSIZE        256
#define  HASHTAB_INCREMENT(x)    len(x)*2
#define  HASHTAB_MAXFILL(x)      len(x)*0.66

****************************************************************************
class gladehashtable(object)
    method initialize
    attrib itemcount
    attrib hasharray
    method add
    method get
    method list

****************************************************************************
function gladehashtable.initialize(this,size) 
    this:(object)initialize
    this:itemcount:=0
    this:hasharray:=array(if(size==NIL,HASHTAB_INITSIZE,size))
    return this

****************************************************************************
static function gladehashtable.add(this,item)
local x:=hash_index(this:hasharray,item[1])
    if( this:hasharray[x]==NIL )
        if( ++this:itemcount>HASHTAB_MAXFILL(this:hasharray) )
            this:hasharray:=hash_rebuild(this:hasharray,HASHTAB_INCREMENT(this:hasharray))
            x:=hash_index(this:hasharray,item[1])
        end
    end
    this:hasharray[x]:=item
    return item

****************************************************************************
static function gladehashtable.get(this,key)
local x:=hash_index(this:hasharray,key)
    if( this:hasharray[x]==NIL )
        //? "key not found:", key
        return NIL
    end
    return this:hasharray[x][2]  //csak a value-t adja!


****************************************************************************
static function gladehashtable.list(this)
local n
    for n:=1 to len(this:hasharray)
        if( this:hasharray[n]!=NIL )
            ? n, this:hasharray[n]
        end
    next

****************************************************************************
//hash algoritmus
****************************************************************************
static function hash_rebuild(hash,len)
local hash1:=array(len),n,x
    for n:=1 to len(hash)
        if( hash[n]!=NIL )
            x:=hash_index(hash1,hash[n][1])
            hash1[x]:=hash[n]
        end
    next
    return hash1

// A hash tábla egy array: {item1,item2,...},
// ahol item==NIL, vagy item=={key,...} alakú.

****************************************************************************
static function hash_index(hash,key)

local hlen:=len(hash)
local hcode:=hashcode(key)
local hidx:=hcode%hlen

    while( .t. )
        if( NIL==hash[1+hidx] )
            return 1+hidx
        elseif( key==hash[1+hidx][1] )
            return 1+hidx
        elseif( ++hidx>=hlen )
            hidx:=0
        end
    end
    return NIL


// Keresés a hash táblában:
//    
// A ciklus véget ér, ui. a tábla hosszabb, 
// mint ahány nem NIL elem van benne.    
//
// visszatérés: hashidx
//
// Ha hash[hashidx]==NIL, akkor a keresett elem nincs a táblában,
//                        és éppen a hashidx helyre kell/lehet betenni.
//
// Ha hash[hashidx]!=NIL, akkor az a keresett elem.

****************************************************************************
