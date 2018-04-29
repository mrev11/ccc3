
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

//--------------------------------------------------------------------------
void _clp_argc(int argno)
{
    CCC_PROLOG("argc",0);
    _retni(ARGC);
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_argv(int argno)
{
    CCC_PROLOG("argv",1);
    int i;
        
    if( ISNUMBER(1) )
    {
        i=_parni(1);
        
        if (i<0 || i>=ARGC)
        {
            _ret();
        }
        else
        {
            unsigned reslen=0;
            CHAR *p=utf8_to_wchar(ARGV[i],0,&reslen);
            _retclen(p,reslen);
            free(p);
        }
    }
    else
    {
        array0(ARGC-1);
        VALUE *a=TOP();
        for(i=1;i<ARGC;i++)
        {
            unsigned reslen=0;
            CHAR *p=utf8_to_wchar(ARGV[i],0,&reslen);
            strings(p,reslen);
            free(p);
            ARRAYPTR(a)[i-1]=*TOP();
            POP();
        }
        _rettop();
    }
    
    CCC_EPILOG();
}

//--------------------------------------------------------------------------

