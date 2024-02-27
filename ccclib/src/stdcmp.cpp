
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


//----------------------------------------------------------------------------------------
int stdcmp(VALUE*a, VALUE*b, int mode) // -1:a<b;  0:a==b;  1:a>b;
{
    if( a->type!=b->type )
    {
        if( a->type==TYPE_NIL )
        {
            return -1;
        }
        if( b->type==TYPE_NIL )
        {
            return 1;
        }

        push(a);
        push(b);
        error_gen(CHRLIT("different types"),"stdcmp",TOP2(),2);
        pop();
        pop();
    }

    switch( a->type )
    {
        case TYPE_NIL:
        {
            return 0;
        }

        case TYPE_STRING:
        {
            CHAR *ap=STRINGPTR(a);
            CHAR *bp=STRINGPTR(b);
            unsigned long al=STRINGLEN(a);
            unsigned long bl=STRINGLEN(b);
            unsigned long minlen=min(al,bl);

            for( unsigned long l=0; l<minlen; l++ )
            {
                if( ap[l]<bp[l] )
                {
                    return(-1);
                }
                else if( ap[l]>bp[l] )
                {
                    return(1);
                }
            }
            if( al<bl )
            {
                return(-1);
            }
            else if( mode==0 && al>bl )
            {
                // mode!=0 eseten
                // regi Clipper osszehasonlitas
                // a jobboldal hosszara korlatozva
                return(1);
            }
            else
            {
                return(0);
            }
        }

        #ifdef _CCC3_
        case TYPE_BINARY:
        {
            char *ap=BINARYPTR(a);
            char *bp=BINARYPTR(b);
            binarysize_t al=BINARYLEN(a);
            binarysize_t bl=BINARYLEN(b);
            binarysize_t minlen=min(al,bl);

            for( binarysize_t l=0; l<minlen; l++ )
            {
                if( ap[l]<bp[l] )
                {
                    return(-1);
                }
                else if( ap[l]>bp[l] )
                {
                    return(1);
                }
            }
            if( al<bl )
            {
                return(-1);
            }
            else if( mode==0 && al>bl )
            {
                // mode!=0 eseten
                // regi Clipper osszehasonlitas
                // a jobboldal hosszara korlatozva
                return(1);
            }
            else
            {
                return(0);
            }
        }
        #endif

        case TYPE_NUMBER:
        {
            if( a->data.number < b->data.number )
            {
                return(-1);
            }
            else if( a->data.number>b->data.number )
            {
                return(1);
            }
            else
            {
                return(0);
            }
        }

        case TYPE_DATE:
        {
            if( a->data.date < b->data.date )
            {
                return(-1);
            }
            else if( a->data.date > b->data.date )
            {
                return(1);
            }
            else
            {
                return(0);
            }
        }

        case TYPE_FLAG:
        {
            if( (a->data.flag==0) == (b->data.flag==0) )
            {
                return(0);
            }
            else
            {
                return( (a->data.flag==0)?-1:1 );
            }
        }

        case TYPE_POINTER:
        {
            if( a->data.pointer < b->data.pointer )
            {
                return(-1);
            }
            else if( a->data.pointer > b->data.pointer )
            {
                return(1);
            }
            else
            {
                return(0);
            }
        }

        case TYPE_ARRAY:
        {
            if( a->data.array.oref < b->data.array.oref )
            {
                return(-1);
            }
            else if( a->data.array.oref > b->data.array.oref )
            {
                return(1);
            }
            else
            {
                return(0);
            }
        }

        case TYPE_BLOCK:
        {
            if( a->data.block.oref < b->data.block.oref )
            {
                return(-1);
            }
            else if( a->data.block.oref > b->data.block.oref )
            {
                return(1);
            }
            else if( (void*)a->data.block.code < (void*)b->data.block.code )
            {
                return(-1);
            }
            else if( (void*)a->data.block.code > (void*)b->data.block.code )
            {
                return(1);
            }
            else
            {
                return(0);
            }
        }

        case TYPE_OBJECT:
        {
            if( a->data.object.oref < b->data.object.oref )
            {
                return(-1);
            }
            else if( a->data.object.oref > b->data.object.oref )
            {
                return(1);
            }
            if( a->data.object.subtype < b->data.object.subtype )
            {
                return(-1);
            }
            else if( a->data.object.subtype > b->data.object.subtype )
            {
                return(1);
            }
            else
            {
                return(0);
            }
        }

        default:
            push(a);
            push(b);
            error_gen(CHRLIT("wrong types"),"stdcmp",TOP2(),2);
            pop();
            pop();

    } //switch

    return 0;
}


//----------------------------------------------------------------------------------------
void _clp_stdcmp(int argno)
{
    CCC_PROLOG("stdcmp",3);
    VALUE *a=base;
    VALUE *b=base+1;
    int mode=ISNIL(3)?0:_parl(3);
    _retni( stdcmp(a,b,mode) );
    CCC_EPILOG();
}

//----------------------------------------------------------------------------------------


