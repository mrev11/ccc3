
#include <cccapi.h>

int cccver()
{
    #ifdef _CCC3_
        return 3;
    #else
        return 2;
    #endif
}

void _clp_cccver(int argno)
{
    stack-=argno;
    number( cccver() );
}

