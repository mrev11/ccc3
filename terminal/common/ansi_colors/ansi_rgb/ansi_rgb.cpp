
#include <stdio.h>
#include <stdlib.h>

#include <log-ansi_rgb_h>

//----------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    int x=0;
    if( argc>1 )
    {
        x=atoi(argv[1]);
    }

    int r,g,b; 
    ansi_rgb(x,&r,&g,&b);
    printf("%d - %02x %02x %02x\n",x,r,g,b);

    return 0;
}

//----------------------------------------------------------------------------------------

