
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

void PUSH(VALUE *v)
{
    int lkx=assign_lock(v);
    stack->type=(v)->type;
    stack->data=(v)->data;
    stack++;
    assign_unlock(lkx);
}

//------------------------------------------------------------------------
void push_symbol(VALUE *v)  // felteteles deref 
{
    assign_lock0();
    int lkx=assign_lock(v);
    if( v->type!=TYPE_REF )
    {
        assign_unlock0();
        stack->type=(v)->type;
        stack->data=(v)->data;
    }
    else
    {
        #ifdef FINE_GRAINED_LOCK
            lkx=assign_lock(&(v->data.vref->value),lkx);
        #endif
        assign_unlock0();
        stack->type=v->data.vref->value.type;
        stack->data=v->data.vref->value.data;
    }
    stack++;
    assign_unlock(lkx);
}

//------------------------------------------------------------------------
void push_blkenv(VALUE *v) // mindig deref
{
    PUSH( &(v->data.vref->value) );
}

//------------------------------------------------------------------------
void push_symbol_ref(VALUE *v) // @par, blokk kornyezet
{
    int lkx=assign_lock(v);
    if( v->type!=TYPE_REF )
    {
        vref_new(v);
    }
    else
    {
        stack->type=(v)->type;
        stack->data=(v)->data;
        stack++;
    }
    assign_unlock(lkx);
}

//------------------------------------------------------------------------
void pop()
{
    --stack;
}

void POP()
{
    --stack;
}

void POP2()
{
    (stack-=2);
}

void POP3()
{
    (stack-=3);
}

//------------------------------------------------------------------------
void dup()
{
    DUP();
}

void DUP()
{
    PUSH(TOP1());
}

void DUP2()
{
    PUSH(TOP2());
}

void DUP3()
{
    PUSH(TOP3());
}

//------------------------------------------------------------------------
void swap()
{
    DUP();
    *TOP2()=*TOP3();
    *TOP3()=*TOP();
    POP();
}

void SWAP()
{
    DUP();
    *TOP2()=*TOP3();
    *TOP3()=*TOP();
    POP();
}

//------------------------------------------------------------------------
void assign(VALUE *lside)
{
    assign_lock0();
    int lkx=assign_lock(lside);
    if( lside->type!=TYPE_REF )
    {
        assign_unlock0();
        valuecopy(lside,TOP());
    }
    else
    {
        #ifdef FINE_GRAINED_LOCK
            lkx=assign_lock(&(lside->data.vref->value),lkx);
        #endif
        assign_unlock0();
        valuecopy(&lside->data.vref->value,TOP());
    }    
    assign_unlock(lkx);
}

//------------------------------------------------------------------------
void assign2(VALUE *lside) // ertekadas tombelemnek (tombelem sosem ref)
{
    int lkx=assign_lock(lside);
    valuecopy(lside,TOP2());
    POP();
    assign_unlock(lkx);
}

//------------------------------------------------------------------------
void block(void (*code)(int), int len)
{
    if( 0<len )
    {
        VALUE *base=stack-len;
        VALUE *valptr=newValue(len+1);
        (valptr+len)->type=TYPE_END;
        (valptr+len)->data.size=len;
        arraycopy(valptr,base,len);
        VALUE v;
        v.type=TYPE_BLOCK;
        v.data.block.code=code;
        oref_new(&v,valptr,len); // PUSH
        *base=*TOP();
        stack=base+1;
    }
    else
    {
        stack->type=TYPE_BLOCK;
        stack->data.block.code=code;
        stack->data.block.oref=0;
        stack++;
    }
}

//------------------------------------------------------------------------
VALUE *blkenv(VALUE *blk)
{
    // ezt az oref-et csak a blokkok hasznaljak,
    // nemletezo oref-re csak akkor lehet hivatkozas,
    // ha rossz a fordito, ezert nem kell vizsgalni
    // (esetleg run time errort lehet generalni)
    
    return BLOCKPTR(blk);
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
