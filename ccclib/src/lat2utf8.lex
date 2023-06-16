
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

#include <memory.h>
#include <cccapi.h>

//ez utkozik egy dobozrajzoloval
//\xc4 {cat(0xc3,0x84); /*Ä*/}


#define BUFINC  8192


struct lat2utf8_lexer : public yyFlexLexer
{
  protected:

    char *input;
    int inputsize;
    int buffersize;

    int LexerInput(char *buf, int maxsize)
    {
        int retsize=0;
        while( (inputsize>0) && (maxsize>0) )
        {
            *buf++=*input++;
            inputsize--;
            maxsize--;
            retsize++;
        }
        return retsize;
    }


    void cat()
    {
        int len=YYLeng();
        const char *txt=YYText();

        if( outputsize+len+1>buffersize )
        {
            output=(char*)realloc(output,buffersize+=(len+BUFINC));
        }
        memcpy(output+outputsize,txt,len+1);
        outputsize+=len;
    }

    void cat(char c)
    {
        if( c>127 )
        {
            // ide akkor jon
            // ha a bemeneti karakterhez
            // nincs Char -> UTF8 flex szabaly
            c='?';
        }
        if( outputsize+1+1>buffersize )
        {
            output=(char*)realloc(output,buffersize+=(1+BUFINC));
        }
        *(output+outputsize)=c;
        *(output+outputsize+1)=0;
        outputsize++;
    }

    void cat(char c1, char c2)
    {
        if( outputsize+2+1>buffersize )
        {
            output=(char*)realloc(output,buffersize+=(2+BUFINC));
        }
        *(output+outputsize)=c1;
        *(output+outputsize+1)=0;
        outputsize++;

        *(output+outputsize)=c2;
        *(output+outputsize+1)=0;
        outputsize++;
    }

    void cat(char c1, char c2, char c3)
    {
        if( outputsize+3+1>buffersize )
        {
            output=(char*)realloc(output,buffersize+=(3+BUFINC));
        }
        *(output+outputsize)=c1;
        *(output+outputsize+1)=0;
        outputsize++;

        *(output+outputsize)=c2;
        *(output+outputsize+1)=0;
        outputsize++;

        *(output+outputsize)=c3;
        *(output+outputsize+1)=0;
        outputsize++;
    }

  public:
    
    char *output;
    int outputsize;

    int yylex(); //Flex definiálja, de nem deklarálja.
    
    lat2utf8_lexer(char *ptr, int size)
    {
        input=ptr;
        inputsize=size;
        output=(char*)malloc(buffersize=BUFINC);
        outputsize=0;
    }

    ~lat2utf8_lexer()
    {
        free(output);
    } 
};



void _clp_lat2utf8(int argno)
{
    CCC_PROLOG("lat2utf8",1);
    char *input=_parb(1);
    int inputsize=_parblen(1);
    if( inputsize )
    {
        lat2utf8_lexer lexer(input,inputsize);
        lexer.yylex();
        _retblen(lexer.output,lexer.outputsize);
    }
    CCC_EPILOG();
}


%}


%option c++
%option yyclass="lat2utf8_lexer"
%option noyywrap
%option stack
%option prefix="lat2utf8"
 
%%

\xdf {cat(0xc3,0x9f); /*ß*/}
\xe4 {cat(0xc3,0xa4); /*ä*/}

\xa0 {cat(0xc3,0xa1);}
\x82 {cat(0xc3,0xa9);}
\xa1 {cat(0xc3,0xad);}
\xa2 {cat(0xc3,0xb3);}
\x94 {cat(0xc3,0xb6);}
\x93 {cat(0xc5,0x91);}
\xa3 {cat(0xc3,0xba);}
\x81 {cat(0xc3,0xbc);}
\x96 {cat(0xc5,0xb1);}
\x8f {cat(0xc3,0x81);}
\x90 {cat(0xc3,0x89);}
\x8c {cat(0xc3,0x8d);}
\x8d {cat(0xc3,0x8d);}
\x95 {cat(0xc3,0x93);}
\x99 {cat(0xc3,0x96);}
\xa7 {cat(0xc5,0x90);}
\x97 {cat(0xc3,0x9a);}
\x9a {cat(0xc3,0x9c);}
\x98 {cat(0xc5,0xb0);}
\xe1 {cat(0xc3,0xa1);}
\xe9 {cat(0xc3,0xa9);}
\xed {cat(0xc3,0xad);}
\xf3 {cat(0xc3,0xb3);}
\xf6 {cat(0xc3,0xb6);}
\xf4 {cat(0xc5,0x91);}
\xf5 {cat(0xc5,0x91);}
\xfa {cat(0xc3,0xba);}
\xfc {cat(0xc3,0xbc);}
\xfb {cat(0xc5,0xb1);}
\xc1 {cat(0xc3,0x81);}
\xc9 {cat(0xc3,0x89);}
\xcd {cat(0xc3,0x8d);}
\xcd {cat(0xc3,0x8d);}
\xd3 {cat(0xc3,0x93);}
\xd6 {cat(0xc3,0x96);}
\xd4 {cat(0xc5,0x90);}
\xd5 {cat(0xc5,0x90);}
\xda {cat(0xc3,0x9a);}
\xdc {cat(0xc3,0x9c);}
\xdb {cat(0xc5,0xb0);}
\xcf {cat(0xe2,0x94,0x8c);}
\xb6 {cat(0xe2,0x94,0x80);}
\xb4 {cat(0xe2,0x94,0xac);}
\xb6 {cat(0xe2,0x94,0x80);}
\xb1 {cat(0xe2,0x94,0x90);}
\xa4 {cat(0xe2,0x94,0x82);}
\xa4 {cat(0xe2,0x94,0x82);}
\xa4 {cat(0xe2,0x94,0x82);}
\xb5 {cat(0xe2,0x94,0x9c);}
\xb6 {cat(0xe2,0x94,0x80);}
\xb7 {cat(0xe2,0x94,0xbc);}
\xb6 {cat(0xe2,0x94,0x80);}
\xa5 {cat(0xe2,0x94,0xa4);}
\xb2 {cat(0xe2,0x94,0x94);}
\xb6 {cat(0xe2,0x94,0x80);}
\xb3 {cat(0xe2,0x94,0xb4);}
\xb6 {cat(0xe2,0x94,0x80);}
\xce {cat(0xe2,0x94,0x98);}
\xbb {cat(0xe2,0x95,0x94);}
\xbf {cat(0xe2,0x95,0x90);}
\xbd {cat(0xe2,0x95,0xa6);}
\xbf {cat(0xe2,0x95,0x90);}
\xad {cat(0xe2,0x95,0x97);}
\xac {cat(0xe2,0x95,0x91);}
\xac {cat(0xe2,0x95,0x91);}
\xac {cat(0xe2,0x95,0x91);}
\xbe {cat(0xe2,0x95,0xa0);}
\xbf {cat(0xe2,0x95,0x90);}
\xc0 {cat(0xe2,0x95,0xac);}
\xbf {cat(0xe2,0x95,0x90);}
\xab {cat(0xe2,0x95,0xa3);}
\xba {cat(0xe2,0x95,0x9a);}
\xbf {cat(0xe2,0x95,0x90);}
\xbc {cat(0xe2,0x95,0xa9);}
\xbf {cat(0xe2,0x95,0x90);}
\xae {cat(0xe2,0x95,0x9d);}
\xc8 {cat(0xe2,0x95,0x92);}
\xbf {cat(0xe2,0x95,0x90);}
\xc4 {cat(0xe2,0x95,0xa4);}
\xbf {cat(0xe2,0x95,0x90);}
\xaa {cat(0xe2,0x95,0x95);}
\xb8 {cat(0xe2,0x95,0x9e);}
\xbf {cat(0xe2,0x95,0x90);}
\xcc {cat(0xe2,0x95,0xaa);}
\xbf {cat(0xe2,0x95,0x90);}
\xa6 {cat(0xe2,0x95,0xa1);}
\xc7 {cat(0xe2,0x95,0x98);}
\xbf {cat(0xe2,0x95,0x90);}
\xc2 {cat(0xe2,0x95,0xa7);}
\xbf {cat(0xe2,0x95,0x90);}
\xb0 {cat(0xe2,0x95,0x9b);}
\xca {cat(0xe2,0x95,0x93);}
\xb6 {cat(0xe2,0x94,0x80);}
\xc5 {cat(0xe2,0x95,0xa5);}
\xb6 {cat(0xe2,0x94,0x80);}
\xa9 {cat(0xe2,0x95,0x96);}
\xb9 {cat(0xe2,0x95,0x9f);}
\xb6 {cat(0xe2,0x94,0x80);}
\xcb {cat(0xe2,0x95,0xab);}
\xb6 {cat(0xe2,0x94,0x80);}
\xa8 {cat(0xe2,0x95,0xa2);}
\xc6 {cat(0xe2,0x95,0x99);}
\xb6 {cat(0xe2,0x94,0x80);}
\xc3 {cat(0xe2,0x95,0xa8);}
\xb6 {cat(0xe2,0x94,0x80);}
\xaf {cat(0xe2,0x95,0x9c);}
\xfe {cat(0xe2,0x96,0x88);}
\xf9 {cat(0xe2,0x96,0x93);}
\x9f {cat(0xe2,0x96,0x92);}
\x9d {cat(0xe2,0x96,0x91);}
 
\n   {cat(*YYText());}
.    {cat(*YYText());}

 
%%

//---------------------------------------------------------------------------
//int main(int argc, char**argv)
//{
//    yylex();
//}
//---------------------------------------------------------------------------


