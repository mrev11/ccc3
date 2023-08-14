
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
#include <openssl/des.h>
#include <cccapi.h>

//extern void hexdump(void *p, int size);

#define LENOUT(l)       ((l)%8?(l)+8-(l)%8:l)  //kiegészít 8 többszörösére
 
//---------------------------------------------------------------------------- 
void _clp_crypto_des_random_key(int argno)
{
    CCC_PROLOG("crypto_des_random_key",0);
    DES_cblock key;
    memset(&key,0,sizeof(key));
    DES_random_key(&key);
    _retblen((char*)&key,sizeof(key));
    CCC_EPILOG();
}

//---------------------------------------------------------------------------- 
void _clp_crypto_des_set_key_unchecked(int argno)
{
    CCC_PROLOG("crypto_des_set_key_unchecked",1);
    const_DES_cblock *key=(const_DES_cblock *)_parb(1); //8 byte
    if( _parblen(1)!=8 )
    {
        ARGERROR();
    }
    DES_key_schedule schedule;
    memset(&schedule,0,sizeof(schedule));
    DES_set_key_unchecked(key,&schedule);
    _retblen((char*)&schedule,sizeof(schedule));
    CCC_EPILOG();
}

//---------------------------------------------------------------------------- 
void _clp_crypto_des_set_key_checked(int argno)
{
    CCC_PROLOG("crypto_des_set_key_checked",1);
    const_DES_cblock *key=(const_DES_cblock *)_parb(1); //8 byte
    if( _parblen(1)!=8 )
    {
        ARGERROR();
    }
    DES_key_schedule schedule;
    memset(&schedule,0,sizeof(schedule));
    int ret=DES_set_key_checked(key,&schedule);
    if( ret<0 )
    {
        _ret();
    }
    else
    {
        _retblen((char*)&schedule,sizeof(schedule));
    }
    CCC_EPILOG();
}

//---------------------------------------------------------------------------- 
void _clp_crypto_des_set_odd_parity(int argno)
{
    CCC_PROLOG("crypto_des_set_odd_parity",1);
    DES_cblock *key=(DES_cblock*)_parb(1); //8 byte
    if( _parblen(1)!=8 )
    {
        ARGERROR();
    }
    DES_set_odd_parity(key);
    _retblen((char*)key,sizeof(DES_cblock));
    CCC_EPILOG();
}

//---------------------------------------------------------------------------- 
void _clp_crypto_des_is_weak_key(int argno)
{
    CCC_PROLOG("crypto_des_is_weak_key",1);
    const_DES_cblock *key=(const_DES_cblock*)_parb(1); //8 byte
    if( _parblen(1)!=8 )
    {
        ARGERROR();
    }
    _retl( 0!=DES_is_weak_key(key) );
    CCC_EPILOG();
}

//---------------------------------------------------------------------------- 
void _clp_crypto_des_ecb_encrypt(int argno) //Electronic Code Book
{
    CCC_PROLOG("crypto_des_ecb_encrypt",3);
    const_DES_cblock *input=(const_DES_cblock*)_parb(1); //8 byte
    if( _parblen(1)!=8 )
    {
        ARGERROR();
    }
    DES_key_schedule *ks=(DES_key_schedule *)_parb(2); //kulcs
    if( _parblen(2)!=sizeof(DES_key_schedule) )
    {
        ARGERROR();
    }
    int enc=_parl(3)?DES_ENCRYPT:DES_DECRYPT; //flag: .t.=titkosít, .f.=visszafejt
    DES_cblock *output=(DES_cblock *)binaryl(sizeof(DES_cblock));
    DES_ecb_encrypt(input,output,ks,enc);
    _rettop();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------- 
#ifndef INTERFACE_DOWNGRADE
#define DESCBLOCK
#else
#define DESCBLOCK  (unsigned char*)
    //openssl 0.9.7.a-ban ez kell
    //ki kéne hagyni ezeket a szemeteket
    //az interface változás miatt nem lehet
    //minden rendszeren egyformán fordítani
#endif

void _clp_crypto_des_ecb2_encrypt(int argno) //Electronic Code Book
{
    CCC_PROLOG("crypto_des_ecb2_encrypt",4);
    const_DES_cblock *input=(const_DES_cblock*)_parb(1); //8 byte
    if( _parblen(1)!=8 )
    {
        ARGERROR();
    }
    DES_key_schedule *ks1=(DES_key_schedule *)_parb(2); //kulcs
    if( _parblen(2)!=sizeof(DES_key_schedule) )
    {
        ARGERROR();
    }
    DES_key_schedule *ks2=(DES_key_schedule *)_parb(3); //kulcs
    if( _parblen(3)!=sizeof(DES_key_schedule) )
    {
        ARGERROR();
    }
    int enc=_parl(4)?DES_ENCRYPT:DES_DECRYPT; //flag: .t.=titkosít, .f.=visszafejt
    DES_cblock *output=(DES_cblock *)binaryl(sizeof(DES_cblock));
    DES_ecb2_encrypt( DESCBLOCK input, DESCBLOCK output,ks1,ks2,enc);
    _rettop();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------- 
void _clp_crypto_des_ecb3_encrypt(int argno) //Electronic Code Book
{
    CCC_PROLOG("crypto_des_ecb3_encrypt",5);
    const_DES_cblock *input=(const_DES_cblock*)_parb(1); //8 byte
    if( _parblen(1)!=8 )
    {
        ARGERROR();
    }
    DES_key_schedule *ks1=(DES_key_schedule *)_parb(2); //kulcs
    if( _parblen(2)!=sizeof(DES_key_schedule) )
    {
        ARGERROR();
    }
    DES_key_schedule *ks2=(DES_key_schedule *)_parb(3); //kulcs
    if( _parblen(3)!=sizeof(DES_key_schedule) )
    {
        ARGERROR();
    }
    DES_key_schedule *ks3=(DES_key_schedule *)_parb(4); //kulcs
    if( _parblen(4)!=sizeof(DES_key_schedule) )
    {
        ARGERROR();
    }
    int enc=_parl(5)?DES_ENCRYPT:DES_DECRYPT; //flag: .t.=titkosít, .f.=visszafejt
    DES_cblock *output=(DES_cblock *)binaryl(sizeof(DES_cblock));
    DES_ecb3_encrypt( DESCBLOCK input, DESCBLOCK output,ks1,ks2,ks3,enc);
    _rettop();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------- 
void _clp_crypto_des_ncbc_encrypt(int argno) //Cypher Block Chaining
{
    CCC_PROLOG("crypto_des_ncbc_encrypt",4);

    // 1 - input    binary
    // 2 - ks       binary
    // 3 - ivec     refbinary
    // 4 - enc      logical
    
    const unsigned char *input=(const unsigned char *)_parb(1);
    size_t length_in=_parblen(1);
    size_t length_out=LENOUT(length_in);

    DES_key_schedule *ks=(DES_key_schedule *)_parb(2); //kulcs
    if( _parblen(2)!=sizeof(DES_key_schedule) )
    {
        ARGERROR();
    }

    //ivec
    if( REFBINLEN(3)!=sizeof(DES_cblock) )
    {
        ARGERROR();
    }
    DES_cblock *ivec=(DES_cblock *)binaryl(sizeof(DES_cblock));
    memcpy((char*)ivec,REFBINPTR(3),sizeof(DES_cblock));//8 byte

    int enc=_parl(4)?DES_ENCRYPT:DES_DECRYPT; //flag: .t.=titkosít, .f.=visszafejt

    unsigned char *output=(unsigned char*)binaryl(length_out);
    DES_ncbc_encrypt(input,output,length_in,ks,ivec,enc);
    *REFVALUE(3)=*TOP2(); //ivec
    _rettop();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------- 
void _clp_crypto_des_xcbc_encrypt(int argno) //RSA's DESX
{
    CCC_PROLOG("crypto_des_xcbc_encrypt",6);

    // 1 - input    binary
    // 2 - ks       binary
    // 3 - ivec     refbinary
    // 4 - inw      binary
    // 5 - outw     binary
    // 6 - enc      logical
    
    const unsigned char *input=(const unsigned char *)_parb(1);
    size_t length_in=_parblen(1);
    size_t length_out=LENOUT(length_in);

    DES_key_schedule *ks=(DES_key_schedule *)_parb(2); //kulcs
    if( _parblen(2)!=sizeof(DES_key_schedule) )
    {
        ARGERROR();
    }

    //ivec
    if( REFBINLEN(3)!=sizeof(DES_cblock) )
    {
        ARGERROR();
    }
    DES_cblock *ivec=(DES_cblock *)binaryl(sizeof(DES_cblock));
    memcpy((char*)ivec,REFBINPTR(3),sizeof(DES_cblock));//8 byte
    
    const_DES_cblock *inw=(const_DES_cblock*)_parb(4);
    const_DES_cblock *outw=(const_DES_cblock*)_parb(5);

    int enc=_parl(6)?DES_ENCRYPT:DES_DECRYPT;

    unsigned char *output=(unsigned char*)binaryl(length_out);
    DES_xcbc_encrypt(input,output,length_in,ks,ivec,inw,outw,enc);
    *REFVALUE(3)=*TOP2(); //ivec
    _rettop();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------- 
void _clp_crypto_des_ede3_cbc_encrypt(int argno) // Triple-DES, SSL
{
    CCC_PROLOG("crypto_des_ede3_cbc_encrypt",6);

    // 1 - input    binary
    // 2 - ks1      binary
    // 3 - ks2      binary
    // 4 - ks3      binary
    // 5 - ivec     refbinary
    // 6 - enc      logical
    
    const unsigned char *input=(const unsigned char *)_parb(1);
    size_t length_in=_parblen(1);
    size_t length_out=LENOUT(length_in);

    DES_key_schedule *ks1=(DES_key_schedule *)_parb(2); //kulcs
    if( _parblen(2)!=sizeof(DES_key_schedule) )
    {
        ARGERROR();
    }

    DES_key_schedule *ks2=(DES_key_schedule *)_parb(3); //kulcs
    if( _parblen(3)!=sizeof(DES_key_schedule) )
    {
        ARGERROR();
    }

    DES_key_schedule *ks3=(DES_key_schedule *)_parb(4); //kulcs
    if( _parblen(4)!=sizeof(DES_key_schedule) )
    {
        ARGERROR();
    }

    //ivec
    if( REFBINLEN(5)!=sizeof(DES_cblock) )
    {
        ARGERROR();
    }
    DES_cblock *ivec=(DES_cblock *)binaryl(sizeof(DES_cblock));
    memcpy((char*)ivec,REFBINPTR(5),sizeof(DES_cblock));//8 byte

    int enc=_parl(6)?DES_ENCRYPT:DES_DECRYPT;

    unsigned char *output=(unsigned char*)binaryl(length_out);
    DES_ede3_cbc_encrypt(input,output,length_in,ks1,ks2,ks3,ivec,enc);

    *REFVALUE(5)=*TOP2(); //ivec
    _rettop();
    CCC_EPILOG();
}


//---------------------------------------------------------------------------- 
void _clp_crypto_des_ede2_cbc_encrypt(int argno) // Triple DES with ks3=ks1
{
    CCC_PROLOG("crypto_des_ede2_cbc_encrypt",5);

    // 1 - input    binary
    // 2 - ks1      binary
    // 3 - ks2      binary
    // 4 - ivec     refbinary
    // 5 - enc      logical
    
    const unsigned char *input=(const unsigned char *)_parb(1);
    size_t length_in=_parblen(1);
    size_t length_out=LENOUT(length_in);

    DES_key_schedule *ks1=(DES_key_schedule *)_parb(2); //kulcs
    if( _parblen(2)!=sizeof(DES_key_schedule) )
    {
        ARGERROR();
    }

    DES_key_schedule *ks2=(DES_key_schedule *)_parb(3); //kulcs
    if( _parblen(3)!=sizeof(DES_key_schedule) )
    {
        ARGERROR();
    }

    //ivec
    if( REFBINLEN(4)!=sizeof(DES_cblock) )
    {
        ARGERROR();
    }
    DES_cblock *ivec=(DES_cblock *)binaryl(sizeof(DES_cblock));
    memcpy((char*)ivec,REFBINPTR(4),sizeof(DES_cblock));//8 byte

    int enc=_parl(5)?DES_ENCRYPT:DES_DECRYPT;

    unsigned char *output=(unsigned char*)binaryl(length_out);
    DES_ede2_cbc_encrypt(input,output,length_in,ks1,ks2,ivec,enc);

    *REFVALUE(4)=*TOP2(); //ivec
    _rettop();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------- 
void _clp_crypto_des_pcbc_encrypt(int argno) //propagating CBC (Kerberos)
{
    CCC_PROLOG("crypto_des_pcbc_encrypt",4); //mint az ncbc

    // 1 - input    binary
    // 2 - ks       binary
    // 3 - ivec     refbinary
    // 4 - enc      logical
    
    const unsigned char *input=(const unsigned char *)_parb(1);
    size_t length_in=_parblen(1);
    size_t length_out=LENOUT(length_in);

    DES_key_schedule *ks=(DES_key_schedule *)_parb(2); //kulcs
    if( _parblen(2)!=sizeof(DES_key_schedule) )
    {
        ARGERROR();
    }

    if( REFBINLEN(3)!=sizeof(DES_cblock) )
    {
        ARGERROR();
    }
    DES_cblock *ivec=(DES_cblock *)binaryl(sizeof(DES_cblock));
    memcpy((char*)ivec,REFBINPTR(3),sizeof(DES_cblock));//8 byte

    int enc=_parl(4)?DES_ENCRYPT:DES_DECRYPT; //flag: .t.=titkosít, .f.=visszafejt

    unsigned char *output=(unsigned char*)binaryl(length_out);
    DES_pcbc_encrypt(input,output,length_in,ks,ivec,enc);
    *REFVALUE(3)=*TOP2(); //ivec
    _rettop();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------- 
void _clp_crypto_des_cfb_encrypt(int argno) //Cypher FeedBack
{
    CCC_PROLOG("crypto_des_cfb_encrypt",5);

    // 1 - input    binary
    // 2 - numbit   number
    // 3 - ks       binary
    // 4 - ivec     refbinary
    // 5 - enc      logical
    
    const unsigned char *input=(const unsigned char *)_parb(1);
    size_t length=_parblen(1);

    int numbit=_parni(2);

    DES_key_schedule *ks=(DES_key_schedule *)_parb(3); //kulcs
    if( _parblen(3)!=sizeof(DES_key_schedule) )
    {
        ARGERROR();
    }

    if( REFBINLEN(4)!=sizeof(DES_cblock) )
    {
        ARGERROR();
    }
    DES_cblock *ivec=(DES_cblock *)binaryl(sizeof(DES_cblock));
    memcpy((char*)ivec,REFBINPTR(4),sizeof(DES_cblock));//8 byte

    int enc=_parl(5)?DES_ENCRYPT:DES_DECRYPT; //flag: .t.=titkosít, .f.=visszafejt

    unsigned char *output=(unsigned char*)binaryl(length);
    DES_cfb_encrypt(input,output,numbit,length,ks,ivec,enc);
    *REFVALUE(4)=*TOP2(); //ivec
    _rettop();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------- 
void _clp_crypto_des_cfb64_encrypt(int argno) //CFB with 64bit feedback
{
    CCC_PROLOG("crypto_des_cfb64_encrypt",5);

    // 1 - input    binary
    // 2 - ks       binary
    // 3 - ivec     refbinary
    // 4 - num      refnumber
    // 5 - enc      logical
    
    const unsigned char *input=(const unsigned char *)_parb(1);
    size_t length=_parblen(1);

    DES_key_schedule *ks=(DES_key_schedule *)_parb(2); //kulcs
    if( _parblen(2)!=sizeof(DES_key_schedule) )
    {
        ARGERROR();
    }

    //ivec
    if( REFBINLEN(3)!=sizeof(DES_cblock) )
    {
        ARGERROR();
    }
    DES_cblock *ivec=(DES_cblock *)binaryl(sizeof(DES_cblock));
    memcpy((char*)ivec,REFBINPTR(3),sizeof(DES_cblock));//8 byte

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

    int enc=_parl(5)?DES_ENCRYPT:DES_DECRYPT; //flag: .t.=titkosít, .f.=visszafejt

    unsigned char *output=(unsigned char*)binaryl(length);
    DES_cfb64_encrypt(input,output,length,ks,ivec,&num,enc);

    *REFVALUE(3)=*TOP2(); //ivec
    valnum->type=TYPE_NUMBER;
    valnum->data.number=(double)num;
    _rettop();

    CCC_EPILOG();
}

//---------------------------------------------------------------------------- 
void _clp_crypto_des_ede3_cfb64_encrypt(int argno) //CFB Triple DES, 64bit feedback
{
    CCC_PROLOG("crypto_des_ede3_cfb64_encrypt",7);

    // 1 - input    binary
    // 2 - ks1      binary
    // 3 - ks2      binary
    // 4 - ks3      binary
    // 5 - ivec     refbinary
    // 6 - num      refnumber
    // 7 - enc      logical
    
    const unsigned char *input=(const unsigned char *)_parb(1);
    size_t length=_parblen(1);

    DES_key_schedule *ks1=(DES_key_schedule *)_parb(2); //kulcs
    if( _parblen(2)!=sizeof(DES_key_schedule) )
    {
        ARGERROR();
    }
    DES_key_schedule *ks2=(DES_key_schedule *)_parb(3); //kulcs
    if( _parblen(3)!=sizeof(DES_key_schedule) )
    {
        ARGERROR();
    }
    DES_key_schedule *ks3=(DES_key_schedule *)_parb(4); //kulcs
    if( _parblen(4)!=sizeof(DES_key_schedule) )
    {
        ARGERROR();
    }

    //ivec
    if( REFBINLEN(5)!=sizeof(DES_cblock) )
    {
        ARGERROR();
    }
    DES_cblock *ivec=(DES_cblock *)binaryl(sizeof(DES_cblock));
    memcpy((char*)ivec,REFBINPTR(5),sizeof(DES_cblock));//8 byte

    //num    
    int num=0;
    if( !ISREF(6) )
    {
        ARGERROR();
    }
    VALUE *valnum=REFVALUE(6);
    if( valnum->type==TYPE_NUMBER )
    {
        num=D2INT(valnum->data.number);
    }

    int enc=_parl(7)?DES_ENCRYPT:DES_DECRYPT; //flag: .t.=titkosít, .f.=visszafejt

    unsigned char *output=(unsigned char*)binaryl(length);
    DES_ede3_cfb64_encrypt(input,output,length,ks1,ks2,ks3,ivec,&num,enc);

    *REFVALUE(5)=*TOP2(); //ivec
    valnum->type=TYPE_NUMBER;
    valnum->data.number=(double)num;
    _rettop();

    CCC_EPILOG();
}

//---------------------------------------------------------------------------- 
void _clp_crypto_des_ofb64_encrypt(int argno) //OFB with 64bit feedback
{
    CCC_PROLOG("crypto_des_ofb64_encrypt",4);

    // 1 - input    binary
    // 2 - ks       binary
    // 3 - ivec     refbinary
    // 4 - num      refnumber
    
    const unsigned char *input=(const unsigned char *)_parb(1);
    size_t length=_parblen(1);

    DES_key_schedule *ks=(DES_key_schedule *)_parb(2); //kulcs
    if( _parblen(2)!=sizeof(DES_key_schedule) )
    {
        ARGERROR();
    }

    //ivec
    if( REFBINLEN(3)!=sizeof(DES_cblock) )
    {
        ARGERROR();
    }
    DES_cblock *ivec=(DES_cblock *)binaryl(sizeof(DES_cblock));
    memcpy((char*)ivec,REFBINPTR(3),sizeof(DES_cblock));//8 byte

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

    unsigned char *output=(unsigned char*)binaryl(length);
    DES_ofb64_encrypt(input,output,length,ks,ivec,&num);

    *REFVALUE(3)=*TOP2(); //ivec
    valnum->type=TYPE_NUMBER;
    valnum->data.number=(double)num;
    _rettop();

    CCC_EPILOG();
}

#ifdef NOT_DEFINED
  DES_ofb64_encrypt() is the same as DES_cfb64_encrypt() 
  using Output Feed Back mode.

  DES_ofb64_encrypt() implements OFB mode of DES with 64bit feedback. 
  This routine will allow you to encrypt an arbitrary number of bytes, 
  no 8 byte padding. Each call to this routine will encrypt the input bytes 
  to output and then update ivec and num. num contains 'how far' we are 
  though ivec.
#endif

//---------------------------------------------------------------------------- 
void _clp_crypto_des_ede3_ofb64_encrypt(int argno) //OFB Triple DES, 64bit feedback
{
    CCC_PROLOG("crypto_des_ede3_ofb64_encrypt",6);

    // 1 - input    binary
    // 2 - ks1      binary
    // 3 - ks2      binary
    // 4 - ks3      binary
    // 5 - ivec     refbinary
    // 6 - num      refnumber
    
    const unsigned char *input=(const unsigned char *)_parb(1);
    size_t length=_parblen(1);

    DES_key_schedule *ks1=(DES_key_schedule *)_parb(2); //kulcs
    if( _parblen(2)!=sizeof(DES_key_schedule) )
    {
        ARGERROR();
    }
    DES_key_schedule *ks2=(DES_key_schedule *)_parb(3); //kulcs
    if( _parblen(3)!=sizeof(DES_key_schedule) )
    {
        ARGERROR();
    }
    DES_key_schedule *ks3=(DES_key_schedule *)_parb(4); //kulcs
    if( _parblen(4)!=sizeof(DES_key_schedule) )
    {
        ARGERROR();
    }

    //ivec
    if( REFBINLEN(5)!=sizeof(DES_cblock) )
    {
        ARGERROR();
    }
    DES_cblock *ivec=(DES_cblock *)binaryl(sizeof(DES_cblock));
    memcpy((char*)ivec,REFBINPTR(5),sizeof(DES_cblock));//8 byte

    //num    
    int num=0;
    if( !ISREF(6) )
    {
        ARGERROR();
    }
    VALUE *valnum=REFVALUE(6);
    if( valnum->type==TYPE_NUMBER )
    {
        num=D2INT(valnum->data.number);
    }

    unsigned char *output=(unsigned char*)binaryl(length);
    DES_ede3_ofb64_encrypt(input,output,length,ks1,ks2,ks3,ivec,&num);

    *REFVALUE(5)=*TOP2(); //ivec
    valnum->type=TYPE_NUMBER;
    valnum->data.number=(double)num;
    _rettop();

    CCC_EPILOG();
}

//---------------------------------------------------------------------------- 

