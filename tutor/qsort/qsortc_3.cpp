

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

    VALUE *arr=_para(1);        // first element of the array to sort (&a[1])
    unsigned len=_paralen(1);   // length of the array
    unsigned start=1;           // start index
    unsigned count=len;         // count of elements to sort
    VALUE *blk=&NIL;            // compare block

    // hivasi formak:
    //  asort(a,b)
    //  asort(a,[s],[c],[b])

    if( ISBLOCK(2) )
    {
        blk=PARPTR(2);
    }    
    else
    {
        start=ISNIL(2)?start:_parnu(2);
        count=ISNIL(3)?count:_parnu(3);
        if( ISNIL(4) )
        {
            blk=0;
        }
        else if( ISBLOCK(4) )
        {
            blk=PARPTR(4);
        }
        else
        {
            error_arg("asort",base,4);
        }
    }

    if( count>1  )
    {
        qsort(arr,start,start+count-1,blk);
    }


    stack=base+1;
    CCC_EPILOG();
}

//----------------------------------------------------------------------------------------

