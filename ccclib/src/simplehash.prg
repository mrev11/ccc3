
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

// A simplehash osztály hashitem és get metódusait
// és a hashitemek {key,value} alakját használja ki
// az asszociatív tömbindexelés: hash["key"]:=value.

//2009.01.19 
//  plusz metódusok, bejárók
//  rugalmasan kezeli a törléseket

#define  HASHTAB_INITSIZE       256
#define  HASHTAB_INCFACTOR      2
#define  HASHTAB_MAXFILL        0.66666

****************************************************************************
class simplehash(object)

    attrib  hasharray     //  elemei: NIL/{key,value}, törölt <-> value==NIL
    attrib  initsize      //  kezdeti méret
    attrib  itemcount     //  elemek száma töröltekkel együtt
    attrib  iteridx       //  bejáró index (kezdetben NIL)

    method  initialize
    method  hashitem      //  helyet keres/csinál egy elemnek
    method  rehash        //  átméretez, kihagyja a value==NIL-eket
    method  valuecount    //  elemek száma töröltek nélkül (value!=NIL-ek)
    method  clone         //  shallow copy, kihagyja a value==NIL elemeket
    method  clear         //  kiürít

    method  set           //  h:set(k,v)  <=>  h[k]:=v
    method  get           //  h:get(k)    <=>  h[k]
    method  remove        //  h:remove(k) <=>  h[k]:=NIL

    method  first         //  bejárja a value!=NIL elemeket
    method  firstkey
    method  firstvalue
    method  next          //  -> {key,value}
    method  nextkey       //  -> key
    method  nextvalue     //  -> value

    method  list
    method  listkey
    method  listvalue

    method  toarr
    method  toarrkey
    method  toarrvalue


****************************************************************************
static function simplehash.initialize(this,data) 
local item

    this:(object)initialize

    this:itemcount:=0

    if( valtype(data)=="U" )
        this:initsize:=HASHTAB_INITSIZE 
        this:hasharray:=array(this:initsize)

    elseif( valtype(data)=="N" )
        this:initsize:=max(data,4)
        this:hasharray:=array(this:initsize)

    else //copy constructor
        this:initsize:=data:initsize
        this:hasharray:=array(this:initsize)

        item:=data:first
        while( NIL!=item )
            this:set(item[1],item[2])
            item:=data:next
        end
    end
    return this

****************************************************************************
static function simplehash.hashitem(this,key)
local x:=hash_index(this:hasharray,key)
    if( this:hasharray[x]==NIL )
        if( this:itemcount>=HASHTAB_MAXFILL*len(this:hasharray) )
            this:rehash
            x:=hash_index(this:hasharray,key)
        end
        this:hasharray[x]:={key,NIL}
        this:itemcount++
    end
    return this:hasharray[x]

****************************************************************************
static function simplehash.rehash(this)

local ha:=this:hasharray,len:=len(ha),n
local ha1,len1:=len,vc:=this:valuecount,x

    if( len1<HASHTAB_INCFACTOR*vc )
        len1*=HASHTAB_INCFACTOR
    else
        while( len1/HASHTAB_INCFACTOR>=this:initsize .and.;
               len1/HASHTAB_INCFACTOR>=HASHTAB_INCFACTOR*vc )
            len1/=HASHTAB_INCFACTOR
        end
    end

    ha1:=array(len1)
    for n:=1 to len
        if( ha[n]!=NIL .and. ha[n][2]!=NIL ) //nem törölt
            x:=hash_index(ha1,ha[n][1])
            ha1[x]:=ha[n]
        end
    next

    //? ">>", str(this:itemcount/len,8,3), this:itemcount, vc, len, len1

    this:itemcount:=vc
    this:hasharray:=ha1
    this:iteridx:=NIL
    

****************************************************************************
static function simplehash.valuecount(this)
local ha:=this:hasharray,len:=len(ha),n,vc:=0
    for n:=1 to len
        if( ha[n]!=NIL .and. ha[n][2]!=NIL ) //nem törölt
            vc++ 
        end
    next
    return vc

****************************************************************************
static function simplehash.clone(this)
    return simplehashNew(this)

****************************************************************************
static function simplehash.clear(this)
    this:iteridx:=NIL
    this:itemcount:=0
    this:hasharray:=array(this:initsize)

****************************************************************************
static function simplehash.set(this,key,value)
local item:=this:hashitem(key)
    return item[2]:=value

****************************************************************************
static function simplehash.get(this,key)
local x:=hash_index(this:hasharray,key)
local value //NIL
    if( this:hasharray[x]!=NIL )
        value:=this:hasharray[x][2]
    end
    return value

****************************************************************************
static function simplehash.remove(this,key)
local x:=hash_index(this:hasharray,key)
local value //NIL
    if( this:hasharray[x]!=NIL )
        value:=this:hasharray[x][2]
        this:hasharray[x][2]:=NIL
    end
    return value

****************************************************************************
static function simplehash.first(this)
    this:iteridx:=0
    return this:next

****************************************************************************
static function simplehash.firstkey(this)
    this:iteridx:=0
    return this:nextkey

****************************************************************************
static function simplehash.firstvalue(this)
    this:iteridx:=0
    return this:nextvalue

****************************************************************************
static function simplehash.next(this)
local i
    while( (i:=++this:iteridx)<=len(this:hasharray) )
        if( this:hasharray[i]!=NIL .and. this:hasharray[i][2]!=NIL )
            return this:hasharray[i]  // {key,value}
        end
    end

****************************************************************************
static function simplehash.nextkey(this)
local x:=this:next
    return if(x==NIL,NIL,x[1])

****************************************************************************
static function simplehash.nextvalue(this)
local x:=this:next
    return if(x==NIL,NIL,x[2])


****************************************************************************
static function simplehash.list(this)
local item:=this:first
    while( item!=NIL )
        ? item
        item:=this:next
    end

****************************************************************************
static function simplehash.listkey(this)
local item:=this:firstkey
    while( item!=NIL )
        ? item
        item:=this:nextkey
    end

****************************************************************************
static function simplehash.listvalue(this)
local item:=this:firstvalue
    while( item!=NIL )
        ? item
        item:=this:nextvalue
    end

****************************************************************************
static function simplehash.toarr(this)
local arr,item,cnt:=0
    arr:=array(this:valuecount)
    item:=this:first
    while( item!=NIL )
        arr[++cnt]:=item
        item:=this:next
    end
    return arr

****************************************************************************
static function simplehash.toarrkey(this)
local arr,key,cnt:=0
    arr:=array(this:valuecount)
    key:=this:firstkey
    while( key!=NIL )
        arr[++cnt]:=key
        key:=this:nextkey
    end
    return arr

****************************************************************************
static function simplehash.toarrvalue(this)
local arr,value,cnt:=0
    arr:=array(this:valuecount)
    value:=this:firstvalue
    while( value!=NIL )
        arr[++cnt]:=value
        value:=this:nextvalue
    end
    return arr


****************************************************************************
//hash algoritmus
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

// A hash tábla egy array: {item1,item2,...},
// ahol item==NIL, vagy item=={key,value} alakú.

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
