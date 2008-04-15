
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

#include <ctype.h>
#include <string.h>
#include <cccapi.h>

#ifdef EMLEKEZTETO
    Amikor CCC2-es program fut UTF-8 kódolású adatokon,
    akkor a QOut-ban levő karakterkonverziót ki kell kapcsolni,
    ezért itt átdefiniáljuk a charconv_* függvényeket üresre.
    Ez mellékhatásként az upper/lowert is hatástalanítja,
    ezért ezeket újradefiniáljuk charconv nélkül.
#endif

//---------------------------------------------------------------------
void charconv_string(int tab, char *buf, unsigned int len)
{
}

//---------------------------------------------------------------------
int charconv_char(int tab, int c)
{
    return c;
}


//---------------------------------------------------------------------
void charconv_top(int tab)
{
}

//---------------------------------------------------------------------
void _clp__charconv(int argno)
{
    stack-=(argno-1);
}

//---------------------------------------------------------------------
void _clp_lower(int argno)
{
    CCC_PROLOG("lower",1);
    char *p=_parc(1);
    int len=_parclen(1);
    char *r=stringl(len);
    for(int i=0; i<len; i++)
    {
        r[i]=tolower(p[i]);
    }
    _rettop();
    CCC_EPILOG();
}

//---------------------------------------------------------------------
void _clp_upper(int argno)
{
    CCC_PROLOG("upper",1);
    char *p=_parc(1);
    int len=_parclen(1);
    char *r=stringl(len);
    for(int i=0; i<len; i++)
    {
        r[i]=toupper(p[i]);
    }
    _rettop();
    CCC_EPILOG();
}

//---------------------------------------------------------------------
