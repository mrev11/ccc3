

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
