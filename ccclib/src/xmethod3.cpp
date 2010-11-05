
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


//----------------------------------------------------------------------
_method3_::_method3_(const char *sname)
{
    classid=0;
    slotname=sname; 
    slothashcode=hashcode(sname);
    slot.type=TYPE_NIL;
    MUTEX_INIT(mutex);
};


_method3s_::_method3s_(const char *sname, CLASSID *bid) : _method3_(sname)
{
    baseid=bid; 
};


_method3c_::_method3c_(const char *sname, CLASSID *bid) : _method3_(sname)
{
    baseid=bid; 
};


_method3p_::_method3p_(const char *sname, CLASSID *pid, CLASSID *bid) : _method3_(sname)
{
    prntid=pid; 
    baseid=bid; 
};


//----------------------------------------------------------------------
void _method3_::findslot(int clid)
{
    MUTEX_UNLOCK(mutex);
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
    MUTEX_LOCK(mutex);
    classid=clid;
    slot=*TOP();
}

void _method3s_::findslot(int clid)
{
    MUTEX_UNLOCK(mutex);
    SIGNAL_UNLOCK();
    number(clid);
    binary(slotname);
    baseid(0);              //fv.hívás: clid a stackre
    number(slothashcode);
    extern void _clp___findslot3_s(int);
    _clp___findslot3_s(4);  
    SIGNAL_LOCK();
    MUTEX_LOCK(mutex);
    classid=clid;
    slot=*TOP();
}

void _method3c_::findslot(int clid)
{
    MUTEX_UNLOCK(mutex);
    SIGNAL_UNLOCK();
    number(clid);
    binary(slotname);
    baseid(0);              //fv.hívás: clid a stackre
    number(slothashcode);
    extern void _clp___findslot3_c(int);
    _clp___findslot3_c(4);  
    SIGNAL_LOCK();
    MUTEX_LOCK(mutex);
    classid=clid;
    slot=*TOP();
}

void _method3p_::findslot(int clid)
{
    MUTEX_UNLOCK(mutex);
    SIGNAL_UNLOCK();
    number(clid);
    binary(slotname);
    prntid(0);              //fv.hívás: clid a stackre
    baseid(0);              //fv.hívás: clid a stackre
    number(slothashcode);
    extern void _clp___findslot3_p(int);
    _clp___findslot3_p(5);  
    SIGNAL_LOCK();
    MUTEX_LOCK(mutex);
    classid=clid;
    slot=*TOP();
}
 
 
//----------------------------------------------------------------------
void _method3_::eval(int argno)
{
    //stack: Obj A1 A2... Aargno-1 --- retval
    
    VALUE *base=stack-argno;  //object
    
    if( base->type!=TYPE_OBJECT )
    {
        error_obj(slotname,base,argno);
    }

    SIGNAL_LOCK();
    MUTEX_LOCK(mutex);
    if( base->data.object.subtype!=classid )
    {
        findslot(base->data.object.subtype); //virtual!

        //Ha findslot sikertelen, 
        //akkor Clipper runtime error keletkezik,
        //és ide már nem jön a vezérlés.
    }
    else
    {
        push(&slot);
    }
    MUTEX_UNLOCK(mutex);
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

