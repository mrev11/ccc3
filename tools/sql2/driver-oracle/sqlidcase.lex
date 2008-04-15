
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

//Példa arra, hogyan lehet flex programmal
//átalakításokat végezni egy Clipper stringen.
//Prefix használattal a programban több flexlexer osztály is lehet.
//A rutin reentráns és szálbiztos, ui. az elemző egész állapotát 
//egy sqlidcase_lexer típusú objektum tárolja.

//Az SQL utasításokban "Ident" alakban található
//azonosítókat kis-, vagy nagybetűre konvertálja.

#include <string.h>
#include <cccapi.h>

#define BUFINC  1024

namespace _nsp_sql2{
namespace _nsp_oracle{

struct sqlidcase_lexer : public yyFlexLexer
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

/*
    void cat(char *txt)
    {
        int len=strlen(txt);
        if( textsize+len+1>buffersize )
        {
            text=(char*)realloc(text,buffersize+=(len+BUFINC));
        }
        memcpy(text+textsize,txt,len+1);
        textsize+=len;
    }
*/

  public:
    
    char *text;
    int textsize;
    int upperlower;

    int yylex(); //Flex definiálja, de nem deklarálja.
    
    sqlidcase_lexer(char *ptr, int size, int flag)
    {
        inputptr=ptr;
        inputsize=size;
        text=(char*)malloc(buffersize=BUFINC);
        textsize=0;
        upperlower=flag; //flag==.t. <--> upper
    }

    ~sqlidcase_lexer()
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

void _clp_sqlidcase(int argno)
{
    CCC_PROLOG("sqlidcase",2);
    char *stmt=_parcb(1);
    int leng=_parblen(1);
    int upperlower=_parl(2);
    if( leng )
    {
        sqlidcase_lexer lexer(stmt,leng,upperlower);
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
%option yyclass="_nsp_sql2::_nsp_oracle::sqlidcase_lexer"
%option noyywrap
%option stack
%option prefix="_sql2_oracle_sqlidcase"

string     "\'"[^\']*"\'" 
symbol     "\""[_a-zA-Z][_a-zA-Z0-9]*"\""

%%

{string}        {cat();}
{symbol}        {
                    int len=YYLeng();
                    const char *txt=YYText();
                    int n;
                    for( n=0; n<len; n++ )
                    {
                        if( upperlower )
                        {
                            cat( toupper(*(txt+n)) );
                        }
                        else
                        {
                            cat( tolower(*(txt+n)) );
                        }
                    }
                }
\n              {cat();}
.               {cat();}

%%



