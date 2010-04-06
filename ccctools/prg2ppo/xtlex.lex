
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

%x raw

%{

#include <stdio.h>
#include <string.h>
#include <cccapi.h>
 
static void xtlexstore(const char*);
static void xtlextrim(char*);
 
static int      item_count;
static char     *buffer;
static unsigned buflen;
static unsigned bufidx;

//a generalt kodban:
//#define ECHO (void) fwrite( yytext, yyleng, 1, yyout ) 
//gcc 4.3.2 warning: ignoring return value
//#define ECHO (0==fwrite(yytext,yyleng,1,yyout))

#define YY_NEVER_INTERACTIVE  1
 
#define YY_INPUT(buf,result,max_size)\
  { result = (bufidx<buflen) ?\
             (buf[0]=buffer[bufidx++],1) :\
             YY_NULL; }


static int raw_textsize=0;
static int raw_bufsize=0;
static char* raw_text=0;
static char* raw_symbol=0;

static void raw_cat(char *x)
{
    int len=strlen(x);
    while( raw_textsize+len+1>raw_bufsize )
    {
        raw_text=(char*)realloc(raw_text,raw_bufsize+=1024);
    }
    memcpy(raw_text+raw_textsize,x,len+1);
    raw_textsize+=len;
}

static void raw_beg(int state)
{
    raw_symbol=strdup(yytext);
    raw_textsize=0;
    raw_cat(yytext);
    BEGIN(state); //BEGIN(raw) helyett, Flex 2.5.31 hiba 
}

static void raw_end()
{
    raw_cat(yytext);
    if( 0==strcmp(raw_symbol,yytext) )
    {
        free(raw_symbol);
        xtlexstore(raw_text);
        BEGIN(0); //BEGIN(INITIAL) helyett, Flex 2.5.31 hiba 
    }
}
 
%}

%option noyywrap
%option prefix="xt"

hex          [0-9a-fA-F]
number       [0-9]+("."[0-9]+|"")
numberb      [0][bB][01]+
numberx      [0][xX]{hex}+
symbol       [_a-zA-Z][_a-zA-Z0-9]*
string       ("\""[^\"\n]*"\""|"\'"[^\'\n]*"\'")
binarya      a{string}
binaryx      [xX]("\""({hex}{hex})*"\""|"\'"({hex}{hex})*"\'")
logical      "."(f|F|t|T|and|AND|And|or|OR|Or|not|NOT|Not)"." 
dotdot       ".."
wspace       [ \r\t\n]*
glue         [ \t]*"##"[ \t]* 
trim         [ \t]*[,|{}\[\]][ \t]*|[(][ \t]*|[ \t]*[)] 
sep          "/**/" 
 
%%

"<<"{symbol}">>"    raw_beg(raw);
<raw>{
"<<"{symbol}">>"    raw_end();
"\n"                raw_cat(yytext);
.                   raw_cat(yytext);
}

{symbol}            xtlexstore(yytext);
{number}            xtlexstore(yytext);
{numberb}           xtlexstore(yytext);
{numberx}           xtlexstore(yytext);
{string}            xtlexstore(yytext); 
{binarya}           xtlexstore(yytext); 
{binaryx}           xtlexstore(yytext); 
{logical}           xtlexstore(yytext); 
{dotdot}            xtlexstore(yytext); 
{wspace}            if(item_count) xtlexstore(" ");  
{glue}              xtlexstore("##");   
{trim}              xtlextrim(yytext);
{sep}    
.                   xtlexstore(yytext);  
 
%%


//------------------------------------------------------------------------
void _clp_tokenize(int argno)
{
    CCC_PROLOG("tokenize",1);
  
    str2bin(base);
    buffer=_parb(1);
    buflen=_parblen(1);
    bufidx=0;
    item_count=0;

    xtlex();
    array(item_count);
    _rettop();

    CCC_EPILOG();
}

//------------------------------------------------------------------------
static void xtlexstore(const char*txt) 
{
    binaryn(txt);
    item_count++;
}

//------------------------------------------------------------------------
static void xtlextrim(char*txt) 
{
    while( (*txt==' ') || (*txt=='\t') )
    {
        txt++;
    }

    char buf[2]; buf[0]=*txt; buf[1]=0;

    binaryn(buf);
    item_count++;
}
 
//------------------------------------------------------------------------
