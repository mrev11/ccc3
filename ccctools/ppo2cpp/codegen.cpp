
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

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#include <parsenode.h>
#include <decllist.h>
#include <nodetab.h>
#include <codegen.h>
#include <parser.h>
#include <lexer.h>

extern ppo2cpp_lexer *lexer;

extern FILE *diag;
extern FILE *code;
FILE *src=stdout;

extern void* ParseAlloc(void*(*)(size_t)); 
extern void  ParseFree(void*,void(*)(void*)); 
extern void  ParseTrace(FILE*,const char*); 
extern void  Parse(void*,int,parsenode*);  //3th arg: %token_type {parsenode*} 

#define XNUM_WRITTEN    0 //nem konstans számkifejezés (már ki van írva)
#define XNUM_TOTAL      1 //teljesen kiszámolt számkifejezés
#define XNUM_PARTIAL    2 //részben kiszámolt számkifejezés

#define WRITTEN(f)      (f==XNUM_WRITTEN)
#define TOTAL(f)        (f==XNUM_TOTAL)
#define PARTIAL(f)      (f==XNUM_PARTIAL)

static int tabdepth=0; 
static void nltab(){int i;fprintf(code,"\n");for(i=0;i<tabdepth;i++)fprintf(code,"    ");}
static const char *rtxt(parsenode *p, int x){return p->right[x]->text;}
static int cgen(parsenode *p, int x){return p->right[x]->codegen(p->right[x],0);}
static int cgenv(parsenode *p, int x, void *v){return p->right[x]->codegen(p->right[x],v);}
static void outsrc(parsenode *p,int x){p->right[x]->outsource(p->right[x],0);}
static char *dotsymboltext(parsenode *p);
static char *dot2uln(char *p);

static const char *funcname=""; // az aktuális függvény neve
static int linewritten=0;       // az utoljára kiírt line number
static int loopdepth=0;         // ciklusok mélysége
static int begseqdepth_ret=0;   // begin sequence struktúrák mélysége
static int begseqdepth_loop=0;  // begin sequence struktúrák mélysége
static int starflag=0;          // 0,1,2: jelzi a funcdef([a,]*) típusát
static int argcount=0;          // a függvényargumentumok száma
static int blkflag=0;           // jelzi, hogy kódblokkot fordítunk
static int postfixflag=0;       // postfix függvényhívás jelző

extern int headerflag;          // jelzi, hogy a header-t fordítjuk
extern int parsing_complete;    // Ki kell-e írni a "Parsing complete" szöveget?

static const char *fsep="\n//=======================================================================\n";

extern char *current_namespace;
extern char *inner_namespace;

#define BUFSIZE 1024

//---------------------------------------------------------------------------
static char* dblform(double v)
{
    static char buf[32];
    buf[0]=0;
    if( 8<sprintf(buf,"%.16g",v) &&  0==strchr(buf,'.') )
    {
        strcat(buf,".0");
    }
    return buf;
}

//---------------------------------------------------------------------------
static void paddnum(double v)
{
    //nem kell kiírni, ha v==0
    if( v )
    {
        nltab();fprintf(code,"addnum(%s);",dblform(v));
    }
}

//---------------------------------------------------------------------------
static void pnumber(double v)
{
    nltab();fprintf(code,"number(%s);",dblform(v));
}

//---------------------------------------------------------------------------
static void paddneg(double v)
{
    nltab();fprintf(code,"addneg(%s);",dblform(v));
}

//---------------------------------------------------------------------------
static void pmulnum(double v)
{
    if( v!=1.0 )
    {
        nltab();fprintf(code,"mulnum(%s);",dblform(v));
    }
}

//---------------------------------------------------------------------------
static void sym_eval(parsenode *sym, const char *psr)
{
    //psr: "push"|"push_symbol"|"push_symbol_ref"

    if( sym->cargo & SYM_GLOBSTAT )
    {    
        nltab();
        fprintf(code,"%s(_st_%s_ptr());",psr,sym->text);
        fprintf(code,"//global");
    }

    else if( sym->cargo & SYM_LOCSTAT )
    {
        nltab();
        fprintf(code,"%s(_st_%s.ptr);",psr,sym->text);
        fprintf(code,"//%s",funcname);
    }

    else if( sym->cargo & SYM_LOCAL )
    {
        nltab();
        int idx=0xffff&sym->cargo;
        if( starflag && (idx>=argcount) )
        {
            fprintf(code,"%s(base+argno+%d);",psr,idx-argcount);
        }
        else
        {
            fprintf(code,"%s(base+%d);",psr,idx);
        }
        fprintf(code,"//%s",sym->text);
    }

    else if( sym->cargo & SYM_BLKARG )
    {
        nltab();
        fprintf(code,"%s(base+%d);",psr,0xffff&sym->cargo);
        fprintf(code,"//%s",sym->text);
    }

    else if( sym->cargo & (SYM_BLKSTAT|SYM_BLKLOC) )
    {
        nltab();
        fprintf(code,"%s(env+%d);",psr,0xffff&sym->cargo);
        fprintf(code,"//%s",sym->text);
    }
}

//---------------------------------------------------------------------------
static void sym_assign(parsenode *sym)
{
    if( sym->cargo & SYM_GLOBSTAT )
    {
        nltab();
        fprintf(code,"assign(_st_%s_ptr());",sym->text);
        fprintf(code,"//global");
    }

    else if( sym->cargo & SYM_LOCSTAT )
    {
        nltab();
        fprintf(code,"assign(_st_%s.ptr);",sym->text);
        fprintf(code,"//%s",funcname);
    }

    else if( sym->cargo & SYM_LOCAL )
    {
        nltab();
        int idx=0xffff&sym->cargo;
        if( starflag && (idx>=argcount) )
        {
            fprintf(code,"assign(base+argno+%d);",idx-argcount);
        }
        else
        {
            fprintf(code,"assign(base+%d);",idx);
        }
        fprintf(code,"//%s",sym->text);
    }

    else if( sym->cargo & SYM_BLKARG )
    {
        nltab();
        fprintf(code,"assign(base+%d);",sym->cargo&0xffff);
        fprintf(code,"//%s",sym->text);
    }

    else //block környezet (SYM_BLKSTAT|SYM_BLKLOC)
    {
        nltab();
        fprintf(code,"assign(env+%d);",sym->cargo&0xffff);
        fprintf(code,"//%s",sym->text);
    }
}

//---------------------------------------------------------------------------
static void illegal_lvalue(parsenode *p)
{
    fprintf(stderr,"Error: illegal lvalue at #line %d %s (%s)\n",
            p->lineno?p->lineno:lexer->getinputlineno(),
            lexer->getinputfspec(),
            p->text);
    exit(1);
}

//---------------------------------------------------------------------------
static void lvalue(parsenode *p)
{
    if( p->codegen==codegen_expr_SYMBOL )
    {
        sym_assign(p->right[0]);
    }

    else if( p->codegen==codegen_expr_expr_LBRACKET_expr_RBRACKET )
    {
        double x;
        cgen(p,0);  //expr(array)
        int f=cgenv(p,1,&x); //expr(index)
        
        if( TOTAL(f) )
        {
            nltab();fprintf(code,"assign2(idxxl0(%.16g));",x);
        }
        else if( PARTIAL(f) )
        {
            paddnum(x);
            nltab();fprintf(code,"assign2(idxxl());");
        }
        if( WRITTEN(f) )
        {
            nltab();fprintf(code,"assign2(idxxl());");
        }
    }

    else if( p->codegen==codegen_expr_SYMBOL_ARROW_SYMBOL )
    {
        char fldref[BUFSIZE];
        sprintf(fldref,"%s->%s",rtxt(p,0),rtxt(p,1));
        flddecl_insert(fldref);
        nltab();fprintf(code,"_ef_%s_%s.fput();",rtxt(p,0),rtxt(p,1));
    }

    else if( p->codegen==codegen_expr_LPAR_lexpr_RPAR )
    {
        parsenode *r=p->right[0];
        if( r->codegen==codegen_lexpr_expr )
        {
            lvalue(r->right[0]); //rekurzió!
        }
        else
        {
            illegal_lvalue(r);
        }
    }

    else if( p->codegen==codegen_expr_expr_COLON_SYMBOL_msgpar &&
             p->right[2]->codegen==codegen_msgpar )
    {
        cgen(p,0);
        nltab();fprintf(code,"swap();");

        const char *meth=p->right[1]->text;
        int argc=2; //p->right[2]->cargo+1;
        metdecl_insert(meth,0,0);
        nltab();fprintf(code,"_o_method_%s.eval(%d);",meth,argc);
    }

    else if( p->codegen==codegen_expr_expr_COLON_LPAR_dotsymbol_RPAR_SYMBOL_msgpar &&
             p->right[3]->codegen==codegen_msgpar )
    {
        cgen(p,0);
        nltab();fprintf(code,"swap();");

        char *cls=dotsymboltext(p->right[1]); //p->right[1]->text;
        const char *meth=p->right[2]->text;
        int argc=2; //p->right[3]->cargo+1;
        metdecl_insert(meth,0,cls);
        nltab();fprintf(code,"_o_method_%s_C_%s.eval(%d);",meth,dot2uln(cls),argc);
        free(cls); 
    }

    else if( p->codegen==codegen_expr_expr_COLON_LPAR_dotsymbol_AT_dotsymbol_RPAR_SYMBOL_msgpar &&
             p->right[4]->codegen==codegen_msgpar )
    {
        cgen(p,0);
        nltab();fprintf(code,"swap();");

        char *parent=dotsymboltext(p->right[1]); //p->right[1]->text;
        char *cls=dotsymboltext(p->right[2]); //p->right[2]->text;
        const char *meth=p->right[3]->text;
        int argc=2; //p->right[4]->cargo+1;
        metdecl_insert(meth,parent,cls);
        if( 0==strcmp(parent,"super") )
        {
            nltab();fprintf(code,"_o_method_%s_S_%s.eval(%d);",meth,dot2uln(cls),argc);
        }
        else
        {
            nltab();fprintf(code,"_o_method_%s_P_%s_C_%s.eval(%d);",meth,dot2uln(parent),dot2uln(cls),argc);
        }
        free(parent);
        free(cls);
    }

    else if( p->codegen==codegen_expr_LBRACE_lfuncpar_RBRACE )
    {
        //lfuncpar ::=.
        //lfuncpar ::= parexpr.
        //lfuncpar ::= lfuncpar0 COMMA parexpr0.
        //lfuncpar0 ::= parexpr0.
        //lfuncpar0 ::= lfuncpar0 COMMA parexpr0.
        //parexpr0 ::=.
        //parexpr0 ::= parexpr.
        //parexpr ::= expr.
        //parexpr ::= STAR.
        //parexpr ::= STAR LBRACKET parexpr0 DOTDOT parexpr0 RBRACKET.
        //parexpr ::= AT SYMBOL.

        //fprintf(code,"\n//LINE %d %d",p->lineno,lexer->getinputlineno());

        parsenode *q=p->right[0]; // lfuncpar
        while( q->cargo>=1 ) //amig a lista el nem fogy
        {
            //fprintf(code,"\n//DBG(len=%d) %-40s",q->cargo,q->text);

            parsenode *x=0;

            if( q->codegen==codegen_lfuncpar_lfuncpar0_COMMA_parexpr0 )
            {
                //fprintf(code,"  >>codegen_lfuncpar_lfuncpar0_COMMA_parexpr0 ");
                x=q->right[1];
            }                              
            else if( q->codegen==codegen_lfuncpar0_lfuncpar0_COMMA_parexpr0 )
            {                              
                //fprintf(code,"  >>codegen_lfuncpar0_lfuncpar0_COMMA_parexpr0");
                x=q->right[1];
            }                              
            else if( q->codegen==codegen_lfuncpar0_parexpr0 )
            {                              
                //fprintf(code,"  >>codegen_lfuncpar0_parexpr0");
                x=q->right[0];
            }
            else if( q->codegen==codegen_lfuncpar_parexpr )
            {                              
                //fprintf(code,"  >>codegen_lfuncpar_parexpr");
                x=q->right[0];
            }
            
            //most x: parexpr vagy parexpr0
            if( x->codegen==codegen_parexpr0_parexpr )
            {
                x=x->right[0];
            }

            x->lineno=p->lineno;

            //most x: parexpr (vagy hibas parexpr0)
            if( x->codegen!=codegen_parexpr_expr )
            {
                illegal_lvalue(x);
            }
            x=x->right[0];
            //most x: expr (ami lehet lvalue, de nem biztosan az) 

            //fprintf(code," >>> %s ",x->text);
            
            
            nltab();fprintf(code,"dup();");
            nltab();fprintf(code,"idxr0nil(%d);",q->cargo);
            lvalue(x);
            nltab();fprintf(code,"pop();");

            q=q->right[0];
        }
    }

    else
    {
        illegal_lvalue(p);
    }
}

//---------------------------------------------------------------------------
static void blkenv(parsenode *p)
{
    //Kigyűjti a block környezeti változóit.
    //A változók offsetét nem változtatja.
    //Az offset az eredeti függvény stackjére relatív.
    //Az offset-tel az eredeti függvényben címezhetők a változók.

    if( p->right )
    {
        int i=0;
        while( p->right[i] )
        {
            blkenv(p->right[i]);
            ++i;
        }
    }
    else if( p->tokenid==SYMBOL )
    {
        if( p->cargo & (SYM_BLKSTAT|SYM_BLKLOC) )
        {
            nodetab_blkenv->add1(p);
        }
    }
}

//---------------------------------------------------------------------------
static void blkenvx(parsenode *p)
{
    //Kigyűjti a block környezeti változóit.
    //A változók offsetét átírja.
    //Az új offset a blkenv-re relatív.
    //Az offset-tel a blockban címezhetők a változók.

    if( p->right )
    {
        int i=0;
        while( p->right[i] )
        {
            blkenvx(p->right[i]);
            ++i;
        }
    }
    else if( p->tokenid==SYMBOL )
    {
        if( p->cargo & (SYM_BLKSTAT|SYM_BLKLOC) )
        {
            p->cargo&=0xffff0000;
            p->cargo|=nodetab_blkenv->add1(p); //új offset
        }
    }
}

//---------------------------------------------------------------------------
static void blkcode(nodetab *t,int x)
{
    // base+0  a blokk vartab indexe
    // base+1  első argumentum
    // base+2  második argumentum
    // stb.
    
    blkflag=1;
    
    parsenode *p=(parsenode*)(t->get(x));
    parsenode *bargument=p->right[0];
    parsenode *lexpr=p->right[1];
    parsenode *funcall=0;

    //fprintf(code,"\n//%s",p->text);
    //fprintf(code,"\n//%s",bargument->text);
    //fprintf(code,"\n//%s",lexpr->text);
    
    int blkarg=bargument->cargo; //blk és '*' nincs benne
    int blkoptim=0; //jelzi a {|*|funcall(*)} alakot
    int blkstar=0;  //jelzi a típust, 0=|a|, 1=|*|, 2=|a,*|
    int blkforw=0;  //jelzi a {|this,*|this:a:b:c(*[2..])} alakot

    if( bargument->codegen==codegen_bargument_STAR )
    {
        blkstar=1; 
    }
    else if( bargument->codegen==codegen_bargument_lbarg_COMMA_STAR )
    {
        blkstar=2; 

        //{|this,*|this:a:b:c(*[2..])} alak keresése
        const char *sym;
        parsenode *p=bargument;
        p=p->right[0]; //lbarg
        if( p->codegen==codegen_lbarg_SYMBOL )
        {
            //fprintf(code,"\n//%s",p->text);
            p=p->right[0]; //SYMBOL
            //fprintf(code,"\n//%s",p->text);
            sym=p->text;
            
            p=lexpr;
            if( p->codegen==codegen_lexpr_expr  )
            {
                int forw=0;
                int mpar=0;
                p=p->right[0];

                if( p->codegen==codegen_expr_expr_COLON_SYMBOL_msgpar )
                {
                    parsenode *p1=p->right[2];
                    //fprintf(code,"\n///%s",p1->text);
                    if( p1->codegen==codegen_msgpar_LPAR_lfuncpar_RPAR  )
                    {
                        p1=p1->right[0];
                        //fprintf(code,"\n///%s",p1->text);
                        if( p1->codegen==codegen_lfuncpar_parexpr )
                        {
                            p1=p1->right[0];
                            //fprintf(code,"\n///%s",p1->text);
                            if( p1->codegen==codegen_parexpr_STAR_LBRACKET_parexpr0_DOTDOT_parexpr0_RBRACKET )
                            {
                                //fprintf(code,"\n//%s",p1->right[0]->text);
                                //fprintf(code,"\n//%s",p1->right[1]->text);

                                if( p1->right[0]->codegen==codegen_parexpr0_parexpr &&
                                    p1->right[1]->codegen==codegen_parexpr0 )
                                {
                                    p1=p1->right[0]->right[0];
                                    //fprintf(code,"\n///%s",p1->text);
                                    
                                    if( p1->codegen==codegen_parexpr_expr )
                                    {
                                        p1=p1->right[0];
                                        //fprintf(code,"\n///%s",p1->text);
                                        if( p1->codegen==codegen_expr_NUMBER )
                                        {
                                            p1=p1->right[0];
                                            //fprintf(code,"\n///%s",p1->text);
                                            if( 0==strcmp(p1->text,"2") )
                                            {
                                                //fprintf(code,"\n//*[2..] msgpar detected");
                                                mpar=1;
                                                forw=1;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                p=p->right[0];
                //fprintf(code,"\n//%s",p->text);

                while( mpar &&  p->codegen==codegen_expr_expr_COLON_SYMBOL_msgpar )
                {
                    if( p->right[2]->codegen!=codegen_msgpar )
                    {
                        mpar=0;
                    }
                    forw++;
                    p=p->right[0];
                    //fprintf(code,"\n//%s",p->text);
                }

                if( mpar && p->codegen==codegen_expr_SYMBOL )
                {
                    p=p->right[0];
                    if( 0==strcmp(p->text,sym) )
                    {
                        blkforw=forw; 
                        //{|this,*|this:a:b:c(*[2..])} alak detektálva
                        //fprintf(code,"\n//blkforw %d",blkforw);
                    }
                }
            }
        }
        //{|this,*|this:a:b:c(*[2..])} alak <==> blkforw>0
    }


    if( lexpr->codegen==codegen_lexpr_expr )
    {
        parsenode *expr=lexpr->right[0];
        //fprintf(code,"\n//%s",expr->text);
        if( expr->codegen==codegen_expr_ddotsymbol_LPAR_lfuncpar_RPAR )
        {
            parsenode *lfuncpar=expr->right[1];
            //fprintf(code,"\n//%s",lfuncpar->text);
            if( lfuncpar->codegen==codegen_lfuncpar_parexpr )
            {
                parsenode *parexpr=lfuncpar->right[0];
                //fprintf(code,"\n//%s",parexpr->text);
                if( parexpr->codegen==codegen_parexpr_STAR)
                {
                    blkoptim=(blkstar==1);
                    funcall=expr;
                }
            }
        }
    }

    //fprintf(code,"\n//blkarg=%d, blkstar=%d, blkoptim=%d",
    //                  blkarg,    blkstar,    blkoptim);

    if( blkoptim )
    {
        // {|*|funcname(*)}
        //
        // alakú kódblokk,
        // speciálisan fordítjuk,
        // közvetlen függvényhívás,
        // minden paraméter automatikusan továbbadva,
        // a paraméterek nincsenek átpakkolva,
        // a refek megmaradnak.

        //p->tprint();

        fprintf(code,"\n\nstatic void _blk_%s_%d(int argno)\n{\n//",funcname,x);
        char *fname=dotsymboltext(funcall->right[0]);
        char *fcall=fundecl_clpcall(fname);
        tabdepth=1;
        nltab();fprintf(code,"%s(argno-1);",fcall);
        tabdepth=0;
        free(fname);
        free(fcall);
        fprintf(code,"\n//\n*(stack-2)=*(stack-1);pop();\n}");
    }
    else if( blkforw )
    {
        // {|this,*|this:a:b:c(*[2..])} tipus

        fprintf(code,"\n\nstatic void _blk_%s_%d(int argno)\n{\n",funcname,x);
        if( blkforw>1 )
        {
            fprintf(code,"VALUE *base=stack-argno;\n");
        }
        fprintf(code,"//");

        //p->tprint();                 fprintf(code,"\n//%s",p->text);
        parsenode *p1=p->right[1];   //fprintf(code,"\n//%s",p1->text);  //lexpr ::= expr.
        parsenode *p2=p1->right[0];  //fprintf(code,"\n//%s",p2->text);  //expr ::= expr COLON SYMBOL msgpar.
        parsenode *p3=p2->right[0];  //fprintf(code,"\n//%s",p3->text);  //expr ::= expr COLON SYMBOL msgpar.

        tabdepth=1;

        if( blkforw>1 )
        {
            //this:a:...:c(*[2..]) eset 
            p1->right[0]=p3;    
            cgen(p,1); //kiértékelve 'this:a:...' (de :c kihagyva)
            nltab();fprintf(code,"*(base+1)=*TOP();");
            nltab();fprintf(code,"pop();");
        }
        else
        {
            //this:a(*[2..]) eset, ok
        }

        const char *meth=p2->right[1]->text;
        metdecl_insert(meth,0,0);
        nltab();fprintf(code,"_o_method_%s.eval(argno-1);",meth);

        tabdepth=0;
        fprintf(code,"\n//\n*(stack-2)=*(stack-1);pop();\n}");
    }
    else  //általános eset
    {
        fprintf(code,"\n\nstatic void _blk_%s_%d(int argno)\n{",funcname,x);
        fprintf(code,"\nVALUE *base=stack-argno;");

        nodetab_blkenv->clean();
        blkenvx(lexpr); //összegyűjti lexpr szimbólumait
        if( nodetab_blkenv->top>0 )
        {
            fprintf(code,"\nVALUE *env=blkenv(base);");
        }

        if( blkstar==0 )
        {
            fprintf(code,"\nstack=base+min(argno,%d);",1+blkarg); //blk+args
            fprintf(code,"\nwhile(stack<base+%d)PUSHNIL();",1+blkarg);
            fprintf(code,"\nargno=%d;",1+blkarg); //blk+args
        }
        else if( blkstar==1 )
        {
            //argno
        }
        else
        {
            fprintf(code,"\nwhile(stack<base+%d)PUSHNIL();",1+blkarg);
            fprintf(code,"\nargno=max(argno,%d);",1+blkarg); //blk+args
        }

        char ns[BUFSIZE]="";
        if(current_namespace){strcat(ns,current_namespace);strcat(ns,".");}
        if(inner_namespace){strcat(ns,inner_namespace);strcat(ns,".");}
        fprintf(code,"\npush_call(\"%s_blk_%s_%d\",base);\n//",ns,funcname,x);

        tabdepth=1;
        cgen(p,1);
        tabdepth=0;

        if( lexpr->cargo>0 ) //nem üres lista
        {
            fprintf(code,"\n//\n{*base=*(stack-1);stack=base+1;pop_call();}\n}");
        }
        else
        {
            fprintf(code,"\n//\nstack=base;\npush(&NIL);\npop_call();\n}");
        }
        nodetab_blkenv->clean();
    }
    blkflag=0;
    return;
}

//---------------------------------------------------------------------------
static int labelnext()
{
    static int lab=0;
    return ++lab;
}

//---------------------------------------------------------------------------
static int label(int op)
{
    static int labstack[BUFSIZE]; // ciklusok max mélysége
    static int labidx=0;      // cilusok aktuális mélysége

    if( op>0 )
    {
        labstack[++labidx]=labelnext();
    }
    else if( op<0 )
    {
        labidx--;
    }
    return labstack[labidx];
}

//---------------------------------------------------------------------------
#ifdef NOT_DEFINED
static char *dotsymboltext(parsenode *p)  // sym1.sym2.sym3
{
    char tmp[BUFSIZE];tmp[0]=0;
    char buf[BUFSIZE];buf[0]=0;
    while( p->codegen!=codegen_dotsymbol_SYMBOL )
    {
        strcpy(tmp,buf);
        sprintf(buf,".%s%s",rtxt(p,1),tmp);
        p=p->right[0];
    }
    strcpy(tmp,buf);
    sprintf(buf,"%s%s",rtxt(p,0),tmp);
    return strdup(buf);
}
#endif

//---------------------------------------------------------------------------
static char *dotsymboltext(parsenode *p)  // [.]sym1.sym2.sym3
{
    char tmp[BUFSIZE]={0};
    char buf[BUFSIZE]={0};
    char dot[2]={0,0};

    while(1)
    {
        strcpy(tmp,buf);
        if( p->codegen==codegen_dotsymbol_SYMBOL )
        {
            sprintf(buf,"%s%s%s",dot,rtxt(p,0),tmp);
            break;
        }
        else if( p->codegen==codegen_dotsymbol_dotsymbol_DOT_SYMBOL )
        {
            sprintf(buf,".%s%s",rtxt(p,1),tmp);
            p=p->right[0];
        }
        else if( p->codegen==codegen_ddotsymbol_dotsymbol )
        {
            p=p->right[0];
        }
        else if( p->codegen==codegen_ddotsymbol_DOT_dotsymbol )
        {
            dot[0]='.';
            p=p->right[0];
        }
    }
    return strdup(buf);
}

//---------------------------------------------------------------------------
static char *dot2uln(char *str)
{
    char *p=str;
    while(*p){if(*p=='.')*p='_';p++;}
    return str;
}

//---------------------------------------------------------------------------
static int dotlast(const char *txt)
{
    int i,ldot=0;
    for(i=0; txt[i]; i++)
    {
        if( txt[i]=='.' )
        {
            ldot=i;
        }
    }
    return ldot;
}


//---------------------------------------------------------------------------
static void widestring(const char *us)
{
    unsigned ulen=strlen(us);
    unsigned wlen=0;
    wchar_t *ws=utf8_to_wchar(us,ulen,&wlen);
    unsigned i;
    for( i=0; i<wlen; i++ )
    {
        if( ws[i]<128  )
        {
            fprintf(code,"%c",ws[i]);
        }
        else
        {
            fprintf(code,"\\u%04x",(unsigned)ws[i]);
        }
    }
    free(ws);
}

//---------------------------------------------------------------------------
static void codeblock_required(parsenode *p)
{
    fprintf(stderr,"Error: codeblock required at #line %d %s (%s)\n",
            p->lineno?p->lineno:lexer->getinputlineno(),
            lexer->getinputfspec(),
            p->text);
    exit(1);
}

//---------------------------------------------------------------------------
static void multiple_using(parsenode *p)
{
    fprintf(stderr,"Error: multiple using symbol at #line %d %s (%s)\n",
            p->lineno?p->lineno:lexer->getinputlineno(),
            lexer->getinputfspec(),
            dotsymboltext(p));
    exit(1);
}

//---------------------------------------------------------------------------
static void no_loop_in_sight(parsenode *p)
{
    fprintf(stderr,"Error: no loop in sight at #line %d %s (%s)\n",
            p->lineno?p->lineno:lexer->getinputlineno(),
            lexer->getinputfspec(),
            p->text);
    exit(1);
}

//---------------------------------------------------------------------------
static void function_call_expected(parsenode *p)
{
    //Ellenorzi,
    //hogy fuggvenyhivassal kezdodik-e 
    //a :: es ::= operatorok jobboldalan levo kifejezes

    parsenode *q=p->right[1];
    while( q && q->codegen!=codegen_expr_ddotsymbol_LPAR_lfuncpar_RPAR )
    {
        //fprintf(code,"\n/*%s*/", q->text); fflush(0);
        q=q->right ? q->right[0]:0;
    }
    if( q )
    {
        //fprintf(code,"\n/*%s*/", q->text); fflush(0);
        return;
    }

    fprintf(stderr,"Error: function call required at #line %d %s (%s)\n",
            p->lineno?p->lineno:lexer->getinputlineno(),
            lexer->getinputfspec(),
            p->text);
    exit(1);
}


//---------------------------------------------------------------------------
static void cmp_chain( parsenode *p, const char *op)
{
    cgen(p,0);
    cgen(p,1);

    int cmplabel=p->nodeid;

    // parsenode *r0=p->right[0];
    // parsenode *r1=p->right[1];
    // printf("p   nodeid=%2x cargo=%d %s\n",  p->nodeid,  p->cargo,  p->text);
    // printf("r0  nodeid=%2x cargo=%d %s\n", r0->nodeid, r0->cargo, r0->text);
    // printf("r1  nodeid=%2x cargo=%d %s\n", r1->nodeid, r1->cargo, r1->text);
    // printf("\n");

    if( p->cargo )
    {
        nltab();fprintf(code,"%s();",op);
        nltab();fprintf(code,"cmp_%d:;",cmplabel);
    }
    else
    {
        nltab();fprintf(code,"dup();");
        nltab();fprintf(code,"*TOP2()=*TOP3();");
        nltab();fprintf(code,"*TOP3()=*TOP();");
        nltab();fprintf(code,"%s();",op);
        nltab();fprintf(code,"if(!TOP()->data.flag){swap();pop();goto cmp_%d;}",cmplabel);
        nltab();fprintf(code,"pop();");
    }
}

//---------------------------------------------------------------------------
//codegen functions
//---------------------------------------------------------------------------
int codegen_prg_header_lfunction(parsenode *p,void *v)//PROTO
{
    delete p->right[0];
    delete p->right[1];
    fprintf(diag,"parsenode constructed: %d\n",parsenode::cnt_constructor);
    fprintf(diag,"parsenode destructed: %d\n",parsenode::cnt_destructor);
    parsenode::walk();
    return 0;
}

//---------------------------------------------------------------------------
int codegen_header_lnewline0_namespace_lusing_lstatdefin_clang(parsenode *p,void *v)//PROTO
{
    cgen(p,3); // lstatdefin
    cgen(p,4); // clang

    int i;
    for(i=0; i<nodetab_block->top; i++)
    {
        blkcode(nodetab_block,i);
    }

    fprintf(code,"%s",fsep);

    nodetab_block->clean();    //a headerben definiált codeblockok

    return 0;
}

//---------------------------------------------------------------------------
int codegen_namespace(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_namespace_NAMESPACE_dotsymbol_nsalias_ldotsymbol_lnewline(parsenode *p,void *v)//PROTO
//                              0         1       2          3
{
    extern char*current_namespace;
    current_namespace=dotsymboltext(p->right[0]);
    if( p->right[1]->codegen==codegen_nsalias_EQ_SYMBOL )
    {
        const char *nsalias=rtxt(p->right[1],0);
        fundecl_setalias(current_namespace,nsalias);
    }
    parsenode *s=p->right[2];
    while( s->codegen==codegen_ldotsymbol_ldotsymbol_dotsymbol )
    {
        char *dsymtxt=dotsymboltext(s->right[1]);
        if( !fundecl_using(dsymtxt,current_namespace) )
        {
            multiple_using(s->right[1]);
        }
        free(dsymtxt);
        s=s->right[0];
    }
    return 0;
}

//---------------------------------------------------------------------------
int codegen_lusing(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_lusing_lusing_using(parsenode *p,void *v)//PROTO
{
    return 0;
}


//---------------------------------------------------------------------------
int codegen_using_USING_dotsymbol_nsalias_ldotsymbol_lnewline(parsenode *p,void *v)//PROTO
//                      0         1       2          3
{
    char *nsusing=dotsymboltext(p->right[0]);
    if( p->right[1]->codegen==codegen_nsalias_EQ_SYMBOL )
    {
        const char *nsalias=rtxt(p->right[1],0);
        fundecl_setalias(nsusing,nsalias);
    }
    parsenode *s=p->right[2];
    while( s->codegen==codegen_ldotsymbol_ldotsymbol_dotsymbol )
    {
        char *dsymtxt=dotsymboltext(s->right[1]);
        if( !fundecl_using(dsymtxt,nsusing) )
        {
            multiple_using(s->right[1]);
        }
        free(dsymtxt);
        s=s->right[0];
    }
    free(nsusing);
    return 0;
}


//---------------------------------------------------------------------------
int codegen_nsalias(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_nsalias_EQ_SYMBOL(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_dotsymbol_SYMBOL(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_dotsymbol_dotsymbol_DOT_SYMBOL(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_ldotsymbol(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_ldotsymbol_ldotsymbol_dotsymbol(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_ddotsymbol_dotsymbol(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_ddotsymbol_DOT_dotsymbol(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_lstatdefin(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_lstatdefin_lstatdefin_STATIC_statdefin_lnewline(parsenode *p,void *v)//PROTO 
{
    cgen(p,0); //lstatdefin
    cgen(p,1); //statdefin
    cgen(p,2); //newline
    return 0;
}

//---------------------------------------------------------------------------
int codegen_statdefin_statdef(parsenode *p,void *v)//PROTO 
{
    cgen(p,0);
    return 0;
}
 
//---------------------------------------------------------------------------
int codegen_statdefin_statdefin_COMMA_statdef(parsenode *p,void *v)//PROTO 
{
    cgen(p,0);
    cgen(p,1);
    return 0;
}
 
//---------------------------------------------------------------------------
int codegen_statdef_SYMBOL(parsenode *p,void *v)//PROTO 
{
    parsenode *sym=p->right[0];

    //a CCC szinten külső változót C szinten belsővé tesszük
    if( sym->cargo & SYM_GLOBSTAT )
    {
        nltab();fprintf(code,"static VALUE* _st_%s_ptr()",sym->text);
        nltab();fprintf(code,"{");
        tabdepth++;
    }

    nltab();fprintf(code,"static stvar _st_%s;",sym->text);

    //a CCC szinten külső változót C szinten belsővé tesszük
    if( sym->cargo & SYM_GLOBSTAT )
    {
        nltab();fprintf(code,"return _st_%s.ptr;",sym->text);
        tabdepth--;
        nltab();fprintf(code,"}");
    }

    return 0;
}

//---------------------------------------------------------------------------
int codegen_statdef_SYMBOL_ASSIGN_expr(parsenode *p,void *v)//PROTO 
{
    parsenode *sym=p->right[0];
    parsenode *expr=p->right[1];
    parsenode *expr1=expr->right[0];
    
    //a CCC szinten külső változót C szinten belsővé tesszük
    //(burkoló függvény eleje)
    if( sym->cargo & SYM_GLOBSTAT )
    {
        nltab();fprintf(code,"static VALUE* _st_%s_ptr()",sym->text);
        nltab();fprintf(code,"{");
        tabdepth++;
    }

    if( expr->codegen==codegen_expr_NIL )
    {
        nltab();fprintf(code,"static stvar _st_%s(&NIL);",sym->text);
    }
    else if( expr->codegen==codegen_expr_NUMBER )
    {
        nltab();fprintf(code,"static stvar _st_%s((double)%s);",sym->text,expr1->text);
    }
    else if( expr->codegen==codegen_expr_STRING )
    {
        nltab();
        fprintf(code,"static stvar _st_%s(L",sym->text);
        widestring(expr1->text);
        fprintf(code,");");
    }
    else if( expr->codegen==codegen_expr_NLSTEXT )
    {
        nltab();
        fprintf(code,"static stvar _st_%s(nls_text(L",sym->text);
        widestring(expr1->text);
        fprintf(code,"));");
    }
    else if( expr->codegen==codegen_expr_TRUE )
    {
        nltab();fprintf(code,"static stvar _st_%s(&TRUE);",sym->text);
    }
    else if( expr->codegen==codegen_expr_FALSE )
    {
        nltab();fprintf(code,"static stvar _st_%s(&FALSE);",sym->text);
    }
    else
    {
        nltab();fprintf(code,"static stvar _st_%s;",sym->text);
        nltab();fprintf(code,"static int _ini_%s=[=](){",sym->text);
        tabdepth++;
        cgen(p,1);
        nltab();fprintf(code,"assign(_st_%s.ptr);",rtxt(p,0));
        nltab();fprintf(code,"pop();");
        nltab();fprintf(code,"return 1;");
        tabdepth--;
        nltab();fprintf(code,"}();");
    }

    //a CCC szinten külső változót C szinten belsővé tesszük
    //(burkoló függvény vége)
    if( sym->cargo & SYM_GLOBSTAT )
    {
        nltab();fprintf(code,"return _st_%s.ptr;",sym->text);
        tabdepth--;
        nltab();fprintf(code,"}");
    }

    return 0;
}

//---------------------------------------------------------------------------
int codegen_clang(parsenode *p,void *v)//PROTO  
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_clang_CLANG(parsenode *p,void *v)//PROTO  
{
    namespace_end(current_namespace,code); //global ns
    fprintf(code,"\n\n");
    fprintf(code,"//CLANG");
    fprintf(code,"%s",rtxt(p,0));
    fprintf(code,"//CEND");
    fprintf(code,"\n");
    namespace_begin(current_namespace,code); //restore ns
    return 0;
}

//---------------------------------------------------------------------------
int codegen_lfunction_function(parsenode *p,void *v)//PROTO  
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_lfunction_lfunction_function(parsenode *p,void *v)//PROTO  
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_function_classid_LPAR_ldsym_RPAR_newspec_lnewline_lslot(parsenode *p,void *v)//PROTO
//                   0            1          2                3

#define  CLID_EXTERNAL  //clid külső static változóban
#define  NEW_CPPLEVEL   //C++ szintű (gyorsított) new

{
    //p->tprint();
    
    char curnsp[256]; curnsp[0]=0; //name.space.prefix.
    if( current_namespace )
    {
        sprintf(curnsp,"%s.",current_namespace);
    }

    char *classid=dotsymboltext(p->right[0]->right[0]);
    char *classidid=dot2uln(strdup(classid));

    const char *static_modifier="";
    if( p->right[0]->codegen==codegen_classid_STCLASS_dotsymbol )
    {
        static_modifier="static ";
    }

    const char *newspec=0;
    parsenode *newnode=p->right[2];
    if( newnode->codegen==codegen_newspec )
    {
        newspec="new"; //default
    }
    else if( newnode->codegen==codegen_newspec_NEW_COLON )
    {
        newspec=0; //nincs new
    }
    else if( newnode->codegen==codegen_newspec_NEW_COLON_SYMBOL )
    {
        newspec=newnode->right[0]->text;
    }

    char class_file[256];
    sprintf(class_file,"class_%s%s.tmp",curnsp,classid);
    FILE *cls=fopen(class_file,"w");

#ifdef   CLID_EXTERNAL
    fprintf(cls,"static clid_%s:=%sRegister()\n\n",classidid,classid);
    fprintf(cls,"%sfunction %sClass()\n",static_modifier,classid);
    fprintf(cls,"return clid_%s\n\n",classidid);
    #ifndef  NEW_CPPLEVEL    
    if( newspec )
    {
        fprintf(cls,"%sfunction %s%s(*)\n",static_modifier,classid,newspec);
        fprintf(cls,"return objectNew(clid_%s):initialize(*)\n\n",classidid);
    }
    #endif //NEW_CPPLEVEL
#else  //CLID_EXTERNAL
    fprintf(cls,"%sfunction %sClass()\n",static_modifier,classid);
    fprintf(cls,"static clid_%s:=%sRegister()\n",classidid,classid);
    fprintf(cls,"return clid_%s\n\n",classidid);
    #ifndef  NEW_CPPLEVEL    
    if( newspec )
    {
        fprintf(cls,"%sfunction %s%s(*)\n",static_modifier,classid,newspec);
        fprintf(cls,"return objectNew(%sClass()):initialize(*)\n\n",classidid);
    }
    #endif //NEW_CPPLEVEL
#endif //CLID_EXTERNAL

    //baseclasses
    parsenode *lsym=p->right[1];
    int number_of_baseclasses=lsym->cargo;
    parsenode **baseclass=(parsenode**)malloc((number_of_baseclasses+1)*sizeof(void*));
    int i=0;
    while( ++i<number_of_baseclasses )
    {
        baseclass[number_of_baseclasses-i]=lsym->right[1];
        lsym=lsym->right[0];
    }
    baseclass[number_of_baseclasses-i]=lsym->right[0];

    fprintf(cls,"static function %sRegister()\n",classid);
    fprintf(cls,"local clid:=classRegister(\"%s%s\",{",curnsp,classid);

    for(i=0; i<number_of_baseclasses; i++ )
    {
        char *b=dotsymboltext(baseclass[i]);
        fprintf(cls,"%s.%sClass()",i==0?"":",",b);
        free(b);
    }
    fprintf(cls,"})\n");
    free(baseclass);


    //attribs and methods
    parsenode *lslot=p->right[3];
    int number_of_slots=lslot->cargo;
    parsenode **slot=0;

    if( number_of_slots>0 )
    {
        slot=(parsenode**)malloc((number_of_slots+1)*sizeof(void*));
        i=0;
        while( ++i<=number_of_slots )
        {
            slot[number_of_slots-i]=lslot->right[1];
            lslot=lslot->right[0];
        }
    
        for(i=0; i<number_of_slots; i++ )
        {
            if( slot[i]->codegen==codegen_slot_ATTRIB_SYMBOL )
            {
                const char *attr=slot[i]->right[0]->text;
                fprintf(cls,"classAttrib(clid,\"%s\")\n",attr);
            }
            if( slot[i]->codegen==codegen_slot_METHOD_SYMBOL )
            {
                const char *meth=slot[i]->right[0]->text;
                fprintf(cls,"classMethod(clid,\"%s\",{|*|%s%s.%s(*)})\n",meth,curnsp,classid,meth);
            }
            if( slot[i]->codegen==codegen_slot_METHOD_SYMBOL_forw )
            {
                const char *meth=slot[i]->right[0]->text;
                const char *buf[64]; int bx=0;
                parsenode *p=slot[i]->right[1];
                while( p->codegen==codegen_forw_forw_COLON_SYMBOL  )
                {
                    buf[bx++]=p->right[1]->text;
                    p=p->right[0];
                }
                if( p->codegen==codegen_forw_COLON_SYMBOL  )
                {
                    buf[bx++]=p->right[0]->text;
                }
                fprintf(cls,"classMethod(clid,\"%s\",",meth);
                fprintf(cls,"{|this,*|this");
                for(bx--; bx>=0; bx--)
                {
                    fprintf(cls,":%s",buf[bx]);
                }
                fprintf(cls,"(*[2..])})\n");fflush(0);
            }
            if( slot[i]->codegen==codegen_slot_METHOD_SYMBOL_expr )
            {
                if( slot[i]->right[1]->codegen!=codegen_expr_LBRACE_PIPE_bargument_PIPE_lexpr_RBRACE  &&
                    slot[i]->right[1]->codegen!=codegen_expr_LPAR_PIPE_bargument_PIPE_lexpr_RPAR       )
                {
                    const char *meth=slot[i]->right[0]->text;
                    fprintf(cls,"classMethod(clid,\"%s\",",meth);
                    src=cls;
                    fprintf(cls,"{||");
                    outsrc(slot[i],1);
                    src=0;
                    fprintf(cls,"})\n");
                }
                else
                {
                    const char *meth=slot[i]->right[0]->text;
                    fprintf(cls,"classMethod(clid,\"%s\",",meth);
                    src=cls;
                    outsrc(slot[i],1);
                    src=0;
                    fprintf(cls,")\n");
                }
            }
        }
        free(slot);
    }
    fprintf(cls,"return clid\n\n");
    fclose(cls);


    //Idáig az történt, hogy kiírtuk az osztály
    //definícióját (metódusok nélkül) egy tmp filébe,
    //most ebből kódot kell generálni:

    headerflag=1; 
    parsing_complete=0; 
    funcname="";
    tabdepth=0;
    int fd=open(class_file,0);
    ppo2cpp_lexer *lexer1=new ppo2cpp_lexer(fd);
    void *parser1=ParseAlloc(malloc); 
    parsenode *node;
    while( 0!=(node=lexer1->getnext()) )
    {
        Parse(parser1,node->tokenid,node);
    }
    Parse(parser1,0,0);
    ParseFree(parser1,free);
    delete lexer1;
    close(fd);
    parsing_complete=1; 
    extern int debug;
    if(!debug)
    {
        remove(class_file);
    }

#ifdef NEW_CPPLEVEL
if( newspec ){

    //C++ szintű new generálás.
    //A new meghívja az initialize metódust,
    //és minden paramétert továbbad neki.

    //deklaráció
    { 
        char classidnew[BUFSIZE];
        sprintf(classidnew,"%s%s",classid,newspec);
        fundecl_clpdef(classidnew,*static_modifier?1:0);
    }

    char *clsname;
    int dlast=dotlast(classid);
    if( dlast==0 )
    {
        inner_namespace=0;
        clsname=classid;
    }
    else
    {
        classid[dlast]=0x00;
        inner_namespace=classid;
        clsname=classid+dlast+1;

        fprintf(code,"namespace _nsp_");
        int i; 
        for( i=0; inner_namespace[i]; i++)
        {
            if( inner_namespace[i]=='.' )
            {
                fprintf(code,"{\nnamespace _nsp_");
            }
            else
            {
                fprintf(code,"%c",inner_namespace[i]);
            }
        }
        fprintf(code,"{\n");
    }
    //namespace-ek megnyitva

        
    fprintf(code,"%svoid _clp_%s%s(int argno)\n{",static_modifier,clsname,newspec);
    
    //fprintf(code,"\n    push_call(\"");
    //if(current_namespace) fprintf(code,"%s.",current_namespace);
    //if(inner_namespace)   fprintf(code,"%s.",inner_namespace);
    //fprintf(code,"%snew\",stack-argno);",clsname);

    fprintf(code,"\n    ");
    #ifdef CLID_EXTERNAL
    fprintf(code,"push(_st_clid_%s_ptr());",classidid);
    #else //CLID_EXTERNAL
    if( inner_namespace )
    {
        int i;
        for( i=0; inner_namespace[i]; i++)
        {
            if( inner_namespace[i]=='.' )
            {
                fprintf(code,"::");
            }
            else
            {
                fprintf(code,"%c",inner_namespace[i]);
            }
        }
        fprintf(code,"::");
    }
    fprintf(code,"_clp_%sclass(0);",clsname);
    #endif //CLID_EXTERNAL

    fprintf(code,
                "\n    _clp_objectnew(1);"
                "\n    dup();"
                "\n    int i;"
                "\n    for(i=0; i<argno; i++)"
                "\n    {"
                "\n        *(stack-2-i)=*(stack-3-i);"
                "\n    }"
                "\n    *(stack-2-argno)=*(stack-1);"
                "\n    pop();"
                "\n    _o_method_initialize.eval(1+argno);"
                "\n}");


    //namespace-eket bezárni
    if( inner_namespace )
    {
        fprintf(code,"\n}");
        int i;
        for( i=0; inner_namespace[i]; i++)
        {
            if( inner_namespace[i]=='.' )
            {
                fprintf(code,"}");
            }
        }
        fprintf(code,"//namespace %s",inner_namespace);
    }
    fprintf(code,"%s",fsep);
    
    //deklarációk a fejrészbe:
    metdecl_insert("initialize",0,0);
    free(fundecl_clpcall("objectnew"));

} //newspec
#endif //NEW_CPPLEVEL

    free(classid);
    free(classidid);
    return 0;
}

//---------------------------------------------------------------------------
int codegen_classid_CLASS_dotsymbol(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_classid_STCLASS_dotsymbol(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_newspec(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_newspec_NEW_COLON(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_newspec_NEW_COLON_SYMBOL(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_lslot(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_lslot_lslot_slot_lnewline(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_slot_ATTRIB_SYMBOL(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_slot_METHOD_SYMBOL(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_slot_METHOD_SYMBOL_expr(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_slot_METHOD_SYMBOL_forw(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_forw_COLON_SYMBOL(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_forw_forw_COLON_SYMBOL(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_ldsym_dotsymbol(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_ldsym_ldsym_COMMA_dotsymbol(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_function_funcid_LPAR_argument_RPAR_newline_body(parsenode *p,void *v)//PROTO  
//                   0           1             2       3
{
    linewritten=-1;
    
    parsenode *funcid=p->right[0];
    char *funcidtext=dotsymboltext(funcid->right[0]);
    int funcidstat=(funcid->codegen==codegen_funcid_STFUNCTION_dotsymbol);
    fundecl_clpdef(funcidtext,funcidstat);

    int dlast=dotlast(funcidtext);
    if( dlast==0 )
    {
        inner_namespace=0;
        funcname=funcidtext;
    }
    else
    {
        funcidtext[dlast]=0x00;
        inner_namespace=funcidtext;
        funcname=funcidtext+dlast+1;

        fprintf(code,"namespace _nsp_");
        int i;
        for( i=0; inner_namespace[i]; i++)
        {
            if( inner_namespace[i]=='.' )
            {
                fprintf(code,"{\nnamespace _nsp_");
            }
            else
            {
                fprintf(code,"%c",inner_namespace[i]);
            }
        }
        fprintf(code,"{\n");
    }
    
    if( funcidstat )
    {
        fprintf(code,"static ");
    }

    if( strstr(funcname,"_clp_") == funcname )
    {
        fprintf(code,"void %s(int argno)\n{",funcname);
    }
    else
    {
        fprintf(code,"void _clp_%s(int argno)\n{",funcname);
    }

    int argvar=p->right[1]->cargo;  //argumentum változók száma
    int locvar=p->right[3]->right[0]->cargo; //local változók száma

    fprintf(code,"\nVALUE *base=stack-argno;");

    if( p->right[1]->codegen==codegen_argument_STAR )
    {
        starflag=1;
        argcount=argvar;
        //fprintf(code,"\n//codegen_argument_STAR %d %d",argvar,locvar);
        fprintf(code,"\nwhile(stack<base+argno+%d)PUSHNIL();",locvar);
    }
    else if( p->right[1]->codegen==codegen_argument_larg_COMMA_STAR )
    {
        starflag=2;
        argcount=argvar;
        //fprintf(code,"\n//codegen_argument_larg_COMMA_STAR %d %d",argvar,locvar);
        fprintf(code,"\nwhile(stack<base+%d)PUSHNIL();",argvar);
        fprintf(code,"\nwhile(stack<base+max(argno,%d)+%d)PUSHNIL();",argvar,locvar);
        fprintf(code,"\nargno=max(argno,%d);",argvar);
    }
    else
    {
        starflag=0;
        fprintf(code,"\nstack=base+min(argno,%d);",argvar);
        fprintf(code,"\nwhile(stack<base+%d)PUSHNIL();",argvar+locvar);
        fprintf(code,"\nargno=%d;",argvar);
    }

    char ns[BUFSIZE]="";
    if(current_namespace){strcat(ns,current_namespace);strcat(ns,".");}
    if(inner_namespace){strcat(ns,inner_namespace);strcat(ns,".");}
    fprintf(code,"\npush_call(\"%s%s\",base);\n//",ns,funcname);
    
    tabdepth=1; //code
    cgen(p,1); //argument
    cgen(p,3); //body

    fprintf(code,"\n//\nstack=base;\npush(&NIL);\npop_call();\n}");

    int i;
    for(i=0; i<nodetab_block->top; i++)
    {
        blkcode(nodetab_block,i);
    }

    if( inner_namespace )
    {
        fprintf(code,"\n}");
        int i;
        for( i=0; inner_namespace[i]; i++)
        {
            if( inner_namespace[i]=='.' )
            {
                fprintf(code,"}");
            }
        }
        fprintf(code,"//namespace %s",inner_namespace);
    }
    
    fprintf(code,"%s",fsep);

    nodetab_locstat->clean();  //a függvényben definiált static változók
    nodetab_local->clean();    //a függvény argumentumai és local változói
    nodetab_block->clean();    //a függvényben definiált codeblockok

    inner_namespace=0;
    funcname=0;
    free(funcidtext);

    return 0;
}



//---------------------------------------------------------------------------
int codegen_funcid_FUNCTION_dotsymbol(parsenode *p,void *v)//PROTO  
{
    return 0;
}
 
//---------------------------------------------------------------------------
int codegen_funcid_STFUNCTION_dotsymbol(parsenode *p,void *v)//PROTO  
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_argument(parsenode *p,void *v)//PROTO   
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_argument_STAR(parsenode *p,void *v)//PROTO   
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_argument_larg(parsenode *p,void *v)//PROTO   
{
    cgen(p,0); //larg
    return 0;
}

//---------------------------------------------------------------------------
int codegen_argument_larg_COMMA_STAR(parsenode *p,void *v)//PROTO   
{
    cgen(p,0); //larg
    return 0;
}

//---------------------------------------------------------------------------
int codegen_larg_arg(parsenode *p,void *v)//PROTO   
{
    cgen(p,0); //arg
    return 0;
}

//---------------------------------------------------------------------------
int codegen_larg_larg_COMMA_arg(parsenode *p,void *v)//PROTO
{
    cgen(p,0); //larg
    cgen(p,1); //arg
    return 0;
}

//---------------------------------------------------------------------------
int codegen_arg_SYMBOL(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_arg_SYMBOL_ASSIGN_expr(parsenode *p,void *v)//PROTO
{
    parsenode *sym=p->right[0]; //SYMBOL
    int idx=sym->cargo&0xffff;
    int line=sym->lineno;
    nltab();fprintf(code,"if( ((base+%d)->type==TYPE_NIL)||",idx);
    nltab();fprintf(code,"   (((base+%d)->type==TYPE_REF)&&",idx);
    nltab();fprintf(code,"    ((base+%d)->data.vref->value.type==TYPE_NIL))){",idx);  //-Wparentheses
    nltab();fprintf(code,"line(%d);",line);
    cgen(p,1); //expr
    sym_assign(sym);
    nltab();fprintf(code,"pop();");
    nltab();fprintf(code,"}");
    return 0;
}

//---------------------------------------------------------------------------
int codegen_bargument(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_bargument_lbarg(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_bargument_STAR(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_bargument_lbarg_COMMA_STAR(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_lbarg_SYMBOL(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_lbarg_lbarg_COMMA_SYMBOL(parsenode *p,void *v)//PROTO
{
    return 0;
}
 
//---------------------------------------------------------------------------
int codegen_body_llocdefin_lstatement(parsenode *p,void *v)//PROTO
{
    cgen(p,0);
    cgen(p,1);
    return 0;
}

//---------------------------------------------------------------------------
int codegen_llocdefin(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_llocdefin_llocdefin_newline(parsenode *p,void *v)//PROTO
{
    cgen(p,0); //llocdefin
    //cgen(p,1); //newline
    return 0;
}

//---------------------------------------------------------------------------
int codegen_llocdefin_llocdefin_locdline_newline(parsenode *p,void *v)//PROTO
{
    cgen(p,0); //llocdefin
    cgen(p,2); //newline
    cgen(p,1); //locdline
    return 0;
}

//---------------------------------------------------------------------------
int codegen_locdline_STATIC_statdefin(parsenode *p,void *v)//PROTO
{
    cgen(p,0); //statdefin
    return 0;
}

//---------------------------------------------------------------------------
int codegen_locdline_LOCAL_locdefin(parsenode *p,void *v)//PROTO 
{
    cgen(p,0); //locdefin
    return 0;
}

//---------------------------------------------------------------------------
int codegen_locdefin_locdef(parsenode *p,void *v)//PROTO
{
    cgen(p,0); //locdef
    return 0;
}

//---------------------------------------------------------------------------
int codegen_locdefin_locdefin_COMMA_locdef(parsenode *p,void *v)//PROTO 
{
    cgen(p,0); //locdefin
    cgen(p,1); //locdef
    return 0;
}

//---------------------------------------------------------------------------
int codegen_locdef_SYMBOL(parsenode *p,void *v)//PROTO  
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_locdef_SYMBOL_ASSIGN_expr(parsenode *p,void *v)//PROTO  
{
    cgen(p,1); //expr
    parsenode *sym=p->right[0]; //SYMBOL
    //Miért volt ez külön sínen?
    //nltab();fprintf(code,"assign(base+%d);//%s",sym->cargo&0xffff,sym->text);
    sym_assign(sym);
    nltab();fprintf(code,"pop();");
    return 0;
}

//---------------------------------------------------------------------------
int codegen_lstatement(parsenode *p,void *v)//PROTO  
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_lstatement_lstatement_newline(parsenode *p,void *v)//PROTO  
{
    cgen(p,0); //lstatement
    //cgen(p,1); //newline
    return 0;
}

//---------------------------------------------------------------------------
int codegen_lstatement_lstatement_statement_newline(parsenode *p,void *v)//PROTO  
{
    cgen(p,0); //lstatement
    cgen(p,2); //newline
    cgen(p,1); //statement
    return 0;
}

//---------------------------------------------------------------------------
int codegen_statement_QUIT(parsenode *p,void *v)//PROTO
{
    char *fcall=fundecl_clpcall("__quit");
    nltab();fprintf(code,"_clp___quit(0);");
    nltab();fprintf(code,"pop();");
    free(fcall);
    return 0;
}

//---------------------------------------------------------------------------
int codegen_statement_RETURN_expr(parsenode *p,void *v)//PROTO
{
    cgen(p,0);
    if(begseqdepth_ret!=0)
    {
        nltab();fprintf(code,"begseqpop_ret();");
    }
    else
    {
        nltab();fprintf(code,"{*base=*(stack-1);stack=base+1;pop_call();return;}");
    }
    return 0;
}

//---------------------------------------------------------------------------
int codegen_statement_begseq_lrecov_finally_END(parsenode *p,void *v)//PROTO
//                    0      1      2
{
    nltab();fprintf(code,"{//begin sequence");

    nltab();fprintf(code,"seqjmp->jmp_stack=stack;");
    nltab();fprintf(code,"seqjmp->jmp_trace=trace;");
    nltab();fprintf(code,"seqjmp->jmp_usingstk=usingstk;");

    /*
    parsenode *beg=p->right[0];
    printf("%s\n",beg->text);
    if( beg->codegen==codegen_begseq_BEGSEQ_newline_lstatement )
    {
        printf("BEGSEQ without breakblock\n");
    }
    else if( beg->codegen==codegen_begseq_BEGSEQ_expr_newline_lstatement )
    {
        printf("BEGSEQ with breakblock\n");
    }
    else
    {
        printf("ILYEN NINCS\n");
    }
    */


    parsenode *lst=p->right[1];
    parsenode *fin=p->right[2];
    int recov=0;

    if( fin->codegen==codegen_finally_FINALLY_newline_lstatement  )
    {
        nltab();fprintf(code,"*(usingstk+%d)=END;",recov++);
    }

    if( (lst->codegen==codegen_lrecov) && (fin->codegen==codegen_finally) )
    {
        //implicit recover
        //ha sem recover sem finally nincs
        //akkor minden kivételt elkapunk
        nltab();fprintf(code,"*(usingstk+%d)=NIL;",recov++);
    }

    while( lst->codegen==codegen_lrecov_lrecov_recov  )
    {
        parsenode *r=lst->right[1];

        if( r->codegen==codegen_recov_RECOVER_SYMBOL_expr_newline_lstatement )
        {
            //az expr típusától függ,
            //hogy a recover elkapja-e a kivételt,
            //a típusokat a break() vizsgálja

            cgen(r,2); //newline
            cgen(r,1); //expr
            nltab();fprintf(code,"*(usingstk+%d)=*(stack-1);pop();",recov++);
        }
        else if( r->codegen==codegen_recov_RECOVER_SYMBOL_LT_dotsymbol_GT_newline_lstatement )
        {
            char *type=dotsymboltext(r->right[1]); //r->right[1]->text;
            if( 0==strcmp(type,"u") )
            {
                nltab();fprintf(code,"*(usingstk+%d)=NIL;",recov++); //bármit elkap
            }
            else if( 0==strcmp(type,"n") )
            {
                nltab();fprintf(code,"*(usingstk+%d)=ZERO;",recov++);
            }
            else if( 0==strcmp(type,"l") )
            {
                nltab();fprintf(code,"*(usingstk+%d)=FALSE;",recov++);
            }
            else if( 0==strcmp(type,"d") )
            {
                nltab();fprintf(code,"*(usingstk+%d)=PROTOTYPE_DATE;",recov++);
            }
            else if( 0==strcmp(type,"x") )
            {
                nltab();fprintf(code,"*(usingstk+%d)=PROTOTYPE_BINARY;",recov++);
            }
            else if( 0==strcmp(type,"c") )
            {
                nltab();fprintf(code,"*(usingstk+%d)=PROTOTYPE_STRING;",recov++);
            }
            else if( 0==strcmp(type,"a") )
            {
                nltab();fprintf(code,"*(usingstk+%d)=PROTOTYPE_ARRAY;",recov++);
            }
            else if( 0==strcmp(type,"b") )
            {
                nltab();fprintf(code,"*(usingstk+%d)=PROTOTYPE_BLOCK;",recov++);
            }
            else
            {
                char buf[BUFSIZE];
                sprintf(buf,".%sclass",type);
                char *fcall=fundecl_clpcall(buf);
                nltab();fprintf(code,"%s(0);",fcall);
                nltab();fprintf(code,"*(usingstk+%d)=prototype_object();",recov++);
                free(fcall);
            }
            free(type);
        }
        else
        {
            nltab();fprintf(code,"*(usingstk+%d)=NIL;",recov++); //bármit elkap
        }
        lst=lst->right[0];
    }
    
    nltab();fprintf(code,"usingstk+=%d;",recov);

    begseqdepth_ret++;
    begseqdepth_loop++;

    int lab=labelnext();
    nltab();fprintf(code,"int seq_%d=setjmp((seqjmp++)->jmpb);",lab);

    //begin
    nltab();fprintf(code,"if(seq_%d==0){",lab);
    cgenv(p,0,&lab);
    nltab();fprintf(code,"}");

    //recover
    int cnt=0;
    lst=p->right[1];
    if( (lst->codegen==codegen_lrecov) && (fin->codegen==codegen_finally) )
    {
        //implicit recover: 2007.10.20
        nltab();fprintf(code,"else if(seq_%d==%d){",lab,1);
        nltab();fprintf(code,"pop();");
        nltab();fprintf(code,"}");
    }
    while( lst->codegen==codegen_lrecov_lrecov_recov  )
    {
        ++cnt;
        nltab();fprintf(code,"else if(seq_%d==%d){",lab,cnt);
        cgen(lst,1);
        nltab();fprintf(code,"}");
        lst=lst->right[0];
    }

    begseqdepth_ret--;
    begseqdepth_loop--;

    nltab();fprintf(code,"if(seq_%d>=0){usingstk=(--seqjmp)->jmp_usingstk;}",lab);

    //finally    
    if( fin->codegen==codegen_finally_FINALLY_newline_lstatement )
    {
        cgen(p,2); //lstatement
    }

    nltab();fprintf(code,"if(seq_%d>=0);",lab);
    nltab();fprintf(code,"else if(seq_%d==-1){_clp_break0(1);}",lab);

    nltab();fprintf(code,"else if(seq_%d==-2)",lab);
    if( begseqdepth_ret>0 )
    {
        fprintf(code,"{begseqpop_ret();}");
    }
    else
    {
        fprintf(code,"{*base=*(stack-1);stack=base+1;pop_call();return;}");
    }
        
    if( loopdepth>0 )
    {
        nltab();fprintf(code,"else if(seq_%d==-3)",lab); //loop
        if( begseqdepth_loop>0 )
        {
            fprintf(code,"{begseqpop_loop();}");
        }
        else
        {
            fprintf(code,"{goto lab_%d_1;}//loop",label(0));
        }

        nltab();fprintf(code,"else if(seq_%d==-4)",lab); //exit
        if( begseqdepth_loop )
        {
             fprintf(code,"{begseqpop_exit();}");
        }
        else
        {
            fprintf(code,"{goto lab_%d_2;}//exit",label(0));
        }
    }

    nltab();fprintf(code,"}//end sequence");
    return 0;
}

//---------------------------------------------------------------------------
int codegen_statement_if_lelseif_else_endif(parsenode *p,void *v)//PROTO
//                    0  1       2    3
{
    int lab=labelnext();
    p->right[0]->nodeid=lab;
    p->right[1]->nodeid=lab;
    p->right[2]->nodeid=lab;
    p->right[3]->nodeid=lab;
    p->right[2]->cargo+=p->right[1]->cargo;
    p->right[3]->cargo=p->right[2]->cargo+1;
    cgen(p,0);
    cgen(p,1);
    cgen(p,2);
    cgen(p,3);
    return 0;
}

//---------------------------------------------------------------------------
int codegen_statement_WHILE_expr_newline_lstatement_END(parsenode *p,void *v)//PROTO  
{
    int save_begseqdepth=begseqdepth_loop;
    begseqdepth_loop=0;
    
    label(1);
    nltab();fprintf(code,"lab_%d_1:",label(0));
    cgen(p,1); //newline
    cgen(p,0); //expr
    nltab();fprintf(code,"if(!flag()) goto lab_%d_2;",label(0));
    tabdepth++;
    loopdepth++;
    cgen(p,2); //lstatement
    loopdepth--;
    tabdepth--;
    nltab();fprintf(code,"goto lab_%d_1;",label(0));
    nltab();fprintf(code,"lab_%d_2:;",label(0));
    label(-1);

    begseqdepth_loop=save_begseqdepth;
    return 0;
}
 
//---------------------------------------------------------------------------
int codegen_statement_FOR_SYMBOL_ASSIGN_expr_TO_expr_forstep_newline_lstatement_END(parsenode *p,void *v)//PROTO
//                        0             1       2    3       4       5
{
    int save_begseqdepth=begseqdepth_loop;
    begseqdepth_loop=0;

    label(1);
    nltab();fprintf(code,"{");
    cgen(p,4); //newline
    cgen(p,3); //forstep
    nltab();fprintf(code,"int sg=sign();");    
    cgen(p,1); //expr
    sym_assign(p->right[0]); //SYMBOL
    nltab();fprintf(code,"lab_%d_0:",label(0));
    cgen(p,2); //expr
    nltab();fprintf(code,"if( ((sg>=0)&&greaterthan()) || ((sg<0)&&lessthan())) goto lab_%d_2;",label(0));
        
    tabdepth++;
    loopdepth++;
    cgen(p,5); //lstatement
    loopdepth--;
    tabdepth--;

    nltab();fprintf(code,"lab_%d_1:",label(0));
    cgen(p,3);  //forstep
    nltab();fprintf(code,"dup();");
    nltab();fprintf(code,"sg=sign();");
    sym_eval(p->right[0],"push_symbol"); //SYMBOL
    nltab();fprintf(code,"add();");
    sym_assign(p->right[0]);
    nltab();fprintf(code,"goto lab_%d_0;",label(0));
    nltab();fprintf(code,"lab_%d_2:;",label(0));
    nltab();fprintf(code,"}");
    label(-1);

    begseqdepth_loop=save_begseqdepth;
    return 0;
}

//---------------------------------------------------------------------------
int codegen_statement_LOOP(parsenode *p,void *v)//PROTO
{
    if(loopdepth<=0)
    {
        no_loop_in_sight(p->right[0]);
    }
    if(begseqdepth_loop!=0)
    {
        nltab();fprintf(code,"begseqpop_loop();");
    }
    else
    {
        nltab();fprintf(code,"goto lab_%d_1;//loop",label(0));
    }
    return 0;
}

//---------------------------------------------------------------------------
int codegen_statement_EXIT(parsenode *p,void *v)//PROTO
{
    if(loopdepth<=0)
    {
        no_loop_in_sight(p->right[0]);
    }
    if(begseqdepth_loop!=0)
    {
        nltab();fprintf(code,"begseqpop_exit();");
    }
    else
    {
        nltab();fprintf(code,"goto lab_%d_2;//exit",label(0));
    }
    return 0;
}

//---------------------------------------------------------------------------
int codegen_statement_CLANG(parsenode *p,void *v)//PROTO
{
    int i;
    parsenode *q;

    nltab();fprintf(code,"//clang");
    i=0;
    while( 0!=(q=(parsenode*)(nodetab_local->get(i))) )
    {
        nltab();fprintf(code,"#define LOCAL_%s (base+%d)",q->text,i);
        ++i;
    }

    nltab();fprintf(code,"{%s}",rtxt(p,0));

    i=0;
    while( 0!=(q=(parsenode*)(nodetab_local->get(i))) )
    {
        nltab();fprintf(code,"#undef LOCAL_%s",q->text);
        ++i;
    }
    nltab();fprintf(code,"//cend");
    return 0;
}

//---------------------------------------------------------------------------
int codegen_statement_expr(parsenode *p,void *v)//PROTO
{
    cgen(p,0); //expr
    nltab();fprintf(code,"pop();");
    return 0;
}

//---------------------------------------------------------------------------
int codegen_begseq_BEGSEQ_newline_lstatement(parsenode *p,void *v)//PROTO
{
    tabdepth++;
    nltab();fprintf(code,"_clp_breakblock(0);//BREAKBLOCK");
    cgen(p,1); //lstatement
    nltab();fprintf(code,"pop();//BREAKBLOCK");
    tabdepth--;
    return 0;
}

//---------------------------------------------------------------------------
int codegen_begseq_BEGSEQ_expr_newline_lstatement(parsenode *p,void *v)//PROTO
{
    tabdepth++;
    cgen(p,0); fprintf(code,"//BREAKBLOCK");
    cgen(p,2); //lstatement
    nltab();fprintf(code,"pop();//BREAKBLOCK");
    tabdepth--;
    return 0;
}

//---------------------------------------------------------------------------
int codegen_lrecov(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_lrecov_lrecov_recov(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_recov_RECOVER_newline_lstatement(parsenode *p,void *v)//PROTO
//                        0       1
{
    nltab();fprintf(code,"pop();"); //break felteszi az exception-t, de nem kell
    tabdepth++;
    cgen(p,1); //lstatement
    tabdepth--;
    return 0;
}

//---------------------------------------------------------------------------
int codegen_recov_RECOVER_SYMBOL_newline_lstatement(parsenode *p,void *v)//PROTO
//                        0      1       2
{
    sym_assign(p->right[0]);
    nltab();fprintf(code,"pop();");
    tabdepth++;
    cgen(p,2); //lstatement
    tabdepth--;
    return 0;
}

//---------------------------------------------------------------------------
int codegen_recov_RECOVER_SYMBOL_expr_newline_lstatement(parsenode *p,void *v)//PROTO
//                        0      1    2       3
{
    sym_assign(p->right[0]);
    nltab();fprintf(code,"pop();");
    tabdepth++;
    cgen(p,3); //lstatement
    tabdepth--;
    return 0;
}

//---------------------------------------------------------------------------
int codegen_recov_RECOVER_SYMBOL_LT_dotsymbol_GT_newline_lstatement(parsenode *p,void *v)//PROTO
//                        0         1            2       3
{
    char *type=dotsymboltext(p->right[1]);
    fprintf(code," //<%s>",type);
    sym_assign(p->right[0]);
    nltab();fprintf(code,"pop();");
    tabdepth++;
    cgen(p,3); //lstatement
    tabdepth--;
    free(type);
    return 0;
}

//---------------------------------------------------------------------------
int codegen_finally(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_finally_FINALLY_newline_lstatement(parsenode *p,void *v)//PROTO
//                          0       1
{
    nltab();fprintf(code,"//finally");
    tabdepth++;
    cgen(p,1); //lstatemenet
    tabdepth--;
    return 0;
}

//---------------------------------------------------------------------------
int codegen_if_IF_expr_newline_lstatement(parsenode *p,void *v)//PROTO 
{
    cgen(p,1); //newline
    cgen(p,0); //expr
    nltab();fprintf(code,"if(!flag()) goto if_%d_1;",p->nodeid);
    tabdepth++;
    cgen(p,2); //lstatement
    tabdepth--;
    return 0;
}

//---------------------------------------------------------------------------
int codegen_if_DOCASE_newline_CASE_expr_newline_lstatement(parsenode *p,void *v)//PROTO 
{
    cgen(p,2); //newline
    cgen(p,1); //expr
    nltab();fprintf(code,"if(!flag()) goto if_%d_1;",p->nodeid);
    tabdepth++;
    cgen(p,3); //lstatement
    tabdepth--;
    return 0;
}

//---------------------------------------------------------------------------
int codegen_lelseif(parsenode *p,void *v)//PROTO 
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_lelseif_lelseif_elseif(parsenode *p,void *v)//PROTO 
{
    p->right[0]->nodeid=p->nodeid;
    p->right[1]->nodeid=p->nodeid;
    p->right[1]->cargo=p->cargo;
    cgen(p,0);
    cgen(p,1);
    return 0;
}

//---------------------------------------------------------------------------
int codegen_elseif_ELSEIF_expr_newline_lstatement(parsenode *p,void *v)//PROTO 
{
    nltab();fprintf(code,"goto if_%d_0;",p->nodeid);
    nltab();fprintf(code,"if_%d_%d:",p->nodeid,p->cargo);
    cgen(p,1); //newline
    cgen(p,0); //expr
    nltab();fprintf(code,"if(!flag()) goto if_%d_%d;",p->nodeid,p->cargo+1);
    tabdepth++;
    cgen(p,2); //lstatement
    tabdepth--;
    return 0;
}

//---------------------------------------------------------------------------
int codegen_elseif_CASE_expr_newline_lstatement(parsenode *p,void *v)//PROTO 
{
    return codegen_elseif_ELSEIF_expr_newline_lstatement(p,v);
}

//---------------------------------------------------------------------------
int codegen_else(parsenode *p,void *v)//PROTO 
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_else_ELSE_newline_lstatement(parsenode *p,void *v)//PROTO 
{
    nltab();fprintf(code,"goto if_%d_0;",p->nodeid);
    nltab();fprintf(code,"if_%d_%d:",p->nodeid,p->cargo);
    cgen(p,0); //newline
    tabdepth++;
    cgen(p,1); //lstatement
    tabdepth--;
    return 0;
}

//---------------------------------------------------------------------------
int codegen_else_OTHERWISE_newline_lstatement(parsenode *p,void *v)//PROTO 
{
    return codegen_else_ELSE_newline_lstatement(p,v);
}

//---------------------------------------------------------------------------
int codegen_endif_END(parsenode *p,void *v)//PROTO 
{
    nltab();fprintf(code,"if_%d_%d:",p->nodeid,p->cargo);
    nltab();fprintf(code,"if_%d_0:;",p->nodeid);
    return 0;
}

//---------------------------------------------------------------------------
int codegen_forstep(parsenode *p,void *v)//PROTO 
{
    nltab();fprintf(code,"push(&ONE);");
    return 0;
}

//---------------------------------------------------------------------------
int codegen_forstep_STEP_expr(parsenode *p,void *v)//PROTO 
{
    cgen(p,0);
    return 0;
}

//---------------------------------------------------------------------------
int codegen_lfuncpar(parsenode *p,void *v)//PROTO 
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_lfuncpar_parexpr(parsenode *p,void *v)//PROTO 
{
    cgenv(p,0,v);
    return 0;
}

//---------------------------------------------------------------------------
int codegen_lfuncpar_lfuncpar0_COMMA_parexpr0(parsenode *p,void *v)//PROTO 
{
    cgenv(p,0,v);
    cgenv(p,1,v);
    return 0;
}

//---------------------------------------------------------------------------
int codegen_lfuncpar0_parexpr0(parsenode *p,void *v)//PROTO 
{
    cgenv(p,0,v);
    return 0;
}

//---------------------------------------------------------------------------
int codegen_lfuncpar0_lfuncpar0_COMMA_parexpr0(parsenode *p,void *v)//PROTO 
{
    cgenv(p,0,v);
    cgenv(p,1,v);
    return 0;
}

//---------------------------------------------------------------------------
int codegen_parexpr0(parsenode *p,void *v)//PROTO 
{
    nltab();fprintf(code,"push(&NIL);");
    return 0;
}

//---------------------------------------------------------------------------
int codegen_parexpr0_parexpr(parsenode *p,void *v)//PROTO
{
    cgenv(p,0,v);
    return 0;
}

//---------------------------------------------------------------------------
int codegen_parexpr_expr(parsenode *p,void *v)//PROTO
{
    cgen(p,0);
    return 0;
}

//---------------------------------------------------------------------------
int codegen_parexpr_STAR(parsenode *p,void *v)//PROTO
{
    //A hívó függvény összes paraméterét a stackre teszi.
    //Ha blokkban vagyunk, a 0-dik paramétert ki kell hagyni.
    //Kérdéses, hogy kell-e a paramétereket derefelni.
    //A v mutatja, hogy lfuncpar honnan származik:
    //függvényhívásból, metódushívásból, vagy array-ből. 

    nltab();    
    if( v==codegen_expr_ddotsymbol_LPAR_lfuncpar_RPAR ||
        v==codegen_msgpar_LPAR_lfuncpar_RPAR ||
        v==codegen_msgpar_LPAR_lfuncpar_RPAR_ASSIGN_expr )
    {
        fprintf(code,"{int i;for(i=%d;i<argno;i++){argc++;push(base+i);}}",blkflag);
    }
    else
    {
        fprintf(code,"{int i;for(i=%d;i<argno;i++){argc++;push_symbol(base+i);}}",blkflag);
    }
    return 0;
}

//---------------------------------------------------------------------------
int codegen_parexpr_STAR_LBRACKET_parexpr0_DOTDOT_parexpr0_RBRACKET(parsenode *p,void *v)//PROTO
{
    //A hívó függvény paramétereinek egy szeletét a stackre teszi.
    //Ha blokkban vagyunk, a 0-dik paramétert ki kell hagyni.
    //Kérdéses, hogy kell-e a paramétereket derefelni.
    //A v mutatja, hogy lfuncpar honnan származik:
    //függvényhívásból, metódushívásból, vagy array-ből. 


    nltab();fprintf(code,"{");
    cgen(p,0);
    nltab();fprintf(code,"if(TOP()->type==TYPE_NIL){pop();number(1);} else");
    nltab();fprintf(code,"if(TOP()->type!=TYPE_NUMBER) error_arg(\"*[x..]\",TOP(),1);");
    nltab();fprintf(code,"int xl=D2INT(TOP()->data.number);pop();xl=max(xl,1)-1+%d;",blkflag);

    cgen(p,1);
    nltab();fprintf(code,"if(TOP()->type==TYPE_NIL){pop();number(argno);} else");
    nltab();fprintf(code,"if(TOP()->type!=TYPE_NUMBER) error_arg(\"*[..x]\",TOP(),1);");
    nltab();fprintf(code,"int xh=D2INT(TOP()->data.number)+%d;pop();xh=min(xh,argno);",blkflag);
    
    if( v==codegen_expr_ddotsymbol_LPAR_lfuncpar_RPAR ||
        v==codegen_msgpar_LPAR_lfuncpar_RPAR ||
        v==codegen_msgpar_LPAR_lfuncpar_RPAR_ASSIGN_expr )
    {
        nltab();fprintf(code,"int i;for(i=xl;i<xh;i++){argc++;push(base+i);}");
    }
    else
    {
        nltab();fprintf(code,"int i;for(i=xl;i<xh;i++){argc++;push_symbol(base+i);}");
    }
    nltab();fprintf(code,"}");
    return 0;
}

//---------------------------------------------------------------------------
int codegen_parexpr_AT_SYMBOL(parsenode *p,void *v)//PROTO
{
    sym_eval(p->right[0],"push_symbol_ref");
    return 0;
}

//---------------------------------------------------------------------------
int codegen_parexpr_LBRACKET_SYMBOL_RBRACKET(parsenode *p,void *v)//PROTO
{
    sym_eval(p->right[0],"push");
    return 0;
}

//---------------------------------------------------------------------------
int codegen_lexpr(parsenode *p,void *v)//PROTO
{
    nltab();fprintf(code,"push(&NIL);");
    return 0;
}

//---------------------------------------------------------------------------
int codegen_lexpr_expr(parsenode *p,void *v)//PROTO
{
    double x;
    int f=cgenv(p,0,&x);
        
    if( f==XNUM_TOTAL )
    {
        if( v )
        {
            *(double*)v=x;
            return XNUM_TOTAL;
        }
        else
        {
            pnumber(x);
        }
    }
    else if( f==XNUM_PARTIAL )
    {
        if( v )
        {
            *(double*)v=x;
            return XNUM_PARTIAL;
        }
        else
        {
            paddnum(x);
        }
    }

    return 0;
}

//---------------------------------------------------------------------------
int codegen_lexpr_lexpr0_COMMA_expr0(parsenode *p,void *v)//PROTO
{
    cgen(p,0);
    nltab();fprintf(code,"pop();");
    cgen(p,1);
    return 0;
}

//---------------------------------------------------------------------------
int codegen_lexpr0_expr0(parsenode *p,void *v)//PROTO
{
    cgen(p,0);
    return 0;
}

//---------------------------------------------------------------------------
int codegen_lexpr0_lexpr0_COMMA_expr0(parsenode *p,void *v)//PROTO
{
    cgen(p,0);
    nltab();fprintf(code,"pop();");
    cgen(p,1);
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr0(parsenode *p,void *v)//PROTO
{
    nltab();fprintf(code,"push(&NIL);");
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr0_expr(parsenode *p,void *v)//PROTO
{
    cgen(p,0);
    return 0;
}

//---------------------------------------------------------------------------
int codegen_msgpar(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_msgpar_ASSIGN_expr(parsenode *p,void *v)//PROTO
{
    cgen(p,0);
    return 0;
}

//---------------------------------------------------------------------------
int codegen_msgpar_LPAR_lfuncpar_RPAR(parsenode *p,void *v)//PROTO
{
    cgenv(p,0,(void*)codegen_msgpar_LPAR_lfuncpar_RPAR);
    return 0;
}

//---------------------------------------------------------------------------
int codegen_msgpar_LPAR_lfuncpar_RPAR_ASSIGN_expr(parsenode *p,void *v)//PROTO
{
    cgenv(p,0,(void*)codegen_msgpar_LPAR_lfuncpar_RPAR_ASSIGN_expr);
    cgen(p,1);
    return 0;
}

//---------------------------------------------------------------------------
int codegen_lnewline_newline(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_lnewline_lnewline_newline(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_lnewline0(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_lnewline0_lnewline0_newline(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int codegen_newline_NL(parsenode *p,void *v)//PROTO
{
    int line=p->lineno;
    if( p->right[0]->text[0]=='\n' )
    {
        line--;
    }

    if( linewritten!=0 && linewritten!=line )   
    {
        linewritten=line;
        nltab(); fprintf(code,"line(%d);",line);
    }
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_NUMBER(parsenode *p,void *v)//PROTO
{
    double d=0;
    const char *num=rtxt(p,0);
    if( (*num=='0') && ((*(num+1)=='b') || (*(num+1)=='B')) )
    {
        d=(double)strtoull(num+2,0,2);
    }
    else if( (*num=='0') && ((*(num+1)=='o') || (*(num+1)=='O')) )
    {
        d=(double)strtoull(num+2,0,8);
    }
    else if( (*num=='0') && ((*(num+1)=='x') || (*(num+1)=='X')) )
    {
        d=(double)strtoull(num+2,0,16);
    }
    else
    {
        sscanf(num,"%lf",&d);
    }
    
    if( v )
    {
        *(double*)v=d;
        return XNUM_TOTAL;
    }
    else if( d==0. )
    {
        nltab();fprintf(code,"push(&ZERO);");
    }
    else if( d==1. )
    {
        nltab();fprintf(code,"push(&ONE);");
    }
    else
    {
        pnumber(d);
    }
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_STRING(parsenode *p,void *v)//PROTO
{
    nltab();
    fprintf(code,"string(L");
    widestring(rtxt(p,0));
    fprintf(code,");");
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_BINARYA(parsenode *p,void *v)//PROTO
{
    nltab();fprintf(code,"binary(%s);",rtxt(p,0));
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_NLSTEXT(parsenode *p,void *v)//PROTO
{
    nltab();
    fprintf(code,"string(nls_text(L");
    widestring(rtxt(p,0));
    fprintf(code,"));");
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_BINARYX(parsenode *p,void *v)//PROTO
{
    nltab();fprintf(code,"binaryx(%s);",rtxt(p,0)+1);
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_TRUE(parsenode *p,void *v)//PROTO
{
    nltab();fprintf(code,"push(&TRUE);");
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_FALSE(parsenode *p,void *v)//PROTO
{
    nltab();fprintf(code,"push(&FALSE);");
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_NIL(parsenode *p,void *v)//PROTO
{
    nltab();fprintf(code,"push(&NIL);");
    return 0;
}
 
//---------------------------------------------------------------------------
int codegen_expr_SYMBOL(parsenode *p,void *v)//PROTO
{
    sym_eval(p->right[0],"push_symbol");
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_SYMBOL_ARROW_SYMBOL(parsenode *p,void *v)//PROTO
{
    char fldref[BUFSIZE];
    sprintf(fldref,"%s->%s",rtxt(p,0),rtxt(p,1));
    flddecl_insert(fldref);
    nltab();fprintf(code,"_ef_%s_%s.fget();",rtxt(p,0),rtxt(p,1));
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_expr_COLON_SYMBOL_msgpar(parsenode *p,void *v)//PROTO
//               0          1      2
{
    cgen(p,0); //expr (object)

    const char *meth=p->right[1]->text;
    metdecl_insert(meth,0,0);

    parsenode *msgpar=p->right[2];
    int parcount=(0xffff&msgpar->cargo)+1;
    int starcount=(msgpar->cargo>>16);
    
    if( starcount==0 )
    {
        cgen(p,2); //msgpar
        nltab();fprintf(code,"_o_method_%s.eval(%d);",meth,parcount);
    }
    else
    {
        nltab();fprintf(code,"{int argc=%d-%d;",parcount,starcount);
        cgen(p,2); //msgpar
        nltab();fprintf(code,"_o_method_%s.eval(argc);",meth);
        nltab();fprintf(code,"};");
    }
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_expr_COLON_LPAR_dotsymbol_RPAR_SYMBOL_msgpar(parsenode *p,void *v)//PROTO
//               0               1              2      3
{
    cgen(p,0); //expr (object)

    char *cls=dotsymboltext(p->right[1]);
    const char *meth=p->right[2]->text;
    metdecl_insert(meth,0,cls);

    parsenode *msgpar=p->right[3];
    int parcount=(0xffff&msgpar->cargo)+1;
    int starcount=(msgpar->cargo>>16);

    if( starcount==0 )
    {
        cgen(p,3); //msgpar
        nltab();fprintf(code,"_o_method_%s_C_%s.eval(%d);",meth,dot2uln(cls),parcount);
    }
    else
    {
        nltab();fprintf(code,"{int argc=%d-%d;",parcount,starcount);
        cgen(p,3); //msgpar
        nltab();fprintf(code,"_o_method_%s_C_%s.eval(argc);",meth,dot2uln(cls));
        nltab();fprintf(code,"};");
    }
    free(cls);
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_expr_COLON_LPAR_dotsymbol_AT_dotsymbol_RPAR_SYMBOL_msgpar(parsenode *p,void *v)//PROTO
//               0               1            2              3      4
{
    cgen(p,0); //expr (object)

    char *parent=dotsymboltext(p->right[1]); //p->right[1]->text;
    char *cls=dotsymboltext(p->right[2]); //p->right[2]->text;
    const char *meth=p->right[3]->text;
    metdecl_insert(meth,parent,cls);

    parsenode *msgpar=p->right[4];
    int parcount=(0xffff&msgpar->cargo)+1;
    int starcount=(msgpar->cargo>>16);
    
    if( starcount==0 )
    {
        cgen(p,4); //msgpar
        if( 0==strcmp(parent,"super") )
        {
            nltab();fprintf(code,"_o_method_%s_S_%s.eval(%d);",meth,dot2uln(cls),parcount);
        }
        else
        {
            nltab();fprintf(code,"_o_method_%s_P_%s_C_%s.eval(%d);",meth,dot2uln(parent),dot2uln(cls),parcount);
        }
    }
    else
    {
        nltab();fprintf(code,"{int argc=%d-%d;",parcount,starcount);
        cgen(p,4); //msgpar
        if( 0==strcmp(parent,"super") )
        {
            nltab();fprintf(code,"_o_method_%s_S_%s.eval(argc);",meth,dot2uln(cls));
        }
        else
        {
            nltab();fprintf(code,"_o_method_%s_P_%s_C_%s.eval(argc);",meth,dot2uln(parent),dot2uln(cls));
        }
        nltab();fprintf(code,"};");
    }

    free(parent);
    free(cls);
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_ddotsymbol_LPAR_lfuncpar_RPAR(parsenode *p,void *v)//PROTO
{
    int postfix=postfixflag;
    postfixflag=0;

    parsenode *lfuncpar=p->right[1];
    int parcount=(0xffff&lfuncpar->cargo);
    int starcount=(lfuncpar->cargo>>16);

    char *fname=dotsymboltext(p->right[0]);
    char *fcall=fundecl_clpcall(fname);

    if( starcount==0 )
    {
        cgenv(p,1,(void*)codegen_expr_ddotsymbol_LPAR_lfuncpar_RPAR); //lfuncpar
        nltab();fprintf(code,"%s(%d);",fcall,postfix+parcount);
    }
    else
    {
        nltab();fprintf(code,"{int argc=%d+%d-%d;",postfix,parcount,starcount);
        cgenv(p,1,(void*)codegen_expr_ddotsymbol_LPAR_lfuncpar_RPAR); //lfuncpar
        nltab();fprintf(code,"%s(argc);",fcall);
        nltab();fprintf(code,"};");
    }
    free(fname);
    free(fcall);
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_expr_COLCOL_expr(parsenode *p,void *v)//PROTO
//               0           1
{
    function_call_expected(p);

    cgen(p,0);
    postfixflag=1;
    cgen(p,1);
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_expr_COLCOLASS_expr(parsenode *p,void *v)//PROTO
//               0              1
{
    function_call_expected(p);

    cgen(p,0);
    postfixflag=1;
    cgen(p,1);
    lvalue(p->right[0]);
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_LPAR_lexpr_RPAR(parsenode *p,void *v)//PROTO
{
    double x;
    int f=cgenv(p,0,&x);

    if( f==XNUM_TOTAL )
    {
        if( v )
        {
            *(double*)v=x;
            return XNUM_TOTAL;
        }
        else
        {
            pnumber(x);
        }
    }
    else if( f==XNUM_PARTIAL )
    {
        if( v )
        {
            *(double*)v=x;
            return XNUM_PARTIAL;
        }
        else
        {
            paddnum(x);
        }
    }

    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_LBRACE_PIPE_bargument_PIPE_lexpr_RBRACE(parsenode *p,void *v)//PROTO
{
    int blkcnt=nodetab_block->add(p)-1; //0-tól indul
    fundecl_codeblock(funcname,blkcnt);
    nodetab_blkenv->clean();
    blkenv(p->right[1]); //összegyűjti lexpr szimbólumait
    int i;
    for(i=0; i<nodetab_blkenv->top; i++)
    {
        parsenode *s=(parsenode*)nodetab_blkenv->get(i);
        if( s->cargo&SYM_BLKSTAT )
        {
            nltab();fprintf(code,"push_symbol_ref(_st_%s.ptr);//%s",s->text,funcname);
        }
        if( s->cargo&SYM_BLKLOC )
        {       
            nltab();
            int idx=s->cargo&0xffff;
            if( starflag && (idx>=argcount) )
            {
                fprintf(code,"push_symbol_ref(base+argno+%d);//%s",idx-argcount,s->text);
            }
            else
            {
                fprintf(code,"push_symbol_ref(base+%d);//%s",idx,s->text);
            }
        }
    }
    nltab();fprintf(code,"block(_blk_%s_%d,%d);",funcname,blkcnt,nodetab_blkenv->top);
    nodetab_blkenv->clean();
    return 0;
}


//---------------------------------------------------------------------------
int codegen_expr_LPAR_PIPE_bargument_PIPE_lexpr_RPAR(parsenode *p,void *v)//PROTO
{
    int blkcnt=nodetab_block->add(p)-1; //0-tól indul
    fundecl_codeblock(funcname,blkcnt);
    nodetab_blkenv->clean();
    blkenv(p->right[1]); //összegyűjti lexpr szimbólumait
    int i;
    for(i=0; i<nodetab_blkenv->top; i++)
    {
        parsenode *s=(parsenode*)nodetab_blkenv->get(i);
        if( s->cargo&SYM_BLKSTAT )
        {
            nltab();fprintf(code,"push_symbol(_st_%s.ptr);//%s",s->text,funcname);
        }
        if( s->cargo&SYM_BLKLOC )
        {       
            nltab();
            int idx=s->cargo&0xffff;
            if( starflag && (idx>=argcount) )
            {
                fprintf(code,"push_symbol(base+argno+%d);//%s",idx-argcount,s->text);
            }
            else
            {
                fprintf(code,"push_symbol(base+%d);//%s",idx,s->text);
            }
        }
    }
    nltab();fprintf(code,"block(_blk_%s_%d,%d);",funcname,blkcnt,nodetab_blkenv->top);
    nodetab_blkenv->clean();
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_IF_LPAR_expr_COMMA_expr_COMMA_expr_RPAR(parsenode *p,void *v)//PROTO
{
    cgen(p,0);
    nltab();fprintf(code,"if(flag()){");
    cgen(p,1);
    nltab();fprintf(code,"}else{");
    cgen(p,2);
    nltab();fprintf(code,"}");
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_LBRACE_lfuncpar_RBRACE(parsenode *p,void *v)//PROTO
{
    parsenode *lfuncpar=p->right[0];
    int parcount=(0xffff&lfuncpar->cargo);
    int starcount=(lfuncpar->cargo>>16);

    if( starcount==0 )
    {
        cgenv(p,0,(void*)codegen_expr_LBRACE_lfuncpar_RBRACE);
        nltab();fprintf(code,"array(%d);",parcount);
    }
    else
    {
        nltab();fprintf(code,"{int argc=%d-%d;",parcount,starcount);
        cgenv(p,0,(void*)codegen_expr_LBRACE_lfuncpar_RBRACE); //lfuncpar
        nltab();fprintf(code,"array(argc);");
        nltab();fprintf(code,"};");
    }
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_expr_LBRACKET_expr_RBRACKET(parsenode *p,void *v)//PROTO
{
    double x;
    cgen(p,0);
    int f=cgenv(p,1,&x);

    if( TOTAL(f) )
    {
        nltab();fprintf(code,"idxr0(%.16g);",x);
    }
    else if( PARTIAL(f) )
    {
        paddnum(x);
        nltab();fprintf(code,"idxr();");
    }
    else if( WRITTEN(f) )
    {
        nltab();fprintf(code,"idxr();");
    }
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_expr_LBRACKET_parexpr0_DOTDOT_parexpr0_RBRACKET(parsenode *p,void *v)//PROTO
{
    cgen(p,0);
    cgen(p,1);
    cgen(p,2);
    nltab();fprintf(code,"slice();");
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_expr_ASSIGN_expr(parsenode *p,void *v)//PROTO
{
    cgen(p,1);
    lvalue(p->right[0]);
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_expr_ADDASS_expr(parsenode *p,void *v)//PROTO
{
    cgen(p,0);
    cgen(p,1);
    nltab();fprintf(code,"add();");
    lvalue(p->right[0]);
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_expr_SUBASS_expr(parsenode *p,void *v)//PROTO
{
    cgen(p,0);
    cgen(p,1);
    nltab();fprintf(code,"sub();");
    lvalue(p->right[0]);
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_expr_MULASS_expr(parsenode *p,void *v)//PROTO
{
    cgen(p,0);
    cgen(p,1);
    nltab();fprintf(code,"mul();");
    lvalue(p->right[0]);
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_expr_DIVASS_expr(parsenode *p,void *v)//PROTO
{
    cgen(p,0);
    cgen(p,1);
    nltab();fprintf(code,"div();");
    lvalue(p->right[0]);
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_expr_MODASS_expr(parsenode *p,void *v)//PROTO
{
    cgen(p,0);
    cgen(p,1);
    nltab();fprintf(code,"modulo();");
    lvalue(p->right[0]);
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_DBMINUS_expr(parsenode *p,void *v)//PROTO
{
    cgen(p,0);
    nltab();fprintf(code,"push(&ONE);");
    nltab();fprintf(code,"sub();");
    lvalue(p->right[0]);
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_DBPLUS_expr(parsenode *p,void *v)//PROTO
{
    cgen(p,0);
    nltab();fprintf(code,"push(&ONE);");
    nltab();fprintf(code,"add();");
    lvalue(p->right[0]);
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_expr_DBMINUS(parsenode *p,void *v)//PROTO
{
    cgen(p,0);
    nltab();fprintf(code,"dup();");
    nltab();fprintf(code,"push(&ONE);");
    nltab();fprintf(code,"sub();");
    lvalue(p->right[0]);
    nltab();fprintf(code,"pop();");
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_expr_DBPLUS(parsenode *p,void *v)//PROTO
{
    cgen(p,0);
    nltab();fprintf(code,"dup();");
    nltab();fprintf(code,"push(&ONE);");
    nltab();fprintf(code,"add();");
    lvalue(p->right[0]);
    nltab();fprintf(code,"pop();");
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_expr_PLUS_expr(parsenode *p,void *v)//PROTO
{
    double x1,x2;
    int f1=cgenv(p,0,&x1);
    int f2=cgenv(p,1,&x2);
        
    if( v==0 )
    {
        if( TOTAL(f1) && TOTAL(f2) )
        {
            pnumber(x1+x2);
        }
        else if( TOTAL(f1) && PARTIAL(f2) )
        {
            paddnum(x1+x2);
        }
        else if( TOTAL(f1) && WRITTEN(f2) )
        {
            paddnum(x1);
        }


        else if( PARTIAL(f1) && TOTAL(f2) )
        {
            paddnum(x1+x2);
        }
        else if( PARTIAL(f1) && PARTIAL(f2) )
        {
            nltab();fprintf(code,"add();");
            paddnum(x1+x2);
        }
        else if( PARTIAL(f1) && WRITTEN(f2) )
        {
            nltab();fprintf(code,"add();");
            paddnum(x1);
        }


        else if( WRITTEN(f1) && TOTAL(f2) )
        {
            paddnum(x2);
        }
        else if( WRITTEN(f1) && PARTIAL(f2) )
        {
            nltab();fprintf(code,"add();");
            paddnum(x2);
        }
        else if( WRITTEN(f1) && WRITTEN(f2) )
        {
            nltab();fprintf(code,"add();");
        }

    }
    else
    {
        if( TOTAL(f1) && TOTAL(f2) )
        {
            *(double*)v=x1+x2;
            return XNUM_TOTAL;
        }
        else if( TOTAL(f1) && PARTIAL(f2) )
        {
            *(double*)v=x1+x2;
            return XNUM_PARTIAL;
        }
        else if( TOTAL(f1) && WRITTEN(f2) )
        {
            *(double*)v=x1;
            return XNUM_PARTIAL;
        }


        else if( PARTIAL(f1) && TOTAL(f2) )
        {
            *(double*)v=x1+x2;
            return XNUM_PARTIAL;
        }
        else if( PARTIAL(f1) && PARTIAL(f2) )
        {
            nltab();fprintf(code,"add();");
            *(double*)v=x1+x2;
            return XNUM_PARTIAL;
        }
        else if( PARTIAL(f1) && WRITTEN(f2) )
        {
            nltab();fprintf(code,"add();");
            *(double*)v=x1;
            return XNUM_PARTIAL;
        }


        else if( WRITTEN(f1) && TOTAL(f2) )
        {
            *(double*)v=x2;
            return XNUM_PARTIAL;
        }
        else if( WRITTEN(f1) && PARTIAL(f2) )
        {
            nltab();fprintf(code,"add();");
            *(double*)v=x2;
            return XNUM_PARTIAL;
        }
        else if( WRITTEN(f1) && WRITTEN(f2) )
        {
            nltab();fprintf(code,"add();");
        }
    }

    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_expr_MINUS_expr(parsenode *p,void *v)//PROTO
{
    double x1,x2;
    int f1=cgenv(p,0,&x1);
    int f2=cgenv(p,1,&x2);
       
    if( v==0 )
    {
        if( TOTAL(f1) && TOTAL(f2) )
        {
            pnumber(x1-x2);
        }
        else if( TOTAL(f1) && PARTIAL(f2) )
        {
            paddneg(x2-x1);
        }
        else if( TOTAL(f1) && WRITTEN(f2) )
        {
            paddneg(-x1);
        }


        else if( PARTIAL(f1) && TOTAL(f2) )
        {
            paddnum(x1-x2);
        }
        else if( PARTIAL(f1) && PARTIAL(f2) )
        {
            nltab();fprintf(code,"sub();");
            paddnum(x1-x2);
        }
        else if( PARTIAL(f1) && WRITTEN(f2) )
        {
            nltab();fprintf(code,"sub();");
            paddnum(x1);
        }


        else if( WRITTEN(f1) && TOTAL(f2) )
        {
            paddnum(-x2);
        }
        else if( WRITTEN(f1) && PARTIAL(f2) )
        {
            nltab();fprintf(code,"sub();");
            paddnum(-x2);
        }
        else if( WRITTEN(f1) && WRITTEN(f2) )
        {
            nltab();fprintf(code,"sub();");
        }

    }
    else
    {
        if( TOTAL(f1) && TOTAL(f2) )
        {
            *(double*)v=x1-x2;
            return XNUM_TOTAL;
        }
        else if( TOTAL(f1) && PARTIAL(f2) )
        {
            nltab();fprintf(code,"signneg();");
            *(double*)v=x1-x2;
            return XNUM_PARTIAL;
        }
        else if( TOTAL(f1) && WRITTEN(f2) )
        {
            nltab();fprintf(code,"signneg();");
            *(double*)v=x1;
            return XNUM_PARTIAL;
        }


        else if( PARTIAL(f1) && TOTAL(f2) )
        {
            *(double*)v=x1-x2;
            return XNUM_PARTIAL;
        }
        else if( PARTIAL(f1) && PARTIAL(f2) )
        {
            nltab();fprintf(code,"sub();");
            *(double*)v=x1-x2;
            return XNUM_PARTIAL;
        }
        else if( PARTIAL(f1) && WRITTEN(f2) )
        {
            nltab();fprintf(code,"sub();");
            *(double*)v=x1;
            return XNUM_PARTIAL;
        }


        else if( WRITTEN(f1) && TOTAL(f2) )
        {
            *(double*)v=-x2;
            return XNUM_PARTIAL;
        }
        else if( WRITTEN(f1) && PARTIAL(f2) )
        {
            nltab();fprintf(code,"sub();");
            *(double*)v=-x2;
            return XNUM_PARTIAL;
        }
        else if( WRITTEN(f1) && WRITTEN(f2) )
        {
            nltab();fprintf(code,"sub();");
        }
    }
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_expr_STAR_expr(parsenode *p,void *v)//PROTO
{
    double x1,x2;
            
    int f1=cgenv(p,0,&x1);
    if( PARTIAL(f1) )
    {
        paddnum(x1);
        f1=XNUM_WRITTEN;
    }
            
    int f2=cgenv(p,1,&x2);
    if( PARTIAL(f2) )
    {
        paddnum(x2);
        f2=XNUM_WRITTEN;
    }
            
    if( TOTAL(f1) && TOTAL(f2) )
    {
        if( v )
        {
            *(double*)v=x1*x2;
            return XNUM_TOTAL;
        }
        else
        {
            pnumber(x1*x2);
        }
    }
    else if( TOTAL(f1) && WRITTEN(f2) )
    {
        pmulnum(x1);
    }
    else if( WRITTEN(f1) && TOTAL(f2) )
    {
         pmulnum(x2);
    }
    else if( WRITTEN(f1) && WRITTEN(f2) )
    {
         nltab();fprintf(code,"mul();");
    }

    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_expr_SLASH_expr(parsenode *p,void *v)//PROTO
{
    cgen(p,0);
    cgen(p,1);
    nltab();fprintf(code,"div();");
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_expr_MODULO_expr(parsenode *p,void *v)//PROTO
{
    cgen(p,0);
    cgen(p,1);
    nltab();fprintf(code,"modulo();");
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_expr_DBSTAR_expr(parsenode *p,void *v)//PROTO
{
    cgen(p,0);
    cgen(p,1);
    nltab();fprintf(code,"power();");
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_expr_PIPE_expr(parsenode *p,void *v)//PROTO
{
    cgen(p,0);
    nltab();fprintf(code,"if(TOP()->type==TYPE_NIL){");
    nltab();fprintf(code,"pop();");
    cgen(p,1);
    nltab();fprintf(code,"}");
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_MINUS_expr(parsenode *p,void *v)//PROTO
{
    double x;
    int f=cgenv(p,0,&x);

    if( v )
    {
        if( TOTAL(f) )
        {
            *(double*)v=-x;
            return XNUM_TOTAL;
        }
        else if( PARTIAL(f) )
        {
            nltab();fprintf(code,"signneg();");
            *(double*)v=-x;
            return XNUM_PARTIAL;
        }
        else if( WRITTEN(f) )
        {
            nltab();fprintf(code,"signneg();");
        }
    }
    else
    {
        if( TOTAL(f) )
        {
            pnumber(-x);
        }
        else if( PARTIAL(f) )
        {
            nltab();fprintf(code,"signneg();");
            paddnum(-x);
        }
        else if( WRITTEN(f) )
        {
            nltab();fprintf(code,"signneg();");
        }
    }
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_PLUS_expr(parsenode *p,void *v)//PROTO
{
    double x;
    int f=cgenv(p,0,&x);

    if( v )
    {
        if( TOTAL(f) )
        {
            *(double*)v=x;
            return XNUM_TOTAL;
        }
        else if( PARTIAL(f) )
        {
            *(double*)v=x;
            return XNUM_PARTIAL;
        }
        else if( WRITTEN(f) )
        {
            nltab();fprintf(code,"signpos();");
        }
    }
    else
    {
        if( TOTAL(f) )
        {
            pnumber(x);
        }
        else if( PARTIAL(f) )
        {
            paddnum(x);
        }
        else if( WRITTEN(f) )
        {
            nltab();fprintf(code,"signpos();");
        }
    }

    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_expr_EQEQ_expr(parsenode *p,void *v)//PROTO
{
    cmp_chain(p,"eqeq");
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_expr_EXEQ_expr(parsenode *p,void *v)//PROTO
{
    cmp_chain(p,"neeq");
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_expr_GTEQ_expr(parsenode *p,void *v)//PROTO
{
    cmp_chain(p,"gteq");
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_expr_LTEQ_expr(parsenode *p,void *v)//PROTO
{
    cmp_chain(p,"lteq");
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_expr_GT_expr(parsenode *p,void *v)//PROTO
{
    cmp_chain(p,"gt");
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_expr_LT_expr(parsenode *p,void *v)//PROTO
{
    cmp_chain(p,"lt");
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_expr_DOLLAR_expr(parsenode *p,void *v)//PROTO
{
    cgen(p,0);
    cgen(p,1);
    nltab();fprintf(code,"ss();"); //substring?
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_expr_OR_expr(parsenode *p,void *v)//PROTO
{
    cgen(p,0);
    nltab();fprintf(code,"if(flag()){");
    nltab();fprintf(code,"push(&TRUE);");
    nltab();fprintf(code,"}else{");
    cgen(p,1);
    nltab();fprintf(code,"}");
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_expr_AND_expr(parsenode *p,void *v)//PROTO
{
    cgen(p,0);
    nltab();fprintf(code,"if(!flag()){");
    nltab();fprintf(code,"push(&FALSE);");
    nltab();fprintf(code,"}else{");
    cgen(p,1);
    nltab();fprintf(code,"}");
    return 0;
}

//---------------------------------------------------------------------------
int codegen_expr_NOT_expr(parsenode *p,void *v)//PROTO
{
    cgen(p,0);
    nltab();fprintf(code,"topnot();");
    return 0;
}

//---------------------------------------------------------------------------
//outsource functions
//---------------------------------------------------------------------------
int outsource_bargument(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int outsource_bargument_lbarg(parsenode *p,void *v)//PROTO
{
    outsrc(p,0);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_bargument_STAR(parsenode *p,void *v)//PROTO
{
    fprintf(src,"*");
    return 0;
}

//---------------------------------------------------------------------------
int outsource_bargument_lbarg_COMMA_STAR(parsenode *p,void *v)//PROTO
{
    outsrc(p,0);
    fprintf(src,",*");
    return 0;
}

//---------------------------------------------------------------------------
int outsource_lbarg_SYMBOL(parsenode *p,void *v)//PROTO
{
    fprintf(src,"%s",p->right[0]->text);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_lbarg_lbarg_COMMA_SYMBOL(parsenode *p,void *v)//PROTO
{
    outsrc(p,0);
    fprintf(src,",");
    fprintf(src,"%s",p->right[1]->text);
    return 0;
}
 
//---------------------------------------------------------------------------
int outsource_lfuncpar(parsenode *p,void *v)//PROTO 
{
    return 0;
}

//---------------------------------------------------------------------------
int outsource_lfuncpar_parexpr(parsenode *p,void *v)//PROTO 
{
    outsrc(p,0);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_lfuncpar_lfuncpar0_COMMA_parexpr0(parsenode *p,void *v)//PROTO 
{
    outsrc(p,0);
    fprintf(src,",");
    outsrc(p,1);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_lfuncpar0_parexpr0(parsenode *p,void *v)//PROTO 
{
    outsrc(p,0);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_lfuncpar0_lfuncpar0_COMMA_parexpr0(parsenode *p,void *v)//PROTO 
{
    outsrc(p,0);
    fprintf(src,",");
    outsrc(p,1);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_parexpr0(parsenode *p,void *v)//PROTO 
{
    return 0;
}

//---------------------------------------------------------------------------
int outsource_parexpr0_parexpr(parsenode *p,void *v)//PROTO
{
    outsrc(p,0);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_parexpr_expr(parsenode *p,void *v)//PROTO
{
    outsrc(p,0);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_parexpr_STAR(parsenode *p,void *v)//PROTO
{
    fprintf(src,"*");
    return 0;
}

//---------------------------------------------------------------------------
int outsource_parexpr_STAR_LBRACKET_parexpr0_DOTDOT_parexpr0_RBRACKET(parsenode *p,void *v)//PROTO
{
    fprintf(src,"*[");
    outsrc(p,0);
    fprintf(src,"..");
    outsrc(p,1);
    fprintf(src,"]");
    return 0;
}

//---------------------------------------------------------------------------
int outsource_parexpr_AT_SYMBOL(parsenode *p,void *v)//PROTO
{
    fprintf(src,"@");
    fprintf(src,"%s",p->right[0]->text);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_parexpr_LBRACKET_SYMBOL_RBRACKET(parsenode *p,void *v)//PROTO
{
    fprintf(src,"[");
    fprintf(src,"%s",p->right[0]->text);
    fprintf(src,"]");
    return 0;
}

//---------------------------------------------------------------------------
int outsource_lexpr(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int outsource_lexpr_expr(parsenode *p,void *v)//PROTO
{
    outsrc(p,0);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_lexpr_lexpr0_COMMA_expr0(parsenode *p,void *v)//PROTO
{
    outsrc(p,0);
    fprintf(src,",");
    outsrc(p,1);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_lexpr0_expr0(parsenode *p,void *v)//PROTO
{
    outsrc(p,0);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_lexpr0_lexpr0_COMMA_expr0(parsenode *p,void *v)//PROTO
{
    outsrc(p,0);
    fprintf(src,",");
    outsrc(p,1);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr0(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr0_expr(parsenode *p,void *v)//PROTO
{
    outsrc(p,0);
    return 0;
}


//---------------------------------------------------------------------------
int outsource_msgpar(parsenode *p,void *v)//PROTO
{
    return 0;
}

//---------------------------------------------------------------------------
int outsource_msgpar_ASSIGN_expr(parsenode *p,void *v)//PROTO
{
    fprintf(src,":=");
    outsrc(p,0);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_msgpar_LPAR_lfuncpar_RPAR(parsenode *p,void *v)//PROTO
{
    fprintf(src,"(");
    outsrc(p,0);
    fprintf(src,")");
    return 0;
}

//---------------------------------------------------------------------------
int outsource_msgpar_LPAR_lfuncpar_RPAR_ASSIGN_expr(parsenode *p,void *v)//PROTO
{
    fprintf(src,"(");
    outsrc(p,0);
    fprintf(src,"):=");
    outsrc(p,1);
    return 0;
}


//---------------------------------------------------------------------------
//expr
//---------------------------------------------------------------------------
int outsource_expr_NUMBER(parsenode *p,void *v)//PROTO
{
    fprintf(src,"%s",p->right[0]->text);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_STRING(parsenode *p,void *v)//PROTO
{
    char *buf=strdup(p->right[0]->text);

    char *p0=buf;
    char *p1=buf;
    int qq=0;
    while( *p0 )
    {
        if( *p0=='\\' )
        {
            p0++;
        }

        if( *p0=='\'' )
        {
            qq=1;
        }
        
        *p1=*p0;
        p0++;
        p1++;
    }
    *p1=0;
    if( !qq )
    {
        buf[0]='\'';
        *(p1-1)='\'';
    }
    fprintf(src,"%s",buf);
    free(buf);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_NLSTEXT(parsenode *p,void *v)//PROTO
{
    fprintf(src,"@");
    outsource_expr_STRING(p,v);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_BINARYA(parsenode *p,void *v)//PROTO
{
    fprintf(src,"a");
    outsource_expr_STRING(p,v);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_BINARYX(parsenode *p,void *v)//PROTO
{
    fprintf(src,"%s",rtxt(p,0));
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_TRUE(parsenode *p,void *v)//PROTO
{
    fprintf(src,".t.");
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_FALSE(parsenode *p,void *v)//PROTO
{
    fprintf(src,".f.");
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_NIL(parsenode *p,void *v)//PROTO
{
    fprintf(src,"NIL");
    return 0;
}
 
//---------------------------------------------------------------------------
int outsource_expr_SYMBOL(parsenode *p,void *v)//PROTO
{
    fprintf(src,"%s",p->right[0]->text);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_SYMBOL_ARROW_SYMBOL(parsenode *p,void *v)//PROTO
{
    fprintf(src,"%s",p->right[0]->text);
    fprintf(src,"->");
    fprintf(src,"%s",p->right[1]->text);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_expr_COLON_SYMBOL_msgpar(parsenode *p,void *v)//PROTO
{
    outsrc(p,0);
    fprintf(src,":");
    fprintf(src,"%s",p->right[1]->text);
    outsrc(p,2);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_expr_COLON_LPAR_dotsymbol_RPAR_SYMBOL_msgpar(parsenode *p,void *v)//PROTO
//                 0               1              2      3
{
    char *t;
    outsrc(p,0);
    fprintf(src,":(");
    fprintf(src,"%s",t=dotsymboltext(p->right[1]));free(t);
    fprintf(src,")");
    fprintf(src,"%s",p->right[2]->text);
    outsrc(p,3);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_expr_COLON_LPAR_dotsymbol_AT_dotsymbol_RPAR_SYMBOL_msgpar(parsenode *p,void *v)//PROTO
//                 0               1            2              3      4
{
    char *t;
    outsrc(p,0);
    fprintf(src,":(");
    fprintf(src,"%s",t=dotsymboltext(p->right[1]));free(t);
    fprintf(src,"@");
    fprintf(src,"%s",t=dotsymboltext(p->right[2]));free(t);
    fprintf(src,")");
    fprintf(src,"%s",p->right[3]->text);
    outsrc(p,4);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_ddotsymbol_LPAR_lfuncpar_RPAR(parsenode *p,void *v)//PROTO
{
    char *t;
    fprintf(src,"%s",t=dotsymboltext(p->right[0]));free(t);
    fprintf(src,"(");
    outsrc(p,1);
    fprintf(src,")");
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_expr_COLCOL_expr(parsenode *p,void *v)//PROTO
{
    outsrc(p,0);
    fprintf(src,"::");
    outsrc(p,1);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_expr_COLCOLASS_expr(parsenode *p,void *v)//PROTO
{
    outsrc(p,0);
    fprintf(src,"::=");
    outsrc(p,1);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_LPAR_lexpr_RPAR(parsenode *p,void *v)//PROTO
{
    fprintf(src,"(");
    outsrc(p,0);
    fprintf(src,")");
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_LBRACE_PIPE_bargument_PIPE_lexpr_RBRACE(parsenode *p,void *v)//PROTO
{
    fprintf(src,"{|");
    outsrc(p,0);
    fprintf(src,"|");
    outsrc(p,1);
    fprintf(src,"}");
    return 0;
}


//---------------------------------------------------------------------------
int outsource_expr_LPAR_PIPE_bargument_PIPE_lexpr_RPAR(parsenode *p,void *v)//PROTO
{
    fprintf(src,"(|");
    outsrc(p,0);
    fprintf(src,"|");
    outsrc(p,1);
    fprintf(src,")");
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_IF_LPAR_expr_COMMA_expr_COMMA_expr_RPAR(parsenode *p,void *v)//PROTO
{
    fprintf(src,"if(");
    outsrc(p,0);
    fprintf(src,",");
    outsrc(p,1);
    fprintf(src,",");
    outsrc(p,2);
    fprintf(src,")");
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_LBRACE_lfuncpar_RBRACE(parsenode *p,void *v)//PROTO
{
    fprintf(src,"{");
    outsrc(p,0);
    fprintf(src,"}");
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_expr_LBRACKET_expr_RBRACKET(parsenode *p,void *v)//PROTO
{
    outsrc(p,0);
    fprintf(src,"[");
    outsrc(p,1);
    fprintf(src,"]");
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_expr_LBRACKET_parexpr0_DOTDOT_parexpr0_RBRACKET(parsenode *p,void *v)//PROTO
{
    outsrc(p,0);
    fprintf(src,"[");
    outsrc(p,1);
    fprintf(src,"..");
    outsrc(p,2);
    fprintf(src,"]");
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_expr_ASSIGN_expr(parsenode *p,void *v)//PROTO
{
    outsrc(p,0);
    fprintf(src,":=");
    outsrc(p,1);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_expr_ADDASS_expr(parsenode *p,void *v)//PROTO
{
    outsrc(p,0);
    fprintf(src,"+=");
    outsrc(p,1);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_expr_SUBASS_expr(parsenode *p,void *v)//PROTO
{
    outsrc(p,0);
    fprintf(src,"-=");
    outsrc(p,1);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_expr_MULASS_expr(parsenode *p,void *v)//PROTO
{
    outsrc(p,0);
    fprintf(src,"*=");
    outsrc(p,1);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_expr_DIVASS_expr(parsenode *p,void *v)//PROTO
{
    outsrc(p,0);
    fprintf(src,"/=");
    outsrc(p,1);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_expr_MODASS_expr(parsenode *p,void *v)//PROTO
{
    outsrc(p,0);
    fprintf(src,"%%=");
    outsrc(p,1);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_DBMINUS_expr(parsenode *p,void *v)//PROTO
{
    fprintf(src,"--");
    outsrc(p,0);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_DBPLUS_expr(parsenode *p,void *v)//PROTO
{
    fprintf(src,"++");
    outsrc(p,0);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_expr_DBMINUS(parsenode *p,void *v)//PROTO
{
    outsrc(p,0);
    fprintf(src,"--");
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_expr_DBPLUS(parsenode *p,void *v)//PROTO
{
    outsrc(p,0);
    fprintf(src,"++");
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_expr_PLUS_expr(parsenode *p,void *v)//PROTO
{
    outsrc(p,0);
    fprintf(src,"+");
    outsrc(p,1);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_expr_MINUS_expr(parsenode *p,void *v)//PROTO
{
    outsrc(p,0);
    fprintf(src,"-");
    outsrc(p,1);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_expr_STAR_expr(parsenode *p,void *v)//PROTO
{
    outsrc(p,0);
    fprintf(src,"*");
    outsrc(p,1);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_expr_SLASH_expr(parsenode *p,void *v)//PROTO
{
    outsrc(p,0);
    fprintf(src,"/");
    outsrc(p,1);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_expr_MODULO_expr(parsenode *p,void *v)//PROTO
{
    outsrc(p,0);
    fprintf(src,"%%");
    outsrc(p,1);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_expr_DBSTAR_expr(parsenode *p,void *v)//PROTO
{
    outsrc(p,0);
    fprintf(src,"**");
    outsrc(p,1);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_expr_PIPE_expr(parsenode *p,void *v)//PROTO
{
    outsrc(p,0);
    fprintf(src,"|");
    outsrc(p,1);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_MINUS_expr(parsenode *p,void *v)//PROTO
{
    fprintf(src,"-");
    outsrc(p,0);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_PLUS_expr(parsenode *p,void *v)//PROTO
{
    fprintf(src,"+");
    outsrc(p,0);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_expr_EQEQ_expr(parsenode *p,void *v)//PROTO
{
    outsrc(p,0);
    fprintf(src,"==");
    outsrc(p,1);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_expr_EXEQ_expr(parsenode *p,void *v)//PROTO
{
    outsrc(p,0);
    fprintf(src,"!=");
    outsrc(p,1);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_expr_GTEQ_expr(parsenode *p,void *v)//PROTO
{
    outsrc(p,0);
    fprintf(src,">=");
    outsrc(p,1);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_expr_LTEQ_expr(parsenode *p,void *v)//PROTO
{
    outsrc(p,0);
    fprintf(src,"<=");
    outsrc(p,1);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_expr_GT_expr(parsenode *p,void *v)//PROTO
{
    outsrc(p,0);
    fprintf(src,">");
    outsrc(p,1);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_expr_LT_expr(parsenode *p,void *v)//PROTO
{
    outsrc(p,0);
    fprintf(src,"<");
    outsrc(p,1);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_expr_DOLLAR_expr(parsenode *p,void *v)//PROTO
{
    outsrc(p,0);
    fprintf(src,"$");
    outsrc(p,1);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_expr_OR_expr(parsenode *p,void *v)//PROTO
{
    outsrc(p,0);
    fprintf(src,".or.");
    outsrc(p,1);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_expr_AND_expr(parsenode *p,void *v)//PROTO
{
    outsrc(p,0);
    fprintf(src,".and.");
    outsrc(p,1);
    return 0;
}

//---------------------------------------------------------------------------
int outsource_expr_NOT_expr(parsenode *p,void *v)//PROTO
{
    fprintf(src,"!");
    outsrc(p,0);
    return 0;
}

//---------------------------------------------------------------------------

