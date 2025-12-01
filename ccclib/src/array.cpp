
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

static const int EXTSIZ=4; //plusz elemek szama

DEFINE_METHOD(get);
DEFINE_METHOD(hashitem);

// A simplehash osztaly hashitem, get metodusat
// es a hashitemek {key,value} alakjat hasznalja ki
// az asszociativ tombindexeles: hash["key"]:=value.

//------------------------------------------------------------------------
VALUE *idxxl() // indexkifejezes a baloldalon
{
// stack: a,i --- a
// return: a[i] cime

    VALUE *i=TOP();
    VALUE *a=TOP2();

    if( (a->type==TYPE_ARRAY || a->type==TYPE_OBJECT) && i->type==TYPE_NUMBER )
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

        VALUE *item=TOP(); //item[2] cimet kell adni
        VALUE *x=ARRAYPTR(item)+1;
        return x;
    }

    error_arr("idxxl",a,2);
    return 0;
}

//------------------------------------------------------------------------
VALUE *idxxl0(double i) // indexkifejezes a baloldalon (konstans index)
{
// stack: a --- a
// return: a[i] cime

    VALUE *a=TOP();

    if( (a->type!=TYPE_ARRAY) && (a->type!=TYPE_OBJECT) )
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
void idxr() // indexkifejezes a jobboldalon
{
// stack: a,i --- a[i]

    VALUE *i=TOP();
    VALUE *a=TOP2();

    if( i->type==TYPE_NUMBER )
    {
        if( a->type==TYPE_ARRAY || a->type==TYPE_OBJECT )
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
            unsigned long len=STRINGLEN(a);
            unsigned long idx=D2ULONGX(i->data.number);
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
            binarysize_t len=BINARYLEN(a);
            binarysize_t idx=D2ULONGX(i->data.number);
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
void idxr0(double i) // indexkifejezes a jobboldalon (konstans index)
{
// stack: a --- a[i]

    VALUE *a=TOP();

    if( a->type==TYPE_ARRAY || a->type==TYPE_OBJECT )
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
        unsigned long len=STRINGLEN(a);
        unsigned long idx=D2ULONGX(i);
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
        binarysize_t len=BINARYLEN(a);
        binarysize_t idx=D2ULONGX(i);
        if( idx<1 || len<idx )
        {
            number((double)idx);
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
void idxr0nil(double i) // mint idxr0, csak tulindexelesre NIL-t ad
{
// stack: a --- a[i]

    VALUE *a=TOP();

    if( a->type==TYPE_ARRAY )
    {
        unsigned len=ARRAYLEN(a);
        unsigned idx=D2UINT(i);
        if( idx<1 || len<idx )
        {
            *TOP()=NIL;
        }
        else
        {
            *TOP()=*( ARRAYPTR(a)+idx-1 );
        }
    }

    else if( a->type==TYPE_STRING )
    {
        unsigned long len=STRINGLEN(a);
        unsigned long idx=D2ULONGX(i);
        if( idx<1 || len<idx )
        {
            *TOP()=NIL;
        }
        else
        {
            CHAR c=STRINGPTR(a)[idx-1];
            POP();
            *stringl(1)=c;
        }
    }

    else if( a->type==TYPE_BINARY )
    {
        binarysize_t len=BINARYLEN(a);
        binarysize_t idx=D2ULONGX(i);
        if( idx<1 || len<idx )
        {
            *TOP()=NIL;
        }
        else
        {
            BYTE c=BINARYPTR(a)[idx-1];
            POP();
            *binaryl(1)=c;
        }
    }

    else
    {
        error_arr("idxr0nil",a,1);
    }
}

//------------------------------------------------------------------------
void array(int len) //stackrol levett elemekkel inicializalt array
{
// stack: A1,A2,...,Alen --- A

    VALUE *base=stack-len;

    VALUE *valptr=0;
    if( len>0 )
    {
        valptr=newValue(len+1+EXTSIZ);
        arraycopy(valptr,base,len);
        (valptr+len)->type=TYPE_END;
        (valptr+len)->data.size=len+EXTSIZ;
    }
    VALUE v;
    v.type=TYPE_ARRAY;
    oref_new(&v,valptr,len); //PUSH
    *base=*TOP();
    stack=base+1;
}


//------------------------------------------------------------------------
VALUE *array0(int len) //NIL-ekkel inicializalt 1-dimenzios array
{
// stack: --- A

    VALUE *valptr=0;
    int length=len;
    if( len>0 )
    {
        valptr=newValue(len+1);
        (valptr+len)->type=TYPE_END;
        (valptr+len)->data.size=len;
        while(--len>=0) (valptr+len)->type=TYPE_NIL;
    }
    VALUE v;
    v.type=TYPE_ARRAY;
    oref_new(&v,valptr,length); //PUSH
    return valptr;
}

//------------------------------------------------------------------------
void _clp_array(int argno)
{
// stack: a1,a2,... --- A

    VALUE *base=stack-argno;
    VALUE *a=&NIL;

    // 0 db argumentum eseten
    // a visszateresi ertek NIL

    for( int i=1; i<=argno; i++ )
    {
        if( (base+argno-i)->type!=TYPE_NUMBER )
        {
            error_arg("array",base,argno);
        }
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

    _retv(a);
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

    int lkx=mark_lock(a);

    VALUE *p_old=ARRAYPTR(a);
    int len_old=ARRAYLEN(a);
    int len_ext=p_old?(p_old+len_old)->data.size:0;
    int len_new=len_old+1;

    if( len_new<=len_ext )
    {
        //helyben marad
        valuecopy(p_old+len_new,p_old+len_old); // TYPE_END first!
        valuecopy(p_old+len_old,v);
        ARRAYLEN(a)=len_new;
    }
    else
    {
        //uj buffer
        VALUE *p_new=newValue(len_new+1+EXTSIZ);
        arraycopy(p_new,p_old,len_old);
        valuecopy(p_new+len_old,v);
        (p_new+len_new)->type=TYPE_END;
        (p_new+len_new)->data.size=len_new+EXTSIZ;
        ARRAYPTR(a)=p_new;
        ARRAYLEN(a)=len_new;

        if( p_old )
        {
            deleteValue(p_old);
        }
    }

    mark_unlock(lkx);
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
    VALUE *arr=base;
    VALUE *len=base+1;

    if( arr->type!=TYPE_ARRAY || len->type!=TYPE_NUMBER )
    {
        error_arg("asize",base,2);
    }

    int lkx=mark_lock(arr);

    VALUE *p_old=ARRAYPTR(arr);
    int len_old=ARRAYLEN(arr);

    VALUE *p_new;
    int len_new=D2INT(len->data.number);
    int len_ext=p_old?((p_old+len_old)->data.size):0;

    if( p_old && len_new && (len_new<=len_ext) && ((len_ext-len_new)<(EXTSIZ<<2)) )
    {
        //helyben marad

        (p_old+len_new)->type=TYPE_END; //atomi
        (p_old+len_new)->data.size=len_ext; //nem valtozik, csak uj helyen taroljuk
        int i;
        for( i=len_new-1; len_old<=i; i-- )
        {
            (p_old+i)->type=TYPE_NIL; //atomi
        }
        ARRAYLEN(arr)=len_new;
    }
    else
    {
        //uj buffer
        //nem kell uj oref

        if( len_new>0 )
        {
            p_new=newValue(len_new+1+EXTSIZ);
            arraycopy(p_new,p_old,min(len_old,len_new));
            for(int i=len_old; i<len_new; i++ )
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
        ARRAYPTR(arr)=p_new;
        ARRAYLEN(arr)=len_new;

        if( p_old )
        {
            deleteValue(p_old);
        }
    }

    mark_unlock(lkx);
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
    int lkx=mark_lock(a);
    arraycopy(ptr+pos,ptr+pos-1,len-pos);
    (ptr+pos-1)->type=TYPE_NIL;
    mark_unlock(lkx);
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
    int lkx=mark_lock(a);
    arraycopy(ptr+pos-1,ptr+pos,len-pos);
    (ptr+len-1)->type=TYPE_NIL;
    mark_unlock(lkx);
//
*base=*a;
stack=base+1;
pop_call();
}

//------------------------------------------------------------------------
void _clp_aclone(int argno) // deep clone
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
void _clp_atail(int argno) // atail(arr)
{
    CCC_PROLOG("atail",1);
    VALUE *a=_para(1);
    unsigned len=_paralen(1);
    if( len>0 )
    {
        _retv(a+len-1);
    }
    else
    {
        _ret(); //NIL
    }
    CCC_EPILOG();
}


//------------------------------------------------------------------------
