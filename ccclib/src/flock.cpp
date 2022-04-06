
/*
 *  CCC - The Clipper to C++ Compiler
 *  Copyright (C) 2005 ComFirm BT.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */


#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>
#include <errno.h>

#include <cccapi.h>
#include <flock.h>

//#define DEBUG


#ifdef UNIX
//------------------------------------------------------------------------------------------
static void sighnd(int signum)
{
#ifdef DEBUG
    printf("SIGALRM\n");
#endif
}

static int init_timeout()
{
    int timeout=0;
    const char *env=getenv("CCCLK_TIMEOUT");
    if( env && *env )
    {
        timeout=atoi(env);
    }
    if( timeout>0 )
    {
        //SIGALRM handler
        struct sigaction act;
        memset(&act,0,sizeof(act));
        act.sa_handler=sighnd;
        sigaction(SIGALRM,&act,0);
    }
    return timeout;
}

//------------------------------------------------------------------------------------------
int _ccc_lock(int fd, unsigned low, unsigned high, unsigned length, unsigned flags)
{
    static int timeout=init_timeout();

    off_t start=high;
    start=(start<<32)+low;
    int type=(flags&CCCLK_READ) ? F_RDLCK : F_WRLCK;
    int lock=(flags&CCCLK_WAIT) ? F_SETLKW : F_SETLK;
    int tout=(flags&CCCLK_TIMEOUT);
    
    if( tout && (timeout<=0) )
    {
        lock=F_SETLK; //fallback: timeout not configured
    }

    struct flock fl;
    fl.l_whence = SEEK_SET;
    fl.l_start  = start;
    fl.l_len    = length;
    fl.l_type   = type;

    if( tout && (timeout>0) )
    {
        alarm(timeout); //set timeout
    }
 
    int result;
    do
    {
        result=fcntl(fd,lock,&fl);
    }
    while((result!=0) && (errno==EINTR) && lock==F_SETLKW && (tout==0));

    if( tout && (timeout>0) )
    {
        alarm(0); //clear timeout
    }

#ifdef DEBUG
    printf("pid=%d fd=%d  start=%llx  timeout=%s:%d  %-6s  %-5s  %s\n",
                getpid(),
                fd,
                (long long)start,
                tout?"Y":"N",
                timeout,
                lock==F_SETLKW ? "wait":"nowait",
                type==F_RDLCK ? "read":"write",
                result==0 ? "Ok":"Failed");
#endif

    return result; //OK 0, error -1
}


//------------------------------------------------------------------------------------------
int _ccc_unlock(int fd, unsigned low, unsigned high, unsigned length)
{
    off_t start=high;
    start=(start<<32)+low;
    int type=F_UNLCK;
    int lock=F_SETLK;

    struct flock fl;
    fl.l_whence = SEEK_SET;
    fl.l_start  = start;
    fl.l_len    = length;
    fl.l_type   = type;
    return fcntl(fd,lock,&fl); //OK 0, error -1
}

//------------------------------------------------------------------------------------------
#else //WINDOWS
//------------------------------------------------------------------------------------------
int _ccc_lock(int fd, unsigned low, unsigned high, unsigned length, unsigned flags)
{
    OVERLAPPED overlapped={0,0,0,0,NULL};
    overlapped.Offset=low;
    overlapped.OffsetHigh=high;

    int tout=(flags&CCCLK_TIMEOUT);
    int mode=0;
    if( !tout )
    {
        mode+=(flags&CCCLK_READ) ? 0 : LOCKFILE_EXCLUSIVE_LOCK; 
        mode+=(flags&CCCLK_WAIT) ? 0 : LOCKFILE_FAIL_IMMEDIATELY;  
    }
    else 
    {
        //fallback: timeout not supported
        mode+=(flags&CCCLK_READ) ? 0 : LOCKFILE_EXCLUSIVE_LOCK; 
        mode+=LOCKFILE_FAIL_IMMEDIATELY;  
    }

    int result=LockFileEx(  (HANDLE)_get_osfhandle(fd),
                            mode,
                            0,
                            length,
                            0,
                            &overlapped );
#ifdef DEBUG
    off_t start=high;
    start=(start<<32)+low;
    int timeout=0;

    printf("pid=%d fd=%d  start=%llx  timeout=%s:%d  %-6s  %-5s  %s\n",
                getpid(),
                fd,
                (long long)start,
                tout?"Y":"N",
                timeout,
                (mode & LOCKFILE_FAIL_IMMEDIATELY) ? "nowait":"wait",
                (mode & LOCKFILE_EXCLUSIVE_LOCK) ? "write":"read",
                result ? "Ok":"Failed");
#endif

    return (result==0)?-1:0; //OK 0, error -1                       
}

//------------------------------------------------------------------------------------------
int _ccc_unlock(int fd, unsigned low, unsigned high, unsigned length)
{
    int result=UnlockFile(  (HANDLE)_get_osfhandle(fd),
                            low,
                            high,
                            length,
                            0 );

    return (result==0)?-1:0;  //OK 0, error -1                       
}
//------------------------------------------------------------------------------------------

#endif

