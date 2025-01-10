
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

#include <stdint.h>
#include <openssl/pem.h>
#include <ccc_crypto.h>

#define MEMBIO(x)  BIO_new_mem_buf(x,-1)

//-------------------------------------------------------------------------- 
X509 *PEM_parse_X509(char *pem)
{
    BIO *b=MEMBIO(pem);
    X509 *cert=PEM_read_bio_X509(b,0,0,0);
    BIO_free(b);
    return cert;
}

//-------------------------------------------------------------------------- 
EVP_PKEY *PEM_parse_PrivateKey(char *pem)
{
    BIO *b=MEMBIO(pem);
    EVP_PKEY *pkey=PEM_read_bio_PrivateKey(b,0,0,0);
    BIO_free(b);
    return pkey;
}
 
//-------------------------------------------------------------------------- 
RSA *PEM_parse_RSAPrivateKey(char *pem)
{
    BIO *b=MEMBIO(pem);
    EVP_PKEY *pkey=PEM_read_bio_PrivateKey(b,0,0,0);
    BIO_free(b);

    if( pkey )
    {
        RSA *rsa=EVP_PKEY_get1_RSA(pkey);
        EVP_PKEY_free(pkey);
        return rsa;
    }
    return 0;
}

//-------------------------------------------------------------------------- 
EVP_PKEY *PEM_parse_PublicKey(char *pem)
{
    BIO *b=MEMBIO(pem);
    EVP_PKEY *pkey=PEM_read_bio_PUBKEY(b,0,0,0);  //nincs ilyen??
    BIO_free(b);
    return pkey;
}

//-------------------------------------------------------------------------- 
RSA *PEM_parse_RSAPublicKey(char *pem)
{
    BIO *b=MEMBIO(pem);
    EVP_PKEY *pkey=PEM_read_bio_PUBKEY(b,0,0,0);  //nincs ilyen??
    BIO_free(b);

    if( pkey )
    {
        RSA *rsa=EVP_PKEY_get1_RSA(pkey);
        EVP_PKEY_free(pkey);
        return rsa;
    }
    return 0;
}

//-------------------------------------------------------------------------- 
