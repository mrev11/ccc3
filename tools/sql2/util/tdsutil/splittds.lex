
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
#ifdef EMLEKEZTETO

Bekezdésekre darabol egy tds scriptet, 
ahol egy bekezdés így néz ki:

column: tetsz. szöveg -- megjegyzés
-- megjegyzés
            tetsz. szöveg   ; megjegyzés

Minden bekezdés a következő bekezdésig tart.
A sorok "--" utáni része megjegyzés, amit az elemző kihagy.
A bekezdések ";" utáni része megjegyzés, amit az elemző kihagy.
A bekezdéseket a következő kezdő szimbólumok vezetik be:

name:
version:
table:
join:
column:
colref:
primkey:
index:
select:
type:
include:
comment:

A soremeléseket, tabokat space-ekkel helyettesíti.
Idézeten kívül összevonja a space-eket.
Visszaad egy arrayt, ami a bekezdéseket tartalmazza.

#endif


#include <cccapi.h>

namespace _nsp_tdsutil{

struct tds2prg_splittds : public yyFlexLexer
{
  protected:

    char *inputptr;
    int inputsize;
    int semicol;

    int LexerInput(char *buf, int maxsize)
    {
        int retsize=0;
        while( (inputsize>0) && (maxsize>0) )
        {
            *buf++=*inputptr++;
            inputsize--;
            maxsize--;
            retsize++;
        }
        return retsize;
    }

  public:
    
    int yylex(); //Flex definiálja, de nem deklarálja.

    int entrycnt;
    
    tds2prg_splittds(char *script, int size)
    {
        inputptr=script;
        inputsize=size;
        entrycnt=0;
        semicol=1;
    }

    ~tds2prg_splittds()
    {
        //Flex hiba javítása.
        if( yy_start_stack )
        {
            free(yy_start_stack);
            yy_start_stack=0;
        }
    } 
};

void _clp_splittds(int argno)
{
    CCC_PROLOG("splittds",1);
    char *tds=_parcb(1);
    int leng=_parblen(1);
    if( leng )
    {
        tds2prg_splittds lexer(tds,leng);
        lexer.yylex();
        array(lexer.entrycnt);
    }
    else
    {
        array(0);
    }
    _rettop();
    CCC_EPILOG();
}

} //namespace

%}


%option c++
%option yyclass="_nsp_tdsutil::tds2prg_splittds"
%option noyywrap
%option stack
%option prefix="splittds"

entry   "name"|"version"|"table"|"join"|"column"|"colref"|"primkey"|"index"|"select"|"type"|"include"|"comment"
string1 "\'"[^\'\n]*"\'"
string2 "\""[^\"\n]*"\""
comment --.*\n

%%

{comment}
;                   {semicol=1;}
^{entry}:           {semicol=0;entrycnt++;stringnb(YYText());}
[\r\t\n ]+          {if(semicol==0){stringnb(" ");add();}}
{string1}           {if(semicol==0){stringnb(YYText());add();}}
{string2}           {if(semicol==0){stringnb(YYText());add();}}
[^\r\t\n \-\'\":;]+ {if(semicol==0){stringnb(YYText());add();}}
.                   {if(semicol==0){stringnb(YYText());add();}}

%%


