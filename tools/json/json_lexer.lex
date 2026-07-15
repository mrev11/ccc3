
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
#define JSON_LEXER
#include <json_lexer.h>
%}


%option c++
%option yyclass="json_lexer"
%option noyywrap
%option yylineno
%option stack
%option prefix="json"


number           ("+"|"-"|"")[0-9]+("."[0-9]+|"")
string           "\""([^\"]|"\\\"")*"\""
ws               [ \t\n]*
                 
%%

{string}         {cat(); return STRING;}
{number}         {cat(); return NUMBER;}
"true"           {cat(); return TRUE;}
"false"          {cat(); return FALSE;}
"null"           {cat(); return NuLL;}

"{"              {cat(); return LBRACE;}
"}"              {cat(); return RBRACE;}
"["              {cat(); return LBRACKET;}
"]"              {cat(); return RBRACKET;}
","              {cat(); return COMMA;}
":"              {cat(); return COLON;}
\n
\t
" "
.                {printf("Syntax error at line %d [%s]\n",yylineno, YYText()); return 0;  }


%%


