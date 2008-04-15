
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

#ifndef _SCKCOMPAT_H_

//Ezek kiegyenlítik a UNIX és a Windows
//közötti különbségek túlnyomó részét.


#ifndef _UNIX_
//Windows header files

#include <windows.h>
#include <winsock.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int                     SOCKLEN_T; 
 
#define SOL_TCP                 IPPROTO_TCP
#define now()                   GetTickCount()
#define MSG_NOSIGNAL            0
 
#else
//UNIX header files

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/times.h>
#include <unistd.h>

#ifdef _SOLARIS_
#include <sys/filio.h>
#endif

#ifndef MSG_NOSIGNAL
#define MSG_NOSIGNAL            0  // send SIGPIPE-ot adhat!
#endif
 
 
typedef int                     BOOL;
typedef unsigned long           DWORD;
typedef int                     SOCKET;
typedef struct sockaddr_in      SOCKADDR_IN;
typedef struct sockaddr         SOCKADDR;
typedef struct in_addr          IN_ADDR; 
typedef SOCKADDR*               LPSOCKADDR;
typedef socklen_t               SOCKLEN_T;

#define GetLastError()          errno
#define ioctlsocket             ioctl
#define closesocket             close
#define WSAEWOULDBLOCK          EWOULDBLOCK  

#endif
#endif
 
#define _SCKCOMPAT_H_

