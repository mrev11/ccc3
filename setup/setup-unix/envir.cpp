
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
#include <wchar.h>
#include <cccapi.h>
#include <fileconv.ch>

//-----------------------------------------------------------------------------
void _clp_getenv(int argno)  //Clipper
{
    CCC_PROLOG("getenv",1);
    if( DOSCONV & DOSCONV_ENVVAR2UPPER )
    {
        _clp_upper(1);
    }
    str2bin(base);
    const char *var=_parb(1);
    const char *env=getenv(var);
    _retcb( env?env:"" );
    CCC_EPILOG();
}

//-----------------------------------------------------------------------------
void _clp_putenv(int argno) //nincs NG-ben,  putenv("ID=value")
{
    CCC_PROLOG("putenv",1);

    CHAR *str=_parc(1);
    CHAR *equ=NULL;
              
    if( (_parclen(1)==0) || (NULL==(equ=wcschr(str,'='))) )
    {
        _retl(0); //nem megfelelő formátum
    }

    else if( *(equ+1) ) //set, ha NEM '=' az utolsó karakter
    {
        strings(str,equ-str);
        if( DOSCONV & DOSCONV_ENVVAR2UPPER )
        {
            _clp_upper(1);
        }
        stringn(equ);
        add();
        str2bin(TOP());
        _retl( putenv(strdup(BINARYPTR(TOP())))==0 );
        
        //A manpage nem ír semmit arról, hogy putenv/setenv készít-e
        //másolatot az argumentumáról. Az OpenLinux 2.2, Corel Linux,
        //Debian-slink készít, azonban a SuSE 6.3 NEM! Így SuSE 6.3
        //alatt a szemétgyűjtés letakarítja azt a stringet, amit
        //putenv-nek megadtunk, ezért azt strdup-pal le kell másolni.
        //Sajnos így memória zárványok keletkeznek. NT-n is így van.
    }

    else //unset, ha '=' az utolsó karakter 
    {          
        strings(str,equ-str);
        if (DOSCONV & DOSCONV_ENVVAR2UPPER)
        {
            _clp_upper(1);
        }

        #if defined _SOLARIS_
          stringn(L"=");
          add();
          str2bin(TOP());
          _retl( putenv(strdup(BINARYPTR(TOP())))==0 );

        #elif defined _LINUX_
          str2bin(TOP());
          unsetenv( BINARYPTR(TOP()) ); //void!
          _retl( 1 );

        #elif defined _FREEBSD_
          str2bin(TOP());
          unsetenv( BINARYPTR(TOP()) ); //void!
          _retl( 1 );

        #else //#elif defined _NETBSD_
          str2bin(TOP());
          unsetenv( BINARYPTR(TOP()) ); //void!
          _retl( 1 );
        #endif
    }
 
    CCC_EPILOG();    
}

//-----------------------------------------------------------------------------
void _clp_environment(int argno) //egész környezet
{
    CCC_PROLOG("environment",0);
    extern char **environ;
    char **env=environ;
    int n=0;
    while( *env )
    {
        stringnb(*env);
        n++;
        env++;
    }
    array(n);
    _rettop();
    CCC_EPILOG();
}
 
//-----------------------------------------------------------------------------

