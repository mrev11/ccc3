
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

#include <cccapi.h>
#include <screenbuf.h>

//--------------------------------------------------------------------------
// SCREENCHAR savescreen()-nel kapott karakterváltozoból normál text
//--------------------------------------------------------------------------
void _clp_screenchar(int argno)
{
    CCC_PROLOG("screenchar",1);
    screencell *cell=(screencell*)_parb(1);
    int len=_parblen(1)/sizeof(screencell);
    CHAR *str=stringl(len);
    int i;
    for(i=0; i<len; i++)
    {
        str[i]=cell[i].getchar();
    }
    _rettop();
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
//SCREENATTR savescreen()-nel kapott karakterváltozóból attribútumok
//--------------------------------------------------------------------------
void _clp_screenattr(int argno)
{
    CCC_PROLOG("screenattr",1);
    screencell *cell=(screencell*)_parb(1);
    int len=_parblen(1)/sizeof(screencell);
    char *attr=binaryl(len);
    int i;
    for(i=0; i<len; i++)
    {
        attr[i]=(char)cell[i].getattr();
    }
    _rettop();
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
// SCREENCOMPOSE text+attribs-ból restscreen()-ben használható string
//--------------------------------------------------------------------------
void _clp_screencompose(int argno)
{
    CCC_PROLOG("screencompose",2);
    CHAR *ch=_parc(1);
    char *at=_parb(2);
    int lc=_parclen(1);
    int la=_parblen(2);
    if( (lc<=0) || (la!=lc) )
    {
        ARGERROR();
    }
    int i;
    screencell *cell=(screencell*)binaryl(lc*sizeof(screencell));
    for(i=0; i<lc; i++)
    {
        cell[i].setchar(ch[i]);
        cell[i].setattr(at[i]);
    } 
    _rettop();
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
