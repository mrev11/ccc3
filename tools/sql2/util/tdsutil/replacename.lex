
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

//FlexLexer.h-t a generált kód inkludálja,
//a lex filében nem szabad duplán inkludálni!
//#include <flexlexer.h>

namespace _nsp_tdsutil{

extern void _clp_replacename_cb(int argno);

class replacename : public yyFlexLexer
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

    //const static int increment=256; //MSC hiba
    const static int increment;
    
    char *inbuf;
    int inlen;
    int inidx;
    
    char *outbuf;
    int outlen;
    int outidx;

    int yylex(); //Flex definiálja, de nem deklarálja.

    replacename(char *in, int len)
    {
        inbuf=in;
        inlen=len;
        inidx=0;
        outbuf=(char*)malloc(increment);
        outlen=increment;
        outidx=0;
    }

    ~replacename()
    {
        free(outbuf);
    }
    
    void cat(const char *p, int len)
    {
        while( outidx+len>=outlen )
        {
            outbuf=(char*)realloc(outbuf,outlen+=increment);
        }
        memmove(outbuf+outidx,p,len);
        outidx+=len;
    }
};

//MSC hiba
const int replacename::increment=256;


void _clp_replacename(int argno)
{
    CCC_PROLOG("replacename",2);
    char *p=_parcb(1);
    int len=_parblen(1);
    if( len )
    {
        //STACK: whereclause,collst
        replacename lexer(p,len);
        while(lexer.yylex());
        _retcblen(lexer.outbuf,lexer.outidx);
    }
    else
    {
        _retcb("");
    }
    CCC_EPILOG();
}


} //namespace

%}

%option c++
%option noyywrap
%option yyclass="_nsp_tdsutil::replacename"
%option prefix="replacename"

symbol      [_a-zA-Z][_a-zA-Z0-9]*
string1     "\'"[^\'\n]*"\'"
string2     "\""[^\"\n]*"\""
 
%%

{symbol}   {    
                //STACK: whereclause,collst
                dup();
                stringsb(YYText(),YYLeng());
                //STACK: whereclause,collst,collst,symbol
                _nsp_tdsutil::_clp_replacename_cb(2);
                //STACK: whereclause,collst,SYMBOL
                str2bin(TOP());
                cat(BINARYPTR(TOP()),TOP()->data.binary.len);
                pop();
                //STACK: whereclause,collst
           }

{string1}  cat(YYText(),YYLeng()); //kikerül
{string2}  cat(YYText(),YYLeng()); //kikerül
.          cat(YYText(),YYLeng());
\n         cat(YYText(),YYLeng());
 
%%

