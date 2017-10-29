
#ifdef _UNIX_

#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>

//-----------------------------------------------------------------------------
int fsetlock(int fd, int pos, int nbyte)  //UNIX
{
    struct flock fl;

    fl.l_whence = SEEK_SET;
    fl.l_start  = pos;
    fl.l_len    = nbyte;
    fl.l_type   = F_WRLCK;

    return fcntl(fd,F_SETLK,&fl); //OK 0, error -1
}

//-----------------------------------------------------------------------------
int funlock(int fd, int pos, int nbyte)  //UNIX
{
    struct flock fl;

    fl.l_whence = SEEK_SET;
    fl.l_start  = pos;
    fl.l_len    = nbyte;
    fl.l_type   = F_UNLCK;

    return fcntl(fd,F_SETLK,&fl);  //OK 0, error -1
}

//-----------------------------------------------------------------------------
#else  //WINDOWS
//-----------------------------------------------------------------------------

#include <windows.h>
#include <stdio.h>
#include <io.h>
#include <sys\locking.h>


//-----------------------------------------------------------------------------
int fsetlock(int fd, int pos, int nbyte)  //WINDOWS
{
    return LockFile((HANDLE)_get_osfhandle(fd),pos,0,nbyte,0)? 0:-1;
}


//-----------------------------------------------------------------------------
int funlock(int fd, int pos, int nbyte)  //WINDOWS
{
    return UnlockFile((HANDLE)_get_osfhandle(fd),pos,0,nbyte,0)? 0:-1;
}


//-----------------------------------------------------------------------------
#endif
