
static remark:=<<REMARK>>
  úgy indul, hogy nem készít node-okat
  megkeresi az A="8" attribútummal rendelkező x5 node-ot
  és kigyűjti azt a cargoba

<<REMARK>>


****************************************************************************
function main()

local p,n

    ? remark

    p:=xmlparserNew()

    p:file:="x.xml"

    p:info:buildflag:=.f.   //kikapcsolt node építéssel indul
    p:cargo:={}             //user data

    p:nodebeginblock:={|prs,ni|nodebegin(prs,ni)}
    p:nodeendblock:={|prs,ni,node|nodeend(prs,ni,node)}
    p:attribblock:={|prs,an,av|attrib(prs,an,av)}
    
    p:parse 
    ?
    
    for n:=1 to len(p:cargo)
        p:cargo[n]:xmlout
    next

    ?

****************************************************************************
function nodebegin(prs,ni) //parser, nodeinfo
    ? ">>>", ni, prs:cargo
    

****************************************************************************
function nodeend(prs,ni,node)  //parser, nodeinfo, node/NIL
local n

    ? "<<<", ni, prs:cargo
    
    for n:=1 to len(prs:cargo)
        if( prs:cargo[n]==ni )
            prs:cargo[n]:=node          // gyűjt
        end
    next


****************************************************************************
function attrib(prs,an,av)

    //? "ATR",an,av

    if( an=="A" .and. av=='"8"' )
        prs:info:buildflag:=.t.         // node építés bekapcsol
        aadd(prs:cargo,prs:info)        // megjegyzi
    end

//Megjegyzés: Az attribútum érték része a macskaköröm.

****************************************************************************
