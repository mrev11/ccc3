
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
#include <utf8conv.h>

#define H1 0x80  //1000 0000
#define H2 0xc0  //1100 0000

#define CONT(x)  (((x)&H2)==H1) //continuing char


//----------------------------------------------------------------------------
void _clp_utf8len(int argno)
{
    CCC_PROLOG("utf8len",1);
    char *p=_parb(1);
    unsigned blen=_parblen(1);
    unsigned clen=0;
    unsigned i;
    for( i=0; i<blen; i++ )
    {
        if( !CONT(*(p+i)) ) //not continuing
        {
            clen++;
        }
    }
    _retni(clen);
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp_utf8left(int argno)
{
    CCC_PROLOG("utf8left",2);
    char *p=_parb(1);
    unsigned blen=_parblen(1);
    int clen=_parni(2);

    unsigned i;
    unsigned c=0;
    for( i=0; i<blen && 0<clen; i++ )
    {
        c=*(p+i);
        if( !CONT(c) ) //not continuing
        {
            clen--;
        }
    }
    if( c>0x80 )
    {
        for( ; i<blen; i++ )
        {
            c=*(p+i);
            if( !CONT(c) ) 
            {
                break;
            }
        }
    }
    _retblen(p,i);
    CCC_EPILOG();
}


//----------------------------------------------------------------------------
void _clp_utf8right(int argno)
{
    CCC_PROLOG("utf8right",2);
    char *p=_parb(1);
    unsigned blen=_parblen(1);
    int clen=_parni(2);

    unsigned i;
    for( i=blen; 0<i && 0<clen; i-- )
    {
        if( !CONT(*(p+i-1)) )
        {
            clen--;
        }
    }
    _retblen(p+i,blen-i);
    CCC_EPILOG();
}


//----------------------------------------------------------------------------
void _clp_utf8substr(int argno)
{
    CCC_PROLOG("utf8substr",3);
    char *p=_parb(1);
    unsigned blen=_parblen(1);
    int cbeg=_parni(2);

    unsigned i=0;
    unsigned c=0;
    
    if( cbeg>0 )
    {
        for( i=0; i<blen && 0<cbeg-1; i++ )
        {
            c=*(p+i);
            if( !CONT(c) )
            {
                cbeg--;
            }
        }
        if( c>0x80 )
        {
            for( ; i<blen; i++ )
            {
                c=*(p+i);
                if( !CONT(c) ) 
                {
                    break;
                }
            }
        }
    }
    else if( cbeg<0 )
    {
        for( i=blen; 0<i && cbeg<0; i-- )
        {
            c=*(p+i-1);
            if( !CONT(c) )
            {
                cbeg++;
            }
        }
    }
    
    if( _parni(2)==0 )
    {
        _retb("");
    }
    else if( ISNIL(3) )
    {
        _retblen(p+i,blen-i);
    }
    else
    {
        unsigned pbeg=i;
        int clen=_parni(3);
        c=0;

        for( ; (i<blen)&&(0<clen); i++ )
        {
            c=*(p+i);
            if( !CONT(c) )
            {
                clen--;
            }
        }

        if( c>0x80 )
        {
            for( ; i<blen; i++ )
            {
                c=*(p+i);
                if( !CONT(c) )
                {
                    break;
                }
            }
        }
        _retblen(p+pbeg,i-pbeg);
    }

    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp_utf8seq(int argno)
{
    // UCS4 kod -> UTF-8 bytesorozat 
    // a chr() fuggveny utf8 megfeleloje

    CCC_PROLOG("utf8seq",1);
    unsigned code=_parnu(1);
    char seq[8];
    unsigned len=ucs_to_utf8(code,seq);
    _retblen(seq,len);
    CCC_EPILOG();
}


//----------------------------------------------------------------------------
void _clp_utf8ucs(int argno)
{
    // UTF-8 bytesorozat -> UCS4 kod 
    // az asc() fuggveny utf8 megfeleloje
    // ha a bytesorozat ervenytelen az eredmeny 0

    CCC_PROLOG("utf8ucs",1);
    unsigned code;
    utf8_to_ucs(_parb(1),&code);
    _retni(code);
    CCC_EPILOG();
}


//----------------------------------------------------------------------------
void _clp_ucsarr_to_utf8(int argno)
{
    // UCS4 kodokat (szamokat) tartalmazo 
    // arraybol UTF-8 kodolasu string

    CCC_PROLOG("ucsarr_to_utf8",1);
    unsigned alen=_paralen(1);

    unsigned inc=1024;
    unsigned size=inc;
    char *utf8=(char*)malloc(size);
    unsigned blen=0;

    unsigned i;
    for( i=0; i<alen; i++ )
    {
        if( _parax(1,i)->type!=TYPE_NUMBER )
        {
            ARGERROR();
        }
        if( blen+8<=size )
        {
            size+=inc;
            utf8=(char*)realloc(utf8,size);
        }
        char seq[8];
        unsigned code=D2UINT(_parax(1,i)->data.number);
        unsigned lseq=ucs_to_utf8(code,seq);
        memmove(utf8+blen,seq,lseq);
        blen+=lseq;
    }
    _retblen(utf8,blen);
    free(utf8);
    CCC_EPILOG();
}


//----------------------------------------------------------------------------
void _clp_utf8_to_ucsarr(int argno)
{
    // UTF-8 kodolasu stringbol UCS4 
    // kodokat (szamokat) tartalmazo array

    CCC_PROLOG("utf8_to_ucsarr",1);
    char* utf8=_parb(1);
    unsigned blen=_parblen(1);
    unsigned len=0;
    
    array(0);
    while( len<blen )
    {
        unsigned code;
        unsigned lseq=utf8_to_ucs(utf8+len,&code);
        len+=lseq;
        if( code<=0 )
        {
            code='?';
        }
        dup();
        number(code);
        _clp_aadd(2);
        pop();
    }
    _rettop();
    CCC_EPILOG();
}


//----------------------------------------------------------------------------
void _clp_utf8valid(int argno) // .t., ha a bemenet valid UTF-8 kodolasu
{
    CCC_PROLOG("utf8valid",1);
    char* utf8=_parb(1);
    unsigned blen=_parblen(1);
    unsigned len=0;
    int result=1;
        
    while( result && len<blen )
    {
        unsigned code;
        unsigned lseq=utf8_to_ucs(utf8+len,&code);
        if( (code<=0) && (utf8[len]!=0) )
        {
            result=0;
        }
        len+=lseq;
    }
    _retl(result);
    CCC_EPILOG();
}


#ifdef _CCC2_
//----------------------------------------------------------------------------
void _clp_wstr_to_utf8(int argno)
{
    // UCS4 kodolasu stringbol
    // UTF-8 kodolasu string

    CCC_PROLOG("wstr_to_utf8",1);
    wchar_t *wstr=(wchar_t*)_parc(1);
    unsigned wlen=_parclen(1)/sizeof(wchar_t);

    unsigned inc=1024;
    unsigned size=inc;
    char *utf8=(char*)malloc(size);
    unsigned blen=0;

    unsigned i;
    for( i=0; i<wlen; i++ )
    {
        if( blen+8<=size )
        {
            size+=inc;
            utf8=(char*)realloc(utf8,size);
        }
        char seq[8];
        unsigned lseq=ucs_to_utf8(wstr[i],seq);
        memmove(utf8+blen,seq,lseq);
        blen+=lseq;
    }
    _retclen(utf8,blen);
    free(utf8);
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp_utf8_to_wstr(int argno)
{
    // UTF-8 kodolasu stringbol
    // UCS4 kodokat tartalmazo string

    CCC_PROLOG("utf8_to_wstr",1);
    char *utf8=_parc(1);
    unsigned blen=_parclen(1);
    unsigned len=0;

    unsigned inc=256;
    unsigned size=inc;
    unsigned wlen=0;
    wchar_t *wstr=(wchar_t*)malloc(size*sizeof(wchar_t));
    
    while( len<blen )
    {
        unsigned code;
        unsigned lseq=utf8_to_ucs(utf8+len,&code);
        len+=lseq;
        if( code<=0 )
        {
            code='?';
        }
        if( wlen>=size )
        {
            size+=inc;
            wstr=(wchar_t*)realloc(wstr,size*sizeof(wchar_t));
        }
        *(wstr+wlen++)=code;
    }
    _retclen((char*)wstr,wlen*sizeof(wchar_t));
    free(wstr);
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
#endif
