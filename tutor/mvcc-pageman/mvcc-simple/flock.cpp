

#include <sys/file.h>
#include <cccapi.h>
#include <flock.ch>


void _clp_flock(int argno)
{
    CCC_PROLOG("flock",2);

    int fd=_parni(1);
    int cccop=_parni(2);

    int op=0;
    if( cccop&FLOCK_SH ) op|=LOCK_SH;
    if( cccop&FLOCK_EX ) op|=LOCK_EX;
    if( cccop&FLOCK_UN ) op|=LOCK_UN;
    if( cccop&FLOCK_NB ) op|=LOCK_NB;
    
    _retni( flock(fd,op) );  //success 0, error -1

    CCC_EPILOG();
}
