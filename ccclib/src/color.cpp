
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

#include <string.h>
#include <ctype.h>
#include <cccapi.h>

#define SIZEOF_COLORS 32
static char colors[SIZEOF_COLORS]={7,0,0,7,7,0,7,0,7,0,7,0,7,0,7,0}; //dafault colors

static int coloridx=0; //active color index

//----------------------------------------------------------------------------------------
int gettext_fg(void)
{
    return 255 & colors[ (coloridx<<1)+0 ];
}

int gettext_bg(void)
{
    return 255 & colors[ (coloridx<<1)+1 ];
}

//----------------------------------------------------------------------------------------
void setcoloridx(int x)
{
    coloridx=x;
}

//----------------------------------------------------------------------------------------
void _clp___setcoloridx(int argno)
{
    CCC_PROLOG("__setcoloridx",1);
    coloridx=_parni(1);
    CCC_EPILOG();
}

//----------------------------------------------------------------------------------------
void _clp___clr2num(int argno) //Clipper color string --> color numbers
{
    CCC_PROLOG("__clr2num",1);
    CHAR *p=_parc(1); // colorstring

    int colorindex=0;

    int i=0;
    int c=0;
    int dlim=',';   // elozo delimeter
    int mode=0;     // 0, x=extended, l=legacy
    int ntag=0;

    while( i<SIZEOF_COLORS )
    {
        c=(int)(*p++);

        if( mode==0  )
        {
            mode=isdigit(c)?'x':'l'; // extended/legacy
            ntag=0;                  // szamolas ujrakezdve
            colorindex=0;            // gyujtes ujrakezdve
        }

        if( c==0 ) // corostring vege
        {
            if( ntag>0 )
            {
                if( mode=='x' )
                {
                    colorindex+=16;
                }
                colors[i + ( dlim==','?0:1)]=255 & colorindex; // ',' utan fg, '/' utan bg
            }
            else
            {
                // ures szinnel nem modosit
            }
            break;
        }
        else if( c==',' ) // szinpar vege, uj szinpar kezdodik
        {
            if( ntag>0 )
            {
                if( mode=='x' )
                {
                    colorindex+=16;
                }
                colors[i + (dlim==','?0:1)]=255 & colorindex; // ',' utan fg, '/' utan bg
            }
            mode=0;
            dlim=',';
            i+=2;
        }
        else if( c=='/' ) // foreground vege, background kezdodik
        {
            if( ntag>0 )
            {
                if( mode=='x' )
                {
                    colorindex+=16;
                }
                colors[i]=255 & colorindex; // '/' elott mindig fg
            }
            mode=0;
            dlim='/';
        }
        else if( mode=='x' ) // extended
        {
            if( c!='+' )
            {
                ntag++;
                colorindex=colorindex*6+c-'0';
            }
        }
        else if( mode=='l' ) // legacy
        {
            ntag++;
            switch( toupper(c) )
            {
                case 'R': colorindex|=1; break;
                case 'G': colorindex|=2; break;
                case 'B': colorindex|=4; break;
                case 'W': colorindex|=7; break;
                case '+': colorindex|=8; break;
            }
        }
    }

    // printf("colors:%3d",colors[0]);
    // for(i=1; i<8; i++)
    // {
    //    printf(",%3d",colors[i]);
    // }
    // printf("\n");

    CCC_EPILOG();
}

//----------------------------------------------------------------------------------------
