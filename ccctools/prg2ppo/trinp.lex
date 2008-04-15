
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
//Ez a flex program végzi az xtranslate-ek töltését
 
#include <stdio.h>
#include <cccapi.h>
#include "xtrans.ch"
 
#define YY_NEVER_INTERACTIVE  1

#define YY_INPUT(buf,result,max_size)\
  { result = (bufidx<buflen) ?\
             (buf[0]=buffer[bufidx++],1) :\
             YY_NULL; }


extern void      error(const char *txt);
static void      store_text(const char *txt);
static void      store_flag(int flag);

static void      markreg(void);
static void      marklst(void);
static void      markrst(void);
static void      markwld(void);
static void      markext(void);
static void      markdmb(void);
static void      markstr(void);
static void      markblk(void);
static void      marklog(void);

 
static int       item_count=0;
static int       arrow=0;

static char      *buffer;
static unsigned  buflen;
static unsigned  bufidx;

%}

%option noyywrap
%option prefix="tri"


hex        [0-9a-fA-F]
number     [0-9]+("."[0-9]+|"")
numberb    [0][bB][01]+
numberx    [0][xX]{hex}+
symbol     [_a-zA-Z][_a-zA-Z0-9]*
string     ("\""[^\"\n]*"\""|"\'"[^\'\n]*"\'")
binarya    a{string}
binaryx    [xX]("\""({hex}{hex})*"\""|"\'"({hex}{hex})*"\'")
logical    "."(f|F|t|T|and|AND|And|or|OR|Or|not|NOT|Not)"." 
wspace     [ \t]*
arrow      "=>"[ \t]* 
escaped    ("\\["|"\\]"|"\\<"|"\\>"|"\\\""|"\\\'"|"\\\\"|"\\#")
glue       [ \t]*"##"[ \t]* 
sep        "/**/"
 
markreg    <{symbol}>
marklst    <{symbol}",...>"
markrst    <{symbol}:[^>\n]*>
markwld    "<*"{symbol}"*>"
markext    "<("{symbol}")>"
markdmb    "#<"{symbol}">"
markstr    "<\""{symbol}"\">" 
markblk    "<{"{symbol}"}>"
marklog    "<."{symbol}".>"

%%


{markreg}       markreg();
{marklst}       marklst();
{markrst}       markrst();
{markwld}       markwld();
{markext}       markext();
 
{markdmb}       markdmb();
{markstr}       markstr();
{markblk}       markblk();
{marklog}       marklog();
 
{symbol}        store_text(yytext);
{number}        store_text(yytext);
{numberb}       store_text(yytext);
{numberx}       store_text(yytext);
{string}        store_text(yytext); 
{binarya}       store_text(yytext); 
{binaryx}       store_text(yytext); 
{logical}       store_text(yytext); 
{escaped}       store_text(yytext+1);  
{wspace}        if(arrow) store_text(" ");
"["             store_flag(1);
"]"             store_flag(0);
{arrow}         array(item_count);item_count=0;arrow=1;
\n              store_text(yytext);
{glue}          store_text("##"); 
{sep}           store_text("##"); 
.               store_text(yytext);
 
%%


//------------------------------------------------------------------------
void _clp_token_translate(int argno)
{
    CCC_PROLOG("token_translate",1);

    buffer     = _parb(1);
    buflen     = _parblen(1);
    bufidx     = 0;

    arrow      = 0;
    item_count = 0;
 
    yylex();
    
    if( !arrow )
    {
        error("Translate without =>");
    
    }
    array(item_count);
    push(&NIL);
    array(3);
    _rettop();

    CCC_EPILOG();
}


//------------------------------------------------------------------------
static void store_text(const char*txt) 
{
    binaryn(txt);
    item_count++;
}
 
//------------------------------------------------------------------------
static void store_flag(int flag) 
{
    logical(flag);
    item_count++;
}
 
//------------------------------------------------------------------------
static void markreg()
{
    //<id>
    
    binarys(yytext+1,yyleng-2);
    number(MATCH_REGULAR*1000);
    array(2);
    item_count++;
}

//------------------------------------------------------------------------
static void marklst()
{
    //<id,...>

    if( arrow ) //jobboldal
    {
        error("List marker not allowed on the right side");
    }
    
    binarys(yytext+1,yyleng-6);
    number(MATCH_LIST*1000);
    array(2);
    item_count++;
}

//------------------------------------------------------------------------
static void markrst()
{
    //<id: w1,w2,w3>
    
    if( arrow ) //jobboldal
    {
        error("Restricted marker not allowed on the right side");
    }
    
    char *p=yytext;
    while( *p!=':' ) p++;
    *p=(char)0;
    binaryn(yytext+1);

    number(MATCH_RESTRICTED*1000);
    
    char *q=p;
    while( *q!='>' ) q++;
    *q=(char)0;
    binaryn(p+1);
    
    array(3);
    item_count++;
}
 
//------------------------------------------------------------------------
static void markwld()
{
    //<*id*>

    if( arrow ) //jobboldal
    {
        error("Wild marker not allowed on the right side");
    }

    binarys(yytext+2,yyleng-4);
    number(MATCH_WILD*1000);
    array(2);
    item_count++;
}
 
//------------------------------------------------------------------------
static void markext()
{
    //<(id)> == smart marker a jobboldalon

    if( !arrow ) //baloldal: extended match marker
    {
        binarys(yytext+2,yyleng-4);
        number(MATCH_EXTENDED*1000);
    }
    else //jobboldal: smart stringify result marker
    {
        binarys(yytext+2,yyleng-4);
        number(RESULT_SMARTSTR*1000);
    }
    array(2);
    item_count++;
}
 
//------------------------------------------------------------------------
static void markdmb()
{
    //#<id>
    if( !arrow )
    {
        error("Dumb marker not allowed on the left side");
    }
    
    binarys(yytext+2,yyleng-3);
    number(RESULT_DUMBSTR*1000);
    array(2);
    item_count++;
}
 
//------------------------------------------------------------------------
static void markstr()
{
    //<"id">

    if( !arrow )
    {
        error("String marker not allowed on the left side");
    }
 
    binarys(yytext+2,yyleng-4);
    number(RESULT_NORMALSTR*1000);
    array(2);
    item_count++;
}
 
 
//------------------------------------------------------------------------
static void markblk()
{
    //<{id}>

    if( !arrow )
    {
        error("Block marker not allowed on the left side");
    }
 
    binarys(yytext+2,yyleng-4);
    number(RESULT_BLOCKIFY*1000);
    array(2);
    item_count++;
}
 
//------------------------------------------------------------------------
static void marklog()
{
    //<.id.>

    if( !arrow )
    {
        error("Logical marker not allowed on the left side");
    }
    
    binarys(yytext+2,yyleng-4);
    number(RESULT_LOGIFY*1000);
    array(2);
    item_count++;
}

//------------------------------------------------------------------------

