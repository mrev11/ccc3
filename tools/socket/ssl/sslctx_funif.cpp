
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

//SSL context function interface

#include <string.h>
#include <openssl/err.h>
#include <openssl/ssl.h>

#include <cccapi.h>

static int initmodule()
{
    SSL_load_error_strings();  //printf("SSL_load_error_strings\n");fflush(0); 
    SSL_library_init();        //printf("SSL_library_init\n");fflush(0);  

    extern void init_locking_callback(void);
    init_locking_callback();
    return 1;
}

static int init=initmodule();

//--------------------------------------------------------------------------
void _clp_openssl_get_error(int argno)
{
    CCC_PROLOG("openssl_get_error",0);
    unsigned long errcode=ERR_peek_error();
    _retni(errcode);
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_openssl_error_string(int argno)
{
    CCC_PROLOG("openssl_error_string",1);
    unsigned long errcode=0;
    if( ISNIL(1) )
    {
        errcode=ERR_peek_error();
    }
    else
    {
        errcode=_parnu(1);
    }
    char buf[128];
    ERR_error_string(errcode,buf);
    _retcb(buf);
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_sslctx_new(int argno)
{
    CCC_PROLOG("sslctx_new",1);
    const SSL_METHOD *method=0;
    if( ISNIL(1) )
    {
        method=SSLv23_method(); //kérdéses mi legyen a default
    }
    else
    {
        str2bin(base);
        /* removed
             if( 0==strcmp(_parb(1),"SSLv2") )         method=SSLv2_method();
        else if( 0==strcmp(_parb(1),"SSLv2_server") )  method=SSLv2_server_method();
        else if( 0==strcmp(_parb(1),"SSLv2_client") )  method=SSLv2_client_method();
        else 
        */
        
             if( 0==strcmp(_parb(1),"SSLv3") )         method=SSLv3_method();
        else if( 0==strcmp(_parb(1),"SSLv3_server") )  method=SSLv3_server_method();
        else if( 0==strcmp(_parb(1),"SSLv3_client") )  method=SSLv3_client_method();
        else if( 0==strcmp(_parb(1),"SSLv23") )        method=SSLv23_method();
        else if( 0==strcmp(_parb(1),"SSLv23_server") ) method=SSLv23_server_method();
        else if( 0==strcmp(_parb(1),"SSLv23_client") ) method=SSLv23_client_method();
        else if( 0==strcmp(_parb(1),"TLSv1") )         method=TLSv1_method();
        else if( 0==strcmp(_parb(1),"TLSv1_server") )  method=TLSv1_server_method();
        else if( 0==strcmp(_parb(1),"TLSv1_client") )  method=TLSv1_client_method();
    }

    SSL_CTX *ctx=SSL_CTX_new( (SSL_METHOD*) method );
    if( ctx )
    {
        _retp(ctx);    
    }
    else
    {
        _ret();
    }
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_sslctx_free(int argno)
{
    CCC_PROLOG("sslctx_free",1);
    SSL_CTX *ctx=(SSL_CTX*)_parp(1);
    SSL_CTX_free(ctx);
    _ret();    
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_sslctx_use_certificate_file(int argno)
{
    CCC_PROLOG("sslctx_use_certificate_file",3);
    SSL_CTX *ctx=(SSL_CTX*)_parp(1);
    str2bin(base+1);
    char *fspec=_parb(2);
    int ftype=SSL_FILETYPE_PEM;
    if( !ISNIL(3) )
    {
        ftype=_parni(3);
    }
    int retcode=SSL_CTX_use_certificate_file(ctx,fspec,ftype);
    //printf("retcode %d\n",retcode);fflush(0);
    //ERR_print_errors_fp(stderr);
    _retni( retcode );
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_sslctx_use_certificate_chain_file(int argno)
{
    CCC_PROLOG("sslctx_use_certificate_chain_file",2);
    SSL_CTX *ctx=(SSL_CTX*)_parp(1);
    str2bin(base+1);
    char *fspec=_parb(2);
    int retcode=SSL_CTX_use_certificate_chain_file(ctx,fspec);
    _retni( retcode );
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_sslctx_use_privatekey_file(int argno)
{
    CCC_PROLOG("sslctx_use_privatekey_file",3);
    SSL_CTX *ctx=(SSL_CTX*)_parp(1);
    str2bin(base+1);
    char *fspec=_parb(2);
    int ftype=SSL_FILETYPE_PEM;
    if( !ISNIL(3) )
    {
        ftype=_parni(3);
    }
    int retcode=SSL_CTX_use_PrivateKey_file(ctx,fspec,ftype);
    _retni( retcode );
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_sslctx_check_private_key(int argno)
{
    CCC_PROLOG("sslctx_check_private_key",1);
    SSL_CTX *ctx=(SSL_CTX*)_parp(1);
    int retcode=SSL_CTX_check_private_key(ctx);
    _retni( retcode );
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
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

//--------------------------------------------------------------------------
void _clp_sslctx_set_verify(int argno)
{
    CCC_PROLOG("sslctx_set_verify",2);
    SSL_CTX *ctx=(SSL_CTX*)_parp(1);
    int mode=_parni(2);
    SSL_CTX_set_verify(ctx,mode,cb_verify);
    _ret();
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_sslctx_get_verify_mode(int argno)
{
    CCC_PROLOG("sslctx_get_verify_mode",1);
    SSL_CTX *ctx=(SSL_CTX*)_parp(1);
    _retni(SSL_CTX_get_verify_mode(ctx));
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_sslctx_get_verify_depth(int argno)
{
    CCC_PROLOG("sslctx_get_verify_depth",1);
    SSL_CTX *ctx=(SSL_CTX*)_parp(1);
    _retni(SSL_CTX_get_verify_depth(ctx));
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_sslctx_set_verify_depth(int argno)
{
    CCC_PROLOG("sslctx_set_verify_depth",2);
    SSL_CTX *ctx=(SSL_CTX*)_parp(1);
    int depth=_parni(2);
    SSL_CTX_set_verify_depth(ctx,depth);
    _ret();
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_sslctx_load_verify_locations(int argno)
{
    CCC_PROLOG("sslctx_load_verify_locations",3);
    SSL_CTX *ctx=(SSL_CTX*)_parp(1);
    char *cafile=0;
    char *capath=0;
    if( !ISNIL(2) )
    {
        str2bin(base+1);
        cafile=_parb(2);
    }
    if( !ISNIL(3) )
    {
        str2bin(base+2);
        capath=_parb(3);
    }
    int retcode=SSL_CTX_load_verify_locations(ctx,cafile,capath);
    _retni(retcode);
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_sslctx_load_client_ca_file(int argno)
{
    CCC_PROLOG("sslctx_load_client_ca_file",2);
    SSL_CTX *ctx=(SSL_CTX*)_parp(1);
    str2bin(base+1);
    char *cafile=_parb(2);
    int retcode=0; //failure
    STACK_OF(X509_NAME)*cert_names=SSL_load_client_CA_file(cafile);
    if( cert_names )
    {
        SSL_CTX_set_client_CA_list(ctx,cert_names);
        retcode=1; //success
    }
    _retni(retcode);
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_sslctx_get_quiet_shutdown(int argno)
{
    CCC_PROLOG("sslctx_get_quiet_shutdown",1);
    SSL_CTX *ctx=(SSL_CTX*)_parp(1);
    _retl( SSL_CTX_get_quiet_shutdown(ctx) );
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_sslctx_set_quiet_shutdown(int argno)
{
    CCC_PROLOG("sslctx_set_quiet_shutdown",2);
    SSL_CTX *ctx=(SSL_CTX*)_parp(1);
    int flag=_parl(2);
    SSL_CTX_set_quiet_shutdown(ctx,flag);
    _ret();
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
// session cache handling
//--------------------------------------------------------------------------
void _clp_sslctx_set_session_id_context(int argno)
{
    CCC_PROLOG("sslctx_set_session_id_context",2);
    SSL_CTX *ctx=(SSL_CTX*)_parp(1);
    unsigned char *sidctx=(unsigned char*)_parcb(2);
    int len=_parblen(2);
    _retni( SSL_CTX_set_session_id_context(ctx,sidctx,len) ); //0=failed, 1=succeeded
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_sslctx_get_session_cache_mode(int argno)
{
    CCC_PROLOG("sslctx_get_session_cache_mode",1);
    SSL_CTX *ctx=(SSL_CTX*)_parp(1);
    _retnl( SSL_CTX_get_session_cache_mode(ctx) );
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_sslctx_set_session_cache_mode(int argno)
{
    CCC_PROLOG("sslctx_set_session_cache_mode",2);
    SSL_CTX *ctx=(SSL_CTX*)_parp(1);
    long mode=_parnl(2);
    _retnl( SSL_CTX_set_session_cache_mode(ctx,mode) );
    CCC_EPILOG();
}


//--------------------------------------------------------------------------
void _clp_sslctx_get_timeout(int argno)
{
    //session cache timeout in seconds
    //default = 300 sec

    CCC_PROLOG("sslctx_get_timeout",1);
    SSL_CTX *ctx=(SSL_CTX*)_parp(1);
    _retni( SSL_CTX_get_timeout(ctx) ); 
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_sslctx_set_timeout(int argno)
{
    //sets session cache timeout (in seconds)
    //returns previous timeout (in seconds)

    CCC_PROLOG("sslctx_set_timeout",2);
    SSL_CTX *ctx=(SSL_CTX*)_parp(1);
    long timeout=_parnl(2);
    _retni( SSL_CTX_set_timeout(ctx,timeout) ); 
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_sslctx_sess_get_cache_size(int argno)
{
    CCC_PROLOG("sslctx_sess_get_cache_size",1);
    SSL_CTX *ctx=(SSL_CTX*)_parp(1);
    _retnl( SSL_CTX_sess_get_cache_size(ctx) );
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_sslctx_sess_set_cache_size(int argno)
{
    CCC_PROLOG("sslctx_sess_set_cache_size",2);
    SSL_CTX *ctx=(SSL_CTX*)_parp(1);
    long size=_parnl(2); //0=korlátlan!
    _retnl( SSL_CTX_sess_set_cache_size(ctx,size) );
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_sslctx_flush_sessions(int argno)
{
    CCC_PROLOG("sslctx_flush_sessions",1);
    SSL_CTX *ctx=(SSL_CTX*)_parp(1);
    SSL_CTX_flush_sessions(ctx,time(0));
    _ret();
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_sslctx_sess_number(int argno)
{
    CCC_PROLOG("sslctx_sess_number",1);
    SSL_CTX *ctx=(SSL_CTX*)_parp(1);
    _retni(SSL_CTX_sess_number(ctx));
    CCC_EPILOG();
}

//--------------------------------------------------------------------------



