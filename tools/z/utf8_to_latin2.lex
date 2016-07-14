
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

#include <cccapi.h>

class lexer_utf8_to_latin2 : public yyFlexLexer
{
  protected:

    char *ptr;
    int len;
    int cnt;

    int LexerInput(char *buf, int maxsiz)
    {
        if( cnt<len )
        {
            *buf=ptr[cnt++];
            return 1;
        }
        return 0;
    }

  public:

    int yylex(); //Flex definiálja, de nem deklarálja.

    lexer_utf8_to_latin2(char *p, int len)
    {
        //printf("construct lexer_utf8_to_latin2\n");
        this->ptr=p;
        this->len=len;
        this->cnt=0;
    }

    ~lexer_utf8_to_latin2()
    {
        //printf("destruct lexer_utf8_to_latin2\n");
    } 
};


void _clp_utf8_to_latin2(int argno)  // binary -> binary
{
    CCC_PROLOG("utf8_to_latin2",1);
    char *p=_parb(1);
    int len=_parblen(1);
    char *q=binaryl(len);
    lexer_utf8_to_latin2 lexer(p,len);
    int i=0,c;
    while( 0!=(c=lexer.yylex()) )
    {
        q[i++]=c;
    }
    _retblen(q,i);
    CCC_EPILOG();
}

%}


%option c++
%option yyclass="lexer_utf8_to_latin2"
%option prefix="base_utf8_to_latin2"
%option noyywrap
%option stack

symbol     "\""[_a-zA-Z][_a-zA-Z0-9]*"\""
 
%%

\xc3\xa1 {return 0xe1;}
\xc3\xa9 {return 0xe9;}
\xc3\xad {return 0xed;}
\xc3\xb3 {return 0xf3;}
\xc3\xb6 {return 0xf6;}
\xc5\x91 {return 0xf5;}
\xc3\xba {return 0xfa;}
\xc3\xbc {return 0xfc;}
\xc5\xb1 {return 0xfb;}

\xc3\x81 {return 0xc1;}
\xc3\x89 {return 0xc9;}
\xc3\x8d {return 0xcd;}
\xc3\x93 {return 0xd3;}
\xc3\x96 {return 0xd6;}
\xc5\x90 {return 0xd5;}
\xc3\x9a {return 0xda;}
\xc3\x9c {return 0xdc;}
\xc5\xb0 {return 0xdb;}

.        {return *YYText();}
\n       {return *YYText();}

%%

