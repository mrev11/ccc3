
#include <stdio.h>
#include <stdlib.h>

extern void message(char const *msg, ...);

extern int colorext_extidx2legidx(int);
extern int colorext_legidx2extidx(int);
extern int colorext_palette(int);

//---------------------------------------------------------------------------------
int colorext_extidx2legidx(int x)  //extended index -> legacy index
{
    static int tab_ext2leg[129]={0,0,1,1,1,9,9,9,2,2,3,3,1,9,9,9,2,10,2,10,3,11,9,9,10,10,10,10,10,10,11,11,4,4,5,5,1,9,9,9,6,6,8,8,1,9,9,9,2,10,2,10,3,11,9,9,10,10,10,10,10,10,11,11,4,12,4,12,5,13,9,9,4,12,4,12,5,13,9,9,6,14,6,14,7,7,9,9,10,10,10,10,10,10,11,11,12,12,12,12,12,12,13,13,12,12,12,12,12,12,13,13,12,12,12,12,12,12,13,13,14,14,14,14,14,14,7,15,0};
    return tab_ext2leg[ x & 0x7f ];  // jelzobit leveve
}

//---------------------------------------------------------------------------------
int colorext_legidx2extidx(int x)  // legacy index -> extended index
{
    static int tab_leg2ext[17]={0,4,16,20,64,68,80,126,43,7,25,31,97,103,121,127,0};
    return tab_leg2ext[x] | 0x80;    // jelzobit beallitva
}

//---------------------------------------------------------------------------------
int colorext_palette(int x)  // extidx -> 3byte rgb
{
    int w = (x & 0x01);        //0,1
    int rx=((x & 0x60)>>4)|w;  //3bit intensity index: 0,..,7
    int gx=((x & 0x18)>>2)|w;  //3bit intensity index: 0,..,7
    int bx=((x & 0x06)>>0)|w;  //3bit intensity index: 0,..,7

    //              0    0+   1    1+   2    2+   3    3+
    int color[8]={0x00,0x20,0x40,0x60,0x80,0xa0,0xc0,0xff};
    int rgb=color[rx]<<16|color[gx]<<8|color[bx];

    return rgb;  //3byte rgb
}


#ifdef NOTDEF
//---------------------------------------------------------------------------------
typedef struct colint 
{
    char    name; 
    int     intensity; 
} COLINT;


//---------------------------------------------------------------------------------
static int colcmp( const void *p1, const void *p2 )
{
    COLINT const *x=(COLINT*)p1;
    COLINT const *y=(COLINT*)p2;

    if( x->intensity < y->intensity )
    {
        return 1;
    }
    else if( x->intensity > y->intensity )
    {
        return -1;
    }
    return 0;
}


//---------------------------------------------------------------------------------
static void sort(COLINT *ci)
{
    qsort(ci,3,sizeof(COLINT),colcmp);
}


//---------------------------------------------------------------------------------
static int XXcolorext_extidx2legidx( int extidx )  

// hasznalaton kivul
// helyette: colorext_extidx2legidx(x)
// eredetileg ezzel volt kiszamolva
// a colorext_extidx2legidx-beli tablazat

{
    int legidx=0;

    COLINT colint[3];

    int w=(extidx&0x01);           //0,1
    int r=((extidx&0x60)>>4)|w;    //0,1,2,3,5,6,7
    int g=((extidx&0x18)>>2)|w;    //0,1,2,3,5,6,7
    int b=((extidx&0x06)>>0)|w;    //0,1,2,3,5,6,7

    colint[0].name='r'; colint[0].intensity=r;
    colint[1].name='g'; colint[1].intensity=g;
    colint[2].name='b'; colint[2].intensity=b;
    
    //for( int i=0; i<3; i++ )
    //{
    //    message( "colint: %c %d \n",colint[i].name,colint[i].intensity);
    //}

    sort( colint );

    //for( int i=0; i<3; i++ )
    //{
    //    message( "sorted colint: %c %d \n",colint[i].name,colint[i].intensity);
    //}
    
    if( colint[0].intensity==colint[2].intensity )
    {
        //0  1   2  3   4  5   6  7
        //0, 0+, 1, 1+, 2, 2+, 3, 3+
        //n         n+         w  w+
        //n  n   n+ n+  w  w   w  w+

        if( colint[0].intensity<2 )
        {
            legidx=0;
        }
        else if( colint[0].intensity<4 )
        {
            legidx=8;
        }
        else if( colint[0].intensity<7 )
        {
            legidx=7;
        }
        else 
        {
            legidx=15;
        }
    }
    else if( colint[0].intensity==colint[1].intensity )
    {
        //gb,rb,rg
        if( colint[2].name=='r' ) //4
        {
            legidx=3;
        }
        else if( colint[2].name=='g' ) //2
        {
            legidx=5;
        }
        else if( colint[2].name=='b' ) //1
        {
            legidx=6;
        }

        if( colint[0].intensity>4 )
        {
            legidx|=8;
        }
    }
    else
    {
        //r,g,b
        if( colint[0].name=='r' ) //4
        {
            legidx=4;
        }
        else if( colint[0].name=='g' ) //2
        {
            legidx=2;
        }
        else if( colint[0].name=='b' ) //1
        {
            legidx=1;
        }

        if( colint[0].intensity>4 )
        {
            legidx|=8;
        }
    }

    //message( "extidx2legidx: %x -> %x\n",extidx,legidx);

    return legidx;  //0,1,...15
}



#ifdef NOTDEF

Az extidx szinkodolasrol:

    setcolor( "333/222+,w/n, ... " )
                   ^^^^
                   ||||
                   |||+---  +  minden osszetevot egy fokozattal megemel
                   ||+----  b  0,1,2,3
                   |+-----  g  0,1,2,3
                   +------  r  0,1,2,3

Peldaul 222+  minden osszetevoben az 5-os fokozatot jelenti,
azaz mindharom osszetevo erteke 0xa0.

              0    0+   1    1+   2    2+   3    3+
              0    1    2    3    4    5    6    7
int color[8]={0x00,0x20,0x40,0x60,0x80,0xa0,0xc0,0xff};


A hagyomanyos es az extended szinkodok megfelelese:

    leg   ext
    ---   ---
    n     000   
    n+    111+  
    w     333   
    w+    333+  

    r     200   
    r+    300+  
    g     020   
    g+    030+  
    b     002   
    b+    003+  

    rg    220   
    rg+   330+  
    rb    202   
    rb+   303+  
    gb    022   
    gb+   033+  

A fentiek azonos szint adnak a legacy es az extended kodolassal.
Az extended kodolas tovabbi arnyalatok eloallitasara kepes,
a kodok es szinek megfeleltetese monoton olyan ertelemben,
hogy novekvo rgb kod vilagosabb szint eredmenyez.

Az ncurses-es terminal nem tudja megjeleniteni az extended
kodolassal megadhato osszes szint, ezert visszatranszformalja
a szineket az eredeti 16 szinre (valojaban csak 8), ezert bizonyos
arnyalatok egybeeshetnek.

A CCC2-ben csak 16 szin lehet (4 biten tarolodik egy szin),
ezert a CCC2 is visszatranszformalja az extended kodolast
a hagyomanyos szinekre.

Az extended szinkodok lekepezese 1 bajt bitjeire:

    high             low
    8   7 6  5 4  3 2  1  
    ^   ^^^  ^^^  ^^^  ^
    |    |    |    |   |
    |    |    |    |   +--- minden osszetevot megemelo bit
    |    |    |    +------- b ket biten
    |    |    +------------ g ket biten
    |    +----------------- r ket biten
    +---------------------- extended formatumot jelzo bit



A legacy szinek 6 bajtos rgb ertekei:

    COLOR_BLACK             0x000000
    COLOR_LTBLACK           0x606060
    COLOR_WHITE             0xc0c0c0
    COLOR_LTWHITE           0xffffff
   
    COLOR_RED               0x000080
    COLOR_GREEN             0x008000
    COLOR_BLUE              0x800000
   
    COLOR_CYAN              0x808000
    COLOR_MAGENTA           0x800080
    COLOR_YELLOW            0x008080
   
    COLOR_LTRED             0x2020ff
    COLOR_LTGREEN           0x20ff20
    COLOR_LTBLUE            0xff2020
   
    COLOR_LTCYAN            0xffff20
    COLOR_LTMAGENTA         0xff20ff
    COLOR_LTYELLOW          0x20ffff


A legacy szinek indexei:

    COLOR_BLACK,             //  0
    COLOR_BLUE,              //  1:
    COLOR_GREEN,             //  2:
    COLOR_CYAN,              //  3: 1 2 
    COLOR_RED,               //  4:
    COLOR_MAGENTA,           //  5: 1   4
    COLOR_YELLOW,            //  6:   2 4
    COLOR_WHITE,             //  7: 1 2 4
  
    COLOR_LTBLACK,           //  8:
    COLOR_LTBLUE,            //  9: 1     8
    COLOR_LTGREEN,           // 10:   2   8
    COLOR_LTCYAN,            // 11: 1 2   8
    COLOR_LTRED,             // 12:     4 8
    COLOR_LTMAGENTA,         // 13: 1   4 8
    COLOR_LTYELLOW,          // 14:   2 4 8
    COLOR_LTWHITE            // 15
  

Egymasnak megfelelo szinek es indexek:

    0  1   2  3   4  5   6  7
    0, 0+, 1, 1+, 2, 2+, 3, 3+
    n         n+         w  w+


    legacy  extended      leg        ext
    code    code          idx        idx
    ------------------------------------
    n       000             0          0
    n+      111+            8         43
    w       333             7        126
    w+      333+           15        127
                                   
    r       200             4         64
    r+      300+           12         97
    g       020             2         16
    g+      030+           10         25
    b       002             1          4
    b+      003+            9          7
                                   
    rg      220             6         80
    rg+     330+           14        121
    rb      202             5         68
    rb+     303+           13        103
    gb      022             3         20
    gb+     033+           11         31


    legacy  extended      leg        ext
    code    code          idx        idx
    ------------------------------------
    n       000             0          0 
    b       002             1          4 
    g       020             2         16 
    gb      022             3         20 
    r       200             4         64 
    rb      202             5         68 
    rg      220             6         80 
    w       333             7        126 
    n+      111+            8         43 
    b+      003+            9          7 
    g+      030+           10         25 
    gb+     033+           11         31 
    r+      300+           12         97 
    rb+     303+           13        103 
    rg+     330+           14        121 
    w+      333+           15        127 

#endif
#endif

