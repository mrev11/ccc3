
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
extern void  xmldom_parser(void*,int,CHAR*,VALUE*);

DEFINE_METHOD(file);
DEFINE_METHOD(entityconv);
DEFINE_METHOD(preservespace);
DEFINE_METHOD(debug);
DEFINE_METHOD(lexer);
DEFINE_METHOD(lemparser);

//---------------------------------------------------------------------------
void _clp__xmldom_parser_parseinput(int argno)
{
    CCC_PROLOG("_xmldom_parser_parseinput",4);  
    
    if(!ISOBJECT(1)){ARGERROR();}               //1: parser
    VALUE *parservp=base+0;

    str2bin(base+1);                            //2: inpstr/NIL
    char *inpstr=ISNIL(2)?0:_parb(2);
    int size=ISNIL(2)?0:_parblen(2);

    if(!ISBLOCK(3)&&!ISNIL(3)){ARGERROR();}     //3: inpblk/NIL
    VALUE *inpblk=ISNIL(3)?0:base+2;

    int fd=ISNIL(4)?-1:_parni(4);               //4: fd/NIL


    xmldom_lexer *lexer=new xmldom_lexer(parservp,inpstr,size,inpblk,fd);

    int ecf;
        push(parservp);_o_method_entityconv.eval(1);
        ecf=(TOP()->type==TYPE_FLAG) ? TOP()->data.flag:0; pop();

    int psp;
        push(parservp);_o_method_preservespace.eval(1);
        psp=(TOP()->type==TYPE_FLAG) ? TOP()->data.flag:0; pop();

    int dbg;
        push(parservp);_o_method_debug.eval(1);
        dbg=(TOP()->type==TYPE_FLAG) ? TOP()->data.flag:0; pop();

    char *fnm;
        push(parservp);_o_method_file.eval(1);
        str2bin(TOP());
        fnm=(TOP()->type==TYPE_BINARY) ? BINARYPTR(TOP()):0; pop();

    lexer->entityconversionflag=ecf; //&amp;, &lt;, stb. konvertálása
    lexer->preservespace=psp; //space-ek megőrzése
    lexer->inputfspec=fnm?strdup(fnm):0; //filénév hibaüzenethez
    lexer->debugflag=dbg; //debugolás beállítása

    void *parser=xmldom_parserAlloc(malloc);
    if( dbg )
    {
        xmldom_parserTrace(stdout,">> ");
    }

    push(parservp); // xmlparser:lexer beállítása
    pointer(lexer);
    _o_method_lexer.eval(2);
    pop();

    push(parservp); // xmlparser:lemparser beállítása
    pointer(parser);
    _o_method_lemparser.eval(2);
    pop();

    
    int id;
    CHAR *token;
    while( 0!=(id=lexer->getnext(&token)) )
    {
        xmldom_parser(parser,id,token,parservp);
    }

    xmldom_parser(parser,0,0,parservp);
    xmldom_parserFree(parser,free);
    delete lexer;

    push(parservp); // xmlparser:lexer törlése
    PUSHNIL();
    _o_method_lexer.eval(2);
    pop();

    push(parservp); // xmlparser:lemparser törlése
    PUSHNIL();
    _o_method_lemparser.eval(2);
    pop();
    
    _rettop();

    CCC_EPILOG();
}

//---------------------------------------------------------------------------
// Ha az xml elemzés közben kivétel keletkezik,
// akkor is törölni kell a lemon parsert és lexert,
// máskülönben a rossz filék elemzése fogyasztja a memóriát.
// A CCC parser tárolja a lemon parser és a lexer pointerét,
// és a finally ágból törli őket. Ha az elemzés végigfutott, 
// akkor ez a törlés már nem csinál semmit.
//---------------------------------------------------------------------------
void _clp__xmldom_parser_clean_lexer(int argno)
{
    CCC_PROLOG("_xmldom_parser_clean_lexer",1);
    if( !ISNIL(1) )
    {
        xmldom_lexer *lexer=(xmldom_lexer *)_parp(1);
        delete lexer;
    }

    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp__xmldom_parser_clean_parser(int argno)
{
    CCC_PROLOG("_xmldom_parser_clean_parser",1);
    if( !ISNIL(1) )
    {
        void *parser=_parp(1);
        xmldom_parserFree(parser,free);
    }
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
