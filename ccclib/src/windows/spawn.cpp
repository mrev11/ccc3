
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

#include <process.h>
#include <cccapi.h>

#include <spawn.ch>
 
//------------------------------------------------------------------------
void _clp_spawn(int argno)

// Kombinált spawn, hívási formák:
// spawn(FLAG,prog,arg1,arg2,...,{env} )
// spawn(SPAWN_WAIT+SPAWN_PATH,prog,arg1,arg2,...,{env} )
// spawn(SPAWN_WAIT+SPAWN_PATH,{prog,arg1,arg2,...},{env} )
 
{
    VALUE *base=stack-argno;
    push_call("spawn",base);

    if( argno<2 )
    {
        ARGERROR();
    }
    
    int i;
    int flag_wait=0;
    int flag_path=0;
    int flag_envx=0;
    
    if( ISNUMBER(1) )
    {
        flag_wait = SPAWN_WAIT & _parni(1); 
        flag_path = SPAWN_PATH & _parni(1); 
    }
    else if( ISFLAG(1) ) 
    {
        flag_wait = _parl(1); 
        flag_path = 0;
    }
    else
    {
        ARGERROR();
    }

    char **argv=0;
    
    if( ISARRAY(2) )
    {
        argv=(char**)binaryl((_paralen(2)+1)*sizeof(char*));

        for( i=0; i<_paralen(2); i++ )
        {
            PUSH(_parax(2,i));
            str2bin(TOP());
            argv[i]=BINARYPTR(TOP());
        }
        argv[i]=0;

        if( argno<3 || ISNIL(3) )
        {
            flag_envx=0;
        }
        else if( ISARRAY(3) )
        {
            flag_envx=3;
        }
        else
        {
            ARGERROR();
        }
    }
    else
    {
        argv=(char**)binaryl(argno*sizeof(char*));
        str2bin(PARPTR(2));
        argv[0]=_parb(2);
        for( i=3; i<=argno && !ISARRAY(i); i++ )
        {
            str2bin(PARPTR(i));
            argv[i-2]=_parb(i);
        }
        argv[i-2]=0;
        
        if( i>argno )
        {
            flag_envx=0;
        }
        else if( i==argno && ISARRAY(argno) )
        {
            flag_envx=argno;
        }
        else
        {
            ARGERROR();
        }
    }

    int result;
    flag_wait=flag_wait?P_WAIT:P_NOWAIT;

    if( !flag_envx )
    {
        if( !flag_path )
        {
            result=spawnv(flag_wait,argv[0],argv); 
        }
        else
        {
            result=spawnvp(flag_wait,argv[0],argv ); 
        }
    }
    else
    {
        char **envp=0;
        envp=(char**)binaryl((_paralen(flag_envx)+1)*sizeof(char*));

        for( i=0; i<_paralen(flag_envx); i++ )
        {
            PUSH(_parax(flag_envx,i));
            str2bin(TOP());
            envp[i]=BINARYPTR(TOP());
        }
        envp[i]=0;

        if( !flag_path )
        {
            result=spawnve(flag_wait,argv[0],argv,envp);
        }
        else
        {
            result=spawnvpe(flag_wait,argv[0],argv,envp);
        }
    }

    stack=base;
    number(result);
    pop_call();
}

//------------------------------------------------------------------------
