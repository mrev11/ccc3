
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
            unsigned long len=STRINGLEN(base);
            if( len==0 ) 
            {
                flag=1;
            }
            else
            {
                unsigned long i;
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
            unsigned long len=BINARYLEN(base);
            if( len==0 ) 
            {
                flag=1;
            }
            else
            {
                unsigned long i;
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
            flag=(ARRAYLEN(base)==0);
            break;

        case TYPE_OBJECT:
            flag=(OBJECTLEN(base)==0);
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
    unsigned long len=0;

    switch( base->type )
    {
        case TYPE_BINARY:
            len=BINARYLEN(base);
            break;

        case TYPE_STRING:
            len=STRINGLEN(base);
            break;

        case TYPE_ARRAY:
            len=ARRAYLEN(base);
            break;

        case TYPE_OBJECT:
            len=OBJECTLEN(base);
            break;

        case TYPE_BLOCK:
            if(base->data.block.oref)
            {
                len=BLOCKLEN(base);
            }
            break;
    }
    stack=base;
    number(len);
}

//--------------------------------------------------------------------

