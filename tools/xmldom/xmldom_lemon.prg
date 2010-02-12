

//minden Lemon szabályhoz egy Clipper függvény,
//aminek a neve a szabályból van származtatva

namespace xmldom.lemon

***************************************************************************************
function xmlv__root_xmldecl_content(this,c)
local node
    //? this:lemon
    node:=xmlnodeNew("#ROOT")
    node:content:=this:lemon[c]
    asize(this:lemon,0)
    return node //végeredmény


***************************************************************************************
function xmlv__xmldecl_node(this,n)
local node:=this:lemon[n]
    //? this:lemon
    asize(this:lemon,0)
    if( !empty(this:process(node)) )
        node:=NIL
    end
    return node //végeredmény


***************************************************************************************
function xmldecl__lparqm_qsymbol_attrlist_qmrpar(this,s,a)
local info:=this:lemon[s],node,enc

    node:=xmlnodeNew(info:type)
    node:attrib:=this:lemon[a]
    enc:=node:getattrib("encoding")
    if( enc!=NIL  )
        xmldom.lexer.setencoding(this:lexer,enc)
    end
    if( empty(this:process(node)) )
        this:qmxml:=node
    end
    this:infopop
    asize(this:lemon,s-1)


***************************************************************************************
function node__lpar_symbol_attrlist_slash_rpar(this,s,a)
local info:=this:lemon[s],node

    if( info:buildflag )
        node:=xmlnodeNew(info:type)
        node:attrib:=this:lemon[a]
    end

    if( this:nodeendblock!=NIL )
        eval(this:nodeendblock,this,info,node)
    end

    this:infopop

    this:lemon[s]:=node
    asize(this:lemon,s)
    return s


***************************************************************************************
function node__lpar_symbol_attrlist_rpar_content_lpar_slash_symbol_rpar(this,s1,a,c,s2)
local info:=this:lemon[s1],node,err

    if( !info:type==s2 )
        err:=xmltagerrorNew()
        err:subsystem:="XMLDOM"
        err:operation:="xmldom_parser"
        err:filename:=xmldom.lexer.inputfspec(this:lexer)
        err:description:="tag mismatch <"+info:type+"></"+s2+"> near #line "+alltrim(str(xmldom.lexer.lineno(this:lexer)))
        break(err)
    end

    if( info:buildflag )
        node:=xmlnodeNew(s2)
        node:attrib:=this:lemon[a]
        node:content:=this:lemon[c]
    end

    if( this:nodeendblock!=NIL )
        eval(this:nodeendblock,this,info,node)
    end

    this:infopop

    this:lemon[s1]:=node
    asize(this:lemon,s1)
    return s1


***************************************************************************************
function tnode__text(this,t)
local node
    if( this:textnodeblock!=NIL )
        eval(this:textnodeblock,this,t)
    end
    if( this:info:buildflag )
        node:=xmlnodeNew("#TEXT")
        node:content:={t}
    end
    aadd(this:lemon,node)
    return len(this:lemon)


***************************************************************************************
function tnode__cdata(this,t)
local node
    if( this:textnodeblock!=NIL )
        eval(this:textnodeblock,this,t)
    end
    if( this:info:buildflag )
        node:=xmlnodeNew("#CDATA")
        node:content:={t}
    end
    aadd(this:lemon,node)
    return len(this:lemon)


***************************************************************************************
function content__(this)
    aadd(this:lemon,{})
    return len(this:lemon)


***************************************************************************************
function content__content_tnode(this,c,n)
local node
    if( (node:=this:lemon[n])!=NIL )

        if( this:contentblock!=NIL )
            if( eval(this:contentblock,this,node) )
                aadd(this:lemon[c],node)
            end
        elseif( empty(this:process(node)) )
            aadd(this:lemon[c],node)
        end
    end
    asize(this:lemon,c)
    return c


***************************************************************************************
function content__content_node(this,c,n)
local node
    if( (node:=this:lemon[n])!=NIL )

        if( this:contentblock!=NIL )
            if( eval(this:contentblock,this,node) )
                aadd(this:lemon[c],node)
            end
        elseif( empty(this:process(node)) )
            aadd(this:lemon[c],node)
        end
    end
    asize(this:lemon,c)
    return c


***************************************************************************************
function symbol__symbol(this,s)
local info:=this:infopush(s)
    if( this:nodebeginblock!=NIL )
        eval(this:nodebeginblock,this,info)
    end
    aadd(this:lemon,info)
    return len(this:lemon)


***************************************************************************************
function qsymbol__symbol(this,s)
local info,err
    if( !s=="xml" )
        err:=xmlsyntaxerrorNew()
        err:subsystem:="XMLDOM"
        err:operation:="xmldom_parser"
        err:filename:=xmldom.lexer.inputfspec(this:lexer)
        err:description:="invalid declaration syntax <?"+s+"...?> near #line "+alltrim(str(xmldom.lexer.lineno(this:lexer)))
        break(err)
    end
    info:=this:infopush("?"+s)
    info:buildflag:=.t.
    aadd(this:lemon,info)
    return len(this:lemon)


***************************************************************************************
function attrlist__(this)
    aadd(this:lemon,{})
    return len(this:lemon)


***************************************************************************************
function attrlist__attrlist_symbol_eq_string(this,r,n,v)
    if( this:attribblock!=NIL )
        eval(this:attribblock,this,n,v)
    end
    if( this:info:buildflag )
        aadd(this:lemon[r],xmlattribNew(n,v))
    end
    return r


***************************************************************************************
static function lemstk(this,ret)
local n
    ? ret
    for n:=1 to len(this:lemon)
        ? str(n,3), this:lemon[n]
    next

***************************************************************************************


