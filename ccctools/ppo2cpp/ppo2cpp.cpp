
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

#include <lexer.h>
#include <parser.h>
#include <decllist.h>
#include <parsenode.h>
#include <nodetab.h>

extern void* ParseAlloc(void*(*)(size_t)); 
extern void  ParseFree(void*,void(*)(void*)); 
extern void  ParseTrace(FILE*,const char*); 
extern void  Parse(void*,int,parsenode*);  //3th arg: %token_type {parsenode*} 

static const char *version_number="5.7.1";

ppo2cpp_lexer *lexer;

FILE *diag;
FILE *code;
int debug=0;

nodetab *nodetab_globstat=new nodetab();     //külső static változók
nodetab *nodetab_locstat=new nodetab();      //belsó static változók
nodetab *nodetab_local=new nodetab();        //local változók

nodetab *nodetab_blkarg=new nodetab();       //kódblokk argumentumok
nodetab *nodetab_blkenv=new nodetab();       //kódblokk változók
nodetab *nodetab_block=new nodetab();        //kódblokkok


char *current_namespace=0;
char *inner_namespace=0;

//----------------------------------------------------------------------------
int main(int argc, char**argv)
{
    if( getenv("CPPSTANDARD") )
    {
        fprintf(stderr, "%s (c++%ld) %s\n",__VERSION__,__cplusplus, argv[0]);
        exit(0);
    }

    int fd=0;
    char input[256]="";
    char output[256]="";
    char ppo2cpp_code[256]="";
    char ppo2cpp_diag[256]="";
    char ppo2cpp_meth[256]="";
    lexer=new ppo2cpp_lexer(fd);
    int quiet=0, veronly=0;

    int i;
    for( i=1; i<argc; i++ )
    {
        if( *argv[i]=='-' )
        {
            //opciók;

            if( argv[i][1]=='d' )
            {
                debug=1;
                lexer->setdebugflag(1);
            }

            else if( argv[i][1]=='o' )
            {
                strcpy(output,&argv[i][2]);
            }

            else if( argv[i][1]=='v' )
            {
                veronly=1; //csak verziószám
            }

            else if( argv[i][1]=='q' )
            {
                quiet=1; //nem írja ki a verziószáot
            }

            else if( argv[i][1]=='x' )
            {
                veronly=1; //csak verziószám
                quiet=1; //nem írja ki a verziószáot
            }
        }
        else
        {
            strcpy(input,argv[i]);
            lexer->setinputfspec(argv[i]);
        }
    }
    
    if( !quiet )
    {
        printf("Clipper/C++ Compiler %s Copyright (C) ComFirm Bt.\n",version_number);
    }

    if( veronly )
    {
        exit(0);
    }
    
    if( *input )
    {
        fd=open(input,0);
        if( fd<0 )
        {
            fprintf(stderr,"\nInput (%s) not found.",input);
            exit(1); 
        }
        lexer->setinputfd(fd);
    
        if( !*output )
        {
            char *p;
            strcpy(output,input);
            if( (0!=(p=strrchr(output,'.'))) && 
                (0==strchr(p,'\\')) && 
                (0==strchr(p,'/')) )
            {
                *p=0x00;
            }
            strcat(output,".cpp");
        }

//        strcpy(ppo2cpp_code,input);strcat(ppo2cpp_code,".code");
//        strcpy(ppo2cpp_diag,input);strcat(ppo2cpp_diag,".diag");
//        strcpy(ppo2cpp_meth,input);strcat(ppo2cpp_meth,".meth");

        {//code
            char *p;
            strcpy(ppo2cpp_code,input);
            if( (0!=(p=strrchr(ppo2cpp_code,'.'))) && 
                (0==strchr(p,'\\')) && 
                (0==strchr(p,'/')) )
            {
                *p=0x00;
            }
            strcat(ppo2cpp_code,".code");
        }

        {//diag
            char *p;
            strcpy(ppo2cpp_diag,input);
            if( (0!=(p=strrchr(ppo2cpp_diag,'.'))) && 
                (0==strchr(p,'\\')) && 
                (0==strchr(p,'/')) )
            {
                *p=0x00;
            }
            strcat(ppo2cpp_diag,".diag");
        }

        {//meth
            char *p;
            strcpy(ppo2cpp_meth,input);
            if( (0!=(p=strrchr(ppo2cpp_meth,'.'))) && 
                (0==strchr(p,'\\')) && 
                (0==strchr(p,'/')) )
            {
                *p=0x00;
            }
            strcat(ppo2cpp_meth,".meth");
        }
    }

    code=fopen(ppo2cpp_code,"w");
    diag=fopen(ppo2cpp_diag,"w");

    fundecl_ini();
    flddecl_ini();
    metdecl_ini();

    void *parser=ParseAlloc(malloc); 

    if(debug)
    {
        ParseTrace(diag,">> ");
    }
    
    parsenode *node;
    while( 0!=(node=lexer->getnext()) )
    {
        Parse(parser,node->tokenid,node);
    }

    Parse(parser,0,0);
    ParseFree(parser,free);
    delete lexer;

    fclose(diag);
    fclose(code);

    // 2009.12.10
    // először kell kiírni fundecl_list-et
    // azután  kell kiírni metdecl_list-et
    // csakhogy metdecl_list-nek járuléka van fundecl_list-ben
    // ezért kétszer kell futtatni (az első kimenet ppo2cpp.meth-be)
    void *retcode=freopen(ppo2cpp_meth,"w+",stdout); //warning: ignoring return value
    metdecl_list();

    if( *output )
    {
        void *retcode=freopen(output,"w+",stdout); //warning: ignoring return value
    }

    printf("//input: %s (%s)\n\n",input,version_number);
    printf("#include <cccdef.h>\n");

    fundecl_list();
    flddecl_list();
    metdecl_list();

    code=fopen(ppo2cpp_code,"r");
    namespace_begin(current_namespace,stdout);
    int c;
    while( EOF!=(c=fgetc(code)) )
    {
        putchar(c);
    }
    namespace_end(current_namespace,stdout);
    putchar('\n');
    
    fclose(code);
    
    if( !debug )
    {
        remove(ppo2cpp_code);
        remove(ppo2cpp_diag);
        remove(ppo2cpp_meth);
    }

    return 0;
}

//----------------------------------------------------------------------------

