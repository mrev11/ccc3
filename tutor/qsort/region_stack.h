

#define STKSIZ 100

//----------------------------------------------------------------------------------------
struct region_stack
{
    int stkptr=0;

    struct
    {
        int lo;
        int hi;

    } stk[STKSIZ];
    
    void push(int p, int r)
    {
        if( stkptr>=STKSIZ )
        {
            fprintf(stderr,"region stack overflow\n");
            exit(1);
        }

        stk[stkptr].lo=p;
        stk[stkptr].hi=r;
        ++stkptr;
    }

    int pop(int *p, int *r)
    {
        if( stkptr>0 )
        {
            --stkptr;
            *p=stk[stkptr].lo;
            *r=stk[stkptr].hi;
            return 1; 
        }
        return 0; 
    }
};


//----------------------------------------------------------------------------------------
