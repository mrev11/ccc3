
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


//---------------------------------------------------------------------------
typedef struct elem
{
   struct elem *left;
   struct elem *right;
   char * text;
}  ELEM;

static ELEM *root;

//---------------------------------------------------------------------------
void metdecl_ini()
{
    root=0;
}

//---------------------------------------------------------------------------
static ELEM* insert(char *text)
{
    ELEM *e=(ELEM*)malloc(sizeof(ELEM));

    e->left=0;
    e->right=0;
    e->text=text; //nem kell duplikálni
    return e;
}
 
//---------------------------------------------------------------------------
void metdecl_insert(const char *slotname, const char *prntname, const char *basename)
{
    int ls=strlen(slotname);
    int lb=basename?strlen(basename):0;
    int lp=prntname?strlen(prntname):0;
    char *text=(char*)malloc(ls+lb+lp+3);

    strcpy(text,slotname);
    if( basename )
    {
        strcat(text,"!");
        strcat(text,basename);
    }
    if( prntname )
    {
        strcat(text,"?");
        strcat(text,prntname);
    }
    
    if( root==0 )
    {
        root=insert(text);
        return;
    }

    ELEM *elem=root;
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

//---------------------------------------------------------------------------
static void walk(ELEM *elem)
{
    if( elem->left )
    {
        walk(elem->left);
    }
    
    char *sname=elem->text;
    char *bname_d=strstr(sname,"!");
    char *pname_d=strstr(sname,"?");
    char *bname=0;
    char *pname=0;
    
    if( bname_d )
    {
        *bname_d=0x00; //! helyére 0
        bname_d++;
    }

    if( pname_d )
    {
        *pname_d=0x00; //? helyére 0
        pname_d++;
    }

    if( bname_d )
    {
        bname=strdup(bname_d);
        char *p=bname; while(*p){if(*p=='.')*p='_';p++;}
    }

    if( pname_d )
    {
        pname=strdup(pname_d);
        char *p=pname; while(*p){if(*p=='.')*p='_';p++;}
    }

    if( bname==0  ) // object:method
    {
        printf("\nclass _method_%s: public _method2_",sname);
        printf("{public: _method_%s():_method2_(\"%s\"){};};",sname,sname);
        printf(" static _method_%s _o_method_%s;",sname,sname);
    }
    else if( pname==0  ) // object:(class)method 
    {
        printf("\nclass _method_%s_C_%s: public _methodc2_",sname,bname);
        printf("{public: _method_%s_C_%s():_methodc2_(\"%s\",\"%s\"){};};",sname,bname,sname,bname_d);
        printf(" static _method_%s_C_%s _o_method_%s_C_%s;",sname,bname,sname,bname);
    }
    else if( 0==strcmp(pname,"super") ) // object:(super:class)method  
    {
        printf("\nclass _method_%s_S_%s: public _methods2_",sname,bname);
        printf("{public: _method_%s_S_%s():_methods2_(\"%s\",\"%s\"){};};",sname,bname,sname,bname_d);
        printf(" static _method_%s_S_%s _o_method_%s_S_%s;",sname,bname,sname,bname);
    }
    else  // object:(parent:class)method   
    {
        printf("\nclass _method_%s_P_%s_C_%s: public _methodp2_",sname,pname,bname);
        printf("{public: _method_%s_P_%s_C_%s():_methodp2_(\"%s\",\"%s\",\"%s\"){};};",sname,pname,bname,sname,pname_d,bname_d);
        printf(" static _method_%s_P_%s_C_%s _o_method_%s_P_%s_C_%s;",sname,pname,bname,sname,pname,bname);
    }
    
    if(bname)free(bname);
    if(pname)free(pname);
 
    if( elem->right )
    {
        walk(elem->right);
    }
}

//---------------------------------------------------------------------------
void metdecl_list()
{
   if( root )
   {
       walk(root);
       printf("\n");
   }
}

//---------------------------------------------------------------------------

