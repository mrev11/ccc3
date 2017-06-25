

function printlog(additive:=.f.)
local logfile:="log-"+argv(0)::strtran(".exe","")

    if( additive )
        set printer to (logfile)  additive
    else
        set printer to (logfile)
    end

    set printer on
    
    