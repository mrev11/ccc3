
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

#undef ASYNC
#define ASYNC


#undef   min
#undef   max
#define  min(x,y)   ((x)<(y)?(x):(y))
#define  max(x,y)   ((x)>(y)?(x):(y))


#undef MUTEX_CREATE
#undef MUTEX_LOCK
#undef MUTEX_UNLOCK

#if ! defined ASYNC     // SYNC-UNIX-WINDOWS

#define MUTEX_CREATE(x)
#define MUTEX_LOCK(x)
#define MUTEX_UNLOCK(x)

#elif defined UNIX      // ASYNC-UNIX

#include <pthread.h>

#define MUTEX_CREATE(x)    static pthread_mutex_t x=PTHREAD_MUTEX_INITIALIZER
#define MUTEX_LOCK(x)      pthread_mutex_lock(&x)
#define MUTEX_UNLOCK(x)    pthread_mutex_unlock(&x)

#else                   // ASYNC-WINDOWS

#define MUTEX_CREATE(x)    static HANDLE x=CreateMutex(0,0,0)
#define MUTEX_LOCK(x)      WaitForSingleObject(x,INFINITE)
#define MUTEX_UNLOCK(x)    ReleaseMutex(x)

#endif


extern int signal_raise(int);

