

#include <math.h>
#include <cccapi.h>
#include <qsort.ch>
#include <qsort.h>
#include <region_stack.h>


//----------------------------------------------------------------------------------------
static int qsplit( VALUE *arr, int p, int r, VALUE *blk )
{
    int i=p-1; // 1 based
    int j=r+1; // 1 based

    VALUE *pivot=push_pivot(arr,p,r,blk);

    while( 1 )
    {
        while( 0>compare(arr+(++i-1),pivot,blk) );
        while( 0<compare(arr+(--j-1),pivot,blk) );

        if( i>=j )
        {
            break;
        }
        swap(arr+i-1,arr+j-1);
    }

    POP(); //pivot
    return j;
}


//----------------------------------------------------------------------------------------
static void qsort(VALUE *arr, int p, int r, VALUE* blk) // stack instead of recursion
{
    region_stack stk;
    stk.push(p,r);

    while( stk.pop(&p,&r) )    
    {    
        while( p+ISORT_TRESHOLD<r )
        {
            int q=qsplit(arr,p,r,blk);
    
            if( q-p>r-q )
            {
                stk.push(p,q);
                p=q+1;
            }
            else
            {
                stk.push(q+1,r);
                r=q;
            }
        }
        if( p<r )
        {
            isort(arr,p,r,blk);
        }
    }
}

//----------------------------------------------------------------------------------------
void _clp_qsortc_hs(int argno)
{
    printf("%-16s","qsortc_hs");fflush(0);

    CCC_PROLOG("qsort",4);

    VALUE *arr;
    unsigned len;
    unsigned p;
    unsigned r;
    VALUE *blk=0;

    if( !ISARRAY(1) )
    {
        error_arg("qsort",base,4);
    }
    arr=ARRAYPTR(base);
    len=ARRAYLEN(base);

    if( ISBLOCK(2) )
    {
        p=1;
        r=len;
        blk=base+1;
    }
    else
    {
        p=ISNIL(2)?1:_parnu(2);
        r=ISNIL(3)?len:_parnu(3);
        if( p<1 || len<p  || r<1 || len<r )
        {
            error_arg("qsort",base,4);
        }
        if( ISNIL(4) )
        {
            blk=0;
        }
        else if( ISBLOCK(4) )
        {
            blk=base+3;
        }
        else
        {
            error_arg("qsort",base,4);
        }
    }

    qsort(arr,p,r,blk);

    stack=base+1;
    CCC_EPILOG();
}

//----------------------------------------------------------------------------------------

