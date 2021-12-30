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
        else if( !BINARYLEN(token) )
        {
            //kihagy;
        }
        else
        {
            *len=BINARYLEN(token);
            p=BINARYPTR(token);
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

#line 252 "./xtxlegal.c"
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
#define YYNSTATE 141
#define YYNRULE 68
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
 /*     0 */     2,   34,    3,    7,  105,   39,  140,   11,   29,   27,
 /*    10 */     9,   13,   15,   17,   19,   21,   23,   31,   37,  104,
 /*    20 */     2,   34,    3,    7,  193,   39,   41,   11,   29,   27,
 /*    30 */     9,   13,   15,   17,   19,   21,   23,   31,   37,  135,
 /*    40 */    42,    2,   34,    3,    7,   46,   39,   82,   11,   29,
 /*    50 */    27,    9,   13,   15,   17,   19,   21,   23,   31,   37,
 /*    60 */     2,   34,    3,    7,    6,   39,   98,   11,   29,   27,
 /*    70 */     9,   13,   15,   17,   19,   21,   23,   31,   37,    2,
 /*    80 */    34,    3,    7,   67,   39,   63,   11,   29,   27,    9,
 /*    90 */    13,   15,   17,   19,   21,   23,   31,   37,   64,   76,
 /*   100 */     2,   34,    3,    7,   59,   39,   89,   11,   29,   27,
 /*   110 */     9,   13,   15,   17,   19,   21,   23,   31,   37,    2,
 /*   120 */    34,    3,    7,  134,   39,   44,   11,   29,   27,    9,
 /*   130 */    13,   15,   17,   19,   21,   23,   31,   37,    2,   34,
 /*   140 */     3,    7,   48,   39,   78,   11,   29,   27,    9,   13,
 /*   150 */    15,   17,   19,   21,   23,   31,   37,  141,   57,    2,
 /*   160 */    34,    3,    7,   72,   39,   63,   11,   29,   27,    9,
 /*   170 */    13,   15,   17,   19,   21,   23,   31,   37,    2,   34,
 /*   180 */     3,    7,    8,   39,   53,   11,   29,   27,    9,   13,
 /*   190 */    15,   17,   19,   21,   23,   31,   37,    2,   34,    3,
 /*   200 */     7,  131,   39,   93,   11,   29,   27,    9,   13,   15,
 /*   210 */    17,   19,   21,   23,   31,   37,    2,   34,    3,    7,
 /*   220 */   109,   39,  116,   11,   29,   27,    9,   13,   15,   17,
 /*   230 */    19,   21,   23,   31,   37,  107,    2,   34,    3,    7,
 /*   240 */     6,   39,  108,   11,   29,   27,    9,   13,   15,   17,
 /*   250 */    19,   21,   23,   31,   37,   10,   87,    2,   34,    3,
 /*   260 */     7,  129,   39,   74,   11,   29,   27,    9,   13,   15,
 /*   270 */    17,   19,   21,   23,   31,   37,    4,    5,   25,  136,
 /*   280 */    47,   49,   51,   55,   54,   56,   58,   38,   69,   38,
 /*   290 */    71,  137,   70,   63,  139,   60,  210,    1,   65,   12,
 /*   300 */     4,    5,   25,   45,   47,   49,   51,  127,   54,   56,
 /*   310 */    58,  130,   38,   66,  103,   61,  101,   14,  128,   60,
 /*   320 */   125,   63,   65,   52,    4,   24,   25,   45,   47,   49,
 /*   330 */    51,   16,   54,   56,   58,   38,  100,  123,   38,   61,
 /*   340 */    62,  110,  114,  102,   18,   63,   65,  121,    4,    5,
 /*   350 */    25,   45,   47,   49,   51,   20,   54,   56,   58,   73,
 /*   360 */    50,   75,  119,   22,   77,  117,   26,   60,  115,   28,
 /*   370 */    65,  113,   68,   30,    4,    5,   25,   45,   47,   49,
 /*   380 */    51,   81,   54,   56,   58,  111,   32,   33,  106,  120,
 /*   390 */    35,   36,  118,   60,   85,  138,   65,   97,    4,    5,
 /*   400 */    25,   45,   47,   49,   51,   95,   54,   56,   58,   86,
 /*   410 */    40,   92,   43,   88,  102,  102,  102,   60,  102,  102,
 /*   420 */    65,  102,    4,    5,   25,   45,   47,   49,   51,   79,
 /*   430 */    54,   56,   58,  102,  102,  102,  102,  102,  102,  102,
 /*   440 */   102,   60,  102,  102,   65,  102,    4,    5,   25,   45,
 /*   450 */    47,   49,   51,  102,   54,   56,   58,  102,  102,  102,
 /*   460 */   102,  102,  102,  102,  102,   60,  102,   80,   65,    4,
 /*   470 */     5,   25,   45,   47,   49,   51,   94,   54,   56,   58,
 /*   480 */   102,  102,  102,  102,  102,  102,  102,  102,   60,  102,
 /*   490 */   102,   65,  102,    4,    5,   25,   45,   47,   49,   51,
 /*   500 */    90,   54,   56,   58,  102,  102,  102,  102,  102,  102,
 /*   510 */   102,  102,   60,  102,  102,   65,  102,    4,    5,   25,
 /*   520 */    45,   47,   49,   51,  102,   54,   56,   58,  102,  102,
 /*   530 */   102,  102,  102,  102,  102,  124,   60,  102,  102,   65,
 /*   540 */   102,    4,    5,   25,   45,   47,   49,   51,  102,   54,
 /*   550 */    56,   58,  102,  102,  102,  102,  102,  102,  102,  112,
 /*   560 */    60,  102,  102,   65,  102,    4,    5,   25,   45,   47,
 /*   570 */    49,   51,  102,   54,   56,   58,  102,  102,  102,  102,
 /*   580 */   102,  102,  102,  126,   60,  102,  102,   65,  102,    4,
 /*   590 */     5,   25,   45,   47,   49,   51,  102,   54,   56,   58,
 /*   600 */    73,  102,  102,  102,  102,  102,  102,  102,   60,  102,
 /*   610 */   102,   65,  102,    4,    5,   25,   45,   47,   49,   51,
 /*   620 */    83,   54,   56,   58,  102,  102,  102,  102,  102,  102,
 /*   630 */   102,  102,   60,  102,  102,   65,  102,    4,    5,   25,
 /*   640 */    45,  132,   49,   51,  102,   54,   56,   58,  102,  102,
 /*   650 */   102,  102,  102,  102,  102,  133,   60,  102,  102,   65,
 /*   660 */   102,    4,    5,   25,   45,   47,   49,   51,   99,   54,
 /*   670 */    56,   58,  102,  102,  102,  102,  102,  102,  102,  102,
 /*   680 */    60,  102,  102,   65,  102,    4,    5,   25,   45,   47,
 /*   690 */    49,   51,  102,   54,   56,   58,  102,  102,  102,  102,
 /*   700 */   102,  102,  102,  102,   60,  102,   96,   65,    4,    5,
 /*   710 */    25,   45,   47,   49,   51,  102,   54,   56,   58,  102,
 /*   720 */   102,  102,  102,  102,  102,  102,  102,   60,  102,   91,
 /*   730 */    65,    4,    5,   25,   45,   47,   49,   51,  102,   54,
 /*   740 */    56,   58,   84,  102,  102,  102,  102,  102,  102,  102,
 /*   750 */    60,  102,  102,   65,  102,    4,    5,   25,   45,   47,
 /*   760 */    49,   51,  102,   54,   56,   58,  102,  102,  102,  102,
 /*   770 */   102,  102,  102,  122,   60,  102,  102,   65,  102,    4,
 /*   780 */     5,   25,   45,   47,   49,   51,  102,   54,   56,   58,
 /*   790 */   102,  102,  102,  102,  102,  102,  102,  102,   60,  102,
 /*   800 */   102,   65,  102,    4,   24,   25,   45,   47,   49,   51,
 /*   810 */   102,   54,   56,   58,  102,  102,  102,  102,  102,  102,
 /*   820 */   102,  102,  102,  102,  102,   65,
};
static YYCODETYPE yy_lookahead[] = {
 /*     0 */     2,    3,    4,    5,    6,    7,   29,    9,   10,   11,
 /*    10 */    12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*    20 */     2,    3,    4,    5,   26,    7,    8,    9,   10,   11,
 /*    30 */    12,   13,   14,   15,   16,   17,   18,   19,   20,   29,
 /*    40 */    22,    2,    3,    4,    5,   29,    7,    8,    9,   10,
 /*    50 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*    60 */     2,    3,    4,    5,   29,    7,    8,    9,   10,   11,
 /*    70 */    12,   13,   14,   15,   16,   17,   18,   19,   20,    2,
 /*    80 */     3,    4,    5,   24,    7,   26,    9,   10,   11,   12,
 /*    90 */    13,   14,   15,   16,   17,   18,   19,   20,   29,   22,
 /*   100 */     2,    3,    4,    5,   29,    7,    8,    9,   10,   11,
 /*   110 */    12,   13,   14,   15,   16,   17,   18,   19,   20,    2,
 /*   120 */     3,    4,    5,   29,    7,    8,    9,   10,   11,   12,
 /*   130 */    13,   14,   15,   16,   17,   18,   19,   20,    2,    3,
 /*   140 */     4,    5,   29,    7,    8,    9,   10,   11,   12,   13,
 /*   150 */    14,   15,   16,   17,   18,   19,   20,    0,   29,    2,
 /*   160 */     3,    4,    5,   24,    7,   26,    9,   10,   11,   12,
 /*   170 */    13,   14,   15,   16,   17,   18,   19,   20,    2,    3,
 /*   180 */     4,    5,   29,    7,    8,    9,   10,   11,   12,   13,
 /*   190 */    14,   15,   16,   17,   18,   19,   20,    2,    3,    4,
 /*   200 */     5,   29,    7,    8,    9,   10,   11,   12,   13,   14,
 /*   210 */    15,   16,   17,   18,   19,   20,    2,    3,    4,    5,
 /*   220 */    29,    7,   31,    9,   10,   11,   12,   13,   14,   15,
 /*   230 */    16,   17,   18,   19,   20,   21,    2,    3,    4,    5,
 /*   240 */    29,    7,   31,    9,   10,   11,   12,   13,   14,   15,
 /*   250 */    16,   17,   18,   19,   20,   29,   22,    2,    3,    4,
 /*   260 */     5,   29,    7,    7,    9,   10,   11,   12,   13,   14,
 /*   270 */    15,   16,   17,   18,   19,   20,    1,    2,    3,    4,
 /*   280 */     5,    6,    7,   29,    9,   10,   11,   29,   30,   29,
 /*   290 */    30,   16,   25,   26,   19,   20,   28,   29,   23,   29,
 /*   300 */     1,    2,    3,    4,    5,    6,    7,   29,    9,   10,
 /*   310 */    11,   12,   29,   30,   29,   30,   21,   29,   19,   20,
 /*   320 */    29,   26,   23,   29,    1,    2,    3,    4,    5,    6,
 /*   330 */     7,   29,    9,   10,   11,   29,   30,   29,   29,   30,
 /*   340 */    21,   18,   19,   20,   29,   26,   23,   29,    1,    2,
 /*   350 */     3,    4,    5,    6,    7,   29,    9,   10,   11,   12,
 /*   360 */    29,   29,   29,   29,   29,   29,   29,   20,   29,   29,
 /*   370 */    23,   29,   25,   29,    1,    2,    3,    4,    5,    6,
 /*   380 */     7,   29,    9,   10,   11,   29,   19,   29,   29,   16,
 /*   390 */    19,   29,   19,   20,    7,   29,   23,   29,    1,    2,
 /*   400 */     3,    4,    5,    6,    7,    8,    9,   10,   11,   29,
 /*   410 */    29,   29,   29,   29,   32,   32,   32,   20,   32,   32,
 /*   420 */    23,   32,    1,    2,    3,    4,    5,    6,    7,    8,
 /*   430 */     9,   10,   11,   32,   32,   32,   32,   32,   32,   32,
 /*   440 */    32,   20,   32,   32,   23,   32,    1,    2,    3,    4,
 /*   450 */     5,    6,    7,   32,    9,   10,   11,   32,   32,   32,
 /*   460 */    32,   32,   32,   32,   32,   20,   32,   22,   23,    1,
 /*   470 */     2,    3,    4,    5,    6,    7,    8,    9,   10,   11,
 /*   480 */    32,   32,   32,   32,   32,   32,   32,   32,   20,   32,
 /*   490 */    32,   23,   32,    1,    2,    3,    4,    5,    6,    7,
 /*   500 */     8,    9,   10,   11,   32,   32,   32,   32,   32,   32,
 /*   510 */    32,   32,   20,   32,   32,   23,   32,    1,    2,    3,
 /*   520 */     4,    5,    6,    7,   32,    9,   10,   11,   32,   32,
 /*   530 */    32,   32,   32,   32,   32,   19,   20,   32,   32,   23,
 /*   540 */    32,    1,    2,    3,    4,    5,    6,    7,   32,    9,
 /*   550 */    10,   11,   32,   32,   32,   32,   32,   32,   32,   19,
 /*   560 */    20,   32,   32,   23,   32,    1,    2,    3,    4,    5,
 /*   570 */     6,    7,   32,    9,   10,   11,   32,   32,   32,   32,
 /*   580 */    32,   32,   32,   19,   20,   32,   32,   23,   32,    1,
 /*   590 */     2,    3,    4,    5,    6,    7,   32,    9,   10,   11,
 /*   600 */    12,   32,   32,   32,   32,   32,   32,   32,   20,   32,
 /*   610 */    32,   23,   32,    1,    2,    3,    4,    5,    6,    7,
 /*   620 */     8,    9,   10,   11,   32,   32,   32,   32,   32,   32,
 /*   630 */    32,   32,   20,   32,   32,   23,   32,    1,    2,    3,
 /*   640 */     4,    5,    6,    7,   32,    9,   10,   11,   32,   32,
 /*   650 */    32,   32,   32,   32,   32,   19,   20,   32,   32,   23,
 /*   660 */    32,    1,    2,    3,    4,    5,    6,    7,    8,    9,
 /*   670 */    10,   11,   32,   32,   32,   32,   32,   32,   32,   32,
 /*   680 */    20,   32,   32,   23,   32,    1,    2,    3,    4,    5,
 /*   690 */     6,    7,   32,    9,   10,   11,   32,   32,   32,   32,
 /*   700 */    32,   32,   32,   32,   20,   32,   22,   23,    1,    2,
 /*   710 */     3,    4,    5,    6,    7,   32,    9,   10,   11,   32,
 /*   720 */    32,   32,   32,   32,   32,   32,   32,   20,   32,   22,
 /*   730 */    23,    1,    2,    3,    4,    5,    6,    7,   32,    9,
 /*   740 */    10,   11,   12,   32,   32,   32,   32,   32,   32,   32,
 /*   750 */    20,   32,   32,   23,   32,    1,    2,    3,    4,    5,
 /*   760 */     6,    7,   32,    9,   10,   11,   32,   32,   32,   32,
 /*   770 */    32,   32,   32,   19,   20,   32,   32,   23,   32,    1,
 /*   780 */     2,    3,    4,    5,    6,    7,   32,    9,   10,   11,
 /*   790 */    32,   32,   32,   32,   32,   32,   32,   32,   20,   32,
 /*   800 */    32,   23,   32,    1,    2,    3,    4,    5,    6,    7,
 /*   810 */    32,    9,   10,   11,   32,   32,   32,   32,   32,   32,
 /*   820 */    32,   32,   20,   32,   32,   23,
};
#define YY_SHIFT_USE_DFLT (-3)
static short yy_shift_ofst[] = {
 /*     0 */   778,  157,   -3,  275,   -3,  778,  255,  636,  255,  299,
 /*    10 */   255,  564,  255,  516,  255,  778,  255,  778,  255,  754,
 /*    20 */   255,  373,  255,  323,  802,  778,  255,  778,  255,  778,
 /*    30 */   255,  367,  778,  255,  371,  778,  255,  588,  255,  684,
 /*    40 */    18,   -3,  397,  117,   -3,  778,  255,  778,  255,  778,
 /*    50 */   255,  778,  176,   -3,  778,  255,  778,  255,  778,  255,
 /*    60 */   588,  319,   -3,  730,  255,  347,   59,   -3,  588,  267,
 /*    70 */   588,  139,   -3,  256,  445,   77,  421,  136,   -3,   -3,
 /*    80 */   612,   39,   -3,   -3,  387,  707,  234,  492,   98,   -3,
 /*    90 */    -3,  468,  195,   -3,   -3,   -3,  660,   58,   -3,   -3,
 /*   100 */   295,   -3,  588,   -2,   -3,  778,  214,   -3,   -3,  255,
 /*   110 */   540,  255,  778,  255,  778,  255,  778,  255,  778,  255,
 /*   120 */   778,  255,  778,  255,  778,  255,  778,  255,  778,  255,
 /*   130 */   778,  255,  778,  778,  255,  255,  778,  778,  255,  778,
 /*   140 */   255,
};
#define YY_REDUCE_USE_DFLT (-24)
static short yy_reduce_ofst[] = {
 /*     0 */   268,  -24,  -24,   10,  -24,   35,  -24,  153,  -24,  226,
 /*    10 */   -24,  270,  -24,  288,  -24,  302,  -24,  315,  -24,  326,
 /*    20 */   -24,  334,  -24,  191,  211,  337,  -24,  340,  -24,  344,
 /*    30 */   -24,  -24,  358,  -24,  -24,  362,  -24,  306,  -24,  381,
 /*    40 */   -24,  -24,  383,  -24,  -24,   16,  -24,  113,  -24,  331,
 /*    50 */   -24,  294,  -24,  -24,  254,  -24,  129,  -24,   75,  -24,
 /*    60 */   309,  -24,  -24,   69,  -24,  283,  -24,  -24,  258,  -24,
 /*    70 */   260,  -24,  -24,  -24,  332,  -24,  335,  -24,  -24,  -24,
 /*    80 */   352,  -24,  -24,  -24,  -24,  380,  -24,  384,  -24,  -24,
 /*    90 */   -24,  382,  -24,  -24,  -24,  -24,  368,  -24,  -24,  -24,
 /*   100 */   -24,  -24,  285,  -24,  -24,  359,  -24,  -24,  -24,  -24,
 /*   110 */   356,  -24,  342,  -24,  339,  -24,  336,  -24,  333,  -24,
 /*   120 */   318,  -24,  308,  -24,  291,  -24,  278,  -24,  232,  -24,
 /*   130 */   172,  -24,  113,   94,  -24,  -24,   16,  366,  -24,  -23,
 /*   140 */   -24,
};
static YYACTIONTYPE yy_default[] = {
 /*     0 */   209,  209,  144,  209,  142,  209,  143,  209,  155,  209,
 /*    10 */   157,  209,  158,  209,  159,  209,  160,  209,  161,  209,
 /*    20 */   162,  209,  163,  209,  209,  209,  145,  209,  167,  209,
 /*    30 */   168,  209,  209,  171,  209,  209,  174,  192,  193,  209,
 /*    40 */   209,  184,  209,  209,  185,  209,  146,  209,  147,  209,
 /*    50 */   148,  209,  209,  149,  209,  150,  209,  151,  209,  152,
 /*    60 */   192,  209,  182,  199,  200,  192,  209,  189,  192,  209,
 /*    70 */   192,  209,  190,  194,  209,  209,  209,  209,  198,  196,
 /*    80 */   209,  209,  197,  195,  201,  209,  209,  209,  209,  205,
 /*    90 */   203,  209,  209,  204,  202,  186,  209,  209,  187,  188,
 /*   100 */   209,  183,  192,  209,  206,  209,  209,  207,  208,  164,
 /*   110 */   209,  165,  209,  166,  209,  169,  209,  191,  209,  172,
 /*   120 */   209,  181,  209,  173,  209,  179,  209,  178,  209,  177,
 /*   130 */   209,  180,  154,  209,  175,  156,  153,  209,  170,  209,
 /*   140 */   176,
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
  "MINUS",         "PLUS",          "AT",            "LBRACKET",    
  "RBRACKET",      "SLASH",         "BSLASH",        "DOT",         
  "STAR",          "MODULO",        "POWER",         "DOLLAR",      
  "GT",            "LT",            "COLON",         "EQUAL",       
  "LPAR",          "RPAR",          "DOTDOT",        "LBRACE",      
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
 /*   8 */ "expr ::= LBRACKET expr RBRACKET",
 /*   9 */ "expr ::= SLASH expr",
 /*  10 */ "expr ::= BSLASH expr",
 /*  11 */ "expr ::= DOT expr",
 /*  12 */ "expr ::= expr MINUS MINUS",
 /*  13 */ "expr ::= expr PLUS PLUS",
 /*  14 */ "expr ::= expr PLUS expr",
 /*  15 */ "expr ::= expr MINUS expr",
 /*  16 */ "expr ::= expr STAR expr",
 /*  17 */ "expr ::= expr SLASH expr",
 /*  18 */ "expr ::= expr MODULO expr",
 /*  19 */ "expr ::= expr POWER expr",
 /*  20 */ "expr ::= expr DOLLAR expr",
 /*  21 */ "expr ::= expr GT expr",
 /*  22 */ "expr ::= expr LT expr",
 /*  23 */ "expr ::= expr COLON expr",
 /*  24 */ "expr ::= expr COLON COLON expr",
 /*  25 */ "expr ::= expr COLON COLON EQUAL expr",
 /*  26 */ "expr ::= expr DOT expr",
 /*  27 */ "expr ::= expr BSLASH expr",
 /*  28 */ "expr ::= expr COLON EQUAL expr",
 /*  29 */ "expr ::= expr MINUS GT expr",
 /*  30 */ "expr ::= expr EQUAL EQUAL expr",
 /*  31 */ "expr ::= expr LT EQUAL expr",
 /*  32 */ "expr ::= expr GT EQUAL expr",
 /*  33 */ "expr ::= expr EXCL EQUAL expr",
 /*  34 */ "expr ::= expr PLUS EQUAL expr",
 /*  35 */ "expr ::= expr MINUS EQUAL expr",
 /*  36 */ "expr ::= expr STAR EQUAL expr",
 /*  37 */ "expr ::= expr SLASH EQUAL expr",
 /*  38 */ "expr ::= expr MODULO EQUAL expr",
 /*  39 */ "expr ::= expr STAR STAR expr",
 /*  40 */ "expr ::= expr LT GT expr",
 /*  41 */ "expr ::= LPAR xlst RPAR",
 /*  42 */ "expr ::= expr LPAR xlst RPAR",
 /*  43 */ "expr ::= expr LBRACKET expr RBRACKET",
 /*  44 */ "expr ::= expr LBRACKET expr DOTDOT expr RBRACKET",
 /*  45 */ "expr ::= expr LBRACKET expr DOTDOT RBRACKET",
 /*  46 */ "expr ::= expr LBRACKET DOTDOT expr RBRACKET",
 /*  47 */ "expr ::= expr LBRACKET DOTDOT RBRACKET",
 /*  48 */ "expr ::= LBRACE xlst RBRACE",
 /*  49 */ "expr ::= LBRACE PIPE xlst PIPE xlst RBRACE",
 /*  50 */ "expr ::= expr COLON cast expr",
 /*  51 */ "xlst ::=",
 /*  52 */ "xlst ::= expr",
 /*  53 */ "xlst ::= STAR",
 /*  54 */ "xlst ::= STAR LBRACKET DOTDOT RBRACKET",
 /*  55 */ "xlst ::= STAR LBRACKET expr DOTDOT RBRACKET",
 /*  56 */ "xlst ::= STAR LBRACKET DOTDOT expr RBRACKET",
 /*  57 */ "xlst ::= STAR LBRACKET expr DOTDOT expr RBRACKET",
 /*  58 */ "xlst ::= xlst COMMA",
 /*  59 */ "xlst ::= xlst COMMA expr",
 /*  60 */ "xlst ::= xlst COMMA STAR",
 /*  61 */ "xlst ::= xlst COMMA STAR LBRACKET DOTDOT RBRACKET",
 /*  62 */ "xlst ::= xlst COMMA STAR LBRACKET expr DOTDOT RBRACKET",
 /*  63 */ "xlst ::= xlst COMMA STAR LBRACKET DOTDOT expr RBRACKET",
 /*  64 */ "xlst ::= xlst COMMA STAR LBRACKET expr DOTDOT expr RBRACKET",
 /*  65 */ "cast ::= LPAR expr RPAR",
 /*  66 */ "cast ::= LPAR expr AT expr RPAR",
 /*  67 */ "cast ::= SPACE cast",
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
  { 29, 3 },
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
#line 283 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[0].minor.yy0,yymsp[0].minor.yy0);}
#line 1106 "./xtxlegal.c"
        break;
      case 2:
#line 285 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1111 "./xtxlegal.c"
        break;
      case 3:
#line 286 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1116 "./xtxlegal.c"
        break;
      case 4:
#line 288 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1121 "./xtxlegal.c"
        break;
      case 5:
#line 289 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1126 "./xtxlegal.c"
        break;
      case 6:
#line 290 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1131 "./xtxlegal.c"
        break;
      case 7:
#line 291 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1136 "./xtxlegal.c"
        break;
      case 8:
#line 292 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1141 "./xtxlegal.c"
        /* No destructor defined for expr */
        break;
      case 9:
#line 293 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1147 "./xtxlegal.c"
        break;
      case 10:
#line 294 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1152 "./xtxlegal.c"
        break;
      case 11:
#line 295 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1157 "./xtxlegal.c"
        break;
      case 12:
#line 297 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1162 "./xtxlegal.c"
        /* No destructor defined for MINUS */
        break;
      case 13:
#line 298 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1168 "./xtxlegal.c"
        /* No destructor defined for PLUS */
        break;
      case 14:
#line 300 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1174 "./xtxlegal.c"
        /* No destructor defined for PLUS */
        break;
      case 15:
#line 301 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1180 "./xtxlegal.c"
        /* No destructor defined for MINUS */
        break;
      case 16:
#line 302 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1186 "./xtxlegal.c"
        /* No destructor defined for STAR */
        break;
      case 17:
#line 303 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1192 "./xtxlegal.c"
        /* No destructor defined for SLASH */
        break;
      case 18:
#line 304 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1198 "./xtxlegal.c"
        /* No destructor defined for MODULO */
        break;
      case 19:
#line 305 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1204 "./xtxlegal.c"
        /* No destructor defined for POWER */
        break;
      case 20:
#line 306 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1210 "./xtxlegal.c"
        /* No destructor defined for DOLLAR */
        break;
      case 21:
#line 307 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1216 "./xtxlegal.c"
        /* No destructor defined for GT */
        break;
      case 22:
#line 308 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1222 "./xtxlegal.c"
        /* No destructor defined for LT */
        break;
      case 23:
#line 309 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1228 "./xtxlegal.c"
        /* No destructor defined for COLON */
        break;
      case 24:
#line 310 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1234 "./xtxlegal.c"
        /* No destructor defined for COLON */
        /* No destructor defined for COLON */
        break;
      case 25:
#line 311 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-4].minor.yy0,yymsp[0].minor.yy0);}
#line 1241 "./xtxlegal.c"
        /* No destructor defined for COLON */
        /* No destructor defined for COLON */
        /* No destructor defined for EQUAL */
        break;
      case 26:
#line 312 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1249 "./xtxlegal.c"
        /* No destructor defined for DOT */
        break;
      case 27:
#line 313 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1255 "./xtxlegal.c"
        /* No destructor defined for BSLASH */
        break;
      case 28:
#line 315 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1261 "./xtxlegal.c"
        /* No destructor defined for COLON */
        /* No destructor defined for EQUAL */
        break;
      case 29:
#line 316 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1268 "./xtxlegal.c"
        /* No destructor defined for MINUS */
        /* No destructor defined for GT */
        break;
      case 30:
#line 317 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1275 "./xtxlegal.c"
        /* No destructor defined for EQUAL */
        /* No destructor defined for EQUAL */
        break;
      case 31:
#line 318 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1282 "./xtxlegal.c"
        /* No destructor defined for LT */
        /* No destructor defined for EQUAL */
        break;
      case 32:
#line 319 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1289 "./xtxlegal.c"
        /* No destructor defined for GT */
        /* No destructor defined for EQUAL */
        break;
      case 33:
#line 320 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1296 "./xtxlegal.c"
        /* No destructor defined for EXCL */
        /* No destructor defined for EQUAL */
        break;
      case 34:
#line 321 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1303 "./xtxlegal.c"
        /* No destructor defined for PLUS */
        /* No destructor defined for EQUAL */
        break;
      case 35:
#line 322 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1310 "./xtxlegal.c"
        /* No destructor defined for MINUS */
        /* No destructor defined for EQUAL */
        break;
      case 36:
#line 323 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1317 "./xtxlegal.c"
        /* No destructor defined for STAR */
        /* No destructor defined for EQUAL */
        break;
      case 37:
#line 324 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1324 "./xtxlegal.c"
        /* No destructor defined for SLASH */
        /* No destructor defined for EQUAL */
        break;
      case 38:
#line 325 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1331 "./xtxlegal.c"
        /* No destructor defined for MODULO */
        /* No destructor defined for EQUAL */
        break;
      case 39:
#line 326 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1338 "./xtxlegal.c"
        /* No destructor defined for STAR */
        /* No destructor defined for STAR */
        break;
      case 40:
#line 328 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1345 "./xtxlegal.c"
        /* No destructor defined for LT */
        /* No destructor defined for GT */
        break;
      case 41:
#line 330 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1352 "./xtxlegal.c"
        /* No destructor defined for xlst */
        break;
      case 42:
#line 331 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1358 "./xtxlegal.c"
        /* No destructor defined for LPAR */
        /* No destructor defined for xlst */
        break;
      case 43:
#line 332 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1365 "./xtxlegal.c"
        /* No destructor defined for LBRACKET */
        /* No destructor defined for expr */
        break;
      case 44:
#line 333 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-5].minor.yy0,yymsp[0].minor.yy0);}
#line 1372 "./xtxlegal.c"
        /* No destructor defined for LBRACKET */
        /* No destructor defined for expr */
        /* No destructor defined for DOTDOT */
        /* No destructor defined for expr */
        break;
      case 45:
#line 334 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-4].minor.yy0,yymsp[0].minor.yy0);}
#line 1381 "./xtxlegal.c"
        /* No destructor defined for LBRACKET */
        /* No destructor defined for expr */
        /* No destructor defined for DOTDOT */
        break;
      case 46:
#line 335 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-4].minor.yy0,yymsp[0].minor.yy0);}
#line 1389 "./xtxlegal.c"
        /* No destructor defined for LBRACKET */
        /* No destructor defined for DOTDOT */
        /* No destructor defined for expr */
        break;
      case 47:
#line 336 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1397 "./xtxlegal.c"
        /* No destructor defined for LBRACKET */
        /* No destructor defined for DOTDOT */
        break;
      case 48:
#line 337 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1404 "./xtxlegal.c"
        /* No destructor defined for xlst */
        break;
      case 49:
#line 338 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-5].minor.yy0,yymsp[0].minor.yy0);}
#line 1410 "./xtxlegal.c"
        /* No destructor defined for PIPE */
        /* No destructor defined for xlst */
        /* No destructor defined for PIPE */
        /* No destructor defined for xlst */
        break;
      case 50:
#line 340 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1419 "./xtxlegal.c"
        /* No destructor defined for COLON */
        /* No destructor defined for cast */
        break;
      case 51:
        break;
      case 52:
        /* No destructor defined for expr */
        break;
      case 53:
        /* No destructor defined for STAR */
        break;
      case 54:
        /* No destructor defined for STAR */
        /* No destructor defined for LBRACKET */
        /* No destructor defined for DOTDOT */
        /* No destructor defined for RBRACKET */
        break;
      case 55:
        /* No destructor defined for STAR */
        /* No destructor defined for LBRACKET */
        /* No destructor defined for expr */
        /* No destructor defined for DOTDOT */
        /* No destructor defined for RBRACKET */
        break;
      case 56:
        /* No destructor defined for STAR */
        /* No destructor defined for LBRACKET */
        /* No destructor defined for DOTDOT */
        /* No destructor defined for expr */
        /* No destructor defined for RBRACKET */
        break;
      case 57:
        /* No destructor defined for STAR */
        /* No destructor defined for LBRACKET */
        /* No destructor defined for expr */
        /* No destructor defined for DOTDOT */
        /* No destructor defined for expr */
        /* No destructor defined for RBRACKET */
        break;
      case 58:
        /* No destructor defined for xlst */
        /* No destructor defined for COMMA */
        break;
      case 59:
        /* No destructor defined for xlst */
        /* No destructor defined for COMMA */
        /* No destructor defined for expr */
        break;
      case 60:
        /* No destructor defined for xlst */
        /* No destructor defined for COMMA */
        /* No destructor defined for STAR */
        break;
      case 61:
        /* No destructor defined for xlst */
        /* No destructor defined for COMMA */
        /* No destructor defined for STAR */
        /* No destructor defined for LBRACKET */
        /* No destructor defined for DOTDOT */
        /* No destructor defined for RBRACKET */
        break;
      case 62:
        /* No destructor defined for xlst */
        /* No destructor defined for COMMA */
        /* No destructor defined for STAR */
        /* No destructor defined for LBRACKET */
        /* No destructor defined for expr */
        /* No destructor defined for DOTDOT */
        /* No destructor defined for RBRACKET */
        break;
      case 63:
        /* No destructor defined for xlst */
        /* No destructor defined for COMMA */
        /* No destructor defined for STAR */
        /* No destructor defined for LBRACKET */
        /* No destructor defined for DOTDOT */
        /* No destructor defined for expr */
        /* No destructor defined for RBRACKET */
        break;
      case 64:
        /* No destructor defined for xlst */
        /* No destructor defined for COMMA */
        /* No destructor defined for STAR */
        /* No destructor defined for LBRACKET */
        /* No destructor defined for expr */
        /* No destructor defined for DOTDOT */
        /* No destructor defined for expr */
        /* No destructor defined for RBRACKET */
        break;
      case 65:
        /* No destructor defined for LPAR */
        /* No destructor defined for expr */
        /* No destructor defined for RPAR */
        break;
      case 66:
        /* No destructor defined for LPAR */
        /* No destructor defined for expr */
        /* No destructor defined for AT */
        /* No destructor defined for expr */
        /* No destructor defined for RPAR */
        break;
      case 67:
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
#line 268 "./xtxlegal.lem"

    //printf("Syntax error.\n");
    termflag=1;

#line 1570 "./xtxlegal.c"
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
#line 273 "./xtxlegal.lem"

    //printf("Parsing complete.\n");

#line 1593 "./xtxlegal.c"
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
