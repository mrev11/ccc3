
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

#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <btree.h>


//----------------------------------------------------------------------------
void __bt_pgeval(BTREE *t, pgno_t pgno, VALUE *block)
{
    mpool_count(t->bt_mp,"pgeval-0");//ellenorzes
    __bt_pagelock(t,pgno,0);

    PAGE *h=(PAGE*)mpool_get(t->bt_mp,pgno);
    push(block);
    binarys((char*)h,t->bt_psize);
    _clp_eval(2);
    
    // ha a visszateres egy page
    // akkor azt ki kell irni
    // ha barmi mas (peldaul NIL)
    // akkor nem kell kiirni
    
    if( TOP()->type==TYPE_BINARY &&  BINARYLEN(TOP())==t->bt_psize )
    {
        memmove(h,BINARYPTR(TOP()),t->bt_psize);
        mpool_put(t->bt_mp,h,1);
    }
    else
    {
        mpool_put(t->bt_mp,h,0);
    }
    pop();

    __bt_pageunlock(t,pgno);
    mpool_count(t->bt_mp,"pgeval-1");//ellenorzes
}


//----------------------------------------------------------------------------
int __bt_pgread(BTREE *t, pgno_t pgno, DBT*data)
{
    // statisztikakhoz

    PAGE *h=0;
    int length=0;

    mpool_count(t->bt_mp,"pgread-0");//ellenorzes
    __bt_pagelock(t,pgno,0);

    if( pgno==0 )
    {
        // specialis eset
        // h==t (a btree maga)

        length=(data->size<sizeof(BTREE))?data->size:sizeof(BTREE); // min
        memset(data->data,0,data->size);
        memmove(data->data,t,length);
        length=data->size;
    }
    else
    {
        h=(PAGE*)mpool_get(t->bt_mp,pgno);
        data->size=(data->size<t->bt_psize)?data->size:t->bt_psize; // min
        memmove(data->data,h,data->size);
        length=data->size;
        mpool_put(t->bt_mp,h,0);
    }
    __bt_pageunlock(t,pgno);
    mpool_count(t->bt_mp,"pgread-1");//ellenorzes
    return length;
}


//----------------------------------------------------------------------------
void __bt_pgrewrite(BTREE *t, pgno_t pgno, int cryptflg)
{
    // ki/be titkositashoz

    PAGE *h=0;

    mpool_count(t->bt_mp,"pgrewrite-0");//ellenorzes
    __bt_pagelock(t,pgno,0);

    if( pgno==0 )
    {
        // header kihagy
    }
    else
    {
        h=(PAGE*)mpool_get(t->bt_mp,pgno);
        int cf=t->bt_mp->cryptflg;
        //printf("__bt_rewrite [%d] %d -> %d\n", pgno, cf, cryptflg!=0 );

        if( (cf==0) == (cryptflg==0) )
        {
            // nem kell irni
            mpool_put(t->bt_mp,h,0);
        }
        else if( cryptflg==0 )
        {
            // titkositas nelkul
            t->bt_mp->cryptflg=0;
            mpool_put(t->bt_mp,h,1);
        }
        else if( cryptflg!=0 )
        {
            // titkositassal
            t->bt_mp->cryptflg=1;
            mpool_put(t->bt_mp,h,1);
        }

        t->bt_mp->cryptflg=cf;
    }

    __bt_pageunlock(t,pgno);
    mpool_count(t->bt_mp,"pgrewrite-1");//ellenorzes
}


//----------------------------------------------------------------------------
