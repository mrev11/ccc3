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
#define YYNOCODE 35
#define YYACTIONTYPE unsigned char
#define xtxlegalTOKENTYPE POS
typedef union {
  xtxlegalTOKENTYPE yy0;
  int yy69;
} YYMINORTYPE;
#define YYSTACKDEPTH 100
#define xtxlegalARG_SDECL
#define xtxlegalARG_PDECL
#define xtxlegalARG_FETCH
#define xtxlegalARG_STORE
#define YYNSTATE 153
#define YYNRULE 75
#define YYERRORSYMBOL 27
#define YYERRSYMDT yy69
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
 /*     0 */     2,   36,    3,    7,  117,   41,   35,   13,   31,   29,
 /*    10 */     9,   11,   15,   17,   19,   21,   23,   25,   33,   39,
 /*    20 */   116,  229,    1,  103,  212,   90,  141,    2,   36,    3,
 /*    30 */     7,   34,   41,   43,   13,   31,   29,    9,   11,   15,
 /*    40 */    17,   19,   21,   23,   25,   33,   39,   66,   44,    2,
 /*    50 */    36,    3,    7,   37,   41,  104,   13,   31,   29,    9,
 /*    60 */    11,   15,   17,   19,   21,   23,   25,   33,   39,   86,
 /*    70 */    78,    2,   36,    3,    7,  125,   41,   80,   13,   31,
 /*    80 */    29,    9,   11,   15,   17,   19,   21,   23,   25,   33,
 /*    90 */    39,    2,   36,    3,    7,   32,   41,   55,   13,   31,
 /*   100 */    29,    9,   11,   15,   17,   19,   21,   23,   25,   33,
 /*   110 */    39,    2,   36,    3,    7,   30,   41,  110,   13,   31,
 /*   120 */    29,    9,   11,   15,   17,   19,   21,   23,   25,   33,
 /*   130 */    39,    2,   36,    3,    7,   38,   41,   96,   13,   31,
 /*   140 */    29,    9,   11,   15,   17,   19,   21,   23,   25,   33,
 /*   150 */    39,    2,   36,    3,    7,   71,   41,   90,   13,   31,
 /*   160 */    29,    9,   11,   15,   17,   19,   21,   23,   25,   33,
 /*   170 */    39,  119,    2,   36,    3,    7,  127,   41,   89,   13,
 /*   180 */    31,   29,    9,   11,   15,   17,   19,   21,   23,   25,
 /*   190 */    33,   39,  153,   94,    2,   36,    3,    7,  139,   41,
 /*   200 */   123,   13,   31,   29,    9,   11,   15,   17,   19,   21,
 /*   210 */    23,   25,   33,   39,    2,   36,    3,    7,  143,   41,
 /*   220 */    84,   13,   31,   29,    9,   11,   15,   17,   19,   21,
 /*   230 */    23,   25,   33,   39,    2,   36,    3,    7,   42,   41,
 /*   240 */   100,   13,   31,   29,    9,   11,   15,   17,   19,   21,
 /*   250 */    23,   25,   33,   39,    2,   36,    3,    7,  137,   41,
 /*   260 */    46,   13,   31,   29,    9,   11,   15,   17,   19,   21,
 /*   270 */    23,   25,   33,   39,    2,   36,    3,    7,   28,   41,
 /*   280 */    61,   13,   31,   29,    9,   11,   15,   17,   19,   21,
 /*   290 */    23,   25,   33,   39,    4,    5,   27,   47,   49,   51,
 /*   300 */    53,   87,   56,   58,   60,   70,   75,   40,  105,  106,
 /*   310 */    65,  113,   74,   88,   67,   65,   65,   62,  111,    4,
 /*   320 */    26,   27,   47,   49,   51,   53,   45,   56,   58,   60,
 /*   330 */   115,   68,  121,    6,   76,  128,  120,  122,  126,  114,
 /*   340 */    40,   73,   62,  118,    4,    5,   27,   47,   49,   51,
 /*   350 */    53,   72,   56,   58,   60,   24,  142,   40,  112,   40,
 /*   360 */    63,   64,   65,  140,   67,   86,   77,   62,  111,    4,
 /*   370 */     5,   27,   47,   49,   51,   53,   69,   56,   58,   60,
 /*   380 */    65,   40,   68,   92,   22,  132,   50,   20,  130,   67,
 /*   390 */    79,   18,   62,  146,    4,    5,   27,   47,   49,   51,
 /*   400 */    53,  129,   56,   58,   60,  102,   75,   16,  135,   14,
 /*   410 */    12,   83,   10,  152,   67,  109,   48,   62,   59,    4,
 /*   420 */     5,   27,  148,   49,   51,   53,    8,   56,   58,   60,
 /*   430 */   133,   57,   52,    6,   99,  149,  150,  147,  151,   67,
 /*   440 */    95,   54,   62,   93,    4,    5,   27,   47,   49,   51,
 /*   450 */    53,  101,   56,   58,   60,  131,  111,  111,  111,  111,
 /*   460 */   111,  111,  111,  111,   67,  111,  111,   62,  111,    4,
 /*   470 */     5,   27,   47,   49,   51,   53,  111,   56,   58,   60,
 /*   480 */   111,  111,  111,  111,  111,  111,  111,  111,  134,   67,
 /*   490 */   111,  111,   62,  111,    4,    5,   27,   47,   49,   51,
 /*   500 */    53,  111,   56,   58,   60,  111,   75,  111,  111,  111,
 /*   510 */   111,  111,  111,  111,   67,  111,  111,   62,  111,    4,
 /*   520 */     5,   27,   47,   49,   51,   53,  111,   56,   58,   60,
 /*   530 */   111,  111,  111,  111,  111,  111,  111,  111,  111,   67,
 /*   540 */   111,  111,   62,  111,    4,    5,   27,   47,   49,   51,
 /*   550 */    53,  107,   56,   58,   60,  111,  111,  111,  111,  111,
 /*   560 */   111,  111,  111,  111,   67,  111,  111,   62,  111,    4,
 /*   570 */     5,   27,   47,   49,   51,   53,   81,   56,   58,   60,
 /*   580 */   111,  111,  111,  111,  111,  111,  111,  111,  111,   67,
 /*   590 */   111,  111,   62,  111,    4,    5,   27,   47,   49,   51,
 /*   600 */    53,  111,   56,   58,   60,  111,  111,  111,  111,  111,
 /*   610 */   111,  111,  111,  111,   67,  111,   82,   62,    4,    5,
 /*   620 */    27,   47,   49,   51,   53,   97,   56,   58,   60,  111,
 /*   630 */   111,  111,  111,  111,  111,  111,  111,  111,   67,  111,
 /*   640 */   111,   62,  111,    4,    5,   27,   47,   49,   51,   53,
 /*   650 */   111,   56,   58,   60,  111,  111,  111,  111,  111,  111,
 /*   660 */   111,  111,  111,   67,  111,  108,   62,    4,    5,   27,
 /*   670 */    47,   49,   51,   53,   85,   56,   58,   60,  111,  111,
 /*   680 */   111,  111,  111,  111,  111,  111,  111,   67,  111,  111,
 /*   690 */    62,  111,    4,    5,   27,   47,  144,   51,   53,  111,
 /*   700 */    56,   58,   60,  111,  111,  111,  111,  111,  111,  111,
 /*   710 */   111,  145,   67,  111,  111,   62,  111,    4,    5,   27,
 /*   720 */    47,   49,   51,   53,  111,   56,   58,   60,  111,   91,
 /*   730 */   111,  111,  111,  111,  111,  111,  111,   67,  111,  111,
 /*   740 */    62,  111,    4,    5,   27,   47,   49,   51,   53,  111,
 /*   750 */    56,   58,   60,  111,  111,  111,  111,  111,  111,  111,
 /*   760 */   111,  124,   67,  111,  111,   62,  111,    4,    5,   27,
 /*   770 */    47,   49,   51,   53,  111,   56,   58,   60,  111,  111,
 /*   780 */   111,  111,  111,  111,  111,  111,  138,   67,  111,  111,
 /*   790 */    62,  111,    4,    5,   27,   47,   49,   51,   53,  111,
 /*   800 */    56,   58,   60,  111,  111,  111,  111,  111,  111,  111,
 /*   810 */   111,  136,   67,  111,  111,   62,  111,    4,    5,   27,
 /*   820 */    47,   49,   51,   53,  111,   56,   58,   60,  111,  111,
 /*   830 */   111,  111,  111,  111,  111,  111,  111,   67,  111,   98,
 /*   840 */    62,    4,    5,   27,   47,   49,   51,   53,  111,   56,
 /*   850 */    58,   60,  111,  111,  111,  111,  111,  111,  111,  111,
 /*   860 */   111,   67,  111,  111,   62,  111,    4,   26,   27,   47,
 /*   870 */    49,   51,   53,  111,   56,   58,   60,  111,  111,  111,
 /*   880 */   111,  111,  111,  111,  111,  111,  114,  111,  111,   62,
};
static YYCODETYPE yy_lookahead[] = {
 /*     0 */     2,    3,    4,    5,    6,    7,   29,    9,   10,   11,
 /*    10 */    12,   13,   14,   15,   16,   17,   18,   19,   20,   21,
 /*    20 */    22,   28,   29,   31,   26,   33,   29,    2,    3,    4,
 /*    30 */     5,   20,    7,    8,    9,   10,   11,   12,   13,   14,
 /*    40 */    15,   16,   17,   18,   19,   20,   21,   29,   23,    2,
 /*    50 */     3,    4,    5,   20,    7,   12,    9,   10,   11,   12,
 /*    60 */    13,   14,   15,   16,   17,   18,   19,   20,   21,   26,
 /*    70 */    23,    2,    3,    4,    5,   29,    7,    8,    9,   10,
 /*    80 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*    90 */    21,    2,    3,    4,    5,   29,    7,    8,    9,   10,
 /*   100 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   110 */    21,    2,    3,    4,    5,   29,    7,    8,    9,   10,
 /*   120 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   130 */    21,    2,    3,    4,    5,   29,    7,    8,    9,   10,
 /*   140 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   150 */    21,    2,    3,    4,    5,   31,    7,   33,    9,   10,
 /*   160 */    11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
 /*   170 */    21,   22,    2,    3,    4,    5,   29,    7,   33,    9,
 /*   180 */    10,   11,   12,   13,   14,   15,   16,   17,   18,   19,
 /*   190 */    20,   21,    0,   23,    2,    3,    4,    5,   29,    7,
 /*   200 */    29,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*   210 */    18,   19,   20,   21,    2,    3,    4,    5,   29,    7,
 /*   220 */     8,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*   230 */    18,   19,   20,   21,    2,    3,    4,    5,   29,    7,
 /*   240 */     8,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*   250 */    18,   19,   20,   21,    2,    3,    4,    5,   29,    7,
 /*   260 */     8,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*   270 */    18,   19,   20,   21,    2,    3,    4,    5,   29,    7,
 /*   280 */    29,    9,   10,   11,   12,   13,   14,   15,   16,   17,
 /*   290 */    18,   19,   20,   21,    1,    2,    3,    4,    5,    6,
 /*   300 */     7,    1,    9,   10,   11,   12,   13,   29,   30,   25,
 /*   310 */    26,   22,   22,   13,   21,   26,   26,   24,   34,    1,
 /*   320 */     2,    3,    4,    5,    6,    7,   29,    9,   10,   11,
 /*   330 */    29,   30,   29,   29,    7,   32,   32,   19,   20,   21,
 /*   340 */    29,   30,   24,   29,    1,    2,    3,    4,    5,    6,
 /*   350 */     7,   12,    9,   10,   11,   29,   13,   29,   30,   29,
 /*   360 */    30,   25,   26,   20,   21,   26,   29,   24,   34,    1,
 /*   370 */     2,    3,    4,    5,    6,    7,   22,    9,   10,   11,
 /*   380 */    26,   29,   30,    7,   29,   17,   29,   29,   20,   21,
 /*   390 */    29,   29,   24,   29,    1,    2,    3,    4,    5,    6,
 /*   400 */     7,   29,    9,   10,   11,   12,   13,   29,   29,   29,
 /*   410 */    29,   29,   29,   29,   21,   29,   29,   24,   29,    1,
 /*   420 */     2,    3,    4,    5,    6,    7,   29,    9,   10,   11,
 /*   430 */    29,   29,   29,   29,   29,   17,   29,   29,   20,   21,
 /*   440 */    29,   29,   24,   29,    1,    2,    3,    4,    5,    6,
 /*   450 */     7,    8,    9,   10,   11,   29,   34,   34,   34,   34,
 /*   460 */    34,   34,   34,   34,   21,   34,   34,   24,   34,    1,
 /*   470 */     2,    3,    4,    5,    6,    7,   34,    9,   10,   11,
 /*   480 */    34,   34,   34,   34,   34,   34,   34,   34,   20,   21,
 /*   490 */    34,   34,   24,   34,    1,    2,    3,    4,    5,    6,
 /*   500 */     7,   34,    9,   10,   11,   34,   13,   34,   34,   34,
 /*   510 */    34,   34,   34,   34,   21,   34,   34,   24,   34,    1,
 /*   520 */     2,    3,    4,    5,    6,    7,    8,    9,   10,   11,
 /*   530 */    34,   34,   34,   34,   34,   34,   34,   34,   34,   21,
 /*   540 */    34,   34,   24,   34,    1,    2,    3,    4,    5,    6,
 /*   550 */     7,    8,    9,   10,   11,   34,   34,   34,   34,   34,
 /*   560 */    34,   34,   34,   34,   21,   34,   34,   24,   34,    1,
 /*   570 */     2,    3,    4,    5,    6,    7,    8,    9,   10,   11,
 /*   580 */    34,   34,   34,   34,   34,   34,   34,   34,   34,   21,
 /*   590 */    34,   34,   24,   34,    1,    2,    3,    4,    5,    6,
 /*   600 */     7,   34,    9,   10,   11,   34,   34,   34,   34,   34,
 /*   610 */    34,   34,   34,   34,   21,   34,   23,   24,    1,    2,
 /*   620 */     3,    4,    5,    6,    7,    8,    9,   10,   11,   34,
 /*   630 */    34,   34,   34,   34,   34,   34,   34,   34,   21,   34,
 /*   640 */    34,   24,   34,    1,    2,    3,    4,    5,    6,    7,
 /*   650 */    34,    9,   10,   11,   34,   34,   34,   34,   34,   34,
 /*   660 */    34,   34,   34,   21,   34,   23,   24,    1,    2,    3,
 /*   670 */     4,    5,    6,    7,    8,    9,   10,   11,   34,   34,
 /*   680 */    34,   34,   34,   34,   34,   34,   34,   21,   34,   34,
 /*   690 */    24,   34,    1,    2,    3,    4,    5,    6,    7,   34,
 /*   700 */     9,   10,   11,   34,   34,   34,   34,   34,   34,   34,
 /*   710 */    34,   20,   21,   34,   34,   24,   34,    1,    2,    3,
 /*   720 */     4,    5,    6,    7,   34,    9,   10,   11,   34,   13,
 /*   730 */    34,   34,   34,   34,   34,   34,   34,   21,   34,   34,
 /*   740 */    24,   34,    1,    2,    3,    4,    5,    6,    7,   34,
 /*   750 */     9,   10,   11,   34,   34,   34,   34,   34,   34,   34,
 /*   760 */    34,   20,   21,   34,   34,   24,   34,    1,    2,    3,
 /*   770 */     4,    5,    6,    7,   34,    9,   10,   11,   34,   34,
 /*   780 */    34,   34,   34,   34,   34,   34,   20,   21,   34,   34,
 /*   790 */    24,   34,    1,    2,    3,    4,    5,    6,    7,   34,
 /*   800 */     9,   10,   11,   34,   34,   34,   34,   34,   34,   34,
 /*   810 */    34,   20,   21,   34,   34,   24,   34,    1,    2,    3,
 /*   820 */     4,    5,    6,    7,   34,    9,   10,   11,   34,   34,
 /*   830 */    34,   34,   34,   34,   34,   34,   34,   21,   34,   23,
 /*   840 */    24,    1,    2,    3,    4,    5,    6,    7,   34,    9,
 /*   850 */    10,   11,   34,   34,   34,   34,   34,   34,   34,   34,
 /*   860 */    34,   21,   34,   34,   24,   34,    1,    2,    3,    4,
 /*   870 */     5,    6,    7,   34,    9,   10,   11,   34,   34,   34,
 /*   880 */    34,   34,   34,   34,   34,   34,   21,   34,   34,   24,
};
#define YY_SHIFT_USE_DFLT (-3)
static short yy_shift_ofst[] = {
 /*     0 */   840,  192,   -3,  418,   -3,  840,  272,  691,  272,  840,
 /*    10 */   272,  343,  272,  766,  272,  791,  272,  840,  272,  840,
 /*    20 */   272,  468,  272,  368,  272,  318,  865,  840,  272,  840,
 /*    30 */   272,  840,  272,   11,  840,  272,   33,  840,  272,  493,
 /*    40 */   272,  642,   25,   -3,  543,  252,   -3,  840,  272,  840,
 /*    50 */   272,  840,  272,  840,   89,   -3,  840,  272,  840,  272,
 /*    60 */   840,  272,  393,  336,   -3,  716,  272,  293,  354,   -3,
 /*    70 */   300,  339,  493,  290,   -3,  327,  593,   47,  568,   69,
 /*    80 */    -3,   -3,  666,  212,   -3,   -3,  300,   -3,   -3,   -3,
 /*    90 */    -3,  376,  816,  170,  617,  129,   -3,   -3,  443,  232,
 /*   100 */    -3,   -3,  300,   43,  493,  284,   -3,   -3,  518,  109,
 /*   110 */    -3,   -3,  289,   -3,  293,   -2,   -3,  840,  149,   -3,
 /*   120 */    -3,  272,  741,  272,  840,  272,  840,  272,  840,  272,
 /*   130 */   840,  272,  840,  272,  840,  272,  840,  272,  840,  272,
 /*   140 */   840,  272,  840,  272,  840,  840,  272,  272,  840,  840,
 /*   150 */   272,  840,  272,
};
#define YY_REDUCE_USE_DFLT (-24)
static short yy_reduce_ofst[] = {
 /*     0 */    -7,  -24,  -24,  408,  -24,  404,  -24,  397,  -24,  383,
 /*    10 */   -24,  381,  -24,  380,  -24,  378,  -24,  362,  -24,  358,
 /*    20 */   -24,  355,  -24,  326,  -24,  303,  304,  249,  -24,   86,
 /*    30 */   -24,   66,  -24,  -24,  -23,  -24,  -24,  106,  -24,  328,
 /*    40 */   -24,  209,  -24,  -24,  297,  -24,  -24,  387,  -24,  357,
 /*    50 */   -24,  403,  -24,  412,  -24,  -24,  402,  -24,  389,  -24,
 /*    60 */   251,  -24,  330,  -24,  -24,   18,  -24,  352,  -24,  -24,
 /*    70 */   124,  -24,  311,  -24,  -24,  -24,  337,  -24,  361,  -24,
 /*    80 */   -24,  -24,  382,  -24,  -24,  -24,  145,  -24,  -24,  -24,
 /*    90 */   -24,  -24,  414,  -24,  411,  -24,  -24,  -24,  405,  -24,
 /*   100 */   -24,  -24,   -8,  -24,  278,  -24,  -24,  -24,  386,  -24,
 /*   110 */   -24,  -24,  -24,  -24,  301,  -24,  -24,  314,  -24,  -24,
 /*   120 */   -24,  -24,  171,  -24,   46,  -24,  147,  -24,  372,  -24,
 /*   130 */   426,  -24,  401,  -24,  379,  -24,  229,  -24,  169,  -24,
 /*   140 */    -3,  -24,  189,  -24,  357,  364,  -24,  -24,  387,  407,
 /*   150 */   -24,  384,  -24,
};
static YYACTIONTYPE yy_default[] = {
 /*     0 */   228,  228,  156,  228,  154,  228,  155,  228,  168,  228,
 /*    10 */   167,  228,  170,  228,  171,  228,  172,  228,  173,  228,
 /*    20 */   174,  228,  175,  228,  176,  228,  228,  228,  157,  228,
 /*    30 */   180,  228,  181,  228,  228,  184,  228,  228,  187,  211,
 /*    40 */   212,  228,  228,  196,  228,  228,  197,  228,  158,  228,
 /*    50 */   159,  228,  160,  228,  228,  161,  228,  162,  228,  163,
 /*    60 */   228,  164,  211,  228,  201,  218,  219,  211,  228,  202,
 /*    70 */   208,  228,  211,  228,  204,  213,  228,  228,  228,  228,
 /*    80 */   217,  215,  228,  228,  216,  214,  228,  206,  207,  210,
 /*    90 */   209,  220,  228,  228,  228,  228,  224,  222,  228,  228,
 /*   100 */   223,  221,  208,  228,  211,  228,  203,  198,  228,  228,
 /*   110 */   199,  200,  228,  195,  211,  228,  225,  228,  228,  226,
 /*   120 */   227,  177,  228,  178,  228,  179,  228,  182,  228,  205,
 /*   130 */   228,  185,  228,  194,  228,  186,  228,  192,  228,  191,
 /*   140 */   228,  190,  228,  193,  166,  228,  188,  169,  165,  228,
 /*   150 */   183,  228,  189,
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
  "PIPE",          "STAR",          "MODULO",        "POWER",       
  "DOLLAR",        "GT",            "LT",            "COLON",       
  "EQUAL",         "LPAR",          "RPAR",          "DOTDOT",      
  "LBRACE",        "RBRACE",        "COMMA",         "error",       
  "start",         "expr",          "xlst",          "barglst",     
  "cast",          "blkarg",      
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
 /*  14 */ "expr ::= expr PIPE expr",
 /*  15 */ "expr ::= expr PLUS expr",
 /*  16 */ "expr ::= expr MINUS expr",
 /*  17 */ "expr ::= expr STAR expr",
 /*  18 */ "expr ::= expr SLASH expr",
 /*  19 */ "expr ::= expr MODULO expr",
 /*  20 */ "expr ::= expr POWER expr",
 /*  21 */ "expr ::= expr DOLLAR expr",
 /*  22 */ "expr ::= expr GT expr",
 /*  23 */ "expr ::= expr LT expr",
 /*  24 */ "expr ::= expr COLON expr",
 /*  25 */ "expr ::= expr COLON COLON expr",
 /*  26 */ "expr ::= expr COLON COLON EQUAL expr",
 /*  27 */ "expr ::= expr DOT expr",
 /*  28 */ "expr ::= expr BSLASH expr",
 /*  29 */ "expr ::= expr COLON EQUAL expr",
 /*  30 */ "expr ::= expr MINUS GT expr",
 /*  31 */ "expr ::= expr EQUAL EQUAL expr",
 /*  32 */ "expr ::= expr LT EQUAL expr",
 /*  33 */ "expr ::= expr GT EQUAL expr",
 /*  34 */ "expr ::= expr EXCL EQUAL expr",
 /*  35 */ "expr ::= expr PLUS EQUAL expr",
 /*  36 */ "expr ::= expr MINUS EQUAL expr",
 /*  37 */ "expr ::= expr STAR EQUAL expr",
 /*  38 */ "expr ::= expr SLASH EQUAL expr",
 /*  39 */ "expr ::= expr MODULO EQUAL expr",
 /*  40 */ "expr ::= expr STAR STAR expr",
 /*  41 */ "expr ::= expr LT GT expr",
 /*  42 */ "expr ::= expr LPAR xlst RPAR",
 /*  43 */ "expr ::= expr LBRACKET expr RBRACKET",
 /*  44 */ "expr ::= expr LBRACKET expr DOTDOT expr RBRACKET",
 /*  45 */ "expr ::= expr LBRACKET expr DOTDOT RBRACKET",
 /*  46 */ "expr ::= expr LBRACKET DOTDOT expr RBRACKET",
 /*  47 */ "expr ::= expr LBRACKET DOTDOT RBRACKET",
 /*  48 */ "expr ::= LBRACE xlst RBRACE",
 /*  49 */ "expr ::= LPAR xlst RPAR",
 /*  50 */ "expr ::= LBRACE PIPE barglst PIPE xlst RBRACE",
 /*  51 */ "expr ::= LPAR PIPE barglst PIPE xlst RPAR",
 /*  52 */ "expr ::= expr COLON cast expr",
 /*  53 */ "blkarg ::= EXPR",
 /*  54 */ "blkarg ::= STAR",
 /*  55 */ "barglst ::=",
 /*  56 */ "barglst ::= blkarg",
 /*  57 */ "barglst ::= barglst COMMA blkarg",
 /*  58 */ "xlst ::=",
 /*  59 */ "xlst ::= expr",
 /*  60 */ "xlst ::= STAR",
 /*  61 */ "xlst ::= STAR LBRACKET DOTDOT RBRACKET",
 /*  62 */ "xlst ::= STAR LBRACKET expr DOTDOT RBRACKET",
 /*  63 */ "xlst ::= STAR LBRACKET DOTDOT expr RBRACKET",
 /*  64 */ "xlst ::= STAR LBRACKET expr DOTDOT expr RBRACKET",
 /*  65 */ "xlst ::= xlst COMMA",
 /*  66 */ "xlst ::= xlst COMMA expr",
 /*  67 */ "xlst ::= xlst COMMA STAR",
 /*  68 */ "xlst ::= xlst COMMA STAR LBRACKET DOTDOT RBRACKET",
 /*  69 */ "xlst ::= xlst COMMA STAR LBRACKET expr DOTDOT RBRACKET",
 /*  70 */ "xlst ::= xlst COMMA STAR LBRACKET DOTDOT expr RBRACKET",
 /*  71 */ "xlst ::= xlst COMMA STAR LBRACKET expr DOTDOT expr RBRACKET",
 /*  72 */ "cast ::= LPAR expr RPAR",
 /*  73 */ "cast ::= LPAR expr AT expr RPAR",
 /*  74 */ "cast ::= SPACE cast",
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
  { 29, 4 },
  { 29, 4 },
  { 29, 6 },
  { 29, 5 },
  { 29, 5 },
  { 29, 4 },
  { 29, 3 },
  { 29, 3 },
  { 29, 6 },
  { 29, 6 },
  { 29, 4 },
  { 33, 1 },
  { 33, 1 },
  { 31, 0 },
  { 31, 1 },
  { 31, 3 },
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
  { 32, 3 },
  { 32, 5 },
  { 32, 2 },
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
#line 1136 "./xtxlegal.c"
        break;
      case 2:
#line 285 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1141 "./xtxlegal.c"
        break;
      case 3:
#line 286 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1146 "./xtxlegal.c"
        break;
      case 4:
#line 288 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1151 "./xtxlegal.c"
        break;
      case 5:
#line 289 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1156 "./xtxlegal.c"
        break;
      case 6:
#line 290 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1161 "./xtxlegal.c"
        break;
      case 7:
#line 291 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1166 "./xtxlegal.c"
        break;
      case 8:
#line 292 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1171 "./xtxlegal.c"
        /* No destructor defined for expr */
        break;
      case 9:
#line 293 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1177 "./xtxlegal.c"
        break;
      case 10:
#line 294 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1182 "./xtxlegal.c"
        break;
      case 11:
#line 295 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-1].minor.yy0,yymsp[0].minor.yy0);}
#line 1187 "./xtxlegal.c"
        break;
      case 12:
#line 297 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1192 "./xtxlegal.c"
        /* No destructor defined for MINUS */
        break;
      case 13:
#line 298 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1198 "./xtxlegal.c"
        /* No destructor defined for PLUS */
        break;
      case 14:
#line 300 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1204 "./xtxlegal.c"
        /* No destructor defined for PIPE */
        break;
      case 15:
#line 301 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1210 "./xtxlegal.c"
        /* No destructor defined for PLUS */
        break;
      case 16:
#line 302 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1216 "./xtxlegal.c"
        /* No destructor defined for MINUS */
        break;
      case 17:
#line 303 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1222 "./xtxlegal.c"
        /* No destructor defined for STAR */
        break;
      case 18:
#line 304 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1228 "./xtxlegal.c"
        /* No destructor defined for SLASH */
        break;
      case 19:
#line 305 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1234 "./xtxlegal.c"
        /* No destructor defined for MODULO */
        break;
      case 20:
#line 306 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1240 "./xtxlegal.c"
        /* No destructor defined for POWER */
        break;
      case 21:
#line 307 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1246 "./xtxlegal.c"
        /* No destructor defined for DOLLAR */
        break;
      case 22:
#line 308 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1252 "./xtxlegal.c"
        /* No destructor defined for GT */
        break;
      case 23:
#line 309 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1258 "./xtxlegal.c"
        /* No destructor defined for LT */
        break;
      case 24:
#line 310 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1264 "./xtxlegal.c"
        /* No destructor defined for COLON */
        break;
      case 25:
#line 311 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1270 "./xtxlegal.c"
        /* No destructor defined for COLON */
        /* No destructor defined for COLON */
        break;
      case 26:
#line 312 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-4].minor.yy0,yymsp[0].minor.yy0);}
#line 1277 "./xtxlegal.c"
        /* No destructor defined for COLON */
        /* No destructor defined for COLON */
        /* No destructor defined for EQUAL */
        break;
      case 27:
#line 313 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1285 "./xtxlegal.c"
        /* No destructor defined for DOT */
        break;
      case 28:
#line 314 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1291 "./xtxlegal.c"
        /* No destructor defined for BSLASH */
        break;
      case 29:
#line 316 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1297 "./xtxlegal.c"
        /* No destructor defined for COLON */
        /* No destructor defined for EQUAL */
        break;
      case 30:
#line 317 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1304 "./xtxlegal.c"
        /* No destructor defined for MINUS */
        /* No destructor defined for GT */
        break;
      case 31:
#line 318 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1311 "./xtxlegal.c"
        /* No destructor defined for EQUAL */
        /* No destructor defined for EQUAL */
        break;
      case 32:
#line 319 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1318 "./xtxlegal.c"
        /* No destructor defined for LT */
        /* No destructor defined for EQUAL */
        break;
      case 33:
#line 320 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1325 "./xtxlegal.c"
        /* No destructor defined for GT */
        /* No destructor defined for EQUAL */
        break;
      case 34:
#line 321 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1332 "./xtxlegal.c"
        /* No destructor defined for EXCL */
        /* No destructor defined for EQUAL */
        break;
      case 35:
#line 322 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1339 "./xtxlegal.c"
        /* No destructor defined for PLUS */
        /* No destructor defined for EQUAL */
        break;
      case 36:
#line 323 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1346 "./xtxlegal.c"
        /* No destructor defined for MINUS */
        /* No destructor defined for EQUAL */
        break;
      case 37:
#line 324 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1353 "./xtxlegal.c"
        /* No destructor defined for STAR */
        /* No destructor defined for EQUAL */
        break;
      case 38:
#line 325 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1360 "./xtxlegal.c"
        /* No destructor defined for SLASH */
        /* No destructor defined for EQUAL */
        break;
      case 39:
#line 326 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1367 "./xtxlegal.c"
        /* No destructor defined for MODULO */
        /* No destructor defined for EQUAL */
        break;
      case 40:
#line 327 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1374 "./xtxlegal.c"
        /* No destructor defined for STAR */
        /* No destructor defined for STAR */
        break;
      case 41:
#line 328 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1381 "./xtxlegal.c"
        /* No destructor defined for LT */
        /* No destructor defined for GT */
        break;
      case 42:
#line 330 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1388 "./xtxlegal.c"
        /* No destructor defined for LPAR */
        /* No destructor defined for xlst */
        break;
      case 43:
#line 331 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1395 "./xtxlegal.c"
        /* No destructor defined for LBRACKET */
        /* No destructor defined for expr */
        break;
      case 44:
#line 332 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-5].minor.yy0,yymsp[0].minor.yy0);}
#line 1402 "./xtxlegal.c"
        /* No destructor defined for LBRACKET */
        /* No destructor defined for expr */
        /* No destructor defined for DOTDOT */
        /* No destructor defined for expr */
        break;
      case 45:
#line 333 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-4].minor.yy0,yymsp[0].minor.yy0);}
#line 1411 "./xtxlegal.c"
        /* No destructor defined for LBRACKET */
        /* No destructor defined for expr */
        /* No destructor defined for DOTDOT */
        break;
      case 46:
#line 334 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-4].minor.yy0,yymsp[0].minor.yy0);}
#line 1419 "./xtxlegal.c"
        /* No destructor defined for LBRACKET */
        /* No destructor defined for DOTDOT */
        /* No destructor defined for expr */
        break;
      case 47:
#line 335 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1427 "./xtxlegal.c"
        /* No destructor defined for LBRACKET */
        /* No destructor defined for DOTDOT */
        break;
      case 48:
#line 336 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1434 "./xtxlegal.c"
        /* No destructor defined for xlst */
        break;
      case 49:
#line 337 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-2].minor.yy0,yymsp[0].minor.yy0);}
#line 1440 "./xtxlegal.c"
        /* No destructor defined for xlst */
        break;
      case 50:
#line 338 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-5].minor.yy0,yymsp[0].minor.yy0);}
#line 1446 "./xtxlegal.c"
        /* No destructor defined for PIPE */
        /* No destructor defined for barglst */
        /* No destructor defined for PIPE */
        /* No destructor defined for xlst */
        break;
      case 51:
#line 339 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-5].minor.yy0,yymsp[0].minor.yy0);}
#line 1455 "./xtxlegal.c"
        /* No destructor defined for PIPE */
        /* No destructor defined for barglst */
        /* No destructor defined for PIPE */
        /* No destructor defined for xlst */
        break;
      case 52:
#line 341 "./xtxlegal.lem"
{yygotominor.yy0=pstore(yymsp[-3].minor.yy0,yymsp[0].minor.yy0);}
#line 1464 "./xtxlegal.c"
        /* No destructor defined for COLON */
        /* No destructor defined for cast */
        break;
      case 53:
        /* No destructor defined for EXPR */
        break;
      case 54:
        /* No destructor defined for STAR */
        break;
      case 55:
        break;
      case 56:
        /* No destructor defined for blkarg */
        break;
      case 57:
        /* No destructor defined for barglst */
        /* No destructor defined for COMMA */
        /* No destructor defined for blkarg */
        break;
      case 58:
        break;
      case 59:
        /* No destructor defined for expr */
        break;
      case 60:
        /* No destructor defined for STAR */
        break;
      case 61:
        /* No destructor defined for STAR */
        /* No destructor defined for LBRACKET */
        /* No destructor defined for DOTDOT */
        /* No destructor defined for RBRACKET */
        break;
      case 62:
        /* No destructor defined for STAR */
        /* No destructor defined for LBRACKET */
        /* No destructor defined for expr */
        /* No destructor defined for DOTDOT */
        /* No destructor defined for RBRACKET */
        break;
      case 63:
        /* No destructor defined for STAR */
        /* No destructor defined for LBRACKET */
        /* No destructor defined for DOTDOT */
        /* No destructor defined for expr */
        /* No destructor defined for RBRACKET */
        break;
      case 64:
        /* No destructor defined for STAR */
        /* No destructor defined for LBRACKET */
        /* No destructor defined for expr */
        /* No destructor defined for DOTDOT */
        /* No destructor defined for expr */
        /* No destructor defined for RBRACKET */
        break;
      case 65:
        /* No destructor defined for xlst */
        /* No destructor defined for COMMA */
        break;
      case 66:
        /* No destructor defined for xlst */
        /* No destructor defined for COMMA */
        /* No destructor defined for expr */
        break;
      case 67:
        /* No destructor defined for xlst */
        /* No destructor defined for COMMA */
        /* No destructor defined for STAR */
        break;
      case 68:
        /* No destructor defined for xlst */
        /* No destructor defined for COMMA */
        /* No destructor defined for STAR */
        /* No destructor defined for LBRACKET */
        /* No destructor defined for DOTDOT */
        /* No destructor defined for RBRACKET */
        break;
      case 69:
        /* No destructor defined for xlst */
        /* No destructor defined for COMMA */
        /* No destructor defined for STAR */
        /* No destructor defined for LBRACKET */
        /* No destructor defined for expr */
        /* No destructor defined for DOTDOT */
        /* No destructor defined for RBRACKET */
        break;
      case 70:
        /* No destructor defined for xlst */
        /* No destructor defined for COMMA */
        /* No destructor defined for STAR */
        /* No destructor defined for LBRACKET */
        /* No destructor defined for DOTDOT */
        /* No destructor defined for expr */
        /* No destructor defined for RBRACKET */
        break;
      case 71:
        /* No destructor defined for xlst */
        /* No destructor defined for COMMA */
        /* No destructor defined for STAR */
        /* No destructor defined for LBRACKET */
        /* No destructor defined for expr */
        /* No destructor defined for DOTDOT */
        /* No destructor defined for expr */
        /* No destructor defined for RBRACKET */
        break;
      case 72:
        /* No destructor defined for LPAR */
        /* No destructor defined for expr */
        /* No destructor defined for RPAR */
        break;
      case 73:
        /* No destructor defined for LPAR */
        /* No destructor defined for expr */
        /* No destructor defined for AT */
        /* No destructor defined for expr */
        /* No destructor defined for RPAR */
        break;
      case 74:
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

#line 1631 "./xtxlegal.c"
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

#line 1654 "./xtxlegal.c"
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
