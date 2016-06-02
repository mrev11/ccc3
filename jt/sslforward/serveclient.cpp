
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


#ifdef UNIX
//#include <unistd.h>
#else
#include <process.h>
#endif
 
#include <openssl/err.h>
#include <openssl/ssl.h>
 
#include <sckcompat.h>
#include <sckutil.h>
 
extern SSL_CTX *ssl_server_context();
extern SSL_CTX *ssl_client_context();
extern void socketpair(int*,int*);
extern void forward(SSL *ssl, int trmsck, int appsck);
extern void start_srvapp(int clnsck);
extern void start_child(char* argv[]);

static void serve_client(int trmsck, int srvflg);
static int  noinherit(int);


//----------------------------------------------------------------------------
void serve_client_accept(int trmsck)
{
    serve_client(trmsck,1);
}

//----------------------------------------------------------------------------
void serve_client_connect(int trmsck)
{
    serve_client(trmsck,0);
}

//----------------------------------------------------------------------------
static void serve_client(int trmsck, int srvflg)
{
    int appsck,clnsck;
    socketpair(&appsck,&clnsck); //kilep, ha sikertelen
#ifdef WINDOWS
    appsck=noinherit(appsck);
    trmsck=noinherit(trmsck);
#endif

    SSL_CTX*ctx=srvflg ? ssl_server_context():ssl_client_context();
    SSL *ssl=SSL_new(ctx);
    SSL_set_fd(ssl,trmsck);
    
    if(srvflg)
    {
        if( !SSL_accept(ssl) )
        {
            fprintf(stderr,"\nSSL_accept failed");
            exit(1);
        }
    }
    else
    {
        if( !SSL_connect(ssl) )
        {
            fprintf(stderr,"\nSSL_connect failed");
            exit(1);
        }
    }

#ifdef WINDOWS
    start_srvapp(clnsck); 
    socket_close(clnsck);
    forward(ssl,trmsck,appsck);
#else //UNIX
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
#endif
}


//----------------------------------------------------------------------------
void start_child( char* argv[])
{

#ifdef WINDOWS
    int result=spawnvp(P_NOWAIT,argv[0],argv);
    //azonnal visszajön
    if(result==-1)
    {
        fprintf(stderr,"\nspawnvp failed: %s ", argv[0]);
    }
#else //UNIX
    execvp(argv[0],argv);
    //csak hiba esetén jön vissza
    fprintf(stderr,"\nexecvp failed: %s ", argv[0]);
#endif


}


//----------------------------------------------------------------------------
#ifdef WINDOWS

static int noinherit(int socket)
{
    int sckdup;
    HANDLE procid=GetCurrentProcess();

    BOOL ok=DuplicateHandle( procid, 
                             (HANDLE)socket, 
                             procid, 
                             (HANDLE*)&sckdup,
                             DUPLICATE_SAME_ACCESS, 
                             (BOOL)0, //no inherir
                             0 );

    socket_close(socket);
    return ok ? sckdup : -1;
}

#endif
//----------------------------------------------------------------------------


