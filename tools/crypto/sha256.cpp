
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

//interfész az openssl könyvtárhoz
 
#include <stdint.h>
#include <stdio.h>
//#include <string.h>

#include <openssl/sha.h>

#include <cccapi.h>
 
//---------------------------------------------------------------------------- 
void _clp_crypto_sha256(int argno)
{
    CCC_PROLOG("crypto_sha256",1);
    char *text=_parb(1);
    size_t length=_parblen(1);

    SHA256_CTX *c=new SHA256_CTX();
    SHA256_Init(c);
    SHA256_Update(c,text,length);
    char sha256[SHA256_DIGEST_LENGTH];
    SHA256_Final((unsigned char*)sha256,c);
    delete c;

    _retblen( sha256, SHA256_DIGEST_LENGTH );

    CCC_EPILOG();
}

//---------------------------------------------------------------------------- 
void _clp_crypto_sha256_init(int argno)
{
    CCC_PROLOG("crypto_sha256_init",0);
    SHA256_CTX *c=new SHA256_CTX();
    SHA256_Init(c);
    _retp(c);
    CCC_EPILOG();
}
 

//---------------------------------------------------------------------------- 
void _clp_crypto_sha256_update(int argno)
{
    CCC_PROLOG("crypto_sha256_update",2);
    SHA256_CTX *c=(SHA256_CTX*)_parp(1);
    char *text=_parb(2);
    size_t length=_parblen(2);
    SHA256_Update(c,text,length);
    _ret();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------- 
void _clp_crypto_sha256_final(int argno)
{
    CCC_PROLOG("crypto_sha256_final",1);
    SHA256_CTX *c=(SHA256_CTX*)_parp(1);
    char sha256[SHA256_DIGEST_LENGTH]; 
    SHA256_Final((unsigned char*)sha256,c);
    delete c;
    _retblen( sha256, SHA256_DIGEST_LENGTH );
    CCC_EPILOG();
}

//---------------------------------------------------------------------------- 

#ifdef HOW_TO_USE_SHA256_FUNCTIONS

function main()

local text:=memoread("main.prg",.t.) 
local sha256, hex, shactx, n


    sha256:=crypto_sha256(text) 
    hex:=crypto_bin2hex(sha256) 
    ? hex, len(hex)
    
    shactx:=crypto_sha256_init()
    for n:=1 to len(text)
        crypto_sha256_update(shactx,substr(text,n,1))
    next
    sha256:=crypto_sha256_final(shactx)  
    hex:=crypto_bin2hex(sha256) 
    ? hex, len(hex)
    ?

    run("sha256sum main.prg")

    ?

#endif    

//---------------------------------------------------------------------------- 

