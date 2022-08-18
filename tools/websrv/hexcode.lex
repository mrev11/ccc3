
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

#ifdef NOT_DEFINED //hexcode
  A %hh kódolású byteokat becseréli: pl. %20 -> ' '
#endif

#include <string.h>
#include <memory.h>
#include <cccapi.h>

#define BUFINC  1024

namespace _nsp_websrv{

struct hexcode_lexer : public yyFlexLexer
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

    void cat(const char* txt)
    {
        int len=strlen(txt);
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

    char code()
    {
        int c=0,c1,i;
        const char *txt=YYText();
        
        for( i=1; i<=2; i++ )
        {

            c1=txt[i];
            if( 'a'<=c1 && c1<='f' )
            {
                c1=10+c1-'a';
            }
            else if( 'A'<=c1 && c1<='F' )
            {
                c1=10+c1-'A';
            }
            else
            {
                c1=c1-'0';
            }
            c=(c<<4)+c1;
        }
        return (char)c;
    }

  public:
    
    char *text;
    int textsize;

    int yylex(); //Flex definiálja, de nem deklarálja.
    
    hexcode_lexer(char *ptr, int size)
    {
        inputptr=ptr;
        inputsize=size;
        text=(char*)malloc(buffersize=BUFINC);
        textsize=0;
    }

    ~hexcode_lexer()
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

void _clp_hexdecode(int argno)
{
    CCC_PROLOG("hexdecode",1);
    char *input=_parb(1);
    int leng=_parblen(1);
    if( leng )
    {
        hexcode_lexer lexer(input,leng);
        lexer.yylex();
        _retblen(lexer.text,lexer.textsize);
    }
    else
    {
        _retb("");
    }
    CCC_EPILOG();
}

void _clp_hexencode(int argno)
{
    CCC_PROLOG("hexencode",1);
    char *input=_parb(1);
    int leng=_parblen(1);
    char *p=binaryl(leng*3);
    int i=0, j=0;
    for(i; i<leng; i++)
    {
        int c=255&(int)input[i];

        if( 32<c && c<128 && c!=35 ) //'#'
        {
            p[j]=c;
            j+=1;
        }
        else
        {
            sprintf(p+j,"%%%02X",c);
            j+=3;
        }
    }
    binarys(p,j);
    _rettop();
    CCC_EPILOG();
}

} //namesace

%}


%option c++
%option yyclass="_nsp_websrv::hexcode_lexer"
%option noyywrap
%option stack
%option prefix="hexcode"

hex             [0-9a-fA-F]

%%

"\%"{hex}{hex}  {cat(code());}
\n              {cat();}
.               {cat();}

%%


