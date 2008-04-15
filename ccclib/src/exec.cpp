
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

#ifdef _UNIX_
    #include <unistd.h>
#else
    #include <process.h>
#endif

#include <stdio.h>
#include <cccapi.h>

#define MAXARG  128
#define MAXENV 1024
 
//--------------------------------------------------------------------------
void _clp_exec(int argno)

// Kombinált exec, hívási formák:
//
// exec(prog,arg1,arg2,...)
// exec(prog,arg1,arg2,...,flagPath)
// exec({prog,arg1,arg2,...},flagPath)
// exec(prog,arg1,arg2,...,{env},flagPath)
// exec({prog,arg1,arg2,...},{env},flagPath)
// stb.
 
{
    VALUE *base=stack-argno;
    push_call("exec",base);

    if( argno<1 )
    {
        ARGERROR();
    }

    int i;
    int flag_envx=0;
    int flag_path=0;
    int maxarg=max(argno,ISARRAY(1)?_paralen(1):0);
    
    #if defined BORLAND || defined MSVC
        char *argv[MAXARG];
    #else
        char *argv[maxarg+1];
    #endif
    
    if( ISARRAY(1) )
    {
        for( i=0; i<_paralen(1); i++ )
        {
            push(_parax(1,i));
            _clp_str2bin(1);
            argv[i]=BINARYPTR(TOP());
            //argv[i]=STRINGPTR(_parax(1,i));
        }
        argv[i]=0;
        i=2;
    }
    else
    {
        push_symbol(base);
        _clp_str2bin(1);
        argv[0]=BINARYPTR(TOP());
        //argv[0]=_parc(1);

        for( i=2; i<=argno && !ISARRAY(i) && !ISFLAG(i); i++ )
        {
            push_symbol(base+i-1);
            _clp_str2bin(1);
            argv[i-1]=BINARYPTR(TOP());
            //argv[i-1]=_parc(i);
        }
        argv[i-1]=0;
    }

    for( ; i<=argno; i++ )
    {
        if( ISNIL(i) )
        {
            //kihagy
        }
        else if( ISARRAY(i) )
        {
            flag_envx=i;
        }
        else if( ISFLAG(i) )
        {
            flag_path=_parl(i);
        }
        else
        {
            ARGERROR();
        }
    }

    int result;
 
    if( !flag_envx )
    {
        if( !flag_path )
        {
            result=execv(argv[0],argv); 
        }
        else
        {
            result=execvp(argv[0],argv); 
        }
    }
    else
    {
        #if defined BORLAND || defined MSVC
            char *envp[MAXENV];
        #else
            char *envp[_paralen(flag_envx)+1];
        #endif

        for( i=0; i<_paralen(flag_envx); i++ )
        {
            push(_parax(flag_envx,i));
            _clp_str2bin(1);
            envp[i]=BINARYPTR(TOP());
            //envp[i]=STRINGPTR(_parax(flag_envx,i));
        }
        envp[i]=0;

        if( !flag_path )
        {
            result=execve(argv[0],argv,envp);
        }
        else
        {
            #ifdef _UNIX_
                result=execve(argv[0],argv,envp); //miért nincs execvpe ??
            #else
                result=execvpe(argv[0],argv,envp); 
            #endif
        }
    }

    stack=base;
    number(result);
    pop_call();
}

//--------------------------------------------------------------------------
