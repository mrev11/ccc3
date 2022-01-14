
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


//#include <unistd.h>
//#include <sys/wait.h>
 
#include <openssl/err.h>
#include <openssl/ssl.h>
 
#include <sckcompat.h>
#include <sckutil.h>


#define CAPATH      "SSLFORW_CAPATH"
#define CAFILE      "SSLFORW_CAFILE"
#define CADEPTH     "SSLFORW_CADEPTH"
#define CERTFILE    "SSLFORW_CERTFILE"
#define PKEYFILE    "SSLFORW_PKEYFILE"

#define SSL_VERIFY_PEER_CERT    (SSL_VERIFY_PEER+SSL_VERIFY_FAIL_IF_NO_PEER_CERT+SSL_VERIFY_CLIENT_ONCE)


//-----------------------------------------------------------------------------------
static const char* capath()
{
    static const char*p=getenv(CAPATH);
    if( (p!=0) && (*p!=0) )
    {
        return p;
    }
    return 0;
}

static const char* cafile()
{
    static const char*p=getenv(CAFILE);
    if( (p!=0) && (*p!=0) )
    {
        return p;
    }
    return 0;
}

static int cadepth()
{
    static const char*p=getenv(CADEPTH);
    if( (p!=0) && (*p!=0) )
    {
        return atoi(p);
    }
    return 100;
}

static const char* pkeyfile()
{
    static const char*p=getenv(PKEYFILE);
    if( (p!=0) && (*p!=0) )
    {
        return p;
    }
    return 0;
}


static const char* certfile()
{
    static const char*p=getenv(CERTFILE);
    if( (p!=0) && (*p!=0) )
    {
        return p;
    }
    
    //ha nincs megadva a CERTFILE,
    //akkor feltetelezi, hogy a PKEYFILE
    //a certificate-ot is tartalmazza
    
    return pkeyfile();
}


//-----------------------------------------------------------------------------------
static void error()
{
    ERR_print_errors_fp(stderr);
    exit(1);
}

//-----------------------------------------------------------------------------------
static int cb_verify(int preverify_ok, X509_STORE_CTX *ctx)
{
    if( preverify_ok )
    {
        char buf[512]; buf[0]=0;
        //SSL *ssl=(SSL*)X509_STORE_CTX_get_ex_data(ctx,SSL_get_ex_data_X509_STORE_CTX_idx());
        X509 *cert=X509_STORE_CTX_get_current_cert(ctx);
        X509_NAME_oneline(X509_get_subject_name(cert),buf,256);
        fprintf(stderr,"\nsslaccept: %s",buf);
    }
    return preverify_ok;
}


//-----------------------------------------------------------------------------------
SSL_CTX *ssl_server_context()
{
    int ftype=SSL_FILETYPE_PEM; //bedrótozva
    int mode=SSL_VERIFY_PEER_CERT; //bedrótozva


    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();
    SSL_CTX *ctx=SSL_CTX_new( SSLv23_server_method() );
    
    if( !SSL_CTX_use_certificate_file(ctx,certfile(),ftype) )
    {
        error();
    }    

    if( !SSL_CTX_use_PrivateKey_file(ctx,pkeyfile(),ftype) )
    {
        error();
    }

    if( !SSL_CTX_check_private_key(ctx) )
    {
        error();
    }
    

    if( capath() || cafile() )
    {
        SSL_CTX_set_verify(ctx,mode,cb_verify);
        SSL_CTX_set_verify_depth(ctx,cadepth());
        SSL_CTX_load_verify_locations(ctx,cafile(),capath());
    }
    
    return ctx;

}


//-----------------------------------------------------------------------------------
SSL_CTX *ssl_client_context()
{
    int ftype=SSL_FILETYPE_PEM; //bedrótozva
    int mode=SSL_VERIFY_PEER_CERT; //bedrótozva


    SSL_load_error_strings();
    OpenSSL_add_ssl_algorithms();
    SSL_CTX *ctx=SSL_CTX_new( SSLv23_client_method() );

    if( certfile() )
    {    
        if( !SSL_CTX_use_certificate_file(ctx,certfile(),ftype) )
        {
            error();
        }
    }    

    if( pkeyfile() )
    {
        if( !SSL_CTX_use_PrivateKey_file(ctx,pkeyfile(),ftype) )
        {
            error();
        }
        if( !SSL_CTX_check_private_key(ctx) )
        {
            error();
        }
    }

    if( capath() || cafile() )
    {
        SSL_CTX_set_verify(ctx,mode,cb_verify);
        SSL_CTX_set_verify_depth(ctx,cadepth());
        SSL_CTX_load_verify_locations(ctx,cafile(),capath());
    }
    
    return ctx;
}

//-----------------------------------------------------------------------------------

