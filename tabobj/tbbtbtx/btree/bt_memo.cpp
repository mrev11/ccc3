
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
#include <sys/param.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <btree.h>

// memo szabadlista:
// egy lap a szabadlistaban van, ha page->linkpg!=0
// a szabadlista elso elemere mutat header->bt_memo
// a szabadlista nemutolso elemein page->linkpg a kovetkezo elemre mutat
// a szabadlista utolso elemen page->linkpg==page->pgno (onmagara mutat)

//----------------------------------------------------------------------------
static size_t metasize()
{
    return   sizeof(indx_t)    // index        2  memorekord offsete lapon belul
           + sizeof(u_int32_t) // length       4  memorekord hossza (pgno+indx+memoertek)
           + sizeof(pgno_t)    // RECPOS.pgno  4  kovetkezo memorekord lapja vagy 0
           + sizeof(indx_t);   // RECPOS.index 2  kovetkezo memorekord indexe vagy 0
}

//----------------------------------------------------------------------------
static size_t minspace()
{
    // ha egy lapon ennel kisebb hely marad
    // akkor azt nem teszi be a szabadlistaba

    return 4*metasize();
}

//----------------------------------------------------------------------------
static PAGE* __bt_memopage(BTREE *t)
{
    PAGE *memopg=0;
    pgno_t pgno=t->bt_memo; // szabadlista eleje

    if( pgno )
    {
        // page a szabadlistabol
        __bt_pagelock(t,pgno,1); // wrlk
        memopg=(PAGE*)mpool_get(t->bt_mp,pgno);
        //printf(">>> memopage %x %x %p\n", pgno, memopg->pgno, memopg);
        //printf(">>> lower %x\n",(int)memopg->lower);
        //printf(">>> upper %x\n",(int)memopg->upper);
        //printf(">>> space %d\n",(int)memopg->upper-(int)memopg->lower);
        //mpool_dump(t->bt_mp,memopg);
    }
    else
    {
        // vadonat uj page
        memopg=__bt_new0(t,&pgno,0);
        __bt_pagelock(t,pgno,1); // wrlk
        memopg->pgno   = pgno;
        memopg->linkpg = 0;
        memopg->prevpg = 0;
        memopg->nextpg = 0;
        memopg->lower  = BTDATAOFF;
        memopg->upper  = t->bt_psize;
        memopg->flags  = P_MEMO;
    }
    return memopg;
}

//----------------------------------------------------------------------------
static RECPOS  __bt_memowrite(BTREE *t, DBT *data)
{
    RECPOS recpos={0,0};
    if( data->size==0 )
    {
        return recpos;
    }

    mpool_count(t->bt_mp,"memowrite-0");//ellenorzes
    __bt_header_read(t,1);

    pgno_t pgno;
    PAGE *memopg=0;
    PAGE *prevpage=0;
    indx_t previndex=0;

    size_t written=0;
    while( written<data->size )
    {
        memopg=__bt_memopage(t); // behozza, lockolja

        size_t space=(memopg->upper)-(memopg->lower);   // szabad hely
        space-=metasize();                              // max ennyi adat fer el
        indx_t indx;
        for( indx=0; indx<NEXTINDEX(memopg); indx++)
        {
            if( memopg->linp[indx]==0 )
            {
                // korabbi torlessel
                // keletkezett lyuk
                space+=sizeof(indx_t);
                break;
            }
        }
        size_t towrite=MIN(data->size-written,space);   // ennyit irunk most ki

        if( recpos.pgno==0 )
        {
            // ez lesz a visszateres
            recpos.pgno=memopg->pgno;
            recpos.index=indx;
        }

        //printf("indx  %x\n",(int)indx);
        //printf("lower %x\n",(int)memopg->lower);
        //printf("upper %x\n",(int)memopg->upper);
        //printf("meta %d\n",(int)metasize());
        //printf("space %d\n",(int)space);
        //printf("towrite %d\n",(int)towrite);

        memopg->upper-=towrite;
            memmove( (char*)memopg+memopg->upper, (char*)data->data+written, towrite);

        memopg->upper-=sizeof(indx_t);
            indx_t recpos_index=0;
            memmove( (char*)memopg+memopg->upper, (char*)&recpos_index, sizeof(indx_t));

        memopg->upper-=sizeof(pgno_t);
            pgno_t recpos_pgno=0;
            memmove( (char*)memopg+memopg->upper, (char*)&recpos_pgno, sizeof(pgno_t) );

        memopg->upper-=sizeof(u_int32_t);
            u_int32_t length=sizeof(pgno_t)+sizeof(indx_t)+towrite;
            memmove( (char*)memopg+memopg->upper, (char*)&length, sizeof(u_int32_t) );

        memopg->linp[indx]=memopg->upper;
        if( indx==NEXTINDEX(memopg)  )
        {
            // ha nem volt korabbi
            // torlesbol maradt lyuk
            memopg->lower+=sizeof(indx_t);
        }

        written+=towrite;

        if( prevpage )
        {
            char *recpos=(char*)prevpage+prevpage->linp[previndex];
            recpos+=sizeof(u_int32_t); // length
                memmove(recpos,&memopg->pgno,sizeof(pgno_t));
            recpos+=sizeof(pgno_t); // RECPOS.pgno
                memmove(recpos,&indx,sizeof(indx_t));

            pgno=prevpage->pgno; // mpool_put atirja CRC-re
            mpool_put(t->bt_mp,prevpage,MPOOL_DIRTY);
            __bt_pageunlock(t,pgno);

            // megjegyezes
            //   8 = sizeof(RECPOS)
            //   6 = sizeof(RECPOS.pgno) + sizeof(RECPOS.index)
            // tehat a RECPOS merete elter a tagjai meretenek osszegetol
            // nem celszeru a diszk adatokat RECPOS strukturakent kezelni
            // mert a RECPOS struktura merete fugghet a forditotol
            // ezzel szemben  RECPOS.pgno-nak es RECPOS.index-nek
            // kulon kulon fix merete van
        }


        // szabadlista modositas
        
        if( (memopg->upper)-(memopg->lower) < (indx_t)minspace() )
        {
            // NEM MARADT HELY A LAPON
            if( memopg->linkpg!=0 )
            {
                // szabadlistabol vett lap
                // ki kell vanni a szabadlistabol
                // KIVESZ

                if( memopg->linkpg==memopg->pgno )
                {
                    // utolso elem
                    t->bt_memo=0;
                    memopg->linkpg=0;
                }
                else
                {
                    // folytatodik a lista
                    t->bt_memo=memopg->linkpg;
                    memopg->linkpg=0;
                }
            }
            else
            {
                // nem szabadlistabol vett lap
                // nem modosul a szabadlista
            }
        }
        else
        {
            // MARADT HELY A LAPON
            if( memopg->linkpg!=0 )
            {
                // szabadlistabol vett lap
                // nem modosul a szabadlista
            }
            else
            {
                // nem szabadlistabol vett lap
                // be kell tenni a szabadlista elejere
                // BERAK

                t->bt_memo=memopg->pgno;
                memopg->linkpg=memopg->pgno; // utolso elem
            }
        }

        prevpage=memopg;
        previndex=indx;
    }

    pgno=memopg->pgno; // mpool_put atirja CRC-re
    mpool_put(t->bt_mp,memopg,MPOOL_DIRTY);
    __bt_pageunlock(t,pgno);

    __bt_header_write(t);
    mpool_count(t->bt_mp,"memowrite-1");//ellenorzes
    return recpos;
}


//----------------------------------------------------------------------------
static DBT __bt_memoread(BTREE *t, RECPOS recpos)
{
    mpool_count(t->bt_mp,"memoread-0");//ellenorzes

    pgno_t pgno=recpos.pgno;
    indx_t indx=recpos.index;
    PAGE *memopg;

    char * data=0;
    size_t size=0;
    size_t cpct=0;

    __bt_pagelock(t,pgno,0); // rdlk

    while(1)
    {
        memopg=(PAGE*)mpool_get(t->bt_mp,pgno);
        if( memopg==0 )
        {
            char error[128];
            sprintf(error,"__bt_memoread: cannot read page (%x)\n",pgno);
            __bt_error(error);
        }
        else if( memopg->flags!=P_MEMO )
        {
            char error[128];
            sprintf(error,"__bt_memoread: invalid page type (%x,%d)\n",pgno,memopg->flags);
            __bt_error(error);
        }
        else if( indx>=NEXTINDEX(memopg) )
        {
            char error[128];
            sprintf(error,"__bt_memoread: memo index out of bound (%x,%d)\n",pgno,indx);
            __bt_error(error);
        }
        else if( memopg->linp[indx]==0 )
        {
            char error[128];
            sprintf(error,"__bt_memodel: deleted memo (%x,%d)\n",pgno,indx);
            __bt_error(error);
        }


        BLEAF *rec=GETBLEAF(memopg,indx);  // {u_in32_t ksize, char bytes[]}
        pgno_t next_pgno=0; memmove(&next_pgno,rec->bytes,sizeof(pgno_t));
        indx_t next_indx=0; memmove(&next_indx,rec->bytes+sizeof(pgno_t),sizeof(indx_t));
        size_t segsize=rec->ksize-(sizeof(pgno_t)+sizeof(indx_t));
        char * segdata=rec->bytes+(sizeof(pgno_t)+sizeof(indx_t));

        if( data==0 )
        {
            data=(char*)malloc(segsize);
            memmove(data,segdata,segsize);
            size+=segsize;
            cpct+=segsize;
        }
        else if( cpct<size+segsize )
        {
            data=(char*)realloc(data,cpct+t->bt_psize);
            memmove(data+size,segdata,segsize);
            size+=segsize;
            cpct+=t->bt_psize;
        }
        else
        {
            memmove(data+size,segdata,segsize);
            size+=segsize;
        }
        mpool_put(t->bt_mp,memopg,0);

        if( next_pgno==0 )
        {
            break;
        }

        __bt_pagelock(t,next_pgno,0); // rdlk
        __bt_pageunlock(t,pgno);

        pgno=next_pgno;
        indx=next_indx;
    }

    __bt_pageunlock(t,pgno);
    mpool_count(t->bt_mp,"memoread-1");//ellenorzes

    DBT dbt;
    dbt.size=size;
    dbt.data=data;

    return dbt;
}

//----------------------------------------------------------------------------
static void __bt_memodel(BTREE *t, RECPOS recpos)
{
    //printf("MEMODEL(%x,%x)\n", recpos.pgno,recpos.index);

    mpool_count(t->bt_mp,"memodel-0");//ellenorzes
    __bt_header_read(t,1);

    pgno_t pgno=recpos.pgno;
    indx_t indx=recpos.index;
    PAGE *memopg;

    __bt_pagelock(t,pgno,1); // wrlk

    while(1)
    {
        memopg=(PAGE*)mpool_get(t->bt_mp,pgno);
        if( memopg==0 )
        {
            char error[128];
            sprintf(error,"__bt_memodel: cannot read page (%x)\n",pgno);
            __bt_error(error);
        }
        else if( memopg->flags!=P_MEMO )
        {
            char error[128];
            sprintf(error,"__bt_memodel: invalid page type (%x,%d)\n",pgno,memopg->flags);
            __bt_error(error);
        }
        else if( indx>=NEXTINDEX(memopg) )
        {
            char error[128];
            sprintf(error,"__bt_memodel: memo index out of bound (%x,%d)\n",pgno,indx);
            __bt_error(error);
        }
        else if( memopg->linp[indx]==0 )
        {
            char error[128];
            sprintf(error,"__bt_memodel: deleted memo (%x,%d)\n",pgno,indx);
            __bt_error(error);
        }


        BLEAF *rec=GETBLEAF(memopg,indx);  // {u_in32_t ksize, char bytes[]}
        pgno_t next_pgno=0; memmove(&next_pgno,rec->bytes,sizeof(pgno_t));
        indx_t next_indx=0; memmove(&next_indx,rec->bytes+sizeof(pgno_t),sizeof(indx_t));

        size_t size=sizeof(rec->ksize)+rec->ksize; // felszabadulo hely merete
        memmove( (char*)memopg+memopg->upper+size,(char*)memopg+memopg->upper,memopg->linp[indx]-memopg->upper );
        memset(  (char*)memopg+memopg->upper,0,size );
        memopg->upper+=size;

        memopg->linp[indx]=0;
        for(indx_t i=indx+1; i<NEXTINDEX(memopg); i++)
        {
            if( memopg->linp[i] )
            {
                memopg->linp[i]+=size;
            }
            else
            {
                // a lyukak helyen 0 van
                // amit nem szabad novelni
            }
        }


        if( (memopg->upper)-(memopg->lower)<(indx_t)minspace() )
        {
            // nem keletkezett eleg szabad hely
            // => korabban sem lehetett a szabadlistaban
            // => a szabadlista nem valtozik
        }
        else if( memopg->linkpg!=0 )
        {
            // korabban is a szabadlistaban volt
            // => a szabadlista nem valtozik
        }
        else
        {
            // korabban nem volt a szabadlistaban
            // a szabad lista elejere be kell fuzni

            pgno_t link=t->bt_memo;             // szabadlista eleje vagy 0
            t->bt_memo=memopg->pgno;            // uj elso elem
            if( link==0)
            {
                memopg->linkpg=memopg->pgno;    // onmagara mutat, ha utolso
            }
            else
            {
                memopg->linkpg=link;            // a korabbi elsore mutat
            }
        }

        mpool_put(t->bt_mp,memopg,MPOOL_DIRTY);

        if( next_pgno==0 )
        {
            break;
        }

        __bt_pagelock(t,next_pgno,1); // wrlk
        __bt_pageunlock(t,pgno);

        pgno=next_pgno;
        indx=next_indx;
    }
    __bt_pageunlock(t,pgno);

    __bt_header_write(t);
    mpool_count(t->bt_mp,"memodel-1");//ellenorzes
}


//----------------------------------------------------------------------------
#include <cccapi.h>
//----------------------------------------------------------------------------
void _clp__db_memowrite(int argno)
{
    CCC_PROLOG("_db_memowrite",2);
    BTREE *db=(BTREE*)_parp(1);
    str2bin(base+1);
    DBT dbt;
    dbt.data=_parb(2);
    dbt.size=_parblen(2);
    RECPOS rp=__bt_memowrite(db,&dbt);
    char recpos[32];
    sprintf(recpos,"%07x%03x",rp.pgno,rp.index);
    _retb(recpos);
    CCC_EPILOG();
}


//----------------------------------------------------------------------------
void _clp__db_memoread(int argno)
{
    CCC_PROLOG("_db_memoread",2);
    BTREE *db=(BTREE*)_parp(1);
    str2bin(base+1);
    char *pos=_parb(2);
    int pgno,index;
    if( _parblen(2)!=10 || 2!=sscanf(pos,"%07x%03x",&pgno,&index) )
    {
        error_arg("_db_memoread",base,argno);
    }
    RECPOS recpos;
    recpos.pgno=pgno;
    recpos.index=index;
    DBT dbt=__bt_memoread(db,recpos);
    _retblen((char*)dbt.data,dbt.size);
    free(dbt.data);
    CCC_EPILOG();
}


//----------------------------------------------------------------------------
void _clp__db_memodel(int argno)
{
    CCC_PROLOG("_db_memodel",2);
    BTREE *db=(BTREE*)_parp(1);
    str2bin(base+1);
    char *pos=_parb(2);
    int pgno,index;
    if( _parblen(2)!=10 || 2!=sscanf(pos,"%07x%03x",&pgno,&index) )
    {
        error_arg("_db_memodel",base,argno);
    }
    RECPOS recpos;
    recpos.pgno=pgno;
    recpos.index=index;
    __bt_memodel(db,recpos);
    _ret();
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
