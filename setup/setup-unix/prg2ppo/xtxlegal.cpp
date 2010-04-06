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

#ifdef _CCC2_
#define TYPE_BINARY     TYPE_STRING
#define binptr          chrptr
#define ISBINARY        ISSTRING
#endif

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
#define YYNSTATE 138
#define YYNRULE 67
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
 /*     0 */     2,   34,    3,    7,  102,   11,   29,   27,    9,   13,
 /*    10 */    15,   17,   19,   21,   23,   31,   37,  101,   39,  132,
 /*    20 */     2,   34,    3,    7,  189,   11,   29,   27,    9,   13,
 /*    30 */    15,   17,   19,   21,   23,   31,   37,    6,   39,   41,
 /*    40 */    42,  138,    8,    2,   34,    3,    7,   32,   11,   29,
 /*    50 */    27,    9,   13,   15,   17,   19,   21,   23,   31,   37,
 /*    60 */    10,   39,    2,   34,    3,    7,   12,   11,   29,   27,
 /*    70 */     9,   13,   15,   17,   19,   21,   23,   31,   37,   14,
 /*    80 */    39,   44,   16,    2,   34,    3,    7,   18,   11,   29,
 /*    90 */    27,    9,   13,   15,   17,   19,   21,   23,   31,   37,
 /*   100 */   106,   39,  113,   73,    2,   34,    3,    7,   20,   11,
 /*   110 */    29,   27,    9,   13,   15,   17,   19,   21,   23,   31,
 /*   120 */    37,   22,   39,   75,   26,    2,   34,    3,    7,   28,
 /*   130 */    11,   29,   27,    9,   13,   15,   17,   19,   21,   23,
 /*   140 */    31,   37,   30,   39,   79,   33,    2,   34,    3,    7,
 /*   150 */    35,   11,   29,   27,    9,   13,   15,   17,   19,   21,
 /*   160 */    23,   31,   37,    6,   39,  105,   84,    2,   34,    3,
 /*   170 */     7,   36,   11,   29,   27,    9,   13,   15,   17,   19,
 /*   180 */    21,   23,   31,   37,   40,   39,   86,   43,    2,   34,
 /*   190 */     3,    7,   46,   11,   29,   27,    9,   13,   15,   17,
 /*   200 */    19,   21,   23,   31,   37,   48,   39,   90,   50,    2,
 /*   210 */    34,    3,    7,   52,   11,   29,   27,    9,   13,   15,
 /*   220 */    17,   19,   21,   23,   31,   37,   54,   39,   95,   56,
 /*   230 */     2,   34,    3,    7,   61,   11,   29,   27,    9,   13,
 /*   240 */    15,   17,   19,   21,   23,   31,   37,  104,   39,    2,
 /*   250 */    34,    3,    7,   71,   11,   29,   27,    9,   13,   15,
 /*   260 */    17,   19,   21,   23,   31,   37,   64,   39,   60,    4,
 /*   270 */     5,   25,  133,   47,   49,   51,   53,   55,  206,    1,
 /*   280 */    38,   97,  134,   59,   72,  136,   57,   38,   58,   74,
 /*   290 */    60,   62,   78,    4,    5,   25,   45,   47,   49,   51,
 /*   300 */    53,   55,  127,   38,   63,   38,   66,   67,   60,  125,
 /*   310 */    57,   82,   38,   68,   83,   62,   85,    4,    5,   25,
 /*   320 */    45,   47,   49,   51,   53,   55,   69,   89,   60,   98,
 /*   330 */   117,  101,   94,  115,   57,  103,   60,  100,   58,   62,
 /*   340 */   108,    4,   24,   25,   45,   47,   49,   51,   53,   55,
 /*   350 */   110,  112,  114,  116,  118,  120,  107,  111,   99,  122,
 /*   360 */   124,  101,  126,   62,  128,    4,    5,   25,   45,   47,
 /*   370 */    49,   51,   53,   55,   70,  131,  135,  137,  101,  101,
 /*   380 */   101,  101,   57,  101,  101,  101,  101,   62,  101,   65,
 /*   390 */   101,    4,    5,   25,   45,  129,   49,   51,   53,   55,
 /*   400 */   101,  101,  101,  101,  101,  101,  101,  130,   57,  101,
 /*   410 */   101,  101,  101,   62,  101,    4,    5,   25,   45,   47,
 /*   420 */    49,   51,   53,   55,  101,  101,  101,  101,  101,  101,
 /*   430 */   101,  123,   57,  101,  101,  101,  101,   62,  101,    4,
 /*   440 */     5,   25,   45,   47,   49,   51,   53,   55,  101,  101,
 /*   450 */   101,  101,  101,  101,  101,  121,   57,  101,  101,  101,
 /*   460 */   101,   62,  101,    4,    5,   25,   45,   47,   49,   51,
 /*   470 */    53,   55,  101,  101,  101,  101,  101,  101,  101,  119,
 /*   480 */    57,  101,  101,  101,  101,   62,  101,    4,    5,   25,
 /*   490 */    45,   47,   49,   51,   53,   55,   70,  101,  101,  101,
 /*   500 */   101,  101,  101,  101,   57,  101,  101,  101,  101,   62,
 /*   510 */   101,    4,    5,   25,   45,   47,   49,   51,   53,   55,
 /*   520 */   101,  101,  101,  101,  101,  101,  101,  101,   57,  101,
 /*   530 */   101,  101,   93,   62,    4,    5,   25,   45,   47,   49,
 /*   540 */    51,   53,   55,  101,  101,  101,  101,  101,  101,  101,
 /*   550 */   101,   57,  101,  101,   92,  101,   62,  101,    4,    5,
 /*   560 */    25,   45,   47,   49,   51,   53,   55,   81,  101,  101,
 /*   570 */   101,  101,  101,  101,  101,   57,  101,  101,  101,  101,
 /*   580 */    62,  101,    4,    5,   25,   45,   47,   49,   51,   53,
 /*   590 */    55,  101,  101,  101,  101,  101,  101,  101,  101,   57,
 /*   600 */   101,  101,  101,   77,   62,    4,    5,   25,   45,   47,
 /*   610 */    49,   51,   53,   55,  101,  101,  101,  101,  101,  101,
 /*   620 */   101,  101,   57,  101,  101,   76,  101,   62,  101,    4,
 /*   630 */     5,   25,   45,   47,   49,   51,   53,   55,  101,  101,
 /*   640 */   101,  101,  101,  101,  101,  101,   57,  101,  101,   80,
 /*   650 */   101,   62,  101,    4,    5,   25,   45,   47,   49,   51,
 /*   660 */    53,   55,  101,  101,  101,  101,  101,  101,  101,  101,
 /*   670 */    57,  101,  101,  101,   88,   62,    4,    5,   25,   45,
 /*   680 */    47,   49,   51,   53,   55,  101,  101,  101,  101,  101,
 /*   690 */   101,  101,  101,   57,  101,  101,   87,  101,   62,  101,
 /*   700 */     4,    5,   25,   45,   47,   49,   51,   53,   55,  101,
 /*   710 */   101,  101,  101,  101,  101,  101,  101,   57,  101,  101,
 /*   720 */    91,  101,   62,  101,    4,    5,   25,   45,   47,   49,
 /*   730 */    51,   53,   55,  101,  101,  101,  101,  101,  101,  101,
 /*   740 */   101,   57,  101,  101,   96,  101,   62,  101,    4,    5,
 /*   750 */    25,   45,   47,   49,   51,   53,   55,  101,  101,  101,
 /*   760 */   101,  101,  101,  101,  109,   57,  101,  101,  101,  101,
 /*   770 */    62,  101,    4,    5,   25,   45,   47,   49,   51,   53,
 /*   780 */    55,  101,  101,  101,  101,  101,  101,  101,  101,   57,
 /*   790 */   101,  101,  101,  101,   62,  101,    4,   24,   25,   45,
 /*   800 */    47,   49,   51,   53,   55,  101,  101,  101,  101,  101,
 /*   810 */   101,  101,  101,   99,  101,  101,  101,  101,   62,
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
 /*   100 */    29,   20,   31,   22,    2,    3,    4,    5,   29,    7,
 /*   110 */     8,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*   120 */    18,   29,   20,   21,   29,    2,    3,    4,    5,   29,
 /*   130 */     7,    8,    9,   10,   11,   12,   13,   14,   15,   16,
 /*   140 */    17,   18,   29,   20,   21,   29,    2,    3,    4,    5,
 /*   150 */    17,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*   160 */    16,   17,   18,   29,   20,   31,   22,    2,    3,    4,
 /*   170 */     5,   29,    7,    8,    9,   10,   11,   12,   13,   14,
 /*   180 */    15,   16,   17,   18,   29,   20,   21,   29,    2,    3,
 /*   190 */     4,    5,   29,    7,    8,    9,   10,   11,   12,   13,
 /*   200 */    14,   15,   16,   17,   18,   29,   20,   21,   29,    2,
 /*   210 */     3,    4,    5,   29,    7,    8,    9,   10,   11,   12,
 /*   220 */    13,   14,   15,   16,   17,   18,   29,   20,   21,   29,
 /*   230 */     2,    3,    4,    5,   29,    7,    8,    9,   10,   11,
 /*   240 */    12,   13,   14,   15,   16,   17,   18,   19,   20,    2,
 /*   250 */     3,    4,    5,   20,    7,    8,    9,   10,   11,   12,
 /*   260 */    13,   14,   15,   16,   17,   18,   24,   20,   26,    1,
 /*   270 */     2,    3,    4,    5,    6,    7,    8,    9,   28,   29,
 /*   280 */    29,   30,   14,   19,   29,   17,   18,   29,   30,   29,
 /*   290 */    26,   23,   29,    1,    2,    3,    4,    5,    6,    7,
 /*   300 */     8,    9,   10,   29,   30,   29,   30,   25,   26,   17,
 /*   310 */    18,   20,   29,   30,   29,   23,   29,    1,    2,    3,
 /*   320 */     4,    5,    6,    7,    8,    9,   24,   29,   26,   19,
 /*   330 */    14,   32,   29,   17,   18,   29,   26,   29,   30,   23,
 /*   340 */    29,    1,    2,    3,    4,    5,    6,    7,    8,    9,
 /*   350 */    29,   29,   29,   29,   29,   29,   16,   17,   18,   29,
 /*   360 */    29,   32,   29,   23,   29,    1,    2,    3,    4,    5,
 /*   370 */     6,    7,    8,    9,   10,   29,   29,   29,   32,   32,
 /*   380 */    32,   32,   18,   32,   32,   32,   32,   23,   32,   25,
 /*   390 */    32,    1,    2,    3,    4,    5,    6,    7,    8,    9,
 /*   400 */    32,   32,   32,   32,   32,   32,   32,   17,   18,   32,
 /*   410 */    32,   32,   32,   23,   32,    1,    2,    3,    4,    5,
 /*   420 */     6,    7,    8,    9,   32,   32,   32,   32,   32,   32,
 /*   430 */    32,   17,   18,   32,   32,   32,   32,   23,   32,    1,
 /*   440 */     2,    3,    4,    5,    6,    7,    8,    9,   32,   32,
 /*   450 */    32,   32,   32,   32,   32,   17,   18,   32,   32,   32,
 /*   460 */    32,   23,   32,    1,    2,    3,    4,    5,    6,    7,
 /*   470 */     8,    9,   32,   32,   32,   32,   32,   32,   32,   17,
 /*   480 */    18,   32,   32,   32,   32,   23,   32,    1,    2,    3,
 /*   490 */     4,    5,    6,    7,    8,    9,   10,   32,   32,   32,
 /*   500 */    32,   32,   32,   32,   18,   32,   32,   32,   32,   23,
 /*   510 */    32,    1,    2,    3,    4,    5,    6,    7,    8,    9,
 /*   520 */    32,   32,   32,   32,   32,   32,   32,   32,   18,   32,
 /*   530 */    32,   32,   22,   23,    1,    2,    3,    4,    5,    6,
 /*   540 */     7,    8,    9,   32,   32,   32,   32,   32,   32,   32,
 /*   550 */    32,   18,   32,   32,   21,   32,   23,   32,    1,    2,
 /*   560 */     3,    4,    5,    6,    7,    8,    9,   10,   32,   32,
 /*   570 */    32,   32,   32,   32,   32,   18,   32,   32,   32,   32,
 /*   580 */    23,   32,    1,    2,    3,    4,    5,    6,    7,    8,
 /*   590 */     9,   32,   32,   32,   32,   32,   32,   32,   32,   18,
 /*   600 */    32,   32,   32,   22,   23,    1,    2,    3,    4,    5,
 /*   610 */     6,    7,    8,    9,   32,   32,   32,   32,   32,   32,
 /*   620 */    32,   32,   18,   32,   32,   21,   32,   23,   32,    1,
 /*   630 */     2,    3,    4,    5,    6,    7,    8,    9,   32,   32,
 /*   640 */    32,   32,   32,   32,   32,   32,   18,   32,   32,   21,
 /*   650 */    32,   23,   32,    1,    2,    3,    4,    5,    6,    7,
 /*   660 */     8,    9,   32,   32,   32,   32,   32,   32,   32,   32,
 /*   670 */    18,   32,   32,   32,   22,   23,    1,    2,    3,    4,
 /*   680 */     5,    6,    7,    8,    9,   32,   32,   32,   32,   32,
 /*   690 */    32,   32,   32,   18,   32,   32,   21,   32,   23,   32,
 /*   700 */     1,    2,    3,    4,    5,    6,    7,    8,    9,   32,
 /*   710 */    32,   32,   32,   32,   32,   32,   32,   18,   32,   32,
 /*   720 */    21,   32,   23,   32,    1,    2,    3,    4,    5,    6,
 /*   730 */     7,    8,    9,   32,   32,   32,   32,   32,   32,   32,
 /*   740 */    32,   18,   32,   32,   21,   32,   23,   32,    1,    2,
 /*   750 */     3,    4,    5,    6,    7,    8,    9,   32,   32,   32,
 /*   760 */    32,   32,   32,   32,   17,   18,   32,   32,   32,   32,
 /*   770 */    23,   32,    1,    2,    3,    4,    5,    6,    7,    8,
 /*   780 */     9,   32,   32,   32,   32,   32,   32,   32,   32,   18,
 /*   790 */    32,   32,   32,   32,   23,   32,    1,    2,    3,    4,
 /*   800 */     5,    6,    7,    8,    9,   32,   32,   32,   32,   32,
 /*   810 */    32,   32,   32,   18,   32,   32,   32,   32,   23,
};
#define YY_SHIFT_USE_DFLT (-3)
static short yy_shift_ofst[] = {
 /*     0 */   771,   41,   -3,  268,   -3,  771,  247,  390,  247,  292,
 /*    10 */   247,  414,  247,  438,  247,  771,  247,  771,  247,  462,
 /*    20 */   247,  316,  247,  340,  795,  771,  247,  771,  247,  771,
 /*    30 */   247,   30,  771,  247,  133,  771,  247,  486,  247,  510,
 /*    40 */    18,   -3,  533,   60,   -3,  771,  247,  771,  247,  771,
 /*    50 */   247,  771,  247,  771,  247,  771,  247,  486,  264,   -3,
 /*    60 */   557,  247,  364,  242,   -3,  486,  282,  486,  302,   -3,
 /*    70 */   233,  581,   81,  604,  102,   -3,   -3,  628,  123,   -3,
 /*    80 */    -3,  291,  652,  144,  675,  165,   -3,   -3,  699,  186,
 /*    90 */    -3,   -3,   -3,  723,  207,   -3,   -3,  310,   -3,  486,
 /*   100 */    -2,   -3,  771,  228,   -3,   -3,  247,  747,  247,  771,
 /*   110 */   247,  771,  247,  771,  247,  771,  247,  771,  247,  771,
 /*   120 */   247,  771,  247,  771,  247,  771,  247,  771,  247,  771,
 /*   130 */   771,  247,  247,  771,  771,  247,  771,  247,
};
#define YY_REDUCE_USE_DFLT (-11)
static short yy_reduce_ofst[] = {
 /*     0 */   250,  -11,  -11,  -10,  -11,    8,  -11,   13,  -11,   31,
 /*    10 */   -11,   37,  -11,   50,  -11,   53,  -11,   58,  -11,   79,
 /*    20 */   -11,   92,  -11,   71,  134,   95,  -11,  100,  -11,  113,
 /*    30 */   -11,  -11,  116,  -11,  -11,  142,  -11,  251,  -11,  155,
 /*    40 */   -11,  -11,  158,  -11,  -11,  163,  -11,  176,  -11,  179,
 /*    50 */   -11,  184,  -11,  197,  -11,  200,  -11,  258,  -11,  -11,
 /*    60 */   205,  -11,  274,  -11,  -11,  276,  -11,  283,  -11,  -11,
 /*    70 */   -11,  255,  -11,  260,  -11,  -11,  -11,  263,  -11,  -11,
 /*    80 */   -11,  -11,  285,  -11,  287,  -11,  -11,  -11,  298,  -11,
 /*    90 */   -11,  -11,  -11,  303,  -11,  -11,  -11,  -11,  -11,  308,
 /*   100 */   -11,  -11,  306,  -11,  -11,  -11,  -11,  311,  -11,  321,
 /*   110 */   -11,  322,  -11,  323,  -11,  324,  -11,  325,  -11,  326,
 /*   120 */   -11,  330,  -11,  331,  -11,  333,  -11,  335,  -11,  176,
 /*   130 */   346,  -11,  -11,  163,  347,  -11,  348,  -11,
};
static YYACTIONTYPE yy_default[] = {
 /*     0 */   205,  205,  141,  205,  139,  205,  140,  205,  151,  205,
 /*    10 */   153,  205,  154,  205,  155,  205,  156,  205,  157,  205,
 /*    20 */   158,  205,  159,  205,  205,  205,  142,  205,  163,  205,
 /*    30 */   164,  205,  205,  167,  205,  205,  170,  188,  189,  205,
 /*    40 */   205,  180,  205,  205,  181,  205,  143,  205,  144,  205,
 /*    50 */   145,  205,  146,  205,  147,  205,  148,  188,  205,  178,
 /*    60 */   195,  196,  188,  205,  185,  188,  205,  188,  205,  186,
 /*    70 */   190,  205,  205,  205,  205,  194,  192,  205,  205,  193,
 /*    80 */   191,  197,  205,  205,  205,  205,  201,  199,  205,  205,
 /*    90 */   200,  198,  182,  205,  205,  183,  184,  205,  179,  188,
 /*   100 */   205,  202,  205,  205,  203,  204,  160,  205,  161,  205,
 /*   110 */   162,  205,  165,  205,  187,  205,  168,  205,  177,  205,
 /*   120 */   169,  205,  175,  205,  174,  205,  173,  205,  176,  150,
 /*   130 */   205,  171,  152,  149,  205,  166,  205,  172,
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
  int xxmajor;                  /* The symbol code for the token */
  YYMINORTYPE xxminor;          /* The value for the token */
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
 /*  53 */ "xlst ::= STAR LBRACKET DOTDOT RBRACKET",
 /*  54 */ "xlst ::= STAR LBRACKET expr DOTDOT RBRACKET",
 /*  55 */ "xlst ::= STAR LBRACKET DOTDOT expr RBRACKET",
 /*  56 */ "xlst ::= STAR LBRACKET expr DOTDOT expr RBRACKET",
 /*  57 */ "xlst ::= xlst COMMA",
 /*  58 */ "xlst ::= xlst COMMA expr",
 /*  59 */ "xlst ::= xlst COMMA STAR",
 /*  60 */ "xlst ::= xlst COMMA STAR LBRACKET DOTDOT RBRACKET",
 /*  61 */ "xlst ::= xlst COMMA STAR LBRACKET expr DOTDOT RBRACKET",
 /*  62 */ "xlst ::= xlst COMMA STAR LBRACKET DOTDOT expr RBRACKET",
 /*  63 */ "xlst ::= xlst COMMA STAR LBRACKET expr DOTDOT expr RBRACKET",
 /*  64 */ "cast ::= LPAR expr RPAR",
 /*  65 */ "cast ::= LPAR expr AT expr RPAR",
 /*  66 */ "cast ::= SPACE cast",
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
  if(pParser->xxmajor)
  {
      yy_destructor(pParser->xxmajor,&pParser->xxminor);
  }
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
  { 30, 4 },
  { 30, 5 },
  { 30, 5 },
  { 30, 6 },
  { 30, 2 },
  { 30, 3 },
  { 30, 3 },
  { 30, 6 },
  { 30, 7 },
  { 30, 7 },
  { 30, 8 },
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
#line 291 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[0].minor.yy0,yymsp[0].minor.yy0);}
#line 1107 "./xtxlegal.c"
        break;
      case 2:
#line 293 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1112 "./xtxlegal.c"
        break;
      case 3:
#line 294 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1117 "./xtxlegal.c"
        break;
      case 4:
#line 296 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1122 "./xtxlegal.c"
        break;
      case 5:
#line 297 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1127 "./xtxlegal.c"
        break;
      case 6:
#line 298 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1132 "./xtxlegal.c"
        break;
      case 7:
#line 299 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1137 "./xtxlegal.c"
        break;
      case 8:
#line 300 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1142 "./xtxlegal.c"
        break;
      case 9:
#line 301 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1147 "./xtxlegal.c"
        break;
      case 10:
#line 302 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1152 "./xtxlegal.c"
        break;
      case 11:
#line 304 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1157 "./xtxlegal.c"
        /* No destructor defined for MINUS */
        break;
      case 12:
#line 305 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1163 "./xtxlegal.c"
        /* No destructor defined for PLUS */
        break;
      case 13:
#line 307 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1169 "./xtxlegal.c"
        /* No destructor defined for PLUS */
        break;
      case 14:
#line 308 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1175 "./xtxlegal.c"
        /* No destructor defined for MINUS */
        break;
      case 15:
#line 309 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1181 "./xtxlegal.c"
        /* No destructor defined for STAR */
        break;
      case 16:
#line 310 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1187 "./xtxlegal.c"
        /* No destructor defined for SLASH */
        break;
      case 17:
#line 311 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1193 "./xtxlegal.c"
        /* No destructor defined for MODULO */
        break;
      case 18:
#line 312 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1199 "./xtxlegal.c"
        /* No destructor defined for POWER */
        break;
      case 19:
#line 313 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1205 "./xtxlegal.c"
        /* No destructor defined for DOLLAR */
        break;
      case 20:
#line 314 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1211 "./xtxlegal.c"
        /* No destructor defined for GT */
        break;
      case 21:
#line 315 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1217 "./xtxlegal.c"
        /* No destructor defined for LT */
        break;
      case 22:
#line 316 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1223 "./xtxlegal.c"
        /* No destructor defined for COLON */
        break;
      case 23:
#line 317 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1229 "./xtxlegal.c"
        /* No destructor defined for COLON */
        /* No destructor defined for COLON */
        break;
      case 24:
#line 318 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-4].minor.yy0,yymsp[0].minor.yy0);}
#line 1236 "./xtxlegal.c"
        /* No destructor defined for COLON */
        /* No destructor defined for COLON */
        /* No destructor defined for EQUAL */
        break;
      case 25:
#line 319 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1244 "./xtxlegal.c"
        /* No destructor defined for DOT */
        break;
      case 26:
#line 320 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1250 "./xtxlegal.c"
        /* No destructor defined for BSLASH */
        break;
      case 27:
#line 322 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1256 "./xtxlegal.c"
        /* No destructor defined for COLON */
        /* No destructor defined for EQUAL */
        break;
      case 28:
#line 323 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1263 "./xtxlegal.c"
        /* No destructor defined for MINUS */
        /* No destructor defined for GT */
        break;
      case 29:
#line 324 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1270 "./xtxlegal.c"
        /* No destructor defined for EQUAL */
        /* No destructor defined for EQUAL */
        break;
      case 30:
#line 325 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1277 "./xtxlegal.c"
        /* No destructor defined for LT */
        /* No destructor defined for EQUAL */
        break;
      case 31:
#line 326 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1284 "./xtxlegal.c"
        /* No destructor defined for GT */
        /* No destructor defined for EQUAL */
        break;
      case 32:
#line 327 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1291 "./xtxlegal.c"
        /* No destructor defined for EXCL */
        /* No destructor defined for EQUAL */
        break;
      case 33:
#line 328 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1298 "./xtxlegal.c"
        /* No destructor defined for PLUS */
        /* No destructor defined for EQUAL */
        break;
      case 34:
#line 329 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1305 "./xtxlegal.c"
        /* No destructor defined for MINUS */
        /* No destructor defined for EQUAL */
        break;
      case 35:
#line 330 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1312 "./xtxlegal.c"
        /* No destructor defined for STAR */
        /* No destructor defined for EQUAL */
        break;
      case 36:
#line 331 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1319 "./xtxlegal.c"
        /* No destructor defined for SLASH */
        /* No destructor defined for EQUAL */
        break;
      case 37:
#line 332 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1326 "./xtxlegal.c"
        /* No destructor defined for MODULO */
        /* No destructor defined for EQUAL */
        break;
      case 38:
#line 333 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1333 "./xtxlegal.c"
        /* No destructor defined for STAR */
        /* No destructor defined for STAR */
        break;
      case 39:
#line 335 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1340 "./xtxlegal.c"
        /* No destructor defined for LT */
        /* No destructor defined for GT */
        break;
      case 40:
#line 337 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1347 "./xtxlegal.c"
        /* No destructor defined for xlst */
        break;
      case 41:
#line 338 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1353 "./xtxlegal.c"
        /* No destructor defined for LPAR */
        /* No destructor defined for xlst */
        break;
      case 42:
#line 339 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1360 "./xtxlegal.c"
        /* No destructor defined for LBRACKET */
        /* No destructor defined for expr */
        break;
      case 43:
#line 340 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-5].minor.yy0,yymsp[0].minor.yy0);}
#line 1367 "./xtxlegal.c"
        /* No destructor defined for LBRACKET */
        /* No destructor defined for expr */
        /* No destructor defined for DOTDOT */
        /* No destructor defined for expr */
        break;
      case 44:
#line 341 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-4].minor.yy0,yymsp[0].minor.yy0);}
#line 1376 "./xtxlegal.c"
        /* No destructor defined for LBRACKET */
        /* No destructor defined for expr */
        /* No destructor defined for DOTDOT */
        break;
      case 45:
#line 342 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-4].minor.yy0,yymsp[0].minor.yy0);}
#line 1384 "./xtxlegal.c"
        /* No destructor defined for LBRACKET */
        /* No destructor defined for DOTDOT */
        /* No destructor defined for expr */
        break;
      case 46:
#line 343 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1392 "./xtxlegal.c"
        /* No destructor defined for LBRACKET */
        /* No destructor defined for DOTDOT */
        break;
      case 47:
#line 344 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1399 "./xtxlegal.c"
        /* No destructor defined for xlst */
        break;
      case 48:
#line 345 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-5].minor.yy0,yymsp[0].minor.yy0);}
#line 1405 "./xtxlegal.c"
        /* No destructor defined for PIPE */
        /* No destructor defined for xlst */
        /* No destructor defined for PIPE */
        /* No destructor defined for xlst */
        break;
      case 49:
#line 347 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1414 "./xtxlegal.c"
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
        /* No destructor defined for STAR */
        /* No destructor defined for LBRACKET */
        /* No destructor defined for DOTDOT */
        /* No destructor defined for RBRACKET */
        break;
      case 54:
        /* No destructor defined for STAR */
        /* No destructor defined for LBRACKET */
        /* No destructor defined for expr */
        /* No destructor defined for DOTDOT */
        /* No destructor defined for RBRACKET */
        break;
      case 55:
        /* No destructor defined for STAR */
        /* No destructor defined for LBRACKET */
        /* No destructor defined for DOTDOT */
        /* No destructor defined for expr */
        /* No destructor defined for RBRACKET */
        break;
      case 56:
        /* No destructor defined for STAR */
        /* No destructor defined for LBRACKET */
        /* No destructor defined for expr */
        /* No destructor defined for DOTDOT */
        /* No destructor defined for expr */
        /* No destructor defined for RBRACKET */
        break;
      case 57:
        /* No destructor defined for xlst */
        /* No destructor defined for COMMA */
        break;
      case 58:
        /* No destructor defined for xlst */
        /* No destructor defined for COMMA */
        /* No destructor defined for expr */
        break;
      case 59:
        /* No destructor defined for xlst */
        /* No destructor defined for COMMA */
        /* No destructor defined for STAR */
        break;
      case 60:
        /* No destructor defined for xlst */
        /* No destructor defined for COMMA */
        /* No destructor defined for STAR */
        /* No destructor defined for LBRACKET */
        /* No destructor defined for DOTDOT */
        /* No destructor defined for RBRACKET */
        break;
      case 61:
        /* No destructor defined for xlst */
        /* No destructor defined for COMMA */
        /* No destructor defined for STAR */
        /* No destructor defined for LBRACKET */
        /* No destructor defined for expr */
        /* No destructor defined for DOTDOT */
        /* No destructor defined for RBRACKET */
        break;
      case 62:
        /* No destructor defined for xlst */
        /* No destructor defined for COMMA */
        /* No destructor defined for STAR */
        /* No destructor defined for LBRACKET */
        /* No destructor defined for DOTDOT */
        /* No destructor defined for expr */
        /* No destructor defined for RBRACKET */
        break;
      case 63:
        /* No destructor defined for xlst */
        /* No destructor defined for COMMA */
        /* No destructor defined for STAR */
        /* No destructor defined for LBRACKET */
        /* No destructor defined for expr */
        /* No destructor defined for DOTDOT */
        /* No destructor defined for expr */
        /* No destructor defined for RBRACKET */
        break;
      case 64:
        /* No destructor defined for LPAR */
        /* No destructor defined for expr */
        /* No destructor defined for RPAR */
        break;
      case 65:
        /* No destructor defined for LPAR */
        /* No destructor defined for expr */
        /* No destructor defined for AT */
        /* No destructor defined for expr */
        /* No destructor defined for RPAR */
        break;
      case 66:
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
#line 276 "./xtxlegal.lem"

    //printf("Syntax error.\n");
    termflag=1;

#line 1565 "./xtxlegal.c"
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
#line 281 "./xtxlegal.lem"

    //printf("Parsing complete.\n");

#line 1588 "./xtxlegal.c"
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
  yypParser->xxmajor=yymajor;
  yypParser->xxminor.yy0=yyminor;
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

      yypParser->xxmajor=0;
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
        yypParser->xxmajor=0;

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
          yypParser->xxmajor=0;

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
      yypParser->xxmajor=0;

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
