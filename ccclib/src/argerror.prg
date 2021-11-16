

function argerror(*)
local err:=errorNew()
    err:operation:=procname(1)
    err:description:="argument error"
    err:args:={*}
    break(err)

