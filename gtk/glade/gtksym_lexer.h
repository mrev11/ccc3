
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

#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#ifndef GTKSYM_LEXER 
#undef  yyFlexLexer
#define yyFlexLexer gtksymFlexLexer
#include <flexlexer.h>
#endif

#include <gtksym_parser.h>


struct gtksym_lexer : public yyFlexLexer
{
  protected:

    char *input;
    char *inputptr;
    int inputsize;
    int eofflag;

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

    int value;
  
    int getnext(int *token)
    {
        if( eofflag )
        {
            *token=0;
            return 0;
        }
        
        value=0;
        int id=yylex();
        
        if( id==0 )
        {
            eofflag=1;
            *token=0;
            return 0;
        }
        
        *token=value;
        return id;
    }
    
    int yylex(); //Flex definiálja, de nem deklarálja.
    
    gtksym_lexer(char *ptr, int size)
    {
        input=ptr;
        inputptr=ptr;
        inputsize=size;
        eofflag=0;
    }

    ~gtksym_lexer()
    {
        //Flex hiba javítása.
        if( yy_start_stack )
        {
            free(yy_start_stack);
            yy_start_stack=0;
        }
    } 
};
