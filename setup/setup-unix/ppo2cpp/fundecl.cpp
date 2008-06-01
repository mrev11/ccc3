
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
#include <string.h>

extern char *current_namespace;
extern char *inner_namespace;

#define BUFSIZE 512

//--------------------------------------------------------------------------
typedef struct nsalias
{
   struct nsalias *previtem;
   char *name;
   char *alias;
}  NSALIAS;

static NSALIAS *alias_lastitem;

void fundecl_setalias(char*name, const char*alias)
{
    NSALIAS *a=(NSALIAS*)malloc(sizeof(NSALIAS));
    a->previtem=alias_lastitem;
    a->name=strdup(name);
    a->alias=strdup(alias);
    alias_lastitem=a;
}

static char *fundecl_getrealname(char*alias)
{
    NSALIAS *a=alias_lastitem;
    while( a!=0 )
    {
        if( 0==strcmp(alias,a->alias) )
        {
            return a->name;
        }
        a=a->previtem;
    }
    return alias;
}

//--------------------------------------------------------------------------
typedef struct elem
{
   struct elem *left;
   struct elem *right;
   char *text;
   char *nsinfo;
   int  info;
}  ELEM;

static ELEM *symtab_rootitem;

 
//--------------------------------------------------------------------------
void fundecl_ini()
{
    symtab_rootitem=0;
    alias_lastitem=0;
}

//--------------------------------------------------------------------------
static ELEM* insert(char *text, char *nsinfo, int info)
{
    ELEM *e=(ELEM*)malloc(sizeof(ELEM));

    e->left=0;
    e->right=0;
    e->text=strdup(text);
    e->nsinfo=nsinfo?strdup(nsinfo):0;
    e->info=info;
    
    //printf("insert [%s] [%s] [%d]\n",text,nsinfo?nsinfo:"",info);
    return e;
}
 
//--------------------------------------------------------------------------
static ELEM *fundecl_search(char *text)
{
    if( symtab_rootitem==0 )
    {
        return 0;
    }

    ELEM *elem=symtab_rootitem;
    int  cmp;

    while( 0!=(cmp=strcmp(elem->text,text)) )
    {
        if( cmp>0 )
        {
            if( elem->left )
            {
                elem=elem->left;
            }
            else
            {
                return 0;
            }
        }
        else if( cmp<0 )
        {
            if( elem->right )
            {
                elem=elem->right;
            }
            else
            {
                return 0;
            }
        }
    }

    return elem;
}


//--------------------------------------------------------------------------
static ELEM *fundecl_insert(char *text, char *nsinfo, int info)
{
    if( symtab_rootitem==0 )
    {
        return symtab_rootitem=insert(text,nsinfo,info);
    }

    ELEM *elem=symtab_rootitem;
    int  cmp;

    while( 0!=(cmp=strcmp(elem->text,text)) )
    {
        if( cmp>0 )
        {
            if( elem->left )
            {
                elem=elem->left;
            }
            else
            {
                return elem->left=insert(text,nsinfo,info);
            }
        }
        else if( cmp<0 )
        {
            if( elem->right )
            {
                elem=elem->right;
            }
            else
            {
                return elem->right=insert(text,nsinfo,info);
            }
        }
    }
    
    if( nsinfo )
    {
        if(elem->nsinfo)
        {
            free(elem->nsinfo);
        }
        elem->nsinfo=strdup(nsinfo);
    }
    if( info )
    {
        elem->info=info;
    }
    return elem;
}

//--------------------------------------------------------------------------
static int dotfirst(const char *txt)
{
    int i;
    for(i=0; txt[i]; i++)
    {
        if( txt[i]=='.' )
        {
            return i;
        }
    }
    return 0;
}

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

//--------------------------------------------------------------------------
int fundecl_using(char *fun, char*nsp)
{
    char buf[BUFSIZE];
    int dl=dotlast(fun);
    if( dl==0 )
    {
        sprintf(buf,"_clp_%s",fun);
    }
    else
    {
        fun[dl]=0x00;
        sprintf(buf,"%s._clp_%s",fun,fun+dl+1);
        fun[dl]='.';
    }

    int retcode=(0==fundecl_search(buf));
    fundecl_insert(buf,nsp,0);

    return retcode;  
    //retcode=1, ha nem volt benn korrábban
    //retcode=0, ha már benn volt (hiba)
}

//--------------------------------------------------------------------------
void fundecl_clpdef(char *fun,int stflag)
{
    char buf[BUFSIZE];
    int dl=dotlast(fun);
    if( dl==0 )
    {
        if( strstr(fun,"_clp_")==fun )
        {
            fun+=5;
        }
        sprintf(buf,"_clp_%s",fun);
    }
    else
    {
        fun[dl]=0x00;
        sprintf(buf,"%s._clp_%s",fun,fun+dl+1);
        fun[dl]='.';
    }
    fundecl_insert(buf,current_namespace,stflag);
}

//--------------------------------------------------------------------------
static char *fundecl_clpcallg(const char *fun)
{
    char buf[BUFSIZE];
    char buf1[BUFSIZE];
    int df=dotfirst(fun);
    int dl=dotlast(fun);

    if( dl==0 )
    {
        sprintf(buf1,"._clp_%s",fun);
    }
    else
    {
        //error: assignment of read-only location
        //fun[dl]=0x00;
        //sprintf(buf1,".%s._clp_%s",fun,fun+dl+1);
        //fun[dl]='.';

        //helyette
        sprintf(buf1,".%s",fun);
        sprintf(buf1+dl+2,"_clp_%s",fun+dl+1);
    }

    //buf1:  .[aa.bb.]_clp_cc

    fundecl_insert(buf1,0,0);

    int i=0,j=0;
    while( buf1[i] )
    {
        if( buf1[i]=='.' )
        {
            i++;
            buf[j++]=':';
            buf[j++]=':';
            if( strchr(buf1+i,'.') ) //ha namespace következik: _nsp_ prefix
            {
                buf[j++]='_';
                buf[j++]='n';
                buf[j++]='s';
                buf[j++]='p';
                buf[j++]='_';
            }
        }
        else
        {
            buf[j++]=buf1[i++];
        }
    }
    buf[j]=0x00; 

    //buf:  ::[aa::bb::]_clp_cc

    return strdup(buf);
}

//--------------------------------------------------------------------------
char *fundecl_clpcall(const char *fun)
{
    if( *fun=='.' )
    {
        return fundecl_clpcallg(fun+1);
    }

    char buf[BUFSIZE];
    char buf1[BUFSIZE];
    int df=dotfirst(fun);
    int dl=dotlast(fun);

    if( dl==0 )
    {
        sprintf(buf,"_clp_%s",fun);
    }
    else
    {
        //fun[dl]=0x00;
        //sprintf(buf,"%s._clp_%s",fun,fun+dl+1);
        //fun[dl]='.';

        //helyette
        sprintf(buf,"%s",fun);
        sprintf(buf+dl+1,"_clp_%s",fun+dl+1);
    }

    //buf: [aa.bb.]_clp_cc

    
    if( df==0 )
    {
        sprintf(buf1,"%s",buf);
    }
    else
    {
        buf[df]=0x00;
        char *ns=fundecl_getrealname(buf);
        sprintf(buf1,"%s.%s",ns,buf+df+1);
        buf[df]='.';
    }
    
    //buf1: [ns.bb.]_clp_cc

    ELEM *elem=fundecl_search(buf1);
    if( !elem )
    {
        elem=fundecl_insert(buf1,0,0);
    }

    if( (elem->nsinfo==0) ||
        ((current_namespace!=0) && (0==strcmp(elem->nsinfo,current_namespace))) )
    {
        sprintf(buf1,"%s",elem->text);
    }
    else
    {
        sprintf(buf1,"%s.%s",elem->nsinfo,elem->text);
    }

    //buf1: namespace._clp_cc

    int i=0,j=0;
    if( strchr(buf1,'.') ) //ha namespace következik: _nsp_ prefix
    {
        buf[j++]='_';
        buf[j++]='n';
        buf[j++]='s';
        buf[j++]='p';
        buf[j++]='_';
    }
    while( buf1[i] )
    {
        if( buf1[i]=='.' )
        {
            i++;
            buf[j++]=':';
            buf[j++]=':';
            if( strchr(buf1+i,'.') ) //ha namespace következik: _nsp_ prefix
            {
                buf[j++]='_';
                buf[j++]='n';
                buf[j++]='s';
                buf[j++]='p';
                buf[j++]='_';
            }
        }
        else
        {
            buf[j++]=buf1[i++];
        }
    }
    buf[j]=0x00; 

    //buf: namespace::_clp_cc

    return strdup(buf);
}

//--------------------------------------------------------------------------
void fundecl_codeblock(const char *fun,int cnt)
{
    char buf[BUFSIZE];
    char nsp[BUFSIZE]="";
    if( current_namespace )
    {
        strcat(nsp,current_namespace);
        strcat(nsp,".");
    }
    if( inner_namespace )
    {
        strcat(nsp,inner_namespace);
        strcat(nsp,".");
    }
    sprintf(buf,"%s_blk_%s_%d",nsp,fun,cnt);
    fundecl_insert(buf,0,2);
}

//--------------------------------------------------------------------------
void fundecl_statini(const char *fun,const char*var)
{
    char buf[BUFSIZE];
    char nsp[BUFSIZE]="";
    if( current_namespace )
    {
        strcat(nsp,current_namespace);
        strcat(nsp,".");
    }
    sprintf(buf,"%s_ini_%s_%s",nsp,fun,var);
    fundecl_insert(buf,0,3);
}

//--------------------------------------------------------------------------
void fundecl_locstatini(const char *fun,const char*var)
{
    char buf[BUFSIZE];
    char nsp[BUFSIZE]="";
    if( current_namespace )
    {
        strcat(nsp,current_namespace);
        strcat(nsp,".");
    }
    if( inner_namespace )
    {
        strcat(nsp,inner_namespace);
        strcat(nsp,".");
    }
    sprintf(buf,"%s_ini_%s_%s",nsp,fun,var);
    fundecl_insert(buf,0,4);
}


//--------------------------------------------------------------------------
void namespace_begin(char *ns)
{
    if( ns )
    {
        char *p=ns;
        printf( "\nnamespace _nsp_");
        while( *p )
        {
            if( *p=='.' )
            {
                printf("{\nnamespace _nsp_");
            }
            else
            {
                printf("%c",*p);
            }
            p++;
        }
        printf("{");
    }
}

//--------------------------------------------------------------------------
void namespace_end(char *ns)
{
    if( ns )
    {
        printf("\n}");
        char *p=ns;
        while( *p )
        {
            if( *p=='.' )
            {
                printf("}");
            }
            p++;
        }
        printf("//namespace %s",ns);
    }
}

//--------------------------------------------------------------------------
static char *nsprint(char *txt)
{
    static char *nmspac=0;

    char *ns1=0;
    char *name=txt;

    char *lastdot=0;
    int i=0;
    while( txt && txt[i]  )
    {
        if( txt[i]=='.' )
        {
            lastdot=txt+i;
        }
        i++;
    }
    if( lastdot )
    {
        *lastdot=0x00;
        ns1=strdup(txt);
        *lastdot='.';
        name=lastdot+1;
    }
    
    if( (nmspac!=0) && ((ns1==0) || (strcmp(nmspac,ns1)!=0)) )
    {
        namespace_end(nmspac);
        free(nmspac);
        nmspac=0;
    }

    if( (ns1!=0) && ((nmspac==0) || (strcmp(nmspac,ns1)!=0)) )
    {
        printf("\n");
        namespace_begin(ns1);
        nmspac=ns1;
    }
    
    return name;
}

//--------------------------------------------------------------------------
static void walk(ELEM *elem)
{
    if( elem->left )
    {
        walk(elem->left);
    }
    
    switch( elem->info )
    {
        case 0:
            printf("\nextern void %s(int argno);",nsprint(elem->text));
            //?printf("\nextern void _clp_%s(int argno);",nsprint(elem->text));
            break;

        case 1:
            printf("\nstatic void %s(int argno);",nsprint(elem->text));
            //?printf("\nstatic void _clp_%s(int argno);",nsprint(elem->text));
            break;

        case 2:
            printf("\nstatic void %s(int argno);",nsprint(elem->text));
            //?printf("\nstatic void _blk_%s(int argno);",nsprint(elem->text));
            break;

        case 3:
            printf("\nstatic void %s();",nsprint(elem->text));
            //?printf("\nstatic void _ini_%s();",nsprint(elem->text));
            break;

        case 4:
            printf("\nstatic void %s(VALUE*);",nsprint(elem->text));
            //?printf("\nstatic void _ini_%s(VALUE*);",nsprint(elem->text));
            break;
    }


    if( elem->right )
    {
        walk(elem->right);
    }
}
 

//--------------------------------------------------------------------------
static void walk0(ELEM *elem)
{
    //Átmásolja a fát, miközben
    //konkatenál: text:=nsinfo+text,
    //elhagyja text-ből a globális névteret jelző '.'-ot,
    //rendeződik az új tábla az új text szerint.

    if( elem->left )
    {
        walk0(elem->left);
    }

    char buf[BUFSIZE];
    if( elem->nsinfo )
    {
        sprintf(buf,"%s.%s",elem->nsinfo,elem->text);
    }
    else if( (*elem->text)=='.' )
    {
        sprintf(buf,"%s",elem->text+1);
    }
    else
    {
        sprintf(buf,"%s",elem->text);
    }
    fundecl_insert(buf,0,elem->info);
    
    if( elem->right )
    {
        walk0(elem->right);
    }
}

//--------------------------------------------------------------------------
void fundecl_list()
{
    ELEM *symtab_save;
    symtab_save=symtab_rootitem;
    symtab_rootitem=0;

    if( symtab_save )
    {
        walk0(symtab_save);
    }

    if( symtab_rootitem )
    {
        walk(symtab_rootitem);
        nsprint(0);
        printf("\n");
    }
}

//--------------------------------------------------------------------------

