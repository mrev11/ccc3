
/*
 *  CCC - The Clipper to C++ Compiler
 *  Copyright (C) 2005 ComFirm BT.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

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
    if( blk==0 || blk->type==TYPE_NIL )
    {
        cmp=stdcmp(a,b); //default ascend
    }
    else if( blk->type==TYPE_FLAG )
    {
        cmp=blk->data.flag ? stdcmp(a,b):stdcmp(b,a);  //asc/desc
    }
    else
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
    return cmp;
}

//----------------------------------------------------------------------------------------
static int comparex(VALUE *a, unsigned x, unsigned y, VALUE *blk)
{
    int cmp=0;

    if( blk==0 || blk->type==TYPE_NIL )
    {
        cmp=stdcmp(a+x,a+y); //default ascend
    }
    else if( blk->type==TYPE_FLAG )
    {
        cmp=blk->data.flag ? stdcmp(a+x,a+y):stdcmp(a+y,a+x);  //asc/desc
    }
    else
    {
        push(blk);
        push(a+x);
        push(a+y);
        _clp_eval(3);
        if( TOP()->type!=TYPE_NUMBER )
        {
            error_gen(CHRLIT("wrong return type"),"compare block of sorting",TOP(),1);
            exit(1);
        }
        cmp=TOP()->data.number;
        POP();
    }

    return cmp;
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
static int guess_median(VALUE *arr, int p, int r, VALUE* blk, int m)
{
    int index[m];
    int x,i,j;
    index[0]=p;
    for(  i=1; i<m-1; i++)
    {
        index[i]=index[i-1]+(r-p+1)/(m-1);
    }
    index[m-1]=r;
    //printf("\n\n>>"); for(int n=0; n<m; n++) printf(" %d ",index[n]);

    i=1;
    while( i<m )
    {
        x=index[i];
        j=i;
        //printf("\ncompare p=%-2d r=%-2d  %3d %3d",p,r,index[j-1],x);
        while( j>0 && 0<comparex(arr,index[j-1]-1,x-1,blk) )
        {
            index[j]=index[j-1];
            j--;
        }
        index[j]=x;
        i++;
    }
    return index[(m+1)/2-1];
}

//----------------------------------------------------------------------------------------
#ifdef PIVOT_MIDDLE
static int pivot_index(VALUE *arr, int p, int r, VALUE *blk)
{
    return p+(r-p+1)/2;
}
#endif

#ifdef PIVOT_RANDOM
static int pivot_index(VALUE *arr, int p, int r, VALUE *blk)
{
    return p+rand(r-p+1);
}
#endif

#ifdef PIVOT_MEDIAN
static int pivot_index(VALUE *arr, int p, int r, VALUE *blk)
{
    int len=r-p+1;
    if( blk==0 )
    {
        return p+len/2;
    }
    else if( len<200 )
    {
        return guess_median(arr,p,r,blk,3);
    }
    else if( len<1000 )
    {
        return guess_median(arr,p,r,blk,5);
    }
    else
    {
        return guess_median(arr,p,r,blk,7);
    }
}
#endif

//----------------------------------------------------------------------------------------
static VALUE *push_pivot(VALUE *arr, int p, int r, VALUE *blk) // stack: -- pivot
{
    int px=pivot_index(arr,p,r,blk);
    //printf("\n%7d  pivot_index: %7d %7d %7d", r-p+1, p, px ,r); fflush(0);
    push( arr+px-1 );
    return TOP();
}

//----------------------------------------------------------------------------------------



