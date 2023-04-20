

#include <cccapi.h>
#include <ansi_colors.h>


void _clp_ccccolor_to_ansicolor(int argno)
{
    // be: color "123+"
    // ki: ansi  {r,g,b}

    CCC_PROLOG("ccccolor_to_ansicolor",1);
    str2bin(base);
    char *color=_parb(1);

    int rgb[4]={0,0,0,0};
    //          r g b w
    
    for( int i=0; i<4; i++ )
    {
        if( color[i]==0 )
        {
            break;
        }
        else if( color[i]=='+' )
        {
            rgb[3]=1;
            break;
        }
        
        rgb[i]=(color[i]-'0'); // 0,1,2,3
    }

    int x=0;
    x=(x<<2)|(rgb[0]&3); //r
    x=(x<<2)|(rgb[1]&3); //g
    x=(x<<2)|(rgb[2]&3); //b
    x=(x<<1)| rgb[3];    //w
    
    _retni(ansi_colors[x]);
    
    CCC_EPILOG();
}