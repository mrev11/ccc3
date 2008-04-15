
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

#include <openssl/err.h>
#include <openssl/pem.h>

#include <cccapi.h>
#include <ccc_crypto.h>

//-------------------------------------------------------------------------- 
void _clp_crypto_rsa_public_encrypt(int argno) 
{
    CCC_PROLOG("crypto_rsa_public_encrypt",2);

    char *datbuf=_parb(1);
    int datlen=_parblen(1);

    char *key=_parb(2); 

    RSA *rsa=PEM_parse_RSAPublicKey(key); 
    if( rsa==NULL )
    {
        crypto_error("PEM_parse_RSAPublicKey");
    }

    //Ezt tudják a normális fordítók (GCC):
    //  unsigned char buf[ RSA_size(rsa) ];
    //A windowsos C++ fordítók gyatrák,
    //az alábbi megoldással a buffer a CCC stacken van,
    //és a CCC szemétgyűjtés fogja eltakarítani.

    char *buf=binaryl(RSA_size(rsa));
    int len=RSA_public_encrypt(datlen,(unsigned char*)datbuf,(unsigned char*)buf,rsa,RSA_PKCS1_OAEP_PADDING);

    RSA_free(rsa);
    
    if( len<0 )
    {
        crypto_error("RSA_public_encrypt");
    }

    _retblen(buf,len);

    CCC_EPILOG();
}


//-------------------------------------------------------------------------- 
void _clp_crypto_rsa_private_decrypt(int argno) 
{
    CCC_PROLOG("crypto_rsa_private_decrypt",2);

    char *datbuf=_parb(1);
    int datlen=_parblen(1);

    char *key=_parb(2);

    RSA *rsa=PEM_parse_RSAPrivateKey(key);  
    if( rsa==NULL )
    {
        crypto_error("PEM_parse_RSAPrivateKey");
    }

    //Ezt tudják a normális fordítók (GCC):
    //  unsigned char buf[ RSA_size(rsa) ];
    //A windowsos C++ fordítók gyatrák,
    //az alábbi megoldással a buffer a CCC stacken van,
    //és a CCC szemétgyűjtés fogja eltakarítani.

    char *buf=binaryl(RSA_size(rsa));
    int len=RSA_private_decrypt(datlen,(unsigned char*)datbuf,(unsigned char*)buf,rsa,RSA_PKCS1_OAEP_PADDING);

    RSA_free(rsa);
    
    if( len<0 )
    {
        crypto_error("RSA_private_decrypt");
    }

    _retblen(buf,len);

    CCC_EPILOG();
}
 
//-------------------------------------------------------------------------- 

