
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
#include <string.h>
#include <signal.h>
#include <xsigset.h>


#ifdef WINDOWS
//--------------------------------------------------------------------------
void xsigset(int signum, sighandler_t sighnd)
{
    //empty
}

//--------------------------------------------------------------------------
void xsigset_handlers()
{
    //empty
}

//--------------------------------------------------------------------------
#endif



#ifdef _UNIX_
//--------------------------------------------------------------------------
void xsigset(int signum, sighandler_t sighnd)
{
    struct sigaction act;
    memset(&act,0,sizeof(act));
    act.sa_handler=sighnd;
    sigaction(signum,&act,0);
}

//--------------------------------------------------------------------------
void xsigset_handlers()
{
    xsigset(SIGCHLD,SIG_IGN); //zombik ellen 2021.02.13
}

//--------------------------------------------------------------------------
#endif


