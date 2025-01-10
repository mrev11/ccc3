
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

#include <openssl/md5.h>

#include <cccapi.h>
 
//---------------------------------------------------------------------------- 
void _clp_crypto_md5(int argno)
{
    CCC_PROLOG("crypto_md5",1);
    str2bin(base);
    char *text=_parb(1);
    size_t length=_parblen(1);

    MD5_CTX *c=new MD5_CTX();
    MD5_Init(c);
    MD5_Update(c,text,length);
    char md5[MD5_DIGEST_LENGTH];
    MD5_Final((unsigned char*)md5,c);
    delete c;

    _retblen( md5, MD5_DIGEST_LENGTH );

    CCC_EPILOG();
}

//---------------------------------------------------------------------------- 
void _clp_crypto_md5_init(int argno)
{
    CCC_PROLOG("crypto_md5_init",0);
    MD5_CTX *c=new MD5_CTX();
    MD5_Init(c);
    _retp(c);
    CCC_EPILOG();
}

//---------------------------------------------------------------------------- 
void _clp_crypto_md5_update(int argno)
{
    CCC_PROLOG("crypto_md5_update",2);
    MD5_CTX *c=(MD5_CTX*)_parp(1);
    str2bin(base+1);
    char *text=_parb(2);
    size_t length=_parblen(2);
    MD5_Update(c,text,length);
    _ret();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------- 
void _clp_crypto_md5_final(int argno)
{
    CCC_PROLOG("crypto_md5_final",1);
    MD5_CTX *c=(MD5_CTX*)_parp(1);
    char md5[MD5_DIGEST_LENGTH]; 
    MD5_Final((unsigned char*)md5,c);
    delete c;
    _retblen( md5, MD5_DIGEST_LENGTH );
    CCC_EPILOG();
}

//---------------------------------------------------------------------------- 

#ifdef HOW_TO_USE_MD5_FUNCTIONS

local text:="Van, aki forrón szereti!" 
local md5, hex, md5ctx, n


    md5:=crypto_md5(text) 
    hex:=crypto_bin2hex(md5) 
    ? hex, len(hex)
    ?
    
    md5ctx:=crypto_md5_init()
    for n:=1 to len(text)
        crypto_md5_update(md5ctx,substr(text,n,1))
    next
    md5:=crypto_md5_final(md5ctx)  
    hex:=crypto_bin2hex(md5) 
    ? hex, len(hex)
    ?

    return NIL

#endif    

//---------------------------------------------------------------------------- 

