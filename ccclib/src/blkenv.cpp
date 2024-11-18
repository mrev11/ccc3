
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
void _clp_blkenv(int argno)
{
    CCC_PROLOG("blkenv",2);


    if( argno==1 )
    {
        VALUE *blk=base;

        if( !ISBLOCK(1) )
        {
            error_arg("blkenv",blk,2);
        }
        else if( !blk->data.block.oref )
        {
            blk->type=TYPE_NIL;
        }
        else
        {
            blk->type=TYPE_ARRAY;
        }
        pop(); 

        //return: NIL/array
    }
    else
    {
        if( !ISBLOCK(1) || !ISARRAY(2) )
        {
            error_arg("blkenv",base,2);
        }
        VALUE *blk=base;
        VALUE *arr=base+1;
        blk->data.block.oref=arr->data.block.oref;
        pop();
        
        //return: blk
    }
    CCC_EPILOG();
}

//----------------------------------------------------------------------------------------
