
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
#include <string.h>
#include <cccapi.h>

extern void _clp_bin(int);


#define BITS_PER_BYTE           8
#define BITS_PER_B32_BLOCK      5

static char b32_alphabet[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";

DEFINE_METHOD(args);
DEFINE_METHOD(description);
DEFINE_METHOD(operation);

//----------------------------------------------------------------------------------------
void _clp_base32_encode(int argno)
{
    // plain 5 byte => encoded 8 byte

    CCC_PROLOG("base32_encode",1);
    str2bin(base);
    char *data=_parb(1);
    int len=_parblen(1);

    int total_bits=8*len;
    int num_of_equals=0;
    switch( total_bits%40 )
    {
        case 8:  num_of_equals = 6; break;
        case 16: num_of_equals = 4; break;
        case 24: num_of_equals = 3; break;
        case 32: num_of_equals = 1; break;
    }
    int output_length=(len*8+4)/5;
    char *encoded_data=binaryl(output_length+num_of_equals);

    for( int i=0, j=0; i<len; i+=5 )
    {
        uint64_t quintuple=0;
        for( int k=0; k<5; k++ )
        {
            quintuple=(quintuple<<8) | (i+k<len?data[i+k]:0);
        }
        for( int shift=35; shift>=0; shift-=5)
        {
            encoded_data[j++]=(char)b32_alphabet[(quintuple>>shift) & 0x1f];
        }
    }
    for( int i=0; i<num_of_equals; i++)
    {
        encoded_data[output_length+i]='=';
    }
    _rettop();
    CCC_EPILOG();
}

//----------------------------------------------------------------------------------------
void _clp_base32_decode(int argno)
{
    CCC_PROLOG("base32_decode",1);
    str2bin(base);
    char *data=_parb(1);
    int len=_parblen(1);

    int output_length=(int)((len+1.6+1)/1.6); // round up
    char *decoded_data=binaryl(output_length); // temporary
    int decoded_length=0;

    char mask, current_byte=0;
    int bits_left=8;
    for( int i=0; i<len; i++)
    {
        int chidx;

        char *p=strchr( b32_alphabet,data[i] );
        if( p )
        {
            chidx=p-b32_alphabet;
        }
        else if( strchr("= \n\r",data[i]) )
        {
            continue;
        }
        else
        {
            _clp_invalidformaterrornew(0);
 
            DUP();
            string(CHRLIT("base32_decode"));
            _o_method_operation.eval(2);
            POP();

            DUP();
            string(CHRLIT("character not in base32 alphabet"));
            _o_method_description.eval(2);
            POP();
   
            DUP();
            number(i+1);
            number(data[i]);_clp_bin(1);
            array(2);
            _o_method_args.eval(2);
            POP();

            _clp_break(1);
            continue;
        }

        if( bits_left>BITS_PER_B32_BLOCK )
        {
            mask=(uint8_t)chidx << (bits_left-BITS_PER_B32_BLOCK);
            current_byte |= mask;
            bits_left -= BITS_PER_B32_BLOCK;
        }
        else
        {
            mask=(uint8_t)chidx >> (BITS_PER_B32_BLOCK - bits_left);
            current_byte |= mask;
            decoded_data[decoded_length++]=current_byte;
            current_byte=(uint8_t)(chidx << (BITS_PER_BYTE-BITS_PER_B32_BLOCK+bits_left));
            bits_left+=BITS_PER_BYTE-BITS_PER_B32_BLOCK;
        }
    }
    binarys(decoded_data,decoded_length);
    _rettop();
    CCC_EPILOG();
}

//----------------------------------------------------------------------------------------

