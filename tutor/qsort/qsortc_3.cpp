

#include <math.h>
#include <cccapi.h>
#include <qsort.ch>
#include <qsort.h>

#define PERCENT(x) (int)(100.0*(x)/(r-p+1))

//----------------------------------------------------------------------------------------
void prnstat(int p, int q1, int q2, int r)
{
    printf("\n");
    printf( "%8d:  %8d%% %8d%% %8d%%", 
             r-p+1, PERCENT(q1-p+1), PERCENT(q2-q1+1), PERCENT(r-q2+1) );
}

//----------------------------------------------------------------------------------------
static void qsplit( VALUE *arr, int p, int r, int *q1, int *q2, VALUE *blk )
{
    int lt=p; // 1 based
    int eq=p; // 1 based
    int gt=r; // 1 based

    VALUE *pivot=push_pivot(arr,p,r,blk);
    
    while( eq<=gt )
    {
        int cmp=compare(arr+eq-1,pivot,blk);

        if( cmp<0 )
        {
            swap(arr+eq-1,arr+lt-1);
            lt++;
            eq++;
        }
        else if( cmp>0 )
        {
            swap(arr+eq-1,arr+gt-1);
            gt--;
        }
        else
        {
            eq++;
        }
    }

    *q1=lt-1;
    *q2=eq;

    POP(); //pivot

    //prnstat(p,*q1,*q2,r);
}

//----------------------------------------------------------------------------------------
static void qsort(VALUE *arr, int p, int r, VALUE* blk) // tail recursion
{
    while( p+ISORT_TRESHOLD<r )
    {
        int lt=0;
        int gt=0;

        qsplit(arr,p,r,&lt,&gt,blk);

        // kisebbik reszre rekurzio
        // nagyobbik reszre ciklus

        if( lt-p<r-gt )
        {
            qsort(arr,p,lt,blk);
            p=gt;
        }
        else
        {
            qsort(arr,gt,r,blk);
            r=lt;
        }
    }

    if( p<r )
    {
        isort(arr,p,r,blk);
    }
}

//----------------------------------------------------------------------------------------
void _clp_qsortc_3(int argno)
{
    printf("%-16s","qsortc_3");fflush(0);

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

