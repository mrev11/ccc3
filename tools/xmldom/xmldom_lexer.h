
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
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#ifdef WIN32
#include <io.h>
#endif

#ifndef XMLDOM_LEXER 
#undef  yyFlexLexer
#define yyFlexLexer xmldomFlexLexer
#include <flexlexer.h>
#endif

#include <cccapi.h>

#include <xmldom_parser.h>

#ifdef _CCC3_
#include <latin2.h>
#endif

DEFINE_METHOD(subsystem);
DEFINE_METHOD(operation);
DEFINE_METHOD(description);
DEFINE_METHOD(filename);
DEFINE_METHOD(oscode);
DEFINE_METHOD(subcode);
DEFINE_METHOD(args);
DEFINE_METHOD(process);

#define BUFINC  1024


class xmldom_lexer : public yyFlexLexer
{
  protected:

    int LexerInput(char *buf, int maxsiz)
    {
        if( inputfd>=0 )
        {
            return read(inputfd,buf,maxsiz);
        }
        else if( inputptr!=0 && *inputptr!=0 )
        {
            *buf=*inputptr++;
            return 1;
        }
        else
        {
            return 0;
        }
    }

  public:

    int inputfd;
    char *inputptr;
    char *inputfspec;
    int entityconversionflag;
    int eofflag;
    int debugflag;

    int encoding; //0==UTF-8, 1==ISO-8859-1, 2==ISO-8859-2, -1=ismeretlen
    char *text;
    int textsize;
    int buffersize;


    int yylex(); //Flex definiálja, de nem deklarálja.

    void cat()
    {
        int len=YYLeng();
        char *txt=(char*)YYText();

        if( textsize+len+1>buffersize )
        {
            text=(char*)realloc(text,buffersize+=(len+BUFINC));
        }
        memcpy(text+textsize,txt,len+1);
        textsize+=len;
    }

    void cat(const char *txt)
    {
        int len=strlen(txt);
        if( textsize+len+1>buffersize )
        {
            text=(char*)realloc(text,buffersize+=(len+BUFINC));
        }
        memcpy(text+textsize,txt,len+1);
        textsize+=len;
    }


    int trim()
    {
        while( (textsize>0) && isspace(text[textsize-1]) )
        {
            text[textsize-1]=0;
            textsize--;
        }
        return textsize>0;
    }

    int getnext(wchar_t **token)
    {
        *token=0;
        
        if( eofflag )
        {
            return 0;
        }
    
        if( buffersize>BUFINC )
        {
            text=(char*)realloc(text,buffersize=BUFINC);
        }
        textsize=0;
        *text=0;


        int id=yylex();

        if( id==0 )
        {
            eofflag=1;
            return 0; //nincs több bemenet       
        }
        
        if( debugflag )
        {
            printf("LEX %2d [%s]\n",id,text);
        }
        
        if( *text )
        {
        #ifdef _CCC2_
            *token=strdup(text);
        #else  

            //printf("encoding=%d\n",encoding);

            if( encoding==0 ) //UTF-8 (default)
            {
                *token=utf8_to_wchar(text,textsize,0);
            }

            else if( encoding==2 ) //Latin-2
            {
                *token=(wchar_t*)malloc((textsize+1)*sizeof(wchar_t));
                int i;
                for(i=0; i<textsize; i++)
                {
                   *(*token+i)=(wchar_t)latin2[(unsigned)*(text+i)];
                }
                *(*token+i)=(wchar_t)0;
            }

            else //if( encoding==1 ) //Latin-1 (és minden más)
            {
                *token=(wchar_t*)malloc((textsize+1)*sizeof(wchar_t));
                int i;
                for(i=0; i<textsize; i++)
                {
                   *(*token+i)=(wchar_t)*(text+i); //triviális 8bit -> 32bit
                }
                *(*token+i)=(wchar_t)0;
            }

            //Csak UTF-8, Latin-1 és Latin-2 támogatás van. 
            //Minden más kódolás úgy konvertálódik, mint a Latin-1.
            //Nem foglalkozunk a szabvány szerint érvénytelen kódokkal.
        #endif
        }
        return id;
    }
    
    void init()
    {
        inputfd=-1;
        inputptr=0;
        inputfspec=0;
        entityconversionflag=0;
        eofflag=0;
        debugflag=0;
        encoding=0;
        text=(char*)malloc(buffersize=BUFINC);
        textsize=0;
        *text=0;
    }
    
    void setencoding(char *enc)
    {
        //printf("setencoding: %s\n",enc);

        if( strcasecmp("UTF-8",enc)==0 )
        {
            encoding=0;
        }
        else if( strcasecmp("ISO-8859-1",enc)==0 )
        {
            encoding=1;
        }
        else if( strcasecmp("ISO-8859-2",enc)==0 )
        {
            encoding=2;
        }
        else
        {
        #ifdef _CCC3_
            printf("Encoding not supported: %s\n",enc);
        #endif
            encoding=-1;
        }
    }
    
    xmldom_lexer(int fd)
    {
        init();
        inputfd=fd;
    }

    xmldom_lexer(char *ptr)
    {
        init();
        inputptr=ptr;
    }

    ~xmldom_lexer()
    {
        free(text);
        
        //Flex hiba javítása.
        //A Flex nem szabadítja fel az alábbi buffert:
        //yy_start_stack protected member az yyFlexLexer osztályban,
        //és elfedi a static yy_start_stack külső változót (zavaros).
        
        if( yy_start_stack )
        {
            free(yy_start_stack);
            yy_start_stack=0;
        }
    } 
};

