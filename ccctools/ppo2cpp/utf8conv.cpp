
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <utf8conv.h>

#define H1 0x80  //1000 0000
#define H2 0xc0  //1100 0000
#define H3 0xe0  //1110 0000
#define H4 0xf0  //1111 0000
#define H5 0xf8  //1111 1000
#define H6 0xfc  //1111 1100
#define H7 0xfe  //1111 1110

#define L1 0x01  //0000 0001
#define L2 0x03  //0000 0011
#define L3 0x07  //0000 0111
#define L4 0x0f  //0000 1111
#define L5 0x1f  //0001 1111
#define L6 0x3f  //0011 1111
#define L7 0x7f  //0111 1111

#define CONT(x)  (((x)&H2)==H1) //continuing char
#define SEQ2(x)  (((x)&H3)==H2) //2 byte sequence
#define SEQ3(x)  (((x)&H4)==H3) //3 byte sequence
#define SEQ4(x)  (((x)&H5)==H4) //4 byte sequence
#define SEQ5(x)  (((x)&H6)==H5) //5 byte sequence
#define SEQ6(x)  (((x)&H7)==H6) //6 byte sequence

#define LOW1(x)  ((x)&L1)
#define LOW2(x)  ((x)&L2)
#define LOW3(x)  ((x)&L3)
#define LOW4(x)  ((x)&L4)
#define LOW5(x)  ((x)&L5)
#define LOW6(x)  ((x)&L6)


//----------------------------------------------------------------------------
unsigned utf8_to_ucs(const char *utf8, unsigned *ucs)
{
    // egy UTF-8 sorozattal kodolt karaktert konvertal UCS4-re
    // ha a bytesorozat ervenytelen akkor az eredmeny 0
    // visszaadja a bytesorozatbol elhasznalt byteok szamat

    unsigned code=0;
    unsigned c=*utf8;

    if( c<128 )
    {
        *ucs=(unsigned)c;
        return 1;
    }
    else
    {
        unsigned seq=0;

             if( SEQ2(c) ){ seq=2; code=LOW5(c); }
        else if( SEQ3(c) ){ seq=3; code=LOW4(c); }
        else if( SEQ4(c) ){ seq=4; code=LOW3(c); }
        else if( SEQ5(c) ){ seq=5; code=LOW2(c); }
        else if( SEQ6(c) ){ seq=6; code=LOW1(c); }
        else if( 0xfe==c ){ seq=6; code=2;       }  //extension
        else if( 0xff==c ){ seq=6; code=3;       }  //extension
    
        unsigned i;
        for( i=1; i<seq; i++ )
        {
            unsigned x=0;
            code=code<<6;
            if( !CONT(x=*(utf8+i)) )
            {
                *ucs=0;
                return i;
            }
            else
            {
                code|=LOW6(x);
            }
            //printf(" [%d %x]",i,code);
        }
        *ucs=code;
        return i;
    }
}

//----------------------------------------------------------------------------
unsigned ucs_to_utf8(unsigned ucs, char*utf8)
{
    // egy karaktert konvertal UCS4 kodrol UTF-8 bytesorozatra
    // a bytesorozat max 8 hosszu (ennyi helyet kell foglalni)
    // visszaadja a bytesorozat hosszat

    unsigned code=ucs&0xffffffff; //32 bit
    if( code<128 )
    {
        utf8[0]=(char)code;
        utf8[1]=(char)0;
        return 1;
    }
    else
    {
        unsigned i=0;
        unsigned char hdr=0;
        unsigned char seq[8];
        #define SEQ seq[7-i]
        SEQ=0;
        while( code || ((hdr>>1) & H6 & SEQ) )
        {
            i++;
            SEQ=H1|LOW6(code);
            hdr=H1|(hdr>>1);
            code=code>>6;
            //printf(" [%d %x %x %x] ",i,SEQ,hdr,code);
        }
        SEQ|=hdr;
        memmove(utf8,&SEQ,i+1);
        return i;
    }
}


//----------------------------------------------------------------------------
char *wchar_to_utf8(wchar_t const *wstr, unsigned wlen, unsigned *reslen)
{
    //bemenet: wstr wide karaktertomb, wlen a tomb hossza
    //vissza : utf8 kodolasu bytearray (a vegen 0)
    //kimenet: reslen a bytarray hossza 
    //felhasznalas utan a pointert fel kell szabaditani (free)


    // 2021-12-08 inkompatibilis javitas
    // if( wlen==0 )
    // {
    //     wlen=wcslen(wstr);
    // }
    //
    // Ez rossz, mert nem kulonbozteti meg
    // a 0 hosszu stringet az ismeretelen hosszu stringtol.
    // A wlen<0 jelzes sem mukodik, mert blen unsigned.
    // A hivo kodban kell kiszamolni a string hosszat.


    unsigned inc=1024;
    unsigned size=inc+wlen*2;

    char *utf8=(char*)malloc(size);
    unsigned blen=0;
    unsigned i;
    for( i=0; i<wlen; i++ )
    {
        if( (blen+8)>=size )
        {
            size+=inc;
            utf8=(char*)realloc(utf8,size);
        }
        blen+=ucs_to_utf8(wstr[i],utf8+blen);
    }
    *(utf8+blen)=(char)0;

    if( reslen )
    {
        *reslen=blen;
    }
    return utf8;
}


//----------------------------------------------------------------------------
wchar_t *utf8_to_wchar(char const *utf8, unsigned blen, unsigned *reslen)
{
    //bemenet: utf8 kodolasu blen hosszu bytearray
    //vissza : wide karaktereket tartalmazo string (a vegen 0)
    //kimenet: reslen a string hossza
    //felhasznalas utan a pointert fel kell szabaditani (free)

    // 2021-12-08 inkompatibilis javitas
    // if( blen==0 )
    // {
    //     blen=strlen(utf8);
    // }
    //
    // Ez rossz, mert nem kulonbozteti meg
    // a 0 hosszu stringet az ismeretelen hosszu stringtol.
    // A blen<0 jelzes sem mukodik, mert blen unsigned.
    // A hivo kodban kell kiszamolni a string hosszat.


    unsigned inc=1024;
    unsigned size=blen;

    unsigned len=0;
    unsigned wlen=0;
    wchar_t *wstr=(wchar_t*)malloc((size+1)*sizeof(wchar_t));
    
    while( len<blen )
    {
        unsigned code;
        unsigned lseq=utf8_to_ucs(utf8+len,&code);
        if( code<=0  && (0!=utf8[len]) )
        {
            code='?';
            //printf("[%d %x]",lseq,utf8[len]);
        }
        if( wlen>=size )
        {
            size+=inc;
            wstr=(wchar_t*)realloc(wstr,size*sizeof(wchar_t));
        }
        *(wstr+wlen++)=code;
        len+=lseq;
    }
    *(wstr+wlen)=(char)0;

    if( reslen )
    {
        *reslen=wlen;
    }
    return wstr;
}


//----------------------------------------------------------------------------

