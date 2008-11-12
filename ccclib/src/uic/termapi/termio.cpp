
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>

#ifdef WINDOWS
#include <process.h>
#endif

#include <sckcompat.h>
#include <sckutil.h>
#include <inttypes.h>
#include <termcmd.h>
#include <termio.h>
#include <termapi.h>

#include <signal.ch>
#include <cccapi.h>


static int termsck=-1;

//----------------------------------------------------------------------------
static void error(const char *msg)
{
    fprintf(stderr,"%s error=%d\n",msg,socket_error());
    signal_raise(SIG_TERM);
    exit(1);
}

//----------------------------------------------------------------------------
static void sleep(int ms)
{
#ifdef UNIX
    struct timeval t;
    t.tv_sec=ms/1000;
    t.tv_usec=(ms%1000)*1000;
    select(0,0,0,0,&t);
#else
    Sleep(ms);
#endif
}

//----------------------------------------------------------------------------
static void atexit_bye()
{
    close(termsck); // jelzés a terminálnak
    sleep(100);     // (0.1sec) a terminál kilép
    
    //A terminál a socket lezáródásából értesül arról, hogy 
    //a szerverprogram kilépett. Így a terminálnak (child)
    //van ideje előbb kilépni, mint ahogy a szerverprogram 
    //(parent) kilépne. Ez akkor fontos, amikor a szerver és 
    //az ncurses terminál ugyanabban az ablakban fut.
}

//----------------------------------------------------------------------------
void connect_to_terminal()
{
    //CCCTERM_CONNECT nincs megadva    -> connect 127.0.0.1:55000
    //CCCTERM_CONNECT létező termspec  -> automatikusan elindítja
    //CCCTERM_CONNECT port             -> connect 127.0.0.1:port
    //CCCTERM_CONNECT :port            -> connect 127.0.0.1:port
    //CCCTERM_CONNECT host:port        -> connect host:port
    //CCCTERM_CONNECT SOCKET:sck       -> örökli a socketet

    char *constr=getenv("CCCTERM_CONNECT");
    struct stat buf;

    if( constr==0 ) //nincs megadva
    {
        termsck=client_socket("127.0.0.1",55000);
        //printf("default:127.0.0.1/55000\n");
    }

    else if( 0==stat(constr,&buf) ) //létező termspec
    {
        int s=socket_new();
        int p, p1=55500, p2=55700;
        //socket_setoption(s,SOCKOPT_REUSEADDR,0);
        for( p=p1; (p<=p2) && (0!=socket_bind(s,"127.0.0.1",p)); p++ )
        {
            //printf("port %d %d\n",p,socket_error());fflush(0);
        }
        if( p>p2 )
        {
            error("bind failed");
        }
        //printf("port %d\n",p);fflush(0);
        if( 0!=socket_listen(s) )
        {
            error("listen failed");
        }
        int clntsck=client_socket("127.0.0.1",p);
        if( clntsck<0 )
        {
            error("connect failed");
        }

        char buf[16];
        const char *argv[4]; //hogy lehet elkerülni a cast-ot (exec-nél)?
        argv[0]=constr;
        argv[1]="--socket";
        argv[2]=buf;sprintf(buf,"%d",clntsck);
        argv[3]=0;

        #ifdef WINDOWS        
            spawnv(P_NOWAIT,argv[0],argv);
            //Windowsban nincs jó hely lezárni s-t.

        #else
            if( fork()==0 )
            {
                socket_close(s);
                execv(argv[0], (char*const*)argv); //kurva anyjukat 
                //csak ha execv sikertelen
                fprintf(stderr,"%s %s %s\n",argv[0],argv[1],argv[2]);
                error("execv failed");
            }
        #endif        
        
        termsck=socket_accept(s);
        socket_close(s);
        socket_close(clntsck);
        if( termsck<0 )
        {
            error("accept failed");
        }
        atexit(atexit_bye);
    }

    else
    {
        char host[256];
        int port=0;
        char *colon=strchr(constr,':');

        if( colon==0 )
        {
            strcpy(host,"127.0.0.1");
            sscanf(constr,"%d",&port);
        }
        else if( colon==constr )
        {
            strcpy(host,"127.0.0.1");
            sscanf(constr+1,"%d",&port);
        }
        else
        {
            *colon=(char)0;
            strcpy(host,constr);
            *colon=':';
            sscanf(colon+1,"%d",&port);
        }
        
        if( strcmp(host,"SOCKET")==0 )
        {
            termsck=port;
            //printf("inherit:%d\n",termsck);
        }
        else
        {
            termsck=client_socket(host,port);
            //printf("connect:%s/%d(%d)\n",host,port,termsck);
        }
    }

    if( termsck<0 )
    {
        error("connect_to_terminal failed");
    }
}

//--------------------------------------------------------------------------
int termio_send(void* source, int size) //adatküldés
{ 
    //printf("termio_send: %d\n",size);fflush(0);

    char *buffer=(char*)source;
    int result, nbyte=0;
    
    while( size>nbyte )
    {
        result=socket_write(termsck,buffer+nbyte,size-nbyte);
        if( result<0 )
        {
            error("termio_send failed");
        }
        nbyte+=result;
    }
    return nbyte;
}

//----------------------------------------------------------------------------
int termio_recv(void *destination, int size, int timeout, int errflag)
{
    //printf("termio_recv size %d timeout %d errflag %d\n",size,timeout,errflag);fflush(0);

    char *buffer=(char*)destination;
    int nbyte=socket_read(termsck,buffer,size,timeout);
    if( nbyte>0 && nbyte<size )
    {
        //jott valamennyi, de nem az osszes:
        //a timeout-tol fuggetlenul bevarjuk a csomag veget
        //printf("termio_recv darabol %d\n",nbyte);
        
        int nb=socket_read(termsck,buffer+nbyte,size-nbyte,-1);
        if( nb<0 )
        {
            error("termio_recv failed");
        }
        nbyte+=nb;
    }
    if( errflag && (nbyte!=size) )
    {
        error("termio_recv failed");
    }
    return nbyte;
}

//----------------------------------------------------------------------------
void termio_drop(int size)
{
    int i;
    for( i=0; i<size; i++ )
    {
        char buf;
        int nbyte=socket_read(termsck,&buf,1,-1);
        if( nbyte!=1 )
        {
            error("termio_drop failed");
        }
    }
}

//----------------------------------------------------------------------------

