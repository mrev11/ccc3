
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

//input: dbundef.ppo (5.0.17)

#include <cccdef.h>

extern void _clp_alltrim(int argno);
extern void _clp_len(int argno);
extern void _clp_rule_df_del(int argno);
extern void _clp_tokenize(int argno);
extern void _clp_undef(int argno);

//=======================================================================
void _clp_undef(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+3)PUSHNIL();
argno=1;
push_call("undef",base);
//
    line(23);
    push_symbol(base+0);//line
    _clp_alltrim(1);
    _clp_tokenize(1);
    assign(base+1);//toklist
    pop();
    line(24);
    push_symbol(base+1);//toklist
    _clp_len(1);
    push(&ZERO);
    gt();
    if(flag()){
    push_symbol(base+1);//toklist
    idxr0(1);
    }else{
    push(&NIL);
    }
    assign(base+2);//symbol
    pop();
    line(25);
    push_symbol(base+2);//symbol
    _clp_rule_df_del(1);
    pop();
    line(26);
    push(&NIL);
    {*base=*(stack-1);stack=base+1;pop_call();return;}
//
stack=base;
push(&NIL);
pop_call();
}
//=======================================================================

