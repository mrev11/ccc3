
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
#include "termcmd.h"
#include "termio.h"
#include "termapi.h"
#include "termutil.h"

#include <signal.ch>


static int termsck=-1;

MUTEX_CREATE(mutex_send);

//----------------------------------------------------------------------------
static void error(const char *msg)
{
    fprintf(stderr,"%s error=%d\n",msg,socket_error());
    signal_raise(SIG_TERM);
    exit(1);

    //A signal_raise kozvetlenul meghivja a CCC signal kezelot.
    //Ertelme, hogy a hibakezeles igy egyszeruen atadhato CCC szintre.
    //Ha a terminalt nem CCC kornyezetben hasznaljuk, akkor kell mellekelni
    //egy signal_raise fuggvenyt.
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
    socket_close(termsck); // jelzes a terminalnak
    sleep(100);     // (0.1sec) a terminal kilep
    
    //A terminal a socket lezarodasabol ertesul arrol, hogy 
    //a szerverprogram kilepett. Igy a terminalnak (child)
    //van ideje elobb kilepni, mint ahogy a szerverprogram 
    //(parent) kilepne. Ez akkor fontos, amikor a szerver es 
    //az ncurses terminal ugyanabban az ablakban fut.
}



#ifdef UNIX
//----------------------------------------------------------------------------
void cccterm_connect_term(char *constr)  // UNIX socket
{
    if( strchr(constr+1,'/')==0 )
    {
        constr++; // "/term.exe" -> "term.exe" (PATH-ban keresi)
    }  
    //printf("cccterm_connect_term [%s]\n",constr);

    int sv[2]={-1,-1}; 
    int clntsck;
    if( 0!=socketpair(AF_LOCAL,SOCK_STREAM,0,sv) )
    {
        error("socketpair failed");
    }
    clntsck=sv[0];
    termsck=sv[1];

    char buf[16];
    const char *argv[4]; //hogy lehet elkerulni a cast-ot (exec-nel)?
    argv[0]=constr;
    argv[1]="--socket";
    argv[2]=buf;sprintf(buf,"%d",clntsck);
    argv[3]=0;

    if( fork()==0 )
    {
        socket_close(termsck);
        execvp(argv[0],(char*const*)argv);
        //csak ha execv sikertelen
        fprintf(stderr,"%s %s %s\n",argv[0],argv[1],argv[2]);
        error("execv failed");
    }
    socket_close(clntsck);
    atexit(atexit_bye);
}

#else
//----------------------------------------------------------------------------
void cccterm_connect_term(char *constr) // TCP socket
{
    if( strchr(constr+1,':')!=0  )
    {
        if( constr[0]=='/' )
        {
            constr++; // "/c:\path\term.exe" -> "c:\path\term.exe"
        }
    }
    else if( strchr(constr+1,'/')!=0 )
    {
        // abs path
    }  
    else if( strchr(constr+1,'\\')!=0 )
    {
        // abs path (windows)
    }
    else
    {
        constr++; // PATH-ban keresi
    }  
    //printf("cccterm_connect_term [[%s]]\n",constr); fflush(0);

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
    if( socket_noinherit(s)<0 )
    {
        error("noinherit failed");
    }

    char buf[16];
    const char *argv[4]; //hogy lehet elkerulni a cast-ot (exec-nel)?
    argv[0]=constr;
    argv[1]="--socket";
    argv[2]=buf;sprintf(buf,"%d",clntsck);
    argv[3]=0;

    #ifdef WINDOWS        
        spawnvp(P_NOWAIT,argv[0],(char*const*)argv);
        //Windowsban nincs jo hely lezarni s-t.
    #else
        if( fork()==0 )
        {
            socket_close(s);
            execvp(argv[0],(char*const*)argv);
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
    
    //extern int remoteio_enabled;
    //remoteio_enabled=0;

    //Amikor a terminal lokalis (raadasul a CCC program gyereke),
    //akkor jobb, ha nincs remote io. Nincs is ertelme, de foleg azert,
    //mert nehezitene a hibakezelest. Pl., ha a CCC program SIGINT-et kap,
    //azt azonnal megkapja a terminal (gyerek) is. Ilyenkor a program
    //a mar kilepett terminalnak probalja kuldeni a hibauzenetet,
    //amibol ujabb signal keletkezik (hiba a hibakezelesben).
}
#endif

//----------------------------------------------------------------------------
void cccterm_connect_listen(char *constr)
{
    if( strchr(constr+1,':')!=0  )
    {
        constr++; // "/c:\path\term.exe" -> "c:\path\term.exe"
    }
    else if( strchr(constr+1,'/')!=0 )
    {
        // abs path
    }  
    else if( strchr(constr+1,'\\')!=0 )
    {
        // abs path (windows)
    }
    else
    {
        constr++; // PATH-ban keresi
    }  
    //printf("cccterm_connect_listen [%s]\n",constr); fflush(0);

    char *termspec=constr;
    int s=socket_new();
    int p, p1=55500, p2=55700;
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

    char buf[16];
    const char *argv[4];
    argv[0]=termspec;
    argv[1]="127.0.0.1";
    argv[2]=buf;sprintf(buf,"%d",p);
    argv[3]=0;

    #ifdef WINDOWS        
        spawnvp(P_NOWAIT,argv[0],(char*const*)argv);
        //Windowsban nincs jo hely lezarni s-t.
    #else
        if( fork()==0 )
        {
            socket_close(s);
            execvp(argv[0],(char*const*)argv);
            //csak ha execv sikertelen
            fprintf(stderr,"%s %s %s\n",argv[0],argv[1],argv[2]);
            error("execv failed");
        }
    #endif        
    
    termsck=socket_accept(s);
    socket_close(s);
    if( termsck<0 )
    {
        error("accept failed");
    }
    atexit(atexit_bye);
}


//----------------------------------------------------------------------------
void cccterm_connect_connect(char *constr)
{
    //printf("cccterm_connect_connect [%s]\n",constr);

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
        sleep(60); //parent frissitesi ciklusa
        //printf("inherit:%d\n",termsck);
    }
    else
    {
        termsck=client_socket(host,port);
        //printf("connect:%s/%d(%d)\n",host,port,termsck); fflush(0);
    }
}

//----------------------------------------------------------------------------
void cccterm_connect_socket(char *constr)
{
    //printf("cccterm_connect_socket [%s]\n",constr);

    termsck=atoi(constr);
    sleep(60); //parent frissitesi ciklusa
}

//----------------------------------------------------------------------------
void connect_to_terminal()
{
    // URI szintaktika
    // CCCTERM_CONNECT=term://termspec      -> socketpar + inditja a terminalt
    // CCCTERM_CONNECT=listen://termspec    -> listen + inditja a terminalt
    // CCCTERM_CONNECT=connect://host:port  -> konnektal host:port-ra
    // CCCTERM_CONNECT=socket://sckdesc     -> orokli a socket descriptort

    // Regebbi formak (comaptibility)
    // CCCTERM_CONNECT nincs megadva        -> connect 127.0.0.1:55000
    // CCCTERM_CONNECT letezo termspec      -> automatikusan elinditja
    // CCCTERM_CONNECT port                 -> connect 127.0.0.1:port
    // CCCTERM_CONNECT :port                -> connect 127.0.0.1:port
    // CCCTERM_CONNECT host:port            -> connect host:port
    // CCCTERM_CONNECT SOCKET:sck           -> orokli a socketet

    char *constr=getenv("CCCTERM_CONNECT");
    //printf("CCCTERM_CONNECT=%s\n",constr); fflush(0);
    struct stat buf;

    if( constr==0 ) //nincs megadva
    {
        termsck=client_socket("127.0.0.1",55000);
    }
    else if( constr==strstr(constr,"term://") )
    {
        cccterm_connect_term(constr+6);
    }
    else if( constr==strstr(constr,"listen://") )
    {
        cccterm_connect_listen(constr+8);
    }
    else if( constr==strstr(constr,"connect://") )
    {
        cccterm_connect_connect(constr+10);
    }
    else if( constr==strstr(constr,"socket://") )
    {
        cccterm_connect_socket(constr+9);
    }

    // compatibility 

    else if( 0==stat(constr,&buf) ) //letezo termspec
    {
        cccterm_connect_term(constr);
    }
    else
    {
        cccterm_connect_connect(constr);
    }


    if( termsck<0 )
    {
        error("connect_to_terminal failed");
    }
    
    
    char *inh=getenv("CCCTERM_INHERIT");
    if(  inh!=0 && 0==strcmp(inh,"yes") )
    {
        char buf[64];
        sprintf(buf,"CCCTERM_CONNECT=SOCKET:%d",termsck);
        putenv(strdup(buf));
        
        //CCCTERM_CONNECT-et a jelen program tobbet nem hasznalja,
        //viszont egy esetleges child process az atallitas hatasara
        //ugyanazt a terminalt fogja hasznalni, mint a parent,
        //barmi is volt korabban CCCTERM_CONNECT-ben.
    }
}

//--------------------------------------------------------------------------
static int termio_send_without_lock(void* source, int size) //adatkuldes
{ 
    //printf("termio_send: %d\n",size);fflush(0);
    //printf(".");fflush(0);

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


//--------------------------------------------------------------------------
int termio_send(void* source, int size) //adatkuldes
{ 
    MUTEX_LOCK(mutex_send);
    int nbyte=termio_send_without_lock(source,size);
    MUTEX_UNLOCK(mutex_send);
    return nbyte;  //not used
}


//--------------------------------------------------------------------------
int termio_send2(void* source, int size, void* source2, int size2) //adatkuldes
{ 
    int nbyte=0;
    MUTEX_LOCK(mutex_send);
    nbyte+=termio_send_without_lock(source,size);
    nbyte+=termio_send_without_lock(source2,size2);
    MUTEX_UNLOCK(mutex_send);
    return nbyte;  //not used
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
int termio_socket()
{
    return termsck;
}

//----------------------------------------------------------------------------

