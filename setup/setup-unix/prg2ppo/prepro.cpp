
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

//input: prepro.ppo (5.0.11)

#include <cccdef.h>

extern void _clp_alltrim(int argno);
extern void _clp_endofline(int argno);
extern void _clp_leftspace(int argno);
extern void _clp_linepragma(int argno);
extern void _clp_match(int argno);
extern void _clp_nextline(int argno);
extern void _clp_outline(int argno);
extern void _clp_prepro(int argno);
extern void _clp_qqout(int argno);
extern void _clp_space(int argno);
extern void _clp_str(int argno);
extern void _clp_tokenize(int argno);

//=======================================================================
void _clp_nextline(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
argno=2;
push_call("nextline",base);
//
    line(27);
    line(23);
    _clp_linepragma(0);
    if(!flag()) goto if_1_1;
        line(24);
        _clp_endofline(0);
        string(L"#line");
        add();
        push_symbol(base+0);//lineno
        _clp_str(1);
        _clp_alltrim(1);
        string(L"\"");
        push_symbol(base+1);//fname
        add();
        string(L"\"");
        add();
        _clp_qqout(3);
        pop();
    goto if_1_0;
    if_1_1:
    line(25);
        line(26);
        _clp_endofline(0);
        _clp_qqout(1);
        pop();
    if_1_2:
    if_1_0:;
    line(28);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================
void _clp_prepro(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+3)PUSHNIL();
argno=1;
push_call("prepro",base);
//
    line(34);
    push_symbol(base+0);//line
    _clp_leftspace(1);
    assign(base+1);//indent
    pop();
    line(35);
    push_symbol(base+0);//line
    _clp_alltrim(1);
    _clp_tokenize(1);
    assign(base+2);//toklist
    pop();
    line(41);
    line(37);
    push_symbol(base+1);//indent
    push(&ZERO);
    gt();
    if(!flag()) goto if_2_1;
        line(38);
        _clp_endofline(0);
        push_symbol(base+1);//indent
        _clp_space(1);
        add();
        _clp_qqout(1);
        pop();
    goto if_2_0;
    if_2_1:
    line(39);
        line(40);
        _clp_endofline(0);
        _clp_qqout(1);
        pop();
    if_2_2:
    if_2_0:;
    line(43);
    push_symbol(base+2);//toklist
    _clp_match(1);
    _clp_outline(1);
    _clp_qqout(1);
    pop();
    line(45);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

