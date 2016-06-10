
%{

#include <cccapi.h>

class lexer_latin2_to_ascii : public yyFlexLexer
{
  protected:

    char *ptr;
    int len;
    int cnt;

    int LexerInput(char *buf, int maxsiz)
    {
        if( cnt<len )
        {
            *buf=ptr[cnt++];
            return 1;
        }
        return 0;
    }

  public:

    int yylex(); //Flex definiálja, de nem deklarálja.

    lexer_latin2_to_ascii(char *p, int len)
    {
        //printf("construct lexer_latin2_to_ascii\n");
        this->ptr=p;
        this->len=len;
        this->cnt=0;
    }

    ~lexer_latin2_to_ascii()
    {
        //printf("destruct lexer_latin2_to_ascii\n");
    } 
};


void _clp_latin2_to_ascii(int argno)  // binary -> binary
{
    CCC_PROLOG("latin2_to_ascii",1);
    char *p=_parb(1);
    int len=_parblen(1);
    char *q=binaryl(len);
    lexer_latin2_to_ascii lexer(p,len);
    int i=0,c;
    while( 0!=(c=lexer.yylex()) )
    {
        q[i++]=c;
    }
    _retblen(q,i);
    CCC_EPILOG();
}

%}


%option c++
%option yyclass="lexer_latin2_to_ascii"
%option prefix="base_latin2_to_ascii"
%option noyywrap
%option stack

symbol     "\""[_a-zA-Z][_a-zA-Z0-9]*"\""
 
%%

\xe1 {return 'a';}
\xe9 {return 'e';}
\xed {return 'i';}
\xf3 {return 'o';}
\xf6 {return 'o';}
\xf5 {return 'o';}
\xfa {return 'u';}
\xfc {return 'u';}
\xfb {return 'u';}
    
\xc1 {return 'A';}
\xc9 {return 'E';}
\xcd {return 'I';}
\xd3 {return 'O';}
\xd6 {return 'O';}
\xd5 {return 'O';}
\xda {return 'U';}
\xdc {return 'U';}
\xdb {return 'U';}


\xa0 {return 'a';}
\x82 {return 'e';}
\xa1 {return 'i';}
\xa2 {return 'o';}
\x94 {return 'o';}
\x93 {return 'o';}
\xf4 {return 'o';}
\xa3 {return 'u';}
\x81 {return 'u';}
\x96 {return 'u';}
\x8f {return 'A';}
\x90 {return 'E';}
\x8c {return 'I';}
\x8d {return 'I';}
\x95 {return 'O';}
\x99 {return 'O';}
\xa7 {return 'O';}
\xd4 {return 'O';}
\x97 {return 'U';}
\x9a {return 'U';}
\x98 {return 'U';}



.        {return *YYText();}
\n       {return *YYText();}

%%

