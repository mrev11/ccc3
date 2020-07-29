
#include "fileio.ch"

******************************************************************************
function main()

local semafd:=semafd()
local result

    fwaitlock_w(semafd,1,1)
    result:=fwaitlock_w(semafd,0,1)
    funlock(semafd,1,1)

    if( result==0 )
        ? "CCC_LOCK_SEMAPHOR locked, hit any key ..."
        inkey(0)
        funlock(semafd,0,1)
        ? "CCC_LOCK_SEMAPHOR unlocked"
    else
        ? "CCC_LOCK_SEMAPHOR failed"
    end
    ?


******************************************************************************
static function semafd()
local sema,fd:=-1
    sema:=getenv("CCC_LOCK_SEMAPHOR")
    if( empty(sema) )
        ? "CCC_LOCK_SEMAPHOR variable is not set"
    elseif( !file(sema) )
        ? "CCC_LOCK_SEMAPHOR file does not exist", sema
    elseif( 0>(fd:=fopen(sema,FO_NOLOCK+FO_READWRITE)) )
        ? "Cannot open CCC_LOCK_SEMAPHOR file", sema
    end
    if( fd<0 )
        ?
        quit
    end
    return fd


******************************************************************************
