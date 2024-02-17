
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
#include <codeset_letter.h>

class codeset_letter_utf8_to_ascii : public yyFlexLexer
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

    int yylex();

    codeset_letter_utf8_to_ascii(char *p, int len)
    {
        this->ptr=p;
        this->len=len;
        this->cnt=0;
    }
};


void _clp_codeset_letter_utf8_to_ascii(int argno)  // binary -> binary
{
    CCC_PROLOG("codeset_letter_utf8_to_ascii",1);
    char *p=_parb(1);
    int len=_parblen(1);
    char *q=binaryl(len);
    codeset_letter_utf8_to_ascii lexer(p,len);
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
%option yyclass="codeset_letter_utf8_to_ascii"
%option prefix="codeset_letter_utf8_to_ascii"
%option noyywrap
%option stack


UTF8_SMALL_A_ACUTE                  \xc3\xa1
UTF8_SMALL_E_ACUTE                  \xc3\xa9
UTF8_SMALL_I_ACUTE                  \xc3\xad
UTF8_SMALL_O_ACUTE                  \xc3\xb3
UTF8_SMALL_O_DIAERESIS              \xc3\xb6
UTF8_SMALL_O_DOUBLE_ACUTE           \xc5\x91
UTF8_SMALL_U_ACUTE                  \xc3\xba
UTF8_SMALL_U_DIAERESIS              \xc3\xbc
UTF8_SMALL_U_DOUBLE_ACUTE           \xc5\xb1
UTF8_SMALL_A_DIAERESIS              \xc3\xa4

UTF8_CAPITAL_A_ACUTE                \xc3\x81
UTF8_CAPITAL_E_ACUTE                \xc3\x89
UTF8_CAPITAL_I_ACUTE                \xc3\x8d
UTF8_CAPITAL_O_ACUTE                \xc3\x93
UTF8_CAPITAL_O_DIAERESIS            \xc3\x96
UTF8_CAPITAL_O_DOUBLE_ACUTE         \xc5\x90
UTF8_CAPITAL_U_ACUTE                \xc3\x9a
UTF8_CAPITAL_U_DIAERESIS            \xc3\x9c
UTF8_CAPITAL_U_DOUBLE_ACUTE         \xc5\xb0
UTF8_CAPITAL_A_DIAERESIS            \xc3\x84

%%

{UTF8_SMALL_A_ACUTE}                {return('a');}
{UTF8_SMALL_E_ACUTE}                {return('e');}
{UTF8_SMALL_I_ACUTE}                {return('i');}
{UTF8_SMALL_O_ACUTE}                {return('o');}
{UTF8_SMALL_O_DIAERESIS}            {return('o');}
{UTF8_SMALL_O_DOUBLE_ACUTE}         {return('o');}
{UTF8_SMALL_U_ACUTE}                {return('u');}
{UTF8_SMALL_U_DIAERESIS}            {return('u');}
{UTF8_SMALL_U_DOUBLE_ACUTE}         {return('u');}
{UTF8_SMALL_A_DIAERESIS}            {return('a');}
                                    
{UTF8_CAPITAL_A_ACUTE}              {return('A');}
{UTF8_CAPITAL_E_ACUTE}              {return('E');}
{UTF8_CAPITAL_I_ACUTE}              {return('I');}
{UTF8_CAPITAL_O_ACUTE}              {return('O');}
{UTF8_CAPITAL_O_DIAERESIS}          {return('O');}
{UTF8_CAPITAL_O_DOUBLE_ACUTE}       {return('O');}
{UTF8_CAPITAL_U_ACUTE}              {return('U');}
{UTF8_CAPITAL_U_DIAERESIS}          {return('U');}
{UTF8_CAPITAL_U_DOUBLE_ACUTE}       {return('U');}
{UTF8_CAPITAL_A_DIAERESIS}          {return('A');}

\n                                  {return *YYText();}
.                                   {return *YYText();}

%%

