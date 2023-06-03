
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


#define uint                    u_int32_t
#define MEMOPG                  u_int32_t


#define PGNO(page)              page[0]         // page sorszam (diszken CRC)
#define LINK(page)              page[1]         // kovetkezo szabad memo page (28 biten)
#define LOWER(page)             page[2]         // elso szabad hely offsete
#define UPPER(page)             page[3]         // elso nemszabad hely offsete

#define MASKLINK                0x0fffffff
#define MASKFLAG                ~MASKLINK
#define FLAGMEMO                0x8

#define GETLINK(page)           (LINK(page)&MASKLINK)
#define SETLINK(page,x)         (LINK(page)=((LINK(page)&MASKFLAG)|((x)&MASKLINK)))

#define GETFLAG(page)           ((LINK(page)&MASKFLAG)>>28)
#define SETFLAG(page,x)         (LINK(page)=((LINK(page)&MASKLINK)|(((x)<<28)&MASKFLAG)))

#define MEMO_ID(page,x)         page[4*x+4]     // memo ID
#define MEMO_DESC(page,x)       page[4*x+5]     // memo szegmens offsete es merete
#define MEMO_PGNEXT(page,x)     page[4*x+6]     // kovetkezo szegmens lapja
#define MEMO_IXNEXT(page,x)     page[4*x+7]     // kovetkezo szegmens indexe

#define MEMOID(r,x)             ((r)|((x)<<28)) // 28 bit recno + 4 bit memox
#define MEMODESC(o,s)           ((o)|((s)<<16)) // 16 bit offset + 16 bit size

#define MEMO_OFFS(p,x)          (0xffff&(MEMO_DESC(p,x)    ))   //also 16 bit
#define MEMO_SIZE(p,x)          (0xffff&(MEMO_DESC(p,x)>>16))   //felso 16 bit


#define PAGEHEAD                (4*sizeof(uint))
#define MEMOHEAD                (4*sizeof(uint))
#define MINSPACE                (512)

#define PLOWER(page)            ((char*)page+LOWER(page))
#define PUPPER(page)            ((char*)page+UPPER(page))
#define ADDRESS(page,x)         ((char*)page+MEMO_OFFS(page,x))
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

        SETLINK(memopg,0);
        SETFLAG(memopg,FLAGMEMO);

        //printf(">>>>>__bt_memopage-new  %x\n", pgno);
    }
    return memopg;
}

//----------------------------------------------------------------------------------------
static RECPOS  __bt_memowrite(BTREE *t, DBT *data, uint recno, uint memox)
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
            if( MEMO_DESC(memopg,indx)==0 )
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
            MEMO_IXNEXT(prevpage,previndx) = indx;

            uint prevpgno=PGNO(prevpage);  // mpool_put atirja CRC-re
            mpool_put(t->bt_mp,prevpage,MPOOL_DIRTY);
            __bt_pageunlock(t,prevpgno);
        }


        size_t space=UPPER(memopg)-LOWER(memopg);     // szabad hely
        size_t towrite=MIN(data->size-written,space); // ennyit irunk most ki
        UPPER(memopg)-=towrite;
        memmove(PUPPER(memopg), (char*)data->data+written, towrite);

        MEMO_ID(memopg,indx)     = MEMOID(recno,memox);
        MEMO_DESC(memopg,indx)   = MEMODESC(UPPER(memopg),towrite);
        MEMO_PGNEXT(memopg,indx) = 0;
        MEMO_IXNEXT(memopg,indx) = 0;

        written+=towrite;

        // szabadlista modositas

        if( UPPER(memopg)-LOWER(memopg) < MINSPACE )
        {
            // NEM MARADT HELY A LAPON
            if( GETLINK(memopg)!=0 )
            {
                // szabadlistabol vett lap
                // ki kell vanni a szabadlistabol
                // KIVESZ

                if( GETLINK(memopg)==PGNO(memopg) )
                {
                    // utolso elem
                    t->bt_memo=0;
                }
                else
                {
                    // folytatodik a lista
                    t->bt_memo=GETLINK(memopg);
                }
                SETLINK(memopg,0);
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
            if( GETLINK(memopg)!=0 )
            {
                // szabadlistabol vett lap
                // nem modosul a szabadlista
            }
            else
            {
                // nem szabadlistabol vett lap
                // be kell rakni a szabadlistaba
                // (elso es egyben utolso elem)
                // BERAK

                t->bt_memo=PGNO(memopg);        // elso elem
                SETLINK(memopg,PGNO(memopg));   // utolso elem
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
static DBT __bt_memoread(BTREE *t, RECPOS recpos, uint recno, uint memox)
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
        else if( (GETFLAG(memopg)&FLAGMEMO)==0 )
        {
            char error[128];
            sprintf(error,"__bt_memoread: invalid page type (%x,%d)\n",pgno,GETFLAG(memopg));
            __bt_error(error);
        }
        else if( indx>=MEMOCOUNT(memopg) )
        {
            // hasonlo a helyzet mint a kovetkezo if agban
            // a takaritas a megvaltozott memo headerjet arrebb teheti

            //char error[128];
            //sprintf(error,"__bt_memoread: memo index out of bound (%x,%d)\n",pgno,indx);

            data=0;
            size=0;
            mpool_put(t->bt_mp,memopg,0);
            break;
        }
        else if( MEMO_ID(memopg,indx)!=MEMOID(recno,memox) )
        {
            // A rekordbuffer beolvasasa utan (de a memo beolvasasa elott)
            // egy masik processz atirhatja a memo-t, es azert itt egy masik
            // rekord memojat is kaphatjuk. Ilyenkor ures memoerteket adunk.
            // Ujra kell olvasni a rekordot, es probalkozni az uj memo-val. 

            data=0;
            size=0;
            mpool_put(t->bt_mp,memopg,0);
            break;
        }

        uint next_pgno=MEMO_PGNEXT(memopg,indx);
        uint next_indx=MEMO_IXNEXT(memopg,indx);
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
        else if( (GETFLAG(memopg)&FLAGMEMO)==0 )
        {
            char error[128];
            sprintf(error,"__bt_memodel: invalid page type (%x,%d)\n",pgno,GETFLAG(memopg));
            __bt_error(error);
        }
        else if( indx>=MEMOCOUNT(memopg) )
        {
            char error[128];
            sprintf(error,"__bt_memodel: memo index out of bound (%x,%d)\n",pgno,indx);
            __bt_error(error);
        }
        else if( MEMO_DESC(memopg,indx)==0 )
        {
            char error[128];
            sprintf(error,"__bt_memodel: deleted memo (%x,%d)\n",pgno,indx);
            __bt_error(error);
        }

        uint size=MEMO_SIZE(memopg,indx); // felszabadulo hely merete
        memmove(PUPPER(memopg)+size,PUPPER(memopg),MEMO_OFFS(memopg,indx)-UPPER(memopg));
        memset(PUPPER(memopg),0,size);
        UPPER(memopg)+=size;

        for(uint i=0; i<MEMOCOUNT(memopg); i++)
        {
            if( MEMO_DESC(memopg,i)==0 )
            {
                // a lyukak helyen 0 van
            }
            else if( MEMO_OFFS(memopg,i)<MEMO_OFFS(memopg,indx)  )
            {
                // ezek hatrebb csusztak
                MEMO_DESC(memopg,i)=MEMODESC(MEMO_OFFS(memopg,i)+size,MEMO_SIZE(memopg,i));
            }
        }


        uint next_pgno=MEMO_PGNEXT(memopg,indx);
        uint next_indx=MEMO_IXNEXT(memopg,indx);

        MEMO_ID(memopg,indx)=0;
        MEMO_DESC(memopg,indx)=0;
        MEMO_PGNEXT(memopg,indx)=0;
        MEMO_IXNEXT(memopg,indx)=0;

        for(uint i=MEMOCOUNT(memopg)-1; i>=0; i-- )
        {
            if( MEMO_DESC(memopg,i)!=0 )
            {
                break;
            }
            LOWER(memopg)-=MEMOHEAD; //takarit
        }


        if( UPPER(memopg)-LOWER(memopg) < MINSPACE )
        {
            // nem keletkezett eleg szabad hely
            // => korabban sem lehetett a szabadlistaban
            // => a szabadlista nem valtozik
        }
        else if( GETLINK(memopg)!=0 )
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
                SETLINK(memopg,link);           // a korabbi elsore mutat
            }
            else
            {
                SETLINK(memopg,PGNO(memopg));   // utolso elem onmagara mutat
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


//----------------------------------------------------------------------------------------
#include <cccapi.h>
//----------------------------------------------------------------------------------------
void _clp__db_memowrite(int argno)
{
    CCC_PROLOG("_db_memowrite",4);
    BTREE *db=(BTREE*)_parp(1);
    str2bin(base+1);
    DBT dbt;
    dbt.data=_parb(2);
    dbt.size=_parblen(2);
    uint recno=_parnu(3);
    uint memox=_parnu(4);
    RECPOS rp=__bt_memowrite(db,&dbt,recno,memox);
    char recpos[32];
    sprintf(recpos,"%07x%03x",rp.pgno,rp.index);
    _retb(recpos);
    CCC_EPILOG();
}


//----------------------------------------------------------------------------------------
void _clp__db_memoread(int argno)
{
    CCC_PROLOG("_db_memoread",4);
    BTREE *db=(BTREE*)_parp(1);
    str2bin(base+1);
    char *pos=_parb(2);
    uint recno=_parnu(3);
    uint memox=_parnu(4);
    int pgno=0,index=0;
    if( _parblen(2)!=10 || 2!=sscanf(pos,"%07x%03x",&pgno,&index) )
    {
        error_arg("_db_memoread",base,argno);
    }
    RECPOS recpos;
    recpos.pgno=pgno;
    recpos.index=index;
    DBT dbt=__bt_memoread(db,recpos,recno,memox);
    if( dbt.data )
    {
        _retblen((char*)dbt.data,dbt.size);
        free(dbt.data);
    }
    else
    {
        _ret(); //NIL
    }
    CCC_EPILOG();
}


//----------------------------------------------------------------------------------------
void _clp__db_memodel(int argno)
{
    CCC_PROLOG("_db_memodel",2);
    BTREE *db=(BTREE*)_parp(1);
    str2bin(base+1);
    char *pos=_parb(2);
    int pgno=0,index=0;
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
