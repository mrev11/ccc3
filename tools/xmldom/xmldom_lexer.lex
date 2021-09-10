
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
#define XMLDOM_LEXER
#include <xmldom_lexer.h>
%}

%x comment tag cdata doctype

%option c++
%option yyclass="xmldom_lexer"
%option noyywrap
%option stack
%option yylineno
%option prefix="xmldom"

symbol     [_a-zA-Z][\.\-:_a-zA-Z0-9]*
string     "\""[^\"]*"\""|"\'"[^\']*"\'" 
wspace     [ \t\r\n]*
dec        [0-9]+ 
hex        [0-9a-fA-F]+ 


%%

"<#ROOT#>"       {return ROOT;} 
[^<]             {cat();}
"&amp;"          {entityconversionflag ? cat("&")  : cat();}
"&lt;"           {entityconversionflag ? cat("<")  : cat();}
"&gt;"           {entityconversionflag ? cat(">")  : cat();}
"&quot;"         {entityconversionflag ? cat("\"") : cat();}
"&apos;"         {entityconversionflag ? cat("\'") : cat();}

"&#"{dec}";"     {entityconversionflag ? code()    : cat();}
"&#x"{hex}";"    {entityconversionflag ? code()    : cat();}

[^<]/"<"         {cat(); if(trim()) return TEXT;}
"&amp;"/"<"      {entityconversionflag ? cat("&")  : cat(); return TEXT;}
"&lt;"/"<"       {entityconversionflag ? cat("<")  : cat(); return TEXT;}
"&gt;"/"<"       {entityconversionflag ? cat(">")  : cat(); return TEXT;}
"&quot;"/"<"     {entityconversionflag ? cat("\"") : cat(); return TEXT;}
"&apos;"/"<"     {entityconversionflag ? cat("\'") : cat(); return TEXT;}

"&#"{dec}";"/"<" {entityconversionflag ? code()    : cat(); return TEXT;}
"&#x"{hex}";"/"<" {entityconversionflag ? code()   : cat(); return TEXT;}


"<![CDATA["      {yy_push_state(cdata);}
<cdata>{
"]]>"            {yy_pop_state(); return CDATA;}  
.|\n             {cat();}  
}


"<!--"           {yy_push_state(comment);}
<comment>{
"-->"            {yy_pop_state();}
.|\n             {} 
}

"<!DOCTYPE"      {yy_push_state(doctype);}
<doctype>{
{string}         {}  
">"              {yy_pop_state();}
.|\n             {} 
}
 

"<"              {yy_push_state(tag); initialwspace=0; return LPAR;}
"<?"             {yy_push_state(tag); return LPARQM;}
<tag>{
">"              {yy_pop_state(); return RPAR;} 
"/>"             {yy_pop_state(); return SLRPAR;} 
"?>"             {yy_pop_state(); return QMRPAR;} 
{symbol}         {cat(); return SYMBOL;}  
{string}         {cat(); return STRING;}  
{wspace}         {}
"/"              {return SLASH;}
"="              {return EQ;}

.                {
                    char desc[256]; 
                    sprintf(desc,"unexpected char (%s) near #line %d",YYText(),lineno());
                    _clp_xmlsyntaxerrornew(0);
                    dup();stringnb("XMLDOM");_o_method_subsystem.eval(2);pop();
                    dup();stringnb("xmldom_lexer");_o_method_operation.eval(2);pop();
                    dup();stringnb(desc);_o_method_description.eval(2);pop();
                    dup();number(1);_o_method_subcode.eval(2);pop();
                    if( inputfspec )
                    {
                        dup();stringnb(inputfspec);_o_method_filename.eval(2);pop();
                    }
                    _clp_break(1);
                    pop();
                }
}

<<EOF>>         {return trim()?TEXT:0;}

%%



