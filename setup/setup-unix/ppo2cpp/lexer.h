
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

#ifdef WINDOWS
#include <io.h>
#endif

#ifndef INCLUDED_FROM_LEXER_LEX 
#include <flexlexer.h>
#endif

#include <parser.h>
#include <parsenode.h>

#define RAWBUF      1024
#define COMPOUND    255

extern char *wchar_to_utf8(wchar_t const *wstr, unsigned wlen, unsigned *reslen);
extern wchar_t *utf8_to_wchar(char const *utf8, unsigned blen, unsigned *reslen);

class ppo2cpp_lexer : public yyFlexLexer
{
    int inputfd;
    int inputlineno;
    char *inputfspec;
    int eofflag;
    int debugflag;
    char *compound;
    int compound_idx;
    

    protected:

    
    int LexerInput(char *buf, int maxsiz)
    {
        return read(inputfd,buf,maxsiz);
    }

    char *raw_symbol;
    char *raw_text;
    int raw_textsize;
    int raw_buffersize;

    void raw_cat()
    {
        int len=YYLeng();
        char *txt=(char*)YYText();

        if( raw_textsize+len+1>raw_buffersize )
        {
            raw_text=(char*)realloc(raw_text,raw_buffersize+=(len+RAWBUF));
        }
        memcpy(raw_text+raw_textsize,txt,len+1);
        raw_textsize+=len;
    }

    void raw_cat(const char *txt)
    {
        int len=strlen(txt);
        if( raw_textsize+len+1>raw_buffersize )
        {
            raw_text=(char*)realloc(raw_text,raw_buffersize+=(len+RAWBUF));
        }
        memcpy(raw_text+raw_textsize,txt,len+1);
        raw_textsize+=len;
    }

    void raw_set()
    {
        raw_symbol=strdup(YYText());
        raw_cat("\"");
    }

    int raw_cmp()
    {
        if( strcmp(raw_symbol,YYText())==0 )
        {
            raw_cat("\"");
            return 1;
        }
        raw_cat();
        return 0;
    }

    int ttype(int c)
    {
             if( c=='.' ) return DOT;
        else if( c==':' ) return COLON;
        else if( c=='(' ) return LPAR;
        else if( c==')' ) return RPAR;
        else if( c=='@' ) return AT;
        else if( c=='-' ) return ARROW;
        return 0;
    }
    
    parsenode *getnext_compound()
    {
        //printf(">>%s\n",compound+compound_idx);fflush(0);

        int idx=0,tt=0,c;
        while( ((c=compound[compound_idx+idx])!=0) && ((tt=ttype(c))==0) )
        {
            idx++;
        }

        parsenode *token=0;

        if( idx )
        {
            compound[compound_idx+idx]=0;
            token=(new parsenode)->token(SYMBOL,strdup(compound+compound_idx),inputlineno);
            compound[compound_idx+idx]=c;
            compound_idx+=idx;
        }
        else if( tt==ARROW )
        {
            token=(new parsenode)->token(tt,strdup("->"),inputlineno);
            compound_idx+=2;
        }
        else if( tt==COLON && compound[compound_idx+1]==':' )
        {
            if( compound[compound_idx+2]=='='  )
            {
                token=(new parsenode)->token(COLCOLASS,strdup("::="),inputlineno);
                compound_idx+=3;
            }
            else
            {
                token=(new parsenode)->token(COLCOL,strdup("::"),inputlineno);
                compound_idx+=2;
            }
        }
        else if( tt )
        {
            char buf[2];buf[0]=c;buf[1]=0;
            token=(new parsenode)->token(tt,strdup(buf),inputlineno);
            compound_idx+=1;
        }
        
        if( compound[compound_idx]==0 )
        {
            free(compound);
            compound=0;
            compound_idx=0;
        }

        if( debugflag )
        {
            token->print();
            fflush(0);
        }

        return token;
    }


    public:
 
    int yylex(); //Flex definiálja, de nem deklarálja.
    
    void setdebugflag(int flag)
    {
        debugflag=flag;
    }

    int geteofflag()
    {
        return eofflag;
    }
    
    int setinputfd(int fd)
    {
        return inputfd=fd;
    }

    int getinputlineno()
    {
        return inputlineno;
    }

    int setinputlineno()
    {
        sscanf(YYText(),"%d",&inputlineno);
        return inputlineno;
    }

    int setinputlineno(int ln)
    {
        return inputlineno=ln;
    }

    int incinputlineno()
    {
        return ++inputlineno;
    }
    
    char *getinputfspec()
    {
        return inputfspec?inputfspec:(char*)"";
    }

    char *setinputfspec()
    {
        if( inputfspec )
        {
            free(inputfspec);
        }
        return inputfspec=strdup(YYText());
    }

    char *setinputfspec(char *fs)
    {
        if( inputfspec )
        {
            free(inputfspec);
        }
        return inputfspec=strdup(fs);
    }
    
 
    parsenode *getnext()
    {
        if( eofflag )
        {
            return 0;
        }

        if( compound )
        {
            return getnext_compound();
        }

        raw_textsize=0;
        raw_symbol=0;

        int id=yylex();

        if( id==0 )
        {
            eofflag=1;
            return 0; //nincs több bemenet       
        }

        if( raw_symbol ) 
        {
            free(raw_symbol);
            parsenode *token=(new parsenode)->token(STRING,strdup(raw_text),inputlineno);
            if( debugflag )
            {
                token->print();
                fflush(0);
            }
            return token;
        }

        char *txt=(char*)YYText();
        int len=YYLeng()-(id==NLSTEXT||id==BINARYA?1:0);
        txt=strdup(txt+(id==NLSTEXT||id==BINARYA?1:0));

        //Mindent, ami nem string kisbetűre konvertálunk,
        //ezzel véglegesen biztosítva lesz a case insensitivity.

        if( (id!=STRING) && (id!=BINARYA) && (id!=NLSTEXT) )
        {
            int i=0;
            while( *(txt+i)!=0 )
            {
                *(txt+i)=tolower(*(txt+i));
                i++;
            }
        }

        if( id==COMPOUND )
        {
            //wspace szures
            {   
                char *p=(char*)malloc(len+1);
                int i,j;
                for( i=0,j=0; i<len; i++ )
                {
                    if( txt[i]!=' ' && txt[i]!='\t' )
                    {
                        p[j++]=txt[i];
                    }
                }
                p[j]=0;
                free(txt);
                txt=p;
                len=j;
            }
        
            //ures zarojelpar kieg
            if( txt[0]==':' && txt[1]==':' && txt[len-1]!='(' )
            {   
                char *p=(char*)malloc(len+3);
                memcpy(p,txt,len);
                p[len+0]='(';
                p[len+1]=')';
                p[len+2]=0;
                free(txt);
                txt=p;
                len+=2;
            }

            compound=txt;
            compound_idx=0;
            return getnext_compound();
        }

        //A '...' stringeket "..." alakra kell hozni,
        //a belső "-ket \"-vel, a \-eket \\-vel védeni kell.

        if( (id==STRING) || (id==BINARYA) || (id==NLSTEXT) )
        {
            if( *txt=='\'' )
            {
                *txt='"';
                *(txt+len-1)='"';
            }
                
            int i,n;
            for( i=1,n=0; i<len-1; i++ )
            {
                if( *(txt+i)=='\\' )
                {
                    n++;
                }
                else if( *(txt+i)=='\"' )
                {
                    n++;
                }
            }
            
            if( n>0 )
            {
                char *p=(char*)malloc(len+n+1);
                *p='"';
                *(p+n+len-1)='"';
                *(p+n+len)=(char)0;

                for( i=1,n=1; i<len-1; i++ )
                {
                    if( *(txt+i)=='\\' )
                    {
                        *(p+n++)='\\';
                    }
                    else if( *(txt+i)=='\"' )
                    {
                        *(p+n++)='\\';
                    }
                    *(p+n++)=*(txt+i);
                }
                free(txt);
                txt=p;
            }
        }

        if( id==BINARYX )
        {
            if( *(txt+1)=='\'' )
            {
                *(txt+1)='"';
                *(txt+len-1)='"';
            }
        }

        //A számok elejéről a felesleges 0-kat levesszük,
        //hogy a C fordító ne akarja őket oktálisnak értelmezni.
        
        if( id==NUMBER && *txt=='0' && isdigit(*(txt+1))  )
        {
            char *p=txt;
            while( *p=='0' && isdigit(*(p+1)) )
            {
                p++;
            }
            char *p1=strdup(p);
            free(txt);
            txt=p1;
        }
        
        if( id==STRING )
        {
            unsigned len=0;
            wchar_t *wc=utf8_to_wchar(txt,strlen(txt),&len);
            char *uc=wchar_to_utf8(wc,len,0);
            
            if( strcmp(uc,txt) )
            {
                id=INVALIDENCODING;
            }
            free(wc);
            free(uc);
        }
        
        parsenode *token=(new parsenode)->token(id,txt,inputlineno);
        
        if( debugflag )
        {
            token->print();
            fflush(0);
        }

        return token;
    }
    
    ppo2cpp_lexer(int fd=0)
    {
        inputfd=fd;
        inputfspec=0;
        inputlineno=1;
        eofflag=0;
        debugflag=0;

        raw_text=0;
        raw_symbol=0;
        raw_textsize=0;
        raw_buffersize=0;

        compound=0;
        compound_idx=0;
    }

    ~ppo2cpp_lexer()
    {
    } 
};

