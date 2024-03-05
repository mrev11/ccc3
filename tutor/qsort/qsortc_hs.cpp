

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

    VALUE *pivot=push_pivot(arr,p,r-1,blk);

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

