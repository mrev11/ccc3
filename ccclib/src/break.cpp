
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

#include <cccapi.h>


DEFINE_METHOD(isderivedfrom);

//----------------------------------------------------------------------------
static const char *ctype(int type)
{
    switch( type )
    {
        case TYPE_END:      return "E";
        case TYPE_NIL:      return "U";
        case TYPE_NUMBER:   return "N";
        case TYPE_DATE:     return "D";
        case TYPE_FLAG:     return "L";
        case TYPE_POINTER:  return "P";
        case TYPE_BINARY:   return "X";
        case TYPE_STRING:   return "C";
        case TYPE_ARRAY:    return "A";
        case TYPE_BLOCK:    return "B";
        case TYPE_OBJECT:   return "O";
        case TYPE_REF:      return "R";
    }
    return ".";
}


static void _break_(int argno,int bbflag);


//----------------------------------------------------------------------------
void _clp_break0(int argno)
{
    _break_(argno,0);
}

//----------------------------------------------------------------------------
void _clp_break(int argno)
{
    _break_(argno,1);
}


//----------------------------------------------------------------------------
static int bbeval(VALUE *exception, VALUE *usingstk1)
{
    int result=1;

    SEQJMP *seqjmp1=seqjmp;
    while( (--seqjmp1)->jmp_usingstk >= usingstk1 )
    {
        //keressuk a breakblockot
    }

    if( seqjmp1->jmp_stack->type==TYPE_BLOCK )
    {
        push(seqjmp1->jmp_stack);
        push(exception);
        _clp_eval(2);
        result=TOP()->type==TYPE_NIL;
        pop();
    }

    return result;

    // ha nincs breakblock          -> result==1 -> elkapja
    // ha breakblock eredmenye  NIL -> result==1 -> elkapja
    // ha breakblock eredmenye !NIL -> result==0 -> nem kapja el
}

//----------------------------------------------------------------------------
static void _break_(int argno,int bbflag)
{
    //Figyelem:
    //a stack pointerek az első szabad helyre mutatnak
    //(stack, trace, seqjmp, usingstk).

    VALUE *base=stack-argno;
    VALUE *exception=(argno>0) ? base : &NIL; //ezt dobták
    int xtype=exception->type;
    int xsubtype=(xtype==TYPE_OBJECT?exception->data.object.subtype:0);
  
    //printf("\nx-type %s %d",ctype(xtype),xsubtype);fflush(0);
    
    //kompatibilis recover-t keresünk
    VALUE *usingstk1=usingstk;
    while( usingstk1>usingstkbuf )
    {
        //printf("\n!1! %x %x",usingstk1,usingstkbuf);fflush(0);

        VALUE *rcv=usingstk1-1; //top
        int type=rcv->type;
        int subtype=(type==TYPE_OBJECT)?rcv->data.object.subtype:0;
        //printf("\nrec-type %s %d",ctype(type),subtype);fflush(0);

        if( type==TYPE_NIL )
        {
            //ha nincs megadva, 
            //hogy mit vár a recover,
            //akkor bármit elkapunk

            if( !bbflag || bbeval(exception,usingstk1) )
            {
                break;
            }
        }
        else if( type==xtype )
        {
            //ha ismert, hogy mit vár a recover,
            //akkor az egyező típusokat, objektumoknál pedig 
            //a leszármaztatott osztályokat kapjuk el

            if( type!=TYPE_OBJECT )
            {
                if( !bbflag || bbeval(exception,usingstk1) )
                {
                    break;
                }
            }
            else
            {
                push(exception);
                number(subtype);
                _o_method_isderivedfrom.eval(2);
                if( flag() )
                {
                    if( !bbflag || bbeval(exception,usingstk1) )
                    {
                        break;
                    }
                }
            }
        }
        --usingstk1;
    }
    
    //printf("\n!2! %x %x",usingstk1,usingstkbuf);fflush(0);
    
    if( usingstk1>usingstkbuf )
    {
        //printf("\nkivétel elkapva");fflush(0);
        //találtunk kompatibilis recover-t
        //megkeressük a hozzá tartozó seqjmp elemet
        //eközben a finally blokkokat végrehajtjuk

        //amíg seqjmp->jmp_usingstk szabad helyre mutat
        while( (--seqjmp)->jmp_usingstk >= usingstk1 )
        {
            int type=seqjmp->jmp_usingstk->type;
            //printf("\nseq-type %s",ctype(type));fflush(0);
        
            if( type==TYPE_END )
            {
                //olyan begin utasítás,
                //amiben egy recover sem kapta el a breaket,
                //de van benne finally blokk, amit most végrehajtunk

                *(seqjmp->jmp_stack)=*exception;
                stack=seqjmp->jmp_stack+1; 
                trace=seqjmp->jmp_trace;
                usingstk=seqjmp->jmp_usingstk;
                longjmp(seqjmp->jmpb,-1);
            }
        }

        int finally=(seqjmp->jmp_usingstk->type==TYPE_END)?1:0;
        int level=usingstk1-seqjmp->jmp_usingstk-finally;

        //level=1,2,3...
        //printf("\nlevel %d",level);fflush(0);

        //kivételt a stackre
        *(seqjmp->jmp_stack)=*exception;
        stack=seqjmp->jmp_stack+1;    
        trace=seqjmp->jmp_trace;    
        usingstk=seqjmp->jmp_usingstk+finally;  //esetleges END-et vissza
        longjmp(seqjmp++->jmpb,level);  //végleges pop a recoverben
    }
    else
    {
        //printf("\nkezeletlen kivétel");fflush(0);
        //nem találtunk kompatibilis recover-t
        //ilyenkor a stacket nem fejtjük vissza
        //a begin blokkokat nem hajtjuk végre
        //csak végrehajtjuk az errorblock-ot

        _clp_errorblock(0);
        push(exception);        
        _clp_eval(2);
        _rettop();

        //Visszatérhet, 
        //ha például a kivétel error leszármazott,
        //és canretry==.t. vagy  candefault==.t..
    }
}

//----------------------------------------------------------------------------
void begseqpop_ret()
{
    --seqjmp;
    *(seqjmp->jmp_stack)=*TOP(); //retval
    stack=seqjmp->jmp_stack+1; 
    trace=seqjmp->jmp_trace;
    usingstk=seqjmp->jmp_usingstk;
    longjmp(seqjmp->jmpb,-2);
}

//----------------------------------------------------------------------------
void begseqpop_loop()
{
    --seqjmp;
    stack=seqjmp->jmp_stack; 
    trace=seqjmp->jmp_trace;
    usingstk=seqjmp->jmp_usingstk;
    longjmp(seqjmp->jmpb,-3);
}

//----------------------------------------------------------------------------
void begseqpop_exit()
{
    --seqjmp;
    stack=seqjmp->jmp_stack; 
    trace=seqjmp->jmp_trace;
    usingstk=seqjmp->jmp_usingstk;
    longjmp(seqjmp->jmpb,-4);
}


//----------------------------------------------------------------------------
