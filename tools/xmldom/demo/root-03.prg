
static remark:=<<REMARK>>
  multiroot document
  xmlparse típusú parserrel elemezve készül egy mesterséges #ROOT node
  az xml deklaráció kihagyását külön meg kell írni

<<REMARK>>


****************************************************************************
function main()
local p,dom

    ? remark

    p:=xmlparserNew("m.xml")
    p:processblock({|node|process(node)})
    dom:=p:parse 
    printnode(dom)
    
    dom:xmlout

    ?

****************************************************************************
static function process(node)
    if( node:type=="?xml" )
        return .t.
    end

****************************************************************************
    