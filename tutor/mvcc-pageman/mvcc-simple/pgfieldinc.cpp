
#include <cccapi.h>


//----------------------------------------------------------------------------
void _clp_pgfield_increment(int argno)  // hexában megadtott számot növel
{
    CCC_PROLOG("pgfield_increment",1);
    char *p=_parb(1);
    int w=_parblen(1);
    char buf[32];
    unsigned long x;
    sscanf(p,"%lx",&x);
    sprintf(buf,"%0*lx",w,x+1);
    _retblen(buf,w);
    CCC_EPILOG();
}

//----------------------------------------------------------------------------


