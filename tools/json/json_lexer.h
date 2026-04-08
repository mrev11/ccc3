
#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#ifndef JSON_LEXER
#undef  yyFlexLexer
#define yyFlexLexer jsonFlexLexer
#include <flexlexer.h>
#endif

#include <json_parser.h>

#define BUFINC  1024

struct json_lexer : public yyFlexLexer
{
  protected:

    char *input;
    char *inputptr;
    int inputsize;
    int eofflag;

    char *textptr;
    int textsize;
    int buffersize;

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

    void cat()
    {
        int len=YYLeng();
        char *txt=(char*)YYText();

        if( textsize+len+1>buffersize )
        {
            textptr=(char*)realloc(textptr,buffersize+=(len+BUFINC));
        }
        memcpy(textptr+textsize,txt,len+1);
        textsize+=len;
    }

    int getnext(char **token)
    {
        *token=0;
        if( eofflag )
        {
            return 0;
        }

        if( buffersize>BUFINC )
        {
            textptr=(char*)realloc(textptr,buffersize=BUFINC);
        }
        textsize=0;
        *textptr=0;

        int id=yylex();

        if( id==0 )
        {
            eofflag=1;
            return 0;
        }

        //printf("LEX %2d [%s]\n",id,textptr);

        if( *textptr )
        {
            if( id==STRING )
            {
                // unquote
                *token=strdup(textptr+1); // bal " leszedve
                //(*token)[ strlen(*token)-1 ]=0; // jobb " leszedve
                
                // unescape
                char *p=*token;
                char *q=*token;
                while( *q!=0 && *q != '\"' )
                {
                    if( *q=='\\' )
                    {
                        q++;
                    }
                    *p++=*q++;
                }
                *p=0; // jobb " leszedve
                
            }
            else
            {
                *token=strdup(textptr);
            }
        }
        return id;
    }

    int yylex(); //Flex definiálja, de nem deklarálja.

    json_lexer(char *ptr, int size)
    {
        input=ptr;
        inputptr=ptr;
        inputsize=size;
        eofflag=0;

        textptr=(char*)malloc(buffersize=BUFINC);
        textsize=0;
        *textptr=0;
    }

    ~json_lexer()
    {
        free(textptr);
    }
};
