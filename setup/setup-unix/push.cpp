
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
#include <cccapi.h>

//------------------------------------------------------------------------
void push(VALUE *v)
{
    PUSH(v);
}

//------------------------------------------------------------------------
void push_symbol(VALUE *v)  // feltételes deref 
{
    PUSH( (v->type!=TYPE_REF) ? v : &(v->data.vref->value) );
}

//------------------------------------------------------------------------
void push_blkenv(VALUE *v) // mindig deref
{
    PUSH( &(v->data.vref->value) );
}

//------------------------------------------------------------------------
void push_symbol_ref(VALUE *v) // @ par, blokk környezet
{
    if( v->type!=TYPE_REF )
    {
        VARTAB_LOCK();
        VREF *vr=vref_new();
        vr->value=*v;
        vr->next=NEXT_RESERVED;
        v->data.vref=vr;
        v->type=TYPE_REF;
        VARTAB_UNLOCK();
    }
    PUSH(v);
}

//------------------------------------------------------------------------
void pop()
{
    --stack;
}

//------------------------------------------------------------------------
void dup()
{
    DUP();
}

//------------------------------------------------------------------------
void swap()
{
    DUP();
    *TOP2()=*TOP3();
    *TOP3()=*TOP();
    POP();
}

//------------------------------------------------------------------------
void assign(VALUE *lside)
{
    if( lside->type!=TYPE_REF )
    {
        *lside=*TOP();
    }
    else
    {
        lside->data.vref->value=*TOP();
    }
}

//------------------------------------------------------------------------
void assign2(VALUE *lside) //tömbindexeléshez
{
    if( lside->type!=TYPE_REF )
    {
        *lside=*TOP2();
    }
    else
    {
        lside->data.vref->value=*TOP2();
    }
    POP();
}

//------------------------------------------------------------------------
void block(void (*code)(int), int len)
{
    if( 0<len )
    {
        VALUE *base=stack-len;

        VARTAB_LOCK();
        OREF *orp=oref_new();
        VALUE *p=newValue(len+1);
        orp->length=len;
        orp->ptr.valptr=p;
        (p+len)->type=TYPE_END;
        (p+len)->data.size=len;
        while(--len>=0) *(p+len)=*(base+len);
        orp->next=NEXT_RESERVED;
 
        stack=base;
        PUSHNIL();
        base->data.block.oref=orp;
        base->data.block.code=code;
        base->type=TYPE_BLOCK;
        VARTAB_UNLOCK();
    }
    else
    {
        VALUE *base=PUSHNIL();
        base->data.block.code=code;
        base->data.block.oref=NULL;
        base->type=TYPE_BLOCK;
    }
}

//------------------------------------------------------------------------
VALUE *blkenv(VALUE *blk)
{
    // ezt az oref-et csak a blokkok használják,
    // nemlétező oref-re csak akkor lehet hivatkozás,
    // ha rossz a fordító, ezért nem kell vizsgálni
    // (esetleg run time errort lehet generálni)
    
    return blk->data.block.oref->ptr.valptr;
}

//------------------------------------------------------------------------
void number(double num)
{
    VALUE *v=PUSHNUM();
    v->data.number=num;
}

//------------------------------------------------------------------------
void logical(int flag)
{
    VALUE *v=PUSHFLG();
    v->data.flag=(flag!=0);
}


//------------------------------------------------------------------------
void date(long ldate)
{
    VALUE *v=PUSHDAT();
    v->data.date=ldate;
}

//------------------------------------------------------------------------
void pointer(void *ptr)
{
    VALUE *v=PUSHPTR();
    v->data.pointer=ptr;
}

//------------------------------------------------------------------------
VALUE prototype_object(void)
{
    //stack: clid --- 
    VALUE o=PROTOTYPE_OBJECT;
    o.data.object.subtype=D2INT(TOP()->data.number);
    pop();
    return o;
}

//------------------------------------------------------------------------
