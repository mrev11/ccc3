
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

#include <sckcompat.h>
#include <sckutil.h>

static char *s_interface="127.0.0.1";
static int  s_helper=50000;
 
#define THREAD(x,a)  CreateThread(0,0,(LPTHREAD_START_ROUTINE)x,a,0,0)


//----------------------------------------------------------------------------
static void *thconnect(int *cs)
{
    int n=0;
    SOCKET sck=socket_new();
    while( 0>socket_connect(sck,s_interface,s_helper) )
    {
        if( n++<10  )
        {
            //printf("wait for connect ...\n");
            Sleep(10);
        }
        else
        {
            *cs=-1;
            return (void*)-1; //failed
        }
    }
    *cs=sck;
    return 0; //OK
}

//----------------------------------------------------------------------------
int socket_pair( int sp[2] )
{
    int s0,s1,s2;
    
    s0=socket_new();
    while( 0>socket_bind(s0,s_interface,s_helper) )
    {
        s_helper++;
        
        if( (s_helper&0xffff)==0 )
        {
            fprintf(stderr,"socket_pair failed (no free port)\n");
            return -1;
        }
    }

    if( 0>socket_listen(s0) )
    {
        fprintf(stderr,"socket_pair failed (listen)\n");
        return -1;
    }
        
    HANDLE th=THREAD(thconnect,&s2);
    
    s1=socket_accept(s0);             
    if( s1<0 )
    {
        fprintf(stderr,"socket_pair failed (accept)\n");
        return -1;
    }

    socket_close(s0);    
    int count=0;
    DWORD exitcode=1;
    while( (++count<100) && GetExitCodeThread(th,&exitcode) && exitcode )
    {
        //printf("wait for thread ...\n");
        Sleep(10);
    }
    
    if( exitcode )
    {
        fprintf(stderr,"thconnect failed\n");
        return -1;
    }

    sp[0]=s1;
    sp[1]=s2;
 
    return 0;
}


//----------------------------------------------------------------------------
