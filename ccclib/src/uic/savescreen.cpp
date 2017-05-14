
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
#include <cccapi.h>
#include <termapi.h>

//----------------------------------------------------------------------------
void _clp_savescreen(int argno)
{
    CCC_PROLOG("savescreen",4);

    unsigned top=ISNIL(1)?0:(int)_parnd(1);
    unsigned lef=ISNIL(2)?0:(int)_parnd(2);
    unsigned bot=ISNIL(3)?maxrow():(int)_parnd(3);
    unsigned rig=ISNIL(4)?maxcol():(int)_parnd(4);

    if( top>bot || bot>(unsigned)maxrow() || 
        lef>rig || rig>(unsigned)maxcol() )
    {
        error_gen(CHRLIT("incompatible screen size"),"savescreen",base,4);
    }

    unsigned len=(bot-top+1)*(rig-lef+1)*sizeof(screencell);
    screencell *scr=(screencell*)binaryl(len);
    getrect(lef,top,rig,bot,scr);
    _rettop();
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp_restscreen(int argno)
{
    CCC_PROLOG("restscreen",5);

    unsigned top=ISNIL(1)?0:(int)_parnd(1);
    unsigned lef=ISNIL(2)?0:(int)_parnd(2);
    unsigned bot=ISNIL(3)?maxrow():(int)_parnd(3);
    unsigned rig=ISNIL(4)?maxcol():(int)_parnd(4);
    screencell *scr=(screencell*)_parb(5);
    unsigned len=_parblen(5);

    if( top>bot || bot>(unsigned)maxrow() || 
        lef>rig || rig>(unsigned)maxcol() ||
        ((bot-top+1)*(rig-lef+1)*sizeof(screencell))!=len )
    {
        error_gen(CHRLIT("incompatible screen size"),"restscreen",base,5);
    }

    putrect(lef,top,rig,bot,scr);
    _ret();
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
void _clp_screeninv(int argno)
{
    CCC_PROLOG("screeninv",1);
    screencell *scr=(screencell*)_parb(1);
    int blen=_parblen(1);
    int clen=blen/sizeof(screencell);
    screencell *inv=(screencell*)binaryl(blen);
    int i;
    for( i=0; i<clen; i++)
    {
        int c=scr[i].getchar();
        int a=scr[i].getattr();
        inv[i].setchar(c);
        if( a&0xff00 )
        {
            inv[i].setattr(((0xff00&a)>>8)+((0x00ff&a)<<8));
        }
        else
        {
            inv[i].setattr(((0xf0&a)>>4)+((0x0f&a)<<4));
        }
    }
    _rettop();
    CCC_EPILOG();
}


//----------------------------------------------------------------------------
