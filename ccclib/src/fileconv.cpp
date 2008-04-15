
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

#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <cccapi.h>
#include <fileconv.ch>

int DOSCONV=0; //DOSCONV_DEFAULT;


#ifdef _UNIX_
#define DIRSEP     '/'
#define DIRSEPREV  '\\'
#else
#define DIRSEP     '\\'
#define DIRSEPREV  '/'
#endif


//----------------------------------------------------------------------
static char *convert(char *fspec, char *convbuf) //reentráns változat
{
    // convbuf-ot a hívó allokálja,
    // és legalább olyan hosszú, mint fspec,
    // visszatérés: convbuf
    
    int flag_fnamertrim  = DOSCONV & DOSCONV_FNAMERTRIM;
    int flag_bs2slash    = DOSCONV & DOSCONV_BS2SLASH;
    int flag_fname2lower = DOSCONV & DOSCONV_FNAME2LOWER;
    int flag_path2lower  = DOSCONV & DOSCONV_PATH2LOWER;

    int len=strlen(fspec);

    // jobbról trimeljük

    while( flag_fnamertrim && len>0 && fspec[len-1]==' ' )
    {
        len--;
    }

    int i,c;

    // megkeressük, hol kezdődik a filé neve
 
    for( i=len-1; i>=0; i-- )
    { 
        c=fspec[i];
        if( (c==DIRSEP) || flag_bs2slash && (c==DIRSEPREV) )
        {
            break;
        }
    }
    int namestart=i+1;

    // konvertálunk
 
    for( i=0; i<len; i++ )
    {
        c=fspec[i];

        if( flag_bs2slash && c==DIRSEPREV )
        {
            c=DIRSEP;
        }
        else if( flag_path2lower && i<namestart )
        {
            c=tolower(c);
        }
        else if( flag_fname2lower && i>=namestart )
        {
            c=tolower(c);
        }

        convbuf[i]=c;
    }

    convbuf[i]=0x00;
    return convbuf;
}

//----------------------------------------------------------------------
void _clp_convertfspec2nativeformat(int argno) //reentráns
{
    CCC_PROLOG("convertfspec2nativeformat",1);
    str2bin(base);
    char *fspec=_parb(1);
    if( DOSCONV & FDOSCONV_ALL  )
    {
        char *convbuf=binaryl(_parblen(1)+1);
        convert(fspec,convbuf);
        binaryn(convbuf); //hossz egyeztetés!
    }
    _rettop();
    CCC_EPILOG();
}

//----------------------------------------------------------------------
void convertfspec2nativeformat(VALUE*v) //reentráns
{
    push_symbol(v);
    _clp_convertfspec2nativeformat(1);
    *v=*TOP();
    POP();
}

//----------------------------------------------------------------------
void _clp_reset_dosconv(int argno)
// a DOSCONV konverziót szabályozó flageket a default-ra állítja
{
    DOSCONV=DOSCONV_DEFAULT;
    stack-=argno;
    PUSH(&NIL);
}

//----------------------------------------------------------------------
void _clp_get_dosconv(int argno)
// megadja a DOSCONV konverziót szabályozó flageket
{
    stack-=argno;
    number(DOSCONV);
}

//----------------------------------------------------------------------
void _clp_set_dosconv(int argno)
// beállítja a DOSCONV konverziót szabályozó flageket
{
    CCC_PROLOG("set_dosconv",1);
    DOSCONV=_parni(1);
    _ret();
    CCC_EPILOG();
}

//----------------------------------------------------------------------

