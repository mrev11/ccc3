
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

//Clipper ?, ??, set printer, ...

#ifdef _UNIX_
#include <sys/wait.h>
#endif

#include <stdio.h>
#include <ctype.h>
#include <wctype.h>
#include <wchar.h>
#include <cccapi.h>
#include <fileio.ch>

//#include <remoteio.h>
extern int  remopen(int fp, char *fname, int additive);
extern void remclose(int fp);
extern void remwrite(int fp, char *data, int datalen);
 
//------------------------------------------------------------------------
#define FP_CONSOLE    0
#define FP_PRINTER    1
#define FP_ALTERNATE  2 
#define FP_EXTRA      3
#define FP_ERROR      4

static struct
{
    int  flag;             //kell-e a csatornára küldeni
    FILE *fp;              //local FILE pointer
    const char *def;       //default file/device név
    int  remstat;          //0:alapállapot, 1:remote nyitva, -1:nem nyitható
} outfile[5] = 
{
    {1, NULL   , "CON" , 0},
    {0, NULL   , "PRN" , 0},
    {0, NULL   , NULL  , 0},
    {0, NULL   , NULL  , 0},
    {0, NULL   , "CON" , 0}
};


DEFINE_METHOD(attrvals);
DEFINE_METHOD(classname);

//------------------------------------------------------------------------
// SET FILE/MODE
//------------------------------------------------------------------------
static int locopen(int x, char *fname, int additive)
{
    if( x==FP_CONSOLE && fileno(stdout)>=0 )
    {
        outfile[FP_CONSOLE].fp=stdout;
    }
    else if( x==FP_ERROR && fileno(stderr)>=0 )
    {
        outfile[FP_ERROR].fp=stderr;
    }
    else
    {
        FILE *file=0;
        #ifdef _UNIX_
            // Windowson fopen() kezeli az eszközöket
            // (mint CON:, NUL:, LPT1:, LPT2:, stb.),
            // a UNIX-os fopen ezeket nem ismeri,
            // ezért van szükség a plusz rétegre.
            // (csak DOSCONV ON esetén számít)

            int fd=-1;
            if( additive )
            {
                stringnb(fname);
                number(FO_READWRITE);
                _clp_fopen(2);
                fd=D2INT(TOP()->data.number);
                POP();
                //nincs szükség lseek-re
            }
            if( fd<0 )
            {
                stringnb(fname);
                number(FC_NORMAL);
                _clp_fcreate(2);
                fd=D2INT(TOP()->data.number);
                POP();
            }
            if( fd>=0 )
            {
                file=fdopen(fd,additive?"ab":"wb");
            }
        #else
            //file=fopen(fname,additive?"ab":"wb");
            CHAR*wfn=utf8_to_wchar(fname,strlen(fname),0);
            file=_wfopen(wfn,additive?L"ab":L"wb");
            free(wfn);
        #endif

        outfile[x].fp=file;
    }

    return outfile[x].fp!=0;
}

//------------------------------------------------------------------------
static void locclose(int x)
{
    if( x==FP_CONSOLE )
    {
        fflush(stdout);
        outfile[FP_CONSOLE].fp=NULL;
    }
    else if( x==FP_ERROR )
    {
        fflush(stderr);
        outfile[FP_ERROR].fp=NULL;
    }
    else if( outfile[x].fp )
    {
        fclose(outfile[x].fp);
        outfile[x].fp=NULL;
    }
    #ifdef _UNIX_
        // A printelés elindít egy child processt,
        // aminek a befejeződése után zombi keletkezik,
        // itt ezeket a zombikat lőjük lefele.
        int stat;
        waitpid(-1,&stat,WNOHANG);
    #endif
}

//------------------------------------------------------------------------
static void setfp(int argno,int x) // file/mode
{
VALUE *base=stack-argno;
stack=base+min(argno,2);
while(stack<base+2)PUSHNIL();
//
    convertfspec2nativeformat(base);

    VALUE *f=base;         //filename
    VALUE *m=base+1;       //mode (additive)
    char *fname;
    int additive;

    if( outfile[x].fp ) //ha lokálisan nyitva
    {
        locclose(x); //lezárni
    }

    if( outfile[x].remstat>0 ) //ha remote nyitva
    {
        remclose(x); //lezárni
        outfile[x].remstat=0;
    }

    if( (f->type==TYPE_BINARY) && (f->data.string.len>0) )
    {
        fname=BINARYPTR(f);
    }
    else
    {
        fname=NULL;
    }

    if( m->type==TYPE_FLAG && m->data.flag )
    {
        additive=1;
    }
    else
    {
        additive=0;
    }

    if( fname )
    {
        if( outfile[x].remstat==0 ) // remote nyitható
        {
            int rop=remopen(x,fname,additive);
            outfile[x].remstat=(rop?1:-1);
            //printf("REMOPEN %s %d\n",fname,rop);fflush(0);
        }

        if( outfile[x].remstat<=0 ) // nincs nyitva remote
        {
            int lop=locopen(x,fname,additive); //megnyitni lokálisan
            //printf("LOCOPEN %s %d\n",fname,lop);fflush(0);
        }
    }
//    
stack=base;
PUSH(&NIL);
}

//------------------------------------------------------------------------
void _clp___printer(int argno){setfp(argno,FP_PRINTER);}
void _clp___alternate(int argno){setfp(argno,FP_ALTERNATE);}
void _clp___extra(int argno){setfp(argno,FP_EXTRA);}


//------------------------------------------------------------------------
// SET ON/OFF
//------------------------------------------------------------------------
static void setonoff(int argno, int x)
{
VALUE *base=stack-argno;
stack=base+min(argno,1);
while(stack<base+1)PUSHNIL();
//
    VALUE *newset=base;
    int oldset=outfile[x].flag;
    
    if( newset->type==TYPE_FLAG )
    {
        outfile[x].flag=(0!=newset->data.flag);
    }
    else if( newset->type==TYPE_STRING )
    {
        //outfile[x].flag=!wcscasecmp(STRINGPTR(newset),L"ON");
        //there is not wcscasecmp, workaround:
        CHAR *p=STRINGPTR(newset);
        outfile[x].flag=(towupper(p[0])=='O')&&(towupper(p[1])=='N');
    }

    logical(oldset);
//    
RETURN(base);
}

//------------------------------------------------------------------------
void _clp_setconsole(int argno){setonoff(argno,FP_CONSOLE);}
void _clp_setprinter(int argno){setonoff(argno,FP_PRINTER);}
void _clp_setalternate(int argno){setonoff(argno,FP_ALTERNATE);}
void _clp_setextra(int argno){setonoff(argno,FP_EXTRA);}


//------------------------------------------------------------------------
// QOUT/QQOUT/__EJECT/OUTERR/OUTSTD
//------------------------------------------------------------------------
static void print_bin(int x)
{
    unsigned len=TOP()->data.binary.len;
    if( len )
    {
        if( outfile[x].remstat>0  )
        {
            remwrite(x,BINARYPTR(TOP()),len);
        }
        if( outfile[x].fp )
        {
            int retcode=fwrite(BINARYPTR(TOP()),1,len,outfile[x].fp);
            fflush(outfile[x].fp);
        }
    }
    POP();
}

//------------------------------------------------------------------------
static void print_str(int x)
{
    str2bin(TOP());
    print_bin(x);
}

//------------------------------------------------------------------------
static int out0(int x)
{
    if( (outfile[x].fp==0)  && 
        (outfile[x].remstat==0)  && 
        (outfile[x].def!=0) )
    {
        //nincs megnyitva, 
        //de van default filé,
        //röptében megnyitja
        
        stringnb(outfile[x].def);
        setfp(1,x);
        pop();
    }
    return (outfile[x].fp!=NULL) || (outfile[x].remstat>0);
}

//------------------------------------------------------------------------
static void out1(int x, VALUE *v)
{
    if( !out0(x) )
    {
        return;
    }

    VALUE *base=stack;

    switch( v->type )
    {
        case TYPE_NIL:
            string(L"NIL");
            print_str(x);
            break;

        case TYPE_NUMBER:
            number(v->data.number);
            _clp_str(1);
            print_str(x);
            break;

        case TYPE_DATE:
            date(v->data.date);
            _clp_dtoc(1);
            print_str(x);
            break;

        case TYPE_POINTER:
            pointer(v->data.pointer);
            _clp_l2hex(1);
            print_str(x);
            break;

        case TYPE_BINARY:
            if( v->data.string.len>0 )
            {
                PUSH(v);
                print_bin(x);
            }
            break;

        case TYPE_STRING:
            if( v->data.string.len>0 )
            {
                PUSH(v);
                print_str(x);
            }
            break;

        case TYPE_FLAG:
            stringnb(v->data.flag?".T.":".F.");
            print_str(x);
            break;

        case TYPE_ARRAY:
        {
            string(L"{");
            print_str(x);
            

            for(int i=0;i<v->data.array.oref->length;i++)
            {
                if(i)
                {
                   string(L",");
                   print_str(x);
                }
                push(v->data.array.oref->ptr.valptr+i);
                out1(x,TOP());
                pop();
            }

            string(L"}");
            print_str(x);
            break;
        }

        case TYPE_OBJECT:
        {
            string(L"<");
            print_str(x);
            push_symbol(v);
            _o_method_classname.eval(1);
            print_str(x);
            string(L">");
            print_str(x);
 
            push_symbol(v);
            _o_method_attrvals.eval(1);
            out1(x,TOP());
            pop();
 
            break;
        }

        case TYPE_BLOCK:
            string(L"block");
            print_str(x);
            break;
    }

    stack=base;
}

//------------------------------------------------------------------------
static void out(VALUE *v)
{
    int i;
    for( i=0; i<4; i++ )
    {
        if( outfile[i].flag )
        {
            out1(i,v);
        }
    }
}   

//------------------------------------------------------------------------
void _clp_qqout(int argno)
{
    VALUE *base=stack-argno;
    for(int i=0; i<argno; i++)
    {
        if(i>0)
        {
            string(L" ");
            out( TOP() );
            pop();
        }
        out(base+i);
    }
    stack=base;
    PUSH(&NIL);
}

//------------------------------------------------------------------------
void _clp_qout(int argno)
{
    _clp_endofline(0);
    _clp_qqout(1);
    pop();
    _clp_qqout(argno);
}    

//------------------------------------------------------------------------
void _clp_print(int argno)
{
    VALUE *base=stack-argno;
    push_call("print",base);
    if( (argno<1) || (str2bin(base),(base->type!=TYPE_BINARY)) )
    {
        ARGERROR();
    }

    char *file=_parb(1);
    int len=_parblen(1);
    for(int i=1; i<argno; i++)
    {
        for(int j=0; j<len; j++)
        {
            switch( tolower(file[j]) )
            {
                case 'c': out1(FP_CONSOLE,base+i);break;
                case 'p': out1(FP_PRINTER,base+i);break;
                case 'a': out1(FP_ALTERNATE,base+i);break;
                case 'e': out1(FP_EXTRA,base+i);break;
            }
        }
    }

    pop_call();
    stack=base;
    PUSH(&NIL);
}

//------------------------------------------------------------------------
void _clp___eject(int argno)
{
    VALUE *base=stack-argno;
    if( outfile[FP_PRINTER].fp!=NULL )
    {
        number(12); _clp_chr(1);
        number(13); _clp_chr(1);
        add();
        out1(FP_PRINTER,TOP());
    }
    stack=base;
    PUSH(&NIL);
}

//------------------------------------------------------------------------
void _clp_outstd(int argno)
{
    VALUE *base=stack-argno;
    for(int i=0; i<argno; i++)
    {
        if(i>0)
        {
            string(L" ");
            out1(FP_CONSOLE,TOP());
            pop();
        }
        out1(FP_CONSOLE,base+i);
    }
    stack=base;
    PUSH(&NIL);
}

//------------------------------------------------------------------------
void _clp_outerr(int argno)
{
    VALUE *base=stack-argno;
    for(int i=0; i<argno; i++)
    {
        if(i>0)
        {
            string(L" ");
            out1(FP_ERROR,TOP());
            pop();
        }
        out1(FP_ERROR,base+i);
    }
    stack=base;
    PUSH(&NIL);
}

//------------------------------------------------------------------------
void _clp_fflush(int argno)
{
    CCC_PROLOG("fflush",1);
    if( ISNIL(1) )
    {
        fflush(0);
    }
    else
    {
        int x=_parni(1);
        if( 0<=x && x<5 )
        {
            fflush(outfile[x].fp);
        }
    }
    _ret();
    CCC_EPILOG();
}

//------------------------------------------------------------------------
