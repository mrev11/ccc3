


****************************************************************************
function main(build)

    thread_create({||dogc()})
    thread_create({||doparse(build)})
    thread_create({||doparse(build)})
    thread_create({||doparse(build)})
    thread_create({||doparse(build)})
    thread_create({||doparse(build)})
    thread_create({||doparse(build)})
    thread_create({||doparse(build)})
    thread_create({||doparse(build)})
    
    inkey(0)



****************************************************************************
function doparse(build)
local p,dom,n:=0

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
        sleep(12*rand())
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
    while(.t.)
        gc()
        sleep(10)
    end

****************************************************************************
