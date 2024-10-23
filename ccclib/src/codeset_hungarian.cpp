
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

#include <inthash.h>
#include <cccapi.h>


static int asc[]={97,101,105,111,111,111,117,117,117,97,65,69,73,79,79,79,85,85,85,65,0};
static int uni[]={225,233,237,243,246,337,250,252,369,228,193,201,205,211,214,336,218,220,368,196,0};
static int lat[]={225,233,237,243,246,245,250,252,251,228,193,201,205,211,214,213,218,220,219,196,0};


//----------------------------------------------------------------------------------------
void _clp_codeset_hungarian_accented_to_ascii(int argno) // CCC2 es CCC3
{
    #ifdef _CCC3_
        static inthash hash(256,uni,asc);
    #else
        static inthash hash(256,lat,asc);
    #endif

    CCC_PROLOG("codeset_hungarian_accented_to_ascii",1);
    CHAR *inp=_parc(1);
    int  len=_parclen(1);
    CHAR *out=stringl(len); //top
    for( int i=0; i<len; i++ )
    {
        out[i]=hash.getx(inp[i]);
    }
    _rettop();
    CCC_EPILOG();
}


//----------------------------------------------------------------------------------------
void _clp_codeset_hungarian_unicode_to_latin2(int argno) //csak CCC3 
{
    CCC_PROLOG("codeset_hungarian_unicode_to_latin2",1);
    #ifdef _CCC3_
        static inthash hash(256,uni,lat);
        CHAR *inp=_parc(1);
        int  len=_parclen(1);
        char *out=binaryl(len); //top
        for( int i=0; i<len; i++ )
        {
            out[i]=hash.getx(inp[i]);
        }
    #endif
    _rettop();
    CCC_EPILOG();
}


//----------------------------------------------------------------------------------------
void _clp_codeset_hungarian_latin2_to_unicode(int argno) //csak CCC3 
{
    CCC_PROLOG("codeset_hungarian_latin2_to_unicode",1);
    #ifdef _CCC3_
        static inthash hash(256,lat,uni);
        char *inp=_parb(1);
        int  len=_parblen(1);
        CHAR *out=stringl(len); //top
        for( int i=0; i<len; i++ )
        {
            out[i]=hash.getx(inp[i]);
        }
    #endif
    _rettop();
    CCC_EPILOG();
}

//----------------------------------------------------------------------------------------

