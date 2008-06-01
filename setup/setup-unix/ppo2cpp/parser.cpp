
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
//void ParseTrace(FILE *TraceFILE, const char *zTracePrompt);

/* Driver template for the LEMON parser generator.
** The author disclaims copyright to this source code.
*/
/* First off, code is include which follows the "include" declaration
** in the input file. */
#include <stdio.h>
#line 21 "./parser.lem"


#include <stdlib.h>
#include <parsenode.h>
#include <lexer.h>
#include <codegen.h>
#include <nodetab.h>

extern ppo2cpp_lexer *lexer;

int headerflag=1;
int parsing_complete=1;
static int blockflag=0;

static void nested_block()
{
    fprintf(stderr,"Error: nested code block at #line %d %s.\n",
            lexer->getinputlineno(),
            lexer->getinputfspec());

    exit(1);
}

static void double_defined_symbol(parsenode *p)
{
    fprintf(stderr,"Error: double defined symbol at #line %d %s (%s).\n",
            p->lineno, //lexer->getinputlineno(),
            lexer->getinputfspec(),
            p->text);

    exit(1);
}


static void add_static(parsenode *p)
{
    if( headerflag )
    {
        if( nodetab_globstat->search(p)>=0 )
        {
            double_defined_symbol(p);
        }
        nodetab_globstat->add(p);
    }
    else
    {
        if( nodetab_locstat->search(p)>=0 || nodetab_local->search(p)>=0 )
        {
            double_defined_symbol(p);
        }
        nodetab_locstat->add(p);
    }
}


static void add_local(parsenode *p)
{
    if( nodetab_locstat->search(p)>=0 || nodetab_local->search(p)>=0 )
    {
        double_defined_symbol(p);
    }
    nodetab_local->add(p);
}


static void add_blkarg(parsenode *p)
{
    //Itt felmerült, hogy hibát jelezzek, ha a blockargumentum 
    //korábbról definiálva van locstat-ként, vagy local-ként. 
    //Ehelyett azt az elvet követem, hogy belső változók
    //mindig felüldefiniálhatják a külső változókat.
    //A régebbi változat is így működött.

    if( nodetab_blkarg->search(p)>=0 )
    {
        double_defined_symbol(p);
    }
    nodetab_blkarg->add(p);
}


static void symbol_search(parsenode *p)
{
    int x;

    if( blockflag && (x=nodetab_blkarg->search(p))>=0 )
    {
        p->cargo=(x+1)|SYM_BLKARG;
    }
    else if( (x=nodetab_local->search(p))>=0 )
    {
        p->cargo=x|(blockflag?SYM_BLKLOC:SYM_LOCAL);
    }
    else if( (x=nodetab_locstat->search(p))>=0 )
    {
        p->cargo=x|(blockflag?SYM_BLKSTAT:SYM_LOCSTAT);
    }
    else if( (x=nodetab_globstat->search(p))>=0 )
    {
        p->cargo=x|SYM_GLOBSTAT;
    }
    else
    {
        fprintf(stderr,"Error: undefined symbol at #line %d %s (%s).\n",
                p->lineno, //lexer->getinputlineno(),
                lexer->getinputfspec(),
                p->text);
        exit(1);
    }

    //p->print("search");
    return;
}

static void write_strtab(FILE *strtab, parsenode *pnode)
{
    const char *p=pnode->text;
    int len=strlen(p);
    if( len>3 )
    {
        int i;
        for(i=0; i<len; i++)
        {
            if( isalpha(p[i]) || ((int)p[i]>128) )
            {
                break;
            }
        }
        if( i<len )
        {
            char inp[512];
            sprintf(inp,"%s",lexer->getinputfspec());
            unsigned int k;
            for( k=0; k<sizeof(inp); k++ )
            {
                if( inp[k]==0 )
                {
                    break;
                }
                else if( inp[k]=='\"' )
                {
                    inp[k]=' ';
                }
            }
            fprintf(strtab,"%s<<\"\" from %s (%d)\n",p,inp,pnode->lineno);
        }
    }
}


#line 165 "./parser.c"
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
**    ParseTOKENTYPE     is the data type used for minor tokens given 
**                       directly to the parser from the tokenizer.
**    YYMINORTYPE        is the data type used for all minor tokens.
**                       This is typically a union of many types, one of
**                       which is ParseTOKENTYPE.  The entry in the union
**                       for base tokens is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.
**    ParseARG_SDECL     A static variable declaration for the %extra_argument
**    ParseARG_PDECL     A parameter declaration for the %extra_argument
**    ParseARG_STORE     Code to store %extra_argument into yypParser
**    ParseARG_FETCH     Code to extract %extra_argument from yypParser
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
*/
/*  */
#define YYCODETYPE unsigned char
#define YYNOCODE 136
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE parsenode*
typedef union {
  ParseTOKENTYPE yy0;
  int yy271;
} YYMINORTYPE;
#define YYSTACKDEPTH 100
#define ParseARG_SDECL
#define ParseARG_PDECL
#define ParseARG_FETCH
#define ParseARG_STORE
#define YYNSTATE 315
#define YYNRULE 167
#define YYERRORSYMBOL 81
#define YYERRSYMDT yy271
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
 /*     0 */    18,   28,   61,   63,   65,   67,   69,   71,   60,   59,
 /*    10 */    35,   31,  137,   65,   67,   69,   71,   60,   59,   35,
 /*    20 */    31,  135,  133,  483,    1,  170,  293,  131,  129,  288,
 /*    30 */   290,  402,  394,   27,   32,   24,  155,  101,   91,  191,
 /*    40 */   260,  102,  239,  200,  243,  246,  183,  184,  208,  204,
 /*    50 */   209,   27,  219,  220,  222,   33,   91,  225,  229,  102,
 /*    60 */    14,    5,   18,   28,   17,   40,   41,   42,   43,   44,
 /*    70 */    45,   46,   47,  107,  137,  141,  103,  118,   71,   60,
 /*    80 */    59,   35,   31,  135,  133,    3,    4,    7,  149,  131,
 /*    90 */   129,  172,   13,  119,  103,  118,   27,   24,   10,  101,
 /*   100 */   315,   91,  168,    2,  236,   18,   19,    8,  183,  184,
 /*   110 */   218,  204,  209,  340,  219,  220,  222,  292,    4,  225,
 /*   120 */   229,   20,   22,  172,   18,   28,  324,   40,   41,   42,
 /*   130 */    43,   44,   45,   46,   47,  107,  137,   11,  141,  103,
 /*   140 */   118,  266,    8,  170,  162,  135,  133,  288,  290,   27,
 /*   150 */   274,  131,  129,  165,   91,  114,   25,   30,   27,   24,
 /*   160 */    27,  101,  324,   91,    6,   91,  106,  115,   37,    8,
 /*   170 */   183,  184,  403,  204,  209,   27,  219,  220,  222,  157,
 /*   180 */    91,  225,  229,   34,  116,  110,   18,   28,  282,   40,
 /*   190 */    41,   42,   43,   44,   45,   46,   47,  107,  137,   36,
 /*   200 */   287,  145,  105,  353,   27,  160,  359,  135,  133,   91,
 /*   210 */   263,  341,   48,  131,  129,   16,  179,  264,  111,    9,
 /*   220 */    27,   24,   27,  101,   18,   91,    8,   91,  252,   19,
 /*   230 */    97,    8,  183,  184,  404,  204,  209,  250,  219,  220,
 /*   240 */   222,  177,   27,  225,  229,  178,  167,   91,   18,   28,
 /*   250 */    50,   40,   41,   42,   43,   44,   45,   46,   47,  107,
 /*   260 */   137,   36,  328,   96,   12,  306,   27,  329,  305,  135,
 /*   270 */   133,   91,   27,   27,   52,  131,  129,   91,   91,   27,
 /*   280 */    54,   56,   19,   24,   91,  101,  188,   58,   18,  360,
 /*   290 */    35,   31,  190,   17,  183,  184,  395,  204,  209,   27,
 /*   300 */   219,  220,  222,   27,   91,  225,  229,   62,   91,  174,
 /*   310 */   345,   64,  283,   40,   41,   42,   43,   44,   45,   46,
 /*   320 */    47,  107,  415,  249,   39,   49,   51,   53,   55,   57,
 /*   330 */    87,   89,   18,   15,   73,   77,   79,   75,   81,   83,
 /*   340 */    85,   61,   63,   65,   67,   69,   71,   60,   59,   35,
 /*   350 */    31,   18,   28,   27,    8,  268,  267,  112,   91,   27,
 /*   360 */    27,   97,   18,  137,   91,   91,   27,   66,   68,  113,
 /*   370 */   230,   91,  135,  133,   70,   27,   21,   27,  131,  129,
 /*   380 */    91,   23,   91,   72,   19,   74,   24,  285,  101,  196,
 /*   390 */   339,  231,   36,  199,  147,  309,   38,  183,  184,  286,
 /*   400 */   204,  209,   26,  219,  220,  222,   27,   27,  225,  229,
 /*   410 */   306,   91,   91,  313,   76,   78,   40,   41,   42,   43,
 /*   420 */    44,   45,   46,   47,  107,  406,  154,   19,   29,   39,
 /*   430 */    49,   51,   53,   55,   57,   87,   89,  275,  281,   73,
 /*   440 */    77,   79,   75,   81,   83,   85,   61,   63,   65,   67,
 /*   450 */    69,   71,   60,   59,   35,   31,  124,   39,   49,   51,
 /*   460 */    53,   55,   57,   87,   89,  294,   92,   73,   77,   79,
 /*   470 */    75,   81,   83,   85,   61,   63,   65,   67,   69,   71,
 /*   480 */    60,   59,   35,   31,   27,  314,  414,  369,  237,   91,
 /*   490 */   269,  419,   80,  347,  298,  267,  100,   39,   49,   51,
 /*   500 */    53,   55,   57,   87,   89,   95,  412,   73,   77,   79,
 /*   510 */    75,   81,   83,   85,   61,   63,   65,   67,   69,   71,
 /*   520 */    60,   59,   35,   31,  424,   39,   49,   51,   53,   55,
 /*   530 */    57,   87,   89,  104,  422,   73,   77,   79,   75,   81,
 /*   540 */    83,   85,   61,   63,   65,   67,   69,   71,   60,   59,
 /*   550 */    35,   31,  124,   39,   49,   51,   53,   55,   57,   87,
 /*   560 */    89,  411,  362,   73,   77,   79,   75,   81,   83,   85,
 /*   570 */    61,   63,   65,   67,   69,   71,   60,   59,   35,   31,
 /*   580 */   126,   39,   49,   51,   53,   55,   57,   87,   89,  361,
 /*   590 */   117,   73,   77,   79,   75,   81,   83,   85,   61,   63,
 /*   600 */    65,   67,   69,   71,   60,   59,   35,   31,   39,   49,
 /*   610 */    51,   53,   55,   57,   87,   89,  284,  421,   73,   77,
 /*   620 */    79,   75,   81,   83,   85,   61,   63,   65,   67,   69,
 /*   630 */    71,   60,   59,   35,   31,    8,    8,  370,   18,  379,
 /*   640 */   276,  269,  128,   39,   49,   51,   53,   55,   57,   87,
 /*   650 */    89,  355,  257,   73,   77,   79,   75,   81,   83,   85,
 /*   660 */    61,   63,   65,   67,   69,   71,   60,   59,   35,   31,
 /*   670 */    18,  120,  351,    8,   39,   49,   51,   53,   55,   57,
 /*   680 */    87,   89,  122,  140,   73,   77,   79,   75,   81,   83,
 /*   690 */    85,   61,   63,   65,   67,   69,   71,   60,   59,   35,
 /*   700 */    31,   39,   49,   51,   53,   55,   57,   87,   89,  352,
 /*   710 */   146,   73,   77,   79,   75,   81,   83,   85,   61,   63,
 /*   720 */    65,   67,   69,   71,   60,   59,   35,   31,   89,  142,
 /*   730 */   144,   73,   77,   79,   75,   81,   83,   85,   61,   63,
 /*   740 */    65,   67,   69,   71,   60,   59,   35,   31,  213,  296,
 /*   750 */    18,  299,  148,  386,  300,  152,  151,   39,   49,   51,
 /*   760 */    53,   55,   57,   87,   89,   19,  156,   73,   77,   79,
 /*   770 */    75,   81,   83,   85,   61,   63,   65,   67,   69,   71,
 /*   780 */    60,   59,   35,   31,  407,    6,  159,  158,   39,   49,
 /*   790 */    51,   53,   55,   57,   87,   89,  161,  164,   73,   77,
 /*   800 */    79,   75,   81,   83,   85,   61,   63,   65,   67,   69,
 /*   810 */    71,   60,   59,   35,   31,   39,   49,   51,   53,   55,
 /*   820 */    57,   87,   89,  163,  166,   73,   77,   79,   75,   81,
 /*   830 */    83,   85,   61,   63,   65,   67,   69,   71,   60,   59,
 /*   840 */    35,   31,   28,   27,  413,  169,    8,   27,   91,   27,
 /*   850 */   171,  221,   91,  137,   91,   82,  173,   84,  307,  342,
 /*   860 */   180,  175,  135,  133,   98,  176,  378,   27,  131,  129,
 /*   870 */   181,  186,   91,  182,  194,   86,   24,  189,  101,  192,
 /*   880 */   187,   73,   77,   79,   75,   81,   83,   85,   61,   63,
 /*   890 */    65,   67,   69,   71,   60,   59,   35,   31,  121,  380,
 /*   900 */   193,  198,  195,  381,  405,   99,   40,   41,   42,   43,
 /*   910 */    44,   45,   46,   47,  107,  109,  408,   28,   27,  413,
 /*   920 */   197,  203,   27,   91,   27,  207,   97,   91,  137,   91,
 /*   930 */    97,  382,   88,  202,  206,  210,  211,  135,  133,   98,
 /*   940 */   215,   27,   27,  131,  129,  216,   91,   91,  217,   90,
 /*   950 */   123,   24,  383,  101,  408,  224,  143,   93,   94,  108,
 /*   960 */   139,   93,   94,  108,   27,  384,   27,  385,  228,   91,
 /*   970 */   223,   91,  125,  121,  127,  227,  233,  234,  241,  242,
 /*   980 */    99,   40,   41,   42,   43,   44,   45,   46,   47,  107,
 /*   990 */    28,  413,  244,  245,  247,   27,  248,   27,  253,  251,
 /*  1000 */    91,  137,   91,  130,  256,   97,  254,   28,  258,  259,
 /*  1010 */   135,  133,   98,  261,   27,  262,  131,  129,  137,   91,
 /*  1020 */   265,  271,  132,  272,   24,  270,  101,  135,  133,   98,
 /*  1030 */   278,  277,  279,  131,  129,  150,   93,   94,  108,   27,
 /*  1040 */    27,   24,  354,  101,   91,   91,  121,  134,  136,  356,
 /*  1050 */   301,  289,  295,   99,   40,   41,   42,   43,   44,   45,
 /*  1060 */    46,   47,  107,  121,  291,  297,  302,  304,  303,   28,
 /*  1070 */    99,   40,   41,   42,   43,   44,   45,   46,   47,  107,
 /*  1080 */   137,  308,  413,  310,  312,  311,   28,  304,  423,  135,
 /*  1090 */   133,   98,  304,   27,  304,  131,  129,  137,   91,  304,
 /*  1100 */   304,  138,  304,   24,  304,  101,  135,  133,  304,   27,
 /*  1110 */   304,  304,  131,  129,   91,  304,   27,  153,  304,  304,
 /*  1120 */    24,   91,  101,  418,  185,  121,  304,  304,  304,  304,
 /*  1130 */   304,  304,   99,   40,   41,   42,   43,   44,   45,   46,
 /*  1140 */    47,  107,  121,  304,  304,  304,  304,  304,  304,  304,
 /*  1150 */    40,   41,   42,   43,   44,   45,   46,   47,  107,   28,
 /*  1160 */    27,  423,  304,  304,   27,   91,   27,  304,  201,   91,
 /*  1170 */   137,   91,  205,  304,  212,   18,   28,  304,  304,  135,
 /*  1180 */   133,  304,  304,   27,  304,  131,  129,  137,   91,  304,
 /*  1190 */   304,  214,  304,   24,  255,  101,  135,  133,  304,   27,
 /*  1200 */   304,  304,  131,  129,   91,  304,   27,  226,  304,  304,
 /*  1210 */    24,   91,  101,   27,  232,  121,  304,  304,   91,  304,
 /*  1220 */   304,  238,  304,   40,   41,   42,   43,   44,   45,   46,
 /*  1230 */    47,  107,  121,  418,  304,  304,  304,  346,   28,  304,
 /*  1240 */    40,   41,   42,   43,   44,   45,   46,   47,  107,  137,
 /*  1250 */   304,  304,  304,  304,  304,   28,  304,  304,  135,  133,
 /*  1260 */   304,  304,   27,  304,  131,  129,  137,   91,  304,  304,
 /*  1270 */   240,  304,   24,  304,  101,  135,  133,  304,   27,  304,
 /*  1280 */   304,  131,  129,   91,  304,   27,  273,  304,  304,   24,
 /*  1290 */    91,  101,  304,  280,  121,  304,  304,  304,  304,  304,
 /*  1300 */   304,  304,   40,   41,   42,   43,   44,   45,   46,   47,
 /*  1310 */   107,  121,  304,  304,  304,  304,  304,   28,  304,   40,
 /*  1320 */    41,   42,   43,   44,   45,   46,   47,  107,  137,  304,
 /*  1330 */   304,  304,  304,  304,  304,  304,  304,  135,  133,  304,
 /*  1340 */   304,  304,  304,  131,  129,  304,  304,  304,  304,  304,
 /*  1350 */   304,   24,  304,  235,  304,  304,  304,  304,  304,  304,
 /*  1360 */   304,  304,  304,  304,  304,  304,  304,  304,  304,  304,
 /*  1370 */   304,  304,  304,  121,  304,  304,  304,  304,  304,  304,
 /*  1380 */   304,   40,   41,   42,   43,   44,   45,   46,   47,  107,
};
static YYCODETYPE yy_lookahead[] = {
 /*     0 */     4,    5,   25,   26,   27,   28,   29,   30,   31,   32,
 /*    10 */    33,   34,   16,   27,   28,   29,   30,   31,   32,   33,
 /*    20 */    34,   25,   26,   82,   83,   43,   85,   31,   32,   47,
 /*    30 */    48,   52,   52,   89,   39,   39,   41,   41,   94,   59,
 /*    40 */    60,   97,   63,   64,   65,   66,   50,   51,   52,   53,
 /*    50 */    54,   89,   56,   57,   58,    8,   94,   61,   62,   97,
 /*    60 */   102,   41,    4,    5,  106,   69,   70,   71,   72,   73,
 /*    70 */    74,   75,   76,   77,   16,  131,  132,  133,   30,   31,
 /*    80 */    32,   33,   34,   25,   26,   98,   99,   89,   41,   31,
 /*    90 */    32,  104,   92,  131,  132,  133,   89,   39,  100,   41,
 /*   100 */     0,   94,    7,   84,   97,    4,  106,    5,   50,   51,
 /*   110 */    52,   53,   54,    4,   56,   57,   58,   98,   99,   61,
 /*   120 */    62,   45,   46,  104,    4,    5,    5,   69,   70,   71,
 /*   130 */    72,   73,   74,   75,   76,   77,   16,   42,  131,  132,
 /*   140 */   133,   40,    5,   43,   42,   25,   26,   47,   48,   89,
 /*   150 */    49,   31,   32,   44,   94,   27,   35,   97,   89,   39,
 /*   160 */    89,   41,   41,   94,   39,   94,   97,   39,   97,    5,
 /*   170 */    50,   51,   52,   53,   54,   89,   56,   57,   58,   42,
 /*   180 */    94,   61,   62,   97,  109,  110,    4,    5,   27,   69,
 /*   190 */    70,   71,   72,   73,   74,   75,   76,   77,   16,  128,
 /*   200 */    39,  130,  133,   42,   89,   68,   78,   25,   26,   94,
 /*   210 */   106,    4,   97,   31,   32,   92,  112,  113,    7,   39,
 /*   220 */    89,   39,   89,   41,    4,   94,    5,   94,   97,  106,
 /*   230 */    97,    5,   50,   51,   52,   53,   54,  106,   56,   57,
 /*   240 */    58,  107,   89,   61,   62,  111,   39,   94,    4,    5,
 /*   250 */    97,   69,   70,   71,   72,   73,   74,   75,   76,   77,
 /*   260 */    16,  128,   41,  130,  101,   89,   89,   41,   92,   25,
 /*   270 */    26,   94,   89,   89,   97,   31,   32,   94,   94,   89,
 /*   280 */    97,   97,  106,   39,   94,   41,  119,   97,    4,   78,
 /*   290 */    33,   34,  125,  106,   50,   51,   52,   53,   54,   89,
 /*   300 */    56,   57,   58,   89,   94,   61,   62,   97,   94,  105,
 /*   310 */     4,   97,  108,   69,   70,   71,   72,   73,   74,   75,
 /*   320 */    76,   77,    6,   39,    8,    9,   10,   11,   12,   13,
 /*   330 */    14,   15,    4,  103,   18,   19,   20,   21,   22,   23,
 /*   340 */    24,   25,   26,   27,   28,   29,   30,   31,   32,   33,
 /*   350 */    34,    4,    5,   89,    5,   95,   96,   27,   94,   89,
 /*   360 */    89,   97,    4,   16,   94,   94,   89,   97,   97,   39,
 /*   370 */    92,   94,   25,   26,   97,   89,   39,   89,   31,   32,
 /*   380 */    94,   39,   94,   97,  106,   97,   39,   27,   41,  122,
 /*   390 */    41,   63,  128,  126,  130,   37,   80,   50,   51,   39,
 /*   400 */    53,   54,   39,   56,   57,   58,   89,   89,   61,   62,
 /*   410 */    89,   94,   94,   92,   97,   97,   69,   70,   71,   72,
 /*   420 */    73,   74,   75,   76,   77,    4,  134,  106,   89,    8,
 /*   430 */     9,   10,   11,   12,   13,   14,   15,  114,  115,   18,
 /*   440 */    19,   20,   21,   22,   23,   24,   25,   26,   27,   28,
 /*   450 */    29,   30,   31,   32,   33,   34,    7,    8,    9,   10,
 /*   460 */    11,   12,   13,   14,   15,   86,   41,   18,   19,   20,
 /*   470 */    21,   22,   23,   24,   25,   26,   27,   28,   29,   30,
 /*   480 */    31,   32,   33,   34,   89,  106,    7,    4,   67,   94,
 /*   490 */     7,   42,   97,    4,   95,   96,   39,    8,    9,   10,
 /*   500 */    11,   12,   13,   14,   15,    7,    7,   18,   19,   20,
 /*   510 */    21,   22,   23,   24,   25,   26,   27,   28,   29,   30,
 /*   520 */    31,   32,   33,   34,    7,    8,    9,   10,   11,   12,
 /*   530 */    13,   14,   15,    7,    7,   18,   19,   20,   21,   22,
 /*   540 */    23,   24,   25,   26,   27,   28,   29,   30,   31,   32,
 /*   550 */    33,   34,    7,    8,    9,   10,   11,   12,   13,   14,
 /*   560 */    15,    7,   78,   18,   19,   20,   21,   22,   23,   24,
 /*   570 */    25,   26,   27,   28,   29,   30,   31,   32,   33,   34,
 /*   580 */     7,    8,    9,   10,   11,   12,   13,   14,   15,   78,
 /*   590 */    78,   18,   19,   20,   21,   22,   23,   24,   25,   26,
 /*   600 */    27,   28,   29,   30,   31,   32,   33,   34,    8,    9,
 /*   610 */    10,   11,   12,   13,   14,   15,    7,    7,   18,   19,
 /*   620 */    20,   21,   22,   23,   24,   25,   26,   27,   28,   29,
 /*   630 */    30,   31,   32,   33,   34,    5,    5,    4,    4,    4,
 /*   640 */     7,    7,   42,    8,    9,   10,   11,   12,   13,   14,
 /*   650 */    15,   42,   22,   18,   19,   20,   21,   22,   23,   24,
 /*   660 */    25,   26,   27,   28,   29,   30,   31,   32,   33,   34,
 /*   670 */     4,   79,   41,    5,    8,    9,   10,   11,   12,   13,
 /*   680 */    14,   15,   41,   79,   18,   19,   20,   21,   22,   23,
 /*   690 */    24,   25,   26,   27,   28,   29,   30,   31,   32,   33,
 /*   700 */    34,    8,    9,   10,   11,   12,   13,   14,   15,   41,
 /*   710 */     6,   18,   19,   20,   21,   22,   23,   24,   25,   26,
 /*   720 */    27,   28,   29,   30,   31,   32,   33,   34,   15,   42,
 /*   730 */    42,   18,   19,   20,   21,   22,   23,   24,   25,   26,
 /*   740 */    27,   28,   29,   30,   31,   32,   33,   34,   55,   88,
 /*   750 */     4,   92,   80,    4,   93,    8,   42,    8,    9,   10,
 /*   760 */    11,   12,   13,   14,   15,  106,   89,   18,   19,   20,
 /*   770 */    21,   22,   23,   24,   25,   26,   27,   28,   29,   30,
 /*   780 */    31,   32,   33,   34,    4,   39,  134,   39,    8,    9,
 /*   790 */    10,   11,   12,   13,   14,   15,   89,  134,   18,   19,
 /*   800 */    20,   21,   22,   23,   24,   25,   26,   27,   28,   29,
 /*   810 */    30,   31,   32,   33,   34,    8,    9,   10,   11,   12,
 /*   820 */    13,   14,   15,   39,   34,   18,   19,   20,   21,   22,
 /*   830 */    23,   24,   25,   26,   27,   28,   29,   30,   31,   32,
 /*   840 */    33,   34,    5,   89,    7,   89,    5,   89,   94,   89,
 /*   850 */    89,   97,   94,   16,   94,   97,   41,   97,   17,    4,
 /*   860 */   106,   42,   25,   26,   27,  106,    4,   89,   31,   32,
 /*   870 */   116,  117,   94,  106,  120,   97,   39,   52,   41,  106,
 /*   880 */   118,   18,   19,   20,   21,   22,   23,   24,   25,   26,
 /*   890 */    27,   28,   29,   30,   31,   32,   33,   34,   61,    4,
 /*   900 */   112,   52,  121,    4,    4,   68,   69,   70,   71,   72,
 /*   910 */    73,   74,   75,   76,   77,   78,   79,    5,   89,    7,
 /*   920 */   123,  112,   89,   94,   89,  112,   97,   94,   16,   94,
 /*   930 */    97,    4,   97,  106,  106,   39,    8,   25,   26,   27,
 /*   940 */   124,   89,   89,   31,   32,  106,   94,   94,  112,   97,
 /*   950 */    97,   39,    4,   41,   42,  112,  127,  128,  129,  130,
 /*   960 */   127,  128,  129,  130,   89,    4,   89,    4,  112,   94,
 /*   970 */   106,   94,   97,   61,   97,  106,  106,  112,  106,  112,
 /*   980 */    68,   69,   70,   71,   72,   73,   74,   75,   76,   77,
 /*   990 */     5,    6,  106,  112,  106,   89,  112,   89,  106,  112,
 /*  1000 */    94,   16,   94,   97,   89,   97,  112,    5,  106,  112,
 /*  1010 */    25,   26,   27,  106,   89,  112,   31,   32,   16,   94,
 /*  1020 */   106,   39,   97,    8,   39,   96,   41,   25,   26,   27,
 /*  1030 */    39,  115,    8,   31,   32,  127,  128,  129,  130,   89,
 /*  1040 */    89,   39,   42,   41,   94,   94,   61,   97,   97,   42,
 /*  1050 */    38,   89,   87,   68,   69,   70,   71,   72,   73,   74,
 /*  1060 */    75,   76,   77,   61,   89,   40,   89,   91,   90,    5,
 /*  1070 */    68,   69,   70,   71,   72,   73,   74,   75,   76,   77,
 /*  1080 */    16,   39,   80,   89,   91,   90,    5,  135,    7,   25,
 /*  1090 */    26,   27,  135,   89,  135,   31,   32,   16,   94,  135,
 /*  1100 */   135,   97,  135,   39,  135,   41,   25,   26,  135,   89,
 /*  1110 */   135,  135,   31,   32,   94,  135,   89,   97,  135,  135,
 /*  1120 */    39,   94,   41,   42,   97,   61,  135,  135,  135,  135,
 /*  1130 */   135,  135,   68,   69,   70,   71,   72,   73,   74,   75,
 /*  1140 */    76,   77,   61,  135,  135,  135,  135,  135,  135,  135,
 /*  1150 */    69,   70,   71,   72,   73,   74,   75,   76,   77,    5,
 /*  1160 */    89,    7,  135,  135,   89,   94,   89,  135,   97,   94,
 /*  1170 */    16,   94,   97,  135,   97,    4,    5,  135,  135,   25,
 /*  1180 */    26,  135,  135,   89,  135,   31,   32,   16,   94,  135,
 /*  1190 */   135,   97,  135,   39,   23,   41,   25,   26,  135,   89,
 /*  1200 */   135,  135,   31,   32,   94,  135,   89,   97,  135,  135,
 /*  1210 */    39,   94,   41,   89,   97,   61,  135,  135,   94,  135,
 /*  1220 */   135,   97,  135,   69,   70,   71,   72,   73,   74,   75,
 /*  1230 */    76,   77,   61,   79,  135,  135,  135,    4,    5,  135,
 /*  1240 */    69,   70,   71,   72,   73,   74,   75,   76,   77,   16,
 /*  1250 */   135,  135,  135,  135,  135,    5,  135,  135,   25,   26,
 /*  1260 */   135,  135,   89,  135,   31,   32,   16,   94,  135,  135,
 /*  1270 */    97,  135,   39,  135,   41,   25,   26,  135,   89,  135,
 /*  1280 */   135,   31,   32,   94,  135,   89,   97,  135,  135,   39,
 /*  1290 */    94,   41,  135,   97,   61,  135,  135,  135,  135,  135,
 /*  1300 */   135,  135,   69,   70,   71,   72,   73,   74,   75,   76,
 /*  1310 */    77,   61,  135,  135,  135,  135,  135,    5,  135,   69,
 /*  1320 */    70,   71,   72,   73,   74,   75,   76,   77,   16,  135,
 /*  1330 */   135,  135,  135,  135,  135,  135,  135,   25,   26,  135,
 /*  1340 */   135,  135,  135,   31,   32,  135,  135,  135,  135,  135,
 /*  1350 */   135,   39,  135,   41,  135,  135,  135,  135,  135,  135,
 /*  1360 */   135,  135,  135,  135,  135,  135,  135,  135,  135,  135,
 /*  1370 */   135,  135,  135,   61,  135,  135,  135,  135,  135,  135,
 /*  1380 */   135,   69,   70,   71,   72,   73,   74,   75,   76,   77,
};
#define YY_SHIFT_USE_DFLT (-24)
static short yy_shift_ofst[] = {
 /*     0 */   -24,  -18,  100,  -24,   20,  125,  -24,  164,  180,  -24,
 /*    10 */    95,  109,  220,  220,   76,  220,  220,  -24,  -24,  -24,
 /*    20 */   337,  306,  342, 1233,  121,  363,  -24,  221,  125,  226,
 /*    30 */   489,   -5,   47, 1250,  807,  985,  -24,  316,  -24, 1250,
 /*    40 */   -24,  -24,  -24,  -24,  -24,  -24,  -24,  -24,  807, 1250,
 /*    50 */   807, 1250,  807, 1250,  807, 1250,  807, 1250,  807,  -24,
 /*    60 */   -24, 1250,  -14, 1250,  -14, 1250,   48, 1250,   48, 1250,
 /*    70 */    48, 1250,   48, 1250,  -23, 1250,  -23, 1250,  -23, 1250,
 /*    80 */   -23, 1250,  -23, 1250,  -23, 1250,  -23, 1250,  713, 1250,
 /*    90 */   863,  425,  912,  479,  498, 1064,  499,  807,  -24,  457,
 /*   100 */   -24, 1081,  517,  526, 1250,  527,  807,  837,  554,  128,
 /*   110 */   211,  330,  484,  -24,  511,  -24,  512, 1154,  610,  592,
 /*   120 */   -24,  641, 1250,  545, 1250,  573, 1250,  600,  -24, 1250,
 /*   130 */   257, 1250,  257, 1250,  257, 1250,  257, 1250,  863,  604,
 /*   140 */   -24,  687,  -24,  688,  -24,  704, 1002,  672,  -24,  912,
 /*   150 */   714,  747, 1250,  807,  -24,  125,  137,  748,   47,  -24,
 /*   160 */   125,  102,  784,   47,  -24,  790,  207,  855,  125,  164,
 /*   170 */   125,  349,  815,  161,  819,  220,  -24,  -24,  101,  347,
 /*   180 */   -24,  220,  -24,  862, 1250,  635,  -24,  -20,  825,  895,
 /*   190 */   -24,  284,  -24,  347,  -24,  -21,  849,  899,  900,  -24,
 /*   200 */  1250,  666,  -24,  347, 1250,  666,  -24,   -4,  927,  896,
 /*   210 */   928, 1250,  693, 1250,  421,  220,  -24,   58,  948,  961,
 /*   220 */   963,  749,  220,  -24,  347, 1312,  666,  -24,  347,  220,
 /*   230 */   328, 1250,  666,  -24,  347, 1081,  449, 1250,  780, 1250,
 /*   240 */   666,  -24,  347,  220,  -24,  120,  220,  -24,  182, 1171,
 /*   250 */   -24,  347,  666,  -24,  347,  125,  630,  220,  -24,  347,
 /*   260 */   220,  -24,  244,  -24,  220,  -24,  982,  -24,  483,  982,
 /*   270 */   -24, 1015, 1250,  807,  991,  633,  991,  -24, 1024, 1250,
 /*   280 */   807,  -24, 1000,  609,  360, 1007,  -24,  -24,  125,  631,
 /*   290 */   125,  668,  -24,  358,  -24, 1012, 1025,  982,  634,  220,
 /*   300 */   -24,  125,  841,  -24,  746,  220,  164, 1042,  -24,  125,
 /*   310 */   841,  -24,  746,  220,  -24,
};
#define YY_REDUCE_USE_DFLT (-60)
static short yy_reduce_ofst[] = {
 /*     0 */   -59,   19,  -13,  -60,  -60,   -2,  -60,  -60,  -60,  -60,
 /*    10 */   -60,  163,    0,  -42,  230,  123,  187,  -60,  -60,  -60,
 /*    20 */   -60,  -60,  -60,   60,  -60,  -60,  -60,  -60,  339,  -60,
 /*    30 */   -60,  -60,  292,   86,  -60,   71,  -60,  -60,  -60,  115,
 /*    40 */   -60,  -60,  -60,  -60,  -60,  -60,  -60,  -60,  -60,  153,
 /*    50 */   -60,  177,  -60,  183,  -60,  184,  -60,  190,  -60,  -60,
 /*    60 */   -60,  210,  -60,  214,  -60,  270,  -60,  271,  -60,  277,
 /*    70 */   -60,  286,  -60,  288,  -60,  317,  -60,  318,  -60,  395,
 /*    80 */   -60,  758,  -60,  760,  -60,  778,  -60,  835,  -60,  852,
 /*    90 */   -60,  -60,  829,  -60,  -60,  133,  -60,  -60,  -60,  -60,
 /*   100 */   -60,  -56,  -60,  -60,   69,  -60,  -60,  833,  -60,   75,
 /*   110 */   -60,  -60,  -60,  -60,  -60,  -60,  -60,  -38,  -60,  -60,
 /*   120 */   -60,  -60,  853,  -60,  875,  -60,  877,  -60,  -60,  906,
 /*   130 */   -60,  925,  -60,  950,  -60,  951,  -60, 1004,  -60,  -60,
 /*   140 */   -60,  -60,  -60,  -60,  -60,  -60,  264,  -60,  -60,  908,
 /*   150 */   -60,  -60, 1020,  -60,  -60,  677,  -60,  -60,  652,  -60,
 /*   160 */   707,  -60,  -60,  663,  -60,  -60,  -60,  -60,  756,  -60,
 /*   170 */   761,  -60,  -60,  204,  -60,  759,  134,  -60,  104,  754,
 /*   180 */   -60,  767,  -60,  -60, 1027,  -60,  762,  167,  -60,  -60,
 /*   190 */   -60,  773,  788,  754,  781,  267,  797,  -60,  -60,  -60,
 /*   200 */  1071,  827,  809,  754, 1075,  828,  813,  754,  -60,  -60,
 /*   210 */   -60, 1077,  -60, 1094,  816,  839,  836,  754,  -60,  -60,
 /*   220 */   -60,  -60,  864,  843,  754, 1110,  869,  856,  754,  278,
 /*   230 */   187, 1117,  870,  865,  754,    7,  -60, 1124,  -60, 1173,
 /*   240 */   872,  867,  754,  886,  881,  754,  888,  884,  754,  131,
 /*   250 */   887,  754,  892,  894,  754,  915,  -60,  902,  897,  754,
 /*   260 */   907,  903,  754,  -60,  914,  -60,  260,  -60,  -60,  929,
 /*   270 */   -60,  -60, 1189,  -60,  323,  -60,  916,  -60,  -60, 1196,
 /*   280 */   -60,  -60,  -60,  -60,  -60,  -60,  -60,  -60,  962,  -60,
 /*   290 */   975,  -60,  -60,  379,  965,  661,  -60,  399,  659,  187,
 /*   300 */   -60,  977,  978,  976,  176,  187,  -60,  -60,  -60,  994,
 /*   310 */   995,  993,  321,  187,  -60,
};
static YYACTIONTYPE yy_default[] = {
 /*     0 */   431,  482,  482,  337,  482,  482,  324,  348,  482,  325,
 /*    10 */   482,  482,  482,  343,  338,  482,  344,  430,  433,  429,
 /*    20 */   482,  482,  482,  482,  442,  482,  443,  482,  482,  482,
 /*    30 */   482,  482,  425,  482,  426,  482,  414,  482,  452,  482,
 /*    40 */   434,  435,  436,  437,  438,  439,  440,  441,  454,  482,
 /*    50 */   455,  482,  456,  482,  457,  482,  458,  482,  459,  462,
 /*    60 */   463,  482,  464,  482,  465,  482,  466,  482,  467,  482,
 /*    70 */   468,  482,  469,  482,  472,  482,  473,  482,  474,  482,
 /*    80 */   475,  482,  476,  482,  477,  482,  478,  482,  479,  482,
 /*    90 */   480,  482,  482,  409,  482,  413,  410,  415,  416,  482,
 /*   100 */   417,  482,  419,  482,  423,  420,  424,  482,  482,  482,
 /*   110 */   482,  482,  482,  364,  482,  363,  482,  482,  482,  482,
 /*   120 */   449,  482,  482,  482,  482,  482,  482,  482,  450,  482,
 /*   130 */   460,  482,  461,  482,  470,  482,  471,  482,  481,  482,
 /*   140 */   451,  482,  448,  482,  447,  482,  482,  482,  453,  482,
 /*   150 */   482,  427,  482,  428,  444,  482,  482,  482,  425,  445,
 /*   160 */   482,  482,  482,  425,  446,  482,  482,  482,  482,  349,
 /*   170 */   482,  482,  482,  482,  482,  482,  366,  350,  375,  365,
 /*   180 */   376,  482,  377,  482,  482,  482,  388,  482,  482,  482,
 /*   190 */   389,  482,  375,  390,  398,  482,  482,  482,  482,  399,
 /*   200 */   482,  482,  375,  400,  482,  482,  375,  482,  482,  482,
 /*   210 */   482,  482,  482,  482,  482,  482,  375,  482,  482,  482,
 /*   220 */   482,  482,  482,  375,  387,  482,  482,  375,  396,  482,
 /*   230 */   482,  482,  482,  375,  397,  482,  482,  482,  482,  482,
 /*   240 */   482,  375,  401,  482,  375,  482,  482,  375,  482,  482,
 /*   250 */   375,  391,  482,  375,  392,  482,  482,  482,  375,  393,
 /*   260 */   482,  375,  482,  367,  482,  368,  482,  332,  482,  482,
 /*   270 */   333,  334,  482,  335,  482,  482,  482,  372,  373,  482,
 /*   280 */   374,  371,  482,  482,  482,  482,  358,  357,  482,  482,
 /*   290 */   482,  482,  336,  317,  319,  330,  316,  482,  482,  331,
 /*   300 */   320,  482,  322,  326,  482,  321,  327,  482,  323,  482,
 /*   310 */   322,  326,  482,  318,  432,
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
  ParseARG_SDECL                /* A place to hold %extra_argument */
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
void ParseTrace(FILE *TraceFILE, const char *zTracePrompt){
  yyTraceFILE = TraceFILE;
  yyTracePrompt = zTracePrompt;
  if( yyTraceFILE==0 ) yyTracePrompt = 0;
  else if( yyTracePrompt==0 ) yyTraceFILE = 0;
}
void ParseTrace(FILE *TraceFILE, char *zTracePrompt){
  ParseTrace(TraceFILE, (const char*) zTracePrompt);
}
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static const char *yyTokenName[] = { 
  "$",             "LOWPRECEDENCE",  "UNEXPECTEDCHAR",  "INVALIDENCODING",
  "NL",            "DOT",           "DOTDOT",        "COMMA",       
  "ASSIGN",        "ADDASS",        "SUBASS",        "MULASS",      
  "DIVASS",        "MODASS",        "OR",            "AND",         
  "NOT",           "EQ",            "EQEQ",          "GTEQ",        
  "LTEQ",          "EXEQ",          "GT",            "LT",          
  "DOLLAR",        "PLUS",          "MINUS",         "STAR",        
  "SLASH",         "MODULO",        "DBSTAR",        "DBPLUS",      
  "DBMINUS",       "LBRACKET",      "COLON",         "ARROW",       
  "HIGHPRECEDENCE",  "NAMESPACE",     "USING",         "SYMBOL",      
  "STATIC",        "LPAR",          "RPAR",          "CLASS",       
  "NEW",           "ATTRIB",        "METHOD",        "FUNCTION",    
  "STFUNCTION",    "LOCAL",         "QUIT",          "RETURN",      
  "END",           "WHILE",         "FOR",           "TO",          
  "LOOP",          "EXIT",          "BEGSEQ",        "RECOVER",     
  "FINALLY",       "IF",            "DOCASE",        "CASE",        
  "ELSEIF",        "ELSE",          "OTHERWISE",     "STEP",        
  "AT",            "NUMBER",        "STRING",        "NLSTEXT",     
  "BINARYX",       "BINARYA",       "TRUE",          "FALSE",       
  "NIL",           "LBRACE",        "PIPE",          "RBRACE",      
  "RBRACKET",      "error",         "prg",           "header",      
  "lfunction",     "lnewline0",     "namespace",     "lusing",      
  "lstatdefin",    "dotsymbol",     "nsalias",       "ldotsymbol",  
  "lnewline",      "using",         "ddotsymbol",    "statdefin",   
  "statdef",       "expr",          "function",      "classid",     
  "ldsym",         "newspec",       "lslot",         "slot",        
  "funcid",        "argument",      "newline",       "body",        
  "larg",          "bargument",     "lbarg",         "llocdefin",   
  "lstatement",    "locdline",      "locdefin",      "locdef",      
  "statement",     "begseq",        "lrecov",        "finally",     
  "if",            "lelseif",       "else",          "endif",       
  "forstep",       "recov",         "elseif",        "lfuncpar",    
  "parexpr",       "lfuncpar0",     "parexpr0",      "lexpr",       
  "lexpr0",        "expr0",         "msgpar",      
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *yyRuleName[] = {
 /*   0 */ "prg ::= header lfunction",
 /*   1 */ "header ::= lnewline0 namespace lusing lstatdefin",
 /*   2 */ "namespace ::=",
 /*   3 */ "namespace ::= NAMESPACE dotsymbol nsalias ldotsymbol lnewline",
 /*   4 */ "lusing ::=",
 /*   5 */ "lusing ::= lusing using",
 /*   6 */ "using ::= USING dotsymbol nsalias ldotsymbol lnewline",
 /*   7 */ "nsalias ::=",
 /*   8 */ "nsalias ::= EQ SYMBOL",
 /*   9 */ "dotsymbol ::= SYMBOL",
 /*  10 */ "dotsymbol ::= dotsymbol DOT SYMBOL",
 /*  11 */ "ldotsymbol ::=",
 /*  12 */ "ldotsymbol ::= ldotsymbol dotsymbol",
 /*  13 */ "ddotsymbol ::= dotsymbol",
 /*  14 */ "ddotsymbol ::= DOT dotsymbol",
 /*  15 */ "lstatdefin ::=",
 /*  16 */ "lstatdefin ::= lstatdefin STATIC statdefin lnewline",
 /*  17 */ "statdefin ::= statdef",
 /*  18 */ "statdefin ::= statdefin COMMA statdef",
 /*  19 */ "statdef ::= SYMBOL",
 /*  20 */ "statdef ::= SYMBOL ASSIGN expr",
 /*  21 */ "lfunction ::= function",
 /*  22 */ "lfunction ::= lfunction function",
 /*  23 */ "function ::= classid LPAR ldsym RPAR newspec lnewline lslot",
 /*  24 */ "classid ::= CLASS dotsymbol",
 /*  25 */ "newspec ::=",
 /*  26 */ "newspec ::= NEW COLON",
 /*  27 */ "newspec ::= NEW COLON SYMBOL",
 /*  28 */ "lslot ::=",
 /*  29 */ "lslot ::= lslot slot lnewline",
 /*  30 */ "slot ::= ATTRIB SYMBOL",
 /*  31 */ "slot ::= METHOD SYMBOL",
 /*  32 */ "slot ::= METHOD SYMBOL expr",
 /*  33 */ "ldsym ::= dotsymbol",
 /*  34 */ "ldsym ::= ldsym COMMA dotsymbol",
 /*  35 */ "function ::= funcid LPAR argument RPAR newline body",
 /*  36 */ "funcid ::= FUNCTION dotsymbol",
 /*  37 */ "funcid ::= STFUNCTION dotsymbol",
 /*  38 */ "argument ::=",
 /*  39 */ "argument ::= STAR",
 /*  40 */ "argument ::= larg",
 /*  41 */ "argument ::= larg COMMA STAR",
 /*  42 */ "larg ::= SYMBOL",
 /*  43 */ "larg ::= larg COMMA SYMBOL",
 /*  44 */ "bargument ::=",
 /*  45 */ "bargument ::= lbarg",
 /*  46 */ "bargument ::= STAR",
 /*  47 */ "bargument ::= lbarg COMMA STAR",
 /*  48 */ "lbarg ::= SYMBOL",
 /*  49 */ "lbarg ::= lbarg COMMA SYMBOL",
 /*  50 */ "body ::= llocdefin lstatement",
 /*  51 */ "llocdefin ::=",
 /*  52 */ "llocdefin ::= llocdefin newline",
 /*  53 */ "llocdefin ::= llocdefin locdline newline",
 /*  54 */ "locdline ::= STATIC statdefin",
 /*  55 */ "locdline ::= LOCAL locdefin",
 /*  56 */ "locdefin ::= locdef",
 /*  57 */ "locdefin ::= locdefin COMMA locdef",
 /*  58 */ "locdef ::= SYMBOL",
 /*  59 */ "locdef ::= SYMBOL ASSIGN expr",
 /*  60 */ "lstatement ::=",
 /*  61 */ "lstatement ::= lstatement newline",
 /*  62 */ "lstatement ::= lstatement statement newline",
 /*  63 */ "statement ::= QUIT",
 /*  64 */ "statement ::= RETURN expr",
 /*  65 */ "statement ::= begseq lrecov finally END",
 /*  66 */ "statement ::= if lelseif else endif",
 /*  67 */ "statement ::= WHILE expr newline lstatement END",
 /*  68 */ "statement ::= FOR SYMBOL ASSIGN expr TO expr forstep newline lstatement END",
 /*  69 */ "statement ::= LOOP",
 /*  70 */ "statement ::= EXIT",
 /*  71 */ "statement ::= expr",
 /*  72 */ "begseq ::= BEGSEQ newline lstatement",
 /*  73 */ "lrecov ::=",
 /*  74 */ "lrecov ::= lrecov recov",
 /*  75 */ "recov ::= RECOVER newline lstatement",
 /*  76 */ "recov ::= RECOVER SYMBOL newline lstatement",
 /*  77 */ "recov ::= RECOVER SYMBOL expr newline lstatement",
 /*  78 */ "recov ::= RECOVER SYMBOL LT dotsymbol GT newline lstatement",
 /*  79 */ "finally ::=",
 /*  80 */ "finally ::= FINALLY newline lstatement",
 /*  81 */ "if ::= IF expr newline lstatement",
 /*  82 */ "if ::= DOCASE lnewline CASE expr newline lstatement",
 /*  83 */ "lelseif ::=",
 /*  84 */ "lelseif ::= lelseif elseif",
 /*  85 */ "elseif ::= ELSEIF expr newline lstatement",
 /*  86 */ "elseif ::= CASE expr newline lstatement",
 /*  87 */ "else ::=",
 /*  88 */ "else ::= ELSE newline lstatement",
 /*  89 */ "else ::= OTHERWISE newline lstatement",
 /*  90 */ "endif ::= END",
 /*  91 */ "forstep ::=",
 /*  92 */ "forstep ::= STEP expr",
 /*  93 */ "lfuncpar ::=",
 /*  94 */ "lfuncpar ::= parexpr",
 /*  95 */ "lfuncpar ::= lfuncpar0 COMMA parexpr0",
 /*  96 */ "lfuncpar0 ::= parexpr0",
 /*  97 */ "lfuncpar0 ::= lfuncpar0 COMMA parexpr0",
 /*  98 */ "parexpr0 ::=",
 /*  99 */ "parexpr0 ::= parexpr",
 /* 100 */ "parexpr ::= expr",
 /* 101 */ "parexpr ::= STAR",
 /* 102 */ "parexpr ::= AT SYMBOL",
 /* 103 */ "lexpr ::=",
 /* 104 */ "lexpr ::= expr",
 /* 105 */ "lexpr ::= lexpr0 COMMA expr0",
 /* 106 */ "lexpr0 ::= expr0",
 /* 107 */ "lexpr0 ::= lexpr0 COMMA expr0",
 /* 108 */ "expr0 ::=",
 /* 109 */ "expr0 ::= expr",
 /* 110 */ "msgpar ::=",
 /* 111 */ "msgpar ::= ASSIGN expr",
 /* 112 */ "msgpar ::= LPAR lfuncpar RPAR",
 /* 113 */ "msgpar ::= LPAR lfuncpar RPAR ASSIGN expr",
 /* 114 */ "lnewline ::= newline",
 /* 115 */ "lnewline ::= lnewline newline",
 /* 116 */ "lnewline0 ::=",
 /* 117 */ "lnewline0 ::= lnewline0 newline",
 /* 118 */ "newline ::= NL",
 /* 119 */ "expr ::= NUMBER",
 /* 120 */ "expr ::= STRING",
 /* 121 */ "expr ::= NLSTEXT",
 /* 122 */ "expr ::= BINARYX",
 /* 123 */ "expr ::= BINARYA",
 /* 124 */ "expr ::= TRUE",
 /* 125 */ "expr ::= FALSE",
 /* 126 */ "expr ::= NIL",
 /* 127 */ "expr ::= SYMBOL",
 /* 128 */ "expr ::= SYMBOL ARROW SYMBOL",
 /* 129 */ "expr ::= expr COLON SYMBOL msgpar",
 /* 130 */ "expr ::= expr COLON LPAR dotsymbol RPAR SYMBOL msgpar",
 /* 131 */ "expr ::= expr COLON LPAR dotsymbol AT dotsymbol RPAR SYMBOL msgpar",
 /* 132 */ "expr ::= ddotsymbol LPAR lfuncpar RPAR",
 /* 133 */ "expr ::= LPAR lexpr RPAR",
 /* 134 */ "expr ::= LBRACE PIPE bargument PIPE lexpr RBRACE",
 /* 135 */ "expr ::= IF LPAR expr COMMA expr COMMA expr RPAR",
 /* 136 */ "expr ::= LBRACE lfuncpar RBRACE",
 /* 137 */ "expr ::= expr LBRACKET expr RBRACKET",
 /* 138 */ "expr ::= expr LBRACKET parexpr0 DOTDOT parexpr0 RBRACKET",
 /* 139 */ "expr ::= expr ASSIGN expr",
 /* 140 */ "expr ::= expr ADDASS expr",
 /* 141 */ "expr ::= expr SUBASS expr",
 /* 142 */ "expr ::= expr MULASS expr",
 /* 143 */ "expr ::= expr DIVASS expr",
 /* 144 */ "expr ::= expr MODASS expr",
 /* 145 */ "expr ::= DBMINUS expr",
 /* 146 */ "expr ::= DBPLUS expr",
 /* 147 */ "expr ::= expr DBMINUS",
 /* 148 */ "expr ::= expr DBPLUS",
 /* 149 */ "expr ::= expr PLUS expr",
 /* 150 */ "expr ::= expr MINUS expr",
 /* 151 */ "expr ::= expr STAR expr",
 /* 152 */ "expr ::= expr SLASH expr",
 /* 153 */ "expr ::= expr MODULO expr",
 /* 154 */ "expr ::= expr DBSTAR expr",
 /* 155 */ "expr ::= MINUS expr",
 /* 156 */ "expr ::= PLUS expr",
 /* 157 */ "expr ::= expr EQEQ expr",
 /* 158 */ "expr ::= expr EXEQ expr",
 /* 159 */ "expr ::= expr GTEQ expr",
 /* 160 */ "expr ::= expr LTEQ expr",
 /* 161 */ "expr ::= expr GT expr",
 /* 162 */ "expr ::= expr LT expr",
 /* 163 */ "expr ::= expr DOLLAR expr",
 /* 164 */ "expr ::= expr OR expr",
 /* 165 */ "expr ::= expr AND expr",
 /* 166 */ "expr ::= NOT expr",
};
#endif /* NDEBUG */

/*
** This function returns the symbolic name associated with a token
** value.
*/
const char *ParseTokenName(int tokenType){
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
** to Parse and ParseFree.
*/
void *ParseAlloc(void *(*mallocProc)(size_t)){
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
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
    case 27:
    case 28:
    case 29:
    case 30:
    case 31:
    case 32:
    case 33:
    case 34:
    case 35:
    case 36:
    case 37:
    case 38:
    case 39:
    case 40:
    case 41:
    case 42:
    case 43:
    case 44:
    case 45:
    case 46:
    case 47:
    case 48:
    case 49:
    case 50:
    case 51:
    case 52:
    case 53:
    case 54:
    case 55:
    case 56:
    case 57:
    case 58:
    case 59:
    case 60:
    case 61:
    case 62:
    case 63:
    case 64:
    case 65:
    case 66:
    case 67:
    case 68:
    case 69:
    case 70:
    case 71:
    case 72:
    case 73:
    case 74:
    case 75:
    case 76:
    case 77:
    case 78:
    case 79:
    case 80:
#line 218 "./parser.lem"
{delete (yypminor->yy0);}
#line 1102 "./parser.c"
      break;
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
**       obtained from ParseAlloc.
** <li>  A pointer to a function used to reclaim memory obtained
**       from malloc.
** </ul>
*/
void ParseFree(
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
     ParseARG_FETCH;
     yypParser->yyidx--;
#ifndef NDEBUG
     if( yyTraceFILE ){
       fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
     }
#endif
     while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
     /* Here code is inserted which will execute if the parser
     ** stack every overflows */
     ParseARG_STORE; /* Suppress warning about unused %extra_argument var */
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
  { 82, 2 },
  { 83, 4 },
  { 86, 0 },
  { 86, 5 },
  { 87, 0 },
  { 87, 2 },
  { 93, 5 },
  { 90, 0 },
  { 90, 2 },
  { 89, 1 },
  { 89, 3 },
  { 91, 0 },
  { 91, 2 },
  { 94, 1 },
  { 94, 2 },
  { 88, 0 },
  { 88, 4 },
  { 95, 1 },
  { 95, 3 },
  { 96, 1 },
  { 96, 3 },
  { 84, 1 },
  { 84, 2 },
  { 98, 7 },
  { 99, 2 },
  { 101, 0 },
  { 101, 2 },
  { 101, 3 },
  { 102, 0 },
  { 102, 3 },
  { 103, 2 },
  { 103, 2 },
  { 103, 3 },
  { 100, 1 },
  { 100, 3 },
  { 98, 6 },
  { 104, 2 },
  { 104, 2 },
  { 105, 0 },
  { 105, 1 },
  { 105, 1 },
  { 105, 3 },
  { 108, 1 },
  { 108, 3 },
  { 109, 0 },
  { 109, 1 },
  { 109, 1 },
  { 109, 3 },
  { 110, 1 },
  { 110, 3 },
  { 107, 2 },
  { 111, 0 },
  { 111, 2 },
  { 111, 3 },
  { 113, 2 },
  { 113, 2 },
  { 114, 1 },
  { 114, 3 },
  { 115, 1 },
  { 115, 3 },
  { 112, 0 },
  { 112, 2 },
  { 112, 3 },
  { 116, 1 },
  { 116, 2 },
  { 116, 4 },
  { 116, 4 },
  { 116, 5 },
  { 116, 10 },
  { 116, 1 },
  { 116, 1 },
  { 116, 1 },
  { 117, 3 },
  { 118, 0 },
  { 118, 2 },
  { 125, 3 },
  { 125, 4 },
  { 125, 5 },
  { 125, 7 },
  { 119, 0 },
  { 119, 3 },
  { 120, 4 },
  { 120, 6 },
  { 121, 0 },
  { 121, 2 },
  { 126, 4 },
  { 126, 4 },
  { 122, 0 },
  { 122, 3 },
  { 122, 3 },
  { 123, 1 },
  { 124, 0 },
  { 124, 2 },
  { 127, 0 },
  { 127, 1 },
  { 127, 3 },
  { 129, 1 },
  { 129, 3 },
  { 130, 0 },
  { 130, 1 },
  { 128, 1 },
  { 128, 1 },
  { 128, 2 },
  { 131, 0 },
  { 131, 1 },
  { 131, 3 },
  { 132, 1 },
  { 132, 3 },
  { 133, 0 },
  { 133, 1 },
  { 134, 0 },
  { 134, 2 },
  { 134, 3 },
  { 134, 5 },
  { 92, 1 },
  { 92, 2 },
  { 85, 0 },
  { 85, 2 },
  { 106, 1 },
  { 97, 1 },
  { 97, 1 },
  { 97, 1 },
  { 97, 1 },
  { 97, 1 },
  { 97, 1 },
  { 97, 1 },
  { 97, 1 },
  { 97, 1 },
  { 97, 3 },
  { 97, 4 },
  { 97, 7 },
  { 97, 9 },
  { 97, 4 },
  { 97, 3 },
  { 97, 6 },
  { 97, 8 },
  { 97, 3 },
  { 97, 4 },
  { 97, 6 },
  { 97, 3 },
  { 97, 3 },
  { 97, 3 },
  { 97, 3 },
  { 97, 3 },
  { 97, 3 },
  { 97, 2 },
  { 97, 2 },
  { 97, 2 },
  { 97, 2 },
  { 97, 3 },
  { 97, 3 },
  { 97, 3 },
  { 97, 3 },
  { 97, 3 },
  { 97, 3 },
  { 97, 2 },
  { 97, 2 },
  { 97, 3 },
  { 97, 3 },
  { 97, 3 },
  { 97, 3 },
  { 97, 3 },
  { 97, 3 },
  { 97, 3 },
  { 97, 3 },
  { 97, 3 },
  { 97, 2 },
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
  ParseARG_FETCH;
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
#line 245 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-1].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="prg ::= header lfunction.";
    yygotominor.yy0->codegen=codegen_prg_header_lfunction;

    //!
    //(yygotominor.yy0->codegen)(yygotominor.yy0,0); //EXEC
    //Itt korábban takarítás volt, és a struktúrák teszt célú bejárása.
    //A parser 4.4.xx óta rekurzív, azért itt nem lehet takarítani.
}
#line 1493 "./parser.c"
        break;
      case 1:
#line 256 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(4,yymsp[-3].minor.yy0,yymsp[-2].minor.yy0,yymsp[-1].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="header ::= lnewline0 namespace lusing lstatdefin.";
    yygotominor.yy0->codegen=codegen_header_lnewline0_namespace_lusing_lstatdefin;

    if( headerflag )
    {
        //!
        (yygotominor.yy0->codegen)(yygotominor.yy0,0); //EXEC
        headerflag=0; //header kész
    }
}
#line 1509 "./parser.c"
        break;
      case 2:
#line 269 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(0);
    yygotominor.yy0->text="namespace ::= .";
    yygotominor.yy0->codegen=codegen_namespace;
}
#line 1518 "./parser.c"
        break;
      case 3:
#line 275 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(4,yymsp[-3].minor.yy0,yymsp[-2].minor.yy0,yymsp[-1].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="namespace ::= NAMESPACE dotsymbol nsalias ldotsymbol lnewline.";
    yygotominor.yy0->codegen=codegen_namespace_NAMESPACE_dotsymbol_nsalias_ldotsymbol_lnewline;

    //!
    (yygotominor.yy0->codegen)(yygotominor.yy0,0); //EXEC
}
#line 1530 "./parser.c"
  yy_destructor(37,&yymsp[-4].minor);
        break;
      case 4:
#line 284 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(0);
    yygotominor.yy0->text="lusing ::= .";
    yygotominor.yy0->codegen=codegen_lusing;
}
#line 1540 "./parser.c"
        break;
      case 5:
#line 290 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-1].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="lusing ::= lusing using.";
    yygotominor.yy0->codegen=codegen_lusing_lusing_using;
}
#line 1549 "./parser.c"
        break;
      case 6:
#line 296 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(4,yymsp[-3].minor.yy0,yymsp[-2].minor.yy0,yymsp[-1].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="using ::= USING dotsymbol nsalias ldotsymbol lnewline.";
    yygotominor.yy0->codegen=codegen_using_USING_dotsymbol_nsalias_ldotsymbol_lnewline;

    //!
    (yygotominor.yy0->codegen)(yygotominor.yy0,0); //EXEC
}
#line 1561 "./parser.c"
  yy_destructor(38,&yymsp[-4].minor);
        break;
      case 7:
#line 305 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(0);
    yygotominor.yy0->text="nsalias ::= .";
    yygotominor.yy0->codegen=codegen_nsalias;
}
#line 1571 "./parser.c"
        break;
      case 8:
#line 311 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="nsalias ::= EQ SYMBOL.";
    yygotominor.yy0->codegen=codegen_nsalias_EQ_SYMBOL;
}
#line 1580 "./parser.c"
  yy_destructor(17,&yymsp[-1].minor);
        break;
      case 9:
#line 317 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="dotsymbol ::= SYMBOL.";
    yygotominor.yy0->codegen=codegen_dotsymbol_SYMBOL;
}
#line 1590 "./parser.c"
        break;
      case 10:
#line 323 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="dotsymbol ::= dotsymbol DOT SYMBOL.";
    yygotominor.yy0->codegen=codegen_dotsymbol_dotsymbol_DOT_SYMBOL;
}
#line 1599 "./parser.c"
  yy_destructor(5,&yymsp[-1].minor);
        break;
      case 11:
#line 329 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(0);
    yygotominor.yy0->text="ldotsymbol ::= .";
    yygotominor.yy0->codegen=codegen_ldotsymbol;
}
#line 1609 "./parser.c"
        break;
      case 12:
#line 335 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-1].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="ldotsymbol ::= ldotsymbol dotsymbol.";
    yygotominor.yy0->codegen=codegen_ldotsymbol_ldotsymbol_dotsymbol;
}
#line 1618 "./parser.c"
        break;
      case 13:
#line 341 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="ddotsymbol ::= dotsymbol.";
    yygotominor.yy0->codegen=codegen_ddotsymbol_dotsymbol;
}
#line 1627 "./parser.c"
        break;
      case 14:
#line 347 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="ddotsymbol ::= DOT dotsymbol.";
    yygotominor.yy0->codegen=codegen_ddotsymbol_DOT_dotsymbol;
}
#line 1636 "./parser.c"
  yy_destructor(5,&yymsp[-1].minor);
        break;
      case 15:
#line 353 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(0);
    yygotominor.yy0->text="lstatdefin ::= .";
    yygotominor.yy0->codegen=codegen_lstatdefin;
}
#line 1646 "./parser.c"
        break;
      case 16:
#line 359 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(3,yymsp[-3].minor.yy0,yymsp[-1].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="lstatdefin ::= lstatdefin STATIC statdefin lnewline.";
    yygotominor.yy0->codegen=codegen_lstatdefin_lstatdefin_STATIC_statdefin_lnewline; 
}
#line 1655 "./parser.c"
  yy_destructor(40,&yymsp[-2].minor);
        break;
      case 17:
#line 365 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="statdefin ::= statdef.";
    yygotominor.yy0->codegen=codegen_statdefin_statdef; 
}
#line 1665 "./parser.c"
        break;
      case 18:
#line 371 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="statdefin ::= statdefin COMMA statdef.";
    yygotominor.yy0->codegen=codegen_statdefin_statdefin_COMMA_statdef; 
}
#line 1674 "./parser.c"
  yy_destructor(7,&yymsp[-1].minor);
        break;
      case 19:
#line 377 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="statdef ::= SYMBOL.";
    yygotominor.yy0->codegen=codegen_statdef_SYMBOL; 

    //!    
    add_static(yymsp[0].minor.yy0);
    yymsp[0].minor.yy0->cargo=headerflag?SYM_GLOBSTAT:SYM_LOCSTAT;
}
#line 1688 "./parser.c"
        break;
      case 20:
#line 387 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="statdef ::= SYMBOL ASSIGN expr.";
    yygotominor.yy0->codegen=codegen_statdef_SYMBOL_ASSIGN_expr; 

    //!
    add_static(yymsp[-2].minor.yy0);
    yymsp[-2].minor.yy0->cargo=headerflag?SYM_GLOBSTAT:SYM_LOCSTAT;
}
#line 1701 "./parser.c"
  yy_destructor(8,&yymsp[-1].minor);
        break;
      case 21:
#line 397 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="lfunction ::= function.";
    yygotominor.yy0->codegen=codegen_lfunction_function;
}
#line 1711 "./parser.c"
        break;
      case 22:
#line 403 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-1].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="lfunction ::= lfunction function.";
    yygotominor.yy0->codegen=codegen_lfunction_lfunction_function;
}
#line 1720 "./parser.c"
        break;
      case 23:
#line 409 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(4,yymsp[-6].minor.yy0,yymsp[-4].minor.yy0,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="function ::= classid LPAR ldsym RPAR newspec lnewline lslot.";
    yygotominor.yy0->codegen=codegen_function_classid_LPAR_ldsym_RPAR_newspec_lnewline_lslot; 

    //!
    (yygotominor.yy0->codegen)(yygotominor.yy0,0); //EXEC
}
#line 1732 "./parser.c"
  yy_destructor(41,&yymsp[-5].minor);
  yy_destructor(42,&yymsp[-3].minor);
        /* No destructor defined for lnewline */
        break;
      case 24:
#line 418 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="classid ::= CLASS dotsymbol.";
    yygotominor.yy0->codegen=codegen_classid_CLASS_dotsymbol;
}
#line 1744 "./parser.c"
  yy_destructor(43,&yymsp[-1].minor);
        break;
      case 25:
#line 424 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(0);
    yygotominor.yy0->text="newspec ::= .";
    yygotominor.yy0->codegen=codegen_newspec;
}
#line 1754 "./parser.c"
        break;
      case 26:
#line 430 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(0);
    yygotominor.yy0->text="newspec ::= NEW COLON.";
    yygotominor.yy0->codegen=codegen_newspec_NEW_COLON;
}
#line 1763 "./parser.c"
  yy_destructor(44,&yymsp[-1].minor);
  yy_destructor(34,&yymsp[0].minor);
        break;
      case 27:
#line 436 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="newspec ::= NEW COLON SYMBOL.";
    yygotominor.yy0->codegen=codegen_newspec_NEW_COLON_SYMBOL;
}
#line 1774 "./parser.c"
  yy_destructor(44,&yymsp[-2].minor);
  yy_destructor(34,&yymsp[-1].minor);
        break;
      case 28:
#line 442 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(0);
    yygotominor.yy0->text="lslot ::= .";
    yygotominor.yy0->cargo=0;
    yygotominor.yy0->codegen=codegen_lslot; 
}
#line 1786 "./parser.c"
        break;
      case 29:
#line 449 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-2].minor.yy0,yymsp[-1].minor.yy0);
    yygotominor.yy0->text="lslot ::= lslot slot lnewline.";
    yygotominor.yy0->cargo=yymsp[-2].minor.yy0->cargo+1;
    yygotominor.yy0->codegen=codegen_lslot_lslot_slot_lnewline; 
}
#line 1796 "./parser.c"
        /* No destructor defined for lnewline */
        break;
      case 30:
#line 456 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="slot ::= ATTRIB SYMBOL.";
    yygotominor.yy0->codegen=codegen_slot_ATTRIB_SYMBOL; 
}
#line 1806 "./parser.c"
  yy_destructor(45,&yymsp[-1].minor);
        break;
      case 31:
#line 462 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="slot ::= METHOD SYMBOL.";
    yygotominor.yy0->codegen=codegen_slot_METHOD_SYMBOL; 
}
#line 1816 "./parser.c"
  yy_destructor(46,&yymsp[-1].minor);
        break;
      case 32:
#line 468 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-1].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="slot ::= METHOD SYMBOL expr.";
    yygotominor.yy0->codegen=codegen_slot_METHOD_SYMBOL_expr; 
}
#line 1826 "./parser.c"
  yy_destructor(46,&yymsp[-2].minor);
        break;
      case 33:
#line 474 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="ldsym ::= dotsymbol.";
    yygotominor.yy0->cargo=1;
    yygotominor.yy0->codegen=codegen_ldsym_dotsymbol;  
}
#line 1837 "./parser.c"
        break;
      case 34:
#line 481 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="ldsym ::= ldsym COMMA dotsymbol.";
    yygotominor.yy0->cargo=yymsp[-2].minor.yy0->cargo+1;
    yygotominor.yy0->codegen=codegen_ldsym_ldsym_COMMA_dotsymbol;  
}
#line 1847 "./parser.c"
  yy_destructor(7,&yymsp[-1].minor);
        break;
      case 35:
#line 488 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(4,yymsp[-5].minor.yy0,yymsp[-3].minor.yy0,yymsp[-1].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="function ::= funcid LPAR argument RPAR newline body.";
    yygotominor.yy0->codegen=codegen_function_funcid_LPAR_argument_RPAR_newline_body; 

    //!
    (yygotominor.yy0->codegen)(yygotominor.yy0,0); //EXEC
}
#line 1860 "./parser.c"
  yy_destructor(41,&yymsp[-4].minor);
  yy_destructor(42,&yymsp[-2].minor);
        break;
      case 36:
#line 497 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="funcid ::= FUNCTION dotsymbol.";
    yygotominor.yy0->codegen=codegen_funcid_FUNCTION_dotsymbol;
}
#line 1871 "./parser.c"
  yy_destructor(47,&yymsp[-1].minor);
        break;
      case 37:
#line 503 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="funcid ::= STFUNCTION dotsymbol.";
    yygotominor.yy0->codegen=codegen_funcid_STFUNCTION_dotsymbol;
}
#line 1881 "./parser.c"
  yy_destructor(48,&yymsp[-1].minor);
        break;
      case 38:
#line 509 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(0);
    yygotominor.yy0->text="argument ::= .";
    yygotominor.yy0->codegen=codegen_argument;  
}
#line 1891 "./parser.c"
        break;
      case 39:
#line 515 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(0);
    yygotominor.yy0->text="argument ::= STAR.";
    yygotominor.yy0->codegen=codegen_argument_STAR;  
}
#line 1900 "./parser.c"
  yy_destructor(27,&yymsp[0].minor);
        break;
      case 40:
#line 521 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="argument ::= larg.";
    yygotominor.yy0->cargo=yymsp[0].minor.yy0->cargo;
    yygotominor.yy0->codegen=codegen_argument_larg;  
}
#line 1911 "./parser.c"
        break;
      case 41:
#line 528 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[-2].minor.yy0);
    yygotominor.yy0->text="argument ::= larg COMMA STAR.";
    yygotominor.yy0->cargo=yymsp[-2].minor.yy0->cargo;
    yygotominor.yy0->codegen=codegen_argument_larg_COMMA_STAR;  
}
#line 1921 "./parser.c"
  yy_destructor(7,&yymsp[-1].minor);
  yy_destructor(27,&yymsp[0].minor);
        break;
      case 42:
#line 535 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="larg ::= SYMBOL.";
    yygotominor.yy0->cargo=1;
    yygotominor.yy0->codegen=codegen_larg_SYMBOL;  
    
    //!
    add_local(yymsp[0].minor.yy0);
}
#line 1936 "./parser.c"
        break;
      case 43:
#line 545 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="larg ::= larg COMMA SYMBOL.";
    yygotominor.yy0->cargo=yymsp[-2].minor.yy0->cargo+1;
    yygotominor.yy0->codegen=codegen_larg_larg_COMMA_SYMBOL;  

    //!
    add_local(yymsp[0].minor.yy0);
}
#line 1949 "./parser.c"
  yy_destructor(7,&yymsp[-1].minor);
        break;
      case 44:
#line 555 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(0);
    yygotominor.yy0->text="bargument ::= .";
    yygotominor.yy0->codegen=codegen_bargument;
    yygotominor.yy0->outsource=outsource_bargument;

    //!
    if( blockflag )
    {
        nested_block();
    }
    blockflag=1;
}
#line 1967 "./parser.c"
        break;
      case 45:
#line 569 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="bargument ::= lbarg.";
    yygotominor.yy0->cargo=yymsp[0].minor.yy0->cargo;
    yygotominor.yy0->codegen=codegen_bargument_lbarg;
    yygotominor.yy0->outsource=outsource_bargument_lbarg;

    //!
    if( blockflag )
    {
        nested_block();
    }
    blockflag=1;
}
#line 1985 "./parser.c"
        break;
      case 46:
#line 584 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(0);
    yygotominor.yy0->text="bargument ::= STAR.";
    yygotominor.yy0->codegen=codegen_bargument_STAR;
    yygotominor.yy0->outsource=outsource_bargument_STAR;

    //!
    if( blockflag )
    {
        nested_block();
    }
    blockflag=1;
}
#line 2002 "./parser.c"
  yy_destructor(27,&yymsp[0].minor);
        break;
      case 47:
#line 598 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[-2].minor.yy0);
    yygotominor.yy0->text="bargument ::= lbarg COMMA STAR.";
    yygotominor.yy0->cargo=yymsp[-2].minor.yy0->cargo;
    yygotominor.yy0->codegen=codegen_bargument_lbarg_COMMA_STAR;
    yygotominor.yy0->outsource=outsource_bargument_lbarg_COMMA_STAR;

    //!
    if( blockflag )
    {
        nested_block();
    }
    blockflag=1;
}
#line 2021 "./parser.c"
  yy_destructor(7,&yymsp[-1].minor);
  yy_destructor(27,&yymsp[0].minor);
        break;
      case 48:
#line 613 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="lbarg ::= SYMBOL.";
    yygotominor.yy0->cargo=1;
    yygotominor.yy0->codegen=codegen_lbarg_SYMBOL;
    yygotominor.yy0->outsource=outsource_lbarg_SYMBOL;
    
    //!
    add_blkarg(yymsp[0].minor.yy0);
}
#line 2037 "./parser.c"
        break;
      case 49:
#line 624 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="lbarg ::= lbarg COMMA SYMBOL.";
    yygotominor.yy0->cargo=yymsp[-2].minor.yy0->cargo+1;
    yygotominor.yy0->codegen=codegen_lbarg_lbarg_COMMA_SYMBOL;
    yygotominor.yy0->outsource=outsource_lbarg_lbarg_COMMA_SYMBOL;

    //!
    add_blkarg(yymsp[0].minor.yy0);
}
#line 2051 "./parser.c"
  yy_destructor(7,&yymsp[-1].minor);
        break;
      case 50:
#line 635 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-1].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="body ::= llocdefin lstatement.";
    yygotominor.yy0->codegen=codegen_body_llocdefin_lstatement;  
}
#line 2061 "./parser.c"
        break;
      case 51:
#line 641 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(0);
    yygotominor.yy0->text="llocdefin ::= .";
    yygotominor.yy0->codegen=codegen_llocdefin;
}
#line 2070 "./parser.c"
        break;
      case 52:
#line 647 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-1].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="llocdefin ::= llocdefin newline.";
    yygotominor.yy0->cargo=yymsp[-1].minor.yy0->cargo;
    yygotominor.yy0->codegen=codegen_llocdefin_llocdefin_newline;
}
#line 2080 "./parser.c"
        break;
      case 53:
#line 654 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(3,yymsp[-2].minor.yy0,yymsp[-1].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="llocdefin ::= llocdefin locdline newline.";
    yygotominor.yy0->cargo=yymsp[-2].minor.yy0->cargo+yymsp[-1].minor.yy0->cargo;
    yygotominor.yy0->codegen=codegen_llocdefin_llocdefin_locdline_newline;
}
#line 2090 "./parser.c"
        break;
      case 54:
#line 661 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="locdline ::= STATIC statdefin.";
    yygotominor.yy0->codegen=codegen_locdline_STATIC_statdefin;
}
#line 2099 "./parser.c"
  yy_destructor(40,&yymsp[-1].minor);
        break;
      case 55:
#line 667 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="locdline ::= LOCAL locdefin.";
    yygotominor.yy0->cargo=yymsp[0].minor.yy0->cargo;
    yygotominor.yy0->codegen=codegen_locdline_LOCAL_locdefin; 
}
#line 2110 "./parser.c"
  yy_destructor(49,&yymsp[-1].minor);
        break;
      case 56:
#line 674 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="locdefin ::= locdef.";
    yygotominor.yy0->cargo=1;
    yygotominor.yy0->codegen=codegen_locdefin_locdef; 
}
#line 2121 "./parser.c"
        break;
      case 57:
#line 681 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="locdefin ::= locdefin COMMA locdef.";
    yygotominor.yy0->cargo=yymsp[-2].minor.yy0->cargo+1;
    yygotominor.yy0->codegen=codegen_locdefin_locdefin_COMMA_locdef;  
}
#line 2131 "./parser.c"
  yy_destructor(7,&yymsp[-1].minor);
        break;
      case 58:
#line 688 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="locdef ::= SYMBOL.";
    yygotominor.yy0->codegen=codegen_locdef_SYMBOL;
    
    //!
    add_local(yymsp[0].minor.yy0);
}
#line 2144 "./parser.c"
        break;
      case 59:
#line 697 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="locdef ::= SYMBOL ASSIGN expr.";
    yygotominor.yy0->codegen=codegen_locdef_SYMBOL_ASSIGN_expr; 

    //!
    add_local(yymsp[-2].minor.yy0);
    symbol_search(yymsp[-2].minor.yy0);
}
#line 2157 "./parser.c"
  yy_destructor(8,&yymsp[-1].minor);
        break;
      case 60:
#line 707 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(0);
    yygotominor.yy0->text="lstatement ::= .";
    yygotominor.yy0->codegen=codegen_lstatement;  
}
#line 2167 "./parser.c"
        break;
      case 61:
#line 713 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-1].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="lstatement ::= lstatement newline.";
    yygotominor.yy0->codegen=codegen_lstatement_lstatement_newline;  
}
#line 2176 "./parser.c"
        break;
      case 62:
#line 719 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(3,yymsp[-2].minor.yy0,yymsp[-1].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="lstatement ::= lstatement statement newline.";
    yygotominor.yy0->codegen=codegen_lstatement_lstatement_statement_newline;  
}
#line 2185 "./parser.c"
        break;
      case 63:
#line 725 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(0);
    yygotominor.yy0->text="statement ::= QUIT.";
    yygotominor.yy0->codegen=codegen_statement_QUIT;  
}
#line 2194 "./parser.c"
  yy_destructor(50,&yymsp[0].minor);
        break;
      case 64:
#line 731 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="statement ::= RETURN expr.";
    yygotominor.yy0->codegen=codegen_statement_RETURN_expr;  
}
#line 2204 "./parser.c"
  yy_destructor(51,&yymsp[-1].minor);
        break;
      case 65:
#line 737 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(3,yymsp[-3].minor.yy0,yymsp[-2].minor.yy0,yymsp[-1].minor.yy0);
    yygotominor.yy0->text="statement ::= begseq lrecov finally END.";
    yygotominor.yy0->codegen=codegen_statement_begseq_lrecov_finally_END;
}
#line 2214 "./parser.c"
  yy_destructor(52,&yymsp[0].minor);
        break;
      case 66:
#line 743 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(4,yymsp[-3].minor.yy0,yymsp[-2].minor.yy0,yymsp[-1].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="statement ::= if lelseif else endif.";
    yygotominor.yy0->codegen=codegen_statement_if_lelseif_else_endif;
}
#line 2224 "./parser.c"
        break;
      case 67:
#line 749 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(3,yymsp[-3].minor.yy0,yymsp[-2].minor.yy0,yymsp[-1].minor.yy0);
    yygotominor.yy0->text="statement ::= WHILE expr newline lstatement END.";
    yygotominor.yy0->codegen=codegen_statement_WHILE_expr_newline_lstatement_END;
}
#line 2233 "./parser.c"
  yy_destructor(53,&yymsp[-4].minor);
  yy_destructor(52,&yymsp[0].minor);
        break;
      case 68:
#line 755 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(6,yymsp[-8].minor.yy0,yymsp[-6].minor.yy0,yymsp[-4].minor.yy0,yymsp[-3].minor.yy0,yymsp[-2].minor.yy0,yymsp[-1].minor.yy0);
    yygotominor.yy0->text="statement ::= FOR SYMBOL ASSIGN expr TO expr forstep newline lstatement END.";
    yygotominor.yy0->codegen=codegen_statement_FOR_SYMBOL_ASSIGN_expr_TO_expr_forstep_newline_lstatement_END; 

    //!
    symbol_search(yymsp[-8].minor.yy0);
}
#line 2247 "./parser.c"
  yy_destructor(54,&yymsp[-9].minor);
  yy_destructor(8,&yymsp[-7].minor);
  yy_destructor(55,&yymsp[-5].minor);
  yy_destructor(52,&yymsp[0].minor);
        break;
      case 69:
#line 764 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="statement ::= LOOP.";
    yygotominor.yy0->codegen=codegen_statement_LOOP; 
}
#line 2260 "./parser.c"
        break;
      case 70:
#line 770 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="statement ::= EXIT.";
    yygotominor.yy0->codegen=codegen_statement_EXIT; 
}
#line 2269 "./parser.c"
        break;
      case 71:
#line 776 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="statement ::= expr.";
    yygotominor.yy0->codegen=codegen_statement_expr; 
}
#line 2278 "./parser.c"
        break;
      case 72:
#line 782 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-1].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="begseq ::= BEGSEQ newline lstatement.";
    yygotominor.yy0->codegen=codegen_begseq_BEGSEQ_newline_lstatement;  
}
#line 2287 "./parser.c"
  yy_destructor(58,&yymsp[-2].minor);
        break;
      case 73:
#line 788 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(0);
    yygotominor.yy0->text="lrecov ::= .";
    yygotominor.yy0->codegen=codegen_lrecov;
}
#line 2297 "./parser.c"
        break;
      case 74:
#line 794 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-1].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="lrecov ::= lrecov recov.";
    yygotominor.yy0->codegen=codegen_lrecov_lrecov_recov;
}
#line 2306 "./parser.c"
        break;
      case 75:
#line 800 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-1].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="recov ::= RECOVER newline lstatement.";
    yygotominor.yy0->codegen=codegen_recov_RECOVER_newline_lstatement; 
}
#line 2315 "./parser.c"
  yy_destructor(59,&yymsp[-2].minor);
        break;
      case 76:
#line 806 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(3,yymsp[-2].minor.yy0,yymsp[-1].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="recov ::= RECOVER SYMBOL newline lstatement.";
    yygotominor.yy0->codegen=codegen_recov_RECOVER_SYMBOL_newline_lstatement;
    
    //!
    symbol_search(yymsp[-2].minor.yy0);
}
#line 2328 "./parser.c"
  yy_destructor(59,&yymsp[-3].minor);
        break;
      case 77:
#line 815 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(4,yymsp[-3].minor.yy0,yymsp[-2].minor.yy0,yymsp[-1].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="recov ::= RECOVER SYMBOL expr newline lstatement.";
    yygotominor.yy0->codegen=codegen_recov_RECOVER_SYMBOL_expr_newline_lstatement;
    
    //!
    symbol_search(yymsp[-3].minor.yy0);
}
#line 2341 "./parser.c"
  yy_destructor(59,&yymsp[-4].minor);
        break;
      case 78:
#line 824 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(4,yymsp[-5].minor.yy0,yymsp[-3].minor.yy0,yymsp[-1].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="recov ::= RECOVER SYMBOL LT dotsymbol GT newline lstatement.";
    yygotominor.yy0->codegen=codegen_recov_RECOVER_SYMBOL_LT_dotsymbol_GT_newline_lstatement;
    
    //!
    symbol_search(yymsp[-5].minor.yy0);
}
#line 2354 "./parser.c"
  yy_destructor(59,&yymsp[-6].minor);
  yy_destructor(23,&yymsp[-4].minor);
  yy_destructor(22,&yymsp[-2].minor);
        break;
      case 79:
#line 834 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(0);
    yygotominor.yy0->text="finally ::= .";
    yygotominor.yy0->codegen=codegen_finally;
}
#line 2366 "./parser.c"
        break;
      case 80:
#line 840 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-1].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="finally ::= FINALLY newline lstatement.";
    yygotominor.yy0->codegen=codegen_finally_FINALLY_newline_lstatement;
}
#line 2375 "./parser.c"
  yy_destructor(60,&yymsp[-2].minor);
        break;
      case 81:
#line 847 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(3,yymsp[-2].minor.yy0,yymsp[-1].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="if ::= IF expr newline lstatement.";
    yygotominor.yy0->codegen=codegen_if_IF_expr_newline_lstatement; 
}
#line 2385 "./parser.c"
  yy_destructor(61,&yymsp[-3].minor);
        break;
      case 82:
#line 853 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(4,yymsp[-4].minor.yy0,yymsp[-2].minor.yy0,yymsp[-1].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="if ::= DOCASE newline CASE expr newline lstatement.";
    yygotominor.yy0->codegen=codegen_if_DOCASE_newline_CASE_expr_newline_lstatement;  
}
#line 2395 "./parser.c"
  yy_destructor(62,&yymsp[-5].minor);
  yy_destructor(63,&yymsp[-3].minor);
        break;
      case 83:
#line 859 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(0);
    yygotominor.yy0->text="lelseif ::= .";
    yygotominor.yy0->cargo=0;
    yygotominor.yy0->codegen=codegen_lelseif;
}
#line 2407 "./parser.c"
        break;
      case 84:
#line 866 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-1].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="lelseif ::= lelseif elseif.";
    yygotominor.yy0->cargo=yymsp[-1].minor.yy0->cargo+1;
    yygotominor.yy0->codegen=codegen_lelseif_lelseif_elseif;
}
#line 2417 "./parser.c"
        break;
      case 85:
#line 873 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(3,yymsp[-2].minor.yy0,yymsp[-1].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="elseif ::= ELSEIF expr newline lstatement.";
    yygotominor.yy0->codegen=codegen_elseif_ELSEIF_expr_newline_lstatement;
}
#line 2426 "./parser.c"
  yy_destructor(64,&yymsp[-3].minor);
        break;
      case 86:
#line 879 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(3,yymsp[-2].minor.yy0,yymsp[-1].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="elseif ::= CASE expr newline lstatement.";
    yygotominor.yy0->codegen=codegen_elseif_CASE_expr_newline_lstatement;
}
#line 2436 "./parser.c"
  yy_destructor(63,&yymsp[-3].minor);
        break;
      case 87:
#line 885 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(0);
    yygotominor.yy0->text="else ::= .";
    yygotominor.yy0->codegen=codegen_else;
}
#line 2446 "./parser.c"
        break;
      case 88:
#line 891 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-1].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="else ::= ELSE newline lstatement";
    yygotominor.yy0->cargo=1;
    yygotominor.yy0->codegen=codegen_else_ELSE_newline_lstatement; 
}
#line 2456 "./parser.c"
  yy_destructor(65,&yymsp[-2].minor);
        break;
      case 89:
#line 898 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-1].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="else ::= OTHERWISE newline lstatement";
    yygotominor.yy0->cargo=1;
    yygotominor.yy0->codegen=codegen_else_OTHERWISE_newline_lstatement; 
}
#line 2467 "./parser.c"
  yy_destructor(66,&yymsp[-2].minor);
        break;
      case 90:
#line 905 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(0);
    yygotominor.yy0->text="endif ::= END";
    yygotominor.yy0->codegen=codegen_endif_END;
}
#line 2477 "./parser.c"
  yy_destructor(52,&yymsp[0].minor);
        break;
      case 91:
#line 911 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(0);
    yygotominor.yy0->text="forstep ::= .";
    yygotominor.yy0->codegen=codegen_forstep;
}
#line 2487 "./parser.c"
        break;
      case 92:
#line 917 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="forstep ::= STEP expr.";
    yygotominor.yy0->codegen=codegen_forstep_STEP_expr; 
}
#line 2496 "./parser.c"
  yy_destructor(67,&yymsp[-1].minor);
        break;
      case 93:
#line 923 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(0);
    yygotominor.yy0->text="lfuncpar ::= .";
    yygotominor.yy0->codegen=codegen_lfuncpar;
    yygotominor.yy0->outsource=outsource_lfuncpar;
    yygotominor.yy0->cargo=0;
}
#line 2508 "./parser.c"
        break;
      case 94:
#line 931 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="lfuncpar ::= parexpr.";
    yygotominor.yy0->codegen=codegen_lfuncpar_parexpr;
    yygotominor.yy0->outsource=outsource_lfuncpar_parexpr;
    yygotominor.yy0->cargo=yymsp[0].minor.yy0->cargo+1;
}
#line 2519 "./parser.c"
        break;
      case 95:
#line 939 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="lfuncpar ::= lfuncpar0 COMMA parexpr0.";
    yygotominor.yy0->codegen=codegen_lfuncpar_lfuncpar0_COMMA_parexpr0;
    yygotominor.yy0->outsource=outsource_lfuncpar_lfuncpar0_COMMA_parexpr0;
    yygotominor.yy0->cargo=yymsp[-2].minor.yy0->cargo+yymsp[0].minor.yy0->cargo+1;
}
#line 2530 "./parser.c"
  yy_destructor(7,&yymsp[-1].minor);
        break;
      case 96:
#line 947 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="lfuncpar0 ::= parexpr0.";
    yygotominor.yy0->codegen=codegen_lfuncpar0_parexpr0;
    yygotominor.yy0->outsource=outsource_lfuncpar0_parexpr0;
    yygotominor.yy0->cargo=yymsp[0].minor.yy0->cargo+1;
}
#line 2542 "./parser.c"
        break;
      case 97:
#line 955 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="lfuncpar0 ::= lfuncpar0 COMMA parexpr0.";
    yygotominor.yy0->codegen=codegen_lfuncpar0_lfuncpar0_COMMA_parexpr0;
    yygotominor.yy0->outsource=outsource_lfuncpar0_lfuncpar0_COMMA_parexpr0;
    yygotominor.yy0->cargo=yymsp[-2].minor.yy0->cargo+yymsp[0].minor.yy0->cargo+1;
}
#line 2553 "./parser.c"
  yy_destructor(7,&yymsp[-1].minor);
        break;
      case 98:
#line 963 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(0);
    yygotominor.yy0->text="parexpr0 ::= .";
    yygotominor.yy0->codegen=codegen_parexpr0;
    yygotominor.yy0->outsource=outsource_parexpr0;
    yygotominor.yy0->cargo=0;
}
#line 2565 "./parser.c"
        break;
      case 99:
#line 971 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="parexpr0 ::= parexpr.";
    yygotominor.yy0->codegen=codegen_parexpr0_parexpr;
    yygotominor.yy0->outsource=outsource_parexpr0_parexpr;
    yygotominor.yy0->cargo=yymsp[0].minor.yy0->cargo;
}
#line 2576 "./parser.c"
        break;
      case 100:
#line 979 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="parexpr ::= expr.";
    yygotominor.yy0->codegen=codegen_parexpr_expr;
    yygotominor.yy0->outsource=outsource_parexpr_expr;
    yygotominor.yy0->cargo=0;
}
#line 2587 "./parser.c"
        break;
      case 101:
#line 987 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(0);
    yygotominor.yy0->text="parexpr ::= STAR.";
    yygotominor.yy0->codegen=codegen_parexpr_STAR;
    yygotominor.yy0->outsource=outsource_parexpr_STAR;
    yygotominor.yy0->cargo=(1<<16);
}
#line 2598 "./parser.c"
  yy_destructor(27,&yymsp[0].minor);
        break;
      case 102:
#line 995 "./parser.lem"
{  //@symbol
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="parexpr ::= AT SYMBOL.";
    yygotominor.yy0->codegen=codegen_parexpr_AT_SYMBOL;
    yygotominor.yy0->outsource=outsource_parexpr_AT_SYMBOL;
    yygotominor.yy0->cargo=0;

    //!
    symbol_search(yymsp[0].minor.yy0);
}
#line 2613 "./parser.c"
  yy_destructor(68,&yymsp[-1].minor);
        break;
      case 103:
#line 1006 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(0);
    yygotominor.yy0->text="lexpr ::= .";
    yygotominor.yy0->codegen=codegen_lexpr;
    yygotominor.yy0->outsource=outsource_lexpr;
}
#line 2624 "./parser.c"
        break;
      case 104:
#line 1013 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="lexpr ::= expr.";
    yygotominor.yy0->cargo=1;
    yygotominor.yy0->codegen=codegen_lexpr_expr;
    yygotominor.yy0->outsource=outsource_lexpr_expr;
}
#line 2635 "./parser.c"
        break;
      case 105:
#line 1021 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="lexpr ::= lexpr0 COMMA expr0.";
    yygotominor.yy0->cargo=yymsp[-2].minor.yy0->cargo+1;
    yygotominor.yy0->codegen=codegen_lexpr_lexpr0_COMMA_expr0;
    yygotominor.yy0->outsource=outsource_lexpr_lexpr0_COMMA_expr0;
}
#line 2646 "./parser.c"
  yy_destructor(7,&yymsp[-1].minor);
        break;
      case 106:
#line 1029 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="lexpr0 ::= expr0.";
    yygotominor.yy0->cargo=1;
    yygotominor.yy0->codegen=codegen_lexpr0_expr0;
    yygotominor.yy0->outsource=outsource_lexpr0_expr0;
}
#line 2658 "./parser.c"
        break;
      case 107:
#line 1037 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="lexpr0 ::= lexpr0 COMMA expr0.";
    yygotominor.yy0->cargo=yymsp[-2].minor.yy0->cargo+1;
    yygotominor.yy0->codegen=codegen_lexpr0_lexpr0_COMMA_expr0;
    yygotominor.yy0->outsource=outsource_lexpr0_lexpr0_COMMA_expr0;
}
#line 2669 "./parser.c"
  yy_destructor(7,&yymsp[-1].minor);
        break;
      case 108:
#line 1045 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(0);
    yygotominor.yy0->text="expr0 ::= .";
    yygotominor.yy0->codegen=codegen_expr0;
    yygotominor.yy0->outsource=outsource_expr0;
}
#line 2680 "./parser.c"
        break;
      case 109:
#line 1052 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="expr0 ::= expr.";
    yygotominor.yy0->codegen=codegen_expr0_expr;
    yygotominor.yy0->outsource=outsource_expr0_expr;
}
#line 2690 "./parser.c"
        break;
      case 110:
#line 1059 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(0);
    yygotominor.yy0->text="msgpar ::= .";
    yygotominor.yy0->codegen=codegen_msgpar;
    yygotominor.yy0->outsource=outsource_msgpar;
}
#line 2700 "./parser.c"
        break;
      case 111:
#line 1066 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="msgpar ::= ASSIGN expr.";
    yygotominor.yy0->cargo=1;
    yygotominor.yy0->codegen=codegen_msgpar_ASSIGN_expr;
    yygotominor.yy0->outsource=outsource_msgpar_ASSIGN_expr;
}
#line 2711 "./parser.c"
  yy_destructor(8,&yymsp[-1].minor);
        break;
      case 112:
#line 1074 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[-1].minor.yy0);
    yygotominor.yy0->text="msgpar ::= LPAR lfuncpar RPAR.";
    yygotominor.yy0->cargo=yymsp[-1].minor.yy0->cargo;
    yygotominor.yy0->codegen=codegen_msgpar_LPAR_lfuncpar_RPAR;
    yygotominor.yy0->outsource=outsource_msgpar_LPAR_lfuncpar_RPAR;
}
#line 2723 "./parser.c"
  yy_destructor(41,&yymsp[-2].minor);
  yy_destructor(42,&yymsp[0].minor);
        break;
      case 113:
#line 1082 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-3].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="msgpar ::= LPAR lfuncpar RPAR ASSIGN expr.";
    yygotominor.yy0->cargo=yymsp[-3].minor.yy0->cargo+1;
    yygotominor.yy0->codegen=codegen_msgpar_LPAR_lfuncpar_RPAR_ASSIGN_expr;
    yygotominor.yy0->outsource=outsource_msgpar_LPAR_lfuncpar_RPAR_ASSIGN_expr;
}
#line 2736 "./parser.c"
  yy_destructor(41,&yymsp[-4].minor);
  yy_destructor(42,&yymsp[-2].minor);
  yy_destructor(8,&yymsp[-1].minor);
        break;
      case 114:
#line 1090 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="lnewline ::= newline.";
    yygotominor.yy0->codegen=codegen_lnewline_newline;
}
#line 2748 "./parser.c"
        break;
      case 115:
#line 1096 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-1].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="lnewline ::= lnewline newline.";
    yygotominor.yy0->codegen=codegen_lnewline_lnewline_newline;
}
#line 2757 "./parser.c"
        break;
      case 116:
#line 1102 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(0);
    yygotominor.yy0->text="lnewline0 ::= .";
    yygotominor.yy0->codegen=codegen_lnewline0;
}
#line 2766 "./parser.c"
        break;
      case 117:
#line 1108 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-1].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="lnewline0 ::= lnewline0 newline.";
    yygotominor.yy0->codegen=codegen_lnewline0_lnewline0_newline;
}
#line 2775 "./parser.c"
        break;
      case 118:
#line 1114 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="newline ::= NL.";
    yygotominor.yy0->codegen=codegen_newline_NL;
}
#line 2784 "./parser.c"
        break;
      case 119:
#line 1120 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="expr ::= NUMBER.";
    yygotominor.yy0->codegen=codegen_expr_NUMBER;
    yygotominor.yy0->outsource=outsource_expr_NUMBER;
}
#line 2794 "./parser.c"
        break;
      case 120:
#line 1127 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="expr ::= STRING.";
    yygotominor.yy0->codegen=codegen_expr_STRING;
    yygotominor.yy0->outsource=outsource_expr_STRING;
    
    static char *strtab_env=getenv("CCC_STRING_TAB");
    static FILE *strtab_fil=(strtab_env&&*strtab_env)?fopen(strtab_env,"a"):0;
    if( strtab_fil )
    {
        write_strtab(strtab_fil,yymsp[0].minor.yy0);
    }
}
#line 2811 "./parser.c"
        break;
      case 121:
#line 1141 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="expr ::= NLSTEXT.";
    yygotominor.yy0->codegen=codegen_expr_NLSTEXT;
    yygotominor.yy0->outsource=outsource_expr_NLSTEXT;
    
    static char *strtab_env=getenv("CCC_NLSTEXT_TAB");
    static FILE *strtab_fil=(strtab_env&&*strtab_env)?fopen(strtab_env,"a"):0;
    if( strtab_fil )
    {
        write_strtab(strtab_fil,yymsp[0].minor.yy0);
    }
}
#line 2828 "./parser.c"
        break;
      case 122:
#line 1155 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="expr ::= BINARYX.";
    yygotominor.yy0->codegen=codegen_expr_BINARYX;
    yygotominor.yy0->outsource=outsource_expr_BINARYX;
}
#line 2838 "./parser.c"
        break;
      case 123:
#line 1162 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="expr ::= BINARYA.";
    yygotominor.yy0->codegen=codegen_expr_BINARYA;
    yygotominor.yy0->outsource=outsource_expr_BINARYA;
}
#line 2848 "./parser.c"
        break;
      case 124:
#line 1169 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="expr ::= TRUE.";
    yygotominor.yy0->codegen=codegen_expr_TRUE;
    yygotominor.yy0->outsource=outsource_expr_TRUE;
}
#line 2858 "./parser.c"
        break;
      case 125:
#line 1176 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="expr ::= FALSE.";
    yygotominor.yy0->codegen=codegen_expr_FALSE;
    yygotominor.yy0->outsource=outsource_expr_FALSE;
}
#line 2868 "./parser.c"
        break;
      case 126:
#line 1183 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="expr ::= NIL.";
    yygotominor.yy0->codegen=codegen_expr_NIL;
    yygotominor.yy0->outsource=outsource_expr_NIL;
}
#line 2878 "./parser.c"
        break;
      case 127:
#line 1190 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="expr ::= SYMBOL.";
    yygotominor.yy0->codegen=codegen_expr_SYMBOL;
    yygotominor.yy0->outsource=outsource_expr_SYMBOL;

    //!
    symbol_search(yymsp[0].minor.yy0);
}
#line 2891 "./parser.c"
        break;
      case 128:
#line 1200 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="expr ::= SYMBOL ARROW SYMBOL.";
    yygotominor.yy0->codegen=codegen_expr_SYMBOL_ARROW_SYMBOL;
    yygotominor.yy0->outsource=outsource_expr_SYMBOL_ARROW_SYMBOL;
}
#line 2901 "./parser.c"
  yy_destructor(35,&yymsp[-1].minor);
        break;
      case 129:
#line 1207 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(3,yymsp[-3].minor.yy0,yymsp[-1].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="expr ::= expr COLON SYMBOL msgpar.";
    yygotominor.yy0->codegen=codegen_expr_expr_COLON_SYMBOL_msgpar;
    yygotominor.yy0->outsource=outsource_expr_expr_COLON_SYMBOL_msgpar;
}
#line 2912 "./parser.c"
  yy_destructor(34,&yymsp[-2].minor);
        break;
      case 130:
#line 1214 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(4,yymsp[-6].minor.yy0,yymsp[-3].minor.yy0,yymsp[-1].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="expr ::= expr COLON LPAR dotsymbol RPAR SYMBOL msgpar.";
    yygotominor.yy0->codegen=codegen_expr_expr_COLON_LPAR_dotsymbol_RPAR_SYMBOL_msgpar;
    yygotominor.yy0->outsource=outsource_expr_expr_COLON_LPAR_dotsymbol_RPAR_SYMBOL_msgpar;
}
#line 2923 "./parser.c"
  yy_destructor(34,&yymsp[-5].minor);
  yy_destructor(41,&yymsp[-4].minor);
  yy_destructor(42,&yymsp[-2].minor);
        break;
      case 131:
#line 1221 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(5,yymsp[-8].minor.yy0,yymsp[-5].minor.yy0,yymsp[-3].minor.yy0,yymsp[-1].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="expr ::= expr COLON LPAR dotsymbol AT dotsymbol RPAR SYMBOL msgpar.";
    yygotominor.yy0->codegen=codegen_expr_expr_COLON_LPAR_dotsymbol_AT_dotsymbol_RPAR_SYMBOL_msgpar;
    yygotominor.yy0->outsource=outsource_expr_expr_COLON_LPAR_dotsymbol_AT_dotsymbol_RPAR_SYMBOL_msgpar;
}
#line 2936 "./parser.c"
  yy_destructor(34,&yymsp[-7].minor);
  yy_destructor(41,&yymsp[-6].minor);
  yy_destructor(68,&yymsp[-4].minor);
  yy_destructor(42,&yymsp[-2].minor);
        break;
      case 132:
#line 1228 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-3].minor.yy0,yymsp[-1].minor.yy0);
    yygotominor.yy0->text="expr ::= ddotsymbol LPAR lfuncpar RPAR.";
    yygotominor.yy0->codegen=codegen_expr_ddotsymbol_LPAR_lfuncpar_RPAR;
    yygotominor.yy0->outsource=outsource_expr_ddotsymbol_LPAR_lfuncpar_RPAR;
}
#line 2950 "./parser.c"
  yy_destructor(41,&yymsp[-2].minor);
  yy_destructor(42,&yymsp[0].minor);
        break;
      case 133:
#line 1235 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-1].minor.yy0,yymsp[-2].minor.yy0); //sorrend!
    yygotominor.yy0->text="expr ::= LPAR lexpr RPAR.";
    yygotominor.yy0->lineno=yymsp[-2].minor.yy0->lineno;
    yygotominor.yy0->codegen=codegen_expr_LPAR_lexpr_RPAR;
    yygotominor.yy0->outsource=outsource_expr_LPAR_lexpr_RPAR;
}
#line 2963 "./parser.c"
  yy_destructor(42,&yymsp[0].minor);
        break;
      case 134:
#line 1243 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(3,yymsp[-3].minor.yy0,yymsp[-1].minor.yy0,yymsp[-5].minor.yy0); //sorrend!
    yygotominor.yy0->text="expr ::= LBRACE PIPE bargument PIPE lexpr RBRACE.";
    yygotominor.yy0->lineno=yymsp[-5].minor.yy0->lineno;
    yygotominor.yy0->codegen=codegen_expr_LBRACE_PIPE_bargument_PIPE_lexpr_RBRACE;
    yygotominor.yy0->outsource=outsource_expr_LBRACE_PIPE_bargument_PIPE_lexpr_RBRACE;

    //!
    blockflag=0;
    nodetab_blkarg->clean();
}
#line 2979 "./parser.c"
  yy_destructor(78,&yymsp[-4].minor);
  yy_destructor(78,&yymsp[-2].minor);
  yy_destructor(79,&yymsp[0].minor);
        break;
      case 135:
#line 1255 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(3,yymsp[-5].minor.yy0,yymsp[-3].minor.yy0,yymsp[-1].minor.yy0);
    yygotominor.yy0->text="expr ::= IF LPAR expr COMMA expr COMMA expr RPAR.";
    yygotominor.yy0->codegen=codegen_expr_IF_LPAR_expr_COMMA_expr_COMMA_expr_RPAR;
    yygotominor.yy0->outsource=outsource_expr_IF_LPAR_expr_COMMA_expr_COMMA_expr_RPAR;
}
#line 2992 "./parser.c"
  yy_destructor(61,&yymsp[-7].minor);
  yy_destructor(41,&yymsp[-6].minor);
  yy_destructor(7,&yymsp[-4].minor);
  yy_destructor(7,&yymsp[-2].minor);
  yy_destructor(42,&yymsp[0].minor);
        break;
      case 136:
#line 1262 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[-1].minor.yy0);
    yygotominor.yy0->text="expr ::= LBRACE lfuncpar RBRACE.";
    yygotominor.yy0->codegen=codegen_expr_LBRACE_lfuncpar_RBRACE;
    yygotominor.yy0->outsource=outsource_expr_LBRACE_lfuncpar_RBRACE;
}
#line 3007 "./parser.c"
  yy_destructor(77,&yymsp[-2].minor);
  yy_destructor(79,&yymsp[0].minor);
        break;
      case 137:
#line 1269 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-3].minor.yy0,yymsp[-1].minor.yy0);
    yygotominor.yy0->text="expr ::= expr LBRACKET expr RBRACKET.";
    yygotominor.yy0->codegen=codegen_expr_expr_LBRACKET_expr_RBRACKET;
    yygotominor.yy0->outsource=outsource_expr_expr_LBRACKET_expr_RBRACKET;
}
#line 3019 "./parser.c"
  yy_destructor(33,&yymsp[-2].minor);
  yy_destructor(80,&yymsp[0].minor);
        break;
      case 138:
#line 1277 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(3,yymsp[-5].minor.yy0,yymsp[-3].minor.yy0,yymsp[-1].minor.yy0);
    yygotominor.yy0->text="expr ::= expr LBRACKET parexpr0 DOTDOT parexpr0 RBRACKET.";
    yygotominor.yy0->codegen=codegen_expr_expr_LBRACKET_parexpr0_DOTDOT_parexpr0_RBRACKET;
    yygotominor.yy0->outsource=outsource_expr_expr_LBRACKET_parexpr0_DOTDOT_parexpr0_RBRACKET;
}
#line 3031 "./parser.c"
  yy_destructor(33,&yymsp[-4].minor);
  yy_destructor(6,&yymsp[-2].minor);
  yy_destructor(80,&yymsp[0].minor);
        break;
      case 139:
#line 1285 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="expr ::= expr ASSIGN expr.";
    yygotominor.yy0->codegen=codegen_expr_expr_ASSIGN_expr;
    yygotominor.yy0->outsource=outsource_expr_expr_ASSIGN_expr;
}
#line 3044 "./parser.c"
  yy_destructor(8,&yymsp[-1].minor);
        break;
      case 140:
#line 1292 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="expr ::= expr ADDASS expr.";
    yygotominor.yy0->codegen=codegen_expr_expr_ADDASS_expr;
    yygotominor.yy0->outsource=outsource_expr_expr_ADDASS_expr;
}
#line 3055 "./parser.c"
  yy_destructor(9,&yymsp[-1].minor);
        break;
      case 141:
#line 1299 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="expr ::= expr SUBASS expr.";
    yygotominor.yy0->codegen=codegen_expr_expr_SUBASS_expr;
    yygotominor.yy0->outsource=outsource_expr_expr_SUBASS_expr;
}
#line 3066 "./parser.c"
  yy_destructor(10,&yymsp[-1].minor);
        break;
      case 142:
#line 1306 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="expr ::= expr MULASS expr.";
    yygotominor.yy0->codegen=codegen_expr_expr_MULASS_expr;
    yygotominor.yy0->outsource=outsource_expr_expr_MULASS_expr;
}
#line 3077 "./parser.c"
  yy_destructor(11,&yymsp[-1].minor);
        break;
      case 143:
#line 1313 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="expr ::= expr DIVASS expr.";
    yygotominor.yy0->codegen=codegen_expr_expr_DIVASS_expr;
    yygotominor.yy0->outsource=outsource_expr_expr_DIVASS_expr;
}
#line 3088 "./parser.c"
  yy_destructor(12,&yymsp[-1].minor);
        break;
      case 144:
#line 1320 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="expr ::= expr MODASS expr.";
    yygotominor.yy0->codegen=codegen_expr_expr_MODASS_expr;
    yygotominor.yy0->outsource=outsource_expr_expr_MODASS_expr;
}
#line 3099 "./parser.c"
  yy_destructor(13,&yymsp[-1].minor);
        break;
      case 145:
#line 1327 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="expr ::= DBMINUS expr.";
    yygotominor.yy0->codegen=codegen_expr_DBMINUS_expr;
    yygotominor.yy0->outsource=outsource_expr_DBMINUS_expr;
}
#line 3110 "./parser.c"
  yy_destructor(32,&yymsp[-1].minor);
        break;
      case 146:
#line 1334 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="expr ::= DBPLUS expr.";
    yygotominor.yy0->codegen=codegen_expr_DBPLUS_expr;
    yygotominor.yy0->outsource=outsource_expr_DBPLUS_expr;
}
#line 3121 "./parser.c"
  yy_destructor(31,&yymsp[-1].minor);
        break;
      case 147:
#line 1341 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[-1].minor.yy0);
    yygotominor.yy0->text="expr ::= expr DBMINUS.";
    yygotominor.yy0->codegen=codegen_expr_expr_DBMINUS;
    yygotominor.yy0->outsource=outsource_expr_expr_DBMINUS;
}
#line 3132 "./parser.c"
  yy_destructor(32,&yymsp[0].minor);
        break;
      case 148:
#line 1348 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[-1].minor.yy0);
    yygotominor.yy0->text="expr ::= expr DBPLUS.";
    yygotominor.yy0->codegen=codegen_expr_expr_DBPLUS;
    yygotominor.yy0->outsource=outsource_expr_expr_DBPLUS;
}
#line 3143 "./parser.c"
  yy_destructor(31,&yymsp[0].minor);
        break;
      case 149:
#line 1355 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="expr ::= expr PLUS expr.";
    yygotominor.yy0->codegen=codegen_expr_expr_PLUS_expr;
    yygotominor.yy0->outsource=outsource_expr_expr_PLUS_expr;
}
#line 3154 "./parser.c"
  yy_destructor(25,&yymsp[-1].minor);
        break;
      case 150:
#line 1362 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="expr ::= expr MINUS expr.";
    yygotominor.yy0->codegen=codegen_expr_expr_MINUS_expr;
    yygotominor.yy0->outsource=outsource_expr_expr_MINUS_expr;
}
#line 3165 "./parser.c"
  yy_destructor(26,&yymsp[-1].minor);
        break;
      case 151:
#line 1369 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="expr ::= expr STAR expr.";
    yygotominor.yy0->codegen=codegen_expr_expr_STAR_expr;
    yygotominor.yy0->outsource=outsource_expr_expr_STAR_expr;
}
#line 3176 "./parser.c"
  yy_destructor(27,&yymsp[-1].minor);
        break;
      case 152:
#line 1376 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="expr ::= expr SLASH expr.";
    yygotominor.yy0->codegen=codegen_expr_expr_SLASH_expr;
    yygotominor.yy0->outsource=outsource_expr_expr_SLASH_expr;
}
#line 3187 "./parser.c"
  yy_destructor(28,&yymsp[-1].minor);
        break;
      case 153:
#line 1383 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="expr ::= expr MODULO expr.";
    yygotominor.yy0->codegen=codegen_expr_expr_MODULO_expr;
    yygotominor.yy0->outsource=outsource_expr_expr_MODULO_expr;
}
#line 3198 "./parser.c"
  yy_destructor(29,&yymsp[-1].minor);
        break;
      case 154:
#line 1390 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="expr ::= expr DBSTAR expr.";
    yygotominor.yy0->codegen=codegen_expr_expr_DBSTAR_expr;
    yygotominor.yy0->outsource=outsource_expr_expr_DBSTAR_expr;
}
#line 3209 "./parser.c"
  yy_destructor(30,&yymsp[-1].minor);
        break;
      case 155:
#line 1397 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="expr ::= MINUS expr.";
    yygotominor.yy0->codegen=codegen_expr_MINUS_expr;
    yygotominor.yy0->outsource=outsource_expr_MINUS_expr;
}
#line 3220 "./parser.c"
  yy_destructor(26,&yymsp[-1].minor);
        break;
      case 156:
#line 1404 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="expr ::= PLUS expr.";
    yygotominor.yy0->codegen=codegen_expr_PLUS_expr;
    yygotominor.yy0->outsource=outsource_expr_PLUS_expr;
}
#line 3231 "./parser.c"
  yy_destructor(25,&yymsp[-1].minor);
        break;
      case 157:
#line 1411 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="expr ::= expr EQEQ expr.";
    yygotominor.yy0->codegen=codegen_expr_expr_EQEQ_expr;
    yygotominor.yy0->outsource=outsource_expr_expr_EQEQ_expr;
}
#line 3242 "./parser.c"
  yy_destructor(18,&yymsp[-1].minor);
        break;
      case 158:
#line 1418 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="expr ::= expr EXEQ expr.";
    yygotominor.yy0->codegen=codegen_expr_expr_EXEQ_expr;
    yygotominor.yy0->outsource=outsource_expr_expr_EXEQ_expr;
}
#line 3253 "./parser.c"
  yy_destructor(21,&yymsp[-1].minor);
        break;
      case 159:
#line 1425 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="expr ::= expr GTEQ expr.";
    yygotominor.yy0->codegen=codegen_expr_expr_GTEQ_expr;
    yygotominor.yy0->outsource=outsource_expr_expr_GTEQ_expr;
}
#line 3264 "./parser.c"
  yy_destructor(19,&yymsp[-1].minor);
        break;
      case 160:
#line 1432 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="expr ::= expr LTEQ expr.";
    yygotominor.yy0->codegen=codegen_expr_expr_LTEQ_expr;
    yygotominor.yy0->outsource=outsource_expr_expr_LTEQ_expr;
}
#line 3275 "./parser.c"
  yy_destructor(20,&yymsp[-1].minor);
        break;
      case 161:
#line 1439 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="expr ::= expr GT expr.";
    yygotominor.yy0->codegen=codegen_expr_expr_GT_expr;
    yygotominor.yy0->outsource=outsource_expr_expr_GT_expr;
}
#line 3286 "./parser.c"
  yy_destructor(22,&yymsp[-1].minor);
        break;
      case 162:
#line 1446 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="expr ::= expr LT expr.";
    yygotominor.yy0->codegen=codegen_expr_expr_LT_expr;
    yygotominor.yy0->outsource=outsource_expr_expr_LT_expr;
}
#line 3297 "./parser.c"
  yy_destructor(23,&yymsp[-1].minor);
        break;
      case 163:
#line 1453 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="expr ::= expr DOLLAR expr.";
    yygotominor.yy0->codegen=codegen_expr_expr_DOLLAR_expr;
    yygotominor.yy0->outsource=outsource_expr_expr_DOLLAR_expr;
}
#line 3308 "./parser.c"
  yy_destructor(24,&yymsp[-1].minor);
        break;
      case 164:
#line 1460 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="expr ::= expr OR expr.";
    yygotominor.yy0->codegen=codegen_expr_expr_OR_expr;
    yygotominor.yy0->outsource=outsource_expr_expr_OR_expr;
}
#line 3319 "./parser.c"
  yy_destructor(14,&yymsp[-1].minor);
        break;
      case 165:
#line 1467 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(2,yymsp[-2].minor.yy0,yymsp[0].minor.yy0);
    yygotominor.yy0->text="expr ::= expr AND expr.";
    yygotominor.yy0->codegen=codegen_expr_expr_AND_expr;
    yygotominor.yy0->outsource=outsource_expr_expr_AND_expr;
}
#line 3330 "./parser.c"
  yy_destructor(15,&yymsp[-1].minor);
        break;
      case 166:
#line 1474 "./parser.lem"
{
    yygotominor.yy0=(new parsenode)->rule(1,yymsp[0].minor.yy0);
    yygotominor.yy0->text="expr ::= NOT expr.";
    yygotominor.yy0->codegen=codegen_expr_NOT_expr;
    yygotominor.yy0->outsource=outsource_expr_NOT_expr;
}
#line 3341 "./parser.c"
  yy_destructor(16,&yymsp[-1].minor);
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
  ParseARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  YYMINORTYPE yyminor            /* The minor type of the error token */
){
  ParseARG_FETCH;
#define TOKEN (yyminor.yy0)
#line 173 "./parser.lem"

    fprintf(stderr,"Error: syntax error at #line %d %s.\n",
            lexer->getinputlineno(),
            lexer->getinputfspec());

    fflush(0);
    
    //Figyelem:
    //itt a "hivatalos" Lemon interface alá nyúlunk,
    //ami a teljes megértés hiányában könnyen segfault-hoz vezet.
    
    //Parser stack:
    int i;
    fprintf(stderr,"Stack:");
    for(i=1; i<=yypParser->yyidx; i++)
    {
        fprintf(stderr," %s",yyTokenName[yypParser->yystack[i].major]);
        //a parsenode text-je: yypParser->yystack[i].minor.yy0->text
        fflush(0);
    }
    fprintf(stderr,".\n");
    
    //Last input token:
    if( !lexer->geteofflag() )
    {
        fprintf(stderr,"Token: %s (%s).\n",yyTokenName[yymajor],yyminor.yy0->text);
        fflush(0);
    }
    else
    {
        fprintf(stderr,"Token: EOF.\n");
        fflush(0);
    }

    exit(1);

#line 3421 "./parser.c"
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
#line 210 "./parser.lem"

    if(parsing_complete)
    {
        printf("Parsing complete.\n");
    }

#line 3447 "./parser.c"
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "ParseAlloc" which describes the current state of the parser.
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
void Parse(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  ParseTOKENTYPE yyminor       /* The value for the token */
  ParseARG_PDECL               /* Optional %extra_argument parameter */
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
  ParseARG_STORE;

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
