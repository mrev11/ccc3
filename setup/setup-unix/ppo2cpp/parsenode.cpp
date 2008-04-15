
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
#include <stdarg.h>
#include <parser.h>
#include <parsenode.h>
 
int parsenode::cnt_constructor=0;
int parsenode::cnt_destructor=0;
parsenode *parsenode::start_node=0;
parsenode *parsenode::last_node=0;

extern FILE *diag;
 
//---------------------------------------------------------------------------
parsenode::parsenode()
{
    cnt_constructor++;
    nodeid=cnt_constructor;

    tokenid=0;
    text=0;
    codegen=0;
    outsource=0;
    lineno=0;
    cargo=0;
    right=0;
    next=0;
    prev=0;

    if( last_node==0 )
    {
        start_node=this;
        last_node=this;
    }
    else
    {
        last_node->next=this;
        this->prev=last_node;
        last_node=this;
    }
}

//---------------------------------------------------------------------------
parsenode::~parsenode()
{
    //print();

    
    if( this==start_node )
    {
        start_node=this->next;
    }
    if( this==last_node )
    {
        last_node=this->prev;
    }
    if( this->next )
    {
        this->next->prev=this->prev;
    }
    if( this->prev )
    {
        this->prev->next=this->next;
    }


    cnt_destructor++;

    if( tokenid>0 && text!=0 ) 
    {
        free((void*)text);
    }

    if( right )
    {
        int i=0;
        parsenode *p;
        while( 0!=(p=*(right+i++)) )
        {
            delete p;
        }
        free(right);
    }
}

 
//---------------------------------------------------------------------------
parsenode *parsenode::token(int id, char *txt, int line)
{
    //Használat: (new parsenode())->token(id,txt,line);

    tokenid=id;
    text=txt;
    lineno=line;
    return this;
}
 
//---------------------------------------------------------------------------
parsenode *parsenode::rule(int rlen,...)
{
    right=(parsenode**)malloc( (rlen+1)*sizeof(void*) );
    
    int i;
    va_list ap;
    va_start(ap,rlen);
    for(i=0; i<rlen; i++)
    {
        *(right+i)=va_arg(ap,parsenode*);
    }
    *(right+i)=0;

    if( right[0] )
    {
        lineno=right[0]->lineno;
    }
    return this;
}

//---------------------------------------------------------------------------
void parsenode::print(const char *prompt)
{
    fprintf(diag,"--------%s--------\n",prompt);
    fprintf(diag,"nodeid   %d\n",nodeid);
    fprintf(diag,"tokenid  %d\n",tokenid);
    fprintf(diag,"text     %s\n",text);
    fprintf(diag,"cargo    %x\n",cargo);
    fprintf(diag,"lineno   %d\n",lineno);

    #ifdef RIGHT
    fprintf(diag,"right   ");
    if( right )
    {
        int i=0;
        parsenode *p;
        while( 0!=(p=*(right+i++)) )
        {
            fprintf(diag," %d",p->nodeid);
            fflush(0); 
        }
    }
    fprintf(diag,"\n~\n");
    #endif

    fflush(0);
}

//---------------------------------------------------------------------------
void parsenode::walk()
{
    parsenode *p=start_node;
    while( p )
    {
        p->print("walk");
        p=p->next;
    }
}

//---------------------------------------------------------------------------
void parsenode::tprint(int indent)
{
    if( tokenid==NL )
    {
        return;
    }

    printf("%*s%s (%d,%d)\n",indent,"",text,tokenid,cargo);
    
    if( right )
    {
        int i=0;
        parsenode *p;
        while( 0!=(p=*(right+i++)) )
        {
            p->tprint(indent+2); //rekurzió
        }
    }
}

//---------------------------------------------------------------------------
 
