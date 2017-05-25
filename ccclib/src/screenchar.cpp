
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
static int trans_ext2leg( int x )
{
    static int tab_ext2leg[129]={0,0,1,1,1,9,9,9,2,2,3,3,1,9,9,9,2,10,2,10,3,11,9,9,10,10,10,10,10,10,11,11,4,4,5,5,1,9,9,9,6,6,8,8,1,9,9,9,2,10,2,10,3,11,9,9,10,10,10,10,10,10,11,11,4,12,4,12,5,13,9,9,4,12,4,12,5,13,9,9,6,14,6,14,7,7,9,9,10,10,10,10,10,10,11,11,12,12,12,12,12,12,13,13,12,12,12,12,12,12,13,13,12,12,12,12,12,12,13,13,14,14,14,14,14,14,7,15,0};
    return tab_ext2leg[x&0x7f];   // jelzobit leveve
}

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
        int a=cell[i].getattr();
        if( 0xff00&a  )
        {
            //extended
            int fg=trans_ext2leg( 0x7f&(a>>0) );
            int bg=trans_ext2leg( 0x7f&(a>>8) );
            attr[i]=(char)(fg+(bg<<4));
        }
        else
        {
            //legacy
            attr[i]=(char)a;
        }
    }
    _rettop();
    CCC_EPILOG();
}

// a 2 bajtos (extended) attributumokat 1 bajtosra kell konvertalni,
// maskepp tobb program is borul, amik 1 bajtos attributumot varnak,
// pl: msk2say, msk2html es tarsaik


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
    
    if( (lc<=0) || ((la!=lc) && (la/2!=lc)) )
    {
        ARGERROR();
    }
    int i;
    screencell *cell=(screencell*)binaryl(lc*sizeof(screencell));
    for(i=0; i<lc; i++)
    {
        cell[i].setchar(ch[i]);
        if( la==lc )
        {
            cell[i].setattr(at[i]);  //1 bajtos szinpar
        }
        else
        {
            cell[i].setattr( at[i<<1] + (at[(i<<1)+1]<<8) ); //2 bajtos szinpar
        }
    } 
    _rettop();
    CCC_EPILOG();
}

// az attributumok lehetnek 1 vagy 2 bajtosak
// az attributumtomb hosszabol kovetkeztet az esetre
   

//--------------------------------------------------------------------------
