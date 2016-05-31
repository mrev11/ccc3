
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


//#include <sys/wait.h>
 
#include <openssl/err.h>
#include <openssl/ssl.h>
 
#include <sckcompat.h>
#include <sckutil.h>

extern void forward(SSL *ssl, int termsck, int appsck);
static void forward1(SSL *ssl, int sck);
static void forward2(int sck, SSL *ssl);
//static void zombi();
static void error();
//static void sleep(int millis);
 
#define MAX(a,b)  (((a)>(b))?(a):(b))
#define MIN(a,b)  (((a)<(b))?(a):(b))

 
//----------------------------------------------------------------------------
void forward(SSL *ssl, int ts, int as)
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
            //zombi();
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
    //printf("forw-1\n");

    int bs=16*1024;
    char buffer[bs];
    int nbyte=SSL_read(ssl,buffer,bs);

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
    //printf("forw-2\n");

    int bs=4*1024;
    char buffer[bs];
    int av=socket_available(sck);
    int nbyte=recv(sck,buffer,MIN(bs,av),0);
    
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
