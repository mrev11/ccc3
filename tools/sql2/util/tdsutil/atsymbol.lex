
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
#include <stdio.h>
#include <string.h>
#include <cccapi.h>

//Szimbólumot keres egy stringben,
//miközben kikerüli az idézeteket.

namespace _nsp_tdsutil{

class atsymbol : public yyFlexLexer
{
    protected:
    
    int LexerInput(char *buf, int maxsiz)
    {
        int len=(inlen-inidx)>maxsiz ? maxsiz:(inlen-inidx);  //min
        if( len>0 )
        {
            memmove(buf,inbuf+inidx,len);
            inidx+=len;
        }
        return len;
    }
    
    public: 

    char *inbuf;
    int inlen;
    int inidx;
    char *search;
    int counter;
    

    int yylex(); //Flex definiálja, de nem deklarálja.

    atsymbol(char *in, int len, char *s)
    {
        inbuf=in;
        inlen=len;
        inidx=0;
        search=s;
        counter=0;
    }

    ~atsymbol()
    {
        //Flex hiba javítása.
        if( yy_start_stack )
        {
            free(yy_start_stack);
            yy_start_stack=0;
        }
    }
};

void _clp_atsymbol(int argno)
{
    CCC_PROLOG("atsymbol",2);
    char *s=_parcb(1);
    char *p=_parcb(2);
    int len=_parblen(2);
    if( len )
    {
        atsymbol lexer(p,len,s);
        _retni(lexer.yylex());
    }
    else
    {
        _retni(0);
    }
    CCC_EPILOG();
}


} //namespace

%}

%option c++
%option noyywrap
%option yyclass="_nsp_tdsutil::atsymbol"
%option prefix="atsymbol"

symbol      [_a-zA-Z][_a-zA-Z0-9]*
string1     "\'"[^\'\n]*"\'"
string2     "\""[^\"\n]*"\""
 
%%

{symbol}    {
                if(0==strcmp(YYText(),search)) 
                {
                    return counter+1;
                }
                else
                {
                    counter+=YYLeng();
                }
            }


{string1}   counter+=YYLeng();
{string2}   counter+=YYLeng();
.           counter+=YYLeng();
\n          counter+=YYLeng();
 
%%

