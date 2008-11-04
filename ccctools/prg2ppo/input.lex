
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

%x st_incl st_ifdef st_ifndef st_ifeq st_ifneq st_waitelse st_waitendif st_comment st_raw

%{

//Ez a flex program vezérli az input olvasását
//
//  végzi az inkludálást,
//  kihagyja az ifdef/else/endif kihagyandó részeit,
//  kihagyja a kommenteket,
//  kiegyenesíti a folytatósorokat,
//  szétválasztja az egy sorba írt utasításokat,
//  számolja a sorokat,
//  kikerüli a stringeket.

//Figyelem:
//  A "st_comment" név helyett nem jó az egyszerű "comment",
//  mert a Windowson include filékben (msxml.h) zavart okoz 
//  a Flex által generált '#define comment 8' makró.
 

#include <string.h>
#include <cccapi.h>

//a generalt kodban:
//#define ECHO (void) fwrite( yytext, yyleng, 1, yyout ) 
//gcc 4.3.2 warning: ignoring return value
#define ECHO (0==fwrite(yytext,yyleng,1,yyout))

//Bizonyos esetekben (folytatósor, sorelválasztó ;)
//a generált kimeneten CR jelenhet meg, ami a további
//fordítást elrontja, ezért legegyszerűbb, ha a CR
//karaktereket, már a bemenet olvasásakor eldobjuk.
//Ugyancsak el kell dobni a filék végén lévő esetleges 
//eof (chr(26)) karaktert, amit a UNIX nem fogad el.

#define ALTERNATIVE_INPUT2
 

#ifdef ALTERNATIVE_INPUT1
#define YY_INPUT(buf,result,max_size) \
{\
    int c=getc(yyin);\
    if( c!=EOF )\
    {\
        result=1;\
        buf[0]=c;\
    }\
    else\
    {\
        result=YY_NULL;\
    }\
}
#endif


#ifdef ALTERNATIVE_INPUT2
#define YY_INPUT(buf,result,max_size)  yy_input(buf,&result,max_size)
 
int yy_input(char *buf, int *result, int max_size)
{
    int c=getc(yyin);
    
    while( (c=='\r') || (c==26) )
    {
        c=getc(yyin);
    }

    if( c!=EOF )
    {
        buf[0]=c;
        *result=1;
    }
    else
    {
        *result=YY_NULL;
    }
    
    //printf("%c",c);
    return *result;
}
#endif
 

 
#define YY_NEVER_INTERACTIVE     1
//#define YY_ALWAYS_INTERACTIVE    1 

#define MAX_INCLUDE_DEPTH       10
#define MAX_LINE_SIZE         8192
#define MAX_STATE_DEPTH         20
 
static YY_BUFFER_STATE include_stack[MAX_INCLUDE_DEPTH];
static unsigned lnumber_stack[MAX_INCLUDE_DEPTH]; 
static char *fname_stack[MAX_INCLUDE_DEPTH]; 
static int include_stack_ptr=0;
static int include_changed=0;
 
static int state_stack[MAX_STATE_DEPTH];
static int state_stack_ptr=0;

static char *outbuf=0;
static int  outbuf_idx=0;
static int  outbuf_siz=0;
static int  outlineno=0;
static int  outtype=0;

static char *filein;

extern void error(const char*);
static void procinclude(void);
static void procifdef(int type);
static void statepush(int state);
static void statepop(void);
static char *getfilename();
static char *tabular(int p);
static void outchar(int c);
static void outtrim();
static void outstr(const char *s);
static int  outempty(void);
static void printbuf(void);
static void counter(void);

extern void _clp_nextline(int argno);
extern void _clp_prepro(int argno);
extern void _clp_define(int argno);
extern void _clp_undef(int argno);
extern void _clp_translate(int argno);
extern void _clp_searchdefine(int argno);
extern void _clp_searchinclude(int argno);


static char *raw_symbol=0;

static void raw_beg(int state)
{
    raw_symbol=strdup(yytext);
    outstr(yytext);
    statepush(state);
}

static void raw_end()
{
    outstr(yytext);
    if( 0==strcmp(raw_symbol,yytext) )
    {
        free(raw_symbol);
        statepop();
    }
}

%}

%option noyywrap
%option yylineno

SYMBOL         [_a-zA-Z][_a-zA-Z0-9]*
STRING         (\"[^"\n]*\"|\'[^'\n]*\')
COMMENT1       "//".*\n 
COMMENTML      "/*" 
 
%%

"<<"{SYMBOL}">>"             raw_beg(st_raw);
<st_raw>{
"<<"{SYMBOL}">>"             raw_end();
"\n"                         outchar(*yytext);
.                            outchar(*yytext);
}

^[ \t]*#include              statepush(st_incl);
^[ \t]*#ifdef                statepush(st_ifdef);
^[ \t]*#ifndef               statepush(st_ifndef);
^[ \t]*#ifeq                 statepush(st_ifeq);
^[ \t]*#ifneq                statepush(st_ifneq);
^[ \t]*#else                 statepush(st_waitendif);
^[ \t]*#endif   
^[ \t]*#define               outtype=1;    
^[ \t]*#xtranslate           outtype=2;
^[ \t]*#translate            outtype=2;
^[ \t]*#xcommand             outtype=3;
^[ \t]*#command              outtype=3;
^[ \t]*#undef                outtype=4;
 

^[ \t]*"*".*\n               //comment
;[ \t]*\n                    //folytató
;[ \t]*"//".*\n              //folytató //comment
;[ \t]*"/*".*"*/".*\n        //folytató /*comment*/
;                            {outtrim();outchar(';');} //szétválasztó
{COMMENT1}                   printbuf(); //egysoros 
{COMMENTML}                  statepush(st_comment); //többsoros 
{STRING}                     outstr(yytext);
\n                           printbuf();
.                            outchar(*yytext);


<st_comment>{
[^*]*                   
"*"+[^/]                
"*"+"/"                      outstr("/**/");statepop(); 
}
 
 
<st_incl>{
{STRING}.*\n                 procinclude();
\n                           error("No filespec for #include"); 
.                       
}        


<st_ifdef>{
{SYMBOL}.*\n                 procifdef(0); 
\n                           error("No symbol for #ifdef");
.                       
}


<st_ifndef>{
{SYMBOL}.*\n                 procifdef(1); 
\n                           error("No symbol for #ifndef");
.                       
}

<st_ifeq>{
{SYMBOL}[ \t]+{SYMBOL}.*\n   procifdef(2); 
\n                           error("No symbols for #ifeq");
.                       
}


<st_ifneq>{
{SYMBOL}[ \t]+{SYMBOL}.*\n   procifdef(3); 
\n                           error("No symbols for #ifneq");
.                       
}
 
 
<st_waitelse>{
^[ \t]*#else                 statepop();
}


<st_waitelse,st_waitendif>{
^[ \t]*#endif                statepop();
^[ \t]*#ifdef.*\n            statepush(st_waitendif);
^[ \t]*#ifndef.*\n           statepush(st_waitendif);
^[ \t]*#ifeq.*\n             statepush(st_waitendif);
^[ \t]*#ifneq.*\n            statepush(st_waitendif);
{STRING}
{COMMENT1}
{COMMENTML}                  statepush(st_comment); //többsoros   
\n
.
}
 

<<EOF>> {

    if( YYSTATE==st_raw )
    {
        char buf[256];
        sprintf(buf,"Open raw string %s at EOF",raw_symbol);
        error(buf);
    }

    printbuf();

    printf("\n%sEnd %s ",tabular(include_stack_ptr),getfilename());
     
    if( --include_stack_ptr<0 )
    {
        outtype=0;
        outchar('\n');
        printbuf();
        yyterminate();
    }
    else
    {
        fclose(yyin);
        yy_delete_buffer( YY_CURRENT_BUFFER );
        yy_switch_to_buffer(include_stack[include_stack_ptr] );
        free(fname_stack[include_stack_ptr]);
        yylineno=lnumber_stack[include_stack_ptr];
    }
    include_changed=1;
}

%%

//---------------------------------------------------------------------------
void _clp_processing(int argno) 
{
    CCC_PROLOG("processing",1);
    _clp_convertfspec2nativeformat(1);

    filein=_parb(1);
    
    //FONTOS
    //a static változók megfelelő inicializálása, 
    //másképp a program nem hívható többször
    
    printf("\nBeg %s ",filein);

    include_changed=0;
    include_stack_ptr=0;
    state_stack_ptr=0;
    outbuf_idx=0;
    outlineno=0;
    outtype=0;
    yylineno=1;
 
    yyin=fopen(filein,"r");
    if( !yyin )
    {
        yylineno=0;
        error("File not found");
    }

    yylex();

    _ret();
    CCC_EPILOG();
}


//---------------------------------------------------------------------------
static void outbuf_resize(int x)
{
    while(outbuf_idx+x+1>outbuf_siz)
    {
        outbuf=(char*)realloc(outbuf,outbuf_siz+=1024);
    }
}

//---------------------------------------------------------------------------
static void outchar(int c)
{
    if( outbuf_idx==0 )
    {
        outlineno=yylineno;
    }
    outbuf_resize(1);
    outbuf[outbuf_idx]=c;
    outbuf_idx++;
}

//---------------------------------------------------------------------------
static void outtrim()
{
    while( (outbuf!=0) &&
           (outbuf_idx>0) && 
           ((outbuf[outbuf_idx-1]==' ') || (outbuf[outbuf_idx-1]=='\t')) )
    {
        outbuf_idx--;
    }
}

//---------------------------------------------------------------------------
static void outstr(const char *s)
{
    if( outbuf_idx==0 )
    {
        outlineno=yylineno;
    }
    int len=strlen(s);
    outbuf_resize(len);
    memcpy(outbuf+outbuf_idx,s,len);
    outbuf_idx+=len;
}
 

//---------------------------------------------------------------------------
static int outempty()
{
    outchar(0);
    int c;
    char *p=outbuf;
    while( ((c=*p)==' ')||(c=='\t') ) p++;
    return !c;  //1, ha a string üres
}


//---------------------------------------------------------------------------
static void printbuf()
{
    if( !outempty() )
    {
        static int lastlineno=0;

        binaryn(outbuf);

        if( outtype==0 ) //normál programsor
        {
            ++lastlineno;
        
            if( include_changed || (lastlineno!=outlineno)  )
            {
                include_changed=0;
                lastlineno=outlineno;
                number(outlineno);
                stringnb(getfilename());
                _clp_nextline(2);
                pop();
            }
            counter();
            _clp_prepro(1); 
        }

        else if( outtype==1 ) //#define direktíva
        {
            _clp_define(1);
        }
        else if( outtype==2 ) //#xtranslate direktíva 
        {
            _clp_translate(1);
        }
        else if( outtype==3 ) //#xcommand direktíva 
        {
            _clp_translate(1);
        }
        else if( outtype==4 ) //#undef direktíva 
        {
            _clp_undef(1);
        }
 
        pop();
        outtype=0;
    }

    outbuf_idx=0;
}
 
//---------------------------------------------------------------------------
void error(const char*txt)
{   
    printf("\n%s",txt);
    printf("\nFile(%s) Line(%d) [%s]",getfilename(),yylineno,yytext);
    exit(1);
}

//---------------------------------------------------------------------------
void _clp_error(int argno) //ugyanaz Clipperből
{
    CCC_PROLOG("error",1);
    str2bin(base);
    char *txt=_parb(1);
    error(txt);
    _ret();
    CCC_EPILOG();
}
 

//---------------------------------------------------------------------------
static void counter()
{
    static int cnt=0;

    if( (++cnt%50)==0 )
    {
         printf(">");
    }
}    

//---------------------------------------------------------------------------
static void statepush(int state)
{
    if( state_stack_ptr<MAX_STATE_DEPTH )
    {
        state_stack[state_stack_ptr++]=YYSTATE;
        BEGIN(state); 
        //printf("\npush BEGIN %3d %s %d %d",yylineno,getfilename(),state_stack_ptr,state);
    }
    else
    {
        error("LEX state stack overflow");
    }
}

//---------------------------------------------------------------------------
static void statepop()
{
    if( --state_stack_ptr>=0 )
    {
        int state=state_stack[state_stack_ptr]; 
        BEGIN(state);
        //printf("\npop  BEGIN %3d %s %d %d",yylineno,getfilename(),state_stack_ptr,state);
    }
    else
    {
        error("LEX state stack underflow");
    }
}

//---------------------------------------------------------------------------
static void procinclude()
{
    if( include_stack_ptr>=MAX_INCLUDE_DEPTH )
    {
        error("Includes nested too deeply");
    }

    int i=1;while( yytext[i]!='"')i++;yytext[i]=0;
    stringnb(yytext+1); //CCC-STACK++
    _clp_searchinclude(1);
    _clp_convertfspec2nativeformat(1);
    char *fspec=BINARYPTR(TOP());
    printf("\n%sBeg %s ",tabular(include_stack_ptr+1),fspec);
    yyin=fopen(fspec,"r");

    if( !yyin )
    {
        error("Include file not found");
    }

    include_stack[include_stack_ptr]=YY_CURRENT_BUFFER;
    fname_stack[include_stack_ptr]=strdup(fspec);
    lnumber_stack[include_stack_ptr]=yylineno;

    include_stack_ptr++;

    yylineno=1;
    yy_switch_to_buffer(yy_create_buffer(yyin,YY_BUF_SIZE));

    statepop();
    pop();                                                    //CCC-STACK--

    number(1);
    stringnb(getfilename());
    _clp_nextline(2);
    pop();
    include_changed=1;
}

 
//---------------------------------------------------------------------------
static char *getfilename()
{
    if( include_stack_ptr>0 )
    {
        return fname_stack[include_stack_ptr-1];
    }

    return filein;
}

//---------------------------------------------------------------------------
static char *tabular(int pos)
{
    static char tab[128];
    int i;
    for( i=0; i<4*pos; i++ )
    {
        tab[i]=' ';
    }
    tab[i]=0;
    return &tab[0];
}
 

//---------------------------------------------------------------------------
static void procifdef(int type)
{
    statepop();

    int def=0;    
    stringnb(yytext);
    _clp_searchdefine(1);
    if( TOP()->type==TYPE_FLAG )
    {
        def=(TOP()->data.flag)?2:1;
    }
    pop();
  
    //def==0 -> nem definiált
    //def==1 -> definiált, de nem egyenlő
    //def==2 -> definiált, és egyenlő

    if( ((type==0) && !def   ) ||  //#ifdef 
        ((type==1) &&  def   ) ||  //#ifndef 
        ((type==2) &&  def!=2) ||  //#ifeq
        ((type==3) &&  def==2) )   //#ifneq
    {
        statepush(st_waitelse); 
    }
}


//---------------------------------------------------------------------------

