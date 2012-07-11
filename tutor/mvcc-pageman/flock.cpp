

#include <sys/file.h>
#include <cccapi.h>
#include <flock.ch>

namespace _nsp_pageman {


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



void _clp_rlock(int argno)  //UNIX
{
    CCC_PROLOG("rlock",3);
    
    int   fd    = _parni(1);
    off_t pos   = (off_t)_parnu(2); 
    off_t nbyte = (off_t)_parnu(3);
 
    struct flock fl;

    fl.l_whence = SEEK_SET;
    fl.l_start  = pos;
    fl.l_len    = nbyte;
    fl.l_type   = F_WRLCK;

    _retni( fcntl(fd,F_SETLK,&fl))  ;

    CCC_EPILOG();
}


void _clp_runlock(int argno)  //UNIX
{
    CCC_PROLOG("runlock",3);
    
    int   fd    = _parni(1);
    off_t pos   = (off_t)_parnu(2); 
    off_t nbyte = (off_t)_parnu(3);
 
    struct flock fl;

    fl.l_whence = SEEK_SET;
    fl.l_start  = pos;
    fl.l_len    = nbyte;
    fl.l_type   = F_UNLCK;

    _retni( fcntl(fd,F_SETLK,&fl))  ;

    CCC_EPILOG();
}

}//namespace
