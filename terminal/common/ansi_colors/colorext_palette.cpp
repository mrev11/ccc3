
#include <cccapi.h>

//---------------------------------------------------------------------------------
void _clp_colorext_palette(int argno)
{
    CCC_PROLOG("colorext_palette",1);
    
    int x=_parni(1);

    int w = (x & 0x01);     // 0,1
    int rx= (x & 0x60)>>4;  // 0,2,4,6
    int gx= (x & 0x18)>>2;  // 0,2,4,6
    int bx= (x & 0x06)>>0;  // 0,2,4,6

    int mx=0;
    if( rx>mx ) mx=rx;
    if( gx>mx ) mx=gx;
    if( bx>mx ) mx=bx;
    
    if( rx==mx ) rx|=w;     // 0,1,2,3,4,5,6,7
    if( gx==mx ) gx|=w;     // 0,1,2,3,4,5,6,7
    if( bx==mx ) bx|=w;     // 0,1,2,3,4,5,6,7

    //            0    0+   1    1+   2    2+   3    3+
    int color[8]={0x00,0x30,0x5f,0x5f,0x87,0xaf,0xd7,0xff};
    
    number(color[rx]);
    number(color[gx]);
    number(color[bx]);
    array(3);
    _rettop();

    CCC_EPILOG();
}


//---------------------------------------------------------------------------------
