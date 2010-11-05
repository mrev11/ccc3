
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

//------------------------------------------------------------------------
void slice()
{
//stack: a,i,j -- slice

    VALUE *j=TOP();
    VALUE *i=TOP2();
    VALUE *a=TOP3();
    
    int idx=0;
    if( i->type==TYPE_NIL )
    {
        idx=1;
    }
    else if( i->type==TYPE_NUMBER )
    {
        idx=D2INT(i->data.number);
    }
    else
    {
        error_arg("slice",a,3);
    }

    int jdx=0;
    if( j->type==TYPE_NIL )
    {
        jdx=0x7fffffff;
    }
    else if( j->type==TYPE_NUMBER )
    {
        jdx=D2INT(j->data.number);
    }
    else
    {
        error_arg("slice",a,3);
    }

   
    if( a->type==TYPE_STRING )
    {
        int len=STRINGLEN(a);
        idx=max(1,idx);
        jdx=min(len,jdx);
        if( idx>jdx )
        {
            string(L"");
        }
        else
        {
            CHAR *s=STRINGPTR(a);
            strings(s+idx-1,jdx-idx+1);
        }
        *a=*TOP();
        stack=a+1;
    }

    else if( a->type==TYPE_BINARY )
    {
        int len=BINARYLEN(a);
        idx=max(1,idx);
        jdx=min(len,jdx);
        if( idx>jdx )
        {
            binary("");
        }
        else
        {
            BYTE *s=BINARYPTR(a);
            binarys(s+idx-1,jdx-idx+1);
        }
        *a=*TOP();
        stack=a+1;
    }

    else if( a->type==TYPE_ARRAY )
    {
        int len=ARRAYLEN(a);
        idx=max(1,idx);
        jdx=min(len,jdx);
        if( idx>jdx )
        {
            array0(0);
        }
        else
        {
            int slen=jdx-idx+1; //>=1
            VALUE *v=array0(slen);
            valuemove(v,VALUEPTR(a)+idx-1,slen);
        }
        *a=*TOP();
        stack=a+1;
    }

    else
    {
        error_arg("slice",a,3);
    }
}


//------------------------------------------------------------------------
void sliceright()
{
//stack: a,i -- slice

    push(&NIL);//j
    slice();
}

//------------------------------------------------------------------------
void sliceleft()
{
//stack: a,j -- slice

    push(&NIL);//i
    swap();
    slice();
}

//------------------------------------------------------------------------
