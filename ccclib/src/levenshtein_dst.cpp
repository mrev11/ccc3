
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
    printf("\n");
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
void _clp_levenshtein_distance(int argno)  // levenshtein_distance(a,b)
{
    CCC_PROLOG("levenshtein_distance",2);

    CHAR *a=_parc(1);
    int lena=_parclen(1);

    CHAR *b=_parc(2);
    int lenb=_parclen(2);
    
    int idxa,idxb,c,c1;
    int *dp,*dc,*tmp;    
    int dist=0;
    
    lena++;    
    lenb++;   
    
    dp=(int*)malloc(lena*sizeof(int));
    dc=(int*)malloc(lena*sizeof(int));

    for(idxa=0; idxa<lena; idxa++)
    {
        dc[idxa]=idxa;
    }

    //print0(a,lena);
    //print(0,' ',dc,lena);
    
    for( idxb=1; idxb<lenb; idxb++ ) //sorok
    {
        tmp=dp;
        dp=dc;
        dc=tmp;
        dc[0]=idxb;
    
        for( idxa=1; idxa<lena; idxa++ ) //oszlopok
        {
            c1=dc[idxa-1]+1;                                     c=c1; // jobbra
            c1=dp[idxa]+1;                              if(c>c1) c=c1; // le
            c1=dp[idxa-1]+(b[idxb-1]==a[idxa-1]?0:1);   if(c>c1) c=c1; // jobbra-le
            dc[idxa]=c;
        }
        //print(idxb,b[idxb-1],dc,lena);
    }

    dist=dc[lena-1];

    free(dp);
    free(dc);

    _retni(dist);

    CCC_EPILOG();
}


//-----------------------------------------------------------------------------------
