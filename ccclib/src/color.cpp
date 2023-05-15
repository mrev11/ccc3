
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
static int colorstring_to_colorindex(CHAR *colorstring, int *nchar)
{
    int colorindex=0;
    int i=0;

    if( colorstring[0]=='#' ) // extended, e.g. "#217"
    {
        for( i=1; colorstring[i]!=0; i++ )
        {
            if( isdigit(colorstring[i]) )
            {
                colorindex=(colorindex*10)+(colorstring[i]-'0');
            }
            else
            {
                break;
            }
        }
    }
    else if( isdigit(colorstring[0]) ) // extended, e.g. "055"
    {
        for( i=0; colorstring[i]!=0; i++ )
        {
            if( isdigit(colorstring[i]) )
            {
                colorindex=(colorindex*6)+(colorstring[i]-'0');
            }
            else if( colorstring[i]=='+' )
            {
                // compatibility
            }
            else
            {
                break;
            }
        }
        colorindex+=16;
    }
    else // legacy, e.g. "gb+"
    {
        for( i=0; colorstring[i]!=0; i++ )
        {
            char c=toupper(colorstring[i]);

                 if( c=='R' ) colorindex|=1;
            else if( c=='G' ) colorindex|=2;
            else if( c=='B' ) colorindex|=4;
            else if( c=='W' ) colorindex|=7;
            else if( c=='+' ) colorindex|=8;
            else              break;
        }
    }

    *nchar=i; // ennyi elemet hasznalt el a stringbol

    return colorindex & 255; // ANSI color index
}


//----------------------------------------------------------------------------------------
void _clp_colorstring_to_colorindex(int argno)
{
    // be - CCC color string: "#217" vagy "044" vagy "gb+"
    // ki - ANSI color index: [0,255]

    CCC_PROLOG("colorstring_to_colorindex",1);
    int nchar=0;
    _retni( colorstring_to_colorindex(_parc(1),&nchar) );
    CCC_EPILOG();
}


//----------------------------------------------------------------------------------------
void _clp___clr2num(int argno) //Clipper color string --> color numbers
{
    CCC_PROLOG("__clr2num",1);
    CHAR *colorstring=_parc(1); // colorstring: "w/n,n/w,...."

    int i=0;
    while( i<SIZEOF_COLORS )
    {
        int nchar=0;
        int colorindex=colorstring_to_colorindex(colorstring,&nchar);
        int delimeter=colorstring[nchar];

        if( (i&1)==0 )
        {
            // foreground
            if( delimeter=='/' )
            {
                colors[i++]=colorindex;
            }
            else if( delimeter==',' )
            {
                colors[i++]=colorindex;
                i++;
            }
            else if( delimeter==0 )
            {
                colors[i++]=colorindex;
                break;
            }
            else
            {
                //error
            }
        }
        else
        {
            // background
            if( delimeter==',' )
            {
                colors[i++]=colorindex;
            }
            else if( delimeter==0 )
            {
                colors[i++]=colorindex;
                break;
            }
            else
            {
                //error
            }
        }
        colorstring+=(nchar+1);
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
