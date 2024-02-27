
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
void ss() //substring

// stack: a,b --- a $ b

{
    VALUE *b=TOP();
    VALUE *a=TOP2();

    if( a->type==TYPE_STRING && b->type==TYPE_STRING )
    {
        unsigned long al=STRINGLEN(a);
        unsigned long bl=STRINGLEN(b);
            
        if( al==0 )
        {
            stack-=2;
            logical(1);
        }
        else if( bl<al )
        {
            stack-=2;
            logical(0);
        }
        else
        {
            // 0<al<=bl

            CHAR *ap=STRINGPTR(a);
            CHAR *bp=STRINGPTR(b);

            unsigned long i,j;
            for(i=0; i<=bl-al; i++)
            {
                for(j=0; j<al; j++)
                {
                    if( *(bp+i+j)!=*(ap+j) ) break;
                }
                if( j>=al ) 
                {
                    break;
                }
            }
            stack-=2;
            logical( i<=bl-al );
        }

        return;
    }      

    else if( a->type==TYPE_BINARY && b->type==TYPE_BINARY )
    {
        unsigned long al=BINARYLEN(a);
        unsigned long bl=BINARYLEN(b);
            
        if( al==0 )
        {
            stack-=2;
            logical(1);
        }
        else if( bl<al )
        {
            stack-=2;
            logical(0);
        }
        else
        {
            // 0<al<=bl
        
            BYTE *ap=BINARYPTR(a);
            BYTE *bp=BINARYPTR(b);
            
            unsigned long i,j;
            for(i=0; i<=bl-al; i++)
            {
                for(j=0; j<al; j++)
                {
                    if( *(bp+i+j)!=*(ap+j) ) break;
                }
                if( j>=al ) 
                {
                    break;
                }
            }
            stack-=2;
            logical( i<=bl-al );
        }

        return;
    }      

    error_arg("$",TOP2(),2);
}

//------------------------------------------------------------------------
