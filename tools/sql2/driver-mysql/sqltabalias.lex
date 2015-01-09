
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

// Megkeresi a 
// ... join ((...( tabalias ...
// környezetben előforduló alias szimbólumot,
// visszaadja az előfordulás pozícióját.

#include <string.h>
#include <cccapi.h>

namespace _nsp_sql2 {
namespace _nsp_mysql {

struct sqltabalias_lexer : public yyFlexLexer
{
  protected:

    char *input;
    char *inputptr;
    int inputsize;
    int inputpos;
    char *searchsym;

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
    
    sqltabalias_lexer(char *ptr, int size, char *srch)
    {
        input=ptr;
        inputptr=ptr;
        inputsize=size;
        inputpos=0;
        searchsym=srch;
    }

    ~sqltabalias_lexer()
    {
        //Flex hiba javítása.
        if( yy_start_stack )
        {
            free(yy_start_stack);
            yy_start_stack=0;
        }
    } 
};

void _clp_sqltabalias(int argno)
{
    CCC_PROLOG("sqltabalias",2);
    char *join=_parcb(1);
    int leng=_parblen(1);
    char *alias=_parcb(2);
    sqltabalias_lexer lexer(join,leng,alias);
    int pos=lexer.yylex(); //UTF-8 kódolásban

    int i=0,ucs=0,len=0; 
    while( i<pos )
    {
        len++;
        i+=utf8_to_ucs(join+i,&ucs);
    }
    _retni( len  ); //UCS kódolásban
    CCC_EPILOG();

    //A lex elemző byteokon tud működni,
    //azért a karaktereket UTF-8 kódolású bytera kell alakítani,
    //így pos az UTF-8 kódolású stringben talált pozíció,
    //végül megszámoljuk, hogy pos-ig hány UCS kód van.
}

}} //namespace

%}


%option c++
%option yyclass="_nsp_sql2::_nsp_mysql::sqltabalias_lexer"
%option noyywrap
%option stack
%option prefix="_sql2_mysql_sqltabalias"

join       [Jj][Oo][Ii][Nn]
lpar       [( \n\r\t]*
symbol     [_a-zA-Z][\._a-zA-Z0-9]*

%%

{join}{lpar}{symbol}    {
                            const char *p=YYText();
                            const char *q=p+YYLeng()-1; //symbol vége
                            while( q>p && 
                                   *q!='(' && *q!=' ' &&
                                   *q!='\n' && *q!='\r' && *q!='\t' )
                            {
                                q--;
                            }
                            q++; //symbol eleje
                            
                            if( strcasecmp(q,searchsym)==0 )
                            {
                                return inputpos+(q-p+1);
                            }
                            else
                            {
                                inputpos+=YYLeng();
                            }
                        }

.                       {inputpos+=YYLeng();}
\n                      {inputpos+=YYLeng();}

%%


