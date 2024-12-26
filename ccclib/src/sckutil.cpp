
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

//egyszerusitett C++ szintu socket interfesz;
//a felsobb szintek elol elfedi a UNIX/Windows kulonbseget;
//viszonylag egyszeruen hasznalhato C++-bol;

#include <sckcompat.h>
#include <sckutil.h>
#include <inttypes.h>

static int wsa_status=socket_wsastartup(); 

//----------------------------------------------------------------------------
int socket_wsastartup() 
{
    #ifdef WINDOWS //wsastartup
        static int firstrun=1;
        if( firstrun )
        {
            firstrun=0;
            WSADATA Data;
            if( WSAStartup(MAKEWORD(1,1),&Data) ) //0:success
            {
                fprintf(stderr,"WSAStartup failed (%d)\n",(int)GetLastError());
            }
        }
    #endif
    return 0;
}

//----------------------------------------------------------------------------
#ifdef WINDOWS //errno beallitas
    #define ERRNO(x)  (errno=(x)?GetLastError():0)
#else
    #define ERRNO(x)
#endif

//----------------------------------------------------------------------------
#ifndef WINDOWS  //UNIX now()
static unsigned long now(void)
{
    struct tms buf;
    return (unsigned long)times(&buf)*10;
}
#endif


//----------------------------------------------------------------------------
static void set_inetaddr(SOCKADDR_IN *addr, const char *host, int port)
{
    memset(addr,0,sizeof(SOCKADDR_IN));

    addr->sin_family       = AF_INET;
    addr->sin_addr.s_addr  = htonl(INADDR_ANY);
    addr->sin_port         = htons((unsigned short)port);

    struct hostent *he=0;
    if( host )
    {
        he=gethostbyname(host);
    }
    if( he!=0 )
    {
        memcpy((void*)&addr->sin_addr, he->h_addr_list[0], he->h_length);
    }
}

 
//----------------------------------------------------------------------------
int socket_tcp()
{
    int sck=(int)socket(AF_INET,SOCK_STREAM,0);
    if( sck>=0 )
    {    
        int nodelay=1;
        int result=setsockopt(sck,SOL_TCP,TCP_NODELAY,(char*)&nodelay,sizeof(nodelay));
        ERRNO( result<0 );
    }
    ERRNO( sck<0 );
    return sck;
} 

//----------------------------------------------------------------------------
int socket_udp()
{
    int sck=(int)socket(AF_INET,SOCK_DGRAM,0);
    if( sck>=0 )
    {    
        int nodelay=1;
        int result=setsockopt(sck,SOL_TCP,TCP_NODELAY,(char*)&nodelay,sizeof(nodelay));
        ERRNO( result<0 );
    }
    ERRNO( sck<0 );
    return sck;
} 

//----------------------------------------------------------------------------
int socket_new() 
{
    return socket_tcp(); // default: TCP
}

//---------------------------------------------------------------------------- 
int socket_bind(int socket, char *iface, int port) //compat
{
    return socket_bind(socket, (const char*) iface, port);
}

int socket_bind(int socket, const char *iface, int port)
{
    SOCKADDR_IN addr;
    set_inetaddr(&addr,iface,port);
    int result=bind(socket,(LPSOCKADDR)&addr,sizeof(addr)); 
    ERRNO(result!=0);
    return result;
} 

//----------------------------------------------------------------------------
int socket_listen(int socket, int queuelength)
{
    int result=listen(socket,queuelength);
    ERRNO(result!=0);
    return result;
}    

int socket_listen(int socket)
{
    int result=listen(socket,2);
    ERRNO(result!=0);
    return result;
}    

//---------------------------------------------------------------------------
int socket_accept(int srvsocket)
{
    SOCKADDR_IN saddr;
    SOCKLEN_T addrlen=sizeof(saddr); 
    int result=(int)accept(srvsocket,(LPSOCKADDR)&saddr,&addrlen);  
    ERRNO(result<0);
    return result;
}    

//----------------------------------------------------------------------------
int socket_connect(int socket, char *host, int port) //compat
{
    return socket_connect(socket, (const char *)host, port);
}

int socket_connect(int socket, const char *host, int port) 
{
    SOCKADDR_IN addr;
    set_inetaddr(&addr,host,port);
    int result=connect(socket,(LPSOCKADDR)&addr,sizeof(addr)); 
    ERRNO(result!=0);
    return result;
} 

//---------------------------------------------------------------------------
int socket_setoption(int s, int option, int value) 
{
    int result=0;

    if( option==SOCKOPT_NODELAY )
    {
        int nodelay=value;
        result=setsockopt(s,SOL_TCP,TCP_NODELAY,(char*)&nodelay,sizeof(nodelay));
    }

    else if( option==SOCKOPT_NONBLOCKING )
    {
        //value==1, nonblocking
        //value==0, blocking

        DWORD nonblocking=(DWORD)value;
        result=ioctlsocket(s,FIONBIO,&nonblocking);
    }

    else if( option==SOCKOPT_REUSEADDR )
    {
        BOOL reuseaddr=(BOOL)value;
        result=setsockopt(s,SOL_SOCKET,SO_REUSEADDR,(char*)&reuseaddr,sizeof(BOOL)); 
    }
    else if( option==SOCKOPT_REUSEPORT )
    {
      #ifdef SO_REUSEPORT
        BOOL reuseport=(BOOL)value;
        result=setsockopt(s,SOL_SOCKET,SO_REUSEPORT,(char*)&reuseport,sizeof(BOOL)); 
      #endif
    }
    
    return result;
}

//----------------------------------------------------------------------------
int socket_noinherit(int s) //close-on-exec
{
  #ifdef WINDOWS
    return (SetHandleInformation((HANDLE)s,HANDLE_FLAG_INHERIT,0)==0) ? -1 : s;
  #else
    return (fcntl(s,F_SETFD,FD_CLOEXEC)==-1) ? -1 : s;  
  #endif
}

//---------------------------------------------------------------------------- 
int socket_available(int sck)
{
    unsigned long readable=0;
    int ok=ioctlsocket(sck,FIONREAD,&readable);
    return (ok==0)?(int)readable:0;
}
 

//---------------------------------------------------------------------------
int socket_write(int s, void*buf, int len)
{
    // UNIX-on a send SIGPIPE-ot valthat ki, 
    // ha a masik fel megszakitja a kapcsolatot.
    // Ha az nincs kezelve, akkor a send csendben kilep. 
    // Windowson, Solarison, FreeBSD-n MSG_NOSIGNAL=0.
    
    return send(s,(char*)buf,len,MSG_NOSIGNAL);
}
 
//---------------------------------------------------------------------------
int socket_read(int s, void*dest, int dlen, int wtime)
{
    //s-bol beolvas dest-be dlen darab byteot

    //akkor ter vissza, ha 
    //  megjott a kert mennyisegu adat,
    //  lejart a varakozasi ido (wtime>=0),
    //  hiba keletkezett az olvasasban
   
    //ha wtime<0, akkor orokke var
 
    //visszateres
    //  recvlen>=0 eseten: beolvasott byteok szama
    //  recvlen<0  eseten: hiba

    //olvasasi hiba eseten, 
    //  ha van beolvasott adat, ezek hosszat adja,
    //  ha nincs beolvasott adat, negativot ad


    char *buf=(char*)dest;                //ide olvasunk
    int recvlen=0;                        //beolvasott adatok hossza
    int result=0;                         //utolso olvasas eredmenye
    int firstread=1;                      //egyszer mindenkeppen olvasunk
    int wtimerest=wtime<0?1000000:wtime;  //maradek ido
    unsigned long time0=now();            //olvasas kezdetenek ideje (ms)
 

    while( firstread || ((recvlen<dlen) && (wtimerest>0)) )
    {
        fd_set fd_read;
        FD_ZERO(&fd_read);
        FD_SET(s,&fd_read);

        fd_set fd_err;
        FD_ZERO(&fd_err);
        FD_SET(s,&fd_err);
 
        struct timeval tv;
        tv.tv_sec=wtimerest/1000;          //sec
        tv.tv_usec=(wtimerest%1000)*1000;  //mikrosec 

        if( select(s+1,&fd_read,NULL,&fd_err,&tv) )
        {
            //ide akkor jon, ha 
            //1) van olvasnivalo,
            //2) a csatorna lezarodott,
            //3) a select hibakoddal tert vissza
            
            //a hibat recv eredmenyebol detektaljuk
            //CSAK a result>0 eset szamit sikeresnek
            //Linuxon recv nemletezo vonal eseten 0-at ad
            //NT-n recv nemletezo vonal eseten -1-et ad

            if( FD_ISSET(s,&fd_err) )
            {
                break;
            }

            result=recv(s,buf+recvlen,dlen-recvlen,0);
            
            if( result>0 )
            {
                recvlen+=result;
            }
            else
            {
                result=-1;
                break;
            }
        }
        
        firstread=0;
        if( wtime>=0 )
        {
            wtimerest=wtime-(now()-time0);
        }
    }

    if( recvlen>0 )
    {
        return recvlen;
    }
    else if( result<0 )
    {
        return -1;
    }
    else
    {
        return 0;
    }
}
 
//---------------------------------------------------------------------------- 
int socket_close(int sck)
{
    return closesocket(sck);
}
 
//---------------------------------------------------------------------------- 
int socket_error()
{
    return errno;

    //return GetLastError();  //UNIX-on errno
    //Az eredeti koncepcio az volt, 
    //hogy ez Windowson a GetLastError()-t adja,
    //azonban a CCC stack kezeles torli a kodot,
    //ezert inkabb megorizzuk a kodot errno-ban.
}
 
//----------------------------------------------------------------------------
//osszetett funkciok
//----------------------------------------------------------------------------
int client_socket_new(const char *ipaddr, int port)
{
    SOCKET sck=socket_new();
    if( 0>socket_connect(sck,ipaddr,port) )
    {
        closesocket(sck); 
        return -1;
    }
    return (int)sck;
}

//----------------------------------------------------------------------------
int server_socket_new(const char *ipaddr, int port)
{
    SOCKET sck=socket_new();
    if( (0!=socket_bind(sck,ipaddr,port)) || (0!=socket_listen(sck)) )
    {
        closesocket(sck); 
        return -1;
    }
    return (int)sck;
}

//----------------------------------------------------------------------------
int server_socket_new(const char *ipaddr, int port, int qlen)
{
    SOCKET sck=socket_new();
    if( (0!=socket_bind(sck,ipaddr,port)) || (0!=socket_listen(sck,qlen)) )
    {
        closesocket(sck); 
        return -1;
    }
    return (int)sck;
}

//----------------------------------------------------------------------------
int client_socket(char *ipaddr, int port){return client_socket_new((const char*)ipaddr,port);} //compat
int client_socket(const char *ipaddr, int port){return client_socket_new(ipaddr,port);}
int server_socket(const char *ipaddr, int port){return server_socket_new(ipaddr,port);}
int server_socket(const char *ipaddr, int port, int qlen){return server_socket_new(ipaddr,port,qlen);}
 
//----------------------------------------------------------------------------
int server_socket_accept(int srvsck)
{
    return socket_accept(srvsck); //hiba eseten -1
}
 
//---------------------------------------------------------------------------- 
