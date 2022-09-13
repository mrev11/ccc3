

#include <cccapi.h>

//----------------------------------------------------------------------------------------
void _clp_realpath(int argno)
{
    CCC_PROLOG("realpath",1);
    convertfspec2nativeformat(base);

    #ifdef _CCC3_    
        bin2str(base);
        CHAR *path=_parc(1);
        CHAR *fpath=_wfullpath(0,path,0);
    #else
        char *path=_parc(1);
        char *fpath=_fullpath(0,path,0);
    #endif

    if( fpath )
    {
        _retc(fpath);
        free(fpath);
    }
    else
    {
        _ret();
    }

    CCC_EPILOG();
}


//----------------------------------------------------------------------------------------

