

#include <ctype.h>
#include <cccapi.h>

//----------------------------------------------------------------------------------------
void _clp_ccccolor_to_ansicolor(int argno)
{
    // be: CCC color string, "044" vagy "gb+"
    // ki: ANSI color index, [0,255]

    CCC_PROLOG("ccccolor_to_ansicolor",1);
    str2bin(base);

    char *colorstring=_parb(1);
    int   colorindex=0;
    
    if( isdigit(colorstring[0]) ) //extended, e.g. 055
    {
        for( int i=0; i<3 && colorstring[i]!=0; i++ )
        {
            colorindex=(colorindex*6)+(colorstring[i]-'0');
        }
        colorindex+=16;
        colorindex&=255; // ANSI color index
    }
    else //legacy, e.g. gb+
    {
        for( int i=0; i<3 && colorstring[i]!=0; i++ )
        {
            char c=toupper(colorstring[i]);
            switch(c)
            {
                case 'R': colorindex|=1; break;
                case 'G': colorindex|=2; break;
                case 'B': colorindex|=4; break;
                case 'W': colorindex|=7; break;
                case '+': colorindex|=8; break;
            }
        }
    }
    _retni(colorindex);
    CCC_EPILOG();
}

//----------------------------------------------------------------------------------------
