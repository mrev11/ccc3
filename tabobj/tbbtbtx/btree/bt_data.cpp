
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
RECPOS __bt_addresource(BTREE *t, DBT*data, indx_t index)
{
    // A data-ban megadott resource-ot kiirja az 1-es page-re,
    // ha az 1-es page meg nem letezik, csinal egy uj page-et,
    // ha ez nem 1-es, akkor perror,
    // a megadott indexbe (0-tol indul) irja data-t,
    // index nem lehet nagyobb NEXTINDEX-nel (vagy perror),
    // ha index<NEXTINDEX, akkor a nagyobb indexu rekordokat torli,
    // igy mindig index lesz a legutolso rekord indexe.
    // Visszaadja azt a recpos-t, amivel a beirt adat kiolvashato.

    PAGE *h;
    u_int32_t nbytes;
    char *dest;
    RECPOS recpos={0,0};

    mpool_count(t->bt_mp,"addresource-0");//ellenorzes

    h=(PAGE*)mpool_get(t->bt_mp,1);
    nbytes=NBLEAFDBT(data->size);

    if( h==0 )
    {
        pgno_t pgno;
        h=__bt_new(t,&pgno);

        if( pgno!=1 )
        {
            __bt_error("__bt_addresource: no resource page");
        }
        h->pgno   = pgno;
        h->linkpg = P_INVALID;
        h->prevpg = P_INVALID;
        h->nextpg = P_INVALID;
        h->flags  = P_DATA;
    }

    if( index>NEXTINDEX(h) )
    {
        __bt_error("__bt_addresource: invalid resource index");
    }
    else if( index<NEXTINDEX(h) )
    {
        h->lower = BTDATAOFF+index*sizeof(indx_t);
        h->upper = index==0 ? t->bt_psize : h->linp[index-1] ;
    }

    if( (u_int32_t)(h->upper-h->lower) < (nbytes+sizeof(indx_t)) )
    {
        __bt_error("__bt_addresource: no space");
    }

    h->lower+=sizeof(indx_t);
    h->linp[index]=h->upper-=nbytes;
    dest=(char*)h+h->upper;
    WR_BLEAF(dest,data);
    mpool_put(t->bt_mp,h,MPOOL_DIRTY);

    recpos.pgno=1;
    recpos.index=index;

    mpool_count(t->bt_mp,"addresource-1");//ellenorzes
    return recpos;
}

//----------------------------------------------------------------------------
RECPOS __bt_append(BTREE *t, DBT*data, int *recno)
{
    PAGE *h=0;
    indx_t index;
    u_int32_t nbytes;
    char *dest;
    RECPOS recpos={0,0};

    mpool_count(t->bt_mp,"append-0");//ellenorzes
    __bt_header_read(t,1);

    if( t->bt_lastdatapage )
    {
        __bt_pagelock(t,t->bt_lastdatapage,1);
        h=(PAGE*)mpool_get(t->bt_mp,t->bt_lastdatapage);
    }

    nbytes=NBLEAFDBT(data->size);

    if( (h==0) || ((u_int32_t)(h->upper-h->lower)<(nbytes+sizeof(indx_t))) )
    {
        pgno_t npg;

        if( h )
        {
            mpool_put(t->bt_mp,h,0);
        }

        #define PREFER_FREELIST
        #ifdef  PREFER_FREELIST
          h=__bt_new(t,&npg);
        #else
          h=__bt_new0(t,&npg); //pack replikalhatosaga erdekeben, 2004.04.18
        #endif

        __bt_pageunlock(t,t->bt_lastdatapage);
        t->bt_lastdatapage=npg;
        __bt_pagelock(t,t->bt_lastdatapage,1);

        h->pgno   = npg;
        h->linkpg = P_INVALID;
        h->prevpg = P_INVALID;
        h->nextpg = P_INVALID;
        h->lower  = BTDATAOFF;
        h->upper  = t->bt_psize;
        h->flags  = P_DATA;
    }
    t->bt_nrecs++;

    index=NEXTINDEX(h);
    h->lower+=sizeof(indx_t);
    h->linp[index]=h->upper-=nbytes;
    dest=(char*)h+h->upper;
    WR_BLEAF(dest,data);
    mpool_put(t->bt_mp,h,MPOOL_DIRTY);

    *recno=t->bt_nrecs;
    recpos.pgno=t->bt_lastdatapage;
    recpos.index=index;

    __bt_pageunlock(t,t->bt_lastdatapage);
    __bt_header_write(t);
    mpool_count(t->bt_mp,"append-1");//ellenorzes

    return recpos;
}

//----------------------------------------------------------------------------
int __bt_read(BTREE *t, DBT*data, RECPOS *recpos)
{
    PAGE *h;
    int recsiz=0;

    mpool_count(t->bt_mp,"read-0");//ellenorzes
    __bt_pagelock(t,recpos->pgno,0);

    if( (0!=(h=(PAGE*)mpool_get(t->bt_mp,recpos->pgno))) &&
        (h->flags==P_DATA) &&
        (recpos->index<NEXTINDEX(h)) )
    {
        BLEAF *bl=GETBLEAF(h,recpos->index);
        data->size=(bl->ksize<data->size)?bl->ksize:data->size;  //min
        memmove(data->data,bl->bytes,data->size);
        recsiz=bl->ksize ;
    }

    if( h )
    {
        mpool_put(t->bt_mp,h,0);
    }
    __bt_pageunlock(t,recpos->pgno);
    mpool_count(t->bt_mp,"read-1");//ellenorzes
    return recsiz;
}

//----------------------------------------------------------------------------
int __bt_read1(BTREE *t, DBT*data, pgno_t pgno, indx_t index)
{
    PAGE *h;
    int recsiz=0;

    mpool_count(t->bt_mp,"read1-0");//ellenorzes
    __bt_pagelock(t,pgno,0);

    if( (0!=(h=(PAGE*)mpool_get(t->bt_mp,pgno))) &&
        (h->flags==P_DATA) &&
        (index<NEXTINDEX(h)) )
    {
        BLEAF *bl=GETBLEAF(h,index);
        data->size=(bl->ksize<data->size)?bl->ksize:data->size;  //min
        memmove(data->data,bl->bytes,data->size);
        recsiz=bl->ksize ;
    }

    if( h )
    {
        mpool_put(t->bt_mp,h,0);
    }
    __bt_pageunlock(t,pgno);
    mpool_count(t->bt_mp,"read1-1");//ellenorzes
    return recsiz;
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
int __bt_rewrite(BTREE *t, DBT*data, RECPOS *recpos)
{
    PAGE *h;
    int success=0;

    mpool_count(t->bt_mp,"rewrite-0");//ellenorzes
    __bt_pagelock(t,recpos->pgno,1);

    if( (0!=(h=(PAGE*)mpool_get(t->bt_mp,recpos->pgno))) &&
        (h->flags==P_DATA) &&
        (recpos->index<NEXTINDEX(h)) )
    {
        BLEAF *bl=GETBLEAF(h,recpos->index);
        if( bl->ksize==data->size )
        {
            memmove(bl->bytes,data->data,data->size);
            success=MPOOL_DIRTY;
        }
    }
    if( h )
    {
        mpool_put(t->bt_mp,h,success);
    }

    __bt_pageunlock(t,recpos->pgno);
    mpool_count(t->bt_mp,"rewrite-1"); //ellenorzes

    return success?RET_SUCCESS:RET_ERROR;
}

//----------------------------------------------------------------------------


