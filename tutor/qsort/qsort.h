

#define DMOD(x,y) ((x)-floor((x)/(y))*(y))

//----------------------------------------------------------------------------------------
static unsigned rand(int m)  // random [0,m)
{
    static double FACTOR  =  16807.0;
    static double MODULUS =  2147483647.0;
    static double seed    =  7657463.0;
    seed*=FACTOR;
    seed=DMOD(seed,MODULUS);
    return ((unsigned)seed)%m;
}

//----------------------------------------------------------------------------------------
static void swap(VALUE *x, VALUE*y)
{
    push(x);
    *x=*y;
    *y=*TOP();
    POP();
}

//----------------------------------------------------------------------------------------
static int compare(VALUE *a, VALUE *b, VALUE *blk)
{
    int cmp=0;
    if( blk )
    {
        push(blk);
        push(a);
        push(b);
        _clp_eval(3);
        if( TOP()->type!=TYPE_NUMBER )
        {
            error_gen(CHRLIT("wrong return type"),"compare block of sorting",TOP(),1);
            exit(1);
        }
        cmp=TOP()->data.number;
        POP();
    }
    else
    {
        cmp=stdcmp(a,b); //default ascend
    }
    return cmp;
}

//----------------------------------------------------------------------------------------
static int m3( VALUE *arr, int p, int r, VALUE *blk ) // median of 3 elements
{
    int lo=p+rand(r-p+1);
    int md=p+rand(r-p+1);
    int hi=p+rand(r-p+1);
    int tmp;

    if( 0<compare( arr+lo-1, arr+hi-1, blk) ){ tmp=lo; lo=hi; hi=tmp; }
    if( 0<compare( arr+lo-1, arr+md-1, blk) ){ tmp=lo; lo=md; md=tmp; }
    if( 0<compare( arr+md-1, arr+hi-1, blk) ){ tmp=md; md=hi; hi=tmp; }

    return md; // 1 based
}

//----------------------------------------------------------------------------------------
static VALUE *push_pivot(VALUE *arr, int p, int r, VALUE *blk) // stack: -- pivot
{
#if defined PIVOT_MEDIAN
    int pivot_index=m3(arr,p,r,blk);

#elif defined PIVOT_RANDOM
    int pivot_index=p+rand(r-p+1);

#else  // PIVOT_MIDDLE
    int pivot_index=p+(r-p)/2;

#endif

    //printf("\n%7d  pivot_index: %7d %7d %7d", r-p+1, p, pivot_index ,r);

    push( arr+pivot_index-1 );
    return TOP();
}

//----------------------------------------------------------------------------------------
static void isort(VALUE *arr, int p, int r, VALUE* blk)  //insertion sort
{
    int i=p+1,j;
    VALUE *x;

    while( i<=r )
    {
        push( arr+i-1 );
        x=TOP();
        j=i;
        while( j>p && 0<compare(arr+j-2,x,blk) )
        {
            arr[j-1]=arr[j-2];
            j--;
        }
        arr[j-1]=*x;
        i++;
        POP(); //x
    }
}

//----------------------------------------------------------------------------------------



