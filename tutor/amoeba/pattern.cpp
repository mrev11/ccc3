
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
#include <amoeba.ch>

#define TABSIZE  6561  //3^8 

typedef char XPATTERN[8];

extern void   ponttab_init();
extern void   ponttab_print(XPATTERN a);
extern int    ponttab(XPATTERN a, char fig);
 

static char const *egy[]={
"    XXXX",
"   XXXX ",
"  XXXX  ",
" XXXX   ",
"XXXX    ",
0};

static char const *ket2[]={
"_XXX_   ", 
" _XXX_  ", 
"  _XXX_ ", 
"   _XXX_", 
"XXX__XXX", 
" XX_X_XX", 
"XX_X_XX ", 
"  X_XX_X", 
" X_XX_X ", 
"X_XX_X  ", 
0};


static char const *ket1[]={
"    _XXX",
"    X_XX",
"    XX_X",
"    XXX_",
"   _XXX ",
"   X_XX ",
"   XX_X ",
"   XXX_ ",
"  _XXX  ",
"  X_XX  ",
"  XX_X  ",
"  XXX_  ",
" _XXX   ",
" X_XX   ",
" XX_X   ",
" XXX_   ",
"_XXX    ",
"X_XX    ",
"XX_X    ",
"XXX_    ",
0};


static char const *harom2[]={
"__XX_   ", 
"_X_X_   ", 
"_XX__   ", 
" __XX_  ", 
" _X_X_  ", 
" _XX__  ", 
"  __XX_ ", 
"  _X_X_ ", 
"  _XX__ ", 
"   __XX_", 
"   _X_X_", 
"   _XX__", 
" XX___XX", 
"XX___XX ", 
"  X__X_X", 
"  X_X__X", 
" X__X_X ", 
" X_X__X ", 
"X__X_X  ", 
"X_X__X  ", 
0};


static char const *harom1[]={
"    __XX",
"    _X_X",
"    _XX_",
"    X__X",
"    X_X_",
"    XX__",
"   __XX ",
"   _X_X ",
"   _XX_ ",
"   X__X ",
"   X_X_ ",
"   XX__ ",
"  __XX  ",
"  _X_X  ",
"  _XX_  ",
"  X__X  ",
"  X_X_  ",
"  XX__  ",
" __XX   ",
" _X_X   ",
" _XX_   ",
" X__X   ",
" X_X_   ",
" XX__   ",
"__XX    ",
"_X_X    ",
"_XX_    ",
"X__X    ",
"X_X_    ",
"XX__    ",
0};
 

static char const *negy2[]={
"___X_   ", 
"__X__   ", 
"_X___   ", 
" ___X_  ", 
" __X__  ", 
" _X___  ", 
"  ___X_ ", 
"  __X__ ", 
"  _X___ ", 
"   ___X_", 
"   __X__", 
"   _X___", 
0};
 
//--------------------------------------------------------------------------
static void aprint(XPATTERN a)
{
    int n;
    for(n=0; n<4; n++)
    {
        printf("%c",a[n]);
    }
    printf(".");
    for(n=4; n<8; n++)
    {
        printf("%c",a[n]);
    }
    printf(" ");
}
 
//--------------------------------------------------------------------------
static int str2x(XPATTERN a, char figure)
{
    int x=0;
    
    for(int i=0; i<8; i++)
    {
        x*=3;
        char c=a[i];

        if(  c==' ' )
        {
            //üres
        }
        else if( c==figure ) 
        {
            x+=1; //saját
        }
        else
        {
            x+=2; //foglalt (vagy kilóg)
        }
    }

    return x;
}

//--------------------------------------------------------------------------
static int str2i(char const *x, int base, int len)
{
    int result=0;
    while( len-->0 )
    {
        result*=base;
        result+=*x-'0';
        x++;
    }
    return result;
}
 
//--------------------------------------------------------------------------
static void i2str(int i, char *x, int base, int len) 
{
    while( len-->0 )
    {
        *(x+len)='0'+i%base;
        i/=base;
    }
}

//--------------------------------------------------------------------------
static int table[TABSIZE]; 

//--------------------------------------------------------------------------
static void ponttab_feltolt( char const *XPATTERN[], int ertek )
{
    for(int n=0; XPATTERN[n]!=0; n++ )
    {
        for(int i=0; i<TABSIZE; i++)
        {
            char x[8]; //nyolcjegyű 3-as számrendszerbeli szám
            i2str(i,x,3,8);
            
            for(int j=0; j<8; j++)
            {
                char c=XPATTERN[n][j];
            
                if( c=='X'  )
                {
                    x[j]='1';
                }
                else if( c=='_'  )
                {
                    x[j]='0';
                }
            }
            
            int ix=str2i(x,3,8);
            if( table[ix]==0 )
            {
                table[ix]=ertek;
            }
        }
    }
}

//--------------------------------------------------------------------------
void ponttab_init()
{
    for(int i=0; i<TABSIZE; i++)
    {
        table[i]=0;
    }
    
    //PONTOK!!
    ponttab_feltolt(egy    , PVALUE_EGY);
    ponttab_feltolt(ket2   , PVALUE_KET2);
    ponttab_feltolt(ket1   , PVALUE_KET1);
    ponttab_feltolt(harom2 , PVALUE_HAR2);
    ponttab_feltolt(harom1 , PVALUE_HAR1);
    ponttab_feltolt(negy2  , PVALUE_NEGY2);
}


//--------------------------------------------------------------------------
int ponttab(XPATTERN a, char figure)
{
    return table[ str2x(a,figure) ];
}

//--------------------------------------------------------------------------
void ponttab_print(XPATTERN a)
{
    int ix=str2x(a,'X');
    int io=str2x(a,'O');
    printf("%4d(%3d) %4d(%3d)",io,table[io],ix,table[ix]);
    aprint(a);
    printf("\n");
}

 
//--------------------------------------------------------------------------
#ifdef MAIN

int main()
{
    ponttab_init();

    for(int n=0; n<TABSIZE; n++)
    {
        char x[9];
        i2str(n,x,3,8); 
        x[8]=0;
        
        //if( table[n]==10 )
        {
            printf("%4d %s %3d \n",n,x,table[n]);
        }
    }

    return 0;
}

#endif

//--------------------------------------------------------------------------
#ifdef ALAKZAT_OSZTALYOZASA

egylépéses fenyegetések (nyerőlépések)

"    .XXXX"
"   X.XXX "
"  XX.XX  "
" XXX.X   "
"XXXX.    "


kétlépéses kétirányú fenyegetések

"_XXX._   " 
" _XX.X_  " 
"  _X.XX_ " 
"   _.XXX_" 
"XXX_._XXX" 
" XX_.X_XX" 
"XX_X._XX " 
"  X_.XX_X" 
" X_X.X_X " 
"X_XX._X  " 


kétlépéses egyirányú fenyegetések
 
"    ._XXX"
"    .X_XX"
"    .XX_X"
"    .XXX_"
"   _.XXX "
"   X._XX "
"   X.X_X "
"   X.XX_ "
"  _X.XX  "
"  X_.XX  "
"  XX._X  "
"  XX.X_  "
" _XX.X   "
" X_X.X   "
" XX_.X   "
" XXX._   "
"_XXX.    "
"X_XX.    "
"XX_X.    "
"XXX_.    "
 

háromlépses kétirányú fenyegetések

"__XX._   " 
"_X_X._   " 
"_XX_._   " 
" __X.X_  " 
" _X_.X_  " 
" _XX.__  " 
"  __.XX_ " 
"  _X._X_ " 
"  _X.X__ " 
"   _._XX_" 
"   _.X_X_" 
"   _.XX__" 
" XX_.__XX" 
"XX__._XX " 
"  X_._X_X" 
"  X_.X__X" 
" X__.X_X " 
" X_X.__X " 
"X__X._X  " 
"X_X_._X  " 


háromlépéses egyirányú fenyegetések
 
"    .__XX"
"    ._X_X"
"    ._XX_"
"    .X__X"
"    .X_X_"
"    .XX__"
"   _._XX "
"   _.X_X "
"   _.XX_ "
"   X.__X "
"   X._X_ "
"   X.X__ "
"  __.XX  "
"  _X._X  "
"  _X.X_  "
"  X_._X  "
"  X_.X_  "
"  XX.__  "
" __X.X   "
" _X_.X   "
" _XX._   "
" X__.X   "
" X_X._   "
" XX_._   "
"__XX.    "
"_X_X.    "
"_XX_.    "
"X__X.    "
"X_X_.    "
"XX__.    "
 

négylépses kétirányú fenyegetések

"___X._   " 
"__X_._   " 
"_X__._   " 
" ___.X_  " 
" __X.__  " 
" _X_.__  " 
"  __._X_ " 
"  __.X__ " 
"  _X.___ " 
"   _.__X_" 
"   _._X__" 
"   _.X___" 

#endif 

