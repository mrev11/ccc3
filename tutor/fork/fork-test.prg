
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



// OTTHON NE PROBALD KI!
// ami itt tortenik, azt a POSIX tiltja
// fork es exec kozott csak ASYNC-SIGNAL-SAFE muveleteket szabad vegezni
// a CCC dolgok (bar latszolag mukodnek) vastagon nem ASYNC-SIGNAL-SAFE-ek
// ez csak egy kiserlet, nem lehet kijavitani, es nincs is sok haszna
// eles alkalmazasban nem szabad hasznalni

// ez a program hibas
// csak azert mukodik (latszolag), mert a fork() hivasok idoben ritkak
// es ezert csak kis valoszinuseggel hagynak inkonzistens allapotot a childban


#include "fileio.ch"
#include "fork.ch"


function main()

local fd,rl,line
local counter:=0
local key

    fd:=fopen("readline.prg",FO_READ)
    ? "FD",fd
    ? "SCKTERM", sckterm()
    ?

    rl:=readlineNew(fd)
    while( (line:=rl:readline)!=NIL )

        sleep(200)

        ?? ++counter,"  "

        if( counter==999 )
            key:="quit"
        elseif( (counter%7)==0 )
            key:="gc"
        elseif( (counter%11)==0 )
            key:="alert"
        elseif( (counter%13)==0  )
            key:="fork"
        else
            key:="_"
        end


        if( key[1]=="q" )
            exit

        elseif( key[1]=="g" )
            gc()
            ?? "gc";?

        elseif( key[1]=="a" )
            ?? "alert";?
            alert("PID"+str(getpid()))

        elseif( key[1]=="f" )

            if( fork(FORK_GC+FORK_SIG+FORK_TERM)==0 )
                // child
                ?? "fork"
            else
                // parent
                quit
            end
            ?

        else
            ??  getpid(), line
        end

    end
    ?


