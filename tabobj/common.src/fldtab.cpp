
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

#include <stdio.h>
#include <string.h>
#include <cccapi.h>

DEFINE_METHOD(args);
DEFINE_METHOD(description);
DEFINE_METHOD(operation);


#define MAXFIELD  1024

typedef struct
{
  char  *alias;    //alias nev
  char  *field;    //mezo nev
  VALUE codeblk;   //oszlop blokk
  int   ninsert;   //ellenorzo szam
} FIELDREF;


static FIELDREF ftab[MAXFIELD];
static int ninsert=0;
static int lastpos=0;
static int initflag=0;


//----------------------------------------------------------------------
void _clp__field_insert(int argno)
{
    CCC_PROLOG("_field_insert",3);
    
    if( !initflag )
    {
        memset((void*)ftab,0,sizeof(ftab));
        initflag=1;
    }
    
    if( 0==++ninsert )
    {
        ninsert++;
    }
    
    int n=lastpos;
    while( ftab[n].ninsert )
    {
        if( MAXFIELD<=++n ) n=0;
        if( n==lastpos ) 
        {
            fprintf(stderr,"\nftab overflow");
            fflush(0);
            exit(1);
        }
    }
    lastpos=n;

    ftab[n].alias   = strdup((str2bin(base),_parb(1)));
    ftab[n].field   = strdup((str2bin(base+1),_parb(2)));
    ftab[n].codeblk = *PARPTR(3);
    ftab[n].ninsert = ninsert;

    //printf("_field_insert %3d %3d %s %s\n",lastpos,ninsert,_parb(1),_parb(2));
    
    _ret();
    CCC_EPILOG();
}

//----------------------------------------------------------------------
void _clp__field_delete(int argno)
{
    CCC_PROLOG("_field_delete",1);
    char *alias=(str2bin(base),_parb(1));
    int n;
    
    //printf("_field_delete %s\n",alias);
    
    if( initflag )
    {
        for(n=0; n<MAXFIELD; n++)
        {
            if( (ftab[n].alias!=NULL)  && (0==strcasecmp(ftab[n].alias,alias)) )
            {
                //printf("_field_delete %3d %3d %s %s\n",n,ftab[n].ninsert,ftab[n].alias,ftab[n].field);
                if(ftab[n].alias){free(ftab[n].alias); ftab[n].alias=NULL;}
                if(ftab[n].field){free(ftab[n].field); ftab[n].field=NULL;}
                ftab[n].ninsert = 0;
            }
        }
    }
    _ret();
    CCC_EPILOG();
}

//----------------------------------------------------------------------
static void fsearch_error(const char*alias, const char*field)
{
    fprintf(stderr,"invalid field reference: %s->%s\n",alias,field);fflush(0);
    _clp_errornew(0);
    DUP();stringnb("invalid field reference");_o_method_description.eval(2);POP();
    DUP();stringnb("dbfield:fsearch");_o_method_operation.eval(2);POP();
    DUP();stringnb(alias);stringnb(field);array(2);_o_method_args.eval(2);POP();
    _clp_break(1);
}

//----------------------------------------------------------------------
#ifndef CLASS_DBFIELD

class dbfield
{
    const char *alias;
    const char *field;
    int  ftabidx;
    int  ninsert;
    void fsearch(void);

  public:
    dbfield(char*a,char*f);
    dbfield(const char*a,const char*f);
    void fget(void);
    void fput(void);
};

#define CLASS_DBFIELD
#endif


//----------------------------------------------------------------------
dbfield::dbfield(char*a, char*f)
{
    ftabidx=-1;
    alias=(const char*)a;
    field=(const char*)f;
};

//----------------------------------------------------------------------
dbfield::dbfield(const char*a, const char*f)
{
    ftabidx=-1;
    alias=a;
    field=f;
};

//----------------------------------------------------------------------
void dbfield::fsearch(void)
{
    ftabidx=-1;
    int n;

    if( initflag )
    {
        for(n=0; n<MAXFIELD; n++)
        {
            //printf("\nfsearch %d %s %s %s %s",
            //       n,
            //       alias,
            //       field,
            //       (ftab[n].alias?ftab[n].alias:"????"),
            //       (ftab[n].field?ftab[n].field:"????") );
        
            if( ftab[n].alias && (strcasecmp(ftab[n].alias,alias)==0) &&
                ftab[n].field && (strcasecmp(ftab[n].field,field)==0) )
            {
                ftabidx=n;
                ninsert=ftab[n].ninsert;
                return;
            }
        }
    }
    fsearch_error(alias,field);
}

//----------------------------------------------------------------------
void dbfield::fget(void)  //stack:   --- value
{
    if( (ftabidx<0) || ftab[ftabidx].ninsert!=ninsert )
    {
        fsearch();
    }
    PUSH(&ftab[ftabidx].codeblk);
    _clp_eval(1);
}

//----------------------------------------------------------------------
void dbfield::fput(void)  //stack: value --- value
{
    if( (ftabidx<0) || ftab[ftabidx].ninsert!=ninsert )
    {
        fsearch();
    }
    DUP();
    *TOP2()=ftab[ftabidx].codeblk;
    _clp_eval(2);
}

//----------------------------------------------------------------------
