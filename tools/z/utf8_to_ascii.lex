
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

class lexer_utf8_to_ascii : public yyFlexLexer
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

    lexer_utf8_to_ascii(char *p, int len)
    {
        //printf("construct lexer_utf8_to_ascii\n");
        this->ptr=p;
        this->len=len;
        this->cnt=0;
    }

    ~lexer_utf8_to_ascii()
    {
        //printf("destruct lexer_utf8_to_ascii\n");
    } 
};


void _clp_utf8_to_ascii(int argno)  // binary -> binary
{
    CCC_PROLOG("utf8_to_ascii",1);
    char *p=_parb(1);
    int len=_parblen(1);
    char *q=binaryl(len);
    lexer_utf8_to_ascii lexer(p,len);
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
%option yyclass="lexer_utf8_to_ascii"
%option prefix="base_utf8_to_ascii"
%option noyywrap
%option stack

symbol     "\""[_a-zA-Z][_a-zA-Z0-9]*"\""
 
%%

\xc3\xa1 {return('a');}
\xc3\xa9 {return('e');}
\xc3\xad {return('i');}
\xc3\xb3 {return('o');}
\xc3\xb6 {return('o');}
\xc5\x91 {return('o');}
\xc3\xba {return('u');}
\xc3\xbc {return('u');}
\xc5\xb1 {return('u');}
\xc3\xa4 {return('a');}
\xc3\x81 {return('A');}
\xc3\x89 {return('E');}
\xc3\x8d {return('I');}
\xc3\x93 {return('O');}
\xc3\x96 {return('O');}
\xc5\x90 {return('O');}
\xc3\x9a {return('U');}
\xc3\x9c {return('U');}
\xc5\xb0 {return('U');}
\xc3\x84 {return('A');}

.        {return *YYText();}
\n       {return *YYText();}

%%

