
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

#line 256 "./xtxlegal.c"
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
#define YYNOCODE 32
#define YYACTIONTYPE unsigned char
#define xtxlegalTOKENTYPE POS
typedef union {
  xtxlegalTOKENTYPE yy0;
  int yy63;
} YYMINORTYPE;
#define YYSTACKDEPTH 100
#define xtxlegalARG_SDECL
#define xtxlegalARG_PDECL
#define xtxlegalARG_FETCH
#define xtxlegalARG_STORE
#define YYNSTATE 106
#define YYNRULE 53
#define YYERRORSYMBOL 26
#define YYERRSYMDT yy63
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
 /*     0 */     2,   34,    3,    7,   74,   11,   29,   27,    9,   13,
 /*    10 */    15,   17,   19,   21,   23,   31,   37,   73,   39,  160,
 /*    20 */     1,   38,   69,  151,  106,  100,    2,   34,    3,    7,
 /*    30 */     6,   11,   29,   27,    9,   13,   15,   17,   19,   21,
 /*    40 */    23,   31,   37,    8,   39,    2,   34,    3,    7,   10,
 /*    50 */    11,   29,   27,    9,   13,   15,   17,   19,   21,   23,
 /*    60 */    31,   37,   12,   39,   41,   14,    2,   34,    3,    7,
 /*    70 */    16,   11,   29,   27,    9,   13,   15,   17,   19,   21,
 /*    80 */    23,   31,   37,   76,   39,    2,   34,    3,    7,   18,
 /*    90 */    11,   29,   27,    9,   13,   15,   17,   19,   21,   23,
 /*   100 */    31,   37,   78,   39,   81,    4,    5,   25,  101,   44,
 /*   110 */    46,   48,   50,   52,    6,   20,   77,   56,  102,   38,
 /*   120 */    55,  104,   54,   57,   38,   60,   59,   22,    4,    5,
 /*   130 */    25,   42,   44,   46,   48,   50,   52,   95,   61,   26,
 /*   140 */    57,   38,   63,   32,   93,   54,   64,   57,   66,   59,
 /*   150 */    57,    4,    5,   25,   42,   44,   46,   48,   50,   52,
 /*   160 */    38,   65,   72,   55,   85,   70,   28,   83,   54,   30,
 /*   170 */    33,   57,   59,   35,    4,    5,   25,   42,   44,   46,
 /*   180 */    48,   50,   52,   67,   86,   36,   40,   43,   45,   47,
 /*   190 */    49,   54,   51,   53,   58,   59,   75,   62,   80,    4,
 /*   200 */     5,   25,   42,   97,   46,   48,   50,   52,   82,   84,
 /*   210 */    86,   88,   90,   86,   92,   98,   54,   94,   96,   99,
 /*   220 */    59,  103,    4,    5,   25,   42,   44,   46,   48,   50,
 /*   230 */    52,  105,   86,   86,   86,   86,   86,   86,   91,   54,
 /*   240 */    86,   86,   86,   59,   86,    4,    5,   25,   42,   44,
 /*   250 */    46,   48,   50,   52,   86,   86,   86,   86,   86,   86,
 /*   260 */    86,   89,   54,   86,   86,   86,   59,   86,    4,    5,
 /*   270 */    25,   42,   44,   46,   48,   50,   52,   86,   86,   86,
 /*   280 */    86,   86,   86,   86,   87,   54,   86,   86,   86,   59,
 /*   290 */    86,    4,   24,   25,   42,   44,   46,   48,   50,   52,
 /*   300 */    86,   86,   86,   86,   86,   86,   86,   79,   71,   86,
 /*   310 */    86,   86,   59,   86,    4,    5,   25,   42,   44,   46,
 /*   320 */    48,   50,   52,   67,   86,   86,   86,   86,   86,   86,
 /*   330 */    86,   54,   86,   86,   86,   59,   86,    4,    5,   25,
 /*   340 */    42,   44,   46,   48,   50,   52,   68,   86,   86,   86,
 /*   350 */    86,   86,   86,   86,   54,   86,   86,   86,   59,   86,
 /*   360 */     4,    5,   25,   42,   44,   46,   48,   50,   52,   86,
 /*   370 */    86,   86,   86,   86,   86,   86,   86,   54,   86,   86,
 /*   380 */    86,   59,   86,    4,   24,   25,   42,   44,   46,   48,
 /*   390 */    50,   52,   86,   86,   86,   86,   86,   86,   86,   86,
 /*   400 */    71,   86,   86,   86,   59,
};
static YYCODETYPE yy_lookahead[] = {
 /*     0 */     2,    3,    4,    5,    6,    7,    8,    9,   10,   11,
 /*    10 */    12,   13,   14,   15,   16,   17,   18,   19,   20,   27,
 /*    20 */    28,   28,   29,   25,    0,   28,    2,    3,    4,    5,
 /*    30 */    28,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*    40 */    16,   17,   18,   28,   20,    2,    3,    4,    5,   28,
 /*    50 */     7,    8,    9,   10,   11,   12,   13,   14,   15,   16,
 /*    60 */    17,   18,   28,   20,   21,   28,    2,    3,    4,    5,
 /*    70 */    28,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*    80 */    16,   17,   18,   19,   20,    2,    3,    4,    5,   28,
 /*    90 */     7,    8,    9,   10,   11,   12,   13,   14,   15,   16,
 /*   100 */    17,   18,   28,   20,   30,    1,    2,    3,    4,    5,
 /*   110 */     6,    7,    8,    9,   28,   28,   30,   19,   14,   28,
 /*   120 */    29,   17,   18,   25,   28,   29,   22,   28,    1,    2,
 /*   130 */     3,    4,    5,    6,    7,    8,    9,   10,   23,   28,
 /*   140 */    25,   28,   29,   17,   17,   18,   24,   25,   23,   22,
 /*   150 */    25,    1,    2,    3,    4,    5,    6,    7,    8,    9,
 /*   160 */    28,   29,   28,   29,   14,   19,   28,   17,   18,   28,
 /*   170 */    28,   25,   22,   17,    1,    2,    3,    4,    5,    6,
 /*   180 */     7,    8,    9,   10,   31,   28,   28,   28,   28,   28,
 /*   190 */    28,   18,   28,   28,   28,   22,   28,   24,   28,    1,
 /*   200 */     2,    3,    4,    5,    6,    7,    8,    9,   28,   28,
 /*   210 */    28,   28,   28,   31,   28,   17,   18,   28,   28,   28,
 /*   220 */    22,   28,    1,    2,    3,    4,    5,    6,    7,    8,
 /*   230 */     9,   28,   31,   31,   31,   31,   31,   31,   17,   18,
 /*   240 */    31,   31,   31,   22,   31,    1,    2,    3,    4,    5,
 /*   250 */     6,    7,    8,    9,   31,   31,   31,   31,   31,   31,
 /*   260 */    31,   17,   18,   31,   31,   31,   22,   31,    1,    2,
 /*   270 */     3,    4,    5,    6,    7,    8,    9,   31,   31,   31,
 /*   280 */    31,   31,   31,   31,   17,   18,   31,   31,   31,   22,
 /*   290 */    31,    1,    2,    3,    4,    5,    6,    7,    8,    9,
 /*   300 */    31,   31,   31,   31,   31,   31,   31,   17,   18,   31,
 /*   310 */    31,   31,   22,   31,    1,    2,    3,    4,    5,    6,
 /*   320 */     7,    8,    9,   10,   31,   31,   31,   31,   31,   31,
 /*   330 */    31,   18,   31,   31,   31,   22,   31,    1,    2,    3,
 /*   340 */     4,    5,    6,    7,    8,    9,   10,   31,   31,   31,
 /*   350 */    31,   31,   31,   31,   18,   31,   31,   31,   22,   31,
 /*   360 */     1,    2,    3,    4,    5,    6,    7,    8,    9,   31,
 /*   370 */    31,   31,   31,   31,   31,   31,   31,   18,   31,   31,
 /*   380 */    31,   22,   31,    1,    2,    3,    4,    5,    6,    7,
 /*   390 */     8,    9,   31,   31,   31,   31,   31,   31,   31,   31,
 /*   400 */    18,   31,   31,   31,   22,
};
#define YY_SHIFT_USE_DFLT (-3)
static short yy_shift_ofst[] = {
 /*     0 */   359,   24,   -3,  104,   -3,  359,   83,  198,   83,  127,
 /*    10 */    83,  221,   83,  244,   83,  359,   83,  359,   83,  267,
 /*    20 */    83,  150,   83,  290,  382,  359,   83,  359,   83,  359,
 /*    30 */    83,  126,  359,   83,  156,  359,   83,  313,   83,  359,
 /*    40 */    43,   -3,  359,   83,  359,   83,  359,   83,  359,   83,
 /*    50 */   359,   83,  359,   83,  313,   98,   -3,  336,   83,  173,
 /*    60 */   115,   -3,  313,  122,  313,  125,   -3,   -3,   -3,  146,
 /*    70 */    -3,  313,   -2,   -3,  359,   64,   -3,   -3,   83,  359,
 /*    80 */    83,  359,   83,  359,   83,  359,   83,  359,   83,  359,
 /*    90 */    83,  359,   83,  359,   83,  359,   83,  359,  359,   83,
 /*   100 */    83,  359,  359,   83,  359,   83,
};
#define YY_REDUCE_USE_DFLT (-9)
static short yy_reduce_ofst[] = {
 /*     0 */    -8,   -9,   -9,   -3,   -9,    2,   -9,   15,   -9,   21,
 /*    10 */    -9,   34,   -9,   37,   -9,   42,   -9,   61,   -9,   87,
 /*    20 */    -9,   99,   -9,   74,   86,  111,   -9,  138,   -9,  141,
 /*    30 */    -9,   -9,  142,   -9,   -9,  157,   -9,   -7,   -9,  158,
 /*    40 */    -9,   -9,  159,   -9,  160,   -9,  161,   -9,  162,   -9,
 /*    50 */   164,   -9,  165,   -9,   91,   -9,   -9,  166,   -9,   96,
 /*    60 */    -9,   -9,  113,   -9,  132,   -9,   -9,   -9,   -9,   -9,
 /*    70 */    -9,  134,   -9,   -9,  168,   -9,   -9,   -9,   -9,  170,
 /*    80 */    -9,  180,   -9,  181,   -9,  182,   -9,  183,   -9,  184,
 /*    90 */    -9,  186,   -9,  189,   -9,  190,   -9,  160,  191,   -9,
 /*   100 */    -9,  159,  193,   -9,  203,   -9,
};
static YYACTIONTYPE yy_default[] = {
 /*     0 */   159,  159,  109,  159,  107,  159,  108,  159,  119,  159,
 /*    10 */   121,  159,  122,  159,  123,  159,  124,  159,  125,  159,
 /*    20 */   126,  159,  127,  159,  159,  159,  110,  159,  129,  159,
 /*    30 */   130,  159,  159,  133,  159,  159,  136,  150,  151,  159,
 /*    40 */   159,  146,  159,  111,  159,  112,  159,  113,  159,  114,
 /*    50 */   159,  115,  159,  116,  150,  159,  144,  153,  154,  150,
 /*    60 */   159,  147,  150,  159,  150,  159,  148,  152,  155,  159,
 /*    70 */   145,  150,  159,  156,  159,  159,  157,  158,  128,  159,
 /*    80 */   131,  159,  149,  159,  134,  159,  143,  159,  135,  159,
 /*    90 */   141,  159,  140,  159,  139,  159,  142,  118,  159,  137,
 /*   100 */   120,  117,  159,  132,  159,  138,
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
  "LBRACKET",      "RBRACKET",      "LBRACE",        "RBRACE",      
  "PIPE",          "COMMA",         "error",         "start",       
  "expr",          "xlst",          "cast",        
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
 /*  23 */ "expr ::= expr DOT expr",
 /*  24 */ "expr ::= expr BSLASH expr",
 /*  25 */ "expr ::= expr COLON EQUAL expr",
 /*  26 */ "expr ::= expr MINUS GT expr",
 /*  27 */ "expr ::= expr EQUAL EQUAL expr",
 /*  28 */ "expr ::= expr LT EQUAL expr",
 /*  29 */ "expr ::= expr GT EQUAL expr",
 /*  30 */ "expr ::= expr EXCL EQUAL expr",
 /*  31 */ "expr ::= expr PLUS EQUAL expr",
 /*  32 */ "expr ::= expr MINUS EQUAL expr",
 /*  33 */ "expr ::= expr STAR EQUAL expr",
 /*  34 */ "expr ::= expr SLASH EQUAL expr",
 /*  35 */ "expr ::= expr MODULO EQUAL expr",
 /*  36 */ "expr ::= expr STAR STAR expr",
 /*  37 */ "expr ::= expr LT GT expr",
 /*  38 */ "expr ::= LPAR xlst RPAR",
 /*  39 */ "expr ::= expr LPAR xlst RPAR",
 /*  40 */ "expr ::= expr LBRACKET expr RBRACKET",
 /*  41 */ "expr ::= LBRACE xlst RBRACE",
 /*  42 */ "expr ::= LBRACE PIPE xlst PIPE xlst RBRACE",
 /*  43 */ "expr ::= expr COLON cast expr",
 /*  44 */ "xlst ::=",
 /*  45 */ "xlst ::= expr",
 /*  46 */ "xlst ::= STAR",
 /*  47 */ "xlst ::= xlst COMMA",
 /*  48 */ "xlst ::= xlst COMMA expr",
 /*  49 */ "xlst ::= xlst COMMA STAR",
 /*  50 */ "cast ::= LPAR expr RPAR",
 /*  51 */ "cast ::= LPAR expr AT expr RPAR",
 /*  52 */ "cast ::= SPACE cast",
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
  { 27, 1 },
  { 28, 1 },
  { 28, 2 },
  { 28, 2 },
  { 28, 2 },
  { 28, 2 },
  { 28, 2 },
  { 28, 2 },
  { 28, 2 },
  { 28, 2 },
  { 28, 2 },
  { 28, 3 },
  { 28, 3 },
  { 28, 3 },
  { 28, 3 },
  { 28, 3 },
  { 28, 3 },
  { 28, 3 },
  { 28, 3 },
  { 28, 3 },
  { 28, 3 },
  { 28, 3 },
  { 28, 3 },
  { 28, 3 },
  { 28, 3 },
  { 28, 4 },
  { 28, 4 },
  { 28, 4 },
  { 28, 4 },
  { 28, 4 },
  { 28, 4 },
  { 28, 4 },
  { 28, 4 },
  { 28, 4 },
  { 28, 4 },
  { 28, 4 },
  { 28, 4 },
  { 28, 4 },
  { 28, 3 },
  { 28, 4 },
  { 28, 4 },
  { 28, 3 },
  { 28, 6 },
  { 28, 4 },
  { 29, 0 },
  { 29, 1 },
  { 29, 1 },
  { 29, 2 },
  { 29, 3 },
  { 29, 3 },
  { 30, 3 },
  { 30, 5 },
  { 30, 2 },
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
#line 281 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[0].minor.yy0,yymsp[0].minor.yy0);}
#line 981 "./xtxlegal.c"
        break;
      case 2:
#line 283 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 986 "./xtxlegal.c"
        break;
      case 3:
#line 284 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 991 "./xtxlegal.c"
        break;
      case 4:
#line 286 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 996 "./xtxlegal.c"
        break;
      case 5:
#line 287 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1001 "./xtxlegal.c"
        break;
      case 6:
#line 288 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1006 "./xtxlegal.c"
        break;
      case 7:
#line 289 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1011 "./xtxlegal.c"
        break;
      case 8:
#line 290 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1016 "./xtxlegal.c"
        break;
      case 9:
#line 291 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1021 "./xtxlegal.c"
        break;
      case 10:
#line 292 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1026 "./xtxlegal.c"
        break;
      case 11:
#line 294 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1031 "./xtxlegal.c"
        /* No destructor defined for MINUS */
        break;
      case 12:
#line 295 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1037 "./xtxlegal.c"
        /* No destructor defined for PLUS */
        break;
      case 13:
#line 297 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1043 "./xtxlegal.c"
        /* No destructor defined for PLUS */
        break;
      case 14:
#line 298 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1049 "./xtxlegal.c"
        /* No destructor defined for MINUS */
        break;
      case 15:
#line 299 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1055 "./xtxlegal.c"
        /* No destructor defined for STAR */
        break;
      case 16:
#line 300 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1061 "./xtxlegal.c"
        /* No destructor defined for SLASH */
        break;
      case 17:
#line 301 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1067 "./xtxlegal.c"
        /* No destructor defined for MODULO */
        break;
      case 18:
#line 302 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1073 "./xtxlegal.c"
        /* No destructor defined for POWER */
        break;
      case 19:
#line 303 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1079 "./xtxlegal.c"
        /* No destructor defined for DOLLAR */
        break;
      case 20:
#line 304 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1085 "./xtxlegal.c"
        /* No destructor defined for GT */
        break;
      case 21:
#line 305 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1091 "./xtxlegal.c"
        /* No destructor defined for LT */
        break;
      case 22:
#line 306 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1097 "./xtxlegal.c"
        /* No destructor defined for COLON */
        break;
      case 23:
#line 307 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1103 "./xtxlegal.c"
        /* No destructor defined for DOT */
        break;
      case 24:
#line 308 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1109 "./xtxlegal.c"
        /* No destructor defined for BSLASH */
        break;
      case 25:
#line 310 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1115 "./xtxlegal.c"
        /* No destructor defined for COLON */
        /* No destructor defined for EQUAL */
        break;
      case 26:
#line 311 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1122 "./xtxlegal.c"
        /* No destructor defined for MINUS */
        /* No destructor defined for GT */
        break;
      case 27:
#line 312 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1129 "./xtxlegal.c"
        /* No destructor defined for EQUAL */
        /* No destructor defined for EQUAL */
        break;
      case 28:
#line 313 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1136 "./xtxlegal.c"
        /* No destructor defined for LT */
        /* No destructor defined for EQUAL */
        break;
      case 29:
#line 314 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1143 "./xtxlegal.c"
        /* No destructor defined for GT */
        /* No destructor defined for EQUAL */
        break;
      case 30:
#line 315 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1150 "./xtxlegal.c"
        /* No destructor defined for EXCL */
        /* No destructor defined for EQUAL */
        break;
      case 31:
#line 316 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1157 "./xtxlegal.c"
        /* No destructor defined for PLUS */
        /* No destructor defined for EQUAL */
        break;
      case 32:
#line 317 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1164 "./xtxlegal.c"
        /* No destructor defined for MINUS */
        /* No destructor defined for EQUAL */
        break;
      case 33:
#line 318 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1171 "./xtxlegal.c"
        /* No destructor defined for STAR */
        /* No destructor defined for EQUAL */
        break;
      case 34:
#line 319 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1178 "./xtxlegal.c"
        /* No destructor defined for SLASH */
        /* No destructor defined for EQUAL */
        break;
      case 35:
#line 320 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1185 "./xtxlegal.c"
        /* No destructor defined for MODULO */
        /* No destructor defined for EQUAL */
        break;
      case 36:
#line 321 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1192 "./xtxlegal.c"
        /* No destructor defined for STAR */
        /* No destructor defined for STAR */
        break;
      case 37:
#line 323 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1199 "./xtxlegal.c"
        /* No destructor defined for LT */
        /* No destructor defined for GT */
        break;
      case 38:
#line 325 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1206 "./xtxlegal.c"
        /* No destructor defined for xlst */
        break;
      case 39:
#line 326 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1212 "./xtxlegal.c"
        /* No destructor defined for LPAR */
        /* No destructor defined for xlst */
        break;
      case 40:
#line 327 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1219 "./xtxlegal.c"
        /* No destructor defined for LBRACKET */
        /* No destructor defined for expr */
        break;
      case 41:
#line 328 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1226 "./xtxlegal.c"
        /* No destructor defined for xlst */
        break;
      case 42:
#line 329 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-5].minor.yy0,yymsp[0].minor.yy0);}
#line 1232 "./xtxlegal.c"
        /* No destructor defined for PIPE */
        /* No destructor defined for xlst */
        /* No destructor defined for PIPE */
        /* No destructor defined for xlst */
        break;
      case 43:
#line 331 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1241 "./xtxlegal.c"
        /* No destructor defined for COLON */
        /* No destructor defined for cast */
        break;
      case 44:
        break;
      case 45:
        /* No destructor defined for expr */
        break;
      case 46:
        /* No destructor defined for STAR */
        break;
      case 47:
        /* No destructor defined for xlst */
        /* No destructor defined for COMMA */
        break;
      case 48:
        /* No destructor defined for xlst */
        /* No destructor defined for COMMA */
        /* No destructor defined for expr */
        break;
      case 49:
        /* No destructor defined for xlst */
        /* No destructor defined for COMMA */
        /* No destructor defined for STAR */
        break;
      case 50:
        /* No destructor defined for LPAR */
        /* No destructor defined for expr */
        /* No destructor defined for RPAR */
        break;
      case 51:
        /* No destructor defined for LPAR */
        /* No destructor defined for expr */
        /* No destructor defined for AT */
        /* No destructor defined for expr */
        /* No destructor defined for RPAR */
        break;
      case 52:
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
#line 266 "./xtxlegal.lem"

    //printf("Syntax error.\n");
    termflag=1;

#line 1328 "./xtxlegal.c"
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
#line 271 "./xtxlegal.lem"

    //printf("Parsing complete.\n");

#line 1351 "./xtxlegal.c"
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
