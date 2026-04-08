
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


