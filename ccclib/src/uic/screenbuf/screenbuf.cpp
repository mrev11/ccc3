
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

#include <malloc.h>
#include <stdio.h>
#include <screenbuf.h>

//---------------------------------------------------------------------------
screenbuf::screenbuf(int x, int y)
{
    sizex=x;
    sizey=y;
    defattr=DEFATTR;
    buffer=(screencell*)malloc(x*y*sizeof(screencell));

    int i,j;
    for( j=0; j<sizey; j++ )
    {
        for( i=0; i<sizex; i++ )
        {
            cell(i,j)->setchar(32);
            cell(i,j)->setattr(DEFATTR);
        }
    }
}

//---------------------------------------------------------------------------
screenbuf::~screenbuf()
{
    if( buffer )
    {
        delete(buffer);
    }
}

//---------------------------------------------------------------------------
screencell *screenbuf::cell(int x, int y)
{
    return buffer+y*sizex+x;
}
    
//----------------------------------------------------------------------------
void screenbuf::dump(const char *caption)
{
    printf("%s-1\n",caption);
    for(int j=0; j<sizey; j++ )
    {
        for(int i=0; i<sizex; i++ )
        {
            printf("%04x %02x ", 
                   cell(i,j)->getchar(),cell(i,j)->getattr() );
        }
        printf("\n");
    }
    printf("%s-2\n",caption);fflush(0);
}

//---------------------------------------------------------------------------
void screenbuf::clear()
{
    int i,j;
    for( j=0; j<sizey; j++ )
    {
        for( i=0; i<sizex; i++ )
        {
            cell(i,j)->setchar(32);
            cell(i,j)->setattr(DEFATTR);
        }
    }
}

//---------------------------------------------------------------------------
void screenbuf::clearrect(int lef, int top, int rig, int bot)
{
    if( top>bot || top<0 || bot>=sizey || 
        lef>rig || lef<0 || rig>=sizex   )
    {
        return;
    }
    int i,j;
    for( j=top; j<=bot; j++ )
    {
        for( i=lef; i<=rig; i++ )
        {
            cell(i,j)->setchar(32);
            cell(i,j)->setattr(defattr);
        }
    }
}

//---------------------------------------------------------------------------
int screenbuf::getrect(int lef, int top, int rig, int bot, screencell *dest)
{
    if( top>bot || top<0 || bot>=sizey || 
        lef>rig || lef<0 || rig>=sizex   )
    {
        return 0;
    }
    int i,j;
    for( j=top; j<=bot; j++ )
    {
        for( i=lef; i<=rig; i++ )
        {
            *dest++=*cell(i,j);
        }
    }
    return 1;
}

//---------------------------------------------------------------------------
int screenbuf::putrect(int lef, int top, int rig, int bot, screencell *src)
{
    if( top>bot || top<0 || bot>=sizey || 
        lef>rig || lef<0 || rig>=sizex   )
    {
        return 0;
    }

    if( top<uptop ) uptop=top;
    if( lef<uplef ) uplef=lef;
    if( bot>upbot ) upbot=bot;
    if( rig>uprig ) uprig=rig;

    int i,j;
    for( j=top; j<=bot; j++ )
    {
        for( i=lef; i<=rig; i++ )
        {
            *cell(i,j)=*src++;
            //printf("%d %d %x %x\n",i,j,cell(i,j)->chr,cell(i,j)->attr);
        }
    }
    return 1;
}

//---------------------------------------------------------------------------

