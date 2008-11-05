
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

//Vermes M.
//signed/unsigned comparison warning elkerülése,
//hogy cpp-ként is warning mentesen forduljon.
//void xtxlegalTrace(FILE *TraceFILE, const char *zTracePrompt);

/* Driver template for the LEMON parser generator.
** The author disclaims copyright to this source code.
*/
/* First off, code is include which follows the "include" declaration
** in the input file. */
#include <stdio.h>
#line 21 "./xtxlegal.lem"
 

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <cccapi.h>

#include <xtxlegal.h>

struct POS 
{
    unsigned int left; 
    unsigned int right;
};

static VALUE    *toklist;
static char     *tokenvir;
static unsigned  toklen;
static unsigned  tokidx;
static unsigned  tokstart;
static unsigned  maxright;
static unsigned  termflag;

extern void* xtxlegalAlloc(void*(*)(size_t)); 
extern void  xtxlegalFree(void*,void(*)(void*)); 
extern void  xtxlegalTrace(FILE*,char*); 
extern void  xtxlegal(void*,int,POS);  //3th arg: %token_type {POS} 

//#define DEBUG

//---------------------------------------------------------------------------
static char *gettoken(int idx,int*len)
{
    *len=0;
    char *p=NULL;
    
    if( toklist && (tokstart+idx<toklen) )
    {
        VALUE *token=&toklist[tokstart+idx];

        if( token->type!=TYPE_BINARY )
        {
            //kihagy;
        }
        else if( !token->data.binary.len )
        {
            //kihagy;
        }
        else
        {
            *len=token->data.binary.len;
            p=token->data.string.oref->ptr.binptr;
        }
    }
    return p;
} 

//---------------------------------------------------------------------------
static int lex(POS *pos)
{
    pos->left=tokidx;
    pos->right=tokidx;

    int toklen=0;
    char *p=gettoken(tokidx++,&toklen);

    if( p )
    {
        if( isalpha(*p) ||  //symbol
            isdigit(*p) ||  //number
            *p=='_'     ||  //symbol
            *p=='\''    ||  //string
            *p=='\"'       )
        {
            return EXPR;
        }
        else if( *p=='<' && toklen>5 )
        {
            return EXPR; //raw string
        }
        else if( *p=='.' )
        {
            //logikai értékek és operátorok
            
            if( toklen==1 )       // "."
            {
                return DOT;
            }
            else if( toklen==2 )  // ".."
            {
                return DOTDOT; 
            }
            else if( toklen==3 )  // ".f.", ".t."
            {
                return EXPR; 
            }
            else if( toklen==4 )  // ".or."
            {
                return PLUS;
            }
            else if( toklen==5 )  // ".and.", ".not."
            {
                return (toupper(*(p+1))=='A') ? STAR:EXCL;
            }
        }
        else
        {
            switch (*p) {
                //case '': return EXPR;
                case ' ': return SPACE;
                case '!': return EXCL;
                case '-': return MINUS;
                case '+': return PLUS;
                case '@': return AT;
                case '/': return SLASH;
                case '\\': return BSLASH;
                case '.': return DOT;
                case '*': return STAR;
                case '%': return MODULO;
                case '^': return POWER;
                case '$': return DOLLAR;
                case '>': return GT;
                case '<': return LT;
                case ':': return COLON;
                case '=': return EQUAL;
                case '(': return LPAR;
                case ')': return RPAR;
                case '[': return LBRACKET;
                case ']': return RBRACKET;
                case '{': return LBRACE;
                case '}': return RBRACE;
                case '|': return PIPE;
                case ',': return COMMA;
            }
        }
    }
    return 255;  //nemlétező tokenid
}

//---------------------------------------------------------------------------
static POS pstore(POS pl, POS pr)
{
    POS p;
    p.left=pl.left;
    p.right=pr.right;

    #ifdef DEBUG
    unsigned i;
    printf("\n>>>%10s>>> %d %d >>>",(tokenvir?tokenvir:""),p.left,p.right);
    for( i=p.left; i<=p.right+1; i++)
    {   
        int len;
        char *p=gettoken(i,&len);
        printf("{%d %s}",i,p?p:"nil");
    }
    #endif

    //p.left  = a kifejezés baloldali tokenjének indexe (0,1,...)
    //p.right = a kifejezés jobboldali tokenjének indexe (0,1,...)
    //gettoken(p.right+1) a kifejezést követő token, vagy NULL
    
    if( tokenvir )
    {
        //olyan legális kifejezést keresünk,
        //amit a tokenvir-ben megadott token követ,
        //csak a lista elején kezdődő kifejezések között keresünk, 
        //azaz csak azok között, melyekre p.left==0.
        
        if( p.left==0 )
        {
            int len;
            char *envir=gettoken(p.right+1,&len);
            if( envir && (0==strcasecmp(envir,tokenvir)) )
            {
                //megtaláltuk a megfelelő kifejezést,
                //itt abba kell hagyni az elemzést

                termflag=1;
                maxright=p.right+1;
            }
        }
    }
    else
    {
        //nincs megadva környezet (tokenvir),
        //ezért a maximális hosszúságú kifejezést keressük,
        //csak a lista elején kezdődő kifejezések hosszát nézzük, 
        //azaz csak azokét, melyekre p.left==0.

        if( (p.left==0) && (p.right+1>maxright) )
        {
            maxright=p.right+1;
        }
    }
    
    return p;
}

//---------------------------------------------------------------------------
void _clp_xtxlegal(int argno)
{
    CCC_PROLOG("xtxlegal",3);

    toklist  = _para(1);
    toklen   = _paralen(1);
    tokstart = _parni(2)-1;

    if( ISBINARY(3) )
    {
        tokenvir=_parb(3);
    }
    else
    {
        tokenvir=NULL;
    }

    tokidx    = 0;
    maxright  = 0;
    termflag  = 0;

    void *parser=xtxlegalAlloc(malloc);
    //xtxlegalTrace(stdout,">> ");
    int id;
    POS token; token.left=0; token.right=0;
    while( (termflag==0) && (0!=(id=lex(&token)))  )
    {
        #ifdef DEBUG
        int len;
        char *p=gettoken(token.left,&len);
        printf("\ntoken (%d) \'%s\'",id,p?p:"nil");
        #endif

        xtxlegal(parser,id,token);
    }
    xtxlegal(parser,0,token);
    xtxlegalFree(parser,free);

    _retni(maxright);

    CCC_EPILOG();
}

//---------------------------------------------------------------------------

#line 260 "./xtxlegal.c"
/* Next is all token values, in a form suitable for use by makeheaders.
** This section will be null unless lemon is run with the -m switch.
*/
/* 
** These constants (all generated automatically by the parser generator)
** specify the various kinds of tokens (terminals) that the parser
** understands. 
**
** Each symbol here is a terminal symbol in the grammar.
*/
/* Make sure the INTERFACE macro is defined.
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/* The next thing included is series of defines which control
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 terminals
**                       and nonterminals.  "int" is used otherwise.
**    YYNOCODE           is a number of type YYCODETYPE which corresponds
**                       to no legal terminal or nonterminal number.  This
**                       number is used to fill in empty slots of the hash 
**                       table.
**    YYFALLBACK         If defined, this indicates that one or more tokens
**                       have fall-back values which should be used if the
**                       original value of the token will not parse.
**    YYACTIONTYPE       is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 rules and
**                       states combined.  "int" is used otherwise.
**    xtxlegalTOKENTYPE     is the data type used for minor tokens given 
**                       directly to the parser from the tokenizer.
**    YYMINORTYPE        is the data type used for all minor tokens.
**                       This is typically a union of many types, one of
**                       which is xtxlegalTOKENTYPE.  The entry in the union
**                       for base tokens is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.
**    xtxlegalARG_SDECL     A static variable declaration for the %extra_argument
**    xtxlegalARG_PDECL     A parameter declaration for the %extra_argument
**    xtxlegalARG_STORE     Code to store %extra_argument into yypParser
**    xtxlegalARG_FETCH     Code to extract %extra_argument from yypParser
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
*/
/*  */
#define YYCODETYPE unsigned char
#define YYNOCODE 33
#define YYACTIONTYPE unsigned char
#define xtxlegalTOKENTYPE POS
typedef union {
  xtxlegalTOKENTYPE yy0;
  int yy65;
} YYMINORTYPE;
#define YYSTACKDEPTH 100
#define xtxlegalARG_SDECL
#define xtxlegalARG_PDECL
#define xtxlegalARG_FETCH
#define xtxlegalARG_STORE
#define YYNSTATE 118
#define YYNRULE 59
#define YYERRORSYMBOL 27
#define YYERRSYMDT yy65
#define YY_NO_ACTION      (YYNSTATE+YYNRULE+2)
#define YY_ACCEPT_ACTION  (YYNSTATE+YYNRULE+1)
#define YY_ERROR_ACTION   (YYNSTATE+YYNRULE)

/* Next are that tables used to determine what action to take based on the
** current state and lookahead token.  These tables are used to implement
** functions that take a state number and lookahead value and return an
** action integer.  
**
** Suppose the action integer is N.  Then the action is determined as
** follows
**
**   0 <= N < YYNSTATE                  Shift N.  That is, push the lookahead
**                                      token onto the stack and goto state N.
**
**   YYNSTATE <= N < YYNSTATE+YYNRULE   Reduce by rule N-YYNSTATE.
**
**   N == YYNSTATE+YYNRULE              A syntax error has occurred.
**
**   N == YYNSTATE+YYNRULE+1            The parser accepts its input.
**
**   N == YYNSTATE+YYNRULE+2            No such action.  Denotes unused
**                                      slots in the yy_action[] table.
**
** The action table is constructed as a single large table named yy_action[].
** Given state S and lookahead X, the action is computed as
**
**      yy_action[ yy_shift_ofst[S] + X ]
**
** If the index value yy_shift_ofst[S]+X is out of range or if the value
** yy_lookahead[yy_shift_ofst[S]+X] is not equal to X or if yy_shift_ofst[S]
** is equal to YY_SHIFT_USE_DFLT, it means that the action is not in the table
** and that yy_default[S] should be used instead.  
**
** The formula above is for computing the action when the lookahead is
** a terminal symbol.  If the lookahead is a non-terminal (as occurs after
** a reduce action) then the yy_reduce_ofst[] array is used in place of
** the yy_shift_ofst[] array and YY_REDUCE_USE_DFLT is used in place of
** YY_SHIFT_USE_DFLT.
**
** The following are the tables generated in this section:
**
**  yy_action[]        A single table containing all actions.
**  yy_lookahead[]     A table containing the lookahead for each entry in
**                     yy_action.  Used to detect hash collisions.
**  yy_shift_ofst[]    For each state, the offset into yy_action for
**                     shifting terminals.
**  yy_reduce_ofst[]   For each state, the offset into yy_action for
**                     shifting non-terminals after a reduce.
**  yy_default[]       Default action for each state.
*/
static YYACTIONTYPE yy_action[] = {
 /*     0 */     2,   34,    3,    7,   82,   11,   29,   27,    9,   13,
 /*    10 */    15,   17,   19,   21,   23,   31,   37,   81,   39,  112,
 /*    20 */     2,   34,    3,    7,  169,   11,   29,   27,    9,   13,
 /*    30 */    15,   17,   19,   21,   23,   31,   37,    6,   39,   41,
 /*    40 */    42,  118,    8,    2,   34,    3,    7,   32,   11,   29,
 /*    50 */    27,    9,   13,   15,   17,   19,   21,   23,   31,   37,
 /*    60 */    10,   39,    2,   34,    3,    7,   12,   11,   29,   27,
 /*    70 */     9,   13,   15,   17,   19,   21,   23,   31,   37,   14,
 /*    80 */    39,   44,   16,    2,   34,    3,    7,   18,   11,   29,
 /*    90 */    27,    9,   13,   15,   17,   19,   21,   23,   31,   37,
 /*   100 */    20,   39,   75,   22,    2,   34,    3,    7,   26,   11,
 /*   110 */    29,   27,    9,   13,   15,   17,   19,   21,   23,   31,
 /*   120 */    37,   84,   39,    2,   34,    3,    7,   28,   11,   29,
 /*   130 */    27,    9,   13,   15,   17,   19,   21,   23,   31,   37,
 /*   140 */    86,   39,   93,    4,    5,   25,  113,   47,   49,   51,
 /*   150 */    53,   55,  178,    1,   30,    6,  114,   85,   33,  116,
 /*   160 */    57,   38,   77,   38,   58,   62,   35,    4,    5,   25,
 /*   170 */    45,   47,   49,   51,   53,   55,  107,   38,   63,   59,
 /*   180 */    64,   36,   60,  105,   57,   93,   60,   38,   66,   62,
 /*   190 */    40,    4,    5,   25,   45,   47,   49,   51,   53,   55,
 /*   200 */    67,   60,   38,   68,   97,   80,   58,   95,   57,   69,
 /*   210 */    43,   60,   46,   62,   93,    4,   24,   25,   45,   47,
 /*   220 */    49,   51,   53,   55,   48,   50,   52,   78,   54,   56,
 /*   230 */    87,   91,   79,   61,   60,   74,   83,   62,   88,    4,
 /*   240 */     5,   25,   45,   47,   49,   51,   53,   55,   70,   90,
 /*   250 */    92,   94,   96,   98,  100,  102,   57,  104,  106,  108,
 /*   260 */   111,   62,  115,   65,  117,    4,    5,   25,   45,  109,
 /*   270 */    49,   51,   53,   55,   93,   93,   93,   93,   93,   93,
 /*   280 */    93,  110,   57,   93,   93,   93,   93,   62,   93,    4,
 /*   290 */     5,   25,   45,   47,   49,   51,   53,   55,   93,   93,
 /*   300 */    93,   93,   93,   93,   93,  103,   57,   93,   93,   93,
 /*   310 */    93,   62,   93,    4,    5,   25,   45,   47,   49,   51,
 /*   320 */    53,   55,   93,   93,   93,   93,   93,   93,   93,  101,
 /*   330 */    57,   93,   93,   93,   93,   62,   93,    4,    5,   25,
 /*   340 */    45,   47,   49,   51,   53,   55,   93,   93,   93,   93,
 /*   350 */    93,   93,   93,   99,   57,   93,   93,   93,   93,   62,
 /*   360 */    93,    4,    5,   25,   45,   47,   49,   51,   53,   55,
 /*   370 */    70,   93,   93,   93,   93,   93,   93,   93,   57,   93,
 /*   380 */    93,   93,   93,   62,   93,    4,    5,   25,   45,   47,
 /*   390 */    49,   51,   53,   55,   93,   93,   93,   93,   93,   93,
 /*   400 */    93,   93,   57,   93,   93,   93,   73,   62,    4,    5,
 /*   410 */    25,   45,   47,   49,   51,   53,   55,   93,   93,   93,
 /*   420 */    93,   93,   93,   93,   93,   57,   93,   93,   72,   93,
 /*   430 */    62,   93,    4,    5,   25,   45,   47,   49,   51,   53,
 /*   440 */    55,   71,   93,   93,   93,   93,   93,   93,   93,   57,
 /*   450 */    93,   93,   93,   93,   62,   93,    4,    5,   25,   45,
 /*   460 */    47,   49,   51,   53,   55,   93,   93,   93,   93,   93,
 /*   470 */    93,   93,   93,   57,   93,   93,   76,   93,   62,   93,
 /*   480 */     4,    5,   25,   45,   47,   49,   51,   53,   55,   93,
 /*   490 */    93,   93,   93,   93,   93,   93,   89,   57,   93,   93,
 /*   500 */    93,   93,   62,   93,    4,    5,   25,   45,   47,   49,
 /*   510 */    51,   53,   55,   93,   93,   93,   93,   93,   93,   93,
 /*   520 */    93,   57,   93,   93,   93,   93,   62,   93,    4,   24,
 /*   530 */    25,   45,   47,   49,   51,   53,   55,   93,   93,   93,
 /*   540 */    93,   93,   93,   93,   93,   79,   93,   93,   93,   93,
 /*   550 */    62,
};
static YYCODETYPE yy_lookahead[] = {
 /*     0 */     2,    3,    4,    5,    6,    7,    8,    9,   10,   11,
 /*    10 */    12,   13,   14,   15,   16,   17,   18,   19,   20,   29,
 /*    20 */     2,    3,    4,    5,   26,    7,    8,    9,   10,   11,
 /*    30 */    12,   13,   14,   15,   16,   17,   18,   29,   20,   21,
 /*    40 */    22,    0,   29,    2,    3,    4,    5,   17,    7,    8,
 /*    50 */     9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
 /*    60 */    29,   20,    2,    3,    4,    5,   29,    7,    8,    9,
 /*    70 */    10,   11,   12,   13,   14,   15,   16,   17,   18,   29,
 /*    80 */    20,   21,   29,    2,    3,    4,    5,   29,    7,    8,
 /*    90 */     9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
 /*   100 */    29,   20,   21,   29,    2,    3,    4,    5,   29,    7,
 /*   110 */     8,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*   120 */    18,   19,   20,    2,    3,    4,    5,   29,    7,    8,
 /*   130 */     9,   10,   11,   12,   13,   14,   15,   16,   17,   18,
 /*   140 */    29,   20,   31,    1,    2,    3,    4,    5,    6,    7,
 /*   150 */     8,    9,   28,   29,   29,   29,   14,   31,   29,   17,
 /*   160 */    18,   29,   30,   29,   30,   23,   17,    1,    2,    3,
 /*   170 */     4,    5,    6,    7,    8,    9,   10,   29,   30,   19,
 /*   180 */    24,   29,   26,   17,   18,   32,   26,   29,   30,   23,
 /*   190 */    29,    1,    2,    3,    4,    5,    6,    7,    8,    9,
 /*   200 */    25,   26,   29,   30,   14,   29,   30,   17,   18,   24,
 /*   210 */    29,   26,   29,   23,   32,    1,    2,    3,    4,    5,
 /*   220 */     6,    7,    8,    9,   29,   29,   29,   19,   29,   29,
 /*   230 */    16,   17,   18,   29,   26,   29,   29,   23,   29,    1,
 /*   240 */     2,    3,    4,    5,    6,    7,    8,    9,   10,   29,
 /*   250 */    29,   29,   29,   29,   29,   29,   18,   29,   29,   29,
 /*   260 */    29,   23,   29,   25,   29,    1,    2,    3,    4,    5,
 /*   270 */     6,    7,    8,    9,   32,   32,   32,   32,   32,   32,
 /*   280 */    32,   17,   18,   32,   32,   32,   32,   23,   32,    1,
 /*   290 */     2,    3,    4,    5,    6,    7,    8,    9,   32,   32,
 /*   300 */    32,   32,   32,   32,   32,   17,   18,   32,   32,   32,
 /*   310 */    32,   23,   32,    1,    2,    3,    4,    5,    6,    7,
 /*   320 */     8,    9,   32,   32,   32,   32,   32,   32,   32,   17,
 /*   330 */    18,   32,   32,   32,   32,   23,   32,    1,    2,    3,
 /*   340 */     4,    5,    6,    7,    8,    9,   32,   32,   32,   32,
 /*   350 */    32,   32,   32,   17,   18,   32,   32,   32,   32,   23,
 /*   360 */    32,    1,    2,    3,    4,    5,    6,    7,    8,    9,
 /*   370 */    10,   32,   32,   32,   32,   32,   32,   32,   18,   32,
 /*   380 */    32,   32,   32,   23,   32,    1,    2,    3,    4,    5,
 /*   390 */     6,    7,    8,    9,   32,   32,   32,   32,   32,   32,
 /*   400 */    32,   32,   18,   32,   32,   32,   22,   23,    1,    2,
 /*   410 */     3,    4,    5,    6,    7,    8,    9,   32,   32,   32,
 /*   420 */    32,   32,   32,   32,   32,   18,   32,   32,   21,   32,
 /*   430 */    23,   32,    1,    2,    3,    4,    5,    6,    7,    8,
 /*   440 */     9,   10,   32,   32,   32,   32,   32,   32,   32,   18,
 /*   450 */    32,   32,   32,   32,   23,   32,    1,    2,    3,    4,
 /*   460 */     5,    6,    7,    8,    9,   32,   32,   32,   32,   32,
 /*   470 */    32,   32,   32,   18,   32,   32,   21,   32,   23,   32,
 /*   480 */     1,    2,    3,    4,    5,    6,    7,    8,    9,   32,
 /*   490 */    32,   32,   32,   32,   32,   32,   17,   18,   32,   32,
 /*   500 */    32,   32,   23,   32,    1,    2,    3,    4,    5,    6,
 /*   510 */     7,    8,    9,   32,   32,   32,   32,   32,   32,   32,
 /*   520 */    32,   18,   32,   32,   32,   32,   23,   32,    1,    2,
 /*   530 */     3,    4,    5,    6,    7,    8,    9,   32,   32,   32,
 /*   540 */    32,   32,   32,   32,   32,   18,   32,   32,   32,   32,
 /*   550 */    23,
};
#define YY_SHIFT_USE_DFLT (-3)
static short yy_shift_ofst[] = {
 /*     0 */   503,   41,   -3,  142,   -3,  503,  121,  264,  121,  166,
 /*    10 */   121,  288,  121,  312,  121,  503,  121,  503,  121,  336,
 /*    20 */   121,  190,  121,  214,  527,  503,  121,  503,  121,  503,
 /*    30 */   121,   30,  503,  121,  149,  503,  121,  360,  121,  384,
 /*    40 */    18,   -3,  407,   60,   -3,  503,  121,  503,  121,  503,
 /*    50 */   121,  503,  121,  503,  121,  503,  121,  360,  160,   -3,
 /*    60 */   431,  121,  238,  156,   -3,  360,  175,  360,  185,   -3,
 /*    70 */    -3,   -3,   -3,  455,   81,   -3,   -3,  208,   -3,  360,
 /*    80 */    -2,   -3,  503,  102,   -3,   -3,  121,  479,  121,  503,
 /*    90 */   121,  503,  121,  503,  121,  503,  121,  503,  121,  503,
 /*   100 */   121,  503,  121,  503,  121,  503,  121,  503,  121,  503,
 /*   110 */   503,  121,  121,  503,  503,  121,  503,  121,
};
#define YY_REDUCE_USE_DFLT (-11)
static short yy_reduce_ofst[] = {
 /*     0 */   124,  -11,  -11,  -10,  -11,    8,  -11,   13,  -11,   31,
 /*    10 */   -11,   37,  -11,   50,  -11,   53,  -11,   58,  -11,   71,
 /*    20 */   -11,   74,  -11,  111,  126,   79,  -11,   98,  -11,  125,
 /*    30 */   -11,  -11,  129,  -11,  -11,  152,  -11,  132,  -11,  161,
 /*    40 */   -11,  -11,  181,  -11,  -11,  183,  -11,  195,  -11,  196,
 /*    50 */   -11,  197,  -11,  199,  -11,  200,  -11,  134,  -11,  -11,
 /*    60 */   204,  -11,  148,  -11,  -11,  158,  -11,  173,  -11,  -11,
 /*    70 */   -11,  -11,  -11,  206,  -11,  -11,  -11,  -11,  -11,  176,
 /*    80 */   -11,  -11,  207,  -11,  -11,  -11,  -11,  209,  -11,  220,
 /*    90 */   -11,  221,  -11,  222,  -11,  223,  -11,  224,  -11,  225,
 /*   100 */   -11,  226,  -11,  228,  -11,  229,  -11,  230,  -11,  195,
 /*   110 */   231,  -11,  -11,  183,  233,  -11,  235,  -11,
};
static YYACTIONTYPE yy_default[] = {
 /*     0 */   177,  177,  121,  177,  119,  177,  120,  177,  131,  177,
 /*    10 */   133,  177,  134,  177,  135,  177,  136,  177,  137,  177,
 /*    20 */   138,  177,  139,  177,  177,  177,  122,  177,  143,  177,
 /*    30 */   144,  177,  177,  147,  177,  177,  150,  168,  169,  177,
 /*    40 */   177,  160,  177,  177,  161,  177,  123,  177,  124,  177,
 /*    50 */   125,  177,  126,  177,  127,  177,  128,  168,  177,  158,
 /*    60 */   171,  172,  168,  177,  165,  168,  177,  168,  177,  166,
 /*    70 */   170,  173,  162,  177,  177,  163,  164,  177,  159,  168,
 /*    80 */   177,  174,  177,  177,  175,  176,  140,  177,  141,  177,
 /*    90 */   142,  177,  145,  177,  167,  177,  148,  177,  157,  177,
 /*   100 */   149,  177,  155,  177,  154,  177,  153,  177,  156,  130,
 /*   110 */   177,  151,  132,  129,  177,  146,  177,  152,
};
#define YY_SZ_ACTTAB (sizeof(yy_action)/sizeof(yy_action[0]))

/* The next table maps tokens into fallback tokens.  If a construct
** like the following:
** 
**      %fallback ID X Y Z.
**
** appears in the grammer, then ID becomes a fallback token for X, Y,
** and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
** but it does not parse, the type of the token is changed to ID and
** the parse is retried before an error is thrown.
*/
#ifdef YYFALLBACK
static const YYCODETYPE yyFallback[] = {
};
#endif /* YYFALLBACK */

/* The following structure represents a single element of the
** parser's stack.  Information stored includes:
**
**   +  The state number for the parser at this level of the stack.
**
**   +  The value of the token stored at this level of the stack.
**      (In other words, the "major" token.)
**
**   +  The semantic value stored at this level of the stack.  This is
**      the information used by the action routines in the grammar.
**      It is sometimes called the "minor" token.
*/
struct yyStackEntry {
  int stateno;       /* The state-number */
  int major;         /* The major token value.  This is the code
                     ** number for the token at this stack level */
  YYMINORTYPE minor; /* The user-supplied minor token value.  This
                     ** is the value of the token  */
};
typedef struct yyStackEntry yyStackEntry;

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser {
  int yyidx;                    /* Index of top element in stack */
  int yyerrcnt;                 /* Shifts left before out of the error */
  xtxlegalARG_SDECL                /* A place to hold %extra_argument */
  yyStackEntry yystack[YYSTACKDEPTH];  /* The parser's stack */
};
typedef struct yyParser yyParser;

#ifndef NDEBUG
#include <stdio.h>
static FILE *yyTraceFILE = 0;
static const char *yyTracePrompt = 0;
#endif /* NDEBUG */

#ifndef NDEBUG
/* 
** Turn parser tracing on by giving a stream to which to write the trace
** and a prompt to preface each trace message.  Tracing is turned off
** by making either argument NULL 
**
** Inputs:
** <ul>
** <li> A FILE* to which trace output should be written.
**      If NULL, then tracing is turned off.
** <li> A prefix string written at the beginning of every
**      line of trace output.  If NULL, then tracing is
**      turned off.
** </ul>
**
** Outputs:
** None.
*/
void xtxlegalTrace(FILE *TraceFILE, const char *zTracePrompt){
  yyTraceFILE = TraceFILE;
  yyTracePrompt = zTracePrompt;
  if( yyTraceFILE==0 ) yyTracePrompt = 0;
  else if( yyTracePrompt==0 ) yyTraceFILE = 0;
}
void xtxlegalTrace(FILE *TraceFILE, char *zTracePrompt){
  xtxlegalTrace(TraceFILE, (const char*) zTracePrompt);
}
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static const char *yyTokenName[] = { 
  "$",             "EXPR",          "SPACE",         "EXCL",        
  "MINUS",         "PLUS",          "AT",            "SLASH",       
  "BSLASH",        "DOT",           "STAR",          "MODULO",      
  "POWER",         "DOLLAR",        "GT",            "LT",          
  "COLON",         "EQUAL",         "LPAR",          "RPAR",        
  "LBRACKET",      "RBRACKET",      "DOTDOT",        "LBRACE",      
  "RBRACE",        "PIPE",          "COMMA",         "error",       
  "start",         "expr",          "xlst",          "cast",        
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *yyRuleName[] = {
 /*   0 */ "start ::= expr",
 /*   1 */ "expr ::= EXPR",
 /*   2 */ "expr ::= SPACE expr",
 /*   3 */ "expr ::= expr SPACE",
 /*   4 */ "expr ::= EXCL expr",
 /*   5 */ "expr ::= MINUS expr",
 /*   6 */ "expr ::= PLUS expr",
 /*   7 */ "expr ::= AT expr",
 /*   8 */ "expr ::= SLASH expr",
 /*   9 */ "expr ::= BSLASH expr",
 /*  10 */ "expr ::= DOT expr",
 /*  11 */ "expr ::= expr MINUS MINUS",
 /*  12 */ "expr ::= expr PLUS PLUS",
 /*  13 */ "expr ::= expr PLUS expr",
 /*  14 */ "expr ::= expr MINUS expr",
 /*  15 */ "expr ::= expr STAR expr",
 /*  16 */ "expr ::= expr SLASH expr",
 /*  17 */ "expr ::= expr MODULO expr",
 /*  18 */ "expr ::= expr POWER expr",
 /*  19 */ "expr ::= expr DOLLAR expr",
 /*  20 */ "expr ::= expr GT expr",
 /*  21 */ "expr ::= expr LT expr",
 /*  22 */ "expr ::= expr COLON expr",
 /*  23 */ "expr ::= expr COLON COLON expr",
 /*  24 */ "expr ::= expr COLON COLON EQUAL expr",
 /*  25 */ "expr ::= expr DOT expr",
 /*  26 */ "expr ::= expr BSLASH expr",
 /*  27 */ "expr ::= expr COLON EQUAL expr",
 /*  28 */ "expr ::= expr MINUS GT expr",
 /*  29 */ "expr ::= expr EQUAL EQUAL expr",
 /*  30 */ "expr ::= expr LT EQUAL expr",
 /*  31 */ "expr ::= expr GT EQUAL expr",
 /*  32 */ "expr ::= expr EXCL EQUAL expr",
 /*  33 */ "expr ::= expr PLUS EQUAL expr",
 /*  34 */ "expr ::= expr MINUS EQUAL expr",
 /*  35 */ "expr ::= expr STAR EQUAL expr",
 /*  36 */ "expr ::= expr SLASH EQUAL expr",
 /*  37 */ "expr ::= expr MODULO EQUAL expr",
 /*  38 */ "expr ::= expr STAR STAR expr",
 /*  39 */ "expr ::= expr LT GT expr",
 /*  40 */ "expr ::= LPAR xlst RPAR",
 /*  41 */ "expr ::= expr LPAR xlst RPAR",
 /*  42 */ "expr ::= expr LBRACKET expr RBRACKET",
 /*  43 */ "expr ::= expr LBRACKET expr DOTDOT expr RBRACKET",
 /*  44 */ "expr ::= expr LBRACKET expr DOTDOT RBRACKET",
 /*  45 */ "expr ::= expr LBRACKET DOTDOT expr RBRACKET",
 /*  46 */ "expr ::= expr LBRACKET DOTDOT RBRACKET",
 /*  47 */ "expr ::= LBRACE xlst RBRACE",
 /*  48 */ "expr ::= LBRACE PIPE xlst PIPE xlst RBRACE",
 /*  49 */ "expr ::= expr COLON cast expr",
 /*  50 */ "xlst ::=",
 /*  51 */ "xlst ::= expr",
 /*  52 */ "xlst ::= STAR",
 /*  53 */ "xlst ::= xlst COMMA",
 /*  54 */ "xlst ::= xlst COMMA expr",
 /*  55 */ "xlst ::= xlst COMMA STAR",
 /*  56 */ "cast ::= LPAR expr RPAR",
 /*  57 */ "cast ::= LPAR expr AT expr RPAR",
 /*  58 */ "cast ::= SPACE cast",
};
#endif /* NDEBUG */

/*
** This function returns the symbolic name associated with a token
** value.
*/
const char *xtxlegalTokenName(int tokenType){
#ifndef NDEBUG
  if( tokenType>0 && tokenType<(int)(sizeof(yyTokenName)/sizeof(yyTokenName[0])) ){
    return yyTokenName[tokenType];
  }else{
    return "Unknown";
  }
#else
  return "";
#endif
}

/* 
** This function allocates a new parser.
** The only argument is a pointer to a function which works like
** malloc.
**
** Inputs:
** A pointer to the function used to allocate memory.
**
** Outputs:
** A pointer to a parser.  This pointer is used in subsequent calls
** to xtxlegal and xtxlegalFree.
*/
void *xtxlegalAlloc(void *(*mallocProc)(size_t)){
  yyParser *pParser;
  pParser = (yyParser*)(*mallocProc)( (size_t)sizeof(yyParser) );
  if( pParser ){
    pParser->yyidx = -1;
  }
  return pParser;
}

/* The following function deletes the value associated with a
** symbol.  The symbol can be either a terminal or nonterminal.
** "yymajor" is the symbol code, and "yypminor" is a pointer to
** the value.
*/
static void yy_destructor(YYCODETYPE yymajor, YYMINORTYPE *yypminor){
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is 
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are not used
    ** inside the C code.
    */
    default:  break;   /* If no destructor action specified: do nothing */
  }
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
**
** Return the major token number for the symbol popped.
*/
static int yy_pop_parser_stack(yyParser *pParser){
  YYCODETYPE yymajor;
  yyStackEntry *yytos = &pParser->yystack[pParser->yyidx];

  if( pParser->yyidx<0 ) return 0;
#ifndef NDEBUG
  if( yyTraceFILE && pParser->yyidx>=0 ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yymajor = yytos->major;
  yy_destructor( yymajor, &yytos->minor);
  pParser->yyidx--;
  return yymajor;
}

/* 
** Deallocate and destroy a parser.  Destructors are all called for
** all stack elements before shutting the parser down.
**
** Inputs:
** <ul>
** <li>  A pointer to the parser.  This should be a pointer
**       obtained from xtxlegalAlloc.
** <li>  A pointer to a function used to reclaim memory obtained
**       from malloc.
** </ul>
*/
void xtxlegalFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
){
  yyParser *pParser = (yyParser*)p;
  if( pParser==0 ) return;
  while( pParser->yyidx>=0 ) yy_pop_parser_stack(pParser);
  (*freeProc)((void*)pParser);
}

/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_shift_action(
  yyParser *pParser,        /* The parser */
  int iLookAhead            /* The look-ahead token */
){
  int i;
  int stateno = pParser->yystack[pParser->yyidx].stateno;
 
  /* if( pParser->yyidx<0 ) return YY_NO_ACTION;  */
  i = yy_shift_ofst[stateno];
  if( i==YY_SHIFT_USE_DFLT ){
    return yy_default[stateno];
  }
  if( iLookAhead==YYNOCODE ){
    return YY_NO_ACTION;
  }
  i += iLookAhead;
  if( i<0 || i>=(int)YY_SZ_ACTTAB || yy_lookahead[i]!=iLookAhead ){
#ifdef YYFALLBACK
    int iFallback;            /* Fallback token */
    if( iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0])
           && (iFallback = yyFallback[iLookAhead])!=0 ){
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE, "%sFALLBACK %s => %s\n",
           yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[iFallback]);
      }
#endif
      return yy_find_shift_action(pParser, iFallback);
    }
#endif
    return yy_default[stateno];
  }else{
    return yy_action[i];
  }
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_reduce_action(
  yyParser *pParser,        /* The parser */
  int iLookAhead            /* The look-ahead token */
){
  int i;
  int stateno = pParser->yystack[pParser->yyidx].stateno;
 
  i = yy_reduce_ofst[stateno];
  if( i==YY_REDUCE_USE_DFLT ){
    return yy_default[stateno];
  }
  if( iLookAhead==YYNOCODE ){
    return YY_NO_ACTION;
  }
  i += iLookAhead;
  if( i<0 || i>=(int)YY_SZ_ACTTAB || yy_lookahead[i]!=iLookAhead ){
    return yy_default[stateno];
  }else{
    return yy_action[i];
  }
}

/*
** Perform a shift action.
*/
static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  int yyNewState,               /* The new state to shift in */
  int yyMajor,                  /* The major token to shift in */
  YYMINORTYPE *yypMinor         /* Pointer ot the minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yyidx++;
  if( yypParser->yyidx>=YYSTACKDEPTH ){
     xtxlegalARG_FETCH;
     yypParser->yyidx--;
#ifndef NDEBUG
     if( yyTraceFILE ){
       fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
     }
#endif
     while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
     /* Here code is inserted which will execute if the parser
     ** stack every overflows */
     xtxlegalARG_STORE; /* Suppress warning about unused %extra_argument var */
     return;
  }
  yytos = &yypParser->yystack[yypParser->yyidx];
  yytos->stateno = yyNewState;
  yytos->major = yyMajor;
  yytos->minor = *yypMinor;
#ifndef NDEBUG
  if( yyTraceFILE && yypParser->yyidx>0 ){
    int i;
    fprintf(yyTraceFILE,"%sShift %d\n",yyTracePrompt,yyNewState);
    fprintf(yyTraceFILE,"%sStack:",yyTracePrompt);
    for(i=1; i<=yypParser->yyidx; i++)
      fprintf(yyTraceFILE," %s",yyTokenName[yypParser->yystack[i].major]);
    fprintf(yyTraceFILE,"\n");
  }
#endif
}

/* The following table contains information about every rule that
** is used during the reduce.
*/
static struct {
  YYCODETYPE lhs;         /* Symbol on the left-hand side of the rule */
  unsigned char nrhs;     /* Number of right-hand side symbols in the rule */
} yyRuleInfo[] = {
  { 28, 1 },
  { 29, 1 },
  { 29, 2 },
  { 29, 2 },
  { 29, 2 },
  { 29, 2 },
  { 29, 2 },
  { 29, 2 },
  { 29, 2 },
  { 29, 2 },
  { 29, 2 },
  { 29, 3 },
  { 29, 3 },
  { 29, 3 },
  { 29, 3 },
  { 29, 3 },
  { 29, 3 },
  { 29, 3 },
  { 29, 3 },
  { 29, 3 },
  { 29, 3 },
  { 29, 3 },
  { 29, 3 },
  { 29, 4 },
  { 29, 5 },
  { 29, 3 },
  { 29, 3 },
  { 29, 4 },
  { 29, 4 },
  { 29, 4 },
  { 29, 4 },
  { 29, 4 },
  { 29, 4 },
  { 29, 4 },
  { 29, 4 },
  { 29, 4 },
  { 29, 4 },
  { 29, 4 },
  { 29, 4 },
  { 29, 4 },
  { 29, 3 },
  { 29, 4 },
  { 29, 4 },
  { 29, 6 },
  { 29, 5 },
  { 29, 5 },
  { 29, 4 },
  { 29, 3 },
  { 29, 6 },
  { 29, 4 },
  { 30, 0 },
  { 30, 1 },
  { 30, 1 },
  { 30, 2 },
  { 30, 3 },
  { 30, 3 },
  { 31, 3 },
  { 31, 5 },
  { 31, 2 },
};

static void yy_accept(yyParser*);  /* Forward Declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
*/
static void yy_reduce(
  yyParser *yypParser,         /* The parser */
  int yyruleno                 /* Number of the rule by which to reduce */
){
  int yygoto;                     /* The next state */
  int yyact;                      /* The next action */
  YYMINORTYPE yygotominor;        /* The LHS of the rule reduced */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  xtxlegalARG_FETCH;
  yymsp = &yypParser->yystack[yypParser->yyidx];
#ifndef NDEBUG
  if( yyTraceFILE && yyruleno>=0 
        && yyruleno<(int)(sizeof(yyRuleName)/sizeof(yyRuleName[0])) ){
    fprintf(yyTraceFILE, "%sReduce [%s].\n", yyTracePrompt,
      yyRuleName[yyruleno]);
  }
#endif /* NDEBUG */

  switch( yyruleno ){
  /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
      case 0:
        /* No destructor defined for expr */
        break;
      case 1:
#line 285 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[0].minor.yy0,yymsp[0].minor.yy0);}
#line 1030 "./xtxlegal.c"
        break;
      case 2:
#line 287 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1035 "./xtxlegal.c"
        break;
      case 3:
#line 288 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1040 "./xtxlegal.c"
        break;
      case 4:
#line 290 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1045 "./xtxlegal.c"
        break;
      case 5:
#line 291 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1050 "./xtxlegal.c"
        break;
      case 6:
#line 292 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1055 "./xtxlegal.c"
        break;
      case 7:
#line 293 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1060 "./xtxlegal.c"
        break;
      case 8:
#line 294 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1065 "./xtxlegal.c"
        break;
      case 9:
#line 295 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1070 "./xtxlegal.c"
        break;
      case 10:
#line 296 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1075 "./xtxlegal.c"
        break;
      case 11:
#line 298 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1080 "./xtxlegal.c"
        /* No destructor defined for MINUS */
        break;
      case 12:
#line 299 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1086 "./xtxlegal.c"
        /* No destructor defined for PLUS */
        break;
      case 13:
#line 301 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1092 "./xtxlegal.c"
        /* No destructor defined for PLUS */
        break;
      case 14:
#line 302 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1098 "./xtxlegal.c"
        /* No destructor defined for MINUS */
        break;
      case 15:
#line 303 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1104 "./xtxlegal.c"
        /* No destructor defined for STAR */
        break;
      case 16:
#line 304 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1110 "./xtxlegal.c"
        /* No destructor defined for SLASH */
        break;
      case 17:
#line 305 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1116 "./xtxlegal.c"
        /* No destructor defined for MODULO */
        break;
      case 18:
#line 306 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1122 "./xtxlegal.c"
        /* No destructor defined for POWER */
        break;
      case 19:
#line 307 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1128 "./xtxlegal.c"
        /* No destructor defined for DOLLAR */
        break;
      case 20:
#line 308 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1134 "./xtxlegal.c"
        /* No destructor defined for GT */
        break;
      case 21:
#line 309 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1140 "./xtxlegal.c"
        /* No destructor defined for LT */
        break;
      case 22:
#line 310 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1146 "./xtxlegal.c"
        /* No destructor defined for COLON */
        break;
      case 23:
#line 311 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1152 "./xtxlegal.c"
        /* No destructor defined for COLON */
        /* No destructor defined for COLON */
        break;
      case 24:
#line 312 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-4].minor.yy0,yymsp[0].minor.yy0);}
#line 1159 "./xtxlegal.c"
        /* No destructor defined for COLON */
        /* No destructor defined for COLON */
        /* No destructor defined for EQUAL */
        break;
      case 25:
#line 313 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1167 "./xtxlegal.c"
        /* No destructor defined for DOT */
        break;
      case 26:
#line 314 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1173 "./xtxlegal.c"
        /* No destructor defined for BSLASH */
        break;
      case 27:
#line 316 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1179 "./xtxlegal.c"
        /* No destructor defined for COLON */
        /* No destructor defined for EQUAL */
        break;
      case 28:
#line 317 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1186 "./xtxlegal.c"
        /* No destructor defined for MINUS */
        /* No destructor defined for GT */
        break;
      case 29:
#line 318 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1193 "./xtxlegal.c"
        /* No destructor defined for EQUAL */
        /* No destructor defined for EQUAL */
        break;
      case 30:
#line 319 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1200 "./xtxlegal.c"
        /* No destructor defined for LT */
        /* No destructor defined for EQUAL */
        break;
      case 31:
#line 320 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1207 "./xtxlegal.c"
        /* No destructor defined for GT */
        /* No destructor defined for EQUAL */
        break;
      case 32:
#line 321 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1214 "./xtxlegal.c"
        /* No destructor defined for EXCL */
        /* No destructor defined for EQUAL */
        break;
      case 33:
#line 322 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1221 "./xtxlegal.c"
        /* No destructor defined for PLUS */
        /* No destructor defined for EQUAL */
        break;
      case 34:
#line 323 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1228 "./xtxlegal.c"
        /* No destructor defined for MINUS */
        /* No destructor defined for EQUAL */
        break;
      case 35:
#line 324 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1235 "./xtxlegal.c"
        /* No destructor defined for STAR */
        /* No destructor defined for EQUAL */
        break;
      case 36:
#line 325 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1242 "./xtxlegal.c"
        /* No destructor defined for SLASH */
        /* No destructor defined for EQUAL */
        break;
      case 37:
#line 326 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1249 "./xtxlegal.c"
        /* No destructor defined for MODULO */
        /* No destructor defined for EQUAL */
        break;
      case 38:
#line 327 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1256 "./xtxlegal.c"
        /* No destructor defined for STAR */
        /* No destructor defined for STAR */
        break;
      case 39:
#line 329 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1263 "./xtxlegal.c"
        /* No destructor defined for LT */
        /* No destructor defined for GT */
        break;
      case 40:
#line 331 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1270 "./xtxlegal.c"
        /* No destructor defined for xlst */
        break;
      case 41:
#line 332 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1276 "./xtxlegal.c"
        /* No destructor defined for LPAR */
        /* No destructor defined for xlst */
        break;
      case 42:
#line 333 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1283 "./xtxlegal.c"
        /* No destructor defined for LBRACKET */
        /* No destructor defined for expr */
        break;
      case 43:
#line 334 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-5].minor.yy0,yymsp[0].minor.yy0);}
#line 1290 "./xtxlegal.c"
        /* No destructor defined for LBRACKET */
        /* No destructor defined for expr */
        /* No destructor defined for DOTDOT */
        /* No destructor defined for expr */
        break;
      case 44:
#line 335 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-4].minor.yy0,yymsp[0].minor.yy0);}
#line 1299 "./xtxlegal.c"
        /* No destructor defined for LBRACKET */
        /* No destructor defined for expr */
        /* No destructor defined for DOTDOT */
        break;
      case 45:
#line 336 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-4].minor.yy0,yymsp[0].minor.yy0);}
#line 1307 "./xtxlegal.c"
        /* No destructor defined for LBRACKET */
        /* No destructor defined for DOTDOT */
        /* No destructor defined for expr */
        break;
      case 46:
#line 337 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1315 "./xtxlegal.c"
        /* No destructor defined for LBRACKET */
        /* No destructor defined for DOTDOT */
        break;
      case 47:
#line 338 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1322 "./xtxlegal.c"
        /* No destructor defined for xlst */
        break;
      case 48:
#line 339 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-5].minor.yy0,yymsp[0].minor.yy0);}
#line 1328 "./xtxlegal.c"
        /* No destructor defined for PIPE */
        /* No destructor defined for xlst */
        /* No destructor defined for PIPE */
        /* No destructor defined for xlst */
        break;
      case 49:
#line 341 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1337 "./xtxlegal.c"
        /* No destructor defined for COLON */
        /* No destructor defined for cast */
        break;
      case 50:
        break;
      case 51:
        /* No destructor defined for expr */
        break;
      case 52:
        /* No destructor defined for STAR */
        break;
      case 53:
        /* No destructor defined for xlst */
        /* No destructor defined for COMMA */
        break;
      case 54:
        /* No destructor defined for xlst */
        /* No destructor defined for COMMA */
        /* No destructor defined for expr */
        break;
      case 55:
        /* No destructor defined for xlst */
        /* No destructor defined for COMMA */
        /* No destructor defined for STAR */
        break;
      case 56:
        /* No destructor defined for LPAR */
        /* No destructor defined for expr */
        /* No destructor defined for RPAR */
        break;
      case 57:
        /* No destructor defined for LPAR */
        /* No destructor defined for expr */
        /* No destructor defined for AT */
        /* No destructor defined for expr */
        /* No destructor defined for RPAR */
        break;
      case 58:
        /* No destructor defined for SPACE */
        /* No destructor defined for cast */
        break;
  };
  yygoto = yyRuleInfo[yyruleno].lhs;
  yysize = yyRuleInfo[yyruleno].nrhs;
  yypParser->yyidx -= yysize;
  yyact = yy_find_reduce_action(yypParser,yygoto);
  if( yyact < YYNSTATE ){
    yy_shift(yypParser,yyact,yygoto,&yygotominor);
  }else if( yyact == YYNSTATE + YYNRULE + 1 ){
    yy_accept(yypParser);
  }
}

/*
** The following code executes when the parse fails
*/
static void yy_parse_failed(
  yyParser *yypParser           /* The parser */
){
  xtxlegalARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
  xtxlegalARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  YYMINORTYPE yyminor            /* The minor type of the error token */
){
  xtxlegalARG_FETCH;
#define TOKEN (yyminor.yy0)
#line 270 "./xtxlegal.lem"

    //printf("Syntax error.\n");
    termflag=1;

#line 1424 "./xtxlegal.c"
  xtxlegalARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  xtxlegalARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
#line 275 "./xtxlegal.lem"

    //printf("Parsing complete.\n");

#line 1447 "./xtxlegal.c"
  xtxlegalARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "xtxlegalAlloc" which describes the current state of the parser.
** The second argument is the major token number.  The third is
** the minor token.  The fourth optional argument is whatever the
** user wants (and specified in the grammar) and is available for
** use by the action routines.
**
** Inputs:
** <ul>
** <li> A pointer to the parser (an opaque structure.)
** <li> The major token number.
** <li> The minor token number.
** <li> An option argument of a grammar-specified type.
** </ul>
**
** Outputs:
** None.
*/
void xtxlegal(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  xtxlegalTOKENTYPE yyminor       /* The value for the token */
  xtxlegalARG_PDECL               /* Optional %extra_argument parameter */
){
  YYMINORTYPE yyminorunion;
  int yyact;            /* The parser action. */
  int yyendofinput;     /* True if we are at the end of input */
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
  yyParser *yypParser;  /* The parser */

  /* (re)initialize the parser, if necessary */
  yypParser = (yyParser*)yyp;
  if( yypParser->yyidx<0 ){
    if( yymajor==0 ) return;
    yypParser->yyidx = 0;
    yypParser->yyerrcnt = -1;
    yypParser->yystack[0].stateno = 0;
    yypParser->yystack[0].major = 0;
  }
  yyminorunion.yy0 = yyminor;
  yyendofinput = (yymajor==0);
  xtxlegalARG_STORE;

#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sInput %s\n",yyTracePrompt,yyTokenName[yymajor]);
  }
#endif

  do{
    yyact = yy_find_shift_action(yypParser,yymajor);
    if( yyact<YYNSTATE ){
      yy_shift(yypParser,yyact,yymajor,&yyminorunion);
      yypParser->yyerrcnt--;
      if( yyendofinput && yypParser->yyidx>=0 ){
        yymajor = 0;
      }else{
        yymajor = YYNOCODE;
      }
    }else if( yyact < YYNSTATE + YYNRULE ){
      yy_reduce(yypParser,yyact-YYNSTATE);
    }else if( yyact == YY_ERROR_ACTION ){
      int yymx;
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE,"%sSyntax Error!\n",yyTracePrompt);
      }
#endif
#ifdef YYERRORSYMBOL
      /* A syntax error has occurred.
      ** The response to an error depends upon whether or not the
      ** grammar defines an error token "ERROR".  
      **
      ** This is what we do if the grammar does define ERROR:
      **
      **  * Call the %syntax_error function.
      **
      **  * Begin popping the stack until we enter a state where
      **    it is legal to shift the error symbol, then shift
      **    the error symbol.
      **
      **  * Set the error count to three.
      **
      **  * Begin accepting and shifting new tokens.  No new error
      **    processing will occur until three tokens have been
      **    shifted successfully.
      **
      */
      if( yypParser->yyerrcnt<0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yymx = yypParser->yystack[yypParser->yyidx].major;
      if( yymx==YYERRORSYMBOL || yyerrorhit ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE,"%sDiscard input token %s\n",
             yyTracePrompt,yyTokenName[yymajor]);
        }
#endif
        yy_destructor(yymajor,&yyminorunion);
        yymajor = YYNOCODE;
      }else{
         while(
          yypParser->yyidx >= 0 &&
          yymx != YYERRORSYMBOL &&
          (yyact = yy_find_shift_action(yypParser,YYERRORSYMBOL)) >= YYNSTATE
        ){
          yy_pop_parser_stack(yypParser);
        }
        if( yypParser->yyidx < 0 || yymajor==0 ){
          yy_destructor(yymajor,&yyminorunion);
          yy_parse_failed(yypParser);
          yymajor = YYNOCODE;
        }else if( yymx!=YYERRORSYMBOL ){
          YYMINORTYPE u2;
          u2.YYERRSYMDT = 0;
          yy_shift(yypParser,yyact,YYERRORSYMBOL,&u2);
        }
      }
      yypParser->yyerrcnt = 3;
      yyerrorhit = 1;
#else  /* YYERRORSYMBOL is not defined */
      /* This is what we do if the grammar does not define ERROR:
      **
      **  * Report an error message, and throw away the input token.
      **
      **  * If the input token is $, then fail the parse.
      **
      ** As before, subsequent error messages are suppressed until
      ** three input tokens have been successfully shifted.
      */
      if( yypParser->yyerrcnt<=0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yypParser->yyerrcnt = 3;
      yy_destructor(yymajor,&yyminorunion);
      if( yyendofinput ){
        yy_parse_failed(yypParser);
      }
      yymajor = YYNOCODE;
#endif
    }else{
      yy_accept(yypParser);
      yymajor = YYNOCODE;
    }
  }while( yymajor!=YYNOCODE && yypParser->yyidx>=0 );
  return;
}
