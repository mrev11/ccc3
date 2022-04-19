
function listxml(fspec)
local doc:=memoread(fspec)::split(chr(10)),n
    for n:=1 to len(doc)
        ? str(n,3),doc[n]
    next

