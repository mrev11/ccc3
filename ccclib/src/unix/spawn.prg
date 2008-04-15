
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

#include "spawn.ch"

//Windows spawn emuláció UNIX-on
// a processz fork-ol
// a fork child ága exec-kel indítja a spawn-ban megadott programot
// a fork parent ága a wait/nowait paraméternek megfelelően vár

//hiba: 
// nem lehet egyszerre path-ból indítani és environment-et megadni,
// mert a UNIX-os exec változatok közül hiányzik execvpe (miért??)

//megj: 
// spawn( flag,prog,arg1,arg2,...{env}      )
// exec (      prog,arg1,arg2,...{env},flag )
// _clp_exec() hívásakor eggyel feljebb toljuk a stacket



function spawn(*)

local arg:={*},n,x,i
local err
local path_flag
local wait_flag
local pid
local execblk:={|*|exec(*)}
local status:=-1
local result

    //? "SPAWN", arg

    if( len(arg)<2 )
        err:=errorNew()
        err:operation:="spawn"
        err:description:="argument error"
        err:args:=arg
        break(err)
    end

    if( valtype(arg[1])=="L" )
        path_flag:=.f.
        wait_flag:=arg[1]
    elseif( valtype(arg[1])=="N" )
        path_flag:=(0!=numand(arg[1],SPAWN_PATH))
        wait_flag:=(0!=numand(arg[1],SPAWN_WAIT))
    else
        err:=errorNew()
        err:operation:="spawn"
        err:description:="argument error"
        err:args:=arg
        break(err)
    end
    
    adel(arg,1)
    arg[len(arg)]:=path_flag

    for n:=1 to len(arg)
        if( valtype(arg[n])=="C" )
            arg[n]:=str2bin(arg[n])
        elseif( valtype(arg[n])=="A" )
            x:=array(len(arg[n]))
            for i:=1 to len(x)
                x[i]:=arg[n][i]
                if( valtype(x[i])=="C" )
                    x[i]:=str2bin(x[i])
                end
            next
            arg[n]:=x
        end
    next

    pid:=fork()

    //fork és exec között tilos bármilyen memóriakezelés!
    
    if( pid==0 )
        result:=evalarray(execblk,arg) 

        //csak hiba esetén tér vissza, 
        //pl. ha nem létezik az indítandó program,
        //itt nem célszerű hibakóddal visszatérni,
        //mert ez nem az eredeti program, hanem a duplikátum,
        //és ezért nehéz megfejteni, hogy mi történik

        err:=errorNew()
        err:operation:="spawn"
        err:description:="exec failed"
        err:args:=arg
        err:oscode:=ferror()
        break(err)
        
    elseif( wait_flag )
        waitpid(pid,@status,0)
        result:=status 
        
        //sajnos a status nem nagyon használható,
        //nem az exitcode-ot tartalmazza,
        //hanem, hogy milyen jellegű a program állapotváltása,
        //pl. kilépett, SIGTERM-et, SIGSTOP-ot, SIGCONT-ot kapott.

    else
        result:=pid
    end
    
    return result


// fork()
//
// The new process has a single thread. 
// If a multi-threaded process calls fork(), the new process contains 
// a replica of the calling thread and its entire address space, 
// including the states of mutexes and other resources. Consequently, 
// to avoid errors, the child process may only execute async-signal safe 
// operations until such time as one of the exec() functions is called. 
// Fork handlers may be established using the pthread_atfork() function 
// to maintain application invariants across fork() calls.

// A fork() fenti tulajdonsága miatt nem szerencsés, hogy _clp_exec-ben
// a C paraméterek átkonvertálódnak X-re (binary), ui. az str2bin-ben
// malloc van, ami deadlockot okoz, ha a fork idején egy másik szálban
// a malloc éppen lockolva volt. Workaround-ként itt előre átkonvertáljuk
// a paramétereket még a fork előtt, így a _clp_exec beli konverzió
// már nem csinál semmit.
