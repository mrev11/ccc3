
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
#include <cccapi.h>

DEFINE_METHOD(operation);
DEFINE_METHOD(description);
DEFINE_METHOD(subsystem);
DEFINE_METHOD(subcode);

extern void _clp_apperrornew(int);


// ha ez definialva van, akkor Windowson 
// a statkus konyvtar hivasait forditja
// #define PCRE2_STATIC


// a pcre2 fuggvenyeknek harom valtozata van:
//  pcre2_match_8
//  pcre2_match_16
//  pcre2_match_32
// (3 kulon lib: pcre2-8, pcre2-16, pcre2-32)
//
// ha PCRE2_CODE_UNIT_WIDTH==0, akkor a kodban
// minden fuggvenyhivasban a tenyleges meretnek
// megfelelo valtozatot kell hasznalni
//
// ha PCRE2_CODE_UNIT_WIDTH==8, akkor a kodban
// a meret nelkuli fuggvenynevek prerocesszalodnak
// a megadott valtozatra: pcre2_match -> pcre2_match_8

#ifdef WINDOWS 
  #define PCRE2_CODE_UNIT_WIDTH  16
#else
  #define PCRE2_CODE_UNIT_WIDTH  32
#endif

// X tipusnal
//    kiirjuk a fuggvenyek _8 postfixet 
//
// C tipusnal 
//    a postfix nelkuli alakot hasznaljuk
//    Windows : pcre2_match -> pcre2_match_16, mert sizeof(wchar_t)==16
//    Linux   : pcre2_match -> pcre2_match_32, mert sizeof(wchar_t)==32


#include <stdint.h> //2019-05-22 korabban ez nem kellett
#include <pcre2.h>

namespace _nsp_pcre2{

//----------------------------------------------------------------------------
struct pcreinfo
{
    int width; // 8, 16 vagy 32 bites karakterek

    union
    {
        pcre2_code_8        *pcode8;    // 8 bites
        pcre2_code          *pcode;     // 16 vagy 32 bites
    } code;
    
    union
    {
        pcre2_match_data_8  *pdata8;    // 8 bites
        pcre2_match_data    *pdata;     // 16 vagy 32 bites
    } data;
};

//----------------------------------------------------------------------------
static pcreinfo *pcreinfo_alloc()
{
    void *p=malloc(sizeof(pcreinfo));
    memset(p,0,sizeof(pcreinfo));
    return (pcreinfo *)p;
}

//----------------------------------------------------------------------------
static void pcreinfo_free(pcreinfo *info)
{
    if( info )
    {
        if( info->width==8 && info->data.pdata8 )
        {
            pcre2_match_data_free_8(info->data.pdata8 );
        }
        else if( info->width>8 && info->data.pdata )
        {
            pcre2_match_data_free(info->data.pdata );
        }

        if( info->width==8 &&  info->code.pcode8 )
        {
            pcre2_code_free_8(info->code.pcode8 );
        }

        else if( info->width>8 && info->code.pcode )
        {
            pcre2_code_free(info->code.pcode );
        }

        free(info);
    }
}

//----------------------------------------------------------------------------
void _clp_free(int argno) //pcre2.free(pcreptr)
{
    CCC_PROLOG("pcre2.free",1);
    pcreinfo *info=ISNIL(1)?0:(pcreinfo*)_parp(1);
    pcreinfo_free(info);
    _ret();
    CCC_EPILOG();
}


//----------------------------------------------------------------------------
void _clp_compile(int argno) //pcre2.compile(regex,flags) -> pcreinfo pointer
{
    CCC_PROLOG("pcre2.compile",2);

    int options=ISNIL(2)?0:_parni(2);

    int errornumber;
    size_t erroroffset;
    pcreinfo *info=pcreinfo_alloc();

#ifdef _CCC2_

        PCRE2_SPTR8 regex=(PCRE2_SPTR8)_parb(1);
        info->width=8;
        info->code.pcode8=pcre2_compile_8(
            regex,              // pattern
            _parblen(1),        // length
            options,            // options
            &errornumber,       // for error number
            &erroroffset,       // for error offset
            0);                 // use default compile context 

#else
    if( base->type==TYPE_BINARY )
    {
        PCRE2_SPTR8 regex=(PCRE2_SPTR8)_parb(1);
        info->width=8;
        info->code.pcode8=pcre2_compile_8(
            regex,              // pattern
            _parblen(1),        // length
            options,            // options
            &errornumber,       // for error number
            &erroroffset,       // for error offset
            0);                 // use default compile context 
    }
    else if( base->type==TYPE_STRING )
    {
        PCRE2_SPTR regex=(PCRE2_SPTR)_parc(1);
        info->width=PCRE2_CODE_UNIT_WIDTH;
        info->code.pcode=pcre2_compile(
            regex,              // pattern
            _parclen(1),        // length
            options,            // options
            &errornumber,       // for error number
            &erroroffset,       // for error offset
            0);                 // use default compile context 
    }
    else
    {
        error_arg("pcre2.compile",base,2);
    }
#endif

    if( info->code.pcode8==0 )
    {
        //HIBA

        //itt nem kell szetagazni a karakterszelessegtol fuggoen
        //hanem ki lehet olvasni a hibat a 8 bites interfesszel
    
        PCRE2_UCHAR8 errmsg[256];
        pcre2_get_error_message_8(errornumber, errmsg, sizeof(errmsg));
        char errbuf[512];
        unsigned len=sprintf(errbuf,"%s (offset %d)", errmsg, (int)erroroffset+1);

        pcreinfo_free(info);
        
        _clp_apperrornew(0);
        dup(); string(CHRLIT("pcre2.compile"));_o_method_operation.eval(2);pop(); 
        dup(); stringsb(errbuf,len);_o_method_description.eval(2);pop();
        dup(); string(CHRLIT("pcre2"));_o_method_subsystem.eval(2);pop(); 
        dup(); number(errornumber);_o_method_subcode.eval(2);pop();
        _clp_break(1);
        _ret();
    }

    pointer(info);
    _rettop();

    CCC_EPILOG();
}


//----------------------------------------------------------------------------
void _clp_match(int argno) //pcre.match(info,text,start,options) -> {idxarr}
{
    CCC_PROLOG("pcre2.match",4);

    pcreinfo *info=(pcreinfo*)_parp(1);
    int start=ISNIL(3)?0:_parni(3)-1;
    int options=ISNIL(4)?0:_parni(4);
    int retval=-1;

    if( info->width==8 )
    {
        if( info->data.pdata8==0 )
        {
            info->data.pdata8=pcre2_match_data_create_from_pattern_8(info->code.pcode8,0);
        }

        retval=pcre2_match_8(
            info->code.pcode8,          // the compiled pattern 
            (PCRE2_SPTR8)_parb(2),      // the subject string
            (size_t)_parblen(2),        // the length of the subject 
            (size_t)start,              // start offset in the subject
            options,                    // options
            info->data.pdata8,          // block for storing the result 
            0);
    }
    
    
    else if( info->width>8 )
    {
        if( info->data.pdata==0 )
        {
            info->data.pdata=pcre2_match_data_create_from_pattern(info->code.pcode,0);
        }

        retval=pcre2_match(
            info->code.pcode,           // the compiled pattern 
            (PCRE2_SPTR)_parc(2),       // the subject string
            (size_t)_parclen(2),        // the length of the subject 
            (size_t)start,              // start offset in the subject
            options,                    // options
            info->data.pdata,           // block for storing the result 
            0);
    }

    else
    {
        //ha ervenytelen a pointer
        error_arg("pcre2.match(pointer)",base,4);
    }

    
    if( retval<-1 )
    {
        //HIBA
        _clp_apperrornew(0);
        dup(); string(CHRLIT("pcre2"));_o_method_subsystem.eval(2);pop(); 
        dup(); string(CHRLIT("pcre2.match"));_o_method_operation.eval(2);pop(); 
        dup(); string(CHRLIT("pcre2.match failed"));_o_method_description.eval(2);pop();
        dup(); number(retval);_o_method_subcode.eval(2);pop();
       _clp_break(1);
        _ret();
    }
    else if( retval==PCRE2_ERROR_NOMATCH )
    {
        //nincs illeszkedes
        _ret();
    }
    else 
    {
        // "xxxxxxMMMMMMMMMMMMMxxxxxxxxxxxxxxxxxxx"
        //        ^            ^
        //    ovector[0]   ovector[1]  
        //
        // Mutatjak az illeszkedo substring hatarait.
        // A tovabbi indexek a regex reszeihez illeszkedo
        // subsubstringek hatarait mutatjak, ezek nehezen
        // ertelmezhetok, es altalaban nincs rajuk szukseg.

        PCRE2_SIZE *ovector;
        
        if( info->width==8 )
        {
            ovector=pcre2_get_ovector_pointer_8(info->data.pdata8);
        }
        else
        {
            ovector=pcre2_get_ovector_pointer(info->data.pdata);
        }
        
        for( int i=0; i<retval; i++ )
        {
            number(ovector[2*i]+1);
            number(ovector[2*i+1]+1);
        }

        array(retval*2);
        _rettop();
    }

    CCC_EPILOG();
}

//----------------------------------------------------------------------------

}//namespace
