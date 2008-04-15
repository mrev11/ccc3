
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

#include <fcntl.h>
#include <xmldom_lexer.h>

extern void* xmldom_parserAlloc(void*(*)(size_t)); 
extern void  xmldom_parserFree(void*,void(*)(void*)); 
extern void  xmldom_parserTrace(FILE*,const char*); 
extern void  xmldom_parser(void*,int,wchar_t*,xmldom_lexer*);  //3th arg: %token_type {char*} 

DEFINE_METHOD(file);
DEFINE_METHOD(entityconv);
DEFINE_METHOD(debug);

//---------------------------------------------------------------------------
void _clp__xmldom_parser_parseinput(int argno)
{
    CCC_PROLOG("_xmldom_parser_parseinput",2);
    
    xmldom_lexer *lexer=0;
    if( ISBINARY(2) )
    {
        lexer=new xmldom_lexer(_parb(2)); //string-ből olvas
    }
    else if( ISSTRING(2) )
    {
        str2bin(base+1); //2007.10.24 -- 1.2.03
        lexer=new xmldom_lexer(_parb(2)); //string-ből olvas
    }
    else if( ISNUMBER(2) )
    {
        lexer=new xmldom_lexer(_parni(2)); //fdesc-ből olvas
    }
    else
    {
        ARGERROR();
    }
    
    int ecf;
        push_symbol(base);_o_method_entityconv.eval(1);
        ecf=(TOP()->type==TYPE_FLAG) ? TOP()->data.flag:0; pop();

    int dbg;
        push_symbol(base);_o_method_debug.eval(1);
        dbg=(TOP()->type==TYPE_FLAG) ? TOP()->data.flag:0; pop();

    char *fnm;
        push_symbol(base);_o_method_file.eval(1);
        str2bin(TOP());
        fnm=(TOP()->type==TYPE_BINARY) ? BINARYPTR(TOP()):0; pop();

    lexer->entityconversionflag=ecf; //&amp;, &lt;, stb. konvertálása
    lexer->inputfspec=fnm; //filénév hibaüzenethez
    lexer->debugflag=dbg; //debugolás beállítása
    
    void *parser=xmldom_parserAlloc(malloc);
    if( dbg )
    {
        xmldom_parserTrace(stdout,">> ");
    }
    
    push_symbol(base); //PRS (xmlPaRS) objektum
    array(0); //LST (Lemon STack) array

    int id;
    wchar_t *token;
    while( 0!=(id=lexer->getnext(&token)) )
    {
        xmldom_parser(parser,id,token,lexer);
    }

    xmldom_parser(parser,0,0,lexer);
    xmldom_parserFree(parser,free);
    delete lexer;
    
    _rettop();

    CCC_EPILOG();
}

//---------------------------------------------------------------------------
