

#include <cccapi.h>


//----------------------------------------------------------------------------------------
void _clp_realpath(int argno)
{
    CCC_PROLOG("realpath",1);
    convertfspec2nativeformat(base);
    char *path=_parb(1);
    char *rpath=realpath(path,0);
    if( rpath )
    {
        _retcb( rpath );
        free(rpath);
    }
    else
    {
        _ret();
    }
    
    CCC_EPILOG();
}


//----------------------------------------------------------------------------------------


