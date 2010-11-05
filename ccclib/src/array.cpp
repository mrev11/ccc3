
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

#include <stdio.h>
#include <stdlib.h>
#include <cccapi.h>

static const int EXTSIZ=4; //plusz elemek száma

DEFINE_METHOD(get);
DEFINE_METHOD(hashitem);

// A simplehash osztály hashitem, get metódusit
// és a hashitemek {key,value} alakját használja ki
// az asszociatív tömbindexelés: hash["key"]:=value.
 
//------------------------------------------------------------------------
VALUE *idxl() // (obsolete) indexkifejezés a baloldalon
{
// stack: a,i ---
// return: a[i] címe

    VALUE *i=TOP();
    VALUE *a=TOP2();

    if( a->type==TYPE_ARRAY && i->type==TYPE_NUMBER ) 
    {
        unsigned int len=ARRAYLEN(a);
        unsigned int idx=D2INT(i->data.number);

        if( (idx<1) || (len<idx) )
        {
            error_idx("idxl",a,2);
        }
        
        VALUE *x=ARRAYPTR(a)+idx-1;
        POP();
        POP();
        return x;

        //MEGJEGYZÉS: array(1)[1]:=x nem thread safe
        //(nem javítható, de szerencsére nincs értelme)
    }

    else if( a->type==TYPE_OBJECT && (i->type==TYPE_STRING || i->type==TYPE_BINARY ) )
    {
        _o_method_hashitem.eval(2); //stack: item={key,value/NIL}

        VALUE *item=TOP(); //item[2] címét kell adni
        VALUE *x=ARRAYPTR(item)+1;
        POP();
        return x;

        //MEGJEGYZÉS: simplehashNew()[key]:=x nem thread safe
        //(nem javítható, de szerencsére nincs értelme)
    }

    error_arr("idxl",a,2);
    return 0;
}

//------------------------------------------------------------------------
VALUE *idxl0(double i) // (obsolete) indexkifejezés a baloldalon (konstans index)
{
// stack: a ---
// return: a[i] címe

    VALUE *a=TOP();

    if( a->type!=TYPE_ARRAY ) 
    {
        error_arr("idxl0",a,1);
    }

    unsigned int len=ARRAYLEN(a);
    unsigned int idx=D2INT(i);
    
    if( (idx<1) || (len<idx) )
    {
        number(i);
        error_idx("idxl0",a,2);
        POP();
    }
    
    VALUE *x=ARRAYPTR(a)+idx-1;
    POP();
    return x;

    //MEGJEGYZÉS: array(1)[1]:=x nem thread safe
    //(nem javítható, de szerencsére nincs értelme)
}

//------------------------------------------------------------------------
VALUE *idxxl() // indexkifejezés a baloldalon
{
// stack: a,i --- a
// return: a[i] címe

    VALUE *i=TOP();
    VALUE *a=TOP2();

    if( a->type==TYPE_ARRAY && i->type==TYPE_NUMBER ) 
    {
        unsigned int len=ARRAYLEN(a);
        unsigned int idx=D2INT(i->data.number);

        if( (idx<1) || (len<idx) )
        {
            error_idx("idxxl",a,2);
        }
        
        VALUE *x=ARRAYPTR(a)+idx-1;
        POP();
        return x;
    }

    else if( a->type==TYPE_OBJECT && (i->type==TYPE_STRING || i->type==TYPE_BINARY ) )
    {
        _o_method_hashitem.eval(2); //stack: item={key,value/NIL}

        VALUE *item=TOP(); //item[2] címét kell adni
        VALUE *x=ARRAYPTR(item)+1;
        return x;
    }

    error_arr("idxxl",a,2);
    return 0;
}

//------------------------------------------------------------------------
VALUE *idxxl0(double i) // indexkifejezés a baloldalon (konstans index)
{
// stack: a --- a
// return: a[i] címe

    VALUE *a=TOP();

    if( a->type!=TYPE_ARRAY ) 
    {
        error_arr("idxxl0",a,1);
    }

    unsigned int len=ARRAYLEN(a);
    unsigned int idx=D2INT(i);
    
    if( (idx<1) || (len<idx) )
    {
        number(i);
        error_idx("idxxl0",a,2);
        POP();
    }
    
    VALUE *x=ARRAYPTR(a)+idx-1;
    return x;
}

//------------------------------------------------------------------------
void idxr() // indexkifejezés a jobboldalon
{
// stack: a,i --- a[i]

    VALUE *i=TOP();
    VALUE *a=TOP2();
    
    if( i->type==TYPE_NUMBER )
    {
        if( a->type==TYPE_ARRAY )
        {
            unsigned len=ARRAYLEN(a);
            unsigned idx=D2UINT(i->data.number);
            if( idx<1 || len<idx )
            {
                error_idx("idxr",a,2);
            }
            POP();    
            *TOP()=*(ARRAYPTR(a)+idx-1);
        }

        else if( a->type==TYPE_STRING )
        {
            unsigned len=STRINGLEN(a);
            unsigned idx=D2UINT(i->data.number);
            if( idx<1 || len<idx )
            {
                error_idx("idxr",a,2);
            }
            CHAR c=STRINGPTR(a)[idx-1];
            POP();
            POP();
            *stringl(1)=c;
        }

        else if( a->type==TYPE_BINARY)
        {
            unsigned len=BINARYLEN(a);
            unsigned idx=D2UINT(i->data.number);
            if( idx<1 || len<idx )
            {
                error_idx("idxr",a,2);
            }
            BYTE c=BINARYPTR(a)[idx-1];
            POP();
            POP();
            *binaryl(1)=c;
        }
        else
        {
            error_arr("idxr",a,2);
        }
    }

    else if( a->type==TYPE_OBJECT && (i->type==TYPE_STRING || i->type==TYPE_BINARY ) )
    {
        _o_method_get.eval(2);
    }

    else
    {
        error_arr("idxr",a,2);
    }
}

//------------------------------------------------------------------------
void idxr0(double i) // indexkifejezés a jobboldalon (konstans index)
{
// stack: a --- a[i]

    VALUE *a=TOP();
    
    if( a->type==TYPE_ARRAY )
    {
        unsigned len=ARRAYLEN(a);
        unsigned idx=D2UINT(i);
        if( idx<1 || len<idx )
        {
            number(idx);
            error_idx("idxr0",a,2);
        }
        *TOP()=*( ARRAYPTR(a)+idx-1 );
    }

    else if( a->type==TYPE_STRING )
    {
        unsigned len=STRINGLEN(a);
        unsigned idx=D2UINT(i);

        if( idx<1 || len<idx )
        {
            number(idx);
            error_idx("idxr0",a,2);
        }
        CHAR c=STRINGPTR(a)[idx-1];
        POP();
        *stringl(1)=c;
    }

    else if( a->type==TYPE_BINARY )
    {
        unsigned len=BINARYLEN(a);
        unsigned idx=D2UINT(i);
        if( idx<1 || len<idx )
        {
            number(idx);
            error_idx("idxr0",a,2);
        }
        BYTE c=BINARYPTR(a)[idx-1];
        POP();
        *binaryl(1)=c;
    }

    else
    {
        error_arr("idxr0",a,1);
    }
}

//------------------------------------------------------------------------
void array(int len) //stackről levett elemekkel inicializált array
{
// stack: A1,A2,...,Alen --- A

    VALUE *base=stack-len;

    VARTAB_LOCK();

    OREF *o=oref_new();
    o->length=len;
    if( len>0 )
    {
        VALUE *p=newValue(len+1+EXTSIZ);
        o->ptr.valptr=p;
        (p+len)->type=TYPE_END;
        (p+len)->data.size=len+EXTSIZ;
        while(--len>=0) *(p+len)=*(base+len);
    }
    else
    {
        o->ptr.valptr=NULL;
    }
    o->next=NEXT_RESERVED;

    stack=base;
    PUSHNIL();
    base->data.array.oref=o;
    base->type=TYPE_ARRAY;

    VARTAB_UNLOCK();
}


//------------------------------------------------------------------------
VALUE *array0(int len) //NIL-ekkel inicializált 1-dimenziós array
{
// stack: --- A

    VARTAB_LOCK();

    OREF *o=oref_new();
    o->length=len;
    if( len>0 )
    {
        VALUE *p=newValue(len+1);
        o->ptr.valptr=p;
        (p+len)->type=TYPE_END;
        (p+len)->data.size=len; 
        while(--len>=0) (p+len)->type=TYPE_NIL;
    }
    else 
    {
        o->ptr.valptr=NULL;
    }
    o->next=NEXT_RESERVED;
 
    VALUE *v=PUSHNIL();
    v->data.array.oref=o;
    v->type=TYPE_ARRAY;

    VARTAB_UNLOCK();
    return o->ptr.valptr;
}

//------------------------------------------------------------------------
#ifdef HASZNALATON_KIVUL

VALUE *array0x(int len) //mint array0, de EXTSIZ hozzáadásával

// Jelenleg ez használaton kívül van.
// Az array-k a megadott mérettel jönnek létre,
// és csak akkor lesz tartalék bufferük, 
// ha a program elkezdi változtatgani a méretüket
// aadd()-dal vagy asize()-zal.
//
// Ha ezt a függvényt tennénk array0() helyére,
// akkor az objectek is EXTSIZ bufferrel jönnének létre,
// ami felesleges, mert az objectek mérete nem változik.
//
// A blockok mérete sem változik. A blockok saját kóddal 
// rendezkednek be a block-array-ben (EXTSIZ nélkül).
//
// A TYPE_END típusú záró elemnél minden esetben be kell
// állítani az array kiterjesztett méretét, objecteknél és
// blockoknál is. Ez kell az object->array konverziónál.
//
// A szemétgyűjtés a gráf bejárásakor nem használja az
// array-k hosszadatát, hanem a TYPE_END elemeket nézi.

{
// stack: --- A

    VARTAB_LOCK();

    OREF *o=oref_new();
    o->length=len;
    if( len>0 )
    {
        VALUE *p=newValue(len+1+EXTSIZ);
        o->ptr.valptr=p;
        (p+len)->type=TYPE_END;
        (p+len)->data.size=len+EXTSIZ; 
        while(--len>=0) (p+len)->type=TYPE_NIL;
    }
    else 
    {
        o->ptr.valptr=NULL;
    }
    o->next=NEXT_RESERVED;
 
    VALUE *v=PUSHNIL();
    v->data.array.oref=o;
    v->type=TYPE_ARRAY;

    VARTAB_UNLOCK();
    return o->ptr.valptr;
}

#endif 

//------------------------------------------------------------------------
void _clp_array(int argno)
{
// stack: a1,a2,... --- A

    VALUE *base=stack-argno;
    VALUE *a=&NIL;
    
    // 0 db argumentum esetén 
    // a visszatérési érték NIL
    
    for( int i=1; i<=argno; i++ )
    {
        int dim=max(D2INT((base+argno-i)->data.number),0);
        
        if( i<=1 )
        {
            array0(dim);
        }
        else
        {
            for( int j=1; j<dim; j++)
            {
                PUSH(a);
                _clp_aclone(1);
            }
            array(dim);
        }
        a=TOP();
    }

    //ROSSZ!
    //stack=base;
    //PUSH(a);     

    _retv(a);  //2004.10.31
}

//------------------------------------------------------------------------
void _clp_aadd(int argno) // aadd(a,v)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
push_call("aadd",base);
//
    VALUE *a=base;     
    VALUE *v=base+1;

    if( a->type!=TYPE_ARRAY )
    {
        error_arg("aadd",base,2);
    }

    VALUE *p_old=ARRAYPTR(a); //(NULL?)
    int len_old=ARRAYLEN(a);
    int len_ext=p_old?(p_old+len_old)->data.size:0;
    int len_new=len_old+1;
    
    if( len_new<=len_ext )
    {
        //helyben marad

        *(p_old+len_new)=*(p_old+len_old); //TYPE_END elem
        *(p_old+len_old)=*v;
        ARRAYLEN(a)=len_new;
    }
    else
    {
        //új buffer
 
        VARTAB_LOCK();
 
        VALUE *p_new=newValue(len_new+1+EXTSIZ);

        (p_new+len_new)->type=TYPE_END;
        (p_new+len_new)->data.size=len_new+EXTSIZ; 
        *(p_new+len_old)=*v;
        //while(--len_old>=0) *(p_new+len_old)=*(p_old+len_old);
        valuemove(p_new,p_old,len_old);

        if( p_old )
        {
            deleteValue(p_old);
        }
        ARRAYPTR(a)=p_new;
        ARRAYLEN(a)=len_new;

        VARTAB_UNLOCK();
    }
//
*base=*v;
stack=base+1;
pop_call();
}


//------------------------------------------------------------------------
void _clp_asize(int argno) // asize(arr,len)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
push_call("asize",base);
//
    VALUE *a=base;     
    VALUE *l=base+1;

    if( a->type!=TYPE_ARRAY || l->type!=TYPE_NUMBER )
    {
        error_arg("asize",base,2);
    }

    VALUE *p_new;
    VALUE *p_old=ARRAYPTR(a); //(NULL?)
    int len_old=ARRAYLEN(a);
    int len_new=D2INT(l->data.number);
    int len_ext=p_old?((p_old+len_old)->data.size):0;

    if( p_old && len_new && (len_new<=len_ext) && ((len_ext-len_new)<(EXTSIZ<<2)) ) 
    {
        //helyben marad

        (p_old+len_new)->type=TYPE_END; //atomi
        (p_old+len_new)->data.size=len_ext; //nem változik, csak új helyen tároljuk
        int i;
        for( i=len_new-1; len_old<=i; i-- )
        {
            (p_old+i)->type=TYPE_NIL; //atomi
        }
        ARRAYLEN(a)=len_new;
    }
    else
    {
        //új buffer
 
        VARTAB_LOCK();
 
        if( len_new>0 )
        {
            int i;

            p_new=newValue(len_new+1+EXTSIZ);
    
            //for(i=0; i<len_old && i<len_new; i++ )
            //{
            //    *(p_new+i)=*(p_old+i);
            //}
            valuemove(p_new,p_old,i=min(len_old,len_new));
    
            for( ; i<len_new; i++ )
            {
                (p_new+i)->type=TYPE_NIL;
            }

            (p_new+len_new)->type=TYPE_END;
            (p_new+len_new)->data.size=len_new+EXTSIZ;
        }
        else
        {
            p_new=NULL;
            len_new=0;
        }
      
        if( p_old )
        {
            deleteValue(p_old);
        }

        ARRAYPTR(a)=p_new;
        ARRAYLEN(a)=len_new;

        VARTAB_UNLOCK();
    }
//
stack=base+1;
pop_call();
}

//------------------------------------------------------------------------
void _clp_ains(int argno) // ains(arr,pos)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
push_call("ains",base);
//
    VALUE *a=base;     
    VALUE *p=base+1;

    if( a->type!=TYPE_ARRAY || p->type!=TYPE_NUMBER )
    {
        error_arg("ains",base,2);
    }

    unsigned int pos=D2INT(p->data.number);
    unsigned int len=ARRAYLEN(a);
    
    if( (pos<1) || (len<pos) )
    {
        error_idx("ains",base,2);
    }

    VALUE *ptr=ARRAYPTR(a); 
    unsigned int i;

    //for( i=len-1; i>=pos; i-- )
    //{
    //    *(ptr+i)=*(ptr+i-1);
    //}
    valuemove(ptr+pos,ptr+pos-1,len-pos);
    *(ptr+pos-1)=NIL;
//
*base=*a;
stack=base+1;
pop_call();
}


//------------------------------------------------------------------------
void _clp_adel(int argno) // adel(arr,pos)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
push_call("adel",base);
//
    VALUE *a=base;     
    VALUE *p=base+1;

    if( a->type!=TYPE_ARRAY || p->type!=TYPE_NUMBER )
    {
        error_arg("adel",base,2);
    }

    unsigned int len=ARRAYLEN(a);
    unsigned int pos=D2INT(p->data.number);
    
    if( (pos<1) || (len<pos) )
    {
        error_idx("adel",base,2);
    }

    VALUE *ptr=ARRAYPTR(a); 
    unsigned int i;

    //for( i=pos; i<len; i++ )
    //{
    //    *(ptr+i-1)=*(ptr+i);
    //}
    valuemove(ptr+pos-1,ptr+pos,len-pos);
    *(ptr+len-1)=NIL;
//
*base=*a;
stack=base+1;
pop_call();
}

//------------------------------------------------------------------------
void _clp_aclone(int argno) // aclone(arr)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
push_call("aclone",base);
//
    VALUE *a=base;     

    if( a->type!=TYPE_ARRAY )
    {
        error_arg("aclone",base,1);
    }
    
    unsigned int len=ARRAYLEN(a);
    VALUE *p_old=ARRAYPTR(a);
    VALUE *p_new=array0(len);

    VALUE *an=TOP();
    unsigned int i;
    
    for( i=0; i<len; i++ )
    {
        if( (p_old+i)->type==TYPE_ARRAY )
        {
            PUSH(p_old+i);
            _clp_aclone(1);
            *(p_new+i)=*TOP();
            POP();
        }
        else
        {
            *(p_new+i)=*(p_old+i);
        }
    }
//
*base=*an;
stack=base+1;
pop_call();
}


//------------------------------------------------------------------------
void _clp_asort(int argno) // asort(arr,[st],[cn],[blk])
{
VALUE *base=stack-argno;
stack=base+min(argno,4);
while(stack<base+4)PUSHNIL();
push_call("asort",base);
//
    VALUE *a=base;     
    VALUE *s=base+1;     
    VALUE *c=base+2;     
    VALUE *b=base+3;     

    if( a->type!=TYPE_ARRAY )
    {
        error_arg("asort",base,4);
    }
    
    if( s->type==TYPE_NIL )
    {
        *s=ONE;
    }

    if( c->type==TYPE_NIL )
    {
        push_symbol(a);
        _clp_len(1);
        *c=*TOP();
        POP();
    }

    if( b->type==TYPE_NIL )
    {
        _clp__asort_ascendblock(0);
        *b=*TOP();
        POP();
    }

    if( s->type!=TYPE_NUMBER ||  c->type!=TYPE_NUMBER || b->type!=TYPE_BLOCK )
    {
        error_arg("asort",base,4);
    }

    unsigned int len=ARRAYLEN(a);
    unsigned int st=D2INT(s->data.number);
    unsigned int cn=D2INT(c->data.number);
    VALUE *p=ARRAYPTR(a);

    push_symbol(b); 
    // qsort alatt az összehasonlító block van a stack tetején,
    // ezt a compare használja két array elem összehasonlítására

    //debug("qsort hívás előtt");
    //qsort(p+st-1,min(cn,len-st+1),sizeof(VALUE),valuecompare);
    valuesort(p+st-1,min(cn,len-st+1));
    //debug("qsort hívás után");
//
*base=*a;
stack=base+1;
pop_call();
}

//------------------------------------------------------------------------
int valuecompare(const void *x, const void *y)
{
#ifdef MULTITHREAD
    //Miközben qsort meghívja az összehasonlítást,
    //engedni kell a szemétgyűjtést, máskülönben deadlock keletkezik,
    //ha az összehasonlító bokkban objektumok is készülnek.
    if( thread_data::tdata_count>1 )    
    {
        thread_data_ptr->unlock();
    }
#endif    

    SIGNAL_UNLOCK();
    
    //TOP=összehasonlító block
    //stack változatlan marad

    // Az összehasonlítást két irányban is el kell végezni,
    // hogy detektálható legyen az egyenlő eset. A Clipperben
    // megadható kódblock nem szimmetrikus (csak T/F-et ad),
    // és ezért az egyenő elemeket tartalmazó array-re a qsort
    // nem mindig tud lefutni, ha csak -1/1-et adogatunk neki.
    // így is baj lehet a Clipper string összehasonlítasa miatt.

    //egyik irány
    DUP();
    push_symbol((VALUE*)x);
    push_symbol((VALUE*)y);
    _clp_eval(3);
    int f1=flag();

    //másik irány
    DUP();
    push_symbol((VALUE*)y);
    push_symbol((VALUE*)x);
    _clp_eval(3);
    int f2=flag();

    SIGNAL_LOCK();

#ifdef MULTITHREAD
    if( thread_data::tdata_count>1 )    
    {
        thread_data_ptr->lock();
    }
#endif    

    return (f1==f2)?0:(f1?-1:1);
}

//------------------------------------------------------------------------

