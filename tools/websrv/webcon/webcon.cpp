
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
 
#ifdef EMLEKEZTETO
    SSL előtétprogram webszerverekhez.

    Példa:
        webcon.exe -l 443 -p 8080 -k server.pem

    A 443 porton figyel a webcon, erre a portra SSL protokollal
    kell konnektálni a böngészővel, pl. https://host:443/...

    A 8080 portra konnektál a webcon, itt figyel a titkosítás 
    nélkül működő webszerver.

    Az SSL-hez szükség van egy kulcsfájlra,
    amiben egy CERTIFICATE és egy PRIVATE KEY szekciónak kell lennie.
    A webcon minden forgalmat továbbít a böngésző és a webszerver 
    között: a böngésző oldalán kódolva, a webszerver oldalán dekódolva.
    
    Összes opció:

    -l  <[if:]port> itt figyel a webcon
                    default: 80 vagy 443 
                    (attól függően, be van-e kapcsolva az SSL)

    -p  <[if:]port> ide konnektál a webcon
                    default: 8080 vagy 4433
                    (attól függően, be van-e kapcsolva az SSL)
    
    -k  <pem>       kulcsfilé, amiben egy CERTIFICATE és 
                    egy PRIVATE KEY szekciónak kell lennie
                    ez kapcsolja be az SSL fordítást
                    default: nincs

    -cf <file>      CA certifiacte file
                    bekapcsolja a kliens hitelesítést
                    default: nincs
    
    -cp <path>      CA certificate path
                    bekapcsolja a kliens hitelesítést
                    default: nincs

    -vd <depth>     max ilyen mély certificate chain-t 
                    fogad el kliens certificate ellenőrzésekor
                    default: 1

    -dump           listázza az üzeneteket stderr-re
                    csak ssl nélkül használható
#endif 


#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
//#include <errno.h>
#include <time.h>
 
#include <openssl/err.h>
#include <openssl/ssl.h>
 
#include <sckcompat.h>
#include <sckutil.h>
 
static int parse_ifport(char *arg, char **iface);
static SSL *ssl_context(void);
static void forward(SSL *ssl, int termsck, int appsck);
static void forward1(SSL *ssl, int sck);
static void forward2(int sck, SSL *ssl);
static void forward3(int s1, int s2);
static void zombi();
static void error();
static void sleep(int millis);
static void printlog(char *buffer,int len);
 
#define MAX(a,b)  (((a)>(b))?(a):(b))
#define MIN(a,b)  (((a)<(b))?(a):(b))

static SSL *ssl=0;
static char *KEYFILE=0;         //bekapcsolja az SSL-t
static char *CAfile=0;          //bekapcsolja a kliens hitelesítést
static char *CApath=0;          //bekapcsolja a kliens hitelesítést
static int verify_depth=1;
static int dumpflag=0;
static int sck_last_accepted=0;

//----------------------------------------------------------------------------
int main(int argc, char* argv[] )
{
    char *if_secure=0; //all interfaces
    char *if_plain="127.0.0.1"; //localhost

    int port_secure=0; //-l port
    int port_plain=0; //-p port
 
    for( int i=1; i<argc; i++ )
    {
        if( 0==strcmp("-l",argv[i]) )
        {
            port_secure=parse_ifport(argv[++i],&if_secure);
        }
        else if( 0==strcmp("-p",argv[i]) )
        {
            port_plain=parse_ifport(argv[++i],&if_plain);
        }
        else if( 0==strcmp("-k",argv[i]) )
        {
            KEYFILE=argv[++i];
        }
        else if( 0==strcmp("-cf",argv[i]) )
        {
            CAfile=argv[++i];
        }
        else if( 0==strcmp("-cp",argv[i]) )
        {
            CApath=argv[++i];
        }
        else if( 0==strcmp("-vd",argv[i]) )
        {
            verify_depth=atoi(argv[++i]);
        }
        else if( 0==strcmp("-dump",argv[i]) )
        {
            dumpflag=1;
        }
        else
        {
            fprintf(stderr,"Invalid option (%s), exit.\n",argv[i]);
            exit(1);
        }
    }
    
    if( port_secure==0 ) port_secure=KEYFILE?443:80;
    if( port_plain==0 ) port_plain=KEYFILE?4433:8080;

    printf("\n");
    printf("listen  < %s:%d\n", if_secure?if_secure:"all",port_secure);
    printf("connect > %s:%d\n", if_plain, port_plain);
    printf("keyfile : %s\n",KEYFILE?KEYFILE:"");
    printf("CApath  : %s\n",CApath?CApath:"");
    printf("CAfile  : %s\n",CAfile?CAfile:"");

    if( KEYFILE )
    {
        if( fopen(KEYFILE,"r")==0 )
        {
            fprintf(stderr,"Keyfile (%s) not found, exit.\n",KEYFILE);
            exit(1);
        }
        ssl=ssl_context();    
        printf("Keyfile (%s) loaded.\n",KEYFILE);
    }

    int sl=server_socket(if_secure,port_secure);
    if( sl<0 )
    {
        fprintf(stderr,"server_socket failed (%d), exit.\n",socket_error());
        exit(1);
    }
    fflush(0); //tiszta lap a forkolás előtt

    while(1)
    {
        int ss=server_socket_accept(sl);
        sck_last_accepted=ss; //log bekapcs
        
        if( fork() ) //parent
        {
            close(ss); //ssl socket
            zombi();
        }
        else //child
        {
            close(sl); //listen socket

            int sp=client_socket(if_plain,port_plain);
            if( sp<0 )
            {
                fprintf(stderr,"client_socket failed (%d), exit.\n",socket_error());
                exit(1);
            }
            if( KEYFILE )
            {
                SSL_set_fd(ssl,ss);
                if( !SSL_accept(ssl) )
                {
                    fprintf(stderr,"SSL_accept failed, exit.\n");
                    exit(1);
                }
            }
            forward(ssl,ss,sp);
        }
    }
    return 0;
}

//----------------------------------------------------------------------------
static int parse_ifport(char *arg, char **iface)
{
    int port=0;
    char *p=strdup(arg);
    char *q=strchr(p,':');

    if( q )
    {
         *q=0;
         *iface=p;
         port=atoi(q+1);
    }
    else
    {
         port=atoi(p);
    }
    
    return port;
}

//----------------------------------------------------------------------------
static int cb_verify(int preverify_ok, X509_STORE_CTX *ctx)
{
    if( preverify_ok )
    {
        char buf[512]; buf[0]=0;
        SSL *ssl=(SSL*)X509_STORE_CTX_get_ex_data(ctx,SSL_get_ex_data_X509_STORE_CTX_idx());
        X509 *cert=X509_STORE_CTX_get_current_cert(ctx);
        X509_NAME_oneline(X509_get_subject_name(cert),buf,256);
        printf("accept: %s\n",buf);
    }
    return preverify_ok;
}

//----------------------------------------------------------------------------
static SSL *ssl_context()
{
    SSL_load_error_strings();  //printf("SSL_load_error_strings\n");fflush(0); 
    SSL_library_init();  //printf("SSL_library_init\n");fflush(0);  
    SSL_CTX *ctx=SSL_CTX_new( SSLv23_server_method() );  //printf("SSL_CTX_new\n");fflush(0);  
    if( !SSL_CTX_use_certificate_file(ctx, KEYFILE, SSL_FILETYPE_PEM) ) error(); //printf("SSL_CTX_use_certificate_file(ctx,%s,%d)\n",KEYFILE,SSL_FILETYPE_PEM);fflush(0);  
    if( !SSL_CTX_use_PrivateKey_file(ctx, KEYFILE, SSL_FILETYPE_PEM) ) error(); //printf("SSL_CTX_use_PrivateKey_file(ctx,%s,%d)\n",KEYFILE,SSL_FILETYPE_PEM);fflush(0);  
    if( !SSL_CTX_check_private_key(ctx) ) error(); //printf("SSL_CTX_check_private_key(ctx)\n");fflush(0);  
    
    if( CAfile || CApath )
    {
        //client authentication

        int mode =  SSL_VERIFY_PEER |
                    SSL_VERIFY_FAIL_IF_NO_PEER_CERT |
                    SSL_VERIFY_CLIENT_ONCE;
    
        SSL_CTX_set_verify(ctx,mode,cb_verify); //printf("SSL_CTX_set_verify(ctx,%d,cb_verify)\n",mode);fflush(0);  
        SSL_CTX_set_verify_depth(ctx,verify_depth); //printf("SSL_CTX_set_verify_depth(ctx,%d)\n",verify_depth);fflush(0);  

        if( !SSL_CTX_load_verify_locations(ctx,CAfile,CApath) ) error(); //printf("SSL_CTX_load_verify_locations(ctx,%s,%s)\n",CAfile,CApath);fflush(0);  
    }

    SSL *ssl=SSL_new(ctx); if(!ssl) error(); //printf("SSL_new(ctx)\n");fflush(0);  
    return ssl;
}

//----------------------------------------------------------------------------
static void forward(SSL *ssl, int ts, int as)
{
    while(1)
    {
        #ifdef NOT_DEFINED
          Van olyan eset, amikor az SSL alatt levő fd-t a select 
          nem olvashatónak mutatja, de maga az SSL mégis olvasható. 
          Ez akkor fordul elő, ha az ssl az fd-ből előreolvasott, 
          és vannak "pending" byteok.
        #endif

        while( ssl && (SSL_pending(ssl)>0) )
        {
            //printf("SSL_pending %d\n",SSL_pending(ssl));fflush(0);
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
            zombi();
            continue;
        }
    
        if( FD_ISSET(ts,&fdread)  )
        {
            if( ssl )
            {
                forward1(ssl,as);
            }
            else
            {
                forward3(ts,as);
            }
        }

        if( FD_ISSET(as,&fdread)  )
        {
            if( ssl )
            {
                forward2(as,ssl);
            }
            else
            {
                forward3(as,ts);
            }
        }
    }
}

//----------------------------------------------------------------------------
static void forward1(SSL *ssl, int sck)
{
    int bs=16*1024;
    char buffer[bs];
    int nbyte=SSL_read(ssl,buffer,bs);
    printlog(buffer,nbyte);

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
        //printf("forward1 connection closed %d\n",sslerr);
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
    int bs=4*1024;
    char buffer[bs];
    int nbyte=recv(sck,buffer,bs,0);

    if( nbyte<=0 )
    {
        //printf("forward2 connection closed\n");
        exit(0);
    }
    else 
    {
        SSL_write(ssl,buffer,nbyte);
    }
}

//----------------------------------------------------------------------------
static void forward3(int s1, int s2)
{
    int bs=4*1024;
    char buffer[bs];
    int nbyte=recv(s1,buffer,bs,0);
    printlog(buffer,nbyte);

    if( nbyte<=0 )
    {
        //printf("forward3 connection closed\n");
        exit(0);
    }
    else 
    {
        send(s2,buffer,nbyte,0);
        if( KEYFILE==0 && dumpflag==1 )
        {
            write(2,buffer,nbyte);
        }
    }
}

//----------------------------------------------------------------------------
static void zombi()
{
    int pid, wstat; 
    while( 0<(pid=waitpid(0,&wstat,WNOHANG)) )
    {
        //printf("waitpid %d %d\n",pid,wstat);
    }
}

//----------------------------------------------------------------------------
static void error()
{
    ERR_print_errors_fp(stderr);
    exit(1);
}
 
//----------------------------------------------------------------------------
static void sleep(int millis)
{
    struct timeval t;
    t.tv_sec=millis/1000;
    t.tv_usec=(millis%1000)*1000;
    select(0,0,0,0,&t);
}

//----------------------------------------------------------------------------
static void datetime()
{
    time_t t;
    time(&t);
    struct tm *p=localtime(&t);
    if( p )
    {
        printf("%04d.%02d.%02d ",p->tm_year+1900,p->tm_mon+1,p->tm_mday); 
        printf("%02d:%02d:%02d ",p->tm_hour,p->tm_min,p->tm_sec); 
    }
}

//----------------------------------------------------------------------------
static void peername(int s)
{
    char sa[32];
    SOCKLEN_T namelen=sizeof(sa);
    char *addr=0;

    if( 0!=getpeername(s,(SOCKADDR*)sa,&namelen) )
    {
        printf("getpeername error:%d", socket_error());
    }
    else if( 0==(addr=inet_ntoa(((IN_ADDR*)sa)[1])) )
    {
        printf("inet_ntoa error:%d", socket_error());
    }
    else
    {
        printf("%s ",addr);
    }
}

//----------------------------------------------------------------------------
static void printlog(char *buffer,int nbyte)
{
    if( sck_last_accepted )
    {
        datetime();
        peername(sck_last_accepted);

        int len=MIN(256,nbyte);
        char buf[len+1];
        memcpy(buf,buffer,len);
        buf[len]=0;
        char *p;
        p=strchr(buf,'\n');if(p)*p=0;
        p=strchr(buf,'\r');if(p)*p=0;
        printf("%s\n",buf);
        fflush(0);

        sck_last_accepted=0;
    }
}

//----------------------------------------------------------------------------
