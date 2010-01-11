
static remark:=<<REMARK>>
  úgy indul, hogy nem készít node-okat
  x4 típusú node-oknál bekapcsolja a node építést
  a cargo-ban kigyűjti az x4 node-okat
  mindenhol kiírja a nodeinfo-t

<<REMARK>>


****************************************************************************
function main()

local p,n

    ? remark

    p:=xmlparser2New()
    p:file:="x.xml"
    p:info:buildflag:=.f.   //kikapcsolja a node építést
    p:cargo:={}             //tetszőleges adat

    p:nodebeginblock:={|prs,ni|nodebegin(prs,ni)}
    p:nodeendblock:={|prs,ni,node|nodeend(prs,ni,node)}
    
    p:parse 
    p:list
    ?
    
    for n:=1 to len(p:cargo)
        ?
        printnode(p:cargo[n])
        p:cargo[n]:xmlout
    next

    ?

****************************************************************************
function nodebegin(prs,ni) //parser, nodeinfo

    if( ni:type=="x4" )
        prs:info:buildflag:=.t. //jön az érdekes rész
    end

    ? ">>>", ni
    

****************************************************************************
function nodeend(prs,ni,node)   //parser, nodeinfo, node/NIL
    ? "<<<", ni //, node

    if( ni:type=="x4" /*.and. node!=NIL*/ )
        aadd(prs:cargo,node)    //gyűjti az x4-eket
    end


****************************************************************************
