
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
#include <utf8conv.h>

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

#define BUFINC  1024

#define ZEROCH  '?'  //ezt rakja be 0 helyett
//#define ZEROCH   0   //eredeti allapot


class xmldom_lexer : public yyFlexLexer
{
  protected:

    int LexerInput(char *buf, int maxsiz)
    {
        if( inputblk && inputsize<16 )
        {
            //ha ez a kodblokk nem NULL
            //akkor minden alkalommal kiertekeljuk
            //toltogetve a benemetet az inputbuf-ba
        
            push(inputblk);
            push(parservp);
            _clp_eval(2);

            VALUE *base=TOP();
            int argno=1;
            push_call("xmldom_lexer:lexerinput",base);
            if( !ISNIL(1) )
            {
                str2bin(base);
                char *input=_parb(1);
                int size=_parblen(1);
                enqueue(input,size);
            }
            pop();
            pop_call();
        }

        if( 0<inputsize )
        {
            int i=0;
            while( i<maxsiz && 0<inputsize )
            {
                buf[i]=*inputptr++;
                inputsize--;
                i++;
            }
            return i;
        }

        else if( inputfd>=0 )
        {
            int nbyte=read(inputfd,buf,maxsiz);
            for(int i=0; i<nbyte; i++)
            {
                if( buf[i]==0 )
                {
                    buf[i]=ZEROCH;
                }
            }
            return nbyte;
        }
        else
        {
            return 0;
        }
    }

  public:

    VALUE *parservp;
    VALUE *inputblk;
    char *inputbuf;
    char *inputptr;
    int inputsize;
    int inputfd;
    char *inputfspec;
    int entityconversionflag;
    int preservespace;
    int initialwspace;
    int eofflag;
    int debugflag;
    int encoding; //0==UTF-8, 1==ISO-8859-1, 2==ISO-8859-2, -1=ismeretlen
    char *text;
    int textsize;
    int buffersize;


    int yylex(); //Flex definialja, de nem deklaralja.


    void enqueue(const char *buf, int size)
    {
        if( size )
        {
            int i;
            for(i=0; i<inputsize; i++)
            {
                inputbuf[i]=inputptr[i];
            }
            inputbuf=(char*)realloc(inputbuf,inputsize+size+1);
            for(i=0; i<size; i++)
            {
                inputbuf[inputsize+i]=buf[i]?buf[i]:ZEROCH;
            }
            inputbuf[inputsize+size]=0;
            inputptr=inputbuf; //innen kell olvasni
            inputsize+=size;
        }
    }


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

    void code()
    {
        char *txt=(char*)YYText();
        unsigned c;
        if( *(txt+2)=='x' )
        {
            c=strtoul(txt+3,0,16);  //&#xhhhh;
        }
        else
        {
            c=strtoul(txt+2,0,10);  //&#nnnn;
        }

        char buf[8];
        #ifdef _CCC2_
            buf[0]=(char)(255&c);
            buf[1]=(char)0;
        #else 
            if( encoding==0 )
            {
                ucs_to_utf8(c,buf);
            }
            else
            {
                buf[0]=(char)(255&c);
                buf[1]=(char)0;
            }
        #endif
        cat(buf);
    }

    int trim()
    {
        if( preservespace==0 || initialwspace==1 )
        {
            int pos=0;    
            while( (textsize>pos) && isspace(text[pos]) )
            {
                pos++;
            }
            if( pos )
            {
                textsize-=pos;
                memmove(text,text+pos,textsize);
                text[textsize]=0;
            }
            while( (textsize>0) && isspace(text[textsize-1]) )
            {
                textsize--;
                text[textsize]=0;
            }
        }
        return textsize>0;
    }

    int getnext(CHAR **token)
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
            return 0; //nincs tobb bemenet       
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
                *token=(CHAR*)malloc((textsize+1)*sizeof(CHAR));
                int i;
                for(i=0; i<textsize; i++)
                {
                   *(*token+i)=(CHAR)latin2[(unsigned)*(text+i)];
                }
                *(*token+i)=(CHAR)0;
            }

            else //if( encoding==1 ) //Latin-1 (es minden mas)
            {
                *token=(CHAR*)malloc((textsize+1)*sizeof(CHAR));
                int i;
                for(i=0; i<textsize; i++)
                {
                   *(*token+i)=(CHAR)*(text+i); //trivialis 8bit -> 32bit
                }
                *(*token+i)=(CHAR)0;
            }

            //Csak UTF-8, Latin-1 es Latin-2 tamogatas van. 
            //Minden mas kodolas ugy konvertalodik, mint a Latin-1.
            //Nem foglalkozunk a szabvany szerint ervenytelen kodokkal.
        #endif
        }
        return id;
    }
    
    void init()
    {
        parservp=0;
        inputblk=0;
        inputbuf=0;  //buffer eleje
        inputptr=0;  //innen kell olvasni
        inputsize=0; //ennyi van meg benn
        inputfd=-1;
        inputfspec=0;
        entityconversionflag=0;
        preservespace=0;
        initialwspace=1;
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
    
    xmldom_lexer(VALUE *pv, char *buf, int size, VALUE *ib, int fd)
    {
        init();
        enqueue(buf,size);
        parservp=pv;
        inputblk=ib;
        inputfd=fd;
    }

    ~xmldom_lexer()
    {
        free(text);
        free(inputbuf);
        free(inputfspec);
    } 
};

