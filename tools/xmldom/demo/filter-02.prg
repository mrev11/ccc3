

static remark:=<<REMARK>>
  úgy indul, hogy nem készít node-okat
  x4 típusú node-oknál bekapcsolja a node építést
  de nem kéri az x6 node-okat (újra kikapcsol)

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
    
    p:parse 
    
    for n:=1 to len(p:cargo)
        ?
        p:cargo[n]:xmlout
    next

    ?

****************************************************************************
function nodebegin(prs,ni) //parser, nodeinfo
    
    if( ni:fullpath=="/x1/x2/x3/x4" )
        prs:info:buildflag:=.t.     //jön az érdekes rész

    elseif( ni:fullpath=="/x1/x2/x3/x4/x5/x6"  )
        prs:info:buildflag:=.f.     //ez nem kell
    end

    ? ">>>", ni
    

****************************************************************************
function nodeend(prs,ni,node)  //parser, nodeinfo, node/NIL

    ? "<<<", ni, node

    if( ni:fullpath=="/x1/x2/x3/x4" )
        aadd(prs:cargo,node)    //gyűjt
    end


****************************************************************************
