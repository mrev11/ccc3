
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


#include <flock.h>

//----------------------------------------------------------------------------------------
#ifdef WINDOWS

#include <fcntl.h>
#include <cccapi.h>

//----------------------------------------------------------------------------------------
static int lowlevel_lock(int fd, unsigned low, unsigned high, unsigned length, int rwtype, int timeout)
{
    OVERLAPPED overlapped={0,0,0,0,NULL};
    overlapped.Offset=low;
    overlapped.OffsetHigh=high;

    int mode=0;
    if( rwtype )
    {
        mode+=LOCKFILE_EXCLUSIVE_LOCK;
    }
    if( timeout>=0  ) 
    {
        mode+=LOCKFILE_FAIL_IMMEDIATELY;
    }

    // timeout = 0: nem var
    // timeout > 0: nincs tamogatva -> nem var
    // timeout < 0: korlatlan ideig var

    int result=LockFileEx(  (HANDLE)_get_osfhandle(fd),
                            mode,
                            0,
                            length,
                            0,
                            &overlapped );

    return (result==0)?-1:0; //OK 0, error -1                       
}

//----------------------------------------------------------------------------------------
static int lowlevel_unlock(int fd, unsigned low, unsigned high, unsigned length)
{
    int result=UnlockFile(  (HANDLE)_get_osfhandle(fd),
                            low,
                            high,
                            length,
                            0 );

    return (result==0)?-1:0;  //OK 0, error -1                       
}

#endif // WINDOWS
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
#ifdef _UNIX_

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <signal.h>

#include <cccapi.h>

#define TIMEOUT_SIGNAL SIGALRM
// #define TIMEOUT_SIGNAL SIGUSR1
// #define TIMEOUT_SIGNAL SIGUSR2

// POSIX names to access some of the members.  
//  #define sigev_notify_function   _sigev_un._sigev_thread._function
//  #define sigev_notify_attributes _sigev_un._sigev_thread._attribute

// platform specifikus

#ifdef _LINUX_
#define sigev_notify_thread_id  _sigev_un._tid
#endif

#ifdef _FREEBSD_
#include <sys/thr.h>
long gettid()
{
    long id=0;
    thr_self(&id);
    return id;
}
#define sigev_notify_thread_id  _sigev_un._threadid
#endif

#ifdef _NETBSD_
static int lowlevel_locktime(int fd, struct flock *fl, unsigned timeout_ms)
{
    return -1; // SIGEV_THREAD_ID not supported
}

#else //LINUX,FREEBSD
//----------------------------------------------------------------------------------------
static void sighandler(int signum)
{
    //empty
}

static int init_sighandler()
{    
    struct sigaction act;
    memset(&act,0,sizeof(act));
    act.sa_handler=sighandler;
    sigaction(TIMEOUT_SIGNAL,&act,0);
    return 1;
}

//----------------------------------------------------------------------------------------
static int lowlevel_locktime(int fd, struct flock *fl, unsigned timeout_ms)
{
    static int init=init_sighandler();

    struct sigevent sev;
    memset(&sev,0,sizeof(struct sigevent));
    sev.sigev_notify=SIGEV_THREAD_ID;
    sev.sigev_signo=TIMEOUT_SIGNAL;
    sev.sigev_notify_thread_id=gettid(); // platform specifikus makro

    timer_t timerid;
    if( timer_create(CLOCK_REALTIME,&sev,&timerid) )
    {
        // lehetne errno==EAGAIN-t vizsgalni
        fprintf(stderr,"timer_create() failed: errno=%d (%s)\n",errno,strerror(errno));
        return -1;
    }

    struct itimerspec timeout;
    memset(&timeout,0,sizeof(timeout));
    timeout.it_value.tv_sec  = (timeout_ms/1000);
    timeout.it_value.tv_nsec = (timeout_ms%1000)*1000000;
    timer_settime(timerid,0,&timeout,NULL);

    int result=fcntl(fd,F_SETLKW,fl);

    timer_delete(timerid);

    return result;
}
#endif

//----------------------------------------------------------------------------------------
static int lowlevel_lock(int fd, unsigned low, unsigned high, unsigned length, int rwtype, int timeout)
{
    off_t start=high;
    start=(start<<32)+low;

    struct flock fl;
    fl.l_whence = SEEK_SET;
    fl.l_start  = start;
    fl.l_len    = length;
    fl.l_type   = rwtype?F_WRLCK:F_RDLCK;

    if( 0==fcntl(fd,F_SETLK,&fl) )
    {
        return 0;
    }
    else if( timeout==0 )
    {
        return -1;
    }
    else if( timeout<0 )
    {
        return fcntl(fd,F_SETLKW,&fl);
    }
    else
    {
        return( lowlevel_locktime(fd,&fl,timeout) ); // OK 0, error -1
    }
}

//----------------------------------------------------------------------------------------
static int lowlevel_unlock(int fd, unsigned low, unsigned high, unsigned length)
{
    off_t start=high;
    start=(start<<32)+low;

    struct flock fl;
    fl.l_whence = SEEK_SET;
    fl.l_start  = start;
    fl.l_len    = length;
    fl.l_type   = F_UNLCK;
    return fcntl(fd,F_SETLK,&fl); // OK 0, error -1
}

#endif // _UNIX_


//----------------------------------------------------------------------------------------
// public interface
//----------------------------------------------------------------------------------------
int fsetlock(int fd, unsigned low, unsigned high, unsigned length, int rwtype)
{
    return lowlevel_lock(fd,low,high,length,rwtype,0);
}
//----------------------------------------------------------------------------------------
int fwaitlock(int fd, unsigned low, unsigned high, unsigned length, int rwtype)
{
    return lowlevel_lock(fd,low,high,length,rwtype,-1);
}
//----------------------------------------------------------------------------------------
int ftimeoutlock(int fd, unsigned low, unsigned high, unsigned length, int rwtype, int timeout)
{
    return lowlevel_lock(fd,low,high,length,rwtype,timeout);
}
//----------------------------------------------------------------------------------------
int funlock(int fd, unsigned low, unsigned high, unsigned length)
{
    return lowlevel_unlock(fd,low,high,length);
}
//----------------------------------------------------------------------------------------


