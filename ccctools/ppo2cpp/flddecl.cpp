
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


//--------------------------------------------------------------------------
typedef struct elem
{
   struct elem *left;
   struct elem *right;
   char * text;
}  ELEM;

static ELEM *root;


//--------------------------------------------------------------------------
void flddecl_ini()
{
    root=0;
}

//--------------------------------------------------------------------------
static ELEM* insert(char *t)
{
    ELEM *e=(ELEM*)malloc(sizeof(ELEM));

    e->left=0;
    e->right=0;
    e->text=strdup(t);
    return e;
}
 
//--------------------------------------------------------------------------
void flddecl_insert(char *text)
{
    if( root==0 )
    {
        root=insert(text);
        return;
    }

    ELEM*elem=root;
    int cmp;

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
                elem->left=insert(text); 
                return;
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
                elem->right=insert(text); 
                return;
            }
        }
    }
}


//--------------------------------------------------------------------------
static void walk(ELEM *elem)
{
    if( elem->left )
    {
        walk(elem->left);
    }
    
    char *alias=elem->text;
    char *field=strstr(alias,"->");

    if( !field )
    {
        fprintf(stderr,"\nInvalid field expression");
        exit(1);
    }
    *field=0x00;  // '->' helyére 0
    field+=2;
    
    printf("\nclass dbfield_%s_%s: public dbfield",alias,field);
    printf("{public: dbfield_%s_%s():dbfield(\"%s\",\"%s\"){};};",alias,field,alias,field);
    printf(" static dbfield_%s_%s _ef_%s_%s;",alias,field,alias,field);


    if( elem->right )
    {
        walk(elem->right);
    }
} 

//--------------------------------------------------------------------------
void flddecl_list()
{
   if( root )
   {
       walk(root);
       printf("\n");
   }
}

//--------------------------------------------------------------------------

