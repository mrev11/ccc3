
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
    trace-level>tracebuf ? stringnb((trace-level)->func) : string(L""); 
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
        string(L"\n  called from "); _clp_qqout(1); pop();
        binaryn(t->func); _clp_qqout(1); pop();
        string(L"("); _clp_qqout(1); pop();
        number(t->line); _clp_str(1); _clp_alltrim(1); _clp_qqout(1); pop();
        string(L")"); _clp_qqout(1); pop();
        --t;
    }

    PUSHNIL();
}

//----------------------------------------------------------------------------
void _clp_varstack(int argno)
{
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

    localstack() lehetővé teszi, hogy a lokális
    stack alján levő változókban a szálra specifikus, 
    a szálban globális adatokat tároljunk.

    Thread-specifikus static változókat körülményes volna 
    CCC-ben implementálni, sokkal egyszerűbb megengedni, 
    hogy a szál lenyúljon a lokális stack aljáig. Példa:

    function main()
    local v:="anything"
    local a:=errorNew() 
    local b:="b" 
    local c:="c"
    local blk:={|x1,x2|proc("hopp")} 
    local th:=thread_create(blk, a, b, c)
        thread_join(th)
        return NIL

    A szálban hívott localstack() értékei:

    localstack(1)  ->  blk
    localstack(2)  ->  a
    localstack(3)  ->  b
    localstack(4)  ->  nem definiált (proc-tól függ)
    localstack(5)  ->  nem definiált, stb.
    
    A blokknak átadott paramétereket lehet megkapni
    a szálból bárhonnan, legfeljebb olyan számban,
    ahány x1, x2,... paramétere van a blocknak.
    Ha közönséges (nem többszálú) programból hívjuk,
    akkor is megkaphatók a lokális stacken levő változók. 
    Tanulságos megnézni varstack() eredményét.
#endif 
 
//----------------------------------------------------------------------------

