
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

MUTEX_CREATE(mutex);

static VALUE **slotbuffer=0;
static unsigned slotbuffer_size=0;
static unsigned *slotbuffer_rowsize=0;
static hashtable_simple *global_slothash=new hashtable_simple();

//#define DEBUG

//----------------------------------------------------------------------
static void bye()
{
    printf("\n----------------------------------------------------------------");

    unsigned sx=0,s0=0;

    hashitem *item=global_slothash->first();
    while(item)
    {
        unsigned slotid=item->value.value_unsigned;
        printf("\n> %-32s%5d",item->key,slotid);

        int x=0;
        for(unsigned clid=1; clid<=slotbuffer_rowsize[slotid-1]; clid++)
        {
            VALUE *slot=slotbuffer[slotid-1]+clid-1;
            if( slot->type!=0 )
            {
                x++;
                printf(" %d(%c)",clid,'@'+(slot->type%21)); //A:attr, M:meth
            }
        }

        //printf(" %4d/%d",x,slotbuffer_rowsize[slotid-1]);
        s0+=slotbuffer_rowsize[slotid-1];
        sx+=x;

        item=global_slothash->next();
    }
    
    printf("\n----------------------------------------------------------------");
    printf("\ntotal %d/%d %f\n",sx,s0,(double)sx/s0);
    printf("\n");
}


//----------------------------------------------------------------------
static unsigned global_cache_set(const char *xslotname, unsigned clid)
{
    SIGNAL_LOCK();
    MUTEX_LOCK(mutex);

  #ifdef DEBUG
    static int atx=atexit(bye);
  #endif
    static unsigned slotcounter=0;
    
    unsigned slotid=global_slothash->get(xslotname).value_unsigned;
    if( slotid==0 )
    {
        hashvalue value;
        value.value_unsigned=++slotcounter;
        global_slothash->add(xslotname,value);
        slotid=value.value_unsigned;
    }

    //printf("\n>>%s slotid=%d clid=%d",xslotname,slotid,clid);fflush(0);

    if( slotbuffer_size<slotid  )
    {   
        //printf("R");fflush(0);

        unsigned oldsize=slotbuffer_size;
        unsigned newsize=slotid+100;  //legalabb

        slotbuffer=(VALUE**)realloc(slotbuffer,newsize*sizeof(void*));
        memset(slotbuffer+oldsize,0,(newsize-oldsize)*sizeof(void*));

        slotbuffer_rowsize=(unsigned*)realloc(slotbuffer_rowsize,newsize*sizeof(unsigned));
        memset(slotbuffer_rowsize+oldsize,0,(newsize-oldsize)*sizeof(unsigned));

        slotbuffer_size=newsize;
    }

    
    //slotbuffer_size               : sorok szama (ennyi slot lehet nyilvantartva)
    //slotbuffer[slotid-1]          : pointer a slotid sorra (VALUE bufferre)
    //slotbuffer_rowsize[slotid-1]  : slotid sor hossza

    if( slotbuffer_rowsize[slotid-1]<clid)
    {
        //printf("r");fflush(0);

        unsigned oldsize=slotbuffer_rowsize[slotid-1];
        unsigned newsize=clid;  //legalabb

        slotbuffer[slotid-1]=(VALUE*)realloc(slotbuffer[slotid-1],newsize*sizeof(VALUE));
        memset(slotbuffer[slotid-1]+oldsize,0,(newsize-oldsize)*sizeof(VALUE));

        slotbuffer_rowsize[slotid-1]=newsize;
    } 

    slotbuffer[slotid-1][clid-1]=*TOP(); //beteszi a cache-be

    MUTEX_UNLOCK(mutex);
    SIGNAL_UNLOCK();
    return slotid;
}

//----------------------------------------------------------------------
static int global_cache_get(unsigned slotid, unsigned clid)
{
    int success=0;
    SIGNAL_LOCK();
    MUTEX_LOCK(mutex);
    if( slotbuffer_size>=slotid && slotbuffer_rowsize[slotid-1]>=clid )
    {
        VALUE *slot=slotbuffer[slotid-1]+clid-1;  
        if( slot->type!=TYPE_NIL )
        {
            //printf(".");
            push(slot);
            success=1;
        }
    }
    MUTEX_UNLOCK(mutex);
    SIGNAL_UNLOCK();
    return success;   
}

//----------------------------------------------------------------------
//----------------------------------------------------------------------
_method6_::_method6_(const char *sname)
{
    slotid=0; 
    slotname=sname; 
    xslotname=sname; 
};


_method6s_::_method6s_(const char *sname, CLASSID *bid) : _method6_(sname)
{
    baseid=bid; 
    char buf[1024];
    sprintf(buf,"(super@%p)%s",baseid,slotname);
    xslotname=strdup(buf);
};


_method6c_::_method6c_(const char *sname, CLASSID *bid) : _method6_(sname)
{
    baseid=bid; 
    char buf[1024];
    sprintf(buf,"(%p)%s",baseid,slotname);
    xslotname=strdup(buf);

    //baseid pointer a _clp_<classname>class fuggvenyre
    //baseid() a stackre tenne az osztalyazonositot
    //jelenleg azonban ezt meg nem lehet hasznalni
    //mert a c++ kulso static objektumok inicializalasakor
    //nem letezik meg a CCC futtatokornyezet
    //ezert magabol a pointerbol keszul a hash kulcs
};


_method6p_::_method6p_(const char *sname, CLASSID *pid, CLASSID *bid) : _method6_(sname)
{
    prntid=pid; 
    baseid=bid; 
    char buf[1024];
    sprintf(buf,"(%p@%p)%s",prntid,baseid,slotname);
    xslotname=strdup(buf);
};


//----------------------------------------------------------------------
void _method6_::findslot(int clid)
{
    number(clid);
    binary(slotname);
    number(hashcode(slotname));
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
}

void _method6s_::findslot(int clid)
{
    number(clid);
    binary(slotname);
    baseid(0);              //fv.hívás: clid a stackre
    number(hashcode(slotname));
    extern void _clp___findslot3_s(int);
    _clp___findslot3_s(4);  
}

void _method6c_::findslot(int clid)
{
    number(clid);
    binary(slotname);
    baseid(0);              //fv.hívás: clid a stackre
    number(hashcode(slotname));
    extern void _clp___findslot3_c(int);
    _clp___findslot3_c(4);  
}

void _method6p_::findslot(int clid)
{
    number(clid);
    binary(slotname);
    prntid(0);              //fv.hívás: clid a stackre
    baseid(0);              //fv.hívás: clid a stackre
    number(hashcode(slotname));
    extern void _clp___findslot3_p(int);
    _clp___findslot3_p(5);  
}
 
 
//----------------------------------------------------------------------
void _method6_::eval(int argno)
{
    //stack: Obj A1 A2... Aargno-1 --- retval

    VALUE *base=stack-argno;  //object
    if( base->type!=TYPE_OBJECT )
    {
        error_obj(slotname,base,argno);
    }

    int clid=base->data.object.subtype;

    if( (slotid==0) || !global_cache_get(slotid,clid) )
    {
        findslot(clid); //virtual!

        //Ha findslot sikertelen, 
        //akkor Clipper runtime error keletkezik,
        //és ide már nem jön a vezérlés.

        //Ha findslot sikeres, 
        //akkor a slot value a stacken
        
        slotid=global_cache_set(xslotname,clid); 
        //betette a cache-be, slot a TOP-on
    }


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

