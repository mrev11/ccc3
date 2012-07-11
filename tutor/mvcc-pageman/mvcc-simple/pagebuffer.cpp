

#include <string.h>
#include <cccapi.h>


void _clp_pagebuffer(int argno)
{
    CCC_PROLOG("pagebuffer",1);
    int size=_parni(1);
    char *p=binaryl(size);
    memset(p,0,size);
    _rettop();
    CCC_EPILOG();
}
