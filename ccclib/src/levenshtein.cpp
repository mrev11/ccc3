
// Levenshtein tavolsag szamitasa
//
// levenshtein_distance(x,y)
// levenshtein_substring(aa,bbb)
//
// o(len(x)*len(y)) muveletet vegez


#include <cccapi.h>


//-----------------------------------------------------------------------------------
static void print0(CHAR*y, int ly)
{
    printf("\n              ");
    for( int j=0; j<ly; j++ )
    {
        printf( "%5c", (char)y[j] );
    }
}

//-----------------------------------------------------------------------------------
static void print(int i, CHAR c, int*dc, int ly)
{
    printf("\nrow=%-2d %c ",i,(char)c);
    for( int j=0; j<ly; j++ )
    {
        printf( "%5d", dc[j] );
    }

}

//-----------------------------------------------------------------------------------
void _clp_levenshtein_distance(int argno)  //termelesi implementacio
{
    CCC_PROLOG("levenshtein_distance",2);

    CHAR *x=_parc(1);
    int lx=_parclen(1);
    CHAR *y=_parc(2);
    int ly=_parclen(2);
    
    int ii,jj,c,c1;
    int *dp,*dc,*tmp;    
    int dist=0;
    
    lx++;
    ly++;
    
    dp=(int*)malloc(ly*sizeof(int));
    dc=(int*)malloc(ly*sizeof(int));

    for(jj=0; jj<ly; jj++)
    {
        dc[jj]=jj;
    }
    //print0(y,ly);
    //print(0,' ',dc,ly);
    
    for( ii=1; ii<lx; ii++ ) //sorok
    {
        tmp=dp;
        dp=dc;
        dc=tmp;
        dc[0]=ii;
    
        for( jj=1; jj<ly; jj++ ) //oszlopok
        {
            c1=dp[jj]+1;                                 c=c1; // le
            c1=dc[jj-1]+1;                      if(c>c1) c=c1; // jobbra
            c1=dp[jj-1]+(x[ii-1]==y[jj-1]?0:1); if(c>c1) c=c1; // jobbra-le
            dc[jj]=c;
        }
        //print(ii,x[ii-1],dc,ly);
    }

    dist=dc[ly-1];

    free(dp);
    free(dc);

    _retni(dist);
    CCC_EPILOG();
}


//-----------------------------------------------------------------------------------
void _clp_levenshtein_substring(int argno)  // levenshtein_substring(aa,bbb)
{
    CCC_PROLOG("levenshtein_substring",2);

    CHAR *aa=_parc(1);          // rovidebb
    int len_aa=_parclen(1);

    CHAR *bbb=_parc(2);         // hosszabb
    int len_bbb=_parclen(2);
    
    int idx_aa,idx_bbb,c,c1;
    int *dp,*dc,*tmp;    
    int dist=0;
    
    len_aa++;    
    len_bbb++;   
    
    dp=(int*)malloc(len_aa*sizeof(int));
    dc=(int*)malloc(len_aa*sizeof(int));

    for(idx_aa=0; idx_aa<len_aa; idx_aa++)
    {
        dc[idx_aa]=idx_aa;
    }

    //print0(aa,len_aa);
    //print(0,' ',dc,len_aa);
    
    for( idx_bbb=1; idx_bbb<len_bbb; idx_bbb++ ) //sorok
    {
        tmp=dp;
        dp=dc;
        dc=tmp;
        dc[0]=0;
    
        for( idx_aa=1; idx_aa<len_aa; idx_aa++ ) //oszlopok
        {
            c1=dp[idx_aa]+(idx_aa==len_aa-1?0:1);                        c=c1; // le
            c1=dc[idx_aa-1]+1;                                  if(c>c1) c=c1; // jobbra
            c1=dp[idx_aa-1]+(bbb[idx_bbb-1]==aa[idx_aa-1]?0:1); if(c>c1) c=c1; // jobbra-le
            dc[idx_aa]=c;
        }
        //print(idx_bbb,bbb[idx_bbb-1],dc,len_aa);
    }

    dist=dc[len_aa-1];

    free(dp);
    free(dc);

    _retni(dist);

    CCC_EPILOG();
}

//-----------------------------------------------------------------------------------

