
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
// SCREENCHAR savescreen()-nel kapott karaktervaltozobol normal text
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
//SCREENATTR savescreen()-nel kapott karaktervaltozobol attributumok
//--------------------------------------------------------------------------
void _clp_screenattr(int argno)
{
    int attrsize=sizeof(screencell)/2; // CCC2:1, CCC3:2

    CCC_PROLOG("screenattr",1);
    screencell *cell=(screencell*)_parb(1);
    int len=_parblen(1)/sizeof(screencell);
    char *attr=binaryl(len*attrsize);

    for(int i=0; i<len; i++)
    {
        int fg=cell[i].get_fg();
        int bg=cell[i].get_bg();

        if( attrsize==1 )
        {
            attr[i]=fg+(bg<<4);
        }
        else
        {
            attr[(i<<1)+0]=fg;
            attr[(i<<1)+1]=bg;
        }
    }
    _rettop();
    CCC_EPILOG();
}


void _clp_screen_fg(int argno)
{
    CCC_PROLOG("screen_fg",1);
    screencell *cell=(screencell*)_parb(1);
    int len=_parblen(1)/sizeof(screencell);
    char *attr=binaryl(len);

    for(int i=0; i<len; i++)
    {
        attr[i]=cell[i].get_fg();
    }

    _rettop();
    CCC_EPILOG();
}

void _clp_screen_bg(int argno)
{
    CCC_PROLOG("screen_bg",1);
    screencell *cell=(screencell*)_parb(1);
    int len=_parblen(1)/sizeof(screencell);
    char *attr=binaryl(len);

    for(int i=0; i<len; i++)
    {
        attr[i]=cell[i].get_bg();
    }

    _rettop();
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
// SCREENCOMPOSE text+attribs-bol restscreen()-ben hasznalhato string
//--------------------------------------------------------------------------
void _clp_screencompose(int argno)
{
    CCC_PROLOG("screencompose",3);

    CHAR *ch=_parc(1);
    int lc=_parclen(1);
    if( lc<=0 )
    {
        ARGERROR();
    }

    screencell *cell=(screencell*)binaryl(lc*sizeof(screencell));

    char *at=0; int la=0;
    char *fg=0; int lf=0;
    char *bg=0; int lb=0;

    if( argno==2 )
    {
        at=_parb(2);
        la=_parblen(2);

        if( (la!=lc) && (la/2!=lc) )
        {
            ARGERROR();
        }

        int attrsize=sizeof(screencell)/2; // CCC2:1, CCC3:2

        for(int i=0; i<lc; i++)
        {
            cell[i].setchar(ch[i]);
            if( attrsize==1 )
            {
                // CCC2: 1 bajtos fg/bg
                cell[i].setattr(at[i]);
            }
            else
            {
                // CCC3: 2 bajtos fg/bg
                cell[i].set_fg( at[(i<<1)+0] );
                cell[i].set_bg( at[(i<<1)+1] );
            }
        }
    }

    else if( argno==3 )
    {
        fg=_parb(2);
        lf=_parblen(2);

        bg=_parb(3);
        lb=_parblen(3);

        if( (lf!=lc) || (lb!=lc) )
        {
            ARGERROR();
        }

        for(int i=0; i<lc; i++)
        {
            cell[i].setchar(ch[i]);
            cell[i].set_fg( fg[i] );
            cell[i].set_bg( bg[i] );
        }
    }
    else
    {
        ARGERROR();
    }

    _rettop();
    CCC_EPILOG();
}


//--------------------------------------------------------------------------
