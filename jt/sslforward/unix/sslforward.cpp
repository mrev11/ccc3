
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
 

#include <unistd.h>
#include <sys/wait.h>
 
#include <openssl/err.h>
#include <openssl/ssl.h>
 
#include <sckcompat.h>
#include <sckutil.h>
 
extern SSL_CTX *ssl_server_context();
extern void socketpair(int*,int*);
extern void forward(SSL *ssl, int trmsck, int appsck);

static void serve_client(int termsck);
static void start_srvapp(int sck);
 
static int ARGC;
static char **ARGV;
 
//----------------------------------------------------------------------------
int main(int argc, char* argv[] )
{
    ARGC=argc;
    ARGV=argv;
 
    int i,jtsocket=0;
    for( i=0; i<argc; i++ )
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
static void serve_client(int trmsck)
{
    SSL_CTX *ctx=ssl_server_context();

    SSL *ssl=SSL_new(ctx);
    SSL_set_fd(ssl,trmsck);
    if( !SSL_accept(ssl) )
    {
        printf("SSL_accept failed\n");
        exit(1);
    }

    int appsck,clnsck;
    socketpair(&appsck,&clnsck); //kilep, ha sikertelen
 
    if( fork() )  
    {
        socket_close(clnsck);
        forward(ssl,trmsck,appsck);
    }
    else
    {
        socket_close(trmsck);
        socket_close(appsck);
        start_srvapp(clnsck);
    }

}

//----------------------------------------------------------------------------
void start_srvapp(int sck)
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

    execvp(argv[0],argv);

    //csak hiba esetén jön vissza
    fprintf(stderr,"\nexecvp failed: %s ", argv[0]);
}

//----------------------------------------------------------------------------
