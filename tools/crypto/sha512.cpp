
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
void _clp_crypto_sha512(int argno)
{
    CCC_PROLOG("crypto_sha512",1);
    char *text=_parb(1);
    size_t length=_parblen(1);

    SHA512_CTX *c=new SHA512_CTX();
    SHA512_Init(c);
    SHA512_Update(c,text,length);
    char sha512[SHA512_DIGEST_LENGTH];
    SHA512_Final((unsigned char*)sha512,c);
    delete c;

    _retblen( sha512, SHA512_DIGEST_LENGTH );

    CCC_EPILOG();
}

//---------------------------------------------------------------------------- 
void _clp_crypto_sha512_init(int argno)
{
    CCC_PROLOG("crypto_sha512_init",0);
    SHA512_CTX *c=new SHA512_CTX();
    SHA512_Init(c);
    _retp(c);
    CCC_EPILOG();
}
 

//---------------------------------------------------------------------------- 
void _clp_crypto_sha512_update(int argno)
{
    CCC_PROLOG("crypto_sha512_update",2);
    SHA512_CTX *c=(SHA512_CTX*)_parp(1);
    char *text=_parb(2);
    size_t length=_parblen(2);
    SHA512_Update(c,text,length);
    _ret();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------- 
void _clp_crypto_sha512_final(int argno)
{
    CCC_PROLOG("crypto_sha512_final",1);
    SHA512_CTX *c=(SHA512_CTX*)_parp(1);
    char sha512[SHA512_DIGEST_LENGTH]; 
    SHA512_Final((unsigned char*)sha512,c);
    delete c;
    _retblen( sha512, SHA512_DIGEST_LENGTH );
    CCC_EPILOG();
}

//---------------------------------------------------------------------------- 

#ifdef HOW_TO_USE_SHA512_FUNCTIONS

function main()

local text:=memoread("main.prg",.t.) 
local sha512, hex, shactx, n


    sha512:=crypto_sha512(text) 
    hex:=crypto_bin2hex(sha512) 
    ? hex, len(hex)
    
    shactx:=crypto_sha512_init()
    for n:=1 to len(text)
        crypto_sha512_update(shactx,substr(text,n,1))
    next
    sha512:=crypto_sha512_final(shactx)  
    hex:=crypto_bin2hex(sha512) 
    ? hex, len(hex)
    ?

    run("sha512sum main.prg")

    ?

#endif    

//---------------------------------------------------------------------------- 

