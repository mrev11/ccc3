

#include <cccapi.h>

//----------------------------------------------------------------------------------------
void _clp_blkenv(int argno)
{
    CCC_PROLOG("blkenv",1);
    VALUE *blk=TOP();
    if( blk->type!=TYPE_BLOCK )
    {
        error_arg("blkenv",blk,1);
    }
    else if( !blk->data.block.oref )
    {
        blk->type=TYPE_NIL;
    }
    else
    {
        blk->type=TYPE_ARRAY;
    }
    CCC_EPILOG();
}

//----------------------------------------------------------------------------------------
