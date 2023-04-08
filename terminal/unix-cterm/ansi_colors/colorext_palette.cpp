
#include <cccapi.h>

//---------------------------------------------------------------------------------
void _clp_colorext_palette(int argno)
{
    CCC_PROLOG("colorext_palette",1);
    
    int x=_parni(1);

    int w = (x & 0x01);        //0,1
    int rx=((x & 0x60)>>4)|w;  //3bit intensity index: 0,..,7
    int gx=((x & 0x18)>>2)|w;  //3bit intensity index: 0,..,7
    int bx=((x & 0x06)>>0)|w;  //3bit intensity index: 0,..,7

    //              0    0+   1    1+   2    2+   3    3+
    int color[8]={0x00,0x20,0x40,0x5f,0x87,0xaf,0xd7,0xff};
    
    number(color[rx]);
    number(color[gx]);
    number(color[bx]);
    array(3);
    _rettop();
 

    CCC_EPILOG();
}


//---------------------------------------------------------------------------------
