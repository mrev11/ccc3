
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

//Ebbe a modulba kell tenni azokat a fuggvenyeket,
//amiknek kozvetlenul aclass-on kell dolgozni.
//Egyik fuggvenynek sem lehet olyan visszateresi erteke,
//amin keresztul aclass veletlenul modosithato.

static aclass:={}

static mutex:=thread_mutex_init()
#define MUTEX_LOCK    (thread_mutex_lock(mutex))
#define MUTEX_UNLOCK  (thread_mutex_unlock(mutex))

//Az aclass array-hez valo hozzaferest mutex szinkronizalja.
//Ha azonban szignal jon a MUTEX_LOCK es MUTEX_UNLOCK kozott,
//es a szignal kezelo maga is lockolni akarja a mutexet, akkor 
//deadlock keletkezhet. Ezt akadalyozza meg s ignal_lock(),
//ami a kurrens szalat vedi a szignaloktol. 

#define  CLASS_NAME      1    //osztalynev
#define  CLASS_BASEID    2    //baseclass azonosito array
#define  CLASS_ATTRCNT   3    //attributumok szama (objektumok hossza)
#define  CLASS_SLOTCNT   4    //attributumok+metodusok szama
#define  CLASS_HASHTAB   5    //hash tabla

//Ha a hash tabla MAXFILL-nel jobban megtelik,
//akkor a meretet INCREMENT szerint noveljuk.
//A 0.66 es 2 szorzokkal az atmeretezett tablak 
//kitoltottsege 1/3 es 2/3 kozott lesz.

#define  HASHTAB_INITSIZE        64
#define  HASHTAB_INCREMENT(x)    len(x)*2
#define  HASHTAB_MAXFILL(x)      len(x)*0.66


******************************************************************************
static function hash_rebuild(hash,len)
local hash1:=array(len),n,x
    for n:=1 to len(hash)
        if( hash[n]!=NIL )
            x:=hash_index(hash1,hash[n][1])
            hash1[x]:=hash[n]
        end
    next
    return hash1

// A hash tabla egy array: {item1,item2,...},
// ahol item==NIL, vagy item=={key,...} alaku.

******************************************************************************
static function hash_index(hash,key,hcode)

local hlen:=len(hash)
local hidx:=if(hcode==NIL,hashcode(key),hcode)%hlen

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


// Kereses a hash tablaban:
//    
// A ciklus veget er, ui. a tabla hosszabb, 
// mint ahany nem NIL elem van benne.    
//
// visszateres: hashidx
//
// Ha hash[hasidx]==NIL, akkor a keresett elem nincs a tablaban,
//                       es eppen a hashidx helyre kell/lehet betenni.
//
// Ha hash[hasidx]!=NIL, akkor az a keresett elem.


******************************************************************************
static function getclsdef(clid)
local clsdef
    MUTEX_LOCK
    clsdef:=aclass[clid]
    MUTEX_UNLOCK
    return clsdef

******************************************************************************
function classListAll()
local n,clsdef,clscount

    MUTEX_LOCK
    clscount:=len(aclass)
    MUTEX_UNLOCK

    for n:=1 to clscount
        clsdef:=getclsdef(n)
        ? str(n,4),;                         // clid
          padr(clsdef[CLASS_NAME],64),;      // classname
          str(clsdef[CLASS_ATTRCNT],4),;     // attrcount
          str(clsdef[CLASS_SLOTCNT],4),;     // slotcount (attr+meth)
          str(len(clsdef[CLASS_HASHTAB]),4)  // hashtab size
    next
    ?
    return NIL

******************************************************************************
function classRegister(clname,clbaseid)

// clbaseid lehet
//
// NIL   : nincs felmeno osztaly (gyoker)
// szam  : baseclass (egyszeres oroklodes)
// array : baseclass-ok listaja (tobbszoros orolodes)

local aid,i,s
local hash:=array(HASHTAB_INITSIZE),bhash
local name,value,inherit
local olen:=0,slen:=0
local hashidx
local clid

    if( clbaseid==NIL )
        aid:={}
    elseif( valtype(clbaseid)=="N" )
        aid:={clbaseid}
    else
        aid:=clbaseid
    end

    if( !empty(aid) )
        // i=1 elso baseclass
        // az elso baseclass atvetelekor
        // megorizzuk az attributumok sorrendjet

        bhash:=getclsdef(aid[1])[CLASS_HASHTAB]

        for s:=1 to len(bhash) //vegigmegy a baseclass slotjain
            if( bhash[s]!=NIL )
                name:=bhash[s][1]
                value:=bhash[s][2] 
                inherit:=bhash[s][3] 

                hashidx:=hash_index(hash,name)
                hash[hashidx]:={name,value,inherit} // eredeti attributum index

                if( valtype(value)=="N" )
                    ++olen
                end
                if( ++slen>HASHTAB_MAXFILL(hash) )
                    hash:=hash_rebuild(hash,HASHTAB_INCREMENT(hash) )
                end
            end
        next
    end

    for i:=2 to len(aid) //vegigmegy a tovabbi baseclass-okon
    
        bhash:=getclsdef(aid[i])[CLASS_HASHTAB]
        
        for s:=1 to len(bhash) //vegigmegy a baseclass slotjain
        
            if( bhash[s]!=NIL )

                name:=bhash[s][1]
                value:=bhash[s][2] 
                inherit:=bhash[s][3] 

                hashidx:=hash_index(hash,name)
            
                if( hash[hashidx]==NIL ) 
                    //nincs meg ilyen

                    if( valtype(value)=="B" )
                        hash[hashidx]:={name,value,inherit}  //uj array!
                    else
                        hash[hashidx]:={name,++olen,inherit}
                    end

                    if( ++slen>HASHTAB_MAXFILL(hash) )
                        hash:=hash_rebuild(hash,HASHTAB_INCREMENT(hash) )
                    end
                end
            end
        next
    next

    MUTEX_LOCK
    aadd(aclass,{str2bin(lower(clname)),aid,olen,slen,hash}) 
    clid:=len(aclass) //classid
    MUTEX_UNLOCK    

    return clid 


******************************************************************************
function classAttrib(clid,name)

local clsdef:=getclsdef(clid)
local lname:=str2bin(lower(name))
local hash:=clsdef[CLASS_HASHTAB]
local hashidx:=hash_index(hash,lname)

    if( hash[hashidx]==NIL ) //uj attributum

        hash[hashidx]:={lname,++clsdef[CLASS_ATTRCNT],clid}

        if( ++clsdef[CLASS_SLOTCNT] > HASHTAB_MAXFILL(hash) )
            clsdef[CLASS_HASHTAB]:=hash_rebuild(hash,HASHTAB_INCREMENT(hash))
        end

    else //feluldefinialas
 
        //method -> attrib : kodblokk helyere index, ++hossz
        //attrib -> attrib : OK

        if( valtype(hash[hashidx][2])=="B" )
            hash[hashidx][2]:=++clsdef[CLASS_ATTRCNT]
            hash[hashidx][3]:=clid 
        end
    end
    
    return NIL


******************************************************************************
function classMethod(clid,name,methblk)

local clsdef:=getclsdef(clid)
local lname:=str2bin(lower(name))
local hash:=clsdef[CLASS_HASHTAB]
local hashidx:=hash_index(hash,lname)
local reindex,cnt,n

    if( hash[hashidx]==NIL ) //uj method

        hash[hashidx]:={lname,methblk,clid}

        if( ++clsdef[CLASS_SLOTCNT] > HASHTAB_MAXFILL(hash) )
            clsdef[CLASS_HASHTAB]:=hash_rebuild(hash,HASHTAB_INCREMENT(hash))
        end

    else //feluldefinialas
 
        //method -> method : kodblokk csere
        //attrib -> method : index helyere kodblokk (->reindex)

        reindex:=valtype(hash[hashidx][2])=="N"

        hash[hashidx][2]:=methblk
        hash[hashidx][3]:=clid

        if( reindex )
            cnt:=0
            for n:=1 to len(hash)
                if( hash[n]!=NIL .and. valtype(hash[n][2])=="N" )
                    hash[n][2]:=++cnt
                end
            next
            clsdef[CLASS_ATTRCNT]:=cnt
        end
    end

******************************************************************************
function classIdByName(name)
local clid
    name:=str2bin(lower(name))
    MUTEX_LOCK
    clid:=ascan(aclass,{|c|c[CLASS_NAME]==name}) 
    MUTEX_UNLOCK
    return clid
 

******************************************************************************
function classObjectLength(clid)
    return getclsdef(clid)[CLASS_ATTRCNT]


******************************************************************************
function classMethodCount(clid)
    return getclsdef(clid)[CLASS_SLOTCNT]-getclsdef(clid)[CLASS_ATTRCNT]


******************************************************************************
function className(clid) 
    return bin2str(getclsdef(clid)[CLASS_NAME])


******************************************************************************
function classBaseID(clid) 
    return aclone(getclsdef(clid)[CLASS_BASEID])


******************************************************************************
function classAttrNames(clid,id) 
local hash:=getclsdef(clid)[CLASS_HASHTAB],n
local attr:=array(classObjectLength(clid)),x
    for n:=1 to len(hash)
        if( hash[n]!=NIL .and. valtype(x:=hash[n][2])=="N" .and. (id==NIL.or.hash[n][3]==id) ) 
            attr[x]:=hash[n][1]
        end
    next
    return attr //index szerinti sorrend!


******************************************************************************
function classMethNames(clid,id) 
local hash:=getclsdef(clid)[CLASS_HASHTAB],n
local meth:=array(classMethodCount(clid)),x:=0
    for n:=1 to len(hash)
        if( hash[n]!=NIL .and. valtype(hash[n][2])=="B" .and. (id==NIL.or.hash[n][3]==id) ) 
            meth[++x]:=bin2str(hash[n][1])
        end
    next
    asize(meth,x)
    return meth  //hash-beli elhelyezkedes sorrendjeben


******************************************************************************
function classInheritStruct(clid) 
local hash:=getclsdef(clid)[CLASS_HASHTAB],n,inherit:={}
    for n:=1 to len(hash)
        if( hash[n]!=NIL )
            aadd(inherit,{bin2str(hash[n][1]),if(valtype(hash[n][2])=="B","M","A"),hash[n][3]} )
        end
    next
    //asort(inherit,,,{|x,y|x[1]<y[1]}) //nev szerint
    asort(inherit,,,{|x,y|x[3]<y[3].or.x[3]==y[3].and.x[1]<y[1]}) //clid+nev szerint
    return inherit


******************************************************************************
function __findslot(clid,slotname,hashcode)

local hash:=getclsdef(clid)[CLASS_HASHTAB]
local hashidx:=hash_index(hash,slotname,hashcode)
local item:=hash[hashidx], err

    if( item==NIL )
        err:=errorNew()
        err:description:=@"no exported method"
        err:operation:=className(clid)+":"+bin2str(slotname)
        break(err)
    end

    return item[2]  //methblk/attridx


******************************************************************************
function __findslot_c(clid,slotname,classname,hashcode)
local clid1,blk,err
    if( 0==(clid1:=classIDByName(classname)) )
        err:=errorNew()
        err:description:="'"+bin2str(classname)+"' "+@"not a valid classname"
        err:operation:=className(clid)+":("+bin2str(classname)+")"+bin2str(slotname)
        break(err)
    end

    blk:=__findslot(clid1,slotname,hashcode)

    if( !valtype(blk)=="B" )
        err:=errorNew()
        err:description:=@"no exported method"
        err:operation:=className(clid)+":("+bin2str(classname)+")"+bin2str(slotname)
        break(err)
    end

    return blk

 
******************************************************************************
function __findslot_s(clid,slotname,classname,hashcode)

local clid1,baseid,i
local hash,hashidx,blk,err
 
    if( 0==(clid1:=classIDByName(classname)) )
        err:=errorNew()
        err:description:="'"+bin2str(classname)+"' "+@"not a valid classname"
        err:operation:=className(clid)+":(super@"+bin2str(classname)+")"+bin2str(slotname)
        break(err)
    end
    
    baseid:=getclsdef(clid1)[CLASS_BASEID] 
 
    for i:=1 to len(baseid)
        hash:=getclsdef(baseid[i])[CLASS_HASHTAB]
        hashidx:=hash_index(hash,slotname,hashcode)
        if( hash[hashidx]!=NIL )
            blk:=hash[hashidx][2] //methblk/attridx
            if( !valtype(blk)=="B" )
                err:=errorNew()
                err:description:=@"no exported method"
                err:operation:=className(clid)+":(super@"+bin2str(classname)+")"+bin2str(slotname)
                break(err)
            end
            return blk
        end
    next

    err:=errorNew()
    err:description:=@"no exported method"
    err:operation:=className(clid)+":(super@"+bin2str(classname)+")"+bin2str(slotname)
    break(err)
 
    return NIL //nem talalhato  
 

******************************************************************************
function __findslot_p(clid,slotname,prntname,classname,hashcode)

local clid0,clid1,blk,err
 
    if( 0==(clid0:=classIDByName(classname)) )
        err:=errorNew()
        err:description:="'"+bin2str(classname)+"' "+@"not a valid classname"
        err:operation:=className(clid)+":("+bin2str(prntname)+"@"+bin2str(classname)+")"+bin2str(slotname)
        break(err)
    end

    if( 0==(clid1:=classIDByName(prntname)) )
        err:=errorNew()
        err:description:="'"+bin2str(prntname)+"' "+@"not a valid classname"
        err:operation:=className(clid)+":("+bin2str(prntname)+"@"+bin2str(classname)+")"+bin2str(slotname)
        break(err)
    end
    
    if( 0==ascan(getclsdef(clid0)[CLASS_BASEID],clid1)  )
        err:=errorNew()
        err:description:="'"+bin2str(prntname)+"' "+@"is not parent of"+" '"+bin2str(classname)+"'"
        err:operation:=className(clid)+":("+bin2str(prntname)+"@"+bin2str(classname)+")"+bin2str(slotname)
        break(err)
    end
    
    blk:=__findslot(clid1,slotname,hashcode)
    
    if( !valtype(blk)=="B" )
        err:=errorNew()
        err:description:=@"no exported method"
        err:operation:=className(clid)+":("+bin2str(prntname)+"@"+bin2str(classname)+")"+bin2str(slotname)
        break(err)
    end

    return blk
 

******************************************************************************
function getmethod(clid,name) //nem objektumfuggveny
    return __findslot(clid,str2bin(lower(name)))


******************************************************************************
// xmethod3 metodusok
******************************************************************************
static function isderivedfrom(cld,clb)
local baseid,n
    if( clb==cld )
        return .t.
    else
        baseid:=classBaseID(cld)
        for n:=1 to len(baseid)
            if( isderivedfrom(baseid[n],clb) )
                return .t.
            end
        next
    end
    return .f.

******************************************************************************
function __findslot3_c(clid,slotname,clid1,hashcode)

local blk,err

    //? "__findslot3_c",clid,slotname,clid1,hashcode

    if( !isderivedfrom(clid,clid1) )
        err:=errorNew()
        err:description:=@"prohibited method cast"
        err:operation:=className(clid)+":("+className(clid1)+")"+bin2str(slotname)
        break(err)
    end

    blk:=__findslot(clid1,slotname,hashcode)

    if( !valtype(blk)=="B" )
        err:=errorNew()
        err:description:=@"prohibited attribute cast"
        err:operation:=className(clid)+":("+className(clid1)+")"+bin2str(slotname)
        break(err)
    end

    return blk
 
******************************************************************************
function __findslot3_s(clid,slotname,clid1,hashcode)

local baseid,i
local hash,hashidx,blk,err

    //? "__findslot3_s",clid,slotname,clid1,hashcode

    if( !isderivedfrom(clid,clid1) )
        err:=errorNew()
        err:description:=@"prohibited method cast"
        err:operation:=className(clid)+":(super@"+className(clid1)+")"+bin2str(slotname)
        break(err)
    end
 
    baseid:=getclsdef(clid1)[CLASS_BASEID] 
 
    for i:=1 to len(baseid)
        hash:=getclsdef(baseid[i])[CLASS_HASHTAB]
        hashidx:=hash_index(hash,slotname,hashcode)
        if( hash[hashidx]!=NIL )
            blk:=hash[hashidx][2] //methblk/attridx
            if( !valtype(blk)=="B" )
                err:=errorNew()
                err:description:=@"prohibited attribute cast"
                err:operation:=className(clid)+":(super@"+className(clid1)+")"+bin2str(slotname)
                break(err)
            end
            return blk
        end
    next

    err:=errorNew()
    err:description:=@"no exported method"
    err:operation:=className(clid)+":(super@"+className(clid1)+")"+bin2str(slotname)
    break(err)
 

******************************************************************************
function __findslot3_p(clid,slotname,clid1,clid0,hashcode)
//                                   prnt  chld
local blk,err

    //? "__findslot3_p",clid,slotname,clid1,clid0,hashcode

    if( !isderivedfrom(clid,clid0) )
        err:=errorNew()
        err:description:=@"prohibited method cast"
        err:operation:=className(clid)+":("+className(clid1)+"@"+className(clid0)+")"+bin2str(slotname)
        break(err)
    end
 
    if( 0==ascan(getclsdef(clid0)[CLASS_BASEID],clid1)  )
        err:=errorNew()
        err:description:="'"+className(clid1)+"' "+@"is not parent of"+" '"+className(clid0)+"'"
        err:operation:=className(clid)+":("+className(clid1)+"@"+className(clid0)+")"+bin2str(slotname)
        break(err)
    end
    
    blk:=__findslot(clid1,slotname,hashcode)
    
    if( !valtype(blk)=="B" )
        err:=errorNew()
        err:description:=@"prohibited attribute cast"
        err:operation:=className(clid)+":("+className(clid1)+"@"+className(clid0)+")"+bin2str(slotname)
        break(err)
    end

    return blk


******************************************************************************

    