
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



%x st_raw
%{

//xtranslate-eket keres, a stringeket kikerüli
 
#include <stdio.h>
#include <string.h>
#include <cccapi.h>

//a generalt kodban:
//#define ECHO (void) fwrite( yytext, yyleng, 1, yyout ) 
//gcc 4.3.2 warning: ignoring return value
#define ECHO (0==fwrite(yytext,yyleng,1,yyout))


static char      *buffer=0;
static int       buflen=0;
static int       bufidx=0;
static int       chrcount=0;
 
#define YY_NEVER_INTERACTIVE  1

#define YY_INPUT(buf,result,max_size)\
  { result = (bufidx<buflen) ?\
             (buf[0]=buffer[bufidx++],1) :\
             YY_NULL; }


static char *raw_symbol=0;
static void raw_beg()
{
    raw_symbol=strdup(yytext);
    BEGIN(st_raw);
}
static void raw_end()
{
    if( 0==strcmp(raw_symbol,yytext) )
    {
        free(raw_symbol);
        BEGIN(0);
    }
}


%}

%option noyywrap
%option prefix="trfind"


symbol     [_a-zA-Z][_a-zA-Z0-9]*
string     ("\""[^\"\n]*"\""|"\'"[^\'\n]*"\'")

%%

"<<"{symbol}">>"    chrcount+=yyleng;raw_beg();
<st_raw>{
"<<"{symbol}">>"    chrcount+=yyleng;raw_end();
"\n"                chrcount++;
.                   chrcount++;
}

{string}            chrcount+=yyleng;
"#command"          return chrcount+1;
"#xcommand"         return chrcount+1;
"#translate"        return chrcount+1;
"#xtranslate"       return chrcount+1;
\n                  chrcount++;
.                   chrcount++;

%%


//------------------------------------------------------------------------
void _clp_find_translate(int argno)
{
    CCC_PROLOG("find_translate",1);

    buffer     = _parb(1);
    buflen     = _parblen(1);
    bufidx     = 0;
    chrcount   = 0;
    _retni( yylex() );
    CCC_EPILOG();
}

//------------------------------------------------------------------------
