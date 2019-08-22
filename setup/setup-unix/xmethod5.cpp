
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

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <cccapi.h>

#include <hashtable_simple.h>

#define GLOBAL_SLOTBUFFER_SIZE 50


struct hashvalue
{
    MUTEX_DECLARE(mutex);
    slotitem buffer[GLOBAL_SLOTBUFFER_SIZE];
};


MUTEX_CREATE(mutex);

//----------------------------------------------------------------------
static slotitem *global_slotbuffer(const char *name, MUTEX_POINTER *mutexptr, unsigned *size)
{
    MUTEX_LOCK(mutex);

    static hashtable_simple *global_slothash=new hashtable_simple();

    hashvalue* value=(hashvalue*)global_slothash->get(name);
    if( value==0 )
    {
        value=new hashvalue;
        memset(value,0,sizeof(hashvalue));
        MUTEX_INIT(value->mutex);
        global_slothash->add(name,value);
    }
    *mutexptr=MUTEX_ADDRESS(value->mutex);
    *size=GLOBAL_SLOTBUFFER_SIZE;

    MUTEX_UNLOCK(mutex);
    return value->buffer;
}

//----------------------------------------------------------------------
_method5_::_method5_(const char *sname)
{
    slotname=sname; 
    slothashcode=hashcode(sname);
    slotbuffer=global_slotbuffer(slotname,&mutexptr,&slotbuffersize);
};


_method5s_::_method5s_(const char *sname, CLASSID *bid) : _method5_(sname)
{
    baseid=bid; 

    slotbuffersize=5;
    slotbuffer=(slotitem*)malloc(sizeof(slotitem)*slotbuffersize);
    memset(slotbuffer,0,sizeof(slotitem)*slotbuffersize);

    MUTEX_INIT(mutex);
    mutexptr=MUTEX_ADDRESS(mutex);
};


_method5c_::_method5c_(const char *sname, CLASSID *bid) : _method5_(sname)
{
    baseid=bid; 

    slotbuffersize=5;
    slotbuffer=(slotitem*)malloc(sizeof(slotitem)*slotbuffersize);
    memset(slotbuffer,0,sizeof(slotitem)*slotbuffersize);

    MUTEX_INIT(mutex);
    mutexptr=MUTEX_ADDRESS(mutex);
};


_method5p_::_method5p_(const char *sname, CLASSID *pid, CLASSID *bid) : _method5_(sname)
{
    prntid=pid; 
    baseid=bid; 

    slotbuffersize=5;
    slotbuffer=(slotitem*)malloc(sizeof(slotitem)*slotbuffersize);
    memset(slotbuffer,0,sizeof(slotitem)*slotbuffersize);

    MUTEX_INIT(mutex);
    mutexptr=MUTEX_ADDRESS(mutex);
};


//----------------------------------------------------------------------
void _method5_::findslot(int clid)
{
    MUTEX_UNLOCK_PTR(mutexptr);
    SIGNAL_UNLOCK();
    number(clid);
    binary(slotname);
    number(slothashcode);
    _clp___findslot(3);  //ua. mint xmethod2-ben
    
    //Clipper szinten keresünk.
    //Ha nem talált, akkor ide már nem jön,
    //mert a hibát _clp___findslot() kezeli.
    //A mutex jelenleg éppen nincs lockolva, tehát, 
    //ha a hibát elkapják, a mutex szabad állapotban marad.
    //Ha talált, akkor a method blokkja,
    //vagy az attribútum indexe van a stacken.
    //Ezt a blokkot/indexet megőrizzük a slot memberben,
    //(VIGYÁZAT) itt a blokkot a szemétgyűjtés nem tudja 
    //megtalálni, és csak amiatt nem takarítódik le, 
    //mert ugyanerre az objektumra a static aclass
    //tömbből is van hivatkozás.
    
    SIGNAL_LOCK();
    MUTEX_LOCK_PTR(mutexptr);
    slotbuffer[clid%slotbuffersize].classid=clid;
    slotbuffer[clid%slotbuffersize].slotvalue=*TOP();
}

void _method5s_::findslot(int clid)
{
    MUTEX_UNLOCK_PTR(mutexptr);
    SIGNAL_UNLOCK();
    number(clid);
    binary(slotname);
    baseid(0);              //fv.hívás: clid a stackre
    number(slothashcode);
    extern void _clp___findslot3_s(int);
    _clp___findslot3_s(4);  
    SIGNAL_LOCK();
    MUTEX_LOCK_PTR(mutexptr);
    slotbuffer[clid%slotbuffersize].classid=clid;
    slotbuffer[clid%slotbuffersize].slotvalue=*TOP();
}

void _method5c_::findslot(int clid)
{
    MUTEX_UNLOCK_PTR(mutexptr);
    SIGNAL_UNLOCK();
    number(clid);
    binary(slotname);
    baseid(0);              //fv.hívás: clid a stackre
    number(slothashcode);
    extern void _clp___findslot3_c(int);
    _clp___findslot3_c(4);  
    SIGNAL_LOCK();
    MUTEX_LOCK_PTR(mutexptr);
    slotbuffer[clid%slotbuffersize].classid=clid;
    slotbuffer[clid%slotbuffersize].slotvalue=*TOP();
}

void _method5p_::findslot(int clid)
{
    MUTEX_UNLOCK_PTR(mutexptr);
    SIGNAL_UNLOCK();
    number(clid);
    binary(slotname);
    prntid(0);              //fv.hívás: clid a stackre
    baseid(0);              //fv.hívás: clid a stackre
    number(slothashcode);
    extern void _clp___findslot3_p(int);
    _clp___findslot3_p(5);  
    SIGNAL_LOCK();
    MUTEX_LOCK_PTR(mutexptr);
    slotbuffer[clid%slotbuffersize].classid=clid;
    slotbuffer[clid%slotbuffersize].slotvalue=*TOP();
}
 
 
//----------------------------------------------------------------------
void _method5_::eval(int argno)
{
    //stack: Obj A1 A2... Aargno-1 --- retval
    
    VALUE *base=stack-argno;  //object
    
    if( base->type!=TYPE_OBJECT )
    {
        error_obj(slotname,base,argno);
    }
    SIGNAL_LOCK();
    MUTEX_LOCK_PTR(mutexptr);

    int clid=base->data.object.subtype;
    int bufidx=clid%slotbuffersize;


    if( clid!=slotbuffer[bufidx].classid )
    {
        //printf("\n>>%d:%s %d/%d",clid,slotname,bufidx,slotbuffersize);
        findslot(clid); //virtual!

        //Ha findslot sikertelen, 
        //akkor Clipper runtime error keletkezik,
        //és ide már nem jön a vezérlés.
    }
    else
    {
        //printf(".");
        push(&slotbuffer[bufidx].slotvalue);
    }
    MUTEX_UNLOCK_PTR(mutexptr);
    SIGNAL_UNLOCK();

    
    //Ha a TOP-ban szám van, akkor az egy attribútum indexe.
    //Ha a TOP-ban kódblokk van, akkor azt ki kell értékelni.

    if( TOP()->type==TYPE_NUMBER )
    {
        //attribútum kiolvasás/felülírás
    
        unsigned int len=OBJECTLEN(base);
        unsigned int idx=(int)TOP()->data.number;

        if( (idx<1) || (len<idx) )
        {
            error_siz("_method_::eval",base,argno);
        }
    
        VALUE *v=OBJECTPTR(base)+idx-1;

        if( argno>1 ) //beírás
        {
            *v=*(base+1);
        }

        *base=*v;
        stack=base+1;
    }
    
    else if( TOP()->type==TYPE_BLOCK )
    {
        //method végrehajtás
        //a stacket eggyel feljebb kell hozni,
        //hogy a kódblokkot betehessük alulra
        
        VALUE blk=*TOP();
        int i;
        for( i=argno; i>0; i-- )
        {
            *(base+i)=*(base+i-1);
        }
        
        //ha most a base-be bemásoljuk a kódblokkot,
        //akkor a verem éppen olyan, mint _clp_eval-nál
        
        *base=blk;
        base->data.block.code(argno+1);
    }

    else
    {
        error_gen(CHRLIT("invalid slot type"),"_method_::eval",base,argno);
    }
}

//----------------------------------------------------------------------

