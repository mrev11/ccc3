
****************************************************************************
function printnode(o,depth:=0)
local n
    ? replicate(" ",depth)//+"<"+o:classname+">"
    ?? "{"
    ?? "type="+o:type
    ?? ","
    ?? "attrib="
    ?? o:attrib
    ?? ","
    ?? "content={"
    for n:=1 to len(o:content)
        if( valtype(o:content[n])=="C"   ) 
            ?? o:content[n]
        else
            printnode(o:content[n],depth+2)
        end
    next
    ?? "}"
    ?? "}"
    
****************************************************************************
