

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


