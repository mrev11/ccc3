
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
 
//----------------------------------------------------------------------------
void _clp_procline(int argno) // Clipper kompatibilis
{
    VALUE*base=stack-argno;
    int level=0;
    if( argno>0 && base->type==TYPE_NUMBER )
    {
        level=D2INT(base->data.number);
    }
    stack=base;
    number( trace-level>tracebuf ? (trace-level)->line : 0 );
}

//----------------------------------------------------------------------------
void _clp_procname(int argno) // Clipper kompatibilis
{
    VALUE*base=stack-argno;
    int level=0;
    if( argno>0 && base->type==TYPE_NUMBER )
    {
        level=D2INT(base->data.number);
    }
    stack=base;
    trace-level>tracebuf ? stringnb((trace-level)->func) : string(CHRLIT("")); 
}

//----------------------------------------------------------------------------
void _clp_callstack(int argno)
{
    VALUE*base=stack-argno;
    int level=0;
    if( argno>0 && base->type==TYPE_NUMBER )
    {
        level=D2INT(base->data.number);
    }
    stack=base;

    TRACE *t=trace-level;
    while( t>tracebuf )
    {
        string(CHRLIT("\n  called from ")); _clp_qqout(1); pop();
        binaryn(t->func); _clp_qqout(1); pop();
        string( CHRLIT("(")); _clp_qqout(1); pop();
        number(t->line); _clp_str(1); _clp_alltrim(1); _clp_qqout(1); pop();
        string(CHRLIT(")")); _clp_qqout(1); pop();
        --t;
    }

    PUSHNIL();
}

//----------------------------------------------------------------------------
void _clp_varstack(int argno)
{
    extern void stack_print(void);
    stack_print();
    stack-=argno;
    PUSHNIL();
}

//----------------------------------------------------------------------------
void _clp___varprint(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
push_call("__varprint",base);
//
    var_print(base);
//
stack=base;
push(&NIL);
pop_call();
}

//----------------------------------------------------------------------------
void _clp_localstack(int argno)
{
    CCC_PROLOG("localstack",1);
    int paridx=_parni(1);
    if( (paridx<1) || (stackbuf+paridx>=stack) )
    {
        _ret();
    }
    else
    {
        //PUSH(stackbuf+paridx-1); //rossz
        push_symbol(stackbuf+paridx-1); //deref 2011.09.19
        _rettop();
    }
    CCC_EPILOG();
}

#ifdef MEGJEGYZES

    localstack() lehetove teszi, hogy a lokalis
    stack aljan levo valtozokban a szalra specifikus, 
    a szalban globalis adatokat taroljunk.

    Thread-specifikus static valtozokat korulmenyes volna 
    CCC-ben implementalni, sokkal egyszerubb megengedni, 
    hogy a szal lenyuljon a lokalis stack aljaig. Pelda:

    function main()
    local v:="anything"
    local a:=errorNew() 
    local b:="b" 
    local c:="c"
    local blk:={|x1,x2|proc("hopp")} 
    local th:=thread_create(blk, a, b, c)
        thread_join(th)
        return NIL

    A szalban hivott localstack() ertekei:

    localstack(1)  ->  blk
    localstack(2)  ->  a
    localstack(3)  ->  b
    localstack(4)  ->  nem definialt (proc-tol fugg)
    localstack(5)  ->  nem definialt, stb.
    
    A blokknak atadott parametereket lehet megkapni
    a szalbol barhonnan, legfeljebb olyan szamban,
    ahany x1, x2,... parametere van a blocknak.
    Ha kozonseges (nem tobbszalu) programbol hivjuk,
    akkor is megkaphatok a lokalis stacken levo valtozok. 
    Tanulsagos megnezni varstack() eredmenyet.
#endif 


//----------------------------------------------------------------------------
void _clp_localstacktop(int argno)
{
    //stack_print();

    CCC_PROLOG("localstack",1);
    int paridx=_parni(1);
    if( (paridx<0) || (stack-paridx-1<stackbuf) )
    {
        _ret();
    }
    else
    {
        push_symbol(stack-paridx-1);
        _rettop();
    }
    CCC_EPILOG();
}

#ifdef MEGJEGYZES
    Ez is a stack elemeihez ad hozzaferest, 
    csak visszafele: a top-tol indulva a stack aljaig
    localstacktop(0) mindig 0, mert a 0 parametert adja
    loclastacktop(1) az 1 alatti elso elem
    loclastacktop(2) a 2 alatti masodik elem, stb.
#endif


//----------------------------------------------------------------------------
void _clp_localstackdepth(int argno)
{
    stack-=argno;
    number(stack-stackbuf);
}

#ifdef MEGJEGYZES
    Megadja a local stacken levo VALUE-k szamat.

    local ...
    local depth:=localstackdepth() //utolso local
    
    if( depth==localstack(depth) )
        //ez teljesul az utolsonak 
        //definialt local valtozora
    end
#endif
 
//----------------------------------------------------------------------------

