
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

#include <stdio.h>
#include <string.h>
 
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/buffer.h>
#include <openssl/opensslv.h>

#include <cccapi.h>
#include <ccc_crypto.h>

#if OPENSSL_VERSION_NUMBER <  0x10100000L
static EVP_MD_CTX *EVP_MD_CTX_new(){return new EVP_MD_CTX;}
static void EVP_MD_CTX_free(EVP_MD_CTX *ctx){delete ctx;}
#endif
 
//-------------------------------------------------------------------------- 
void _clp_crypto_sign(int argno)  //egy lépésben
{
    CCC_PROLOG("crypto_sign",2);

    char *datbuf=_parb(1);
    int datlen=_parblen(1);

    char *privkey=_parb(2);

    EVP_PKEY *pkey=PEM_parse_PrivateKey(privkey);   //new
    if( pkey==NULL )
    {
        crypto_error("PEM_parse_PrivateKey");
    }

    EVP_MD_CTX *md_ctx=EVP_MD_CTX_new();
    EVP_SignInit(md_ctx,EVP_sha1());
    EVP_SignUpdate(md_ctx,datbuf,datlen);

    //Ezt tudják a normális fordítók (GCC):
    //  unsigned char sigbuf[ EVP_PKEY_size(pkey) ];
    //A windowsos C++ fordítók gyatrák,
    //az alábbi megoldással a buffer a CCC stacken van,
    //és a CCC szemétgyűjtés fogja eltakarítani.

    char *sigbuf=binaryl(EVP_PKEY_size(pkey));
    unsigned int siglen=0; //output
    int res=EVP_SignFinal(md_ctx,(unsigned char*)sigbuf,&siglen,pkey);

    EVP_PKEY_free(pkey);                            //free
    EVP_MD_CTX_free(md_ctx);    
    
    if( res!=1 )
    {
        crypto_error("EVP_SignFinal");
    }

    _retblen(sigbuf,siglen);

    CCC_EPILOG();
}

//-------------------------------------------------------------------------- 
void _clp_crypto_sign_init(int argno)  //részletekben
{
    CCC_PROLOG("crypto_sign_init",0);
    EVP_MD_CTX *md_ctx=EVP_MD_CTX_new();
    EVP_SignInit(md_ctx,EVP_sha1());
    _retp(md_ctx);
    CCC_EPILOG();
}

//-------------------------------------------------------------------------- 
void _clp_crypto_sign_update(int argno)
{
    CCC_PROLOG("crypto_sign_update",2);
    EVP_MD_CTX *md_ctx=(EVP_MD_CTX*)_parp(1); 
    char *datbuf=_parb(2);
    int datlen=_parblen(2);
    EVP_SignUpdate(md_ctx,datbuf,datlen);
    _ret();
    CCC_EPILOG();
}

//-------------------------------------------------------------------------- 
void _clp_crypto_sign_final(int argno)
{
    CCC_PROLOG("crypto_sign_final",2);
    EVP_MD_CTX *md_ctx=(EVP_MD_CTX*)_parp(1); 

    char *privkey=_parb(2);

    EVP_PKEY *pkey=PEM_parse_PrivateKey(privkey); 
    if( pkey==NULL )
    {
        EVP_MD_CTX_free(md_ctx);
        crypto_error("PEM_parse_PrivateKey");
    }

    //Ezt tudják a normális fordítók (GCC):
    //  unsigned char sigbuf[ EVP_PKEY_size(pkey) ];
    //A windowsos C++ fordítók gyatrák,
    //az alábbi megoldással a buffer a CCC stacken van,
    //és a CCC szemétgyűjtés fogja eltakarítani.

    char *sigbuf=binaryl(EVP_PKEY_size(pkey));
    unsigned int siglen=0; //output
    int res=EVP_SignFinal(md_ctx,(unsigned char*)sigbuf,&siglen,pkey);

    EVP_PKEY_free(pkey);
    EVP_MD_CTX_free(md_ctx);
 
    if( 1!=res )
    {
        crypto_error("EVP_SignFinal");
    }

    _retblen(sigbuf,siglen);

    CCC_EPILOG();
}


//-------------------------------------------------------------------------- 
void _clp_crypto_verify(int argno)  //egy lépésben
{
    CCC_PROLOG("crypto_verify",3);

    str2bin(base+0);
    str2bin(base+1);
    str2bin(base+2);

    char *datbuf=_parb(1);
    int datlen=_parblen(1);

    char *bm=_parb(2);

    unsigned char *sigbuf=(unsigned char*)_parb(3);
    unsigned int siglen=(unsigned int)_parblen(3);

    EVP_PKEY *pkey=0;
    
    if( 0==strstr(bm,"CERTIFICATE") )
    {
        //printf("\nwith PUBLIC KEY");
        pkey=PEM_parse_PublicKey(bm); 
        if( pkey==NULL )
        {
            crypto_error("PEM_parse_PublicKey");
        }
    }
    else
    {
        //printf("\nwith X509 CERTIFICATE");
        X509 *x509=PEM_parse_X509(bm);
        if( x509==NULL ) 
        {
            crypto_error("PEM_parse_X509");
        }
 
        pkey=X509_get_pubkey(x509); 
        if( pkey==NULL )
        {
            X509_free(x509);
            crypto_error("X509_get_pubkey");
        }

        X509_free(x509);                                   
    }
  
    EVP_MD_CTX *md_ctx=EVP_MD_CTX_new();
    EVP_VerifyInit(md_ctx,EVP_sha1());
    EVP_VerifyUpdate(md_ctx,datbuf,datlen);
    int res=EVP_VerifyFinal(md_ctx,sigbuf,siglen,pkey);

    EVP_PKEY_free(pkey);
    EVP_MD_CTX_free(md_ctx);    
    
    _retl( res==1 );

    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_crypto_verify_init(int argno)  //részletekben
{
    CCC_PROLOG("crypto_verify_init",0);
    EVP_MD_CTX *md_ctx=EVP_MD_CTX_new();
    EVP_VerifyInit(md_ctx,EVP_sha1());
    _retp(md_ctx);
    CCC_EPILOG();
}

//-------------------------------------------------------------------------- 
void _clp_crypto_verify_update(int argno)
{
    CCC_PROLOG("crypto_verify_update",2);
    EVP_MD_CTX *md_ctx=(EVP_MD_CTX*)_parp(1); 
    char *datbuf=_parb(2);
    int datlen=_parblen(2);
    EVP_VerifyUpdate(md_ctx,datbuf,datlen);
    _ret();
    CCC_EPILOG();
}

//-------------------------------------------------------------------------- 
void _clp_crypto_verify_final(int argno)
{
    CCC_PROLOG("crypto_verify_final",3);
    EVP_MD_CTX *md_ctx=(EVP_MD_CTX*)_parp(1); 

    char *bm=_parb(2);

    unsigned char *sigbuf=(unsigned char*)_parb(3);
    unsigned int siglen=(unsigned int)_parblen(3);

    EVP_PKEY *pkey=0;

    if( 0==strstr(bm,"CERTIFICATE") )
    {
        //printf("\nwith PUBLIC KEY");
        pkey=PEM_parse_PublicKey(bm); 
        if( pkey==NULL )
        {
            EVP_MD_CTX_free(md_ctx);    
            crypto_error("PEM_parse_PublicKey");
        }
    }
    else
    {
        //printf("\nwith X509 CERTIFICATE");
        X509 *x509=PEM_parse_X509(bm);
        if( x509==NULL ) 
        {
            EVP_MD_CTX_free(md_ctx);    
            crypto_error("PEM_parse_X509");
        }
 
        pkey=X509_get_pubkey(x509); 
        if( pkey==NULL )
        {
            X509_free(x509);
            EVP_MD_CTX_free(md_ctx);    
            crypto_error("X509_get_pubkey");
        }

        X509_free(x509);                                   
    }
  
    int res=EVP_VerifyFinal(md_ctx,sigbuf,siglen,pkey);

    EVP_PKEY_free(pkey);
    EVP_MD_CTX_free(md_ctx);    
   
    _retl( res==1 );

    CCC_EPILOG();
}

//-------------------------------------------------------------------------- 
 

