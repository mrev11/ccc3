
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

//#include <sys/stat.h>
//#include <errno.h>
//#include <fcntl.h>
//#include <stdio.h>
//#include <unistd.h>

#include <string.h>
#include <stdlib.h>
#include <btree.h>
 
//---------------------------------------------------------------------------
static int nroot(BTREE *t, char *name) //create new root page 
{
    PAGE *root;
    pgno_t npg;
    
    __bt_header_read(t,1);
 
    if( (root=__bt_new(t,&npg))==NULL )
    {
        return RET_ERROR;
    }

    root->pgno    = npg;
    root->linkpg  = P_INVALID;
    root->prevpg  = P_INVALID; //leaf sibling
    root->nextpg  = P_INVALID; //leaf sibling 
    root->lower   = BTDATAOFF;
    root->upper   = t->bt_psize;
    root->flags   = P_BLEAF;
    mpool_put(t->bt_mp, root, MPOOL_DIRTY);

    t->bt_curord = t->bt_nords; 
    P_ROOT(t) = npg;
    P_LASTPAGE(t) = npg;
    P_LASTFREE(t) = 0;
    strcpy(P_NAME(t),name);
    t->bt_nords++;  

    __bt_header_write(t);

    return RET_SUCCESS;
}


//---------------------------------------------------------------------------
static int __bt_srcord(BTREE *t, char *name)
{
    unsigned int n;
    mpool_count(t->bt_mp, "srcord");
    __bt_header_read(t,0);

    for( n=0; n<t->bt_nords; n++ )
    {
        if( 0==strcmp(t->bt_order[n].name,name) )
        {
            return n;
        }
    }
    return -1;
}

//---------------------------------------------------------------------------
int __bt_setord(BTREE *t, char*name)
{
    int n=__bt_srcord(t,name);
    
    if( n>=0 )
    {
        t->bt_curord=n;
    }
    return n;
}

//---------------------------------------------------------------------------
int __bt_creord(BTREE *t, char*name)
{
    int n=__bt_srcord(t,name);

    if( n<0 )
    {
        nroot(t,name);
    }
    mpool_count(t->bt_mp, "creord");
    return __bt_setord(t, name);
}

//---------------------------------------------------------------------------
int __bt_delord(BTREE *t, char*name)
{
    int n=__bt_srcord(t,name);
   
    if( n>0 ) // Recno order (n==0) must not delete.
    {
        PAGE *root;
        __bt_header_read(t,1);
        root=(PAGE*)mpool_get(t->bt_mp, t->bt_order[n].root);
        root->linkpg=t->bt_free;
        mpool_put(t->bt_mp, root, MPOOL_DIRTY);
        t->bt_free=t->bt_order[n].lastpage;
        t->bt_nords--;
        memmove(&t->bt_order[n],&t->bt_order[n+1],(t->bt_nords-n)*sizeof(ORDER));
        memset(&t->bt_order[t->bt_nords],0,sizeof(ORDER));
        __bt_header_write(t);
        
        if( t->bt_curord==n )
        {
            t->bt_curord=0;
        }
    }
    return n;
}
 
//---------------------------------------------------------------------------
int __bt_renord(BTREE *t, char*nameold, char*namenew)
{
    int n=__bt_srcord(t,nameold);

    if( n>=0 )
    {
        __bt_header_read(t,1);
        strncpy(t->bt_order[n].name,namenew,sizeof(t->bt_order[n].name));
        __bt_header_write(t);
    }
    mpool_count(t->bt_mp, "renord");
    return  n;
}

//---------------------------------------------------------------------------

