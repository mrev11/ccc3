
#include "signal.ch"

*****************************************************************************
function sighandler(signum)
local err, block:=SIG_PIPE//+SIG_INT //ezeket elnyomja
    if( numand(signum,block)!=0 ) 
        ? signal_description(signum)
    else
        err:=errorNew() 
        err:description:=signal_description(signum)
        err:subcode:=signum
        err:subsystem:="SIGNAL"
        break(err)
    end

*****************************************************************************
