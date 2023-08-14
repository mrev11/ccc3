
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
 
#include <stdio.h>
#include <string.h>
#include <openssl/cast.h>
#include <cccapi.h>

//extern void hexdump(void *p, int size);

#define CAST_BLOCKSIZE  8
#define LENOUT(l)       ((l)%8?(l)+8-(l)%8:l)  //kiegészít 8 többszörösére


//---------------------------------------------------------------------------- 
void _clp_crypto_cast_set_key(int argno)
{
    // 1 - key
    //      maximum az első 16 byte-ot használja
    //      10-nél kisebb kulcs "rövid"-nek számít

    CCC_PROLOG("crypto_cast_set_key",1);
    const unsigned char *data=(const unsigned char *)_parb(1);
    size_t len=_parblen(1);
    CAST_KEY *ks=(CAST_KEY*)binaryl(sizeof(CAST_KEY));
    CAST_set_key(ks,len,data);
    _rettop();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------- 
void _clp_crypto_cast_ecb_encrypt(int argno)
{
    // 1 - input, 8 byte hosszú
    // 2 - key
    // 3 - enc, .t.=encrypt, .f.=decrypt

    CCC_PROLOG("crypto_cast_ecb_encrypt",3);
    const unsigned char *in=(const unsigned char *)_parb(1);
    if( _parblen(1)!=CAST_BLOCKSIZE )
    {
        ARGERROR();
    }
    CAST_KEY *ks=(CAST_KEY*)_parb(2);
    if( _parblen(2)!=sizeof(CAST_KEY) )
    {
        ARGERROR();
    }
    int enc=_parl(3)?CAST_ENCRYPT:CAST_DECRYPT;
    unsigned char*out=(unsigned char*)binaryl(CAST_BLOCKSIZE);
    CAST_ecb_encrypt(in,out,ks,enc);
    _rettop();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------- 
void _clp_crypto_cast_cbc_encrypt(int argno)
{
    // 1 - input, binary
    // 2 - key
    // 3 - ivec, refbinary 8 bytes
    // 4 - enc , .t.=encrypt, .f.=decrypt

    CCC_PROLOG("crypto_cast_cbc_encrypt",4);
    const unsigned char *in=(const unsigned char *)_parb(1);
    size_t length_in=_parblen(1);
    size_t length_out=LENOUT(length_in);
    CAST_KEY *ks=(CAST_KEY *)_parb(2);
    if( _parblen(2)!=sizeof(CAST_KEY) )
    {
        ARGERROR();
    }
    if( REFBINLEN(3)!=CAST_BLOCKSIZE )
    {
        ARGERROR();
    }
    unsigned char *ivec=(unsigned char *)binaryl(CAST_BLOCKSIZE);
    memcpy((char*)ivec,REFBINPTR(3),CAST_BLOCKSIZE);

    int enc=_parl(4)?CAST_ENCRYPT:CAST_DECRYPT;
    unsigned char *out=(unsigned char*)binaryl(length_out);
    CAST_cbc_encrypt(in,out,length_in,ks,ivec,enc);
    *REFVALUE(3)=*TOP2(); //ivec
    _rettop();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------- 
void _clp_crypto_cast_cfb64_encrypt(int argno)
{
    // 1 - input, binary
    // 2 - key
    // 3 - ivec, refbinary 8 bytes
    // 4 - num, refnumber (firstly 0)
    // 5 - enc , .t.=encrypt, .f.=decrypt

    CCC_PROLOG("crypto_cast_cfb64_encrypt",5);
    
    const unsigned char *in=(const unsigned char *)_parb(1);
    size_t length=_parblen(1);

    CAST_KEY *ks=(CAST_KEY *)_parb(2); //kulcs
    if( _parblen(2)!=sizeof(CAST_KEY) )
    {
        ARGERROR(); 
    }

    //ivec
    if( REFBINLEN(3)!=CAST_BLOCKSIZE )
    {
        ARGERROR(); 
    }
    unsigned char *ivec=(unsigned char *)binaryl(CAST_BLOCKSIZE);
    memcpy((char*)ivec,REFBINPTR(3),CAST_BLOCKSIZE);

    //num
    int num=0;
    if( !ISREF(4) )
    {
        ARGERROR();
    }
    VALUE *valnum=REFVALUE(4);
    if( valnum->type==TYPE_NUMBER )
    {
        num=D2INT(valnum->data.number);
    }

    int enc=_parl(5)?CAST_ENCRYPT:CAST_DECRYPT;

    unsigned char *out=(unsigned char*)binaryl(length);
    CAST_cfb64_encrypt(in,out,length,ks,ivec,&num,enc);

    *REFVALUE(3)=*TOP2(); //ivec
    valnum->type=TYPE_NUMBER;
    valnum->data.number=(double)num;
    _rettop();

    CCC_EPILOG();
}

//---------------------------------------------------------------------------- 
void _clp_crypto_cast_ofb64_encrypt(int argno)
{
    // 1 - input, binary
    // 2 - key
    // 3 - ivec, refbinary 8 bytes
    // 4 - num, refnumber (firstly 0)

    CCC_PROLOG("crypto_cast_ofb64_encrypt",4);
    
    const unsigned char *in=(const unsigned char *)_parb(1);
    size_t length=_parblen(1);

    CAST_KEY *ks=(CAST_KEY *)_parb(2); //kulcs
    if( _parblen(2)!=sizeof(CAST_KEY) )
    {
        ARGERROR(); 
    }

    //ivec
    if( REFBINLEN(3)!=CAST_BLOCKSIZE )
    {
        ARGERROR(); 
    }
    unsigned char *ivec=(unsigned char *)binaryl(CAST_BLOCKSIZE);
    memcpy((char*)ivec,REFBINPTR(3),CAST_BLOCKSIZE);

    //num
    int num=0;
    if( !ISREF(4) )
    {
        ARGERROR();
    }
    VALUE *valnum=REFVALUE(4);
    if( valnum->type==TYPE_NUMBER )
    {
        num=D2INT(valnum->data.number);
    }

    unsigned char *out=(unsigned char*)binaryl(length);
    CAST_ofb64_encrypt(in,out,length,ks,ivec,&num);

    *REFVALUE(3)=*TOP2(); //ivec
    valnum->type=TYPE_NUMBER;
    valnum->data.number=(double)num;
    _rettop();

    CCC_EPILOG();
}

//---------------------------------------------------------------------------- 
