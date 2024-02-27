
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

#include <string.h>
#include <cccapi.h>


DEFINE_METHOD(args);
DEFINE_METHOD(description);
//DEFINE_METHOD(operation);


//------------------------------------------------------------------------
void eqeq() //stack: a,b --- a==b
{
    logical( equalto() );
}

void neeq() //stack: a,b --- a!=b
{
    logical( notequal() );
}

void lt()  //stack: a,b --- a<b
{
    logical( lessthan() );
}

void gt() //stack: a,b --- a>b
{
    logical( greaterthan() );
}

void lteq() //stack: a,b --- a<=b
{
    logical( !greaterthan() );
}

void gteq() //stack: a,b --- a>=b
{
    logical( !lessthan() );
}


//------------------------------------------------------------------------
void topnot() //stack: f --- !f
{
    logical( !flag() );
}


//------------------------------------------------------------------------
int flag() 

// stack: f ---
// return: 1, ha f==TRUE, 0, ha f==FALSE

{
    VALUE *base=TOP();
    if( base->type!=TYPE_FLAG )
    {
        error_cnd("flag",base,1);    
    }
    int result=(0!=(base->data.flag));
    POP();
    return result;
}

//------------------------------------------------------------------------
int equalto()  // szigoru (nem Clipper =) egyenloseg

// stack: a,b ---
// return: 1, ha a==b, 0, ha !(a==b)

{
    VALUE *a=TOP2(); // baloldal
    VALUE *b=TOP();  // jobboldal
    int result=stdcmp(a,b);
    POP2();
    return result==0;
}


//------------------------------------------------------------------------
int notequal()

// stack: a,b ---
// return: 1, ha a!=b, 0, ha a=b (vigyazat Clipper relaciok!)

{
    VALUE *a=TOP2(); // baloldal
    VALUE *b=TOP();  // jobboldal
    int result=stdcmp(a,b,1);
    POP2();
    return result!=0;    
}

//------------------------------------------------------------------------
int greaterthan()

// stack: a,b ---
// return: 1, ha a>b, 0, ha !(a>b) (vigyazat Clipper relaciok!)

{
    VALUE *a=TOP2();
    VALUE *b=TOP();
    int result=stdcmp(a,b,1);
    POP2();
    return result>0;    
}

//------------------------------------------------------------------------
int lessthan()

// stack: a,b ---
// return: 1, ha a<b, 0, ha !(a<b) (vigyazat Clipper relaciok!)

{
    VALUE *a=TOP2();
    VALUE *b=TOP();
    int result=stdcmp(a,b,1);
    POP2();
    return result<0;
}

//------------------------------------------------------------------------
