
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
#include <hashtable_nls.h>
#include <cccapi.h>

static hashtable_nls *nls_hashtable=0;

typedef void hashtable_fill_t(hashtable_nls*);

//----------------------------------------------------------------------------
static void load(char *libname)
{

    HINSTANCE hnd=LoadLibraryEx(libname,NULL,0); 
    if( !hnd )
    {
        fprintf(stderr,"Error: %s not found\n",libname);
        return;
    }

    void *sym=0;

         if( sym=(void*)GetProcAddress(hnd,"hashtable_fill") ); //MSC
    else if( sym=(void*)GetProcAddress(hnd,"_Z14hashtable_fillP13hashtable_nls") ); //GCC 3.x+
    else
    {
        fprintf(stderr,"Error: hashtable_fill not found in %s\n",libname);
        return;
    }
    
    ((hashtable_fill_t*)sym)(nls_hashtable);
    fprintf(stderr,"Loaded: %s\n",libname);
}

//----------------------------------------------------------------------------
void _clp_nls_load_translation(int argno)
{
    CCC_PROLOG("nls_load_translation",2);
    str2bin(base);
    str2bin(base+1);
    char *appl=_parb(1);
    char *lang=ISNIL(2)?getenv("CCC_LANG"):_parb(2);
    if( lang )
    {
        if( !nls_hashtable )
        {
            nls_hashtable=new hashtable_nls();
        }
        char buf[256];
        sprintf(buf,"%s.%s.dll",appl,lang);
        //There is no snprintf in MSC (LOL).
        load(buf);
    }
    _ret();
    CCC_EPILOG();
}

//----------------------------------------------------------------------------
CHAR const *nls_text(CHAR const *str)
{
    CHAR const *p=0;
    if( nls_hashtable && (p=nls_hashtable->get(str)) )
    {
        return p;
    }
    return str;
}

//----------------------------------------------------------------------------

