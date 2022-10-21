
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

#ifndef __NODETAB_H__
#define __NODETAB_H__

#include <parsenode.h>


struct nodetab {

    int len;        //buffer hossz
    int top;        //az első szabad hely indexe
    void **buffer;
        
    nodetab()
    {
        len=256;
        top=0;
        buffer=(void**)malloc(len*sizeof(void*));
    };

    ~nodetab()
    {
        free(buffer);
    };


    int add(void *p)  // return: elemek száma
    {
        //printf("nodetab-add %d %s\n",top,((top>=len)?"realloc":""));

        if( top>=len )
        {
            len+=256;
            buffer=(void**)realloc(buffer,len*sizeof(void*));
        }
        buffer[top++]=p;
        return top;
    };

    void* get(int x)
    {
        return  x<top?buffer[x]:0;
    };

    void clean()
    {
        top=0;
    };


    void list(const char *prompt="")
    {
        int i=0;
        parsenode *p;
        while( 0!=(p=(parsenode*)(this->get(i++))) )
        {
            p->print(prompt);
        }
    }

    int search(parsenode *node)
    {
        int i=0;
        parsenode *p;
        while( 0!=(p=(parsenode*)(this->get(i))) )
        {
            if(0==strcmp(node->text,p->text))
            {
                return i;
            }
            i++;
        }
        return -1;
    }

    int add1(parsenode *p) //return: elem indexe
    {
        int x=search(p);
        if( x<0 )
        {
            x=add(p)-1;
        }
        return x;
    };

};


extern nodetab *nodetab_globstat;
extern nodetab *nodetab_locstat;
extern nodetab *nodetab_local;
extern nodetab *nodetab_blkarg;
extern nodetab *nodetab_blkenv;
extern nodetab *nodetab_block;

#endif

