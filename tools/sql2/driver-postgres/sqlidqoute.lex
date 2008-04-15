
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

%{

//Pl.: schema.fld_1+fld_2 -> "schema"."fld_1"+"fld_2"


#include <memory.h>
#include <cccapi.h>

#define BUFINC  1024

namespace _nsp_sql2 {
namespace _nsp_postgres {

struct sqlidquote_lexer : public yyFlexLexer
{
  protected:

    int LexerInput(char *buf, int maxsize)
    {
        int retsize=0;
        while( (inputsize>0) && (maxsize>0) )
        {
            *buf++=*inputptr++;
            inputsize--;
            maxsize--;
            retsize++;
        }
        return retsize;
    }

    char *inputptr;
    int inputsize;
    int buffersize;

    void cat()
    {
        int len=YYLeng();
        const char *txt=YYText();

        if( textsize+len+1>buffersize )
        {
            text=(char*)realloc(text,buffersize+=(len+BUFINC));
        }
        memcpy(text+textsize,txt,len+1);
        textsize+=len;
    }

    void cat_upper()
    {
        int len=YYLeng();
        const char *txt=YYText();

        if( textsize+len+1>buffersize )
        {
            text=(char*)realloc(text,buffersize+=(len+BUFINC));
        }
        for( int i=0; i<=len; i++ )
        {
            *(text+textsize+i)=toupper(*(txt+i));
        }
        textsize+=len;
    }

    void cat_lower()
    {
        int len=YYLeng();
        const char *txt=YYText();

        if( textsize+len+1>buffersize )
        {
            text=(char*)realloc(text,buffersize+=(len+BUFINC));
        }
        for( int i=0; i<=len; i++ )
        {
            *(text+textsize+i)=tolower(*(txt+i));
        }
        textsize+=len;
    }

    void cat(char c)
    {
        if( textsize+1+1>buffersize )
        {
            text=(char*)realloc(text,buffersize+=(1+BUFINC));
        }
        *(text+textsize)=c;
        *(text+textsize+1)=0;
        textsize++;
    }

  public:
    
    char *text;
    int textsize;

    int yylex(); //Flex definiálja, de nem deklarálja.
    
    sqlidquote_lexer(char *ptr, int size)
    {
        inputptr=ptr;
        inputsize=size;
        text=(char*)malloc(buffersize=BUFINC);
        textsize=0;
    }

    ~sqlidquote_lexer()
    {
        free(text);
        
        //Flex hiba javítása.
        //A Flex nem szabadítja fel az alábbi buffert:
        //yy_start_stack protected member az yyFlexLexer osztályban,
        //és elfedi a static yy_start_stack külső változót (zavaros).
        
        if( yy_start_stack )
        {
            free(yy_start_stack);
            yy_start_stack=0;
        }
    } 
};

void _clp_sqlidquote(int argno)
{
    CCC_PROLOG("sqlidquote",1);
    char *expr=_parcb(1);
    int leng=_parblen(1);
    if(leng)
    {
        sqlidquote_lexer lexer(expr,leng);
        lexer.yylex();
        _retcblen(lexer.text,lexer.textsize);
    }
    else
    {
        _retcb("");
    }
    CCC_EPILOG();
}

}} //namespace

%}


%option c++
%option yyclass="_nsp_sql2::_nsp_postgres::sqlidquote_lexer"
%option noyywrap
%option stack
%option prefix="_sql2_postgres_sqlidquote"

symbol     [_a-zA-Z][_a-zA-Z0-9]*
quoted     "\""{symbol}"\"" 
string     "\'"[^\']*"\'" 

%%

{symbol}        {cat('\"');cat_lower();cat('\"');} /*idézőjelek közé teszi*/
{quoted}        {cat_lower();} /*már idézőjelezve van*/
{string}        {cat();} /*kikerül*/
\n              {}
.               {cat();}

%%


