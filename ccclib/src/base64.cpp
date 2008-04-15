
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

#include <cccapi.h>

//---------------------------------------------------------------------------
void _clp_base64_encode(int argno)
{
    static const char*abc="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

    CCC_PROLOG("base64_encode",1);
    
    str2bin(base);

    char *bin = _parb(1);
    int   len = _parblen(1); 
    char *asc = binaryl( ((len+2)/3)*4 );

    // 3x8 bitet 4x6 bitbe kódol,
    // azaz minden 3 byte-ból 4 byte lesz

    for( int i=0, index=0; i<len; i+=3, index+=4 ) 
    {
        int quad = 0;
        int trip = 0;

        int val = (0xFF&(int)bin[i]);
        val <<= 8;

        if( (i+1)<len ) 
        {
            val |= (0xFF&(int)bin[i+1]);
            trip = 1;
        }
        val <<= 8;

        if( (i+2)<len ) 
        {
            val |= (0xFF&(int)bin[i+2]);
            quad =1; //true
        }

        asc[index+3] = abc[quad?(val&0x3F):64];
        val >>= 6;
        asc[index+2] = abc[trip?(val&0x3F):64];
        val >>= 6;
        asc[index+1] = abc[val&0x3F];
        val >>= 6;
        asc[index+0] = abc[val&0x3F];
    }
    _rettop();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp_base64_decode(int argno) 
{
    static signed char codes[256];
    static int initialize=0;

    if( !initialize )
    {
        initialize=1;    
        
        int i;
        for ( i=0; i<256; i++) codes[i] = -1;
        for ( i='A'; i <= 'Z'; i++) codes[i] = i-'A';
        for ( i='a'; i <= 'z'; i++) codes[i] = 26+i-'a';
        for ( i='0'; i <= '9'; i++) codes[i] = 52+i-'0';
        codes[(int)'+'] = 62;
        codes[(int)'/'] = 63;
    }

    CCC_PROLOG("base64_decode",1);

    str2bin(base);

    char *asc = _parb(1);
    int  alen = _parblen(1); 
 
    int tlen=alen;
    int ix;
    
    for( ix=0; ix<alen; ix++ )
    {
        if( codes[(int)asc[ix]]<0 )
        {
            --tlen; //ignore non-valid chars and padding
        }
    }

    // calculate required length
    // 3 bytes for every 4 valid base64 chars
    // plus 2 bytes if there are 3 extra base64 chars,
    // or plus 1 byte if there are 2 extra.

    int blen=(tlen/4)*3;
    if( (tlen%4)==3 ) blen += 2;
    if( (tlen%4)==2 ) blen += 1;

    char *bin = binaryl( blen );
 
    int shift = 0;   
    int accum = 0;   
    int index = 0;

    for( ix=0; ix<alen; ix++)
    {
        int value=codes[(int)asc[ix]];

        if( value>=0 ) // skip over non-code
        {
            accum <<= 6;  
            shift += 6;      
            accum |= value;     
            if( shift>=8 )     
            {
                shift -= 8;    
                bin[index++]=(accum>>shift)&0xff; 
            }
        }
    }
    _rettop();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------

