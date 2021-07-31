
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
#include <unistd.h>
#include <sys/wait.h>
#include <cccapi.h>

//--------------------------------------------------------------------------
void _clp_wait(int argno)  
{
    CCC_PROLOG("wait",1);
    int status = 0; //kimenet

    int result = wait(&status);

    number(status);
    assign(PARPTR(1));
    _retni( result ) ;
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp_waitpid(int argno)  

// waitpid(pid,@status,0)  vár, míg pid kilép
// waitpid(pid,@status,1)  nem vár, jelzi pid kilépését, takarítja a zombikat

{
    CCC_PROLOG("waitpid",3);
    pid_t pid  = ISNUMBER(1)?_parni(1):0;
    int status = 0; //kimenet
    int mode   = ISNUMBER(3)?_parni(3):0;  //0:várakozik, 1:WNOHANG

    int xmode  = 0; //UNIX mode
    if( mode&1 ) xmode|=WNOHANG;

    int result = waitpid(pid,&status,xmode);

    number(status);
    assign(PARPTR(2));
    _retni( result ) ;
    CCC_EPILOG();
}

//--------------------------------------------------------------------------

