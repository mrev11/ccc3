

#include <math.h>
#include <cccapi.h>
#include <qsort.ch>
#include <qsort.h>

#define PERCENT(x) (int)(100.0*(x)/(r-p+1))

//----------------------------------------------------------------------------------------
void prnstat(int p, int q, int r)
{
    printf("\n");
    printf( "%8d:  %8d%% %8d%%",  
             r-p+1, PERCENT(q-p+1), PERCENT(r-q) );
}


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
    //prnstat(p,j,r);
    return j;
}


//----------------------------------------------------------------------------------------
static void qsort(VALUE *arr, int p, int r, VALUE* blk) // tail recursion
{
    while( p+ISORT_TRESHOLD<r )
    {
        int q=qsplit(arr,p,r,blk);

        // kisebbik reszre rekurzio
        // nagyobbik reszre ciklus

        if( q-p<r-q )
        {
            qsort(arr,p,q,blk);
            p=q+1;
        }
        else
        {
            qsort(arr,q+1,r,blk);
            r=q;
        }
    }

    if( p<r )
    {
        isort(arr,p,r,blk);
    }
}

//----------------------------------------------------------------------------------------
void _clp_qsortc_h(int argno)
{
    printf("%-16s","qsortc_h");fflush(0);

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

