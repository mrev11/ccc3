

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
static void qsplit( VALUE *arr, int p, int r, int *q1, int *q2, VALUE *blk )
{
    int lt=p; // 1 based
    int eq=p; // 1 based
    int gt=r; // 1 based

    push(arr+p-1+xrand()%(r-p+1));
    VALUE *pivot=TOP();
    
    while( eq<=gt )
    {
        int cmp;
        if( blk )
        {
            push(blk);
            push(arr+eq-1);
            push(pivot);
            _clp_eval(3);
            cmp=TOP()->data.number;
            POP();
        }
        else
        {
            cmp=stdcmp(arr+eq-1,pivot);
        }

        if( cmp<0 )
        {
            swap(arr,eq-1,lt-1);
            lt++;
            eq++;
        }
        else if( cmp>0 )
        {
            swap(arr,eq-1,gt-1);
            gt--;
        }
        else
        {
            eq++;
        }
    }

#ifdef DEBUG
    push(pivot);
    number(lt);  _clp_str(1); _clp_alltrim(1);
    number(eq);  _clp_str(1); _clp_alltrim(1);
    number(gt);  _clp_str(1); _clp_alltrim(1);

    for( int i=p; i<=lt-1; i++ )
    {
        push(arr+i-1);
    }
    array(lt-p);

    for( int i=lt; i<=eq-1; i++ )
    {
        push(arr+i-1);
    }
    array(eq-lt);

    for( int i=eq; i<=r; i++ )
    {
        push(arr+i-1);
    }
    array(r-eq+1);

    _clp_qout(7);
    pop();
#endif

    *q1=lt-1;
    *q2=eq;    

    POP();//pivot
}

//----------------------------------------------------------------------------------------
static void qsort(VALUE *arr, int p, int r, VALUE* blk) // tail recursion
{
    while( p<r )
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
}

//----------------------------------------------------------------------------------------
void _clp_qsort_3c(int argno)
{
    printf("3c");

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

