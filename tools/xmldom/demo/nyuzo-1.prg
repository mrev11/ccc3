


****************************************************************************
function main(build)
local p,dom,n:=0

    thread_create({||dogc()})

    p:=xmlparserNew()

    //p:file:="example.xml"
    p:file:="z.xml"
    
    if(build==NIL)
        p:info:buildflag:=.f.
    end
    
    ? "buildflag", p:info:buildflag

    p:nodebeginblock:={|prs,ni|nodebegin(prs,ni)}
    //p:nodeendblock:={|prs,ni,node|nodeend(prs,ni,node)}
    p:contentblock:={|prs,node|content(prs,node)}

    while(.t.)
        dom:=p:parse 
        if( ++n%100==0 )
            ?? "."
        end
    end


****************************************************************************
function nodebegin(prs,ni) //parser, nodeinfo

    if( ni:type=="include" )
        prs:info:buildflag:=.t.     //hogy működjön az include
    end

****************************************************************************
function content(prs,node)
local p,dom

    if( node:type=="include" )
        p:=prs:copy
        p:file:=node:getattrib("file")
        
        //részfa bekapcsolás
        dom:=p:parse
        node:type:=dom:type
        node:content:=dom:content
        node:attrib:=dom:attrib
    end
    
    return .t.


****************************************************************************
function dogc()
    ? thread_self()
    while(.t.)
        sleep(10)
        gc()
    end

****************************************************************************
