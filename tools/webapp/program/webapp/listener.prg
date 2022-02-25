

***************************************************************************************
function sck_listener()
static sck
    if(sck==NIL)
        sck:=socketNew()
        sck:reuseaddress(.t.) //élesből kivenni
        sck:bind(param_iface(),param_port())
    end
    return sck

***************************************************************************************
