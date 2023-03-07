
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


#define uint                    u_int32_t
#define MEMOPG                  u_int32_t


#define PGNO(page)              page[0]         // page sorszam (diszken CRC)
#define LINK(page)              page[1]         // kovetkezo szabad memo page
#define LOWER(page)             page[2]         // elso szabad hely offsete
#define UPPER(page)             page[3]         // elso nemszabad hely offsete
#define FLAGS(page)             page[4]         // page tipus

#define MEMO_PGNEXT(page,x)     page[4*x+5]     // kovetkezo memo szegmens lapja
#define MEMO_IDNEXT(page,x)     page[4*x+6]     // kovetkezo memo szegmens indexe
#define MEMO_OFFSET(page,x)     page[4*x+7]     // memo szegmens offsete
#define MEMO_SIZE(page,x)       page[4*x+8]     // memo szegmens merete


#define MINSPACE                16
#define PAGEHEAD                (5*sizeof(uint))
#define MEMOHEAD                (4*sizeof(uint))

#define PLOWER(page)            ((char*)page+LOWER(page))
#define PUPPER(page)            ((char*)page+UPPER(page))
#define ADDRESS(page,x)         ((char*)page+MEMO_OFFSET(page,x))
#define MEMOCOUNT(page)         ((LOWER(page)-PAGEHEAD)/MEMOHEAD)


// memo szabadlista:
// egy lap a szabadlistaban van, ha page->linkpg!=0
// a szabadlista elso elemere mutat header->bt_memo
// a szabadlista nemutolso elemein page->linkpg a kovetkezo elemre mutat
// a szabadlista utolso elemen page->linkpg==page->pgno (onmagara mutat)



//----------------------------------------------------------------------------------------
static MEMOPG* __bt_memopage(BTREE *t)
{
    MEMOPG *memopg=0;
    uint pgno=t->bt_memo; // szabadlista eleje

    if( pgno )
    {
        __bt_pagelock(t,pgno,1); // wrlk
        memopg=(MEMOPG*)mpool_get(t->bt_mp,pgno);
        //printf(">>>>>__bt_memopage-free %x\n",pgno);
    }
    else
    {
        memopg=(MEMOPG*)__bt_new0(t,&pgno,0);
        __bt_pagelock(t,pgno,1); // wrlk
        PGNO(memopg)    = pgno;
        LINK(memopg)    = 0;
        LOWER(memopg)   = PAGEHEAD;
        UPPER(memopg)   = t->bt_psize;
        FLAGS(memopg)   = P_MEMO;
        //printf(">>>>>__bt_memopage-new  %x\n", pgno);
    }
    return memopg;
}

//----------------------------------------------------------------------------------------
static RECPOS  __bt_memowrite(BTREE *t, DBT *data)
{
    RECPOS recpos={0,0};
    if( data->size==0 )
    {
        return recpos;
    }

    mpool_count(t->bt_mp,"memowrite-0");//ellenorzes
    __bt_header_read(t,1);

    uint    pgno,indx;
    MEMOPG *memopg=0;
    MEMOPG *prevpage=0;
    uint    previndx=0;

    size_t written=0;
    while( written<data->size )
    {
        memopg=__bt_memopage(t); // behozza, lockolja

        for( indx=0; indx<MEMOCOUNT(memopg); indx++)
        {
            if( MEMO_OFFSET(memopg,indx)==0 )
            {
                break;
            }
        }
        // indx<MEMOCOUNT, ha korabbi torles miatt volt ures hely
        // indx=MEMOCOUNT, ha nem volt ures hely
  
        if( indx==MEMOCOUNT(memopg)  )
        {
            LOWER(memopg)+=MEMOHEAD; // kell egy plusz memo header
        }

        if( recpos.pgno==0 )
        {
            // ez lesz a visszateres
            recpos.pgno=PGNO(memopg);
            recpos.index=indx;
        }

        if( prevpage )
        {
            MEMO_PGNEXT(prevpage,previndx) = PGNO(memopg);
            MEMO_IDNEXT(prevpage,previndx) = indx;

            uint prevpgno=PGNO(prevpage);  // mpool_put atirja CRC-re
            mpool_put(t->bt_mp,prevpage,MPOOL_DIRTY);
            __bt_pageunlock(t,prevpgno);
        }


        size_t space=UPPER(memopg)-LOWER(memopg);     // szabad hely
        size_t towrite=MIN(data->size-written,space); // ennyit irunk most ki
        UPPER(memopg)-=towrite;
        memmove(PUPPER(memopg), (char*)data->data+written, towrite);

        MEMO_PGNEXT(memopg,indx) = 0;
        MEMO_IDNEXT(memopg,indx) = 0;
        MEMO_OFFSET(memopg,indx) = UPPER(memopg);
        MEMO_SIZE(memopg,indx)   = towrite;

        written+=towrite;

        // szabadlista modositas

        if( UPPER(memopg)-LOWER(memopg) < MINSPACE )
        {
            // NEM MARADT HELY A LAPON
            if( LINK(memopg)!=0 )
            {
                // szabadlistabol vett lap
                // ki kell vanni a szabadlistabol
                // KIVESZ

                if( LINK(memopg)==PGNO(memopg) )
                {
                    // utolso elem
                    t->bt_memo=0;
                }
                else
                {
                    // folytatodik a lista
                    t->bt_memo=LINK(memopg);
                }
                LINK(memopg)=0;
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
            if( LINK(memopg)!=0 )
            {
                // szabadlistabol vett lap
                // nem modosul a szabadlista
            }
            else
            {
                // nem szabadlistabol vett lap
                // be kell rakni a szabadlistaba
                // (elso es egyben utlso elem)
                // BERAK

                t->bt_memo=PGNO(memopg);   // elso elem
                LINK(memopg)=PGNO(memopg); // utolso elem
            }
        }

        prevpage=memopg;
        previndx=indx;
    }

    pgno=PGNO(memopg); // mpool_put atirja CRC-re
    mpool_put(t->bt_mp,memopg,MPOOL_DIRTY);
    __bt_pageunlock(t,pgno);

    __bt_header_write(t);
    mpool_count(t->bt_mp,"memowrite-1");//ellenorzes
    return recpos;
}


//----------------------------------------------------------------------------------------
static DBT __bt_memoread(BTREE *t, RECPOS recpos)
{
    mpool_count(t->bt_mp,"memoread-0");//ellenorzes

    char * data=0;
    size_t size=0;
    size_t cpct=0;

    uint pgno=recpos.pgno;
    uint indx=recpos.index;
    MEMOPG *memopg;

    __bt_pagelock(t,pgno,0); // rdlk

    while(1)
    {
        memopg=(MEMOPG*)mpool_get(t->bt_mp,pgno);
        if( memopg==0 )
        {
            char error[128];
            sprintf(error,"__bt_memoread: cannot read page (%x)\n",pgno);
            __bt_error(error);
        }
        else if( FLAGS(memopg)!=P_MEMO )
        {
            char error[128];
            sprintf(error,"__bt_memoread: invalid page type (%x,%d)\n",pgno,FLAGS(memopg));
            __bt_error(error);
        }
        else if( indx>=MEMOCOUNT(memopg) )
        {
            char error[128];
            sprintf(error,"__bt_memoread: memo index out of bound (%x,%d)\n",pgno,indx);
            __bt_error(error);
        }
        else if( MEMO_OFFSET(memopg,indx)==0 )
        {
            char error[128];
            sprintf(error,"__bt_memodel: deleted memo (%x,%d)\n",pgno,indx);
            __bt_error(error);
        }

        uint next_pgno=MEMO_PGNEXT(memopg,indx);
        uint next_indx=MEMO_IDNEXT(memopg,indx);
        size_t segsize=MEMO_SIZE(memopg,indx);
        char * segdata=ADDRESS(memopg,indx);

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

//----------------------------------------------------------------------------------------
static void __bt_memodel(BTREE *t, RECPOS recpos)
{
    mpool_count(t->bt_mp,"memodel-0");//ellenorzes
    __bt_header_read(t,1);

    uint pgno=recpos.pgno;
    uint indx=recpos.index;
    MEMOPG *memopg;

    __bt_pagelock(t,pgno,1); // wrlk

    while(1)
    {
        memopg=(MEMOPG*)mpool_get(t->bt_mp,pgno);
        if( memopg==0 )
        {
            char error[128];
            sprintf(error,"__bt_memodel: cannot read page (%x)\n",pgno);
            __bt_error(error);
        }
        else if( FLAGS(memopg)!=P_MEMO )
        {
            char error[128];
            sprintf(error,"__bt_memodel: invalid page type (%x,%d)\n",pgno,FLAGS(memopg));
            __bt_error(error);
        }
        else if( indx>=MEMOCOUNT(memopg) )
        {
            char error[128];
            sprintf(error,"__bt_memodel: memo index out of bound (%x,%d)\n",pgno,indx);
            __bt_error(error);
        }
        else if( MEMO_OFFSET(memopg,indx)==0 )
        {
            char error[128];
            sprintf(error,"__bt_memodel: deleted memo (%x,%d)\n",pgno,indx);
            __bt_error(error);
        }

        uint size=MEMO_SIZE(memopg,indx); // felszabadulo hely merete
        memmove(PUPPER(memopg)+size,PUPPER(memopg),MEMO_OFFSET(memopg,indx)-UPPER(memopg));
        memset(PUPPER(memopg),0,size);
        UPPER(memopg)+=size;

        for(uint i=0; i<MEMOCOUNT(memopg); i++)
        {
            if( MEMO_OFFSET(memopg,i)==0 )
            {
                // a lyukak helyen 0 van
                // amit nem szabad novelni
            }
            else if( MEMO_OFFSET(memopg,i)<MEMO_OFFSET(memopg,indx)  )
            {
                // ezek hatrebb csusztak
                MEMO_OFFSET(memopg,i)+=size;
            }
        }


        if( UPPER(memopg)-LOWER(memopg) < MINSPACE )
        {
            // nem keletkezett eleg szabad hely
            // => korabban sem lehetett a szabadlistaban
            // => a szabadlista nem valtozik
        }
        else if( LINK(memopg)!=0 )
        {
            // korabban is a szabadlistaban volt
            // => a szabadlista nem valtozik
        }
        else
        {
            // korabban nem volt a szabadlistaban
            // a szabad lista elejere kell befuzni

            uint link=t->bt_memo;               // szabadlista eleje vagy 0
            t->bt_memo=PGNO(memopg);            // uj elso elem
            if( link!=0)
            {
                LINK(memopg)=link;              // a korabbi elsore mutat
            }
            else
            {
                LINK(memopg)=PGNO(memopg);      // utolso elem onmagara mutat
            }
        }


        uint next_pgno=MEMO_PGNEXT(memopg,indx);
        uint next_indx=MEMO_IDNEXT(memopg,indx);

        MEMO_PGNEXT(memopg,indx)=0;
        MEMO_IDNEXT(memopg,indx)=0;
        MEMO_OFFSET(memopg,indx)=0;
        MEMO_SIZE(memopg,indx)=0;

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


//----------------------------------------------------------------------------------------
#include <cccapi.h>
//----------------------------------------------------------------------------------------
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


//----------------------------------------------------------------------------------------
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


//----------------------------------------------------------------------------------------
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

//----------------------------------------------------------------------------------------
