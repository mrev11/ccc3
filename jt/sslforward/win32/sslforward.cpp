
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

#ifdef HASZNALAT

    Legyen 

        <command> -jtsocket <sck> 

    egy olyan programindító parancs, ami a listenertől örökölt <sck> 
    sockettel elindít egy J-terminál alkalmazást SSL nélkül. Ekkor a 

        sslforward.exe <command> -jtsocket <sck> 

    parancs elindítja ugyanazt az alkalmazást SSL fordító közbeiktatásával.

    Megjegyzés-1:

        A <command>-nak spawnvp-vel (vagy execvp-vel) indítható,
        filéspecifikációval kell kezdődnie (a PATH-ból is elindul).
 
    Megjegyzés-2:

        A -jtsocket <sck> opció nem csak a parancs végén lehet.

#endif

#include <process.h>
 
#include <sckcompat.h>
#include <sckutil.h>
 
#include <openssl/err.h>
#include <openssl/ssl.h>

#define CERT_FILE  "server.pem"

#define MAX(a,b)  (((a)>(b))?(a):(b))
#define MIN(a,b)  (((a)<(b))?(a):(b))

#define BUFSIZ1   16*1024
#define BUFSIZ2    4*1024

 
static void serve_client(int termsck);
static void start_srvapp( int sck );
static void forward(SSL *ssl, int termsck, int appsck);
static void forward1(SSL *ssl, int sck);
static void forward2(int sck, SSL *ssl);
static void error();

extern int socket_pair( int sp[2] );
extern int socket_dupinherit(int socket, int inherit);
 
static int  ARGC;
static char **ARGV;


//----------------------------------------------------------------------------
int main(int argc, char* argv[] )
{
    ARGC=argc;
    ARGV=argv;
 
    int i,jtsocket=0;
    for( i=1; i<argc-1; i++ )
    {
        if( 0==strcmp("-jtsocket",argv[i]) )
        {
            jtsocket=atoi(argv[i+1]);
        }
    }

    if( jtsocket==0 )
    {
        fprintf(stderr, "Usage: sslforward.exe <command> -jtsocket <sck>\n");
        exit(1);
    }

    serve_client( jtsocket );
    return 0;
}
 
//----------------------------------------------------------------------------
static void serve_client(int jtsocket)
{
    int scktrm=socket_dupinherit(jtsocket,0); //nem öröklődik
    socket_close(jtsocket);

    SSL_load_error_strings();  //printf("SSL_load_error_strings\n");fflush(0); 
    OpenSSL_add_ssl_algorithms();  //printf("OpenSSL_add_ssl_algorithms\n");fflush(0);  
    SSL_CTX *ctx=SSL_CTX_new( SSLv23_server_method() );  //printf("SSL_CTX_new\n");fflush(0);  
    if( !SSL_CTX_use_certificate_file(ctx, CERT_FILE, SSL_FILETYPE_PEM) ) error(); //printf("SSL_CTX_use_certificate_file\n");fflush(0);  
    if( !SSL_CTX_use_PrivateKey_file(ctx, CERT_FILE, SSL_FILETYPE_PEM) ) error(); //printf("SSL_CTX_use_PrivateKey_file\n");fflush(0);  
    if( !SSL_CTX_check_private_key(ctx) ) error(); //printf("SSL_CTX_check_private_key\n");fflush(0);  
 
    SSL *ssl=SSL_new(ctx);
    SSL_set_fd(ssl,scktrm);

    int result;
    if( 0>(result=SSL_accept(ssl)) )
    {
        int status=SSL_get_error(ssl,result);
        printf("SSL_accept failed %d\n",status);
        exit(1);
    }

    int sp[2]={0,0};
    socket_pair(sp);
    int sckapp=socket_dupinherit(sp[0],0); //nem öröklődik 
    socket_close(sp[0]);
    start_srvapp(sp[1]); 
    socket_close(sp[1]);

    //megmaradt socketek:
    //scktrm kapcsolat a terminállal
    //sckapp kapcsolat az alkalmazással
 
    forward(ssl,scktrm,sckapp);
}


//----------------------------------------------------------------------------
static void start_srvapp( int sck )
{
    char buf[32];
    char *argv[1024];
    for( int i=1; i<ARGC; i++ )
    {
        argv[i]=0;
        argv[i-1]=ARGV[i];
        if( 0==strcmp("-jtsocket",ARGV[i-1])  )
        {
            sprintf(buf,"%d",sck);
            argv[i-1]=buf;
        }
    }
    spawnvp(P_NOWAIT,argv[0],argv);
}

//----------------------------------------------------------------------------
static void forward(SSL *ssl, int ts, int as)
{
    while(1)
    {
        #ifdef NOT_DEFINED //ellenőrizni Windowson!
          Van olyan eset, amikor az SSL alatt levő fd-t a select 
          nem olvashatónak mutatja, de maga az SSL mégis olvasható. 
          Ez akkor fordul elő, ha az ssl az fd-ből előreolvasott, 
          és vannak "pending" byteok.
        #endif

        while( SSL_pending(ssl)>0 )
        {
            forward1(ssl,as);
        }

        fd_set fdread;
        FD_ZERO( &fdread ); 
        FD_SET(ts, &fdread ); 
        FD_SET(as, &fdread );  

        struct timeval tv;
        tv.tv_sec=1;
        tv.tv_usec=0;   
    
        if( 0==select(1+MAX(ts,as), &fdread, 0, 0, &tv) )
        {
            continue;
        }
    
        if( FD_ISSET(ts,&fdread)  )
        {
            forward1(ssl,as);
        }

        if( FD_ISSET(as,&fdread)  )
        {
            forward2(as,ssl);
        }
    }
}

//----------------------------------------------------------------------------
static void forward1(SSL *ssl, int sck)
{
    char buffer[BUFSIZ1];
    int nbyte=SSL_read(ssl,buffer,BUFSIZ1);

    if( nbyte<=0 )
    {
        int sslerr=SSL_get_error(ssl,nbyte);
        
        switch( sslerr  )
        {
            case SSL_ERROR_NONE:              return;   //0
            case SSL_ERROR_SSL:               break;    //1
            case SSL_ERROR_WANT_READ:         return;   //2
            case SSL_ERROR_WANT_WRITE:        return;   //3
            case SSL_ERROR_WANT_X509_LOOKUP:  break;    //4
            case SSL_ERROR_SYSCALL:           break;    //5
            case SSL_ERROR_ZERO_RETURN:       break;    //6
            case SSL_ERROR_WANT_CONNECT:      break;    //7
        }

        socket_close(sck);
        printf("forward1 connection closed %d\n",sslerr);
        exit(0);
    }
    else if( nbyte>0 )
    {
        send(sck,buffer,nbyte,0);
    }
}


//----------------------------------------------------------------------------
static void forward2(int sck, SSL *ssl)
{
    char buffer[BUFSIZ2];
    int av=socket_available(sck);
    int nbyte=recv(sck,buffer,MIN(BUFSIZ2,av),0);
    
    if( nbyte<=0 )
    {
        socket_close(sck);
        printf("forward2 connection closed\n");
        exit(0);
    }
    else 
    {
        SSL_write(ssl,buffer,nbyte);
    }
}
 
//----------------------------------------------------------------------------
static void error()
{
    ERR_print_errors_fp(stderr);
    exit(1);
}
 
//----------------------------------------------------------------------------

 