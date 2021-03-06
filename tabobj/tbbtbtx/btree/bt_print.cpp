
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
#include <stdlib.h>
#include <btree.h>

//----------------------------------------------------------------------------
void __bt_print_free(BTREE *t)
{
    pgno_t pgno=t->bt_free;
    while( pgno )
    {
        PAGE *h=(PAGE*)mpool_get(t->bt_mp,pgno);
        if( h==NULL )
        {
            __bt_error("__bt_print_free: mpool_get failed");
        }
        else
        {
            printf(">%d,%d,%d,%d\n",h->pgno,h->linkpg,h->prevpg,h->nextpg);
            pgno=h->linkpg;
            mpool_put(t->bt_mp,h,0);
        }
    }
}
 
//---------------------------------------------------------------------------
void __bt_print_header(BTREE *t,char *msg)
{    
    unsigned int n;

    printf("HEADER          %s\n", msg?msg:"");
    printf("  magic         %x\n", BTREEMAGIC);
    printf("  version       %d\n", BTREEVERSION);
    printf("  psize         %d\n", t->bt_psize);
    printf("  nrecs         %d\n", t->bt_nrecs); 
    printf("  free          %d\n", t->bt_free);
    printf("  lastdatapage  %d\n", t->bt_lastdatapage); 
    printf("  reserved      %d\n", t->reserved);
    printf("  nords         %d\n", t->bt_nords);
 
    for( n=0; n<t->bt_nords; n++ ) 
    {
        printf("root/name %d %s\n", t->bt_order[n].root, t->bt_order[n].name);
    }

    fflush(0);
} 

//---------------------------------------------------------------------------
