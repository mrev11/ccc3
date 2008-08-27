
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

#include <malloc.h>
#include <string.h>
#include <stdio.h>

#define INCLUDED_FROM_LEXER_LEX
#include <lexer.h>

%}

%x line raw sym

%option c++
%option yyclass="ppo2cpp_lexer"
%option noyywrap
%option stack
%option yylineno


wspace          [ \t\r]*
hex             [0-9a-fA-F]
symtrail        {wspace}"("|"."
symtraildot     {wspace}"."
symtrailpar     {wspace}"("
number          [0-9]+("."[0-9]+|"")
numberb         [0][bB][01]+
numberx         [0][xX]{hex}+
symbol          [_a-zA-Z][_a-zA-Z0-9]*
dsym            {symbol}(.{symbol})*
string          "\""[^\"]*"\""|"\'"[^\']*"\'"
binarya         a{string}
binaryx         [xX]("\""({hex}{hex})*"\""|"\'"({hex}{hex})*"\'")
comment         "//".*"\n"

or              [oO][rR] 
and             [aA][nN][dD]
not             [nN][oO][tT]

function        [fF][uU][nN][cC][tT][iI][oO][nN]
procedure       [pP][rR][oO][cC][eE][dD][uU][rR][eE]
static          [sS][tT][aA][tT][iI][cC] 
local           [lL][oO][cC][aA][lL] 
quit            [qQ][uU][iI][tT]
nil             [nN][iI][lL]
return          [rR][eE][tT][uU][rR][nN]

class           [cC][lL][aA][sS][sS]
new             [nN][eE][wW]
attrib          [aA][tT][tT][rR][iI][bB]
method          [mM][eE][tT][hH][oO][dD]

do              [dD][oO]
while           [wW][hH][iI][lL][eE]
exit            [eE][xX][iI][tT]
loop            [lL][oO][oO][pP]
end             [eE][nN][dD]
enddo           [eE][nN][dD][dD][oO]
endwhile        [eE][nN][dD][wW][hH][iI][lL][eE]

for             [fF][oO][rR]
to              [tT][oO]
step            [sS][tT][eE][pP]
next            [nN][eE][xX][tT]
endfor          [eE][nN][dD][fF][oO][rR]

if              [iI][fF]
elseif          [eE][lL][sS][eE][iI][fF]
else            [eE][lL][sS][eE]
endif           [eE][nN][dD][iI][fF]

case            [cC][aA][sS][eE]
otherwise       [oO][tT][hH][eE][rR][wW][iI][sS][eE]
endcase         [eE][nN][dD][cC][aA][sS][eE]

begin           [bB][eE][gG][iI][nN]
sequence        [sS][eE][qQ][uU][eE][nN][cC][eE]
recover         [rR][eE][cC][oO][vV][eE][rR]
using           [uU][sS][iI][nN][gG]
finally         [fF][iI][nN][aA][lL][lLl][yY]
namespace       [nN][aA][mM][eE][sS][pP][aA][cC][eE]

%%

"#line"                             {yy_push_state(line);}
<line>{
{number}                            {setinputlineno();}
{string}                            {setinputfspec();}
{wspace}                            {} 
"\n"                                {yy_pop_state();} 
}

"<<"{symbol}">>"                    {yy_push_state(raw);raw_set();}
<raw>{
"<<"{symbol}">>"                    {if(raw_cmp()){yy_pop_state();return STRING;}}
"\\"                                {raw_cat("\\\\");}
"\""                                {raw_cat("\\\"");}
"\n"                                {raw_cat("\\n\"\nL\"");/*darabol*/}
.                                   {raw_cat();}
}

"."                                 {return DOT;} 
".."                                {return DOTDOT;} 
","                                 {return COMMA;} 
":"                                 {return COLON;} 
"::"                                {return COLCOL;} 
":="                                {return ASSIGN;} 
"+="                                {return ADDASS;} 
"-="                                {return SUBASS;} 
"*="                                {return MULASS;} 
"/="                                {return DIVASS;} 
"%="                                {return MODASS;} 
"::="                               {return COLCOLASS;} 
"="                                 {return EQ;} 
"=="                                {return EQEQ;} 
">="                                {return GTEQ;} 
"<="                                {return LTEQ;} 
"!="|"<>"                           {return EXEQ;} 
">"                                 {return GT;} 
"<"                                 {return LT;} 
"$"                                 {return DOLLAR;} 
"+"                                 {return PLUS;} 
"-"                                 {return MINUS;} 
"*"                                 {return STAR;} 
"/"                                 {return SLASH;} 
"%"                                 {return MODULO;} 
"**"|"^"                            {return DBSTAR;} 
"++"                                {return DBPLUS;} 
"--"                                {return DBMINUS;} 
"["                                 {return LBRACKET;} 
"->"                                {return ARROW;} 
"("                                 {return LPAR;} 
")"                                 {return RPAR;} 
"@"                                 {return AT;} 
"{"                                 {return LBRACE;} 
"|"                                 {return PIPE;} 
"}"                                 {return RBRACE;} 
"]"                                 {return RBRACKET;} 
"."[tT]"."                          {return TRUE;} 
"."[fF]"."                          {return FALSE;} 
"."{or}"."                          {return OR;} 
"."{and}"."                         {return AND;} 
"."{not}"."|"!"                     {return NOT;} 

{function}                          {return FUNCTION;} 
{procedure}                         {return FUNCTION;} 
{static}{wspace}{function}          {return STFUNCTION;} 
{static}{wspace}{procedure}         {return STFUNCTION;} 
{static}                            {return STATIC;} 
{local}                             {return LOCAL;} 
{quit}                              {return QUIT;} 
{nil}                               {return NIL;} 
{return}                            {return RETURN;} 

{class}                             {return CLASS;}
{new}                               {return NEW;}
{attrib}                            {yy_push_state(sym); return ATTRIB;}
{method}                            {yy_push_state(sym); return METHOD;}
<sym>{
{symbol}                            {yy_pop_state();return SYMBOL;}
{wspace}                            {}
.                                   {return UNEXPECTEDCHAR;}
}

{do}{wspace}{while}                 {return WHILE;}
{while}                             {return WHILE;}
{exit}                              {return EXIT;}
{loop}                              {return LOOP;}
{end}                               {return END;}
{enddo}                             {return END;}
{endwhile}                          {return END;}

{for}                               {return FOR;}
{to}                                {return TO;}
{step}                              {return STEP;}
{next}                              {return END;}
{endfor}                            {return END;}

{if}                                {return IF;} 
{elseif}                            {return ELSEIF;} 
{else}                              {return ELSE;} 
{endif}                             {return END;} 

{do}{wspace}{case}                  {return DOCASE;} 
{case}                              {return CASE;} 
{otherwise}                         {return OTHERWISE;} 
{endcase}                           {return END;} 

{begin}                             {return BEGSEQ;}
{begin}{wspace}{sequence}           {return BEGSEQ;}
{recover}                           {return RECOVER;} 
{recover}{wspace}{using}            {return RECOVER;} 
{finally}                           {return FINALLY;}
{end}{wspace}{sequence}             {return END;} 
{namespace}                         {return NAMESPACE;} 
{using}                             {return USING;} 

";"                                 {return NL;}
"\n"                                {incinputlineno();return NL;}
{comment}                           {incinputlineno();return NL;}

{string}                            {return STRING;} 
"@"{string}                         {return NLSTEXT;} 
{binarya}                           {return BINARYA;}
{binaryx}                           {return BINARYX;}
{number}                            {return NUMBER;} 
{numberx}                           {return NUMBER;} 
{numberb}                           {return NUMBER;} 
{symbol}                            {return SYMBOL;} 

"."{symbol}                         {return COMPOUND;} 
":"{symbol}                         {return COMPOUND;}
"::"{symbol}                        {return COMPOUND;}
"::="{symbol}                       {return COMPOUND;}
":("{dsym}")"{symbol}               {return COMPOUND;}
":("{dsym}"@"{dsym}")"{symbol}      {return COMPOUND;}
{symbol}"->"{symbol}                {return COMPOUND;}

{function}/{symtrail}               {return SYMBOL;}
{procedure}/{symtrail}              {return SYMBOL;}
{static}/{symtrail}                 {return SYMBOL;}
{local}/{symtrail}                  {return SYMBOL;}
{quit}/{symtrail}                   {return SYMBOL;}
{nil}/{symtrailpar}                 {return SYMBOL;}
{class}/{symtrail}                  {return SYMBOL;}
{new}/{symtrail}                    {return SYMBOL;}
{attrib}/{symtrail}                 {return SYMBOL;}
{method}/{symtrail}                 {return SYMBOL;}
{exit}/{symtrail}                   {return SYMBOL;}
{loop}/{symtrail}                   {return SYMBOL;}
{end}/{symtrail}                    {return SYMBOL;}
{enddo}/{symtrail}                  {return SYMBOL;}
{endwhile}/{symtrail}               {return SYMBOL;}
{for}/{symtrail}                    {return SYMBOL;}
{to}/{symtraildot}                  {return SYMBOL;}
{step}/{symtraildot}                {return SYMBOL;}
{next}/{symtrail}                   {return SYMBOL;}
{endfor}/{symtrail}                 {return SYMBOL;}
{else}/{symtrail}                   {return SYMBOL;}
{endif}/{symtrail}                  {return SYMBOL;}
{otherwise}/{symtrail}              {return SYMBOL;}
{endcase}/{symtrail}                {return SYMBOL;}
{begin}/{symtrail}                  {return SYMBOL;}
{recover}/{symtrail}                {return SYMBOL;}
{finally}/{symtrail}                {return SYMBOL;}
{namespace}/{symtrail}              {return SYMBOL;}
{using}/{symtrail}                  {return SYMBOL;}

{wspace}                            {}
.                                   {return UNEXPECTEDCHAR;}

%%

