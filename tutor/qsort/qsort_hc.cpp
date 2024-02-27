

// Rendezettseg elleni vedelem: veletlen pivot valasztas
// Egyenlo elemek elleni vedelem: harom reszre osztas (lt,eq,gt)
// Egy az egyben a CCC qsort3 program atirasa C++-ra.

#include <math.h>
#include <cccapi.h>


//#define DEBUG
#define DMOD(x,y) ((x)-floor((x)/(y))*(y))

//----------------------------------------------------------------------------------------
static unsigned xrand()
{
    static double FACTOR  =  16807.0;
    static double MODULUS =  2147483647.0;
    static double seed    =  7657463.0; 
    seed*=FACTOR;
    seed=DMOD(seed,MODULUS);
    return (unsigned)seed;
}

//----------------------------------------------------------------------------------------
static void swap(VALUE *arr, unsigned x, unsigned y)
{
    push(arr+x);
    arr[x]=arr[y];
    arr[y]=*TOP();
    POP();
}

//----------------------------------------------------------------------------------------
static int qsplit( VALUE *arr, int p, int r, VALUE *blk )
{
    int i=p-1; // 1 based
    int j=r+1; // 1 based

    push(arr+p-1+xrand()%(r-p+1));
    VALUE *pivot=TOP();
    
    while( 1 )
    {
        if( blk==0 )
        {
            while( 0>stdcmp(arr+(++i-1),pivot) );
            while( 0<stdcmp(arr+(--j-1),pivot) );
        }
        else
        {
            int cmp=-1;
            while( cmp<0 )
            {
                push(blk);
                push(arr+(++i-1));
                push(pivot);
                _clp_eval(3);
                cmp=TOP()->data.number;
                POP();
            }

            cmp=+1;
            while( cmp>0 )
            {
                push(blk);
                push(arr+(--j-1));
                push(pivot);
                _clp_eval(3);
                cmp=TOP()->data.number;
                POP();
            }
        }

        if( i>=j )
        {
            break;
        }
        swap(arr,i-1,j-1);
    }

    POP();//pivot
    return j;
}

//----------------------------------------------------------------------------------------
static void qsort(VALUE *arr, int p, int r, VALUE* blk) // tail recursion
{
    while( 0<=p && p<r )
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
}

//----------------------------------------------------------------------------------------
void _clp_qsort_hc(int argno)
{
    printf("hc");

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

