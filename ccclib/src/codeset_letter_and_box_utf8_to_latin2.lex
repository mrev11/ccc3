
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
#include <codeset_box.h>
#include <codeset_letter.h>

class codeset_letter_and_box_utf8_to_latin2 : public yyFlexLexer
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

    codeset_letter_and_box_utf8_to_latin2(char *p, int len)
    {
        this->ptr=p;
        this->len=len;
        this->cnt=0;
    }
};


void _clp_codeset_letter_and_box_utf8_to_latin2(int argno)  // binary -> binary
{
    CCC_PROLOG("codeset_letter_and_box_utf8_to_latin2",1);
    char *p=_parb(1);
    int len=_parblen(1);
    char *q=binaryl(len);
    codeset_letter_and_box_utf8_to_latin2 lexer(p,len);
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
%option yyclass="codeset_letter_and_box_utf8_to_latin2"
%option prefix="codeset_letter_and_box_utf8_to_latin2"
%option noyywrap
%option stack


BOX_UTF8_HS                         \xe2\x94\x80
BOX_UTF8_HD                         \xe2\x95\x90
BOX_UTF8_VS                         \xe2\x94\x82
BOX_UTF8_VD                         \xe2\x95\x91
BOX_UTF8_SS1                        \xe2\x94\x94
BOX_UTF8_SS2                        \xe2\x94\xb4
BOX_UTF8_SS3                        \xe2\x94\x98
BOX_UTF8_SS4                        \xe2\x94\x9c
BOX_UTF8_SS5                        \xe2\x94\xbc
BOX_UTF8_SS6                        \xe2\x94\xa4
BOX_UTF8_SS7                        \xe2\x94\x8c
BOX_UTF8_SS8                        \xe2\x94\xac
BOX_UTF8_SS9                        \xe2\x94\x90
BOX_UTF8_DD1                        \xe2\x95\x9a
BOX_UTF8_DD2                        \xe2\x95\xa9
BOX_UTF8_DD3                        \xe2\x95\x9d
BOX_UTF8_DD4                        \xe2\x95\xa0
BOX_UTF8_DD5                        \xe2\x95\xac
BOX_UTF8_DD6                        \xe2\x95\xa3
BOX_UTF8_DD7                        \xe2\x95\x94
BOX_UTF8_DD8                        \xe2\x95\xa6
BOX_UTF8_DD9                        \xe2\x95\x97
BOX_UTF8_SD1                        \xe2\x95\x99
BOX_UTF8_SD2                        \xe2\x95\xa8
BOX_UTF8_SD3                        \xe2\x95\x9c
BOX_UTF8_SD4                        \xe2\x95\x9f
BOX_UTF8_SD5                        \xe2\x95\xab
BOX_UTF8_SD6                        \xe2\x95\xa2
BOX_UTF8_SD7                        \xe2\x95\x93
BOX_UTF8_SD8                        \xe2\x95\xa5
BOX_UTF8_SD9                        \xe2\x95\x96
BOX_UTF8_DS1                        \xe2\x95\x98
BOX_UTF8_DS2                        \xe2\x95\xa7
BOX_UTF8_DS3                        \xe2\x95\x9b
BOX_UTF8_DS4                        \xe2\x95\x9e
BOX_UTF8_DS5                        \xe2\x95\xaa
BOX_UTF8_DS6                        \xe2\x95\xa1
BOX_UTF8_DS7                        \xe2\x95\x92
BOX_UTF8_DS8                        \xe2\x95\xa4
BOX_UTF8_DS9                        \xe2\x95\x95


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

{BOX_UTF8_HS}                       {return BOX_CCC2_HS ;}
{BOX_UTF8_HD}                       {return BOX_CCC2_HD ;}
{BOX_UTF8_VS}                       {return BOX_CCC2_VS ;}
{BOX_UTF8_VD}                       {return BOX_CCC2_VD ;}
{BOX_UTF8_SS1}                      {return BOX_CCC2_SS1;}
{BOX_UTF8_SS2}                      {return BOX_CCC2_SS2;}
{BOX_UTF8_SS3}                      {return BOX_CCC2_SS3;}
{BOX_UTF8_SS4}                      {return BOX_CCC2_SS4;}
{BOX_UTF8_SS5}                      {return BOX_CCC2_SS5;}
{BOX_UTF8_SS6}                      {return BOX_CCC2_SS6;}
{BOX_UTF8_SS7}                      {return BOX_CCC2_SS7;}
{BOX_UTF8_SS8}                      {return BOX_CCC2_SS8;}
{BOX_UTF8_SS9}                      {return BOX_CCC2_SS9;}
{BOX_UTF8_DD1}                      {return BOX_CCC2_DD1;}
{BOX_UTF8_DD2}                      {return BOX_CCC2_DD2;}
{BOX_UTF8_DD3}                      {return BOX_CCC2_DD3;}
{BOX_UTF8_DD4}                      {return BOX_CCC2_DD4;}
{BOX_UTF8_DD5}                      {return BOX_CCC2_DD5;}
{BOX_UTF8_DD6}                      {return BOX_CCC2_DD6;}
{BOX_UTF8_DD7}                      {return BOX_CCC2_DD7;}
{BOX_UTF8_DD8}                      {return BOX_CCC2_DD8;}
{BOX_UTF8_DD9}                      {return BOX_CCC2_DD9;}
{BOX_UTF8_SD1}                      {return BOX_CCC2_SD1;}
{BOX_UTF8_SD2}                      {return BOX_CCC2_SD2;}
{BOX_UTF8_SD3}                      {return BOX_CCC2_SD3;}
{BOX_UTF8_SD4}                      {return BOX_CCC2_SD4;}
{BOX_UTF8_SD5}                      {return BOX_CCC2_SD5;}
{BOX_UTF8_SD6}                      {return BOX_CCC2_SD6;}
{BOX_UTF8_SD7}                      {return BOX_CCC2_SD7;}
{BOX_UTF8_SD8}                      {return BOX_CCC2_SD8;}
{BOX_UTF8_SD9}                      {return BOX_CCC2_SD9;}
{BOX_UTF8_DS1}                      {return BOX_CCC2_DS1;}
{BOX_UTF8_DS2}                      {return BOX_CCC2_DS2;}
{BOX_UTF8_DS3}                      {return BOX_CCC2_DS3;}
{BOX_UTF8_DS4}                      {return BOX_CCC2_DS4;}
{BOX_UTF8_DS5}                      {return BOX_CCC2_DS5;}
{BOX_UTF8_DS6}                      {return BOX_CCC2_DS6;}
{BOX_UTF8_DS7}                      {return BOX_CCC2_DS7;}
{BOX_UTF8_DS8}                      {return BOX_CCC2_DS8;}
{BOX_UTF8_DS9}                      {return BOX_CCC2_DS9;}


{UTF8_SMALL_A_ACUTE}                {return LATIN_SMALL_A_ACUTE         ;}
{UTF8_SMALL_E_ACUTE}                {return LATIN_SMALL_E_ACUTE         ;}
{UTF8_SMALL_I_ACUTE}                {return LATIN_SMALL_I_ACUTE         ;}
{UTF8_SMALL_O_ACUTE}                {return LATIN_SMALL_O_ACUTE         ;}
{UTF8_SMALL_O_DIAERESIS}            {return LATIN_SMALL_O_DIAERESIS     ;}
{UTF8_SMALL_O_DOUBLE_ACUTE}         {return LATIN_SMALL_O_DOUBLE_ACUTE  ;}
{UTF8_SMALL_U_ACUTE}                {return LATIN_SMALL_U_ACUTE         ;}
{UTF8_SMALL_U_DIAERESIS}            {return LATIN_SMALL_U_DIAERESIS     ;}
{UTF8_SMALL_U_DOUBLE_ACUTE}         {return LATIN_SMALL_U_DOUBLE_ACUTE  ;}
{UTF8_SMALL_A_DIAERESIS}            {return LATIN_SMALL_A_DIAERESIS     ;}


{UTF8_CAPITAL_A_ACUTE}              {return LATIN_CAPITAL_A_ACUTE       ;}
{UTF8_CAPITAL_E_ACUTE}              {return LATIN_CAPITAL_E_ACUTE       ;}
{UTF8_CAPITAL_I_ACUTE}              {return LATIN_CAPITAL_I_ACUTE       ;}
{UTF8_CAPITAL_O_ACUTE}              {return LATIN_CAPITAL_O_ACUTE       ;}
{UTF8_CAPITAL_O_DIAERESIS}          {return LATIN_CAPITAL_O_DIAERESIS   ;}
{UTF8_CAPITAL_O_DOUBLE_ACUTE}       {return LATIN_CAPITAL_O_DOUBLE_ACUTE;}
{UTF8_CAPITAL_U_ACUTE}              {return LATIN_CAPITAL_U_ACUTE       ;}
{UTF8_CAPITAL_U_DIAERESIS}          {return LATIN_CAPITAL_U_DIAERESIS   ;}
{UTF8_CAPITAL_U_DOUBLE_ACUTE}       {return LATIN_CAPITAL_U_DOUBLE_ACUTE;}
{UTF8_CAPITAL_A_DIAERESIS}          {return LATIN_CAPITAL_A_DIAERESIS   ;}

\n                                  {return *YYText();}
.                                   {return *YYText();}

%%

