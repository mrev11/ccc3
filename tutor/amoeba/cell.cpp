
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
#include <cccapi.h>

#include <amoeba.ch>  

typedef char XPATTERN[8];

struct cell;
 
static cell *best_move[2]={0,0};
static cell *second_move[2]={0,0};

#define BVAL(x)  (best_move[x]?best_move[x]->fieldval[x]:0)
#define BDIR(x)  (best_move[x]?best_move[x]->valuedir[x]:-1)
#define SVAL(x)  (second_move[x]?second_move[x]->fieldval[x]:0)
#define SDIR(x)  (second_move[x]?second_move[x]->valuedir[x]:-1)

static int  movestack[ROWCOL];  //lépések
static int  movecount = 0;      //lépésszám
static int  moveforw  = 0; 
static char winner    = ' ';
static int  DEBUG     = 0;
 
static cell*  cells[ROWCOL];
static int    spiral[ROWCOL]; 

extern void   _clp_go(int argno);
extern void   _clp_draw(int argno);
extern void   ponttab_init();
extern void   ponttab_print(XPATTERN a);
extern int    ponttab(XPATTERN a, char figure);
static int    posvalue(int);

//--------------------------------------------------------------------------
struct cell
{
    int row;
    int col;
    int count;
    char figure;
    
    XPATTERN pattern[4]; //négy irány: K,ÉK,É,ÉNy
    int fieldval[2];    //két játékos: [0]='O', [1]='X'
    int valuedir[2];    //milyen irányú az alakzat

    cell(int r, int c)
    {
        row=r;
        col=c;
        figure=' ';
        count=row*MAXCOL+col;

        for( int i=0;i<4;i++ )
        {
            for( int j=0;j<8;j++ )
            {
                pattern[i][j]='?'; 
            }
        }
        fieldval[0]=0;
        fieldval[1]=0;

        cells[count]=this;
    }
    
    void draw()
    {
        number(count);
        _clp_draw(1);
        pop();
    }

    cell *set()
    {
        if( (winner==' ') && (movecount<ROWCOL) )
        {
            movestack[movecount]=count;
    
            if( movecount++&1 )
            {
                figure='O'; 
                if( fieldval[0]>=PVALUE_EGY ) //PONTOK!! 
                {
                    winner=figure;
                }
            }
            else 
            {
                figure='X'; 
                if( fieldval[1]>=PVALUE_EGY ) //PONTOK!! 
                {
                    winner=figure;
                }
            }
            amod();
            return this;
        }
        return 0;
    }

    static cell *unset()
    {
        if( movecount>0 )
        {
            --movecount;
            cell *c=cells[movestack[movecount]];
            c->figure=' ';
            c->amod();
            winner=' ';
            return c;
        }
        return 0;
    }

    void amod()
    {
        int i,j;
        for(j=8,i=-4; i<=4; i++)
        {
            if( i==0 ) continue;
            j--;
            int x=count+i;
            if( x<0 || ROWCOL<=x ) continue;
            cell *c=cells[x];
            if( c->row!=row ) continue;
            c->pattern[0][j]=figure;
            if(c->figure==' ') c->ertek();
        }

        for(j=8,i=-4; i<=4; i++)
        {
            if( i==0 ) continue;
            j--;
            int x=count-i*(MAXCOL-1) ;
            if( x<0 || ROWCOL<=x ) continue;
            cell *c=cells[x];
            if( c->row+c->col!=row+col ) continue;
            c->pattern[1][j]=figure;
            if(c->figure==' ') c->ertek();
        }

        for(j=8,i=-4; i<=4; i++)
        {
            if( i==0 ) continue;
            j--;
            int x=count-i*MAXCOL ;
            if( x<0 || ROWCOL<=x ) continue;
            cell *c=cells[x];
            if( c->col!=col ) continue;
            c->pattern[2][j]=figure;
            if(c->figure==' ') c->ertek();
        }

        for(j=8,i=-4; i<=4; i++)
        {
            if( i==0 ) continue;
            j--;
            int x=count+i*(MAXCOL+1) ;
            if( x<0 || ROWCOL<=x ) continue;
            cell *c=cells[x];
            if( c->row-c->col!=row-col ) continue;
            c->pattern[3][j]=figure;
            if(c->figure==' ') c->ertek();
        }
    }

    void ertek()
    {
        fieldval[0]=0;
        fieldval[1]=0;
        valuedir[0]=-1;
        valuedir[1]=-1;

        int p0=0,p1=0,p;
        
        for( int dir=0; dir<4; dir++ )
        {
            p=ponttab(pattern[dir],'O');
            fieldval[0]+=p;
            if( p>p0 )
            {
                p0=p;
                valuedir[0]=dir;
            }
        
            p=ponttab(pattern[dir],'X');
            fieldval[1]+=p;
            if( p>p1 )
            {
                p1=p;
                valuedir[1]=dir;
            }
        }
    }

    int osszertek()
    {
        return max(fieldval[1],fieldval[0]); //X max, O min
    }
}; 


//--------------------------------------------------------------------------
void _clp_c_cb_button_press(int argno)
{
    CCC_PROLOG("c_cb_button_press",1);
    int x=_parni(1);

    cell *c=cells[x];

    if( winner!=' ' )
    {
        printf("\ngame over (%c)",winner);
    }
    else if( c->figure==' ' )
    {
        c->set()->draw();
        _clp_go(0);
        pop();
        moveforw=movecount;
    }
    
    _ret();
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_c_cb_button_press_stat(int argno)
{
    CCC_PROLOG("c_cb_button_press_stat",1);
    int x=_parni(1);

    cell *c=cells[x];

    if( c->figure==' ' )
    {
        printf("\n---------------------------------------\n");
        printf("x1=%d/%d  ",BVAL(1),BDIR(1));
        printf("x2=%d/%d  ",SVAL(1),SDIR(1));
        printf("o1=%d/%d  ",BVAL(0),BDIR(0));
        printf("o2=%d/%d  ",SVAL(0),SDIR(0));
        printf("%d",posvalue(0));
        printf("\n---------------------------------------\n");
        for(int i=0; i<4; i++)
        {
            ponttab_print(c->pattern[i]);
        }
        printf("\n");
    }
    _ret();
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_c_cb_move(int argno)
{
    CCC_PROLOG("c_cb_move",0);

    if( winner!=' ' )
    {
        printf("\ngame over (%c)",winner);
    }
    else
    {
        _clp_go(0);
        pop();
        moveforw=movecount;
    }

    _ret();
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_c_cb_back(int argno)
{
    CCC_PROLOG("c_cb_back",0);
    cell *c=cell::unset();
    if( c )
    {
        c->draw();
    }
    _ret();
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_c_cb_forward(int argno)
{
    CCC_PROLOG("c_cb_forward",0);
    if( movecount<moveforw )
    {
        cell *c=cells[movestack[movecount]];
        c->set();
        c->draw();
    }
    _ret();
    CCC_EPILOG();
}
 
//--------------------------------------------------------------------------
void _clp_c_cb_new( int argno )
{
    CCC_PROLOG("c_cb_new",0);
    cell *c;
    while( (c=cell::unset())!=0 );
    for(int n=0; n<ROWCOL; n++ )
    {
        cells[n]->draw();    
    }
    _ret();
    CCC_EPILOG();
}


//--------------------------------------------------------------------------
static int kozepre(const void *x, const void *y)
{
    cell *a=cells[ *(int*)x ];
    cell *b=cells[ *(int*)y ];
    int ca=abs((a->row-MAXROW/2))+abs((a->col-MAXCOL/2));
    int cb=abs((b->row-MAXROW/2))+abs((b->col-MAXCOL/2));
    
    if( ca>cb )
    {
        return 1;        
    }
    else if( cb>ca )
    {
        return -1;        
    }
    return 0;
}
 
//--------------------------------------------------------------------------
static int posvalue(int depth)
{
    //statikus állásértékelés
    //az elemzőfa levelein

    if( winner=='O' )
    {
        return -PVALUE_INFIN+depth;
    }
    else if( winner=='X' )
    {
        return  PVALUE_INFIN-depth;
    }
    else
    {
        int oturn=((movecount&1)==1);
        int xturn=((movecount&1)==0);
        int bo=BVAL(0),so=SVAL(0);
        int bx=BVAL(1),sx=SVAL(1);
        
        if( xturn )
        {
            if( sx>=bo )
            {
                return(bx+sx);
            }
            else if( bx>=bo )
            {
                return(bx);
            }
            else
            {
                return(-so);
            }
        }
        else //if( oturn )
        {
            if( so>=bx )
            {
                return(-bo-so);
            }
            else if( bo>=bx )
            {
                return(-bo);
            }
            else
            {
                return(sx);
            }
        }
    }
}

//--------------------------------------------------------------------------
static int compar(void const *xp, void const *yp)
{
    int *x=(int*)xp;
    int *y=(int*)yp;

    int res=0;
    
    if( *x<*y )
    {
        res=1;
    }
    else if( *x>*y )
    {
        res=-1;
    }
    return res;
}

//--------------------------------------------------------------------------
static void store_best(cell *c)
{
    for( int x=0; x<=1; x++ )
    {
        int v=c->fieldval[x];
        int d=c->valuedir[x];
        
        if( v>BVAL(x) && d!=SDIR(x) )
        {
            best_move[x]=c;
            
            if( v<SVAL(x) )
            {
                best_move[x]=second_move[x];
                second_move[x]=c;
            }
        }
        else if( v>SVAL(x) && d!=BDIR(x) )
        {
            second_move[x]=c;

            if( v>BVAL(x) )
            {
                second_move[x]=best_move[x];
                best_move[x]=c;
            }
        }
    }
}

//--------------------------------------------------------------------------
void _clp_movegen(int argno)
{
    //kikeresi a megadott számú "legfontosabb" mezőt

    CCC_PROLOG("movegen",1);
    int darab=min(32,min(_parni(1),ROWCOL-movecount));
    
    struct 
    {
        int v;  //mezőérték 
        int x;  //mezőindex
    } 
    legjobb[32];

    int cnt=0;
    int minx=0;
    int minv=-1;
    int maxv=-1;
    
    for(int i=0; i<ROWCOL; i++)
    {
        int x=spiral[i]; //középről kifelé
        int v;
        cell *c=cells[x];
        if( (c->figure==' ') && ((v=c->osszertek())>minv) )
        {
            maxv=max(v,maxv);
            legjobb[minx].x=x;
            legjobb[minx].v=v;
            cnt++;
            
            if( cnt<darab  )
            {
                minx=cnt;
            }
            else
            {
                minx=0;
                minv=legjobb[0].v; 
                for( int n=1; n<darab; n++ )
                {
                    if( legjobb[n].v<minv  )
                    {
                        minx=n;
                        minv=legjobb[n].v;
                    }
                }
            }
        }
    }
    
    qsort(legjobb,darab,2*sizeof(int),compar); //érdemes rendezni?

    //kiszűri az értelmetlen lépések egy részét
    if( maxv>=PVALUE_EGY ) //egylépéses fenyegetés
    {
        minv=PVALUE_EGY;
        
        //1) betömjük (EGY)
        //2) nyerünk máshol (EGY)
    }

#ifdef EZEK_NEM_JOK
    else if( maxv>=PVALUE_KET2 ) //kétlépéses fenyegetés két irányban
    {
        minv=PVALUE_KET1; 

        //1) betömjük (KET2)
        //2) egy irányt védünk (KET1) 
        //3) közbeiktatunk (KET1)
    }
    else if( maxv>=2*PVALUE_HAR2 )
    {
        minv=PVALUE_HAR1; 
    }
#endif

    int db=0;
    best_move[0]=0;
    best_move[1]=0;
    second_move[0]=0;
    second_move[1]=0;
    
    for( int n=0; n<darab; n++ )
    {
        if( legjobb[n].v>=minv )
        {
            cell *c=cells[legjobb[n].x];
            store_best(c);
            number( c->count );
            db++;
        }
    }
    array(db);
    _rettop();

    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_posvalue(int argno)
{
    CCC_PROLOG("posvalue",1);
    int depth=_parni(1);
    _retni(posvalue(depth));
    CCC_EPILOG();
}
 
//--------------------------------------------------------------------------
void _clp_forw(int argno)
{
    CCC_PROLOG("forw",1);
    int x=_parni(1);
    _retl( cells[x]->set() );
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_back(int argno)
{
    CCC_PROLOG("back",0);
    _retl( cell::unset() );
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_turn_x(int argno)
{
    CCC_PROLOG("turn_x",0);
    _retl( (movecount&1)==0 );
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_turn_o(int argno)
{
    CCC_PROLOG("turn_o",0);
    _retl( movecount&1 );
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_turn(int argno)
{
    CCC_PROLOG("turn",0);
    _retc( movecount&1?L"O":L"X" );
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_move(int argno)
{
    CCC_PROLOG("move",0);
    _retni( movecount );
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_figure(int argno)
{
    CCC_PROLOG("figure",1);
    int x=_parni(1);
    _retni( cells[x]->figure );
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_winner(int argno)
{
    CCC_PROLOG("winner",0);
    _retni( winner );
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_topcell(int argno)
{
    CCC_PROLOG("topcell",0);
    if( movecount>0 )
    {
        _retni(movestack[movecount-1]);
    }
    else
    {
        _ret();
    }
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_undercell(int argno)
{
    CCC_PROLOG("undercell",0);
    if( movecount>1 )
    {
        _retni(movestack[movecount-2]);
    }
    else
    {
        _ret();
    }
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_init_cells(int argno)
{
    CCC_PROLOG("init_cells",0);

    int i,j;
    for( i=0; i<MAXROW; i++ )
    for( j=0; j<MAXCOL; j++ )
    {
        cell *c=new cell(i,j); 
    }

    ponttab_init();
 
    for(int n=0; n<ROWCOL; n++ )
    {
        spiral[n]=n;    
        cells[n]->amod();
    }
    qsort(spiral,ROWCOL,sizeof(int),kozepre);

    _ret();
    CCC_EPILOG();
}
 
//--------------------------------------------------------------------------
