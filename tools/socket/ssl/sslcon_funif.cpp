
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

//SSL connection function interface

#include <sckcompat.h>
 
#include <openssl/err.h>
#include <openssl/ssl.h>

#include <cccapi.h>
#include <sckcompat.h>
#include <sckutil.h>

//---------------------------------------------------------------------------
static unsigned long milliseconds(void)
{
  #ifdef _UNIX_
    struct tms buf;
    return (unsigned long)times(&buf)*10;
  #else
    return GetTickCount();
  #endif
}

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

//--------------------------------------------------------------------------
void _clp_sslcon_new(int argno)
{
    CCC_PROLOG("sslcon_new",1);
    SSL_CTX *ctx=(SSL_CTX *)_parp(1);
    SSL *ssl=SSL_new(ctx);  //printf("SSL_new(ctx)\n");fflush(0);  
    
    if( ssl )
    {
        _retp(ssl);    
    }
    else
    {
        _ret();
    }
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_sslcon_free(int argno)
{
    CCC_PROLOG("sslcon_free",1);
    SSL *ssl=(SSL*)_parp(1);
    SSL_free(ssl);
    _ret();    
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_sslcon_set_fd(int argno)
{
    CCC_PROLOG("sslcon_set_fd",2);
    SSL *ssl=(SSL*)_parp(1);
    int fd=_parni(2);
    _retni(SSL_set_fd(ssl,fd)); //0 failed, 1 succeded
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_sslcon_get_fd(int argno)
{
    CCC_PROLOG("sslcon_get_fd",1);
    SSL *ssl=(SSL*)_parp(1);
    int fd=SSL_get_fd(ssl); //-1 failed, 0<= succeded
    _retni(fd);
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_sslcon_set_tlsext_host_name(int argno)
{
    CCC_PROLOG("sslcon_set_tlsext_host_name",2);
    str2bin(base+1);
    SSL  *ssl  = (SSL*)_parp(1);    //SSL struct
    char *name = _parb(2);          //host name
    _retni( SSL_set_tlsext_host_name(ssl,name)); //1 success, 0 error
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_sslcon_accept(int argno)
{
    CCC_PROLOG("sslcon_accept",2);

    SSL *ssl=(SSL*)_parp(1);
    int timeout=ISNIL(2)?1000000:_parni(2); //msec
    
    //A timeout a handshake-re vonatkozik,
    //azaz a connect utan ennyi ido van az SSL kapcsolat felepitesere.
    //Ha az SSL_accept-et blokkolo socketre hivjuk meg, es a konnektalo 
    //fel egyszeruen nem mond semmit, akkor a kommunikacio orokre beragad.
   
    int sckfd=SSL_get_fd(ssl);

    //CCC-ben a socketek blokkolok
    //most atallitjuk nonblockingra
    socket_setoption(sckfd,SOCKOPT_NONBLOCKING,1);

    unsigned long time0=milliseconds();
        
    while(1)
    {
        int retcode=SSL_accept(ssl);
        
        //printf("\nSSL_accept retcode=%d",retcode);fflush(0);

        if( retcode!=-1 )
        {
            _retni(retcode);
            break;
        }
        else
        {
            int errcode=SSL_get_error(ssl,retcode);

            if( errcode==SSL_ERROR_WANT_READ )
            {
                //printf("\nSSL_ERROR_WANT_READ %d",timeout);fflush(0);

                if( SSL_pending(ssl) )
                {
                    //van mit olvasni
                }
                else if( 0>=timeout )
                {
                    _retni(-1000); //sajat hibakod: timeout
                    break;
                }
                else
                {
                    fd_set fd_read;
                    FD_ZERO(&fd_read);
                    FD_SET(sckfd,&fd_read);

                    fd_set fd_err;
                    FD_ZERO(&fd_err);
                    FD_SET(sckfd,&fd_err);
 
                    struct timeval tv;
                    tv.tv_sec=timeout/1000;
                    tv.tv_usec=(timeout%1000)*1000;

                    select(sckfd+1,&fd_read,NULL,&fd_err,&tv);
                }
            }
            else if( errcode==SSL_ERROR_WANT_WRITE  )
            {
                //printf("\nSSL_ERROR_WANT_WRITE %d",timeout);fflush(0);

                if( 0>=timeout )
                {
                    _retni(-1000); //sajat hibakod: timeout
                    break;
                }
                else
                {
                    fd_set fd_writ;
                    FD_ZERO(&fd_writ);
                    FD_SET(sckfd,&fd_writ);

                    fd_set fd_err;
                    FD_ZERO(&fd_err);
                    FD_SET(sckfd,&fd_err);
 
                    struct timeval tv;
                    tv.tv_sec=timeout/1000;
                    tv.tv_usec=(timeout%1000)*1000;

                    select(sckfd+1,NULL,&fd_writ,&fd_err,&tv);
                }
            }
            else
            {
                //char buf[128];
                //ERR_error_string(ERR_peek_error(),buf);
                //printf("\n%s",buf);

                _retni(retcode);
                break;
            }
        }

        unsigned long time1=milliseconds();  
        if( time1<time0 ) //tulcsordulas?
        {
            time0=time1; 
        }
        timeout-=(time1-time0);
        time0=time1;
    }

    //visszaallitjuk blockingra
    socket_setoption(sckfd,SOCKOPT_NONBLOCKING,0);

    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_sslcon_connect(int argno)
{
    CCC_PROLOG("sslcon_connect",2);
    SSL *ssl=(SSL*)_parp(1);
    //masodik parameter: opcionalis blokk!
    _retni(SSL_connect(ssl)); //retcode==1, ha rendben
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_sslcon_clear(int argno)
{
    CCC_PROLOG("sslcon_clear",1);
    SSL *ssl=(SSL*)_parp(1);
    _retni(SSL_clear(ssl)); //retcode==1, ha rendben
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
static int ssl_write(SSL *ssl, void*buf, int len)
{
    // UNIX-on a send SIGPIPE-ot valthat ki, 
    // ha a masik fel megszakitja a kapcsolatot.
    // Ha az nincs kezelve, akkor a send csendben kilep. 
    // Windowson, Solarison, FreeBSD-n MSG_NOSIGNAL=0.
    
    return SSL_write(ssl,(char*)buf,len);
}

//---------------------------------------------------------------------------
static int ssl_read(SSL *s, void*dest, int dlen, int wtime)
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
    unsigned long time0=milliseconds();   //olvasas kezdetenek ideje (ms)
    int sckfd=SSL_get_fd(s);              //socket fdesc

    while( firstread || ((recvlen<dlen) && (wtimerest>0)) )
    {
        fd_set fd_read;
        FD_ZERO(&fd_read);
        FD_SET(sckfd,&fd_read);

        fd_set fd_err;
        FD_ZERO(&fd_err);
        FD_SET(sckfd,&fd_err);
 
        struct timeval tv;
        tv.tv_sec=wtimerest/1000;          //sec
        tv.tv_usec=(wtimerest%1000)*1000;  //mikrosec 

        #ifdef NOT_DEFINED
          Van olyan eset, amikor az SSL alatt levo fd-t a select 
          nem olvashatonak mutatja, de maga az SSL megis olvashato. 
          Ez akkor fordul elo, ha az ssl az fd-bol eloreolvasott, 
          es vannak "pending" byteok.
        #endif

        if( SSL_pending(s) || select(sckfd+1,&fd_read,NULL,&fd_err,&tv) )
        {
            //ide akkor jon, ha 
            //1) van olvasnivalo,
            //2) a csatorna lezarodott,
            //3) a select hibakoddal tert vissza
            
            //a hibat recv eredmenyebol detektaljuk
            //CSAK a result>0 eset szamit sikeresnek
            //Linuxon recv nemletezo vonal eseten 0-at ad
            //NT-n recv nemletezo vonal eseten -1-et ad

            result=SSL_read(s,buf+recvlen,dlen-recvlen);
            //printf("\n>>SSL_read[%d] ",result);fflush(0);
            
            if( result>0 )
            {
                recvlen+=result;
            }
            else
            {
                int sslerr=SSL_get_error(s,recvlen);
                //printf("sslerr[%d] ",sslerr);fflush(0);
                
                     if( sslerr==SSL_ERROR_WANT_READ ){}
                else if( sslerr==SSL_ERROR_WANT_WRITE ){}
                else
                {
                    result=-1;
                    break;
                }
            }
        }
        
        firstread=0;
        if( wtime>=0 )
        {
            unsigned long time1=milliseconds();
            if( time1<time0 ) //tulcsordulas?
            {
                time0=time1;
            }
            wtimerest=wtime-(time1-time0);
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
void _clp_sslcon_write(int argno) //swrite megfeleloje
{
    CCC_PROLOG("sslcon_write",2);
    str2bin(base+1);
    SSL *ssl  = (SSL*)_parp(1);     //SSL struct
    char *buf = _parb(2);           //buffer to write 
    int blen  = _parblen(2);        //number of bytes to write
    _retni( ssl_write(ssl,buf,blen) );
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_sslcon_read(int argno)  //sread megfeleloje
{
    //result:=sslcon_read(ssl,nbyte,wtime)
    //
    //ssl-bol beolvas nbyte darab byteot
    //
    //akkor ter vissza, ha
    //
    //  ready   : result == nbyte hosszusagu bynary string (bytearray)
    //
    //  timeout : result == nbyte-nal rovidebb bynary string (bytearray)
    //
    //  error   : result == NIL, ha semmit sem lehetett olvasni
    //            result == nemures, nbyte-nal rovidebb bytearray

    CCC_PROLOG("sslcon_read",3);
    
    SSL *ssl  = (SSL*)_parp(1);            //SSL socket
    int nbyte = _parni(2);                 //number of bytes to read
    int wtime = ISNUMBER(3)?_parni(3):-1;  //wait time in msec 

    if( (unsigned)nbyte>MAXBINLEN )
    {
        error_bln("sslcon_read",base,argno);
    }

    char *buf=binaryl(nbyte);
    int recvlen=ssl_read(ssl,buf,nbyte,wtime);
    
    if( recvlen<0 )
    {
        push(&NIL);
    }
    else if( recvlen<nbyte )
    {
        binarys(buf,recvlen);
    }
    _rettop();
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_sslcon_pending(int argno)
{
    CCC_PROLOG("sslcon_pending",1);
    SSL *ssl=(SSL*)_parp(1);
    int nbyte=SSL_pending(ssl);
    _retni(nbyte);
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_sslcon_session_reused(int argno)
{
    CCC_PROLOG("sslcon_session_reused",1);
    SSL *ssl=(SSL*)_parp(1);
    _retni( SSL_session_reused(ssl) ); //0=new session, 1=reused session
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_sslcon_shutdown(int argno)
{
    CCC_PROLOG("sslcon_shutdown",1);
    SSL *ssl=(SSL*)_parp(1);
    _retni( SSL_shutdown(ssl) );
    CCC_EPILOG();
}

//--------------------------------------------------------------------------

