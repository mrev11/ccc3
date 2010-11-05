
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

#include <wchar.h>
#include <termapi.h>
#include <cccapi.h>

//------------------------------------------------------------------------
#define TYPEAHEAD   32

static CHAR keyboard_buffer[TYPEAHEAD];
static int kbmax=0;
static int kbact=0;

static int lastkey=0;


//------------------------------------------------------------------------
void _clp_inkey(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
//
    int key=0;

    if( kbact<kbmax )
    {
        key=keyboard_buffer[kbact++];
    }
    else if( base->type==TYPE_NUMBER )
    {
        double wait=base->data.number;
        if( wait<=0 )
        {
            key=getkey(-1);
        }
        else
        {
            key=getkey( (int)(wait*1000) );
        }
    }
    else
    {
        key=getkey(0);
    }

    stack=base;
    number(lastkey=key);
}


//------------------------------------------------------------------------
void _clp_nextkey(int argno)
{
    stack-=argno;

    if( kbact<kbmax )
    {
        number( keyboard_buffer[kbact] );
        return;
    }
    
    int save_lastkey=lastkey;

    _clp_inkey(0);

    lastkey=save_lastkey;
    
    int keycode=D2INT(TOP()->data.number);
    if( keycode )
    {
        kbact=0;
        kbmax=1;
        keyboard_buffer[0]=keycode;
    }
}

//------------------------------------------------------------------------
void _clp_lastkey(int argno)
{
    stack-=argno;
    number(lastkey);
}

//------------------------------------------------------------------------
void _clp___keyboard(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
push_call("__keyboard",base);
//
    
    while(getkey(0)); //clear typeahead

    kbmax=0;
    kbact=0;

    // keyboard "string"

    if( base->type==TYPE_BINARY )
    {
        bin2str(base);
    }

    if( base->type==TYPE_STRING )
    {
        kbmax=min(TYPEAHEAD,STRINGLEN(base));
        wmemcpy(keyboard_buffer,STRINGPTR(base),kbmax);
    }
//
stack=base;
push(&NIL);
pop_call();
}

//------------------------------------------------------------------------
