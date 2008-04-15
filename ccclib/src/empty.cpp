
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

//--------------------------------------------------------------------
void _clp_empty(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
//
    int flag=0;

    switch( base->type )
    {
        case TYPE_NIL:
            flag=1;
            break;

        case TYPE_FLAG:
            flag=(base->data.flag==0);
            break;

        case TYPE_NUMBER:
            flag=(base->data.number==0.0);
            break;

        case TYPE_DATE:
            flag=(base->data.date==0);
            break;

        case TYPE_POINTER:
            flag=(base->data.pointer==0);
            break;

        case TYPE_STRING:
        {
            int len=base->data.string.len;
            if( len==0 ) 
            {
                flag=1;
            }
            else
            {
                int i;
                CHAR *p=CHRPTR(1);
                for(i=0; i<len; i++)
                {
                    if( p[i]!=' ' )
                    {
                        break;
                    }
                }
                flag=(i>=len);
            }
            break;
        }

        case TYPE_BINARY:
        {
            int len=base->data.binary.len;
            if( len==0 ) 
            {
                flag=1;
            }
            else
            {
                int i;
                BYTE *p=BINPTR(1);
                for(i=0; i<len; i++)
                {
                    if( p[i]!=' ' )
                    {
                        break;
                    }
                }
                flag=(i>=len);
            }
            break;
        }

        case TYPE_ARRAY:
        case TYPE_OBJECT:
            flag=(base->data.array.oref->length==0);
            break;
    }

    stack=base;
    logical(flag);
}


//--------------------------------------------------------------------
void _clp_len(int argno)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
//
    int len=0;

    switch( base->type )
    {
        case TYPE_BINARY:
            len=base->data.binary.len;
            break;

        case TYPE_STRING:
            len=base->data.string.len;
            break;

        case TYPE_ARRAY:
            len=base->data.array.oref->length;
            break;
    }
    stack=base;
    number(len);
}

//--------------------------------------------------------------------

