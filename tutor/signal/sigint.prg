
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

//Hogyan kapják a szálak a SIGINT-et (CTRL-C-t)?
//
//Linux (2.4)   : minden szál megkapja
//Linux (2.6)   : csak a gyökér szál kapja meg
//Solaris-10    : csak a gyökér szál kapja meg
//FreeBSD 5.3   : ??
//Windows       : a SIGINT kezelésére új szál indul

#include "signal.ch"

#command THREAD(<list,...>)  => thread_detach(thread_create(<list>))

*****************************************************************************
function main()
    signalblock({|s|sighandler(s)})

    ? getpid(), thread_self()

    THREAD({|x|var(x)},"X")
    THREAD({|x|var(x)},"Y")
    THREAD({|x|var(x)},"Z")

    while( inkey(1)!=113 ) //q
    end

*****************************************************************************
static function var(x)
    while(.t.)
        sleep(2000)
        ? x, getpid(), thread_self()
    next

*****************************************************************************
static function sighandler(signum)
    if( signum==SIG_INT )
        ? "SIG_INT", getpid(), thread_self()
    else
        ? "Signal:",signum,getpid(), thread_self()
    end

*****************************************************************************
