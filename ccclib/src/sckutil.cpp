
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

//egyszerűsített C++ szintű socket interfész;
//a felsőbb szintek elől elfedi a UNIX/Windows különbséget;
//viszonylag egyszerűen használható C++-ból;

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
                fprintf(stderr,"WSAStartup failed (%d)\n",GetLastError());
            }
        }
    #endif
    return 0;
}

//----------------------------------------------------------------------------
#ifdef WINDOWS //errno beállítás
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
static int resolv(const char *addr, char *buf) // "hostname" -> "111.222.333.444"
{
    struct hostent *he;
    he=gethostbyname(addr);
    if( he==NULL )
    {
        //printf("unknown host: %s\n",addr);
        sprintf(buf,"%d.%d.%d.%d",0,0,0,0);
        return(0);
    }
    c_uint32_t ip=ntohl(*((c_uint32_t*)he->h_addr_list[0]));

    //printf("host: %s --> %x --> ",addr,(unsigned)ip);
    //printf("%d.%d.%d.%d\n", 0xff&(ip>>24), 0xff&(ip>>16), 0xff&(ip>>8), 0xff&(ip>>0));
    //fflush(0);

    sprintf(buf,"%d.%d.%d.%d", 0xff&(ip>>24), 0xff&(ip>>16), 0xff&(ip>>8), 0xff&(ip>>0) );
    return 0;
}
 
//----------------------------------------------------------------------------
int socket_new()
{
    int result=(int)socket(AF_INET,SOCK_STREAM,0);
    ERRNO(result<0);
    return result;
} 

//----------------------------------------------------------------------------
static void socket_addr_in(SOCKADDR_IN *saddr, char *ipaddr, int port)
{
    memset(saddr,0,sizeof(saddr));
    saddr->sin_addr.s_addr=ipaddr?inet_addr(ipaddr):htonl(INADDR_ANY);
    saddr->sin_port=htons((unsigned short)port);
    saddr->sin_family=AF_INET;
}

//----------------------------------------------------------------------------
int socket_bind(int socket, char *ipaddr, int port) //compat
{
    return socket_bind(socket, (const char*) ipaddr, port);
}

int socket_bind(int socket, const char *ipaddr, int port)
{
    //Jó-e a default REUSEADDR opció?
    //
    //1. Linuxon nem látszik a hatása. Más processz által fogvatartott
    //   portra semmiképp sem lehet bindelni. A saját processz által
    //   korábban bindelt portot korlátozás nélkül újra lehet használni.
    //
    //2. Windowson REUSEADDR=1 esetén más processz által fogott portot
    //   is lehet bindelni, ami ronda hiba. REUSEADDR=0 esetén viszont egy
    //   processz nem tudja többször bindelni ugyanazt a portot. Például
    //   nem lehet ilyen ciklust használni: socket,bind,listen,accept,close.

    char *host=0;
    char buf[32];
    if( ipaddr )
    {
        resolv(ipaddr,buf);
        host=buf;
    }
    
    SOCKADDR_IN saddr;
    socket_addr_in(&saddr,host,port);
    //BOOL reuseaddr=1;
    //setsockopt(socket,SOL_SOCKET,SO_REUSEADDR,(char*)&reuseaddr,sizeof(BOOL)); 
    int result=bind(socket,(LPSOCKADDR)&saddr,sizeof(saddr)); 
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
int socket_connect(int socket, char *ipaddr, int port) //compat
{
    return socket_connect(socket, (const char *)ipaddr, port);
}

int socket_connect(int socket, const char *ipaddr, int port) 
{
    char *host=0;
    char buf[32];
    if( ipaddr )
    {
        resolv(ipaddr,buf);
        host=buf;
    }
    SOCKADDR_IN saddr;
    socket_addr_in(&saddr,host,port);
    int result=connect(socket,(LPSOCKADDR)&saddr,sizeof(saddr)); 
    ERRNO(result!=0);
    return result;
} 

//---------------------------------------------------------------------------
int socket_setoption(int s, int option, int value) 
{
    int result=0;

    if( option==SOCKOPT_NODELAY )
    {
        #ifdef _LINUX_    
        BOOL nodelay=(BOOL)value;
        result=setsockopt(s,SOL_TCP,TCP_NODELAY,(char*)&nodelay,sizeof(BOOL));
        #endif    
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
    
    return result;
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
    // UNIX-on a send SIGPIPE-ot válthat ki, 
    // ha a másik fél megszakítja a kapcsolatot.
    // Ha az nincs kezelve, akkor a send csendben kilép. 
    // Windowson, Solarison, FreeBSD-n MSG_NOSIGNAL=0.
    
    return send(s,(char*)buf,len,MSG_NOSIGNAL);
}
 
//---------------------------------------------------------------------------
int socket_read(int s, void*dest, int dlen, int wtime)
{
    //s-ből beolvas dest-be dlen darab byteot

    //akkor tér vissza, ha 
    //  megjött a kért mennyiségű adat,
    //  lejárt a várakozási idő (wtime>=0),
    //  hiba keletkezett az olvasásban
   
    //ha wtime<0, akkor örökké vár
 
    //visszatérés
    //  recvlen>=0 esetén: beolvasott byteok száma
    //  recvlen<0  esetén: hiba

    //olvasási hiba esetén, 
    //  ha van beolvasott adat, ezek hosszát adja,
    //  ha nincs beolvasott adat, negatívot ad


    char *buf=(char*)dest;                //ide olvasunk
    int recvlen=0;                        //beolvasott adatok hossza
    int result=0;                         //utolsó olvasás eredménye
    int firstread=1;                      //egyszer mindenképpen olvasunk
    int wtimerest=wtime<0?1000000:wtime;  //maradék idő
    unsigned long time0=now();            //olvasás kezdetének ideje (ms)
 

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
            //ide akkor jön, ha 
            //1) van olvasnivaló,
            //2) a csatorna lezáródott,
            //3) a select hibakóddal tért vissza
            
            //a hibát recv eredményéből detektáljuk
            //CSAK a result>0 eset számít sikeresnek
            //Linuxon recv nemlétező vonal esetén 0-át ad
            //NT-n recv nemlétező vonal esetén -1-et ad

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
    //Az eredeti koncepció az volt, 
    //hogy ez Windowson a GetLastError()-t adja,
    //azonban a CCC stack kezelés törli a kódot,
    //ezért inkább megőrizzük a kódot errno-ban.
}
 
//----------------------------------------------------------------------------
//összetett funkciók
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
    return socket_accept(srvsck); //hiba esetén -1
}
 
//---------------------------------------------------------------------------- 

